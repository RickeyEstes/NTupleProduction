#include "BristolAnalysis/NTupleTools/interface/BristolNTuple_PFJets.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "CondFormats/JetMETObjects/interface/FactorizedJetCorrector.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"
#include <iostream>

BristolNTuple_PFJets::BristolNTuple_PFJets(const edm::ParameterSet& iConfig) :
    inputTag(iConfig.getParameter<edm::InputTag> ("InputTag")),
    prefix(iConfig.getParameter<std::string> ("Prefix")),
    suffix(iConfig.getParameter<std::string> ("Suffix")),
    maxSize(iConfig.getParameter<unsigned int> ("MaxSize")) {

    produces<std::vector<double> > (prefix + "Eta" + suffix);
    produces<std::vector<double> > (prefix + "Phi" + suffix);
    produces<std::vector<double> > (prefix + "Pt" + suffix);
    produces<std::vector<double> > (prefix + "Px" + suffix);
    produces<std::vector<double> > (prefix + "Py" + suffix);
    produces<std::vector<double> > (prefix + "Pz" + suffix);
    produces<std::vector<double> > (prefix + "Charge" + suffix);
    produces<std::vector<double> > (prefix + "Mass" + suffix);

    produces<std::vector<double> > (prefix + "PtRaw" + suffix);
    produces<std::vector<double> > (prefix + "Energy" + suffix);
    produces<std::vector<double> > (prefix + "EnergyRaw" + suffix);
    produces<std::vector<int> > (prefix + "PartonFlavour" + suffix);

    produces<std::vector<double> > (prefix + "ChargedEmEnergyFraction" + suffix);
    produces<std::vector<double> > (prefix + "ChargedHadronEnergyFraction" + suffix);
    produces<std::vector<double> > (prefix + "ChargedMuEnergyFraction" + suffix);
    produces<std::vector<double> > (prefix + "ElectronEnergyFraction" + suffix);
    produces<std::vector<double> > (prefix + "MuonEnergyFraction" + suffix);
    produces<std::vector<double> > (prefix + "NeutralEmEnergyFraction" + suffix);
    produces<std::vector<double> > (prefix + "NeutralHadronEnergyFraction" + suffix);
    produces<std::vector<double> > (prefix + "PhotonEnergyFraction" + suffix);
    produces<std::vector<int> > (prefix + "ChargedHadronMultiplicity" + suffix);
    produces<std::vector<int> > (prefix + "ChargedMultiplicity" + suffix);
    produces<std::vector<int> > (prefix + "ElectronMultiplicity" + suffix);
    produces<std::vector<int> > (prefix + "MuonMultiplicity" + suffix);
    produces<std::vector<int> > (prefix + "NeutralHadronMultiplicity" + suffix);
    produces<std::vector<int> > (prefix + "NeutralMultiplicity" + suffix);
    produces<std::vector<int> > (prefix + "PhotonMultiplicity" + suffix);
    produces<std::vector<int> > (prefix + "NConstituents" + suffix);
    produces<std::vector<double> > (prefix + "ChargedEmEnergyFractionRAW" + suffix);
    produces<std::vector<double> > (prefix + "ChargedHadronEnergyFractionRAW" + suffix);
    produces<std::vector<double> > (prefix + "NeutralEmEnergyFractionRAW" + suffix);
    produces<std::vector<double> > (prefix + "NeutralHadronEnergyFractionRAW" + suffix);

    produces<std::vector<double> > (prefix + "TrackCountingHighEffBTag" + suffix);
    produces<std::vector<double> > (prefix + "TrackCountingHighPurBTag" + suffix);
    produces<std::vector<double> > (prefix + "SimpleSecondaryVertexHighEffBTag" + suffix);
    produces<std::vector<double> > (prefix + "SimpleSecondaryVertexHighPurBTag" + suffix);
    produces<std::vector<double> > (prefix + "JetProbabilityBTag" + suffix);
    produces<std::vector<double> > (prefix + "JetBProbabilityBTag" + suffix);
}

