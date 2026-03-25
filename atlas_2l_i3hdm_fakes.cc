#include "atlas_2l_i3hdm_fakes.h"
// AUTHOR: Rakhi
//  EMAIL: rakhi@cern
void Atlas_2l_i3hdm_fakes::initialize() {
  setAnalysisName("atlas_2l_i3hdm_fakes");          
  setInformation(""
    "# blah\n"
  "");
  setLuminosity(300.0*units::INVFB);      
  bookSignalRegions("SR-00-all;SR-01-2pmuons;SR-03-bveto;SR-04-met;SR-05-jetpt;SR-06-dphij1met;SR-07-dphijmet;SR-08-leptoncuts;SR-09-Njle2;SR-10-Njlt2;SR-11-TLSS;SR-11-TTSS;SR-11-TTOS;SR-11-TLOS;SR1-TTSS;SR1-TLSS;SR1-TTOS;SR1-TLOS");

  int ifile = bookFile("atlas_i3hdm_fakes.root", true);
  const char *rootFileName = fNames[ifile].c_str() ;
  hfile = new TFile(rootFileName, "RECREATE", "Saving Histograms");

  histo_minv = new TH1F("minv", "Lepton Invariant mass", 10, 0, 70);
  histo_met = new TH1F("met", "MET", 50, 0, 500);
  histo_mtau = new TH1F("mtau", "mtau", 40, 0, 400);                                                                                                                                                         

  histo_ptlep1 = new TH1F("ptlep1", "ptlep1", 100, 0, 200);
  histo_ptlep2 = new TH1F("ptlep2", "ptlep2", 50, 0, 100);               
  histo_dy= new TH1F("dy", "|delta y|", 50, 0, 3);
  histo_dphi= new TH1F("dphi", "dphi", 9, 0, 3);
  histo_dphi_jet1_met= new TH1F("dphi_jet1_met", "dphi_jet1_met", 9, 0, 3);
  histo_dphi_l1l2_met= new TH1F("dphi_l1l2_met", "dphi_l1l2_met", 9, 0, 3);      
  histo_drll= new TH1F("drll", "drll", 30, 0, 3);
  histo_dr_jet1_met= new TH1F("dr_jet1_met", "dr_jet1_met", 30, 0, 3);
  
  histo_mtl1l2 = new TH1F("mtl1l2", "mtl1l2", 80, 0, 300);  
  histo_mt2 = new TH1F("mt2", "mt2", 100, 0, 100);
  histo_mt2_bkg = new TH1F("mt2bkg", "mt2bkg", 100, 0, 100);
  histo_mt2_top4 = new TH1F("mt2top4", "mt2top4", 100, 0, 200);
  //  histo_mt2_top5 = new TH1F("mt2top5", "mt2top5", 100, 0, 200);
  //  histo_mt2_top6 = new TH1F("mt2top6", "mt2top6", 100, 0, 200);
  //  histo_mt2_top3 = new TH1F("mt2top3", "mt2top3", 100, 0, 200);
  //  histo_mt2_top7 = new TH1F("mt2top7", "mt2top7", 100, 0, 200);
  histo_ptlep = new TH1F("ptlep", "ptlep", 50, 0, 150);
  histo_htlep = new TH1F("htlep", "htlep", 50, 0, 200);
  histo_htj = new TH1F("htj", "htj", 50, 0, 500);    
  histo_met_sig_lep  = new TH1F("MET_SIG_LEP", "MET_SIG_LEP", 50, 0, 5);
  histo_met_sig_jet  = new TH1F("MET_SIG_jet", "MET_SIG_jet", 50, 0, 5);


  histo_njet = new TH1F("Njet", "Njet", 8, -0.5, 7.5);    
  //  histo_nlpbj = new TH1F("Nlbjet", "Nlbjet", 8, -0.5, 7.5);
  histo_ptj1 = new TH1F("ptj1", "ptj1", 60, 0, 600);

  // You can also book cutflow regions with bookCutflowRegions("CR1;CR2;..."). Note that the regions are
  //  always ordered alphabetically in the cutflow output files.


  // You should initialize any declared variables here
  // You should initialize any declared variables here
}

