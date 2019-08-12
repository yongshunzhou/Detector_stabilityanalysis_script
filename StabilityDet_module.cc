
/**
 * @file    StabilityDet_module.cc
 * @brief   Module for monitoring good run selection variables
 * @Author: Aleena Rafique (aleena@ksu.edu) & Yongshun Zhou (yongshun@uchicago.edu)
 *
 ******************************************************************************/

  // Framework includes
#include "art/Framework/Core/EDAnalyzer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"
#include "art/Framework/Principal/Handle.h"
#include "art/Framework/Principal/Run.h"
#include "art/Framework/Principal/SubRun.h"
#include "art/Framework/Services/Registry/ServiceHandle.h"
#include "art_root_io/RootIOPolicy.h"
#include "art_root_io/TFileService.h"
#include "art_root_io/TFileDirectory.h"
#include "canvas/Persistency/Common/FindManyP.h"
#include "canvas/Persistency/Common/FindMany.h"
#include "canvas/Persistency/Common/PtrVector.h"
#include "messagefacility/MessageLogger/MessageLogger.h"
#include "fhiclcpp/ParameterSet.h"
#include "lardata/Utilities/AssociationUtil.h"


  // LArSoft Includes
#include "larcore/Geometry/Geometry.h"
#include "nusimdata/SimulationBase/MCTruth.h"
#include "nusimdata/SimulationBase/MCFlux.h"
#include "nusimdata/SimulationBase/MCParticle.h"
#include "lardataobj/Simulation/SimChannel.h"
#include "lardataobj/Simulation/AuxDetSimChannel.h"
#include "lardataobj/MCBase/MCShower.h"
#include "lardataobj/MCBase/MCTrack.h"
#include "lardataobj/MCBase/MCStep.h"
#include "lardataobj/AnalysisBase/Calorimetry.h"
#include "lardataobj/AnalysisBase/ParticleID.h"
#include "lardataobj/RawData/RawDigit.h"
#include "lardataobj/RawData/raw.h"
#include "lardataobj/RawData/BeamInfo.h"
#include "lardataobj/RecoBase/PFParticle.h"
#include "lardata/Utilities/AssociationUtil.h"
#include "lardata/DetectorInfoServices/DetectorPropertiesService.h"
#include "larcoreobj/SummaryData/POTSummary.h"
#include "larsim/MCCheater/BackTrackerService.h"
#include "larsim/MCCheater/ParticleInventoryService.h"
#include "lardataobj/RecoBase/Track.h"
#include "lardataobj/RecoBase/Shower.h"
#include "lardataobj/RecoBase/TrackHitMeta.h"
#include "lardataobj/RecoBase/Cluster.h"
#include "lardataobj/RecoBase/SpacePoint.h"
#include "lardataobj/RecoBase/PointCharge.h"
#include "lardataobj/RecoBase/Hit.h"
#include "lardataobj/RecoBase/Wire.h"
#include "lardataobj/RecoBase/EndPoint2D.h"
#include "lardataobj/RecoBase/Vertex.h"
#include "lardataobj/RecoBase/OpFlash.h"
#include "lardataobj/RecoBase/PFParticle.h"
#include "larcoreobj/SimpleTypesAndConstants/geo_types.h"
#include "lardataobj/RawData/RDTimeStamp.h"
#include "dune-raw-data/Overlays/TimingFragment.hh"
#include "dunetpc/dune/DuneObj/ProtoDUNETimeStamp.h"
#include "larreco/RecoAlg/TrackMomentumCalculator.h"
#include "lardataobj/AnalysisBase/CosmicTag.h"
#include "lardataobj/AnalysisBase/FlashMatch.h"
#include "lardataobj/AnalysisBase/T0.h"
#include "lardataobj/AnalysisBase/BackTrackerMatchingData.h"
#include "larevt/SpaceChargeServices/SpaceChargeService.h"
#include "dune/OpticalDetector/OpFlashSort.h"
#include "dune/Protodune/Analysis/ProtoDUNETrackUtils.h"
#include "dune/Protodune/Analysis/ProtoDUNETruthUtils.h"
#include "dune/Protodune/Analysis/ProtoDUNEPFParticleUtils.h"

#include "TFile.h"
#include "TTree.h"
#include "TDirectory.h"
#include "TH1.h"
#include "TH2.h"
#include "TF1.h"
#include "TProfile.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TMath.h"
#include "TGraphErrors.h"
#include "TMinuit.h"
#include "TString.h"
#include "TTimeStamp.h"
#include "TVectorD.h"
#include "TCanvas.h"
#include "TFrame.h"
#include "TLine.h"
#include "TAxis.h"
#include "TTimeStamp.h"
#include "TVector3.h"

#include <vector>
#include <fstream>
#include "TPaveStats.h"
#include <iostream>
#include <string>
#include "math.h"
#include "stdio.h"
#include <iterator>

#include <cstddef> // std::ptrdiff_t
#include <cstring> // std::memcpy()
#include <vector>
#include <map>
#include <iterator> // std::begin(), std::end()
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <functional> // std::mem_fun_ref
#include <typeinfo>
#include <memory> // std::unique_ptr<>

#include "TTree.h"
#include "TTimeStamp.h"

/*From StabilityDet:?
#include "cetlib/exception.h"
#include "canvas/Persistency/Common/Ptr.h"
#include "art/Framework/Services/Optional/TFileService.h"
#include "art/Framework/Services/Optional/TFileDirectory.h"
#include "canvas/Utilities/InputTag.h"
#include "lardataobj/RawData/TriggerData.h"
#include "uboone/RawData/utils/ubdaqSoftwareTriggerData.h"
#include <sys/stat.h>
#include "TMatrixD.h"
#include "TH1D.h"
#include "TGeoManager.h"
#include "TF2.h"
#include "TGraph.h"
#include "TH2F.h"*/

