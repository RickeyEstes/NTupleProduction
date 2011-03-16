#ifndef RootTupleMakerV2Event
#define RootTupleMakerV2Event

#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"

class RootTupleMakerV2_Event_Extra : public edm::EDProducer {
 public:
  explicit RootTupleMakerV2_Event_Extra(const edm::ParameterSet&);

 private:
  void produce( edm::Event &, const edm::EventSetup & );
  const edm::InputTag   dcsInputTag;
};

#endif