void Atlas_2l_i3hdm_fakes::analyze() {
  // Your eventwise analysis code goes here
  // The following objects are always defined unless they are 'ignored' above. They form std::vector objects of the respective Delphes class type (except for Etmiss which is a single object)
  // All std::vector members and etmiss have the common properties PT, Eta, Phi and P4() with the latter giving access to the full ROOT TLorentzVector.
  // Within a std::vector, all members are ordered with highest pt coming first.

  // electronsLoose, electronsMedium, electronsTight   are list of electrons that passed respective efficiency and reconstruction cuts
  // muonsCombinedPlus, muonsCombined                  as above for muons
  // photonsMedium                                     as above for photons
  // jets are all reconstructed jets                   as above for jets. Note that electrons are most certainly also reconstructed as a jet -> overlap removal do avoid double counting necessary!
  // tracks, towers                                    calorimeter and tracker information. Usually not needed.
  // missingET                                         rec missing ET EXCLUDING muons.

  
  // Here is a couple of useful functions and lines:  
  //------------Phase Space Cuts (defined for jets, electronsXYZ, muonsXYZ, photonsXYZ)
  // jets = filterPhaseSpace(jets, 20., -2.8, 2.8)  // The vector 'jets' only contains jets with pt >= 20 GeV and -2.8 < eta < 2.8. This function is applicable to other particles too (electronsMedium, ... ).
  // jets = overlapRemoval(jets, electronsLoose, 0.2) Removes all jets for which there exists any electron in 'electronsLoose' with deltaR < 0.2.
  // jets = overlapRemovel(jets, 0.2) If two jets overlap within deltaR < 0.2, only the harder jet is stored.
  
  //------------Isolation Checks (defined for electronsXYZ, muonsXYZ, photonsXYZ
  //------------        For each object, if the user entered N isolation conditions, they can be
  //------------        checked individually be the second argument (running from 0 to N-1).
  // electronsMedium = filterIsolation(electronsMedium, 0)            Removes electrons that do not pass the first isolation condition entered into the AnalysisManager by the user
  // std::vector<int> flags; flags.push_back(0); flags.push_back(2);
  // electronsMedium = filterIsolation(electronsMedium, flags)        Same as above, but both the first and the third condition have to be fulfilled
  // electronsMedium = filterIsolation(electronsMedium)               Same as above, but all conditions have to be fulfilled.
  
  //-----------Flavour Tag Checks (defined for jets only)
  //----------          Tau tags "loose", "medium" or "tight" can be individually checked if the user enabled tau tagging in the AM.
  //----------          For b-tags, if N working points have been defined, the ith condition can be tested by putting i-1 into the second argument (if there is only one, the argument can be omitted)
  // if checkTauTag(jets[0], "tight") leadingJetIsTagged = True;
  // if checkBTag(jets[0], 0) leadingJetIsBTagged = True;


  //-----------Auxiliary Information
  // - Always ensure that you don't access vectors out of bounds. E.g. 'if(jets[1]->PT > 150)' should rather be if (jets.size() > 1 && jets[1]->PT > 150). 
  // - Use rand()/(RAND_MAX+1.) for random numbers between 0 and 1. The random seed is determined from system time or by the RandomSeed parameter in CheckMATE.
  // - The 'return' statement will end this function for the current event and hence should be called whenever the current event is to be vetoed.
  // - Many advanced kinematical functions like mT2 are implemented. Check the manual for more information.
  // - If you need output to be stored in other files than the cutflow/signal files we provide, check the manual for how to do this conveniently.  
  //  double w = weight;

  missingET->addMuons(muonsCombined);  // Adds muons to missing ET. This should almost always be done which is why this line is not commented out.
  
  electronsLoose = filterPhaseSpace(electronsLoose, 4.5, -2.47, 2.47);
  electronsTight = filterPhaseSpace(electronsTight, 4.5, -2.47, 2.47);
  muonsCombined = filterPhaseSpace(muonsCombined, 4.0, -2.5, 2.5);
  jets = filterPhaseSpace(jets, 20., -4.5, 4.5);
  photonsLoose = filterPhaseSpace(photonsLoose, 25., -2.37, 2.37, true);
  std::vector<Jet*> bjets;
  std::vector<Jet*> lightjets;

  for (int i = 0; i < jets.size(); i++)
    if ( fabs(jets[i]->Eta) < 2.5 && checkBTag(jets[i]) ) bjets.push_back(jets[i]);
    else lightjets.push_back(jets[i]);

  lightjets = overlapRemoval(lightjets, electronsLoose, 0.2, "y");
  bjets = overlapRemoval_muon_jet_tracks(bjets, muonsCombined, 0.4, 2);
  lightjets = overlapRemoval_muon_jet_tracks(lightjets, muonsCombined, 0.4, 2);
  electronsLoose = overlapRemoval(electronsLoose, bjets, 0.4, "y");
  electronsLoose = overlapRemoval(electronsLoose, lightjets, 0.4, "y");
  electronsMedium = overlapRemoval(electronsMedium, bjets, 0.4, "y");
  electronsMedium = overlapRemoval(electronsMedium, lightjets, 0.4, "y");
  electronsTight = overlapRemoval(electronsTight, bjets, 0.4, "y");
  electronsTight = overlapRemoval(electronsTight, lightjets, 0.4, "y");

  std::vector<Electron*> electrons_base = electronsLoose;
  std::vector<Muon*> muons_base = muonsCombined;

  std::vector<Electron*> electrons_signal = Isolate_leptons_with_inverse_track_isolation_cone(electronsLoose, tracks, towers, 0.3, 10., 0.2, 0.15, 0.2, true);
  
  // Now check muon isolation cuts
  std::vector<Muon*> muons_iso = overlapRemoval(muons_base, bjets, 0.4, "y");
  muons_iso = overlapRemoval(muons_iso, lightjets, 0.4, "y");
  
  std::vector<Muon*> muons_signal = Isolate_leptons_with_inverse_track_isolation_cone(muons_iso,  tracks, towers, 0.3, 10., 0.2, 0.06, 0.06, false);
  std::vector<Muon*> muons_not_tight =  overlapRemoval(muons_base, muons_signal, 0.1, "y");

  countCutflowEvent("00_all");
  countSignalEvent("SR-00-all");

//---------------------- BASIC CUTS ------------------------------------

  bool TLflag = false;
  bool TTflag = false;
  bool SSflag = false;
  bool OSflag = false;

  //  if (( muons_signal.size() + muons_not_tight.size() < 2 ) || ( electrons_signal.size() > 0 )) return;    //For muon only
  //  if ( muons_signal.size() != 2 ) return;
 if (( muons_base.size() < 2 ) || ( electrons_signal.size() > 0 )) return;
 countCutflowEvent("01_2pmuons");   
  countSignalEvent("SR-01-2pmuons");
  //  cout << "N_mu= " << muons_base.size();
 

//  << "loose muon " << (muons_loose[0]->P4()).E() << " " << (muons_loose[0]->P4()).Px() << " " << (muons_loose[0]->P4()).Px() << " " << (muons_loose[0]->P4()).Pz() << endl; 
  
  if (bjets.size() != 0 ) return;
  countCutflowEvent("03_bveto");
  countSignalEvent("SR-03-bveto");
 
// // -------------- HISTOGRAM FILLING ------------------------------------------

  TLorentzVector zerovec = TLorentzVector(0.,0.,0.,0.);
  const auto metP4 = missingET->P4();
  double met = missingET->P4().Et();
  double Njet = lightjets.size();
  double Nbjet = bjets.size();
  double Nphoton = photonsLoose.size();
  TLorentzVector sumj = TLorentzVector(0,0,0,0);
  double mt2top_val = 0.0;
  double min_mt2top = std::numeric_limits<double>::max();
  double min_mt2topbj = std::numeric_limits<double>::max();
  double min_mt2topjj = std::numeric_limits<double>::max();
  double ptj1 = 0.;
  double ptb = 0.;
  double ptbj = 0.;    
  double pt_photon1 = 0.;
  double htj = 0.;
  double ptj = 0;
  double ptlj=0;
  double dphi_jet1_met = 0.;
  double dr_jet1_met = 0.;
  double met_sig_lep = 0.;
  double met_sig_jet = 0.;  

  
  if (Njet!=0) ptj1 = lightjets[0]->PT;

  //if (bjets.size()!=0) ptb = bjets[0]->PT;
  //ptbj = ptb + ptj1;
  
  if (Njet!=0){
  for (int i = 0; i < lightjets.size(); i++)
    htj += lightjets[i]->PT;
  

  for (int i = 0; i < lightjets.size(); i++)
    sumj += lightjets[i]->P4();

  ptj = sumj.Perp();

  dphi_jet1_met=fabs(lightjets[0]->P4().DeltaPhi(metP4));
  dr_jet1_met = fabs(lightjets[0]->P4().DeltaR(metP4));
  met_sig_jet = met/htj;  
  }


//   histo_ptlj_met->Fill(ptlj,met);
//   histo_ptj_met->Fill(ptj,met);
//   histo_ptj1_met->Fill(ptj1,met);
//   histo_htlep_met->Fill(htlep,met);
//   histo_htj_met->Fill(htj,met);  
//   histo_mll_met->Fill(mll,met);
//   histo_htj_mll->Fill(htj,mll);
//   histo_htlep_mll->Fill(htlep,mll);
//   histo_drll_met->Fill(drll,met);
//   histo_dphi_met->Fill(dphi,met);
//   histo_dphi_j1_met->Fill(dphi_jet1_met,met);              
  
//-------------------------------------------------------------
  histo_njet->Fill(Njet);
  histo_met->Fill(met);
   
  
  if (Njet!=0) histo_ptj1->Fill(ptj1);
  if (Njet!=0) histo_dr_jet1_met->Fill(dr_jet1_met);
  if (Njet!=0) histo_met_sig_jet->Fill(met_sig_jet);
  if (Njet!=0) histo_dphi_jet1_met->Fill(dphi_jet1_met);

  // if (Nbjet>=2) {
  //   for (unsigned int i=0; i< Nbjet; i++) {
  //     const auto jet_i_p4 = bjets[i]->P4();
  //     for (unsigned int j=i+1; j< Nbjet; j++) {
  // 	const auto jet_j_p4 = bjets[j]->P4();
  // 	double val1 = mT2(leptons[0] + jet_i_p4, leptons[1] + jet_j_p4, 0., metP4);
  // 	double val2 = mT2(leptons[0] + jet_j_p4, leptons[1] + jet_i_p4, 0., metP4);
  // 	double local_min = (val1 < val2) ? val1: val2;
  // 	if (local_min < min_mt2top) {
  // 	  min_mt2top = local_min;
  // 	}
  //     }
  //   }
  // histo_mt2_top4->Fill(min_mt2top);
  // }

  // if (Nbjet==1 && Njet>=1) {
  //   for (unsigned int i=0; i< Njet; i++) {
  //     const auto jet_i_p4 = lightjets[i]->P4();
  //     const auto jet_j_p4 = bjets[0]->P4();
  //     double val1 = mT2(leptons[0] + jet_i_p4, leptons[1] + jet_j_p4, 0., metP4);
  //     double val2 = mT2(leptons[0] + jet_j_p4, leptons[1] + jet_i_p4, 0., metP4);
  //     double local_min = (val1 < val2) ? val1: val2;
  //     if (local_min < min_mt2topbj) {
  // 	min_mt2topbj = local_min;
  //     }
  //   }
  // histo_mt2_top4->Fill(min_mt2topbj);
  // }

  // if (Nbjet==0 && Njet>=2) {
  //   //    cout << "in mT2 loop" << endl;
  //   for (unsigned int i=0; i< Njet; i++) {
  //     const auto jet_i_p4 = lightjets[i]->P4();
  //     for (unsigned int j=i+1; j< Njet; j++) {
  // 	const auto jet_j_p4 = lightjets[j]->P4();
  // 	double val1 = mT2(leptons[0] + jet_i_p4, leptons[1] + jet_j_p4, 0., metP4);
  // 	double val2 = mT2(leptons[0] + jet_j_p4, leptons[1] + jet_i_p4, 0., metP4);
  // 	double local_min = (val1 < val2) ? val1: val2;
  // 	if (local_min < min_mt2topjj) {
  // 	  min_mt2topjj = local_min;
  // 	}
  //     }
  //   }
  //   //    cout << "min_mt2topjj" << endl;;
  //   histo_mt2_top4->Fill(min_mt2topjj);
  // }

  // //topness  assumes semileptonic tops, essentially kinematic constraints on reconstructing tops and Ws
  // double top_ness=0.;
  // if(BTagSignalJets.size()>1) {
  //   top_ness = topness(signalLeps[0]->P4(), BTagSignalJets[0]->P4(), BTagSignalJets[1]->P4(), missingET->P4());
  // }
  // if(BTagSignalJets.size()==1 and notBTagSignalJets.size()>0) {
  //   top_ness = topness(signalLeps[0]->P4(), BTagSignalJets[0]->P4(), notBTagSignalJets[0]->P4(), missingET->P4());
  //   if(notBTagSignalJets.size()>1) {
  //     double tmptop_ness = topness(signalLeps[0]->P4(), BTagSignalJets[0]->P4(), notBTagSignalJets[1]->P4(), missingET->P4());
  //     if (tmptop_ness<top_ness) top_ness = tmptop_ness;
  //   }
  // }
  
  if ( met < 110.) return;
  countCutflowEvent("04_met>110");
  //  histo_mt2_top5->Fill(min_mt2topjj);

  countSignalEvent("SR-04-met");

  if(!lightjets.size() or ptj1 < 120.) return;
  countCutflowEvent("05_ptj1>120");
  //  histo_mt2_top7->Fill(min_mt2topjj);
  countSignalEvent("SR-05-jetpt");
  
  //  if ( dphi_jet1_met < 1.5) return;
  //  countCutflowEvent("08_dphi_jet1_met>1.5");

  if ( dphi_jet1_met < 2.0) return;
  countCutflowEvent("06_dphi_jet1_met>2.0");
  countSignalEvent("SR-06-dphij1met");
  
  for (int i = 0; i < lightjets.size(); i++)
    if ( fabs(lightjets[i]->P4().DeltaPhi(metP4)) < 0.4 ) return;
  countCutflowEvent("07_dphi_jet_met>0.4");
  countSignalEvent("SR-07-dphijmet");
  
  
  // =========================================================================
  // NEW: Form muon pairs and apply lepton-pair cuts
  // =========================================================================

  // 1. Define a struct to hold the pair and its descriptive tags
  struct ValidMuonPair {
    Muon* mu1;
    Muon* mu2;
    bool isTT;
    bool isTL;
    bool isLL;
    bool isOS;
    bool isSS;
    std::string tag;
  };

  // Container to store the pairs that pass your cuts
  std::vector<ValidMuonPair> valid_muon_pairs;  // Container to store the pairs that pass your cuts
  //  std::vector<std::pair<Muon*, Muon*>> valid_muon_pairs;
  
  // Loop over all possible unique pairs of muons
  for (unsigned int i = 0; i < muons_base.size(); ++i) {
    for (unsigned int j = i + 1; j < muons_base.size(); ++j) {
        
      // Get the TLorentzVectors for the two muons in the current pair
      TLorentzVector mu1_p4 = muons_base[i]->P4();
      TLorentzVector mu2_p4 = muons_base[j]->P4();
      TLorentzVector sum = TLorentzVector(0,0,0,0);
      sum = mu1_p4 + mu2_p4;
      
      double ptlep = sum.Perp();
      double dphi=fabs(mu1_p4.DeltaPhi(mu2_p4));
      double dphi_l1_met=fabs(mu1_p4.DeltaPhi(metP4));
      double dphi_l1l2_met=fabs(sum.DeltaPhi(metP4));	      
      double dy = fabs( (mu1_p4).Rapidity() - (mu2_p4).Rapidity() );
      double drll = fabs(mu1_p4.DeltaR(mu2_p4));
      double htlep = mu1_p4.Perp() + mu2_p4.Perp();
      double mtl1l2 = AnalysisBase::mT(sum, metP4);
      double mtau = mtautau(mu1_p4, mu2_p4, metP4);
      double mt2_val = mT2( sum, zerovec, 0., metP4);
      double mt2bkg_val = mT2( mu1_p4, mu2_p4, 0., metP4);
      met_sig_lep = met/htlep;

      if ( drll < 1.5 ) continue;
      if ( mtau >= 0. and mtau < 160. ) continue;
      if ( mt2bkg_val <= 20. ) continue;      
        
      if (Nbjet==0 && Njet>=2) {
	for (unsigned int i=0; i< Njet; i++) {
	  const auto jet_i_p4 = lightjets[i]->P4();
	  for (unsigned int j=i+1; j< Njet; j++) {
	    const auto jet_j_p4 = lightjets[j]->P4();
	    double val1 = mT2(mu1_p4 + jet_i_p4, mu2_p4 + jet_j_p4, 0., metP4);
	    double val2 = mT2(mu1_p4 + jet_j_p4, mu2_p4 + jet_i_p4, 0., metP4);
	    double local_min = (val1 < val2) ? val1: val2;
	    if (local_min < min_mt2topjj) {
	      min_mt2topjj = local_min;
	    }
	  }
	}
      }

      //	if ( min_mt2topjj < 180.) continue;


      // Determine if each muon is 'tight' by checking if it exists in muons_signal
      // (Requires #include <algorithm> at the top of your file, though often already included)
      bool mu1_tight = (std::find(muons_signal.begin(), muons_signal.end(), muons_base[i]) != muons_signal.end());
      bool mu2_tight = (std::find(muons_signal.begin(), muons_signal.end(), muons_base[j]) != muons_signal.end());

      // Count tight muons in this pair
      int nTight = (mu1_tight ? 1 : 0) + (mu2_tight ? 1 : 0);
      bool isTT = (nTight == 2);
      bool isTL = (nTight == 1);
      bool isLL = (nTight == 0);

      // Determine Opposite-Sign (OS) or Same-Sign (SS)
      bool isOS = (muons_base[i]->Charge * muons_base[j]->Charge < 0);
      bool isSS = !isOS;

      // Create a combined string tag (e.g., "TTOS", "TLSS")
      std::string pair_tag = "";
      if (isTT) pair_tag = "TT";
      else if (isTL) pair_tag = "TL";
      else if (isLL) pair_tag = "LL";
      pair_tag += (isOS ? "OS" : "SS");

      // 3. If the pair passes all cuts, save it along with its tags to our valid list
      valid_muon_pairs.push_back({muons_base[i], muons_base[j], isTT, isTL, isLL, isOS, isSS, pair_tag});	
      }
    }

    // Veto the entire event if no muon pairs passed the requirements
    if (valid_muon_pairs.empty()) return;
    countCutflowEvent("08_leptoncuts");
    countSignalEvent("SR-08-leptoncuts");

    if ( Njet > 2 ) return;
    countCutflowEvent("09_Nj<=2");
    //   histo_minv_Njle2->Fill(mll);
    
    countSignalEvent("SR-09-Njle2");
    
    if ( Njet >= 2 ) return;
    countCutflowEvent("10_Nj<2");
    
    //   histo_minv_Njlt2->Fill(mll);
    countSignalEvent("SR-10-Njlt2");

    if ( valid_muon_pairs.size() == 1 ) {
      std::string tag = valid_muon_pairs[0].tag;
      if ( tag == "TTSS" ) countSignalEvent("SR-11-TTSS");
      else if ( tag == "TLSS" ) countSignalEvent("SR-11-TLSS");
      else if ( tag == "TTOS" ) countSignalEvent("SR-11-TTOS");
      else if ( tag == "TLOS" ) countSignalEvent("SR-11-TLOS");
      // You can add LLOS/LLSS here if you eventually introduce those regions
    }
    else {
      cout << "valid muon pairs " << valid_muon_pairs.size() << "\n";
    }

      double mll = (valid_muon_pairs[0].mu1->P4() + valid_muon_pairs[0].mu2->P4()).M();
      if ( mll > 50 ) return;
      countCutflowEvent("12_mll_lt_50");
      std::string tag = valid_muon_pairs[0].tag;
      if ( tag == "TTSS" ) countSignalEvent("SR1-TTSS");
      else if ( tag == "TLSS" ) countSignalEvent("SR1-TLSS");
      else if ( tag == "TTOS" ) countSignalEvent("SR1-TTOS");
      else if ( tag == "TLOS" ) countSignalEvent("SR1-TLOS");
    
// (Optional) Count the event in cutflow since it passed the mll < 50 cut
//countCutflowEvent("xx_mll_lt_50"); 
// =========================================================================

// ... the rest of your analysis ...
// Note: You should update the rest of your code to use `valid_muon_pairs`. 
// For example, valid_muon_pairs[0].first and valid_muon_pairs[0].second 
// instead of assuming the first two muons in muons_base are the correct pair.
//  cout << "mt2_top=" << min_mt2topjj;

//  countCutflowEvent("06_drll<1.5");
  //  histo_mt2_top6->Fill(min_mt2topjj);

//  countSignalEvent("SR-drll");


  
  // if ( mtau >= 0. and mtau < 160. ) return;
  // countCutflowEvent("10_tauveto");
  
  // countSignalEvent("SR-tauveto");

  // //  histo_mt2->Fill(mt2_val);
  // //  histo_mt2_bkg->Fill(mt2bkg_val);

  // if ( mt2bkg_val <= 20. ) return;
  // countCutflowEvent("11_mt2bkgcut");

  // countSignalEvent("SR-mt2bkg");
  // //  histo_minv_mt2bkg->Fill(mll);
  //  histo_htj->Fill(htj);     


  // if (Nbjet==0 && Njet>=2) {
  //   //    cout << "in mT2 loop" << endl;
  //   for (unsigned int i=0; i< Njet; i++) {
  //     const auto jet_i_p4 = lightjets[i]->P4();
  //     for (unsigned int j=i+1; j< Njet; j++) {
  // 	const auto jet_j_p4 = lightjets[j]->P4();
  // 	double val1 = mT2(leptons[0] + jet_i_p4, leptons[1] + jet_j_p4, 0., metP4);
  // 	double val2 = mT2(leptons[0] + jet_j_p4, leptons[1] + jet_i_p4, 0., metP4);
  // 	double local_min = (val1 < val2) ? val1: val2;
  // 	if (local_min < min_mt2topjj) {
  // 	  min_mt2topjj = local_min;
  // 	}
  //     }
  //   }
  //   //    cout << "min_mt2topjj" << endl;;
  //   histo_mt2_top4->Fill(min_mt2topjj);
  // }
  // // if (Njet>=2) {
  // //   for (unsigned int i=0; i< Njet; i++) {
  // //     const auto jet_i_p4 = lightjets[i]->P4();
  // //     for (unsigned int j=i+1; j< Njet; j++) {
  // // 	const auto jet_j_p4 = lightjets[j]->P4();
  // // 	double val1 = mT2(leptons[0] + jet_i_p4, leptons[1] + jet_j_p4, 0., metP4);
  // // 	double val2 = mT2(leptons[0] + jet_j_p4, leptons[1] + jet_i_p4, 0., metP4);
  // // 	double local_min = (val1 < val2) ? val1: val2;
  // // 	if (local_min < min_mt2top) {
  // // 	  min_mt2top = local_min;
  // // 	}
  // //     }
  // //   }
  // //   //  histo_mt2_top->Fill(min_mt2top);
  // //  std::cout << "min_mt2top= " << min_mt2top << std::endl;
  // // }

  // //   histo_minv_mt2top->Fill(mll);


  //  if ( min_mt2topjj < 160.) return;
  //  countCutflowEvent("12_mt2top>160");
  //  //     histo_minv_mt2topgt160->Fill(mll);

  //  countSignalEvent("SR-mt2topgt160");
   
  //  if ( min_mt2topjj < 180.) return;
  //  countCutflowEvent("13_mt2top>180");
  //  //   histo_minv_mt2topgt180->Fill(mll);

  //  countSignalEvent("SR-mt2topgt180");

  // histo_minv->Fill(mll);

  // if (mll > 50.) return;
  // countCutflowEvent("14_mll<50");
  // countSignalEvent("SR1");

  //   histo_nlpbj->Fill(Njet+Nbjet);
  // std::vector<TLorentzVector> leptons;
  // std::vector<TLorentzVector> SSleptons;

  // if (( muons_signal.size() == 1 )&&( muons_not_tight.size() >= 1 )) {
  //   TLflag = true;    //For muon only
  //   leptons.push_back(muons_signal[0]->P4());
  //   SSleptons.push_back(muons_signal[0]->P4());
  //   for (int i = 0; i < muons_not_tight.size(); i++) {
  //     if ( muons_signal[0]->Charge * muons_not_tight[i]->Charge < 0 ) leptons.push_back(muons_not_tight[i]->P4());
  //     else SSleptons.push_back(muons_not_tight[i]->P4());
  //   }
  //   //    if (leptons.size() >= 2) OSflag = true;
  //   //    elseif (SSleptons.size() >=2) SSfla 
  // } 
  // else if ( muons_signal.size() == 2 ) {
  //   TTflag = true;
  //   leptons.push_back(muons_signal[0]->P4());
  //   leptons.push_back(muons_signal[1]->P4());
  //   if ( muons_signal[0]->Charge * muons_signal[1]->Charge < 0 ) {
  //      OSflag = true;}
  //   else SSflag = true;
  // }
  // else return;

  // if ( SSflag ) {
  //   if ( TLflag ) countSignalEvent("SR-TLSS");
  //   if ( TTflag ) countSignalEvent("SR-TTSS");}
  // else if ( OSflag ) {
  //   //    cout << "OS leptons" << endl;
  //   if ( TTflag ) countSignalEvent("SR-TTOS");
  //   if ( TLflag ) countSignalEvent("SR-TLOS");
  // }

  // if (Njet!=0){    
  // for(int i = 0; i < lightjets.size(); i++)
  //           sum += lightjets[i]->P4();


  // ptlj = sum.Perp();
  
  // }

  // histo_mtau->Fill(mtau);  

  // histo_mtl1l2->Fill(mtl1l2);  
    
  // histo_ptlep1->Fill(leptons[0].Perp());
  // histo_ptlep2->Fill(leptons[1].Perp());  
  // histo_ptlep->Fill(ptlep);
  // histo_htlep->Fill(htlep);

  // histo_dy->Fill(dy);
  // histo_dphi->Fill(dphi);
    
  // histo_drll->Fill(drll);
  // histo_dphi_l1l2_met->Fill(dphi_l1l2_met);      
  
  // histo_met_sig_lep->Fill(met_sig_lep);
}

