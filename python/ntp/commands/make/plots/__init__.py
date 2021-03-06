"""
    make plots:
        Runs DailyPythonScripts/dps/analysis/xsection/04_make_plots_matplotlib.py
        
    Usage:
        make plots [--visiblePS]\
                           [--show_generator_ratio]\
                           [--variable=<>]\
                           [--centre_of_mass_energy=<>]

    Flags:
        show_generator_ratio:
            Show the ratio of generators to central

        visiblePS:
            Unfold to visible phase space (instead of full phase space)

    Parameters:
        variable:
            set the variable to analyse ({variables}). Default is MET.

        centre_of_mass_energy: 
            set the centre of mass energy for analysis. Default = 13 [TeV]

"""
import logging
import os
from copy import deepcopy
import importlib

from hepshell.interpreter import time_function

from ntp.commands.run import Command as C
from ntp.commands.setup import DPS_RESULTDIR

DPS_PLOTDIR = os.path.join(DPS_RESULTDIR, 'plots')

LOG = logging.getLogger(__name__)

JSON_PATH = os.path.join(
    DPS_RESULTDIR, 'normalisation', 'background_subtraction')


class Command(C):
    REQUIRE_GRID_CERT = False
    DEFAULTS = {
        'json_path': JSON_PATH,
        'variable': 'MET',
        'centre_of_mass_energy': 13,
        'visiblePS': False,
        'show_generator_ratio': False,
    }

    def __init__(self, path=__file__, doc=__doc__):
        super(Command, self).__init__(path, doc)
        self.__measurement_config = None
        self.__unfolding_files = {}

    @time_function('unfold and measure', LOG)
    def run(self, args, variables):
        from ntp import NTPROOT
        self.__prepare(args, variables)

        conda_path = os.path.join(NTPROOT, 'external', 'miniconda')
        dps_script_path = os.path.join(
            conda_path, 'envs', 'ntp', 'lib',
            'python2.7', 'site-packages', 'dps', 'analysis', 'xsection',
            '04_make_plots_matplotlib.py'
        )
        python = os.path.join(conda_path, 'envs', 'ntp', 'bin', 'python')
        params = ' '.join([
            '-v {0}'.format(self.__variables['variable']),
            '--visiblePS',
            '-c {0}'.format(self.__variables['centre_of_mass_energy']),
            '-p {0}'.format(self.__variables['json_path']),
            '-o {0}'.format(DPS_PLOTDIR),
        ])
        if self.__variables['show_generator_ratio']:  # temporary solution
            params += ' --show-generator-ratio'

        command = '{python} {script} {params}'.format(
            python=python, script=dps_script_path, params=params,
        )
        conda_activate = os.path.join(conda_path, 'bin', 'activate')
        conda_env = 'source {0} ntp'.format(conda_activate)
        command = '{0} && {1}'.format(conda_env, command)
        from hepshell.interpreter import call
        call(command, logger=LOG, shell=True)

        return True
