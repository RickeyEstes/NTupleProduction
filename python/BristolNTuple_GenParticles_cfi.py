import FWCore.ParameterSet.Config as cms

rootTupleGenParticles = cms.EDProducer("BristolNTuple_GenParticles",
    InputTag = cms.InputTag('genParticles'),
    Prefix = cms.string('GenParticle.'),
    Suffix = cms.string(''),
    MaxSize = cms.uint32(25)
)