void Atlas_2l_i3hdm_fakes::finalize() {
  // Whatever should be done after the run goes here
  // Whatever should be done after the run goes here

  TCanvas can1;
  histo_minv->Draw();
  histo_minv->SetTitle("lepton-lepton invariant");
  can1.Close();

  TCanvas can2;
  histo_met->Draw();
  histo_met->SetTitle("Missing ET");
  can2.Close();

  TCanvas can3;
  histo_ptlep1->Draw();
  histo_ptlep1->SetTitle("l1 PT");
  can3.Close();

  TCanvas can4;
  histo_drll->Draw();
  histo_drll->SetTitle("DeltaR [l1l2]");
  can4.Close();

  TCanvas can5;
  histo_dy->Draw();
  histo_dy->SetTitle("dy [l1l2]");
  can5.Close();

  TCanvas can6;
  histo_ptlep2->Draw();
  histo_ptlep2->SetTitle("l2 PT");
  can6.Close();

  TCanvas can8;
  histo_mtl1l2->Draw();
  histo_mtl1l2->SetTitle("MT [l1l2]");
  can8.Close();

  TCanvas can9;
  histo_mt2->Draw();
  histo_mt2->SetTitle("mT2");
  can9.Close();

  TCanvas can10;
  histo_ptlep->Draw();
  histo_ptlep->SetTitle("PTlep");
  can10.Close();

  TCanvas can11;
  histo_dphi->Draw();
  histo_dphi->SetTitle("dPhi [l1l2]");
  can11.Close();

  TCanvas can12;
  histo_met_sig_lep->Draw();
  histo_met_sig_lep->SetTitle("ETmiss/HTlep");
  can12.Close();

  TCanvas can15;
  histo_ptj1->Draw();
  histo_ptj1->SetTitle("PTj1");
  can15.Close();

  TCanvas can17;
  histo_njet->Draw();
  histo_njet->SetTitle("Njet");
  can17.Close();

  TCanvas can24;
  histo_dphi_jet1_met->Draw();
  histo_dphi_jet1_met->SetTitle("dPhi [j1-MET]");
  can24.Close();

  TCanvas can26;
  histo_dr_jet1_met->Draw();
  histo_dr_jet1_met->SetTitle("dr [j1-MET]");
  can26.Close();

  TCanvas can27;
  histo_dphi_l1l2_met->Draw();
  histo_dphi_l1l2_met->SetTitle("dPhi [l1l2-MET]");
  can27.Close();

  TCanvas can28;
  histo_met_sig_jet->Draw();
  histo_met_sig_jet->SetTitle("ETmiss/HTjet");
  can28.Close();

  TCanvas can29;
  histo_htlep->Draw();
  histo_htlep->SetTitle("HTlep");
  can29.Close();

  TCanvas can30;
  histo_htj->Draw();
  histo_htj->SetTitle("HTj");
  can30.Close();

  // TCanvas can31;
  // histo_ptj_met->Draw();
  // histo_ptj_met->SetTitle("PTj-MET");
  // can31.Close();

  // TCanvas can32;
  // histo_ptj1_met->Draw();
  // histo_ptj1_met->SetTitle("PTj1-MET");
  // can32.Close();

  // TCanvas can33;
  // histo_ptlj_met->Draw();
  // histo_ptlj_met->SetTitle("PTlj-MET");
  // can33.Close();
  
  // TCanvas can34;
  // histo_mll_met->Draw();
  // histo_mll_met->SetTitle("mll-MET");
  // can34.Close();

  // TCanvas can35;
  // histo_htlep_met->Draw();
  // histo_htlep_met->SetTitle("htlep-met");
  // can35.Close();

  // TCanvas can36;
  // histo_htj_met->Draw();
  // histo_htj_met->SetTitle("htj-met");
  // can36.Close();

  // TCanvas can37;
  // histo_htlep_mll->Draw();
  // histo_htlep_mll->SetTitle("htlep-mll");
  // can37.Close();

  // TCanvas can38;
  // histo_htj_mll->Draw();
  // histo_htj_mll->SetTitle("htj-mll");
  // can38.Close();
  
  // TCanvas can39;
  // histo_drll_met->Draw();
  // histo_drll_met->SetTitle("drll-met");
  // can39.Close();

  // TCanvas can40;
  // histo_dphi_met->Draw();
  // histo_dphi_met->SetTitle("dphi[l1l2]-met");
  // can40.Close();
  
  // TCanvas can41;
  // histo_dphi_j1_met->Draw();
  // histo_dphi_j1_met->SetTitle("dphi[jet1-met]-met");
  // can41.Close();
  
  TCanvas can31;
  histo_mtau->Draw();
  histo_mtau->SetTitle("m_tautau");
  can31.Close();

  TCanvas can32;
  histo_mt2_bkg->Draw();
  histo_mt2_bkg->SetTitle("mT2_bkg");
  can32.Close();

  TCanvas can33;
  histo_mt2_top4->Draw();
  histo_mt2_top4->SetTitle("mT2_top");
  can33.Close();

  hfile->Write();
  hfile->Close();
}       
double Atlas_2l_i3hdm_fakes::mtautau(const TLorentzVector lep1, const TLorentzVector lep2, const TLorentzVector ptmiss) {

  double wg = lep1.X()*lep2.Y() - lep1.Y()*lep2.X();
  if (wg == 0. ) return 0.;

  double w1 = ptmiss.X()*lep2.Y() - ptmiss.Y()*lep2.X();
  double w2 = lep1.X()*ptmiss.Y() - lep1.Y()*ptmiss.X();

  double x1 = w1/wg;
  double x2 = w2/wg;

  double mtau2 = 2.*(lep1*lep2)*(1. + x1)*(1. + x2);

  if (mtau2 >= 0) return sqrt(mtau2); else return -sqrt(-mtau2);
}


