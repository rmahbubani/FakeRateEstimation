#ifndef ATLAS_2L_I3HDM_FAKES_H_
#define ATLAS_2L_I3HDM_FAKES_H_
// AUTHOR: Rakhi
//  EMAIL: rakhi@cern
#include "AnalysisBase.h"
#include "TH2F.h"
#include "TGraph.h"
#include <algorithm> // for std::min
#include <limits> // for std:numeric_limits

class Atlas_2l_i3hdm_fakes : public AnalysisBase {
  public:
    Atlas_2l_i3hdm_fakes() : AnalysisBase()  {}               
    ~Atlas_2l_i3hdm_fakes() {}
  
    void initialize();
    void analyze();        
    void finalize();

  private:
    double mtautau(const TLorentzVector, const TLorentzVector, const TLorentzVector);
    bool check_nTrack_jet(Jet* jet, std::vector<Track*> tracks, int nTracksMin) ;
    std::vector<Jet*> overlapRemoval_muon_jet_tracks(std::vector<Jet*> cand_jets, std::vector<Muon*> cand_muons, double deltaR, int nTracks);
  TFile *hfile;
  TH1F *histo_minv,*histo_met,*histo_ptlep1,*histo_ptlep2,*histo_dy,*histo_dphi,*histo_dphi_jet1_met,*histo_dphi_l1l2_met,*histo_drll,*histo_dr_jet1_met,*histo_mtl1l2,*histo_mt2,*histo_mt2_bkg,*histo_mt2_top4,
    *histo_ptlep,*histo_htlep,*histo_htj,*histo_met_sig_lep,*histo_met_sig_jet,*histo_njet,*histo_ptj1,*histo_nbjet, *histo_ptbj1, *histo_dphi_l1_met, *histo_mtau;

  //  TH2F *histo_ptj_met,*histo_ptj1_met, *histo_ptlj_met,*histo_htlep_met,*histo_htj_met,*histo_mll_met,*histo_htlep_mll,*histo_htj_mll,*histo_drll_met,*histo_dphi_met,*histo_dphi_j1_met;
};

#endif
