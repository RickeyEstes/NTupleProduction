#ifndef RootTupleMakerV2Tree
#define RootTupleMakerV2Tree

/** \class RootTupleMakerV2_Tree
 *
 *  Makes a tree out of C++ standard types and vectors of C++ standard types
 *
 *  This class, which is an EDAnalyzer, takes the same "keep" and
 *  "drop" outputCommands parameter as the PoolOutputSource, making a
 *  tree of the selected variables, which it obtains from the EDM
 *  tree.
 *
 *  $Date: 2012/08/08 21:54:24 $
 *  $Revision: 1.5 $
 *  \author Burt Betchart - University of Rochester <burton.andrew.betchart@cern.ch>
 */

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include <string>
#include <vector>
#include <TTree.h>
#include <TH1I.h>

class RootTupleMakerV2_Tree: public edm::EDAnalyzer {
private:
	virtual void beginJob();
	virtual void analyze(const edm::Event&, const edm::EventSetup&);
	virtual void endJob() {
	}

	class BranchConnector {
	public:
		virtual ~BranchConnector() {
		}
		;
		virtual void connect(const edm::Event&) = 0;
	};

	template<class T>
	class TypedBranchConnector: public BranchConnector {
	private:
		std::string moduleLabel_; //module label
		std::string productInstanceName_; //product instance name
		T object_;
		T* object_ptr_;
	public:
		TypedBranchConnector(edm::BranchDescription const*, std::string, TTree*);
		void connect(const edm::Event&);
	};

	edm::Service<TFileService> fs_;
	TTree * tree_;
	const std::string treeName_;

	std::vector<BranchConnector*> connectors_;
	edm::ParameterSet pset_;

	template<class T>
	void registerBranch(edm::BranchDescription const* branchDesc, const std::string& type);

	void registerBranches();

public:
	RootTupleMakerV2_Tree(const edm::ParameterSet& iConfig);

	enum LEAFTYPE {
		BOOL = 1,
		BOOL_V,
		SHORT,
		SHORT_V,
		U_SHORT,
		U_SHORT_V,
		INT,
		INT_V,
		U_INT,
		U_INT_V,
		FLOAT,
		FLOAT_V,
		DOUBLE,
		DOUBLE_V,
		LONG,
		LONG_V,
		U_LONG,
		U_LONG_V,
		STRING,
		STRING_V,
		STRING_BOOL_M,
		STRING_INT_M,
		STRING_STRING_M,
		STRING_FLOAT_V_M,
		FLOAT_V_V,
		INT_V_V,
		BOOL_V_V,
		STRING_V_V
	};
};

#include "BristolAnalysis/NTupleTools/interface/RootTupleMakerV2_Tree.hxx"

#endif