bool Atlas_2l_i3hdm_fakes::check_nTrack_jet(Jet* jet, std::vector<Track*> tracks, int nTracksMin) {

  int nTracks = 0;
  for (std::vector<Track*>::iterator it=tracks.begin(); it!=tracks.end(); it++)
    for (int part = 0; part < jet->Particles.GetEntries(); part++)
      if (jet->Particles.At(part) == (*it)->Particle && (*it)->PT > 0.5) nTracks++;

    return nTracks > nTracksMin;
}

std::vector<Jet*> Atlas_2l_i3hdm_fakes::overlapRemoval_muon_jet_tracks(std::vector<Jet*> cand_jets, std::vector<Muon*> cand_muons, double deltaR, int nTracks){

  std::vector<Jet*> passed;
  for (std::vector<Jet*>::iterator jet = cand_jets.begin(); jet != cand_jets.end(); jet++) {

    if (check_nTrack_jet(*jet, tracks, nTracks)) {
      passed.push_back(*jet);
      continue;
    }

    bool iso = true;

    for (std::vector<Muon*>::iterator mu = cand_muons.begin(); mu != cand_muons.end(); mu++)
      if ((*jet)->P4().DeltaR((*mu)->P4()) < deltaR ) {
        iso = false;
        break;
      }

    if (iso) passed.push_back(*jet);
  }

  return passed;
}