void BristolNTuple_PFJets::produce(edm::Event& iEvent, const edm::EventSetup& iSetup) {
    std::auto_ptr < std::vector<double> > eta(new std::vector<double>());
    std::auto_ptr < std::vector<double> > phi(new std::vector<double>());
    std::auto_ptr < std::vector<double> > pt(new std::vector<double>());
    std::auto_ptr < std::vector<double> > px(new std::vector<double>());
    std::auto_ptr < std::vector<double> > py(new std::vector<double>());
    std::auto_ptr < std::vector<double> > pz(new std::vector<double>());
    std::auto_ptr < std::vector<double> > charge(new std::vector<double>());
    std::auto_ptr < std::vector<double> > mass(new std::vector<double>());

    std::auto_ptr < std::vector<double> > pt_raw(new std::vector<double>());
    std::auto_ptr < std::vector<double> > energy(new std::vector<double>());
    std::auto_ptr < std::vector<double> > energy_raw(new std::vector<double>());
    std::auto_ptr < std::vector<int> > partonFlavour(new std::vector<int>());

    std::auto_ptr < std::vector<double> > chargedEmEnergyFraction(new std::vector<double>());
    std::auto_ptr < std::vector<double> > chargedHadronEnergyFraction(new std::vector<double>());
    std::auto_ptr < std::vector<double> > chargedMuEnergyFraction(new std::vector<double>());
    std::auto_ptr < std::vector<double> > electronEnergyFraction(new std::vector<double>());
    std::auto_ptr < std::vector<double> > muonEnergyFraction(new std::vector<double>());
    std::auto_ptr < std::vector<double> > neutralEmEnergyFraction(new std::vector<double>());
    std::auto_ptr < std::vector<double> > neutralHadronEnergyFraction(new std::vector<double>());
    std::auto_ptr < std::vector<double> > photonEnergyFraction(new std::vector<double>());
    std::auto_ptr < std::vector<int> > chargedHadronMultiplicity(new std::vector<int>());
    std::auto_ptr < std::vector<int> > chargedMultiplicity(new std::vector<int>());
    std::auto_ptr < std::vector<int> > electronMultiplicity(new std::vector<int>());
    std::auto_ptr < std::vector<int> > muonMultiplicity(new std::vector<int>());
    std::auto_ptr < std::vector<int> > neutralHadronMultiplicity(new std::vector<int>());
    std::auto_ptr < std::vector<int> > neutralMultiplicity(new std::vector<int>());
    std::auto_ptr < std::vector<int> > photonMultiplicity(new std::vector<int>());
    std::auto_ptr < std::vector<int> > nConstituents(new std::vector<int>());
    std::auto_ptr < std::vector<double> > chargedEmEnergyFractionRAW(new std::vector<double>());
    std::auto_ptr < std::vector<double> > chargedHadronEnergyFractionRAW(new std::vector<double>());
    std::auto_ptr < std::vector<double> > neutralEmEnergyFractionRAW(new std::vector<double>());
    std::auto_ptr < std::vector<double> > neutralHadronEnergyFractionRAW(new std::vector<double>());
    std::auto_ptr < std::vector<double> > trackCountingHighEffBTag(new std::vector<double>());
    std::auto_ptr < std::vector<double> > trackCountingHighPurBTag(new std::vector<double>());
    std::auto_ptr < std::vector<double> > simpleSecondaryVertexHighEffBTag(new std::vector<double>());
    std::auto_ptr < std::vector<double> > simpleSecondaryVertexHighPurBTag(new std::vector<double>());
    std::auto_ptr < std::vector<double> > jetProbabilityBTag(new std::vector<double>());
    std::auto_ptr < std::vector<double> > jetBProbabilityBTag(new std::vector<double>());

    edm::Handle < std::vector<pat::Jet> > jets;
    iEvent.getByLabel(inputTag, jets);

    if (jets.isValid()) {
        edm::LogInfo("BristolNTuple_PFJetsInfo") << "Total # PFJets: " << jets->size();

        for (std::vector<pat::Jet>::const_iterator it = jets->begin(); it != jets->end(); ++it) {
            // exit from loop when you reach the required number of jets
            if (px->size() >= maxSize)
                break;

            // fill in all the vectors
            eta->push_back(it->eta());
            phi->push_back(it->phi());
            pt->push_back(it->pt());
            px->push_back(it->px());
            py->push_back(it->py());
            pz->push_back(it->pz());
            charge->push_back(it->jetCharge());
            mass->push_back(it->mass());

            pt_raw->push_back(it->correctedJet("Uncorrected").pt());
            energy->push_back(it->energy());
            energy_raw->push_back(it->correctedJet("Uncorrected").energy());
            partonFlavour->push_back(it->partonFlavour());

            chargedEmEnergyFraction->push_back(it->chargedEmEnergyFraction());
            chargedHadronEnergyFraction->push_back(it->chargedHadronEnergyFraction());
            chargedMuEnergyFraction->push_back(it->chargedMuEnergyFraction());
            electronEnergyFraction->push_back(it->electronEnergy() / it->energy());
            muonEnergyFraction->push_back(it->muonEnergyFraction());
            neutralEmEnergyFraction->push_back(it->neutralEmEnergyFraction());
            neutralHadronEnergyFraction->push_back(it->neutralHadronEnergyFraction());
            photonEnergyFraction->push_back(it->photonEnergyFraction());
            chargedHadronMultiplicity->push_back(it->chargedHadronMultiplicity());
            chargedMultiplicity->push_back(it->chargedMultiplicity());
            electronMultiplicity->push_back(it->electronMultiplicity());
            muonMultiplicity->push_back(it->muonMultiplicity());
            neutralHadronMultiplicity->push_back(it->neutralHadronMultiplicity());
            neutralMultiplicity->push_back(it->neutralMultiplicity());
            photonMultiplicity->push_back(it->photonMultiplicity());
            nConstituents->push_back(it->numberOfDaughters());
            chargedEmEnergyFractionRAW->push_back(it->correctedJet("Uncorrected").chargedEmEnergyFraction());
            chargedHadronEnergyFractionRAW->push_back(it->correctedJet("Uncorrected").chargedHadronEnergyFraction());
            neutralEmEnergyFractionRAW->push_back(it->correctedJet("Uncorrected").neutralEmEnergyFraction());
            neutralHadronEnergyFractionRAW->push_back(it->correctedJet("Uncorrected").neutralHadronEnergyFraction());

            trackCountingHighEffBTag->push_back(it->bDiscriminator("trackCountingHighEffBJetTags"));
            trackCountingHighPurBTag->push_back(it->bDiscriminator("trackCountingHighPurBJetTags"));
            simpleSecondaryVertexHighEffBTag->push_back(it->bDiscriminator("simpleSecondaryVertexHighEffBJetTags"));
            simpleSecondaryVertexHighPurBTag->push_back(it->bDiscriminator("simpleSecondaryVertexHighPurBJetTags"));
            jetProbabilityBTag->push_back(it->bDiscriminator("jetProbabilityBJetTags"));
            jetBProbabilityBTag->push_back(it->bDiscriminator("jetBProbabilityBJetTags"));

        }
    } else {
        edm::LogError("BristolNTuple_PFJetsError") << "Error! Can't get the product " << inputTag;
    }

    //-----------------------------------------------------------------
    // put vectors in the event
    iEvent.put(eta, prefix + "Eta" + suffix);
    iEvent.put(phi, prefix + "Phi" + suffix);
    iEvent.put(pt, prefix + "Pt" + suffix);
    iEvent.put(px, prefix + "Px" + suffix);
    iEvent.put(py, prefix + "Py" + suffix);
    iEvent.put(pz, prefix + "Pz" + suffix);
    iEvent.put(charge, prefix + "Charge" + suffix);
    iEvent.put(mass, prefix + "Mass" + suffix);

    iEvent.put(pt_raw, prefix + "PtRaw" + suffix);
    iEvent.put(energy, prefix + "Energy" + suffix);
    iEvent.put(energy_raw, prefix + "EnergyRaw" + suffix);
    iEvent.put(partonFlavour, prefix + "PartonFlavour" + suffix);

    iEvent.put(chargedEmEnergyFraction, prefix + "ChargedEmEnergyFraction" + suffix);
    iEvent.put(chargedHadronEnergyFraction, prefix + "ChargedHadronEnergyFraction" + suffix);
    iEvent.put(chargedMuEnergyFraction, prefix + "ChargedMuEnergyFraction" + suffix);
    iEvent.put(electronEnergyFraction, prefix + "ElectronEnergyFraction" + suffix);
    iEvent.put(muonEnergyFraction, prefix + "MuonEnergyFraction" + suffix);
    iEvent.put(neutralEmEnergyFraction, prefix + "NeutralEmEnergyFraction" + suffix);
    iEvent.put(neutralHadronEnergyFraction, prefix + "NeutralHadronEnergyFraction" + suffix);
    iEvent.put(photonEnergyFraction, prefix + "PhotonEnergyFraction" + suffix);
    iEvent.put(chargedHadronMultiplicity, prefix + "ChargedHadronMultiplicity" + suffix);
    iEvent.put(chargedMultiplicity, prefix + "ChargedMultiplicity" + suffix);
    iEvent.put(electronMultiplicity, prefix + "ElectronMultiplicity" + suffix);
    iEvent.put(muonMultiplicity, prefix + "MuonMultiplicity" + suffix);
    iEvent.put(neutralHadronMultiplicity, prefix + "NeutralHadronMultiplicity" + suffix);
    iEvent.put(neutralMultiplicity, prefix + "NeutralMultiplicity" + suffix);
    iEvent.put(photonMultiplicity, prefix + "PhotonMultiplicity" + suffix);
    iEvent.put(nConstituents, prefix + "NConstituents" + suffix);
    iEvent.put(chargedEmEnergyFractionRAW, prefix + "ChargedEmEnergyFractionRAW" + suffix);
    iEvent.put(chargedHadronEnergyFractionRAW, prefix + "ChargedHadronEnergyFractionRAW" + suffix);
    iEvent.put(neutralEmEnergyFractionRAW, prefix + "NeutralEmEnergyFractionRAW" + suffix);
    iEvent.put(neutralHadronEnergyFractionRAW, prefix + "NeutralHadronEnergyFractionRAW" + suffix);
    iEvent.put(trackCountingHighEffBTag, prefix + "TrackCountingHighEffBTag" + suffix);
    iEvent.put(trackCountingHighPurBTag, prefix + "TrackCountingHighPurBTag" + suffix);
    iEvent.put(simpleSecondaryVertexHighEffBTag, prefix + "SimpleSecondaryVertexHighEffBTag" + suffix);
    iEvent.put(simpleSecondaryVertexHighPurBTag, prefix + "SimpleSecondaryVertexHighPurBTag" + suffix);
    iEvent.put(jetProbabilityBTag, prefix + "JetProbabilityBTag" + suffix);
    iEvent.put(jetBProbabilityBTag, prefix + "JetBProbabilityBTag" + suffix);

}