using namespace std;

  namespace StabilityDet {

    class StabilityDet : public art::EDAnalyzer
    {

    public:

     explicit StabilityDet(fhicl::ParameterSet const &pset);
     virtual ~StabilityDet();

      // The actual method for analyzing the events
     void analyze(art::Event const& evt) ;
     //void beginSubRun(const art::SubRun& sr);

     // Allow for fhicl parameters to possibly change during processing...
     //void reconfigure(fhicl::ParameterSet const&)  ;

     // Called when job begins for definitions of histograms/tuples/etc.
     void beginJob()  ;

     // Called when job completes to deal with output of stuff from beginJob
     void endJob();

     // Recover information from the start of a run (if processing across runs)
     void beginRun(const art::Run&);

     // Recover information at the end of a run (if processing across runs)
     void endRun(const art::Run&);

    // Length of reconstructed track, trajectory by trajectory.
    double length(const recob::Track& track);

      private:

    TTree* fDataTree;

    int numevent = 0; //number of event counter

    int Run=-999;
    static const int n = 20000;

    int    Nentries[n]={0};
    int    Nevts[n]={0};
    float  Nrun[n]={0};

    float N_ntrack_pmtrack[n]={0};
    float N_ntrack_pandoraTrack[n]={0};
    float N_trklen_pmtrack[n]={0};
    float N_trklen_pandoraTrack[n]={0};
    float N_nshwr_pandoraShower[n]={0};
    float N_shwrlen_pandoraShower[n]={0};
    float N_nhit_tot[n]={0};
    float N_nhit_U[n]={0};
    float N_nhit_V[n]={0};
    float N_nhit_Y[n]={0};
    float N_hit_ph[n]={0};
    float N_hitph_U[n]={0};
    float N_hitph_V[n]={0};
    float N_hitph_Y[n]={0};
    float N_hit_charge[n]={0};
    float N_hitcharge_U[n]={0};
    float N_hitcharge_V[n]={0};
    float N_hitcharge_Y[n]={0};
    float N_nflashTot_opflashExt[n]={0};
    float N_nflashPE50_opflashExt[n]={0};
    float N_nflashPE20_opflashExt[n]={0};
    float N_nflashPE0_20_opflashExt[n]={0};
    float N_nflashTot_opflashInt[n]={0};
    float N_nflashPE50_opflashInt[n]={0};
    float N_nflashPE20_opflashInt[n]={0};
    float N_nflashPE0_20_opflashInt[n]={0};
    float N_flashycenter_opflashExt[n]={0};
    //float N_flashycenterPE0_20_opflashExt[n]={0};
    float N_flashycenterPE20_opflashExt[n]={0};
    float N_flashycenterPE50_opflashExt[n]={0};
    float N_flashzcenter_opflashExt[n]={0};
    //float N_flashzcenterPE0_20_opflashExt[n]={0};
    float N_flashzcenterPE20_opflashExt[n]={0};
    float N_flashzcenterPE50_opflashExt[n]={0};
    float N_flashycenter_opflashInt[n]={0};
    //float N_flashycenterPE0_20_opflashInt[n]={0};
    float N_flashycenterPE20_opflashInt[n]={0};
    float N_flashycenterPE50_opflashInt[n]={0};
    float N_flashzcenter_opflashInt[n]={0};
    //float N_flashzcenterPE0_20_opflashInt[n]={0};
    float N_flashzcenterPE20_opflashInt[n]={0};
    float N_flashzcenterPE50_opflashInt[n]={0};
    float N_flashPE_opflashExt[n]={0};
    float N_flashPE_opflashInt[n]={0};
    float N_nvrtx_pmtrack[n]={0};
    float N_nvrtx_pandora[n]={0};
    float N_npfps_pmtrack[n]={0};
    float N_npfps_pandora[n]={0};
    float N_trackpos_beginx_pmtrack[n]={0};
    float N_trackpos_beginy_pmtrack[n]={0};
    float N_trackpos_beginz_pmtrack[n]={0};
    float N_trackpos_beginx_pandoraTrack[n]={0};
    float N_trackpos_beginy_pandoraTrack[n]={0};
    float N_trackpos_beginz_pandoraTrack[n]={0};
    float N_trackpos_endx_pmtrack[n]={0};
    float N_trackpos_endy_pmtrack[n]={0};
    float N_trackpos_endz_pmtrack[n]={0};
    float N_trackpos_endx_pandoraTrack[n]={0};
    float N_trackpos_endy_pandoraTrack[n]={0};
    float N_trackpos_endz_pandoraTrack[n]={0};
    float N_Intflash_ywidth[n]={0};
    float N_Intflash_zwidth[n]={0};
    float N_Extflash_ywidth[n]={0};
    float N_Extflash_zwidth[n]={0};

    float N_rms_ntrack_pmtrack[n]={0};
    float N_rms_ntrack_pandoraTrack[n]={0};
    float N_rms_trklen_pmtrack[n]={0};
    float N_rms_trklen_pandoraTrack[n]={0};
    float N_rms_nshwr_pandoraShower[n]={0};
    float N_rms_shwrlen_pandoraShower[n]={0};
    float N_rms_nhit_tot[n]={0};
    float N_rms_nhit_U[n]={0};
    float N_rms_nhit_V[n]={0};
    float N_rms_nhit_Y[n]={0};
    float N_rms_hit_ph[n]={0};
    float N_rms_hitph_U[n]={0};
    float N_rms_hitph_V[n]={0};
    float N_rms_hitph_Y[n]={0};
    float N_rms_hit_charge[n]={0};
    float N_rms_hitcharge_U[n]={0};
    float N_rms_hitcharge_V[n]={0};
    float N_rms_hitcharge_Y[n]={0};
    float N_rms_nflashTot_opflashExt[n]={0};
    float N_rms_nflashPE50_opflashExt[n]={0};
    float N_rms_nflashPE20_opflashExt[n]={0};
    float N_rms_nflashPE0_20_opflashExt[n]={0};
    float N_rms_nflashTot_opflashInt[n]={0};
    float N_rms_nflashPE50_opflashInt[n]={0};
    float N_rms_nflashPE20_opflashInt[n]={0};
    float N_rms_nflashPE0_20_opflashInt[n]={0};
    float N_rms_flashycenter_opflashExt[n]={0};
    //float N_rms_flashycenterPE0_20_opflashExt[n]={0};
    float N_rms_flashycenterPE20_opflashExt[n]={0};
    float N_rms_flashycenterPE50_opflashExt[n]={0};
    float N_rms_flashzcenter_opflashExt[n]={0};
    //float N_rms_flashzcenterPE0_20_opflashExt[n]={0};
    float N_rms_flashzcenterPE20_opflashExt[n]={0};
    float N_rms_flashzcenterPE50_opflashExt[n]={0};
    float N_rms_flashycenter_opflashInt[n]={0};
    //float N_rms_flashycenterPE0_20_opflashInt[n]={0};
    float N_rms_flashycenterPE20_opflashInt[n]={0};
    float N_rms_flashycenterPE50_opflashInt[n]={0};
    float N_rms_flashzcenter_opflashInt[n]={0};
    //float N_rms_flashzcenterPE0_20_opflashInt[n]={0};
    float N_rms_flashzcenterPE20_opflashInt[n]={0};
    float N_rms_flashzcenterPE50_opflashInt[n]={0};
    float N_rms_flashPE_opflashExt[n]={0};
    float N_rms_flashPE_opflashInt[n]={0};
    float N_rms_nvrtx_pmtrack[n]={0};
    float N_rms_nvrtx_pandora[n]={0};
    float N_rms_npfps_pmtrack[n]={0};
    float N_rms_npfps_pandora[n]={0};
    float N_rms_trackpos_beginx_pmtrack[n]={0};
    float N_rms_trackpos_beginy_pmtrack[n]={0};
    float N_rms_trackpos_beginz_pmtrack[n]={0};
    float N_rms_trackpos_beginx_pandoraTrack[n]={0};
    float N_rms_trackpos_beginy_pandoraTrack[n]={0};
    float N_rms_trackpos_beginz_pandoraTrack[n]={0};
    float N_rms_trackpos_endx_pmtrack[n]={0};
    float N_rms_trackpos_endy_pmtrack[n]={0};
    float N_rms_trackpos_endz_pmtrack[n]={0};
    float N_rms_trackpos_endx_pandoraTrack[n]={0};
    float N_rms_trackpos_endy_pandoraTrack[n]={0};
    float N_rms_trackpos_endz_pandoraTrack[n]={0};
    float N_rms_Intflash_ywidth[n]={0};
    float N_rms_Intflash_zwidth[n]={0};
    float N_rms_Extflash_ywidth[n]={0};
    float N_rms_Extflash_zwidth[n]={0};

    float _frun;
    float _fnumevent;

    float _f_mean_ntrack_pmtrack;
    float _f_mean_ntrack_pandoraTrack;
    float _f_mean_trklen_pmtrack;
    float _f_mean_trklen_pandoraTrack;
    float _f_mean_nshwr_pandoraShower;
    float _f_mean_shwrlen_pandoraShower;
    float _f_mean_nhit_tot;
    float _f_mean_nhit_U;
    float _f_mean_nhit_V;
    float _f_mean_nhit_Y;
    float _f_mean_hit_ph;
    float _f_mean_hitph_U;
    float _f_mean_hitph_V;
    float _f_mean_hitph_Y;
    float _f_mean_hit_charge;
    float _f_mean_hitcharge_U;
    float _f_mean_hitcharge_V;
    float _f_mean_hitcharge_Y;
    float _f_mean_nflashTot_opflashExt;
    float _f_mean_nflashPE50_opflashExt;
    float _f_mean_nflashPE20_opflashExt;
    float _f_mean_nflashPE0_20_opflashExt;
    float _f_mean_nflashTot_opflashInt;
    float _f_mean_nflashPE50_opflashInt;
    float _f_mean_nflashPE20_opflashInt;
    float _f_mean_nflashPE0_20_opflashInt;
    float _f_mean_flashycenter_opflashExt;
    //float _f_mean_flashycenterPE0_20_opflashExt;
    float _f_mean_flashycenterPE20_opflashExt;
    float _f_mean_flashycenterPE50_opflashExt;
    float _f_mean_flashzcenter_opflashExt;
    //float _f_mean_flashzcenterPE0_20_opflashExt;
    float _f_mean_flashzcenterPE20_opflashExt;
    float _f_mean_flashzcenterPE50_opflashExt;
    float _f_mean_flashycenter_opflashInt;
    //float _f_mean_flashycenterPE0_20_opflashInt;
    float _f_mean_flashycenterPE20_opflashInt;
    float _f_mean_flashycenterPE50_opflashInt;
    float _f_mean_flashzcenter_opflashInt;
    //float _f_mean_flashzcenterPE0_20_opflashInt;
    float _f_mean_flashzcenterPE20_opflashInt;
    float _f_mean_flashzcenterPE50_opflashInt;
    float _f_mean_flashPE_opflashExt;
    float _f_mean_flashPE_opflashInt;
    float _f_mean_nvrtx_pmtrack;
    float _f_mean_nvrtx_pandora;
    float _f_mean_npfps_pmtrack;
    float _f_mean_npfps_pandora;
    float _f_mean_trackpos_beginx_pmtrack;
    float _f_mean_trackpos_beginy_pmtrack;
    float _f_mean_trackpos_beginz_pmtrack;
    float _f_mean_trackpos_beginx_pandoraTrack;
    float _f_mean_trackpos_beginy_pandoraTrack;
    float _f_mean_trackpos_beginz_pandoraTrack;
    float _f_mean_trackpos_endx_pmtrack;
    float _f_mean_trackpos_endy_pmtrack;
    float _f_mean_trackpos_endz_pmtrack;
    float _f_mean_trackpos_endx_pandoraTrack;
    float _f_mean_trackpos_endy_pandoraTrack;
    float _f_mean_trackpos_endz_pandoraTrack;
    float _f_mean_Intflash_ywidth;
    float _f_mean_Intflash_zwidth;
    float _f_mean_Extflash_ywidth;
    float _f_mean_Extflash_zwidth;

    float _f_rms_ntrack_pmtrack;
    float _f_rms_ntrack_pandoraTrack;
    float _f_rms_trklen_pmtrack;
    float _f_rms_trklen_pandoraTrack;
    float _f_rms_nshwr_pandoraShower;
    float _f_rms_shwrlen_pandoraShower;
    float _f_rms_nhit_tot;
    float _f_rms_nhit_U;
    float _f_rms_nhit_V;
    float _f_rms_nhit_Y;
    float _f_rms_hit_ph;
    float _f_rms_hitph_U;
    float _f_rms_hitph_V;
    float _f_rms_hitph_Y;
    float _f_rms_hit_charge;
    float _f_rms_hitcharge_U;
    float _f_rms_hitcharge_V;
    float _f_rms_hitcharge_Y;
    float _f_rms_nflashTot_opflashExt;
    float _f_rms_nflashPE50_opflashExt;
    float _f_rms_nflashPE20_opflashExt;
    float _f_rms_nflashPE0_20_opflashExt;
    float _f_rms_nflashTot_opflashInt;
    float _f_rms_nflashPE50_opflashInt;
    float _f_rms_nflashPE20_opflashInt;
    float _f_rms_nflashPE0_20_opflashInt;
    float _f_rms_flashycenter_opflashExt;
    //float _f_rms_flashycenterPE0_20_opflashExt;
    float _f_rms_flashycenterPE20_opflashExt;
    float _f_rms_flashycenterPE50_opflashExt;
    float _f_rms_flashzcenter_opflashExt;
    //float _f_rms_flashzcenterPE0_20_opflashExt;
    float _f_rms_flashzcenterPE20_opflashExt;
    float _f_rms_flashzcenterPE50_opflashExt;
    float _f_rms_flashycenter_opflashInt;
    //float _f_rms_flashycenterPE0_20_opflashInt;
    float _f_rms_flashycenterPE20_opflashInt;
    float _f_rms_flashycenterPE50_opflashInt;
    float _f_rms_flashzcenter_opflashInt;
    //float _f_rms_flashzcenterPE0_20_opflashInt;
    float _f_rms_flashzcenterPE20_opflashInt;
    float _f_rms_flashzcenterPE50_opflashInt;
    float _f_rms_flashPE_opflashExt;
    float _f_rms_flashPE_opflashInt;
    float _f_rms_nvrtx_pmtrack;
    float _f_rms_nvrtx_pandora;
    float _f_rms_npfps_pmtrack;
    float _f_rms_npfps_pandora;
    float _f_rms_trackpos_beginx_pmtrack;
    float _f_rms_trackpos_beginy_pmtrack;
    float _f_rms_trackpos_beginz_pmtrack;
    float _f_rms_trackpos_beginx_pandoraTrack;
    float _f_rms_trackpos_beginy_pandoraTrack;
    float _f_rms_trackpos_beginz_pandoraTrack;
    float _f_rms_trackpos_endx_pmtrack;
    float _f_rms_trackpos_endy_pmtrack;
    float _f_rms_trackpos_endz_pmtrack;
    float _f_rms_trackpos_endx_pandoraTrack;
    float _f_rms_trackpos_endy_pandoraTrack;
    float _f_rms_trackpos_endz_pandoraTrack;
    float _f_rms_Intflash_ywidth;
    float _f_rms_Intflash_zwidth;
    float _f_rms_Extflash_ywidth;
    float _f_rms_Extflash_zwidth;



    TH1F* _run;
    TH1F* _ntrack_pmtrack ;
    TH1F* _ntrack_pandoraTrack    ;
    TH1F* _trklen_pmtrack     ;
    TH1F* _trklen_pandoraTrack  ;
    TH1F* _nshwr_pandoraShower;
    TH1F* _shwrlen_pandoraShower;
    TH1F* _nhit_tot                 ;
    TH1F* _nhit_U                ;
    TH1F* _nhit_V                ;
    TH1F* _nhit_Y                ;
    TH1F* _hit_ph               ;
    TH1F* _hitph_U              ;
    TH1F* _hitph_V              ;
    TH1F* _hitph_Y              ;
    TH1F* _hit_charge           ;
    TH1F* _hitcharge_U          ;
    TH1F* _hitcharge_V          ;
    TH1F* _hitcharge_Y          ;
    TH1F* _nflashTot_opflashExt    ;
    TH1F* _nflashPE50_opflashExt  ;
    TH1F* _nflashPE20_opflashExt  ;
    TH1F* _nflashPE0_20_opflashExt;
    TH1F* _nflashTot_opflashInt ;
    TH1F* _nflashPE50_opflashInt  ;
    TH1F* _nflashPE20_opflashInt  ;
    TH1F* _nflashPE0_20_opflashInt;
    TH1F* _flashycenter_opflashExt  ;
    TH1F* _flashycenterPE50_opflashExt;
    TH1F* _flashycenterPE20_opflashExt;
    //TH1F* _flash_ycenter0_20_opflashExt;
    TH1F* _flashzcenter_opflashExt  ;
    TH1F* _flashzcenterPE50_opflashExt;
    TH1F* _flashzcenterPE20_opflashExt;
    //TH1F* _flash_zcenter0_20_opflashExt;
    TH1F* _flashycenter_opflashInt   ;
    TH1F* _flashycenterPE50_opflashInt ;
    TH1F* _flashycenterPE20_opflashInt ;
    //TH1F* _flashycenter0_20_opflashInt;
    TH1F* _flashzcenter_opflashInt   ;
    TH1F* _flashzcenterPE50_opflashInt ;
    TH1F* _flashzcenterPE20_opflashInt ;
    //TH1F* _flashzcenter0_20_opflashInt;
    TH1F* _flashPE_opflashExt     ;
    TH1F* _flashPE_opflashInt;
    TH1F* _nvrtx_pmtrack;
    TH1F* _nvrtx_pandora;
    TH1F* _npfps_pmtrack;
    TH1F* _npfps_pandora;
    TH1F* _trackpos_beginx_pmtrack;
    TH1F* _trackpos_beginy_pmtrack;
    TH1F* _trackpos_beginz_pmtrack;
    TH1F* _trackpos_beginx_pandoraTrack;
    TH1F* _trackpos_beginy_pandoraTrack;
    TH1F* _trackpos_beginz_pandoraTrack;
    TH1F* _trackpos_endx_pmtrack;
    TH1F* _trackpos_endy_pmtrack;
    TH1F* _trackpos_endz_pmtrack;
    TH1F* _trackpos_endx_pandoraTrack;
    TH1F* _trackpos_endy_pandoraTrack;
    TH1F* _trackpos_endz_pandoraTrack;
    TH1F* _Intflash_ywidth;
    TH1F* _Intflash_zwidth;
    TH1F* _Extflash_ywidth;
    TH1F* _Extflash_zwidth;


    std::string              fHitsModuleLabel;
    std::string              fPandoraTrackModuleLabel;
    std::string              fPmtrackModuleLabel;
    std::string              fPandoraShowerModuleLabel;
    std::string              fPandoraVrtxModuleLabel;
    std::string              fPmtrackVrtxModuleLabel;
    std::string              fPandoraPFPFModuleLabel;
    std::string              fPmtrackPFPFModuleLabel;
    std::string              fOpflashIntModuleLabel;
    std::string              fOpflashExtModuleLabel;

    bool      fSaveCaloInfo;
    bool      fSaveTrackInfo;
   };

   //-----------------------------------------------------------------------
    // Constructor
    StabilityDet::StabilityDet(fhicl::ParameterSet const& pset)
   : EDAnalyzer(pset),

   fHitsModuleLabel            (pset.get< std::string >("HitsModuleLabel",          " ")  ),
   fPandoraTrackModuleLabel    (pset.get< std::string >("PandoraTrackModuleLabel",  " ")  ),
   fPmtrackModuleLabel         (pset.get< std::string >("PmtrackModuleLabel",       " ")  ),
   fPandoraShowerModuleLabel   (pset.get< std::string >("PandoraShowerModuleLabel", " ")  ),
   fPandoraVrtxModuleLabel     (pset.get< std::string >("PandoraVrtxModuleLabel",   " ")  ),
   fPmtrackVrtxModuleLabel     (pset.get< std::string >("PmtrackVrtxModuleLabel",   " ")  ),
   fPandoraPFPFModuleLabel     (pset.get< std::string >("PandoraPFPFModuleLabel",   " ")  ),
   fPmtrackPFPFModuleLabel     (pset.get< std::string >("PmtrackPFPFModuleLabel",   " ")  ),
   fOpflashIntModuleLabel      (pset.get< std::string >("OpflashIntModuleLabel",    " ")  ),
   fOpflashExtModuleLabel      (pset.get< std::string >("OpflashExtModuleLabel",    " ")  ),
   fSaveCaloInfo             (pset.get< bool>("SaveCaloInfo",false)),
   fSaveTrackInfo            (pset.get< bool>("SaveTrackInfo",false))

 {
   if (fSaveTrackInfo == false) fSaveCaloInfo = false;
 }

    //-----------------------------------------------------------------------
    // Destructor
    StabilityDet::~StabilityDet()
   {
    }

   //-----------------------------------------------------------------------
   void StabilityDet::beginJob()
   {

    std::cout<<"job begin..."<<std::endl;
    art::ServiceHandle<art::TFileService> tfs;

    fDataTree = tfs->make<TTree>("fDataTree","Data Holder");

    fDataTree->Branch("_frun",&_frun,"_frun/F");
    fDataTree->Branch("_fnumevent",&_fnumevent,"_fnumevent/F");

    fDataTree->Branch("_f_mean_ntrack_pmtrack",&_f_mean_ntrack_pmtrack,"_f_mean_ntrack_pmtrack/F");
    fDataTree->Branch("_f_mean_ntrack_pandoraTrack",&_f_mean_ntrack_pandoraTrack,"_f_mean_ntrack_pandoraTrack/F");
    fDataTree->Branch("_f_mean_trklen_pmtrack",&_f_mean_trklen_pmtrack,"_f_mean_trklen_pmtrack/F");
    fDataTree->Branch("_f_mean_trklen_pandoraTrack",&_f_mean_trklen_pandoraTrack,"_f_mean_trklen_pandoraTrack/F");
    fDataTree->Branch("_f_mean_nshwr_pandoraShower",&_f_mean_nshwr_pandoraShower,"_f_mean_nshwr_pandoraShower/F");
    fDataTree->Branch("_f_mean_shwrlen_pandoraShower",&_f_mean_shwrlen_pandoraShower,"_f_mean_shwrlen_pandoraShower/F");
    fDataTree->Branch("_f_mean_nhit_tot",&_f_mean_nhit_tot,"_f_mean_nhit_tot/F");
    fDataTree->Branch("_f_mean_nhit_U",&_f_mean_nhit_U,"_f_mean_nhit_U/F");
    fDataTree->Branch("_f_mean_nhit_V",&_f_mean_nhit_V,"_f_mean_nhit_V/F");
    fDataTree->Branch("_f_mean_nhit_Y",&_f_mean_nhit_Y,"_f_mean_nhit_Y/F");
    fDataTree->Branch("_f_mean_hit_ph",&_f_mean_hit_ph,"_f_mean_hit_ph/F");
    fDataTree->Branch("_f_mean_hitph_U",&_f_mean_hitph_U,"_f_mean_hitph_U/F");
    fDataTree->Branch("_f_mean_hitph_V",&_f_mean_hitph_V,"_f_mean_hitph_V/F");
    fDataTree->Branch("_f_mean_hitph_Y",&_f_mean_hitph_Y,"_f_mean_hitph_Y/F");
    fDataTree->Branch("_f_mean_hit_charge",&_f_mean_hit_charge,"_f_mean_hit_charge/F");
    fDataTree->Branch("_f_mean_hitcharge_U",&_f_mean_hitcharge_U,"_f_mean_hitcharge_U/F");
    fDataTree->Branch("_f_mean_hitcharge_V",&_f_mean_hitcharge_V,"_f_mean_hitcharge_V/F");
    fDataTree->Branch("_f_mean_hitcharge_Y",&_f_mean_hitcharge_Y,"_f_mean_hitcharge_Y/F");
    fDataTree->Branch("_f_mean_nflashTot_opflashExt",&_f_mean_nflashTot_opflashExt,"_f_mean_nflashTot_opflashExt/F");
    fDataTree->Branch("_f_mean_nflashPE50_opflashExt",&_f_mean_nflashPE50_opflashExt,"_f_mean_nflashPE50_opflashExt/F");
    fDataTree->Branch("_f_mean_nflashPE20_opflashExt",&_f_mean_nflashPE20_opflashExt,"_f_mean_nflashPE20_opflashExt/F");
    fDataTree->Branch("_f_mean_nflashPE0_20_opflashExt",&_f_mean_nflashPE0_20_opflashExt,"_f_mean_nflashPE0_20_opflashExt/F");
    fDataTree->Branch("_f_mean_nflashTot_opflashInt",&_f_mean_nflashTot_opflashInt,"_f_mean_nflashTot_opflashInt/F");
    fDataTree->Branch("_f_mean_nflashPE50_opflashInt",&_f_mean_nflashPE50_opflashInt,"_f_mean_nflashPE50_opflashInt/F");
    fDataTree->Branch("_f_mean_nflashPE20_opflashInt",&_f_mean_nflashPE20_opflashInt,"_f_mean_nflashPE20_opflashInt/F");
    fDataTree->Branch("_f_mean_nflashPE0_20_opflashInt",&_f_mean_nflashPE0_20_opflashInt,"_f_mean_nflashPE0_20_opflashInt/F");
    fDataTree->Branch("_f_mean_flashycenter_opflashExt",&_f_mean_flashycenter_opflashExt,"_f_mean_flashycenter_opflashExt/F");
    fDataTree->Branch("_f_mean_flashycenterPE50_opflashExt",&_f_mean_flashycenterPE50_opflashExt,"_f_mean_flashycenterPE50_opflashExt/F");
    fDataTree->Branch("_f_mean_flashycenterPE20_opflashExt",&_f_mean_flashycenterPE20_opflashExt,"_f_mean_flashycenterPE20_opflashExt/F");
    //fDataTree->Branch("_f_mean_flashycenterPE0_20_opflashExt",&_f_mean_flashycenterPE0_20_opflashExt,"_f_mean_flashycenterPE0_20_opflashExt/F");
    fDataTree->Branch("_f_mean_flashzcenter_opflashExt",&_f_mean_flashzcenter_opflashExt,"_f_mean_flashzcenter_opflashExt/F");
    fDataTree->Branch("_f_mean_flashzcenterPE50_opflashExt",&_f_mean_flashzcenterPE50_opflashExt,"_f_mean_flashzcenterPE50_opflashExt/F");
    fDataTree->Branch("_f_mean_flashzcenterPE20_opflashExt",&_f_mean_flashzcenterPE20_opflashExt,"_f_mean_flashzcenterPE20_opflashExt/F");
    //fDataTree->Branch("_f_mean_flashzcenterPE0_20_opflashExt",&_f_mean_flashzcenterPE0_20_opflashExt,"_f_mean_flashzcenterPE0_20_opflashExt/F");
    fDataTree->Branch("_f_mean_flashycenter_opflashInt",&_f_mean_flashycenter_opflashInt,"_f_mean_flashycenter_opflashInt/F");
    fDataTree->Branch("_f_mean_flashycenterPE50_opflashInt",&_f_mean_flashycenterPE50_opflashInt,"_f_mean_flashycenterPE50_opflashInt/F");
    fDataTree->Branch("_f_mean_flashycenterPE20_opflashInt",&_f_mean_flashycenterPE20_opflashInt,"_f_mean_flashycenterPE20_opflashInt/F");
    //fDataTree->Branch("_f_mean_flashycenterPE0_20_opflashInt",&_f_mean_flashycenterPE0_20_opflashInt,"_f_mean_flashycenterPE0_20_opflashInt/F");
    fDataTree->Branch("_f_mean_flashzcenter_opflashInt",&_f_mean_flashzcenter_opflashInt,"_f_mean_flashzcenter_opflashInt/F");
    fDataTree->Branch("_f_mean_flashzcenterPE50_opflashInt",&_f_mean_flashzcenterPE50_opflashInt,"_f_mean_flashzcenterPE50_opflashInt/F");
    fDataTree->Branch("_f_mean_flashzcenterPE20_opflashInt",&_f_mean_flashzcenterPE20_opflashInt,"_f_mean_flashzcenterPE20_opflashInt/F");
    //fDataTree->Branch("_f_mean_flashzcenterPE0_20_opflashInt",&_f_mean_flashzcenterPE0_20_opflashInt,"_f_mean_flashzcenterPE0_20_opflashInt/F");
    fDataTree->Branch("_f_mean_flashPE_opflashExt",&_f_mean_flashPE_opflashExt,"_f_mean_flashPE_opflashExt/F");
    fDataTree->Branch("_f_mean_flashPE_opflashInt",&_f_mean_flashPE_opflashInt,"_f_mean_flashPE_opflashInt/F");
    fDataTree->Branch("_f_mean_nvrtx_pmtrack",&_f_mean_nvrtx_pmtrack,"_f_mean_nvrtx_pmtrack/F");
    fDataTree->Branch("_f_mean_nvrtx_pandora",&_f_mean_nvrtx_pandora,"_f_mean_nvrtx_pandora/F");
    fDataTree->Branch("_f_mean_npfps_pmtrack",&_f_mean_npfps_pmtrack,"_f_mean_npfps_pmtrack/F");
    fDataTree->Branch("_f_mean_npfps_pandora",&_f_mean_npfps_pandora,"_f_mean_npfps_pandora/F");
    fDataTree->Branch("_f_mean_trackpos_beginx_pmtrack",&_f_mean_trackpos_beginx_pmtrack,"_f_mean_trackpos_beginx_pmtrack/F");
    fDataTree->Branch("_f_mean_trackpos_beginy_pmtrack",&_f_mean_trackpos_beginy_pmtrack,"_f_mean_trackpos_beginy_pmtrack/F");
    fDataTree->Branch("_f_mean_trackpos_beginz_pmtrack",&_f_mean_trackpos_beginz_pmtrack,"_f_mean_trackpos_beginz_pmtrack/F");
    fDataTree->Branch("_f_mean_trackpos_beginx_pandoraTrack",&_f_mean_trackpos_beginx_pandoraTrack,"_f_mean_trackpos_beginx_pandoraTrack/F");
    fDataTree->Branch("_f_mean_trackpos_beginy_pandoraTrack",&_f_mean_trackpos_beginy_pandoraTrack,"_f_mean_trackpos_beginy_pandoraTrack/F");
    fDataTree->Branch("_f_mean_trackpos_beginz_pandoraTrack",&_f_mean_trackpos_beginz_pandoraTrack,"_f_mean_trackpos_beginz_pandoraTrack/F");
    fDataTree->Branch("_f_mean_trackpos_endx_pmtrack",&_f_mean_trackpos_endx_pmtrack,"_f_mean_trackpos_endx_pmtrack/F");
    fDataTree->Branch("_f_mean_trackpos_endy_pmtrack",&_f_mean_trackpos_endy_pmtrack,"_f_mean_trackpos_endy_pmtrack/F");
    fDataTree->Branch("_f_mean_trackpos_endz_pmtrack",&_f_mean_trackpos_endz_pmtrack,"_f_mean_trackpos_endz_pmtrack/F");
    fDataTree->Branch("_f_mean_trackpos_endx_pandoraTrack",&_f_mean_trackpos_endx_pandoraTrack,"_f_mean_trackpos_endx_pandoraTrack/F");
    fDataTree->Branch("_f_mean_trackpos_endy_pandoraTrack",&_f_mean_trackpos_endy_pandoraTrack,"_f_mean_trackpos_endy_pandoraTrack/F");
    fDataTree->Branch("_f_mean_trackpos_endz_pandoraTrack",&_f_mean_trackpos_endz_pandoraTrack,"_f_mean_trackpos_endz_pandoraTrack/F");
    fDataTree->Branch("_f_mean_Intflash_ywidth",&_f_mean_Intflash_ywidth,"_f_mean_Intflash_ywidth/F");
    fDataTree->Branch("_f_mean_Intflash_zwidth",&_f_mean_Intflash_zwidth,"_f_mean_Intflash_zwidth/F");
    fDataTree->Branch("_f_mean_Extflash_ywidth",&_f_mean_Extflash_ywidth,"_f_mean_Extflash_ywidth/F");
    fDataTree->Branch("_f_mean_Extflash_zwidth",&_f_mean_Extflash_zwidth,"_f_mean_Extflash_zwidth/F");

    fDataTree->Branch("_f_rms_ntrack_pmtrack",&_f_rms_ntrack_pmtrack,"_f_rms_ntrack_pmtrack/F");
    fDataTree->Branch("_f_rms_ntrack_pandoraTrack",&_f_rms_ntrack_pandoraTrack,"_f_rms_ntrack_pandoraTrack/F");
    fDataTree->Branch("_f_rms_trklen_pmtrack",&_f_rms_trklen_pmtrack,"_f_rms_trklen_pmtrack/F");
    fDataTree->Branch("_f_rms_trklen_pandoraTrack",&_f_rms_trklen_pandoraTrack,"_f_rms_trklen_pandoraTrack/F");
    fDataTree->Branch("_f_rms_nshwr_pandoraShower",&_f_rms_nshwr_pandoraShower,"_f_rms_nshwr_pandoraShower/F");
    fDataTree->Branch("_f_rms_shwrlen_pandoraShower",&_f_rms_shwrlen_pandoraShower,"_f_rms_shwrlen_pandoraShower/F");
    fDataTree->Branch("_f_rms_nhit_tot",&_f_rms_nhit_tot,"_f_rms_nhit_tot/F");
    fDataTree->Branch("_f_rms_nhit_U",&_f_rms_nhit_U,"_f_rms_nhit_U/F");
    fDataTree->Branch("_f_rms_nhit_V",&_f_rms_nhit_V,"_f_rms_nhit_V/F");
    fDataTree->Branch("_f_rms_nhit_Y",&_f_rms_nhit_Y,"_f_rms_nhit_Y/F");
    fDataTree->Branch("_f_rms_hit_ph",&_f_rms_hit_ph,"_f_rms_hit_ph/F");
    fDataTree->Branch("_f_rms_hitph_U",&_f_rms_hitph_U,"_f_rms_hitph_U/F");
    fDataTree->Branch("_f_rms_hitph_V",&_f_rms_hitph_V,"_f_rms_hitph_V/F");
    fDataTree->Branch("_f_rms_hitph_Y",&_f_rms_hitph_Y,"_f_rms_hitph_Y/F");
    fDataTree->Branch("_f_rms_hit_charge",&_f_rms_hit_charge,"_f_rms_hit_charge/F");
    fDataTree->Branch("_f_rms_hitcharge_U",&_f_rms_hitcharge_U,"_f_rms_hitcharge_U/F");
    fDataTree->Branch("_f_rms_hitcharge_V",&_f_rms_hitcharge_V,"_f_rms_hitcharge_V/F");
    fDataTree->Branch("_f_rms_hitcharge_Y",&_f_rms_hitcharge_Y,"_f_rms_hitcharge_Y/F");
    fDataTree->Branch("_f_rms_nflashTot_opflashExt",&_f_rms_nflashTot_opflashExt,"_f_rms_nflashTot_opflashExt/F");
    fDataTree->Branch("_f_rms_nflashPE50_opflashExt",&_f_rms_nflashPE50_opflashExt,"_f_rms_nflashPE50_opflashExt/F");
    fDataTree->Branch("_f_rms_nflashPE20_opflashExt",&_f_rms_nflashPE20_opflashExt,"_f_rms_nflashPE20_opflashExt/F");
    fDataTree->Branch("_f_rms_nflashPE0_20_opflashExt",&_f_rms_nflashPE0_20_opflashExt,"_f_rms_nflashPE0_20_opflashExt/F");
    fDataTree->Branch("_f_rms_nflashTot_opflashInt",&_f_rms_nflashTot_opflashInt,"_f_rms_nflashTot_opflashInt/F");
    fDataTree->Branch("_f_rms_nflashPE50_opflashInt",&_f_rms_nflashPE50_opflashInt,"_f_rms_nflashPE50_opflashInt/F");
    fDataTree->Branch("_f_rms_nflashPE20_opflashInt",&_f_rms_nflashPE20_opflashInt,"_f_rms_nflashPE20_opflashInt/F");
    fDataTree->Branch("_f_rms_nflashPE0_20_opflashInt",&_f_rms_nflashPE0_20_opflashInt,"_f_rms_nflashPE0_20_opflashInt/F");
    fDataTree->Branch("_f_rms_flashycenter_opflashExt",&_f_rms_flashycenter_opflashExt,"_f_rms_flashycenter_opflashExt/F");
    fDataTree->Branch("_f_rms_flashycenterPE50_opflashExt",&_f_rms_flashycenterPE50_opflashExt,"_f_rms_flashycenterPE50_opflashExt/F");
    fDataTree->Branch("_f_rms_flashycenterPE20_opflashExt",&_f_rms_flashycenterPE20_opflashExt,"_f_rms_flashycenterPE20_opflashExt/F");
    //fDataTree->Branch("_f_rms_flashycenterPE0_20_opflashExt",&_f_rms_flashycenterPE0_20_opflashExt,"_f_rms_flashycenterPE0_20_opflashExt/F");
    fDataTree->Branch("_f_rms_flashzcenter_opflashExt",&_f_rms_flashzcenter_opflashExt,"_f_rms_flashzcenter_opflashExt/F");
    fDataTree->Branch("_f_rms_flashzcenterPE50_opflashExt",&_f_rms_flashzcenterPE50_opflashExt,"_f_rms_flashzcenterPE50_opflashExt/F");
    fDataTree->Branch("_f_rms_flashzcenterPE20_opflashExt",&_f_rms_flashzcenterPE20_opflashExt,"_f_rms_flashzcenterPE20_opflashExt/F");
    //fDataTree->Branch("_f_rms_flashzcenterPE0_20_opflashExt",&_f_rms_flashzcenterPE0_20_opflashExt,"_f_rms_flashzcenterPE0_20_opflashExt/F");
    fDataTree->Branch("_f_rms_flashycenter_opflashInt",&_f_rms_flashycenter_opflashInt,"_f_rms_flashycenter_opflashInt/F");
    fDataTree->Branch("_f_rms_flashycenterPE50_opflashInt",&_f_rms_flashycenterPE50_opflashInt,"_f_rms_flashycenterPE50_opflashInt/F");
    fDataTree->Branch("_f_rms_flashycenterPE20_opflashInt",&_f_rms_flashycenterPE20_opflashInt,"_f_rms_flashycenterPE20_opflashInt/F");
    //fDataTree->Branch("_f_rms_flashycenterPE0_20_opflashInt",&_f_rms_flashycenterPE0_20_opflashInt,"_f_rms_flashycenterPE0_20_opflashInt/F");
    fDataTree->Branch("_f_rms_flashzcenter_opflashInt",&_f_rms_flashzcenter_opflashInt,"_f_rms_flashzcenter_opflashInt/F");
    fDataTree->Branch("_f_rms_flashzcenterPE50_opflashInt",&_f_rms_flashzcenterPE50_opflashInt,"_f_rms_flashzcenterPE50_opflashInt/F");
    fDataTree->Branch("_f_rms_flashzcenterPE20_opflashInt",&_f_rms_flashzcenterPE20_opflashInt,"_f_rms_flashzcenterPE20_opflashInt/F");
    //fDataTree->Branch("_f_rms_flashzcenterPE0_20_opflashInt",&_f_rms_flashzcenterPE0_20_opflashInt,"_f_rms_flashzcenterPE0_20_opflashInt/F");
    fDataTree->Branch("_f_rms_flashPE_opflashExt",&_f_rms_flashPE_opflashExt,"_f_rms_flashPE_opflashExt/F");
    fDataTree->Branch("_f_rms_flashPE_opflashInt",&_f_rms_flashPE_opflashInt,"_f_rms_flashPE_opflashInt/F");
    fDataTree->Branch("_f_rms_nvrtx_pmtrack",&_f_rms_nvrtx_pmtrack,"_f_rms_nvrtx_pmtrack/F");
    fDataTree->Branch("_f_rms_nvrtx_pandora",&_f_rms_nvrtx_pandora,"_f_rms_nvrtx_pandora/F");
    fDataTree->Branch("_f_rms_npfps_pmtrack",&_f_rms_npfps_pmtrack,"_f_rms_npfps_pmtrack/F");
    fDataTree->Branch("_f_rms_npfps_pandora",&_f_rms_npfps_pandora,"_f_rms_npfps_pandora/F");
    fDataTree->Branch("_f_rms_trackpos_beginx_pmtrack",&_f_rms_trackpos_beginx_pmtrack,"_f_rms_trackpos_beginx_pmtrack/F");
    fDataTree->Branch("_f_rms_trackpos_beginy_pmtrack",&_f_rms_trackpos_beginy_pmtrack,"_f_rms_trackpos_beginy_pmtrack/F");
    fDataTree->Branch("_f_rms_trackpos_beginz_pmtrack",&_f_rms_trackpos_beginz_pmtrack,"_f_rms_trackpos_beginz_pmtrack/F");
    fDataTree->Branch("_f_rms_trackpos_beginx_pandoraTrack",&_f_rms_trackpos_beginx_pandoraTrack,"_f_rms_trackpos_beginx_pandoraTrack/F");
    fDataTree->Branch("_f_rms_trackpos_beginy_pandoraTrack",&_f_rms_trackpos_beginy_pandoraTrack,"_f_rms_trackpos_beginy_pandoraTrack/F");
    fDataTree->Branch("_f_rms_trackpos_beginz_pandoraTrack",&_f_rms_trackpos_beginz_pandoraTrack,"_f_rms_trackpos_beginz_pandoraTrack/F");
    fDataTree->Branch("_f_rms_trackpos_endx_pmtrack",&_f_rms_trackpos_endx_pmtrack,"_f_rms_trackpos_endx_pmtrack/F");
    fDataTree->Branch("_f_rms_trackpos_endy_pmtrack",&_f_rms_trackpos_endy_pmtrack,"_f_rms_trackpos_endy_pmtrack/F");
    fDataTree->Branch("_f_rms_trackpos_endz_pmtrack",&_f_rms_trackpos_endz_pmtrack,"_f_rms_trackpos_endz_pmtrack/F");
    fDataTree->Branch("_f_rms_trackpos_endx_pandoraTrack",&_f_rms_trackpos_endx_pandoraTrack,"_f_rms_trackpos_endx_pandoraTrack/F");
    fDataTree->Branch("_f_rms_trackpos_endy_pandoraTrack",&_f_rms_trackpos_endy_pandoraTrack,"_f_rms_trackpos_endy_pandoraTrack/F");
    fDataTree->Branch("_f_rms_trackpos_endz_pandoraTrack",&_f_rms_trackpos_endz_pandoraTrack,"_f_rms_trackpos_endz_pandoraTrack/F");
    fDataTree->Branch("_f_rms_Intflash_ywidth",&_f_rms_Intflash_ywidth,"_f_rms_Intflash_ywidth/F");
    fDataTree->Branch("_f_rms_Intflash_zwidth",&_f_rms_Intflash_zwidth,"_f_rms_Intflash_zwidth/F");
    fDataTree->Branch("_f_rms_Extflash_ywidth",&_f_rms_Extflash_ywidth,"_f_rms_Extflash_ywidth/F");
    fDataTree->Branch("_f_rms_Extflash_zwidth",&_f_rms_Extflash_zwidth,"_f_rms_Extflash_zwidth/F");

   }

   //-----------------------------------------------------------------------
   void StabilityDet::endJob()
  {
  for(int i=0;i<n;i++)
  {
    if(Nentries[i]!=0 && Nrun[i]!=0)
    {
    _frun =  Nrun[i]/Nentries[i];
    _fnumevent = Nevts[i];

    _f_mean_ntrack_pmtrack               = N_ntrack_pmtrack[i]/Nentries[i];
    _f_rms_ntrack_pmtrack                = N_rms_ntrack_pmtrack[i]/Nentries[i];
    _f_mean_ntrack_pandoraTrack          = N_ntrack_pandoraTrack[i]/Nentries[i];
    _f_rms_ntrack_pandoraTrack           = N_rms_ntrack_pandoraTrack[i]/Nentries[i];
    _f_mean_trklen_pmtrack	             = N_trklen_pmtrack[i]/Nentries[i];
    _f_rms_trklen_pmtrack	               = N_rms_trklen_pmtrack[i]/Nentries[i];
    _f_mean_trklen_pandoraTrack          = N_trklen_pandoraTrack[i]/Nentries[i];
    _f_rms_trklen_pandoraTrack           = N_rms_trklen_pandoraTrack[i]/Nentries[i];
    _f_mean_nshwr_pandoraShower          = N_nshwr_pandoraShower[i]/Nentries[i];
    _f_rms_nshwr_pandoraShower           = N_rms_nshwr_pandoraShower[i]/Nentries[i];
    _f_mean_shwrlen_pandoraShower        = N_shwrlen_pandoraShower[i]/Nentries[i];
    _f_rms_shwrlen_pandoraShower         = N_rms_shwrlen_pandoraShower[i]/Nentries[i];
    _f_mean_nhit_tot                     = N_nhit_tot[i]/Nentries[i];
    _f_rms_nhit_tot                      = N_rms_nhit_tot[i]/Nentries[i];
    _f_mean_nhit_U                       = N_nhit_U[i]/Nentries[i];
    _f_rms_nhit_U                        = N_rms_nhit_U[i]/Nentries[i];
    _f_mean_nhit_V                       = N_nhit_V[i]/Nentries[i];
    _f_rms_nhit_V                        = N_rms_nhit_V[i]/Nentries[i];
    _f_mean_nhit_Y                       = N_nhit_Y[i]/Nentries[i];
    _f_rms_nhit_Y                        = N_rms_nhit_Y[i]/Nentries[i];
    _f_mean_hit_ph                       = N_hit_ph[i]/Nentries[i];
    _f_rms_hit_ph                        = N_rms_hit_ph[i]/Nentries[i];
    _f_mean_hitph_U                      = N_hitph_U[i]/Nentries[i];
    _f_rms_hitph_U                       = N_rms_hitph_U[i]/Nentries[i];
    _f_mean_hitph_V                      = N_hitph_V[i]/Nentries[i];
    _f_rms_hitph_V                       = N_rms_hitph_V[i]/Nentries[i];
    _f_mean_hitph_Y                      = N_hitph_Y[i]/Nentries[i];
    _f_rms_hitph_Y                       = N_rms_hitph_Y[i]/Nentries[i];
    _f_mean_hit_charge                   = N_hit_charge[i]/Nentries[i];
    _f_rms_hit_charge                    = N_rms_hit_charge[i]/Nentries[i];
    _f_mean_hitcharge_U                  = N_hitcharge_U[i]/Nentries[i];
    _f_rms_hitcharge_U                   = N_rms_hitcharge_U[i]/Nentries[i];
    _f_mean_hitcharge_V                  = N_hitcharge_V[i]/Nentries[i];
    _f_rms_hitcharge_V                   = N_rms_hitcharge_V[i]/Nentries[i];
    _f_mean_hitcharge_Y                  = N_hitcharge_Y[i]/Nentries[i];
    _f_rms_hitcharge_Y                   = N_rms_hitcharge_Y[i]/Nentries[i];
    _f_mean_nflashTot_opflashExt         = N_nflashTot_opflashExt[i]/Nentries[i];
    _f_rms_nflashTot_opflashExt          = N_rms_nflashTot_opflashExt[i]/Nentries[i];
    _f_mean_nflashPE50_opflashExt        = N_nflashPE50_opflashExt[i]/Nentries[i];
    _f_rms_nflashPE50_opflashExt         = N_rms_nflashPE50_opflashExt[i]/Nentries[i];
    _f_mean_nflashPE20_opflashExt        = N_nflashPE20_opflashExt[i]/Nentries[i];
    _f_rms_nflashPE20_opflashExt         = N_rms_nflashPE20_opflashExt[i]/Nentries[i];
    _f_mean_nflashPE0_20_opflashExt      = N_nflashPE0_20_opflashExt[i]/Nentries[i];
    _f_rms_nflashPE0_20_opflashExt       = N_rms_nflashPE0_20_opflashExt[i]/Nentries[i];
    _f_mean_nflashTot_opflashInt         = N_nflashTot_opflashInt[i]/Nentries[i];
    _f_rms_nflashTot_opflashInt          = N_rms_nflashTot_opflashInt[i]/Nentries[i];
    _f_mean_nflashPE50_opflashInt        = N_nflashPE50_opflashInt[i]/Nentries[i];
    _f_rms_nflashPE50_opflashInt         = N_rms_nflashPE50_opflashInt[i]/Nentries[i];
    _f_mean_nflashPE20_opflashInt        = N_nflashPE20_opflashInt[i]/Nentries[i];
    _f_rms_nflashPE20_opflashInt         = N_rms_nflashPE20_opflashInt[i]/Nentries[i];
    _f_mean_nflashPE0_20_opflashInt      = N_nflashPE0_20_opflashInt[i]/Nentries[i];
    _f_rms_nflashPE0_20_opflashInt       = N_rms_nflashPE0_20_opflashInt[i]/Nentries[i];
    _f_mean_flashycenter_opflashInt      = N_flashycenter_opflashInt[i]/Nentries[i];
    _f_rms_flashycenter_opflashInt       = N_rms_flashycenter_opflashInt[i]/Nentries[i];
    _f_mean_flashycenterPE50_opflashInt  = N_flashycenterPE50_opflashInt[i]/Nentries[i];
    _f_rms_flashycenterPE50_opflashInt   = N_rms_flashycenterPE50_opflashInt[i]/Nentries[i];
    _f_mean_flashycenterPE20_opflashInt  = N_flashycenterPE20_opflashInt[i]/Nentries[i];
    _f_rms_flashycenterPE20_opflashInt   = N_rms_flashycenterPE20_opflashInt[i]/Nentries[i];
    //_f_mean_flashycenterPE0_20_opflashInt= N_flashycenterPE0_20_opflashInt[i]/Nentries[i];
    //_f_rms_flashycenterPE0_20_opflashInt = N_rms_flashycenterPE0_20_opflashInt[i]/Nentries[i];
    _f_mean_flashzcenter_opflashInt      = N_flashzcenter_opflashInt[i]/Nentries[i];
    _f_rms_flashzcenter_opflashInt       = N_rms_flashzcenter_opflashInt[i]/Nentries[i];
    _f_mean_flashzcenterPE50_opflashInt  = N_flashzcenterPE50_opflashInt[i]/Nentries[i];
    _f_rms_flashzcenterPE50_opflashInt   = N_rms_flashzcenterPE50_opflashInt[i]/Nentries[i];
    _f_mean_flashzcenterPE20_opflashInt  = N_flashzcenterPE20_opflashInt[i]/Nentries[i];
    _f_rms_flashzcenterPE20_opflashInt   = N_rms_flashzcenterPE20_opflashInt[i]/Nentries[i];
    //_f_mean_flashzcenterPE0_20_opflashInt= N_flashzcenterPE0_20_opflashInt[i]/Nentries[i];
    //_f_rms_flashzcenterPE0_20_opflashInt = N_rms_flashzcenterPE0_20_opflashInt[i]/Nentries[i];
    _f_mean_flashycenter_opflashExt      = N_flashycenter_opflashExt[i]/Nentries[i];
    _f_rms_flashycenter_opflashExt       = N_rms_flashycenter_opflashExt[i]/Nentries[i];
    _f_mean_flashycenterPE50_opflashExt  = N_flashycenterPE50_opflashExt[i]/Nentries[i];
    _f_rms_flashycenterPE50_opflashExt   = N_rms_flashycenterPE50_opflashExt[i]/Nentries[i];
    _f_mean_flashycenterPE20_opflashExt  = N_flashycenterPE20_opflashExt[i]/Nentries[i];
    _f_rms_flashycenterPE20_opflashExt   = N_rms_flashycenterPE20_opflashExt[i]/Nentries[i];
    //_f_mean_flashycenterPE0_20_opflashExt= N_flashycenterPE0_20_opflashExt[i]/Nentries[i];
    //_f_rms_flashycenterPE0_20_opflashExt = N_rms_flashycenterPE0_20_opflashExt[i]/Nentries[i];
    _f_mean_flashzcenter_opflashExt      = N_flashzcenter_opflashExt[i]/Nentries[i];
    _f_rms_flashzcenter_opflashExt       = N_rms_flashzcenter_opflashExt[i]/Nentries[i];
    _f_mean_flashzcenterPE50_opflashExt  = N_flashzcenterPE50_opflashExt[i]/Nentries[i];
    _f_rms_flashzcenterPE50_opflashExt   = N_rms_flashzcenterPE50_opflashExt[i]/Nentries[i];
    _f_mean_flashzcenterPE20_opflashExt  = N_flashzcenterPE20_opflashExt[i]/Nentries[i];
    _f_rms_flashzcenterPE20_opflashExt   = N_rms_flashzcenterPE20_opflashExt[i]/Nentries[i];
    //_f_mean_flashzcenterPE0_20_opflashExt= N_flashzcenterPE0_20_opflashExt[i]/Nentries[i];
    //_f_rms_flashzcenterPE0_20_opflashExt = N_rms_flashzcenterPE0_20_opflashExt[i]/Nentries[i];]
    _f_mean_flashPE_opflashExt           = N_flashPE_opflashExt[i]/Nentries[i];
    _f_rms_flashPE_opflashExt            = N_rms_flashPE_opflashExt[i]/Nentries[i];
    _f_mean_flashPE_opflashInt           = N_flashPE_opflashInt[i]/Nentries[i];
    _f_rms_flashPE_opflashInt            = N_rms_flashPE_opflashInt[i]/Nentries[i];
    _f_mean_nvrtx_pmtrack                = N_nvrtx_pmtrack[i]/Nentries[i];
    _f_rms_nvrtx_pmtrack                 = N_rms_nvrtx_pmtrack[i]/Nentries[i];
    _f_mean_nvrtx_pandora                = N_nvrtx_pandora[i]/Nentries[i];
    _f_rms_nvrtx_pandora                 = N_rms_nvrtx_pandora[i]/Nentries[i];
    _f_mean_npfps_pmtrack                = N_npfps_pmtrack[i]/Nentries[i];
    _f_rms_npfps_pmtrack                 = N_rms_npfps_pmtrack[i]/Nentries[i];
    _f_mean_npfps_pandora                = N_npfps_pandora[i]/Nentries[i];
    _f_rms_npfps_pandora                 = N_rms_npfps_pandora[i]/Nentries[i];

    _f_mean_trackpos_beginx_pmtrack         = N_trackpos_beginx_pmtrack[i]/Nentries[i];
    _f_mean_trackpos_beginy_pmtrack         = N_trackpos_beginy_pmtrack[i]/Nentries[i];
    _f_mean_trackpos_beginz_pmtrack         = N_trackpos_beginz_pmtrack[i]/Nentries[i];
    _f_mean_trackpos_beginx_pandoraTrack    = N_trackpos_beginx_pandoraTrack[i]/Nentries[i];
    _f_mean_trackpos_beginy_pandoraTrack    = N_trackpos_beginy_pandoraTrack[i]/Nentries[i];
    _f_mean_trackpos_beginz_pandoraTrack    = N_trackpos_beginz_pandoraTrack[i]/Nentries[i];
    _f_mean_trackpos_endx_pmtrack           = N_trackpos_endx_pmtrack[i]/Nentries[i];
    _f_mean_trackpos_endy_pmtrack           = N_trackpos_endy_pmtrack[i]/Nentries[i];
    _f_mean_trackpos_endz_pmtrack           = N_trackpos_endz_pmtrack[i]/Nentries[i];
    _f_mean_trackpos_endx_pandoraTrack      = N_trackpos_endx_pandoraTrack[i]/Nentries[i];
    _f_mean_trackpos_endy_pandoraTrack      = N_trackpos_endy_pandoraTrack[i]/Nentries[i];
    _f_mean_trackpos_endz_pandoraTrack      = N_trackpos_endz_pandoraTrack[i]/Nentries[i];
    _f_mean_Intflash_ywidth                 = N_Intflash_ywidth[i]/Nentries[i];
    _f_mean_Intflash_zwidth                 = N_Intflash_zwidth[i]/Nentries[i];
    _f_mean_Extflash_ywidth                 = N_Extflash_ywidth[i]/Nentries[i];
    _f_mean_Extflash_zwidth                 = N_Extflash_zwidth[i]/Nentries[i];
    _f_rms_trackpos_beginx_pmtrack          = N_rms_trackpos_beginx_pmtrack[i]/Nentries[i];
    _f_rms_trackpos_beginy_pmtrack          = N_rms_trackpos_beginy_pmtrack[i]/Nentries[i];
    _f_rms_trackpos_beginz_pmtrack          = N_rms_trackpos_beginz_pmtrack[i]/Nentries[i];
    _f_rms_trackpos_beginx_pandoraTrack     = N_rms_trackpos_beginx_pandoraTrack[i]/Nentries[i];
    _f_rms_trackpos_beginy_pandoraTrack     = N_rms_trackpos_beginy_pandoraTrack[i]/Nentries[i];
    _f_rms_trackpos_beginz_pandoraTrack     = N_rms_trackpos_beginz_pandoraTrack[i]/Nentries[i];
    _f_rms_trackpos_endx_pmtrack            = N_rms_trackpos_endx_pmtrack[i]/Nentries[i];
    _f_rms_trackpos_endy_pmtrack            = N_rms_trackpos_endy_pmtrack[i]/Nentries[i];
    _f_rms_trackpos_endz_pmtrack            = N_rms_trackpos_endz_pmtrack[i]/Nentries[i];
    _f_rms_trackpos_endx_pandoraTrack       = N_rms_trackpos_endx_pandoraTrack[i]/Nentries[i];
    _f_rms_trackpos_endy_pandoraTrack       = N_rms_trackpos_endy_pandoraTrack[i]/Nentries[i];
    _f_rms_trackpos_endz_pandoraTrack       = N_rms_trackpos_endz_pandoraTrack[i]/Nentries[i];
    _f_rms_Intflash_ywidth                  = N_rms_Intflash_ywidth[i]/Nentries[i];
    _f_rms_Intflash_zwidth                  = N_rms_Intflash_zwidth[i]/Nentries[i];
    _f_rms_Extflash_ywidth                  = N_rms_Extflash_ywidth[i]/Nentries[i];
    _f_rms_Extflash_zwidth                  = N_rms_Extflash_zwidth[i]/Nentries[i];

	fDataTree->Fill();

	}
      }

  }

   //-----------------------------------------------------------------------
   void StabilityDet::beginRun(const art::Run& run)
  {

  _run                  = new TH1F("_run","run number",10000,0,10000);
  _ntrack_pmtrack   = new TH1F("_ntrack_pmtrack","Number of tracks (pmtrack) per event",100,0,6000);
  _ntrack_pandoraTrack      = new TH1F("_ntrack_pandoraTrack","Number of tracks (pandoraTrack) per event",100,0,6000);
  _trklen_pmtrack  = new TH1F("_trklen_pmtrack","track length (pmtrack) per event",100,0,2000);
  _trklen_pandoraTrack     = new TH1F("_trklen_pandoraTrack","track length (pandoraTrack) per event",100,0,2000);
  _nshwr_pandoraShower  = new TH1F("_nshwr_pandoraShower","number of shower (pandoraShower) per event",100,0,6000);
  _shwrlen_pandoraShower = new TH1F("_shwrlen_pandoraShower","shower length (pandoraShower) per event",100,0,2000);
  _nhit_tot               = new TH1F("_nhit_tot","Number of V-plane hits per event ",100,0,1000000);
  _nhit_U                 = new TH1F("_nhit_U","Number of U-plane hits per event ",100,0,1000000);
  _nhit_V                 = new TH1F("_nhit_V","Number of V-plane hits per event ",100,0,1000000);
  _nhit_Y                 = new TH1F("_nhit_Y","Number of Y-plane hits per event ",100,0,1000000);
  _hit_ph               = new TH1F("_hit_ph","Number of hit ph per event ",100,0,30000);
  _hitph_U              = new TH1F("_hitph_U","Number of U-plane hit ph per event ",100,0,30000);
  _hitph_V              = new TH1F("_hitph_V","Number of V-plane hit ph per event ",100,0,30000);
  _hitph_Y              = new TH1F("_hitph_Y","Number of Y-plane hit ph per event ",100,0,30000);
  _hit_charge           = new TH1F("_hit_charge","Number of hit charge per event ",100,0,1600000);
  _hitcharge_U          = new TH1F("_hitcharge_U","Number of U-plane hit charge per event ",100,0,1600000);
  _hitcharge_V          = new TH1F("_hitcharge_V","Number of V-plane hit charge per event ",100,0,1600000);
  _hitcharge_Y          = new TH1F("_hitcharge_Y","Number of Y-plane hit charge per event ",100,0,1600000);
  _nflashTot_opflashExt     = new TH1F("_nflashTot_opflashExt","Number of optical sat flashes per event ",100,0,20000);
  _nflashPE50_opflashExt   = new TH1F("_nflashPE50_opflashExt","Number of > 50 optical sat flashes per event ",100,0,20000);
  _nflashPE20_opflashExt   = new TH1F("_nflashPE20_opflashExt","Number of > 20 optical sat flashes per event ",100,0,20000);
  _nflashPE0_20_opflashExt = new TH1F("_nflashPE0_20_opflashExt","Number of < 20 optical sat flashes per event ",100,0,20000);
  _nflashTot_opflashInt = new TH1F("_nflashTot_opflashInt","Number of opflashInt flashes per event ",100,0,1600000);
  _nflashPE50_opflashInt  = new TH1F("_nflashPE50_opflashInt","Number of > 50 opflashInt flashes per event ",100,0,1600000);
  _nflashPE20_opflashInt   = new TH1F("_nflashPE20_opflashInt","Number of > 20 opflashInt flashes per event ",100,0,1600000);
  _nflashPE0_20_opflashInt = new TH1F("_nflashPE0_20_opflashInt","Number of < 20 opflashInt flashes per event ",100,0,1600000);
  _flashycenter_opflashExt        = new TH1F("_flashycenter_opflashExt","y center of flashes per event ",100,0,1000);
  _flashycenterPE50_opflashExt      = new TH1F("_flashycenterPE50_opflashExt","y center of >50 flashes per event ",100,0,1000);
  _flashycenterPE20_opflashExt      = new TH1F("_flashycenterPE20_opflashExt","y center of >20 flashes per event ",100,0,1000);
  //_flash_ycenter0_20_opflashExt      = new TH1F("_flash_ycenter0_20_opflashExt","y center of <20 flashes per event ",100,0,1000);
  _flashzcenter_opflashExt        = new TH1F("_flashzcenter_opflashExt","z center of flashes per event",100,0,1500);
  _flashzcenterPE50_opflashExt     = new TH1F("_flashzcenterPE50_opflashExt","z center of >50 flashes per event",100,0,1500);
  _flashzcenterPE20_opflashExt     = new TH1F("_flashzcenterPE20_opflashExt","z center of >20 flashes per event",100,0,1500);
  //_flash_zcenter0_20_opflashExt      = new TH1F("_flash_zcenter0_20_opflashExt","z center of <20 flashes per event ",100,0,1000);
  _flashycenter_opflashInt        = new TH1F("_flashycenter_opflashInt","y center of flashes per event ",100,0,1000);
  _flashycenterPE50_opflashInt      = new TH1F("_flashycenterPE50_opflashInt","y center of >50 flashes per event ",100,0,1000);
  _flashycenterPE20_opflashInt      = new TH1F("_flashycenterPE20_opflashInt","y center of >20 flashes per event ",100,0,1000);
  //_flashycenter0_20_opflashInt      = new TH1F("_flashycenter0_20_opflashInt","y center of <20 flashes per event ",100,0,1000);
  _flashzcenter_opflashInt        = new TH1F("_flashzcenter_opflashInt","z center of flashes per event",100,0,1500);
  _flashzcenterPE50_opflashInt      = new TH1F("_flashzcenterPE50_opflashInt","z center of >50 flashes per event",100,0,1500);
  _flashzcenterPE20_opflashInt      = new TH1F("_flashzcenterPE20_opflashInt","z center of >20 flashes per event",100,0,1500);
  //_flashzcenter0_20_opflashInt      = new TH1F("_flashzcenter0_20_opflashInt","z center of <20 flashes per event ",100,0,1000);
  _flashPE_opflashExt             = new TH1F("_flashPE_opflashExt","flashes pe per event ",100,0,1000000);
  _flashPE_opflashInt             = new TH1F("_flashPE_opflashInt","flashes pe per event ",100,0,1000000);
  _nvrtx_pmtrack    = new TH1F("_nvrtx_pmtrack","number of vertex per event",100,0,2000);
  _nvrtx_pandora      = new TH1F("_nvrtx_pandora","number of vertex per event",100,0,2000);
  _npfps_pmtrack      = new TH1F("_nvrtx_pmtrack","number of vertex per event",100,0,2000);
  _npfps_pandora  = new TH1F("_nvrtx_pandora","number of vertex per event",100,0,2000);
  _trackpos_beginx_pmtrack = new TH1F("_trackpos_beginx_pmtrack","Track beginpos x (pmtrack) per event",100,0,1000);
  _trackpos_beginy_pmtrack = new TH1F("_trackpos_beginy_pmtrack","Track beginpos y (pmtrack) per event",100,0,1000);
  _trackpos_beginz_pmtrack = new TH1F("_trackpos_beginz_pmtrack","Track beginpos z (pmtrack) per event",100,0,1500);
  _trackpos_beginx_pandoraTrack = new TH1F("_trackpos_beginx_pandoraTrack","Track beginpos x (pandoraTrack) per event",100,0,1000);
  _trackpos_beginy_pandoraTrack = new TH1F("_trackpos_beginy_pandoraTrack","Track beginpos y (pandoraTrack) per event",100,0,1000);
  _trackpos_beginz_pandoraTrack = new TH1F("_trackpos_beginz_pandoraTrack","Track beginpos z (pandoraTrack) per event",100,0,1500);
  _trackpos_endx_pmtrack = new TH1F("_trackpos_endx_pmtrack","Track endpos x (pmtrack) per event",100,0,1000);
  _trackpos_endy_pmtrack = new TH1F("_trackpos_endy_pmtrack","Track endpos y (pmtrack) per event",100,0,1000);
  _trackpos_endz_pmtrack = new TH1F("_trackpos_endz_pmtrack","Track endpos z (pmtrack) per event",100,0,1500);
  _trackpos_endx_pandoraTrack = new TH1F("_trackpos_endx_pandoraTrack","Track endpos x (pandoraTrack) per event",100,0,1000);
  _trackpos_endy_pandoraTrack = new TH1F("_trackpos_endy_pandoraTrack","Track endpos y (pandoraTrack) per event",100,0,1000);
  _trackpos_endz_pandoraTrack = new TH1F("_trackpos_endz_pandoraTrack","Track endpos z (pandoraTrack) per event",100,0,1500);
  _Intflash_ywidth = new TH1F("_Intflash_ywidth","Intflash y width",100,0,1000);
  _Intflash_zwidth = new TH1F("_Intflash_zwidth","Intflash z width",100,0,1500);
  _Extflash_ywidth = new TH1F("_Extflash_ywidth","Extflash y width",100,0,1000);
  _Extflash_zwidth = new TH1F("_Extflash_zwidth","Extflash z width",100,0,1500);

  }

   //-----------------------------------------------------------------------
   void StabilityDet::endRun(const art::Run& run)
  {
        Run                    =_run->GetMean(1);
	Nevts[Run]             += numevent;
	numevent = 0; //resetting value
	Nentries[Run]            +=1;
	Nrun[Run]                +=Run;

  std::cout<<"\n"<<"\n"<<"run num: "<<Run<<" number of events: "<<Nevts[Run]<<"\n"<<"\n";

	N_ntrack_pmtrack[Run]                   +=_ntrack_pmtrack->GetMean(1);
  N_rms_ntrack_pmtrack[Run]               +=_ntrack_pmtrack->GetRMS(1);
  N_ntrack_pandoraTrack[Run]              +=_ntrack_pandoraTrack->GetMean(1);
  N_rms_ntrack_pandoraTrack[Run]          +=_ntrack_pandoraTrack->GetRMS(1);
  N_trklen_pmtrack[Run]                   +=_trklen_pmtrack->GetMean(1);
  N_rms_trklen_pmtrack[Run]               +=_trklen_pmtrack->GetRMS(1);
  N_trklen_pandoraTrack[Run]              +=_trklen_pandoraTrack->GetMean(1);
  N_rms_trklen_pandoraTrack[Run]          +=_trklen_pandoraTrack->GetRMS(1);
  N_nshwr_pandoraShower[Run]              +=_nshwr_pandoraShower->GetMean(1);
  N_rms_nshwr_pandoraShower[Run]          +=_nshwr_pandoraShower->GetRMS(1);
  N_shwrlen_pandoraShower[Run]            +=_shwrlen_pandoraShower->GetMean(1);
  N_rms_shwrlen_pandoraShower[Run]        +=_shwrlen_pandoraShower->GetRMS(1);
  N_nhit_tot[Run]                         +=_nhit_tot->GetMean(1);
  N_rms_nhit_tot[Run]                     +=_nhit_tot->GetRMS(1);
  N_nhit_U[Run]                           +=_nhit_U->GetMean(1);
  N_rms_nhit_U[Run]                       +=_nhit_U->GetRMS(1);
  N_nhit_V[Run]                           +=_nhit_V->GetMean(1);
  N_rms_nhit_V[Run]                       +=_nhit_V->GetRMS(1);
  N_nhit_Y[Run]                           +=_nhit_Y->GetMean(1);
  N_rms_nhit_Y[Run]                       +=_nhit_Y->GetRMS(1);
  N_hit_ph[Run]                        +=_hit_ph->GetMean(1);
  N_rms_hit_ph[Run]                    +=_hit_ph->GetRMS(1);
  N_hitph_U[Run]                          +=_hitph_U->GetMean(1);
  N_rms_hitph_U[Run]                      +=_hitph_U->GetRMS(1);
  N_hitph_V[Run]                          +=_hitph_V->GetMean(1);
  N_rms_hitph_V[Run]                      +=_hitph_V->GetRMS(1);
  N_hitph_Y[Run]                          +=_hitph_Y->GetMean(1);
  N_rms_hitph_Y[Run]                      +=_hitph_Y->GetRMS(1);
  N_hit_charge[Run]                    +=_hit_charge->GetMean(1);
  N_rms_hit_charge[Run]                +=_hit_charge->GetRMS(1);
  N_hitcharge_U[Run]                      +=_hitcharge_U->GetMean(1);
  N_rms_hitcharge_U[Run]                  +=_hitcharge_U->GetRMS(1);
  N_hitcharge_V[Run]                      +=_hitcharge_V->GetMean(1);
  N_rms_hitcharge_V[Run]                  +=_hitcharge_V->GetRMS(1);
  N_hitcharge_Y[Run]                      +=_hitcharge_Y->GetMean(1);
  N_rms_hitcharge_Y[Run]                  +=_hitcharge_Y->GetRMS(1);
  N_nflashTot_opflashExt[Run]             +=_nflashTot_opflashExt->GetMean(1);
  N_rms_nflashTot_opflashExt[Run]         +=_nflashTot_opflashExt->GetRMS(1);
  N_nflashPE50_opflashExt[Run]            +=_nflashPE50_opflashExt->GetMean(1);
  N_rms_nflashPE50_opflashExt[Run]        +=_nflashPE50_opflashExt->GetRMS(1);
  N_nflashPE20_opflashExt[Run]            +=_nflashPE20_opflashExt->GetMean(1);
  N_rms_nflashPE20_opflashExt[Run]        +=_nflashPE20_opflashExt->GetRMS(1);
  N_nflashPE0_20_opflashExt[Run]          +=_nflashPE0_20_opflashExt->GetMean(1);
  N_rms_nflashPE0_20_opflashExt[Run]      +=_nflashPE0_20_opflashExt->GetRMS(1);
  N_nflashTot_opflashInt[Run]                 +=_nflashTot_opflashInt->GetMean(1);
  N_rms_nflashTot_opflashInt[Run]         +=_nflashTot_opflashInt->GetRMS(1);
  N_nflashPE50_opflashInt[Run]               +=_nflashPE50_opflashInt->GetMean(1);
  N_rms_nflashPE50_opflashInt[Run]        +=_nflashPE50_opflashInt->GetRMS(1);
  N_nflashPE20_opflashInt[Run]               +=_nflashPE20_opflashInt->GetMean(1);
  N_rms_nflashPE20_opflashInt[Run]        +=_nflashPE20_opflashInt->GetRMS(1);
  N_nflashPE0_20_opflashInt[Run]             +=_nflashPE0_20_opflashInt->GetMean(1);
  N_rms_nflashPE0_20_opflashInt[Run]      +=_nflashPE0_20_opflashInt->GetRMS(1);
  N_flashycenter_opflashInt[Run]          +=_flashycenter_opflashInt->GetMean(1);
  N_rms_flashycenter_opflashInt[Run]      +=_flashycenter_opflashInt->GetRMS(1);
  N_flashycenterPE50_opflashInt[Run]      +=_flashycenterPE50_opflashInt->GetMean(1);
  N_rms_flashycenterPE50_opflashInt[Run]  +=_flashycenterPE50_opflashInt->GetRMS(1);
  N_flashycenterPE20_opflashInt[Run]      +=_flashycenterPE20_opflashInt->GetMean(1);
  N_rms_flashycenterPE20_opflashInt[Run]  +=_flashycenterPE20_opflashInt->GetRMS(1);
  //N_flashycenterPE0_20_opflashInt[Run]      +=_flashycenterPE0_20_opflashInt->GetMean(1);
  //N_rms_flashycenterPE0_20_opflashInt[Run]  +=_flashycenterPE0_20_opflashInt->GetRMS(1);
  N_flashzcenter_opflashInt[Run]          +=_flashzcenter_opflashInt->GetMean(1);
  N_rms_flashzcenter_opflashInt[Run]      +=_flashzcenter_opflashInt->GetRMS(1);
  N_flashzcenterPE50_opflashInt[Run]      +=_flashzcenterPE50_opflashInt->GetMean(1);
  N_rms_flashzcenterPE50_opflashInt[Run]  +=_flashzcenterPE50_opflashInt->GetRMS(1);
  N_flashzcenterPE20_opflashInt[Run]      +=_flashzcenterPE20_opflashInt->GetMean(1);
  N_rms_flashzcenterPE20_opflashInt[Run]  +=_flashzcenterPE20_opflashInt->GetRMS(1);
  //N_flashzcenterPE0_20_opflashInt[Run]      +=_flashzcenterPE0_20_opflashInt->GetMean(1);
  //N_rms_flashzcenterPE0_20_opflashInt[Run]  +=_flashzcenterPE0_20_opflashInt->GetRMS(1);
  N_flashycenter_opflashExt[Run]          +=_flashycenter_opflashExt->GetMean(1);
  N_rms_flashycenter_opflashExt[Run]      +=_flashycenter_opflashExt->GetRMS(1);
  N_flashycenterPE50_opflashExt[Run]      +=_flashycenterPE50_opflashExt->GetMean(1);
  N_rms_flashycenterPE50_opflashExt[Run]  +=_flashycenterPE50_opflashExt->GetRMS(1);
  N_flashycenterPE20_opflashExt[Run]      +=_flashycenterPE20_opflashExt->GetMean(1);
  N_rms_flashycenterPE20_opflashExt[Run]  +=_flashycenterPE20_opflashExt->GetRMS(1);
  //N_flashycenterPE0_20_opflashExt[Run]      +=_flashycenterPE0_20_opflashExt->GetMean(1);
  //N_rms_flashycenterPE0_20_opflashExt[Run]  +=_flashycenterPE0_20_opflashExt->GetRMS(1);
  N_flashzcenter_opflashExt[Run]          +=_flashzcenter_opflashExt->GetMean(1);
  N_rms_flashzcenter_opflashExt[Run]      +=_flashzcenter_opflashExt->GetRMS(1);
  N_flashzcenterPE50_opflashExt[Run]      +=_flashzcenterPE50_opflashExt->GetMean(1);
  N_rms_flashzcenterPE50_opflashExt[Run]  +=_flashzcenterPE50_opflashExt->GetRMS(1);
  N_flashzcenterPE20_opflashExt[Run]      +=_flashzcenterPE20_opflashExt->GetMean(1);
  N_rms_flashzcenterPE20_opflashExt[Run]  +=_flashzcenterPE20_opflashExt->GetRMS(1);
  //N_flashzcenterPE0_20_opflashExt[Run]      +=_flashzcenterPE0_20_opflashExt->GetMean(1);
  //N_rms_flashzcenterPE0_20_opflashExt[Run]  +=_flashzcenterPE0_20_opflashExt->GetRMS(1);
  N_flashPE_opflashExt[Run]               +=_flashPE_opflashExt->GetMean(1);
  N_rms_flashPE_opflashExt[Run]           +=_flashPE_opflashExt->GetRMS(1);
  N_flashPE_opflashInt[Run]               +=_flashPE_opflashInt->GetMean(1);
  N_rms_flashPE_opflashInt[Run]           +=_flashPE_opflashInt->GetRMS(1);
  N_nvrtx_pmtrack[Run]                    +=_nvrtx_pmtrack->GetMean(1);
  N_rms_nvrtx_pmtrack[Run]                +=_nvrtx_pmtrack->GetRMS(1);
  N_nvrtx_pandora[Run]                    +=_nvrtx_pandora->GetMean(1);
  N_rms_nvrtx_pandora[Run]                +=_nvrtx_pandora->GetRMS(1);
  N_npfps_pmtrack[Run]                    +=_npfps_pmtrack->GetMean(1);
  N_rms_npfps_pmtrack[Run]                +=_npfps_pmtrack->GetRMS(1);
  N_npfps_pandora[Run]                    +=_npfps_pandora->GetMean(1);
  N_rms_npfps_pandora[Run]                +=_npfps_pandora->GetRMS(1);

  N_trackpos_beginx_pmtrack[Run]            +=_trackpos_beginx_pmtrack->GetMean(1);
  N_trackpos_beginy_pmtrack[Run]            +=_trackpos_beginy_pmtrack->GetMean(1);
  N_trackpos_beginz_pmtrack[Run]            +=_trackpos_beginz_pmtrack->GetMean(1);
  N_trackpos_beginx_pandoraTrack[Run]       +=_trackpos_beginx_pandoraTrack->GetMean(1);
  N_trackpos_beginy_pandoraTrack[Run]       +=_trackpos_beginy_pandoraTrack->GetMean(1);
  N_trackpos_beginz_pandoraTrack[Run]       +=_trackpos_beginz_pandoraTrack->GetMean(1);
  N_trackpos_endx_pmtrack[Run]              +=_trackpos_endx_pmtrack->GetMean(1);
  N_trackpos_endy_pmtrack[Run]              +=_trackpos_endy_pmtrack->GetMean(1);
  N_trackpos_endz_pmtrack[Run]              +=_trackpos_endz_pmtrack->GetMean(1);
  N_trackpos_endx_pandoraTrack[Run]         +=_trackpos_endx_pandoraTrack->GetMean(1);
  N_trackpos_endy_pandoraTrack[Run]         +=_trackpos_endy_pandoraTrack->GetMean(1);
  N_trackpos_endz_pandoraTrack[Run]         +=_trackpos_endz_pandoraTrack->GetMean(1);
  N_Intflash_ywidth[Run]                    +=_Intflash_ywidth->GetMean(1);
  N_Intflash_zwidth[Run]                    +=_Intflash_zwidth->GetMean(1);
  N_Extflash_ywidth[Run]                    +=_Extflash_ywidth->GetMean(1);
  N_Extflash_zwidth[Run]                    +=_Extflash_zwidth->GetMean(1);
  N_rms_trackpos_beginx_pmtrack[Run]        +=_trackpos_beginx_pmtrack->GetRMS(1);
  N_rms_trackpos_beginy_pmtrack[Run]        +=_trackpos_beginy_pmtrack->GetRMS(1);
  N_rms_trackpos_beginz_pmtrack[Run]        +=_trackpos_beginz_pmtrack->GetRMS(1);
  N_rms_trackpos_beginx_pandoraTrack[Run]   +=_trackpos_beginx_pandoraTrack->GetRMS(1);
  N_rms_trackpos_beginy_pandoraTrack[Run]   +=_trackpos_beginy_pandoraTrack->GetRMS(1);
  N_rms_trackpos_beginz_pandoraTrack[Run]   +=_trackpos_beginz_pandoraTrack->GetRMS(1);
  N_rms_trackpos_endx_pmtrack[Run]          +=_trackpos_endx_pmtrack->GetRMS(1);
  N_rms_trackpos_endy_pmtrack[Run]          +=_trackpos_endy_pmtrack->GetRMS(1);
  N_rms_trackpos_endz_pmtrack[Run]          +=_trackpos_endz_pmtrack->GetRMS(1);
  N_rms_trackpos_endx_pandoraTrack[Run]     +=_trackpos_endx_pandoraTrack->GetRMS(1);
  N_rms_trackpos_endy_pandoraTrack[Run]     +=_trackpos_endy_pandoraTrack->GetRMS(1);
  N_rms_trackpos_endz_pandoraTrack[Run]     +=_trackpos_endz_pandoraTrack->GetRMS(1);
  N_rms_Intflash_ywidth[Run]                +=_Intflash_ywidth->GetRMS(1);
  N_rms_Intflash_zwidth[Run]                +=_Intflash_zwidth->GetRMS(1);
  N_rms_Extflash_ywidth[Run]                +=_Extflash_ywidth->GetRMS(1);
  N_rms_Extflash_zwidth[Run]                +=_Extflash_zwidth->GetRMS(1);

  }

    //-----------------------------------------------------------------------
   /*void StabilityDet::reconfigure(fhicl::ParameterSet const& pset)
   {f

    fHitsModuleLabel            = pset.get< std::string > ("HitsModuleLabel","gaushit");
    fpmtrackModuleLabel         = pset.get< std::string > ("pmtrackModuleLabel","pmtrack");
    fPanCosTrackModuleLabel     = pset.get< std::string > ("PanCosTrackModuleLabel","pandoraCosmic");
    fPanNuTrackModuleLabel      = pset.get< std::string > ("PanNuTrackModuleLabel","pandoraNu");
    fPanNuPMATrackModuleLabel   = pset.get< std::string > ("PanNuPMATrackModuleLabel","pandoraNuPMA");
    fpmtrackVrtxModuleLabel     = pset.get< std::string > ("pmtrackVrtxModuleLabel","pmtrack");
    fPanNuVrtxModuleLabel       = pset.get< std::string > ("PanNuVrtxModuleLabel","pandoraNu");
    fPanNuPMAVrtxModuleLabel    = pset.get< std::string > ("PanNuPMAVrtxModuleLabel","pandoraNuPMA");
    fPanCosVrtxModuleLabel      = pset.get< std::string > ("PanCosVrtxModuleLabel","pandoraCosmic");
    fOpFlashModuleLabel         = pset.get< std::string > ("OpFlashModuleLabel","opflash");
    fSimpFlashBeamModuleLabel   = pset.get< std::string > ("SimpFlashBeamModuleLabel","simpleFlashBeam");

    These are not necessary here.
  }*/
 //========================================================================

  // Length of reconstructed track, trajectory by trajectory.
  /*double StabilityDet::length(const recob::Track& track)
  {
    double result = 0.;
    TVector3 disp = track.LocationAtPoint(0);
    int n = track.NumberTrajectoryPoints();

    for(int i = 1; i < n; ++i)
    {
      const TVector3& pos = track.LocationAtPoint(i);
      disp -= pos;
      result += disp.Mag();
      disp = pos;
    }
    return result;
  }*/
 //========================================================================

   void StabilityDet::analyze(art::Event const& evt)
   {

    _run ->Fill(evt.run());

    numevent +=1;

   /////////////Track related quantities///////////////////


   // pmtrack tracks
   art::Handle< std::vector<recob::Track> > pmtrackCol;
   std::vector<art::Ptr<recob::Track> > pmtrklist;
   if(evt.getByLabel(fPmtrackModuleLabel,pmtrackCol)) art::fill_ptr_vector(pmtrklist, pmtrackCol);
   _ntrack_pmtrack->Fill(pmtrklist.size());

   std::cout<<"pmtracks: "<<pmtrklist.size()<<"\n";

   for(size_t i=0; i<pmtrklist.size();++i)
   {
     art::Ptr<recob::Track> ppmtrk(pmtrackCol, i);
     const recob::Track& pmtrk = *ppmtrk;

     _trklen_pmtrack -> Fill(pmtrk.Length());

     TVector3 end = pmtrk.End<TVector3>();
     TVector3 pos(pmtrk.LocationAtPoint(pmtrk.FirstValidPoint()).X(), pmtrk.LocationAtPoint(pmtrk.FirstValidPoint()).Y(), pmtrk.LocationAtPoint(pmtrk.FirstValidPoint()).Z());
     _trackpos_beginx_pmtrack -> Fill(pos.X());
     _trackpos_beginy_pmtrack -> Fill(pos.Y());
     _trackpos_beginz_pmtrack -> Fill(pos.Z());
     _trackpos_endx_pmtrack -> Fill(end.X());
     _trackpos_endy_pmtrack -> Fill(end.Y());
     _trackpos_endz_pmtrack -> Fill(end.Z());
   }


   // pandoraTrack tracks
   art::Handle< std::vector<recob::Track> > pantrackCol;
   std::vector<art::Ptr<recob::Track> > pantrklist;
   if(evt.getByLabel(fPandoraTrackModuleLabel,pantrackCol)) art::fill_ptr_vector(pantrklist, pantrackCol);
   _ntrack_pandoraTrack->Fill(pantrklist.size());

   std::cout<<"pantracks: "<<pantrklist.size()<<"\n";

   for(size_t i=0; i<pantrklist.size();++i)
   {
     art::Ptr<recob::Track> ppantrk(pantrackCol, i);
     const recob::Track& pantrk = *ppantrk;

     _trklen_pandoraTrack -> Fill(pantrk.Length());

     TVector3 end = pantrk.End<TVector3>();
     TVector3 pos(pantrk.LocationAtPoint(pantrk.FirstValidPoint()).X(), pantrk.LocationAtPoint(pantrk.FirstValidPoint()).Y(), pantrk.LocationAtPoint(pantrk.FirstValidPoint()).Z());
     _trackpos_beginx_pandoraTrack -> Fill(pos.X());
     _trackpos_beginy_pandoraTrack -> Fill(pos.Y());
     _trackpos_beginz_pandoraTrack -> Fill(pos.Z());
     _trackpos_endx_pandoraTrack -> Fill(end.X());
     _trackpos_endy_pandoraTrack -> Fill(end.Y());
     _trackpos_endz_pandoraTrack -> Fill(end.Z());
   }


   // pandoraShower showers
   art::Handle< std::vector<recob::Shower> > panshwrCol;
   std::vector<art::Ptr<recob::Shower> > panshwrlist;
   if(evt.getByLabel(fPandoraShowerModuleLabel,panshwrCol)) art::fill_ptr_vector(panshwrlist, panshwrCol);
   _nshwr_pandoraShower->Fill(panshwrlist.size());

   std::cout<<"panshowers: "<<panshwrlist.size()<<"\n";

   for(size_t i=0; i<panshwrlist.size();++i)
   {
     art::Ptr<recob::Shower> ppanshwr(panshwrCol, i);
     const recob::Shower& panshwr = *ppanshwr;

     _shwrlen_pandoraShower -> Fill(panshwr.Length());
   }

   /////////////Vertices and PFPs///////////////////


   // pmtrack vertices
   art::Handle< std::vector<recob::Vertex> > pmvrtxCol;
   std::vector<art::Ptr<recob::Vertex> > pmvrtxlist;
   if(evt.getByLabel(fPmtrackVrtxModuleLabel,pmvrtxCol)) art::fill_ptr_vector(pmvrtxlist, pmvrtxCol);
   _nvrtx_pmtrack->Fill(pmvrtxlist.size());
   std::cout<<"pmvertices: "<<pmvrtxlist.size()<<"\n";


   // pandora vertices
   art::Handle< std::vector<recob::Vertex> > panvrtxCol;
   std::vector<art::Ptr<recob::Vertex> > panvrtxlist;
   if(evt.getByLabel(fPandoraVrtxModuleLabel,panvrtxCol)) art::fill_ptr_vector(panvrtxlist, panvrtxCol);
   _nvrtx_pandora->Fill(panvrtxlist.size());
   std::cout<<"panvertices: "<<panvrtxlist.size()<<"\n";


   // pmtrack PFPs
   art::Handle< std::vector<recob::PFParticle> > pmpfpsCol;
   std::vector<art::Ptr<recob::PFParticle> > pmpfpslist;
   if(evt.getByLabel(fPandoraPFPFModuleLabel,pmpfpsCol)) art::fill_ptr_vector(pmpfpslist, pmpfpsCol);
   _npfps_pmtrack->Fill(pmpfpslist.size());
   std::cout<<"pmpfps: "<<pmpfpslist.size()<<"\n";


   // pandora PFPs
   art::Handle< std::vector<recob::PFParticle> > panpfpsCol;
   std::vector<art::Ptr<recob::PFParticle> > panpfpslist;
   if(evt.getByLabel(fPmtrackVrtxModuleLabel,panpfpsCol)) art::fill_ptr_vector(panpfpslist, panpfpsCol);
   _npfps_pandora->Fill(panpfpslist.size());
   std::cout<<"panpfps: "<<panpfpslist.size()<<"\n";


   /////////////Hits and flashes related quantities///////////////////


   // linecluster hits
   art::Handle< std::vector<recob::Hit> > lineclhitsCol;
   std::vector<art::Ptr<recob::Hit> > lineclhitslist;
   if(evt.getByLabel(fHitsModuleLabel,lineclhitsCol)) art::fill_ptr_vector(lineclhitslist, lineclhitsCol);
   _nhit_tot->  Fill(lineclhitslist.size());

   std::cout<<"linecluster hits: "<<lineclhitslist.size()<<"\n";

   float  rlineclhitsU = 0, rlineclhitsV=0, rlineclhitsY=0;

   for(size_t i=0; i<lineclhitslist.size();++i)
   {
     art::Ptr<recob::Hit> plineclhits(lineclhitsCol, i);
     const recob::Hit& lineclhits = *plineclhits;

     _hit_ph -> Fill(lineclhits.PeakAmplitude());
     _hit_charge -> Fill(lineclhits.Integral());

     if(lineclhits.WireID().Plane==0)
     {
       rlineclhitsU++;
       _hitph_U -> Fill(lineclhits.PeakAmplitude());
       _hitcharge_U -> Fill(lineclhits.Integral());
     }

     if(lineclhits.WireID().Plane==1)
     {
       rlineclhitsV++;
       _hitph_V -> Fill(lineclhits.PeakAmplitude());
       _hitcharge_V -> Fill(lineclhits.Integral());
     }

     if(lineclhits.WireID().Plane==2)
     {
       rlineclhitsY++;
       _hitph_Y -> Fill(lineclhits.PeakAmplitude());
       _hitcharge_Y -> Fill(lineclhits.Integral());
     }
   }
   _nhit_U-> Fill(rlineclhitsU);
   _nhit_V-> Fill(rlineclhitsV);
   _nhit_Y-> Fill(rlineclhitsY);


   // opflashExternal flashes
   art::Handle< std::vector<recob::OpFlash> > opflashExtCol;
   std::vector<art::Ptr<recob::OpFlash> > opflashExtlist;
   if(evt.getByLabel(fOpflashExtModuleLabel,opflashExtCol)) art::fill_ptr_vector(opflashExtlist, opflashExtCol);
   _nflashTot_opflashExt->  Fill(opflashExtlist.size());
   std::cout<<"opflashExt flashes: "<<opflashExtlist.size()<<"\n";
   float ropflashExt50 = 0, ropflashExt20=0, ropflashExt0_20=0;
   for(size_t i=0; i<opflashExtlist.size();++i)
   {
     art::Ptr<recob::OpFlash> popflashExt(opflashExtCol, i);
     const recob::OpFlash& opflashExt = *popflashExt;

     _flashycenter_opflashExt -> Fill(opflashExt.YCenter());
     _flashzcenter_opflashExt -> Fill(opflashExt.ZCenter());
     _flashPE_opflashExt -> Fill(opflashExt.TotalPE());
     _Extflash_ywidth -> Fill(opflashExt.YWidth());
     _Extflash_zwidth -> Fill(opflashExt.ZWidth());

     if(opflashExt.TotalPE()>50)
     {
       ropflashExt50++;
       _flashycenterPE50_opflashExt -> Fill(opflashExt.YCenter());
       _flashzcenterPE50_opflashExt -> Fill(opflashExt.ZCenter());
     }

     if(opflashExt.TotalPE()>20)
     {
       ropflashExt20++;
       _flashycenterPE20_opflashExt -> Fill(opflashExt.YCenter());
       _flashzcenterPE20_opflashExt -> Fill(opflashExt.ZCenter());
     }

     if(opflashExt.TotalPE()<20)
     {
       ropflashExt0_20++;
       //_flash_ycenter0_20_opflashExt -> Fill(opflashExt.YCenter());
       //_flash_zcenter0_20_opflashExt -> Fill(opflashExt.ZCenter());
     }
   }
   _nflashPE50_opflashExt-> Fill(ropflashExt50);
   _nflashPE20_opflashExt-> Fill(ropflashExt20);
   _nflashPE0_20_opflashExt-> Fill(ropflashExt0_20);


   // opflashInternal flashes
   art::Handle< std::vector<recob::OpFlash> > opflashIntCol;
   std::vector<art::Ptr<recob::OpFlash> > opflashIntlist;
   if(evt.getByLabel(fOpflashIntModuleLabel,opflashIntCol)) art::fill_ptr_vector(opflashIntlist, opflashIntCol);
   _nflashTot_opflashInt->  Fill(opflashIntlist.size());
   std::cout<<"opflashInt flashes: "<<opflashIntlist.size()<<"\n";
   float ropflashInt50 = 0, ropflashInt20=0, ropflashInt0_20=0;
   for(size_t i=0; i<opflashIntlist.size();++i)
   {
     art::Ptr<recob::OpFlash> popflashInt(opflashIntCol, i);
     const recob::OpFlash& opflashInt = *popflashInt;

     _flashycenter_opflashInt -> Fill(opflashInt.YCenter());
     _flashzcenter_opflashInt -> Fill(opflashInt.ZCenter());
     _flashPE_opflashInt -> Fill(opflashInt.TotalPE());
     _Intflash_ywidth -> Fill(opflashInt.YWidth());
     _Intflash_zwidth -> Fill(opflashInt.ZWidth());

     if(opflashInt.TotalPE()>50)
     {
       ropflashInt50++;
       _flashycenterPE50_opflashInt -> Fill(opflashInt.YCenter());
       _flashzcenterPE50_opflashInt -> Fill(opflashInt.ZCenter());
     }

     if(opflashInt.TotalPE()>20)
     {
       ropflashInt20++;
       _flashycenterPE20_opflashInt -> Fill(opflashInt.YCenter());
       _flashzcenterPE20_opflashInt -> Fill(opflashInt.ZCenter());
     }

     if(opflashInt.TotalPE()<20)
     {
       ropflashInt0_20++;
       //_flashycenter0_20_opflashInt -> Fill(opflashInt.YCenter());
       //_flashzcenter0_20_opflashInt -> Fill(opflashInt.ZCenter());
     }
   }
   _nflashPE50_opflashInt-> Fill(ropflashInt50);
   _nflashPE20_opflashInt-> Fill(ropflashInt20);
   _nflashPE0_20_opflashInt-> Fill(ropflashInt0_20);

 return;
 } // end StabilityDet::analyze()

   DEFINE_ART_MODULE(StabilityDet)

} // namespace StabilityDet_module
