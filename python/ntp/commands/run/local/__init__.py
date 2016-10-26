"""
    run local:  Runs the n-tuple production on the current machine.
                All run commands require a valid grid certificate as they
                either read data from the grid via XRootD or run on grid
                resources.
                The command will use python/run/miniAODToNTuple_cfg.py.
        Usage:
            run local [campaign=<X>]  [dataset=<X>] [files=file1,file2,..]
                      [nevents=<N>] [noop=false] [output_file=<file name>]

        Parameters:
            campaign: which campaign to run. Corresponds to the folder
                      structure in crab/*
                      Default is 'Test'.
            dataset:  Alias for the single dataset you want to run over. Corresponds
                      to the file names (without extension) in crab/*/*.py.
                      Accepts wild-cards and comma-separated lists.
                      Default is 'TTJets_PowhegPythia8'.
                      This parameter is ignored if parameter file is given.
            files:    Instead of running on a specific dataset, run over the
                      given (comma-separated) list of files
            nevents:  Number of events to process.
                      Default is 1000.
            noop:     'NO OPeration', will not run CMSSW. Default: false
            output_file: Name of the output file. Default: ntuple.root
            json_url: URL to JSON file, e.g. https://cms-service-dqm.web.cern.ch/../..._JSON.txt
                      Default: ''
"""
from __future__ import print_function
import os
import logging

from .. import Command as C
from hepshell.interpreter import time_function
from ntp import NTPROOT
from ntp.commands.setup import CMSSW_SRC, TMPDIR, RESULTDIR, LOGDIR
from crab.util import find_input_files

LOG = logging.getLogger(__name__)
PSET = os.path.join(TMPDIR, 'pset.py')
OUTPUT_FILE = os.path.join(RESULTDIR, '{ds}_ntuple.root')
BTAG_CALIB_FILE = os.path.join(NTPROOT, 'data/BTagSF/CSVv2.csv')

from ntp.commands.run.ntuple.template import PYCONF


class Command(C):

    DEFAULTS = {
        'campaign': 'Test',
        'dataset': 'TTJets_PowhegPythia8',
        'nevents': 1000,
        'files': '',
        'noop': False,
        'output_file': OUTPUT_FILE.format(ds='TTJets_PowhegPythia8'),
        'pset_template': PYCONF,
        'json_url': '',
    }

    def __init__(self, path=__file__, doc=__doc__):
        super(Command, self).__init__(path, doc)

    @time_function('run local', LOG)
    def run(self, args, variables):
        output_file = None
        if 'output_file' in variables:
            output_file = os.path.join(RESULTDIR, variables['output_file'])
            if not output_file.endswith('.root'):
                output_file += '.root'
        else:
            output_file = OUTPUT_FILE.format(ds=variables['dataset'])
        variables['output_file'] = output_file

        self.__prepare(args, variables)
        campaign = self.__variables['campaign']
        chosen_dataset = self.__variables['dataset']
        input_files = find_input_files(
            campaign, chosen_dataset, self.__variables, logger=LOG
        )
        LOG.debug(
            "Using files for NTP input:\n{0}".format('\n'.join(input_files)))

        self.__output_file = self.__variables['output_file']

        self.__write_pset(input_files)

        # making sure the correct HLT menu is read
        if 'reHLT' in input_files[0]:
            self.__variables['isReHLT'] = 1

        if not self.__variables['noop']:
            code = self.__run_cmssw()
            self.__text = "Ran {PSET}\n"
            self.__text += "Logging information can be found in {LOGDIR}/ntp.log\n"
            if code == 0:
                self.__text += "Created ntuples: {OUTPUT_FILE}\n"
                self.__text = self.__text.format(
                    PSET=PSET, LOGDIR=LOGDIR, OUTPUT_FILE=self.__output_file)
            else:
                self.__text += "CMSSW experienced an error,"
                self.__text += " return code: {code}\n"
                self.__text = self.__text.format(
                    PSET=PSET, LOGDIR=LOGDIR, code=code)
                return False

        else:
            LOG.info('Found "noop", not running CMSSW')

        return True

    def __write_pset(self, input_files):
        nevents = int(self.__variables['nevents'])
        input_files = self.__format_input_files(input_files)

        with open(PSET, 'w+') as f:
            content = self.__variables['pset_template'].format(
                nevents=nevents,
                input_files=input_files,
                OUTPUT_FILE=self.__output_file,
                BTAG_CALIB_FILE=BTAG_CALIB_FILE,
                JSON_URL=self.__variables['json_url'],
            )
            f.write(content)

    @time_function('__run_cmssw', LOG)
    def __run_cmssw(self):
        commands = [
            'cd {CMSSW_SRC}',
            'source /cvmfs/cms.cern.ch/cmsset_default.sh',
            'eval `/cvmfs/cms.cern.ch/common/scram runtime -sh`',
            'cmsRun {PSET} {params}',
        ]

        all_in_one = ' && '.join(commands)
        all_in_one = all_in_one.format(
            CMSSW_SRC=CMSSW_SRC, PSET=PSET, params=self.__extract_params())

        LOG.info("Executing cmsRun")
        from hepshell.interpreter import call
        code, _, _ = call(
            [all_in_one], LOG, stdout_log_level=logging.INFO, shell=True)

        return code
