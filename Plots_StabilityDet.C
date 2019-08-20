#include <TH1.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TMath.h>
#include "TF1.h"
#include "TF2.h"
#include <stdio.h>
#include <stdlib.h>
#include "algorithm"
#include <iostream>
#include <TChain.h>
#include <TFile.h>
#include <fstream>
#include "TLegend.h"
#include "TStyle.h"
#include "TLine.h"
#include "TGraphErrors.h"
#include "TPad.h"

using namespace std;

void Plots_StabilityDet()
 {

//Extact Treedata
TChain *TreeData = new TChain("stabilitydet/fDataTree");
TreeData->Add("/Users/zhouyongshun/Desktop/Argonne/Module/StabilityDet/Plots_StabilityDet_V2.1/cosmic.root");
TChain *MCData = new TChain("stabilitydet/fDataTree");
MCData->Add("/Users/zhouyongshun/Desktop/Argonne/Module/StabilityDet/Plots_StabilityDet_V2.1/stabilitydet_MC.root");

float nentries = -999;

Int_t run_bin=4000;
Float_t run_low=5000,run_high=9000;

TH2F* mean_ntrack_pmtrack = new TH2F("mean_ntrack_pmtrack","# mean_ntrack_pmtrack vs run",run_bin,run_low,run_high,200,0.0,400);
TH2F* mean_ntrack_pandoraTrack = new TH2F("mean_ntrack_pandoraTrack","# mean_ntrack_pandoraTrack vs run",run_bin,run_low,run_high,200,0.0,400);
TH2F* mean_trklen_pmtrack = new TH2F("mean_trklen_pmtrack","# mean_trklen_pmtrack vs run",run_bin,run_low,run_high,200,0.0,200);
TH2F* mean_trklen_pandoraTrack = new TH2F("mean_trklen_pandoraTrack","# mean_trklen_pandoraTrack vs run",run_bin,run_low,run_high,200,0.0,200);
TH2F* mean_nshwr_pandoraShower = new TH2F("mean_nshwr_pandoraShower","# mean_nshwr_pandoraShower vs run",run_bin,run_low,run_high,450,0.0,900);
TH2F* mean_shwrlen_pandoraShower = new TH2F("mean_shwrlen_pandoraShower","# mean_shwrlen_pandoraShower vs run",run_bin,run_low,run_high,100,0.0,100);
TH2F* mean_nhit_tot = new TH2F("mean_nhit_tot","mean_nhit_tot vs run",run_bin,run_low,run_high,1000,0.0,200000);
TH2F* mean_nhit_U = new TH2F("mean_nhit_U","mean_nhit_U vs run",run_bin,run_low,run_high,1000,0.0,200000);
TH2F* mean_nhit_V = new TH2F("mean_nhit_V","mean_nhit_V vs run",run_bin,run_low,run_high,1000,0.0,200000);
TH2F* mean_nhit_Y = new TH2F("mean_nhit_Y","mean_nhit_Y vs run",run_bin,run_low,run_high,1000,0.0,200000);
TH2F* mean_hit_ph = new TH2F("mean_hit_ph","mean_hit_ph vs run",run_bin,run_low,run_high,80,0.0,80);
TH2F* mean_hitph_U = new TH2F("mean_hitph_U","mean_hitph_U vs run",run_bin,run_low,run_high,80,0.0,80);
TH2F* mean_hitph_V = new TH2F("mean_hitph_V","# mean_hitph_V vs run",run_bin,run_low,run_high,80,0.0,80);
TH2F* mean_hitph_Y = new TH2F("mean_hitph_Y","# mean_hitph_Y vs run",run_bin,run_low,run_high,80,0.0,80);
TH2F* mean_hit_charge = new TH2F("mean_hit_charge","# mean_hit_charge vs run",run_bin,run_low,run_high,200,0.0,600);
TH2F* mean_hitcharge_U = new TH2F("mean_hitcharge_U","# mean_hitcharge_U vs run",run_bin,run_low,run_high,200,0.0,600);
TH2F* mean_hitcharge_V = new TH2F("mean_hitcharge_V","# mean_hitcharge_V vs run",run_bin,run_low,run_high,200,0.0,600);
TH2F* mean_hitcharge_Y = new TH2F("mean_hitcharge_Y","# mean_hitcharge_Y vs run",run_bin,run_low,run_high,200,0.0,600);
TH2F* mean_nflashTot_opflashExt = new TH2F("mean_nflashTot_opflashExt","# mean_nflashTot_opflashExt vs run",run_bin,run_low,run_high,50,0.0,2);
TH2F* mean_nflashPE50_opflashExt = new TH2F("mean_nflashPE50_opflashExt","# mean_nflashPE50_opflashExt vs run",run_bin,run_low,run_high,50,0.0,2);
TH2F* mean_nflashPE20_opflashExt = new TH2F("mean_nflashPE20_opflashExt","# mean_nflashPE20_opflashExt vs run",run_bin,run_low,run_high,50,0.0,2);
TH2F* mean_nflashPE0_20_opflashExt = new TH2F("mean_nflashPE0_20_opflashExt","# mean_nflashPE0_20_opflashExt vs run",run_bin,run_low,run_high,50,0.0,2);
TH2F* mean_nflashTot_opflashInt = new TH2F("mean_nflashTot_opflashInt","# mean_nflashTot_opflashInt vs run",run_bin,run_low,run_high,200,0.0,200);
TH2F* mean_nflashPE50_opflashInt = new TH2F("mean_nflashPE50_opflashInt","# mean_nflashPE50_opflashInt vs run",run_bin,run_low,run_high,200,0.0,200);
TH2F* mean_nflashPE20_opflashInt = new TH2F("mean_nflashPE20_opflashInt","# mean_nflashPE20_opflashInt vs run",run_bin,run_low,run_high,200,0.0,200);
TH2F* mean_nflashPE0_20_opflashInt = new TH2F("mean_nflashPE0_20_opflashInt","# mean_nflashPE0_20_opflashInt vs run",run_bin,run_low,run_high,200,0.0,200);
TH2F* mean_flashycenter_opflashExt = new TH2F("mean_flashycenter_opflashExt","# mean_flashycenter_opflashExt vs run",run_bin,run_low,run_high,200,0.0,600);
TH2F* mean_flashycenterPE50_opflashExt = new TH2F("mean_flashycenterPE50_opflashExt","# mean_flashycenterPE50_opflashExt vs run",run_bin,run_low,run_high,200,0.0,600);
TH2F* mean_flashycenterPE20_opflashExt = new TH2F("mean_flashycenterPE20_opflashExt","# mean_flashycenterPE20_opflashExt vs run",run_bin,run_low,run_high,200,0.0,600);
TH2F* mean_flashzcenter_opflashExt = new TH2F("mean_flashzcenter_opflashExt","# mean_flashzcenter_opflashExt vs run",run_bin,run_low,run_high,200,0.0,600);
TH2F* mean_flashzcenterPE50_opflashExt = new TH2F("mean_flashzcenterPE50_opflashExt","# mean_flashzcenterPE50_opflashExt vs run",run_bin,run_low,run_high,200,0.0,600);
TH2F* mean_flashzcenterPE20_opflashExt = new TH2F("mean_flashzcenterPE20_opflashExt","# mean_flashzcenterPE20_opflashExt vs run",run_bin,run_low,run_high,200,0.0,600);
TH2F* mean_flashycenter_opflashInt = new TH2F("mean_flashycenter_opflashInt","# mean_flashycenter_opflashInt vs run",run_bin,run_low,run_high,200,0.0,600);
TH2F* mean_flashycenterPE50_opflashInt = new TH2F("mean_flashycenterPE50_opflashInt","# mean_flashycenterPE50_opflashInt vs run",run_bin,run_low,run_high,200,0.0,600);
TH2F* mean_flashycenterPE20_opflashInt = new TH2F("mean_flashycenterPE20_opflashInt","# mean_flashycenterPE20_opflashInt vs run",run_bin,run_low,run_high,200,0.0,600);
TH2F* mean_flashzcenter_opflashInt = new TH2F("mean_flashzcenter_opflashInt","# mean_flashzcenter_opflashInt vs run",run_bin,run_low,run_high,200,0.0,600);
TH2F* mean_flashzcenterPE50_opflashInt = new TH2F("mean_flashzcenterPE50_opflashInt","# mean_flashzcenterPE50_opflashInt vs run",run_bin,run_low,run_high,200,0.0,600);
TH2F* mean_flashzcenterPE20_opflashInt = new TH2F("mean_flashzcenterPE20_opflashInt","# mean_flashzcenterPE20_opflashInt vs run",run_bin,run_low,run_high,200,0.0,600);
TH2F* mean_flashPE_opflashExt = new TH2F("mean_flashPE_opflashExt","# mean_flashPE_opflashExt vs run",run_bin,run_low,run_high,1000,0.0,100000);
TH2F* mean_flashPE_opflashInt = new TH2F("mean_flashPE_opflashInt","# mean_flashPE_opflashInt vs run",run_bin,run_low,run_high,1000,0.0,20000);
TH2F* mean_nvrtx_pmtrack = new TH2F("mean_nvrtx_pmtrack","# mean_nvrtx_pmtrack vs run",run_bin,run_low,run_high,600,0.0,1200);
TH2F* mean_nvrtx_pandora = new TH2F("mean_nvrtx_pandora","# mean_nvrtx_pandora vs run",run_bin,run_low,run_high,600,0.0,1200);
TH2F* mean_npfps_pmtrack = new TH2F("mean_npfps_pmtrack","# mean_npfps_pmtrack vs run",run_bin,run_low,run_high,600,0.0,1200);
TH2F* mean_npfps_pandora = new TH2F("mean_npfps_pandora","# mean_npfps_pandora vs run",run_bin,run_low,run_high,600,0.0,1200);
TH2F* mean_trackpos_beginx_pmtrack = new TH2F("mean_trackpos_beginx_pmtrack","# mean_trackpos_beginx_pmtrack vs run",run_bin,run_low,run_high,200,0.0,600);
TH2F* mean_trackpos_beginy_pmtrack = new TH2F("mean_trackpos_beginy_pmtrack","# mean_trackpos_beginy_pmtrack vs run",run_bin,run_low,run_high,200,0.0,600);
TH2F* mean_trackpos_beginz_pmtrack = new TH2F("mean_trackpos_beginz_pmtrack","# mean_trackpos_beginz_pmtrack vs run",run_bin,run_low,run_high,200,0.0,600);
TH2F* mean_trackpos_beginx_pandoraTrack = new TH2F("mean_trackpos_beginx_pandoraTrack","# mean_trackpos_beginx_pandoraTrack vs run",run_bin,run_low,run_high,200,0.0,600);
TH2F* mean_trackpos_beginy_pandoraTrack = new TH2F("mean_trackpos_beginy_pandoraTrack","# mean_trackpos_beginy_pandoraTrack vs run",run_bin,run_low,run_high,200,0.0,600);
TH2F* mean_trackpos_beginz_pandoraTrack = new TH2F("mean_trackpos_beginz_pandoraTrack","# mean_trackpos_beginz_pandoraTrack vs run",run_bin,run_low,run_high,200,0.0,600);
TH2F* mean_trackpos_endx_pmtrack = new TH2F("mean_trackpos_endx_pmtrack","# mean_trackpos_endx_pmtrack vs run",run_bin,run_low,run_high,200,0.0,600);
TH2F* mean_trackpos_endy_pmtrack = new TH2F("mean_trackpos_endy_pmtrack","# mean_trackpos_endy_pmtrack vs run",run_bin,run_low,run_high,200,0.0,600);
TH2F* mean_trackpos_endz_pmtrack = new TH2F("mean_trackpos_endz_pmtrack","# mean_trackpos_endz_pmtrack vs run",run_bin,run_low,run_high,200,0.0,600);
TH2F* mean_trackpos_endx_pandoraTrack = new TH2F("mean_trackpos_endx_pandoraTrack","# mean_trackpos_endx_pandoraTrack vs run",run_bin,run_low,run_high,200,0.0,600);
TH2F* mean_trackpos_endy_pandoraTrack = new TH2F("mean_trackpos_endy_pandoraTrack","# mean_trackpos_endy_pandoraTrack vs run",run_bin,run_low,run_high,200,0.0,600);
TH2F* mean_trackpos_endz_pandoraTrack = new TH2F("mean_trackpos_endz_pandoraTrack","# mean_trackpos_endz_pandoraTrack vs run",run_bin,run_low,run_high,200,0.0,600);
TH2F* mean_Intflash_ywidth = new TH2F("mean_Intflash_ywidth","# mean_Intflash_ywidth vs run",run_bin,run_low,run_high,150,0.0,300);
TH2F* mean_Intflash_zwidth = new TH2F("mean_Intflash_zwidth","# mean_Intflash_zwidth vs run",run_bin,run_low,run_high,150,0.0,300);
TH2F* mean_Extflash_ywidth = new TH2F("mean_Extflash_ywidth","# mean_Extflash_ywidth vs run",run_bin,run_low,run_high,150,0.0,300);
TH2F* mean_Extflash_zwidth = new TH2F("mean_Extflash_zwidth","# mean_Extflash_zwidth vs run",run_bin,run_low,run_high,150,0.0,300);

TH2F* rms_ntrack_pmtrack = new TH2F("rms_ntrack_pmtrack","# rms_ntrack_pmtrack vs run",run_bin,run_low,run_high,200,0.0,400);
TH2F* rms_ntrack_pandoraTrack = new TH2F("rms_ntrack_pandoraTrack","# rms_ntrack_pandoraTrack vs run",run_bin,run_low,run_high,200,0.0,400);
TH2F* rms_trklen_pmtrack = new TH2F("rms_trklen_pmtrack","# rms_trklen_pmtrack vs run",run_bin,run_low,run_high,200,0.0,400);
TH2F* rms_trklen_pandoraTrack = new TH2F("rms_trklen_pandoraTrack","# rms_trklen_pandoraTrack vs run",run_bin,run_low,run_high,200,0.0,400);
TH2F* rms_nshwr_pandoraShower = new TH2F("rms_nshwr_pandoraShower","# rms_nshwr_pandoraShower vs run",run_bin,run_low,run_high,450,0.0,900);
TH2F* rms_shwrlen_pandoraShower = new TH2F("rms_shwrlen_pandoraShower","# rms_shwrlen_pandoraShower vs run",run_bin,run_low,run_high,100,0.0,100);
TH2F* rms_nhit_tot = new TH2F("rms_nhit_tot","rms_nhit_tot vs run",run_bin,run_low,run_high,1000,0.0,200000);
TH2F* rms_nhit_U = new TH2F("rms_nhit_U","rms_nhit_U vs run",run_bin,run_low,run_high,1000,0.0,200000);
TH2F* rms_nhit_V = new TH2F("rms_nhit_V","rms_nhit_V vs run",run_bin,run_low,run_high,1000,0.0,200000);
TH2F* rms_nhit_Y = new TH2F("rms_nhit_Y","rms_nhit_Y vs run",run_bin,run_low,run_high,1000,0.0,200000);
TH2F* rms_hit_ph = new TH2F("rms_hit_ph","rms_hit_ph vs run",run_bin,run_low,run_high,80,0.0,80);
TH2F* rms_hitph_U = new TH2F("rms_hitph_U","rms_hitph_U vs run",run_bin,run_low,run_high,80,0.0,80);
TH2F* rms_hitph_V = new TH2F("rms_hitph_V","# rms_hitph_V vs run",run_bin,run_low,run_high,80,0.0,80);
TH2F* rms_hitph_Y = new TH2F("rms_hitph_Y","# rms_hitph_Y vs run",run_bin,run_low,run_high,80,0.0,80);
TH2F* rms_hit_charge = new TH2F("rms_hit_charge","# rms_hit_charge vs run",run_bin,run_low,run_high,600,0.0,1200);
TH2F* rms_hitcharge_U = new TH2F("rms_hitcharge_U","# rms_hitcharge_U vs run",run_bin,run_low,run_high,600,0.0,1200);
TH2F* rms_hitcharge_V = new TH2F("rms_hitcharge_V","# rms_hitcharge_V vs run",run_bin,run_low,run_high,600,0.0,1200);
TH2F* rms_hitcharge_Y = new TH2F("rms_hitcharge_Y","# rms_hitcharge_Y vs run",run_bin,run_low,run_high,600,0.0,1200);
TH2F* rms_nflashTot_opflashExt = new TH2F("rms_nflashTot_opflashExt","# rms_nflashTot_opflashExt vs run",run_bin,run_low,run_high,50,0.0,2);
TH2F* rms_nflashPE50_opflashExt = new TH2F("rms_nflashPE50_opflashExt","# rms_nflashPE50_opflashExt vs run",run_bin,run_low,run_high,50,0.0,2);
TH2F* rms_nflashPE20_opflashExt = new TH2F("rms_nflashPE20_opflashExt","# rms_nflashPE20_opflashExt vs run",run_bin,run_low,run_high,50,0.0,2);
TH2F* rms_nflashPE0_20_opflashExt = new TH2F("rms_nflashPE0_20_opflashExt","# rms_nflashPE0_20_opflashExt vs run",run_bin,run_low,run_high,50,0.0,2);
TH2F* rms_nflashTot_opflashInt = new TH2F("rms_nflashTot_opflashInt","# rms_nflashTot_opflashInt vs run",run_bin,run_low,run_high,200,0.0,200);
TH2F* rms_nflashPE50_opflashInt = new TH2F("rms_nflashPE50_opflashInt","# rms_nflashPE50_opflashInt vs run",run_bin,run_low,run_high,200,0.0,200);
TH2F* rms_nflashPE20_opflashInt = new TH2F("rms_nflashPE20_opflashInt","# rms_nflashPE20_opflashInt vs run",run_bin,run_low,run_high,200,0.0,200);
TH2F* rms_nflashPE0_20_opflashInt = new TH2F("rms_nflashPE0_20_opflashInt","# rms_nflashPE0_20_opflashInt vs run",run_bin,run_low,run_high,200,0.0,200);
TH2F* rms_flashycenter_opflashExt = new TH2F("rms_flashycenter_opflashExt","# rms_flashycenter_opflashExt vs run",run_bin,run_low,run_high,200,0.0,600);
TH2F* rms_flashycenterPE50_opflashExt = new TH2F("rms_flashycenterPE50_opflashExt","# rms_flashycenterPE50_opflashExt vs run",run_bin,run_low,run_high,200,0.0,600);
TH2F* rms_flashycenterPE20_opflashExt = new TH2F("rms_flashycenterPE20_opflashExt","# rms_flashycenterPE20_opflashExt vs run",run_bin,run_low,run_high,200,0.0,600);
TH2F* rms_flashzcenter_opflashExt = new TH2F("rms_flashzcenter_opflashExt","# rms_flashzcenter_opflashExt vs run",run_bin,run_low,run_high,200,0.0,600);
TH2F* rms_flashzcenterPE50_opflashExt = new TH2F("rms_flashzcenterPE50_opflashExt","# rms_flashzcenterPE50_opflashExt vs run",run_bin,run_low,run_high,200,0.0,600);
TH2F* rms_flashzcenterPE20_opflashExt = new TH2F("rms_flashzcenterPE20_opflashExt","# rms_flashzcenterPE20_opflashExt vs run",run_bin,run_low,run_high,200,0.0,600);
TH2F* rms_flashycenter_opflashInt = new TH2F("rms_flashycenter_opflashInt","# rms_flashycenter_opflashInt vs run",run_bin,run_low,run_high,200,0.0,600);
TH2F* rms_flashycenterPE50_opflashInt = new TH2F("rms_flashycenterPE50_opflashInt","# rms_flashycenterPE50_opflashInt vs run",run_bin,run_low,run_high,200,0.0,600);
TH2F* rms_flashycenterPE20_opflashInt = new TH2F("rms_flashycenterPE20_opflashInt","# rms_flashycenterPE20_opflashInt vs run",run_bin,run_low,run_high,200,0.0,600);
TH2F* rms_flashzcenter_opflashInt = new TH2F("rms_flashzcenter_opflashInt","# rms_flashzcenter_opflashInt vs run",run_bin,run_low,run_high,200,0.0,600);
TH2F* rms_flashzcenterPE50_opflashInt = new TH2F("rms_flashzcenterPE50_opflashInt","# rms_flashzcenterPE50_opflashInt vs run",run_bin,run_low,run_high,200,0.0,600);
TH2F* rms_flashzcenterPE20_opflashInt = new TH2F("rms_flashzcenterPE20_opflashInt","# rms_flashzcenterPE20_opflashInt vs run",run_bin,run_low,run_high,200,0.0,600);
TH2F* rms_flashPE_opflashExt = new TH2F("rms_flashPE_opflashExt","# rms_flashPE_opflashExt vs run",run_bin,run_low,run_high,1000,0.0,100000);
TH2F* rms_flashPE_opflashInt = new TH2F("rms_flashPE_opflashInt","# rms_flashPE_opflashInt vs run",run_bin,run_low,run_high,1000,0.0,20000);
TH2F* rms_nvrtx_pmtrack = new TH2F("rms_nvrtx_pmtrack","# rms_nvrtx_pmtrack vs run",run_bin,run_low,run_high,600,0.0,1200);
TH2F* rms_nvrtx_pandora = new TH2F("rms_nvrtx_pandora","# rms_nvrtx_pandora vs run",run_bin,run_low,run_high,600,0.0,1200);
TH2F* rms_npfps_pmtrack = new TH2F("rms_npfps_pmtrack","# rms_npfps_pmtrack vs run",run_bin,run_low,run_high,600,0.0,1200);
TH2F* rms_npfps_pandora = new TH2F("rms_npfps_pandora","# rms_npfps_pandora vs run",run_bin,run_low,run_high,600,0.0,1200);
TH2F* rms_trackpos_beginx_pmtrack = new TH2F("rms_trackpos_beginx_pmtrack","# rms_trackpos_beginx_pmtrack vs run",run_bin,run_low,run_high,200,0.0,600);
TH2F* rms_trackpos_beginy_pmtrack = new TH2F("rms_trackpos_beginy_pmtrack","# rms_trackpos_beginy_pmtrack vs run",run_bin,run_low,run_high,200,0.0,600);
TH2F* rms_trackpos_beginz_pmtrack = new TH2F("rms_trackpos_beginz_pmtrack","# rms_trackpos_beginz_pmtrack vs run",run_bin,run_low,run_high,200,0.0,600);
TH2F* rms_trackpos_beginx_pandoraTrack = new TH2F("rms_trackpos_beginx_pandoraTrack","# rms_trackpos_beginx_pandoraTrack vs run",run_bin,run_low,run_high,200,0.0,600);
TH2F* rms_trackpos_beginy_pandoraTrack = new TH2F("rms_trackpos_beginy_pandoraTrack","# rms_trackpos_beginy_pandoraTrack vs run",run_bin,run_low,run_high,200,0.0,600);
TH2F* rms_trackpos_beginz_pandoraTrack = new TH2F("rms_trackpos_beginz_pandoraTrack","# rms_trackpos_beginz_pandoraTrack vs run",run_bin,run_low,run_high,200,0.0,600);
TH2F* rms_trackpos_endx_pmtrack = new TH2F("rms_trackpos_endx_pmtrack","# rms_trackpos_endx_pmtrack vs run",run_bin,run_low,run_high,200,0.0,600);
TH2F* rms_trackpos_endy_pmtrack = new TH2F("rms_trackpos_endy_pmtrack","# rms_trackpos_endy_pmtrack vs run",run_bin,run_low,run_high,200,0.0,600);
TH2F* rms_trackpos_endz_pmtrack = new TH2F("rms_trackpos_endz_pmtrack","# rms_trackpos_endz_pmtrack vs run",run_bin,run_low,run_high,200,0.0,600);
TH2F* rms_trackpos_endx_pandoraTrack = new TH2F("rms_trackpos_endx_pandoraTrack","# rms_trackpos_endx_pandoraTrack vs run",run_bin,run_low,run_high,200,0.0,600);
TH2F* rms_trackpos_endy_pandoraTrack = new TH2F("rms_trackpos_endy_pandoraTrack","# rms_trackpos_endy_pandoraTrack vs run",run_bin,run_low,run_high,200,0.0,600);
TH2F* rms_trackpos_endz_pandoraTrack = new TH2F("rms_trackpos_endz_pandoraTrack","# rms_trackpos_endz_pandoraTrack vs run",run_bin,run_low,run_high,200,0.0,600);
TH2F* rms_Intflash_ywidth = new TH2F("rms_Intflash_ywidth","# rms_Intflash_ywidth vs run",run_bin,run_low,run_high,150,0.0,300);
TH2F* rms_Intflash_zwidth = new TH2F("rms_Intflash_zwidth","# rms_Intflash_zwidth vs run",run_bin,run_low,run_high,150,0.0,300);
TH2F* rms_Extflash_ywidth = new TH2F("rms_Extflash_ywidth","# rms_Extflash_ywidth vs run",run_bin,run_low,run_high,150,0.0,300);
TH2F* rms_Extflash_zwidth = new TH2F("rms_Extflash_zwidth","# rms_Extflash_zwidth vs run",run_bin,run_low,run_high,150,0.0,300);



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

float _f_mean_ntrack_pmtrack_MC;
float _f_mean_ntrack_pandoraTrack_MC;
float _f_mean_trklen_pmtrack_MC;
float _f_mean_trklen_pandoraTrack_MC;
float _f_mean_nshwr_pandoraShower_MC;
float _f_mean_shwrlen_pandoraShower_MC;
float _f_mean_nhit_tot_MC;
float _f_mean_nhit_U_MC;
float _f_mean_nhit_V_MC;
float _f_mean_nhit_Y_MC;
float _f_mean_hit_ph_MC;
float _f_mean_hitph_U_MC;
float _f_mean_hitph_V_MC;
float _f_mean_hitph_Y_MC;
float _f_mean_hit_charge_MC;
float _f_mean_hitcharge_U_MC;
float _f_mean_hitcharge_V_MC;
float _f_mean_hitcharge_Y_MC;
float _f_mean_nflashTot_opflashExt_MC;
float _f_mean_nflashPE50_opflashExt_MC;
float _f_mean_nflashPE20_opflashExt_MC;
float _f_mean_nflashPE0_20_opflashExt_MC;
float _f_mean_nflashTot_opflashInt_MC;
float _f_mean_nflashPE50_opflashInt_MC;
float _f_mean_nflashPE20_opflashInt_MC;
float _f_mean_nflashPE0_20_opflashInt_MC;
float _f_mean_flashycenter_opflashExt_MC;
//float _f_mean_flashycenterPE0_20_opflashExt_MC;
float _f_mean_flashycenterPE20_opflashExt_MC;
float _f_mean_flashycenterPE50_opflashExt_MC;
float _f_mean_flashzcenter_opflashExt_MC;
//float _f_mean_flashzcenterPE0_20_opflashExt_MC;
float _f_mean_flashzcenterPE20_opflashExt_MC;
float _f_mean_flashzcenterPE50_opflashExt_MC;
float _f_mean_flashycenter_opflashInt_MC;
//float _f_mean_flashycenterPE0_20_opflashInt_MC;
float _f_mean_flashycenterPE20_opflashInt_MC;
float _f_mean_flashycenterPE50_opflashInt_MC;
float _f_mean_flashzcenter_opflashInt_MC;
//float _f_mean_flashzcenterPE0_20_opflashInt_MC;
float _f_mean_flashzcenterPE20_opflashInt_MC;
float _f_mean_flashzcenterPE50_opflashInt_MC;
float _f_mean_flashPE_opflashExt_MC;
float _f_mean_flashPE_opflashInt_MC;
float _f_mean_nvrtx_pmtrack_MC;
float _f_mean_nvrtx_pandora_MC;
float _f_mean_npfps_pmtrack_MC;
float _f_mean_npfps_pandora_MC;
float _f_mean_trackpos_beginx_pmtrack_MC;
float _f_mean_trackpos_beginy_pmtrack_MC;
float _f_mean_trackpos_beginz_pmtrack_MC;
float _f_mean_trackpos_beginx_pandoraTrack_MC;
float _f_mean_trackpos_beginy_pandoraTrack_MC;
float _f_mean_trackpos_beginz_pandoraTrack_MC;
float _f_mean_trackpos_endx_pmtrack_MC;
float _f_mean_trackpos_endy_pmtrack_MC;
float _f_mean_trackpos_endz_pmtrack_MC;
float _f_mean_trackpos_endx_pandoraTrack_MC;
float _f_mean_trackpos_endy_pandoraTrack_MC;
float _f_mean_trackpos_endz_pandoraTrack_MC;
float _f_mean_Intflash_ywidth_MC;
float _f_mean_Intflash_zwidth_MC;
float _f_mean_Extflash_ywidth_MC;
float _f_mean_Extflash_zwidth_MC;

float _f_rms_ntrack_pmtrack_MC;
float _f_rms_ntrack_pandoraTrack_MC;
float _f_rms_trklen_pmtrack_MC;
float _f_rms_trklen_pandoraTrack_MC;
float _f_rms_nshwr_pandoraShower_MC;
float _f_rms_shwrlen_pandoraShower_MC;
float _f_rms_nhit_tot_MC;
float _f_rms_nhit_U_MC;
float _f_rms_nhit_V_MC;
float _f_rms_nhit_Y_MC;
float _f_rms_hit_ph_MC;
float _f_rms_hitph_U_MC;
float _f_rms_hitph_V_MC;
float _f_rms_hitph_Y_MC;
float _f_rms_hit_charge_MC;
float _f_rms_hitcharge_U_MC;
float _f_rms_hitcharge_V_MC;
float _f_rms_hitcharge_Y_MC;
float _f_rms_nflashTot_opflashExt_MC;
float _f_rms_nflashPE50_opflashExt_MC;
float _f_rms_nflashPE20_opflashExt_MC;
float _f_rms_nflashPE0_20_opflashExt_MC;
float _f_rms_nflashTot_opflashInt_MC;
float _f_rms_nflashPE50_opflashInt_MC;
float _f_rms_nflashPE20_opflashInt_MC;
float _f_rms_nflashPE0_20_opflashInt_MC;
float _f_rms_flashycenter_opflashExt_MC;
//float _f_rms_flashycenterPE0_20_opflashExt_MC;
float _f_rms_flashycenterPE20_opflashExt_MC;
float _f_rms_flashycenterPE50_opflashExt_MC;
float _f_rms_flashzcenter_opflashExt_MC;
//float _f_rms_flashzcenterPE0_20_opflashExt_MC;
float _f_rms_flashzcenterPE20_opflashExt_MC;
float _f_rms_flashzcenterPE50_opflashExt_MC;
float _f_rms_flashycenter_opflashInt_MC;
//float _f_rms_flashycenterPE0_20_opflashInt_MC;
float _f_rms_flashycenterPE20_opflashInt_MC;
float _f_rms_flashycenterPE50_opflashInt_MC;
float _f_rms_flashzcenter_opflashInt_MC;
//float _f_rms_flashzcenterPE0_20_opflashInt_MC;
float _f_rms_flashzcenterPE20_opflashInt_MC;
float _f_rms_flashzcenterPE50_opflashInt_MC;
float _f_rms_flashPE_opflashExt_MC;
float _f_rms_flashPE_opflashInt_MC;
float _f_rms_nvrtx_pmtrack_MC;
float _f_rms_nvrtx_pandora_MC;
float _f_rms_npfps_pmtrack_MC;
float _f_rms_npfps_pandora_MC;
float _f_rms_trackpos_beginx_pmtrack_MC;
float _f_rms_trackpos_beginy_pmtrack_MC;
float _f_rms_trackpos_beginz_pmtrack_MC;
float _f_rms_trackpos_beginx_pandoraTrack_MC;
float _f_rms_trackpos_beginy_pandoraTrack_MC;
float _f_rms_trackpos_beginz_pandoraTrack_MC;
float _f_rms_trackpos_endx_pmtrack_MC;
float _f_rms_trackpos_endy_pmtrack_MC;
float _f_rms_trackpos_endz_pmtrack_MC;
float _f_rms_trackpos_endx_pandoraTrack_MC;
float _f_rms_trackpos_endy_pandoraTrack_MC;
float _f_rms_trackpos_endz_pandoraTrack_MC;
float _f_rms_Intflash_ywidth_MC;
float _f_rms_Intflash_zwidth_MC;
float _f_rms_Extflash_ywidth_MC;
float _f_rms_Extflash_zwidth_MC;



TreeData -> SetBranchAddress("_frun",&_frun);
TreeData -> SetBranchAddress("_fnumevent",&_fnumevent);

TreeData -> SetBranchAddress("_f_mean_ntrack_pmtrack",&_f_mean_ntrack_pmtrack);
TreeData -> SetBranchAddress("_f_mean_ntrack_pandoraTrack",&_f_mean_ntrack_pandoraTrack);
TreeData -> SetBranchAddress("_f_mean_trklen_pmtrack",&_f_mean_trklen_pmtrack);
TreeData -> SetBranchAddress("_f_mean_trklen_pandoraTrack",&_f_mean_trklen_pandoraTrack);
TreeData -> SetBranchAddress("_f_mean_nshwr_pandoraShower",&_f_mean_nshwr_pandoraShower);
TreeData -> SetBranchAddress("_f_mean_shwrlen_pandoraShower",&_f_mean_shwrlen_pandoraShower);
TreeData -> SetBranchAddress("_f_mean_nhit_tot",&_f_mean_nhit_tot);
TreeData -> SetBranchAddress("_f_mean_nhit_U",&_f_mean_nhit_U);
TreeData -> SetBranchAddress("_f_mean_nhit_V",&_f_mean_nhit_V);
TreeData -> SetBranchAddress("_f_mean_nhit_Y",&_f_mean_nhit_Y);
TreeData -> SetBranchAddress("_f_mean_hit_ph",&_f_mean_hit_ph);
TreeData -> SetBranchAddress("_f_mean_hitph_U",&_f_mean_hitph_U);
TreeData -> SetBranchAddress("_f_mean_hitph_V",&_f_mean_hitph_V);
TreeData -> SetBranchAddress("_f_mean_hitph_Y",&_f_mean_hitph_Y);
TreeData -> SetBranchAddress("_f_mean_hit_charge",&_f_mean_hit_charge);
TreeData -> SetBranchAddress("_f_mean_hitcharge_U",&_f_mean_hitcharge_U);
TreeData -> SetBranchAddress("_f_mean_hitcharge_V",&_f_mean_hitcharge_V);
TreeData -> SetBranchAddress("_f_mean_hitcharge_Y",&_f_mean_hitcharge_Y);
TreeData -> SetBranchAddress("_f_mean_nflashTot_opflashExt",&_f_mean_nflashTot_opflashExt);
TreeData -> SetBranchAddress("_f_mean_nflashPE50_opflashExt",&_f_mean_nflashPE50_opflashExt);
TreeData -> SetBranchAddress("_f_mean_nflashPE20_opflashExt",&_f_mean_nflashPE20_opflashExt);
TreeData -> SetBranchAddress("_f_mean_nflashPE0_20_opflashExt",&_f_mean_nflashPE0_20_opflashExt);
TreeData -> SetBranchAddress("_f_mean_nflashTot_opflashInt",&_f_mean_nflashTot_opflashInt);
TreeData -> SetBranchAddress("_f_mean_nflashPE50_opflashInt",&_f_mean_nflashPE50_opflashInt);
TreeData -> SetBranchAddress("_f_mean_nflashPE20_opflashInt",&_f_mean_nflashPE20_opflashInt);
TreeData -> SetBranchAddress("_f_mean_nflashPE0_20_opflashInt",&_f_mean_nflashPE0_20_opflashInt);
TreeData -> SetBranchAddress("_f_mean_flashycenter_opflashExt",&_f_mean_flashycenter_opflashExt);
//TreeData -> SetBranchAddress("_f_mean_flashycenterPE0_20_opflashExt",&_f_mean_flashycenterPE0_20_opflashExt);
TreeData -> SetBranchAddress("_f_mean_flashycenterPE20_opflashExt",&_f_mean_flashycenterPE20_opflashExt);
TreeData -> SetBranchAddress("_f_mean_flashycenterPE50_opflashExt",&_f_mean_flashycenterPE50_opflashExt);
TreeData -> SetBranchAddress("_f_mean_flashzcenter_opflashExt",&_f_mean_flashzcenter_opflashExt);
//TreeData -> SetBranchAddress("_f_mean_flashzcenterPE0_20_opflashExt",&_f_mean_flashzcenterPE0_20_opflashExt);
TreeData -> SetBranchAddress("_f_mean_flashzcenterPE20_opflashExt",&_f_mean_flashzcenterPE20_opflashExt);
TreeData -> SetBranchAddress("_f_mean_flashzcenterPE50_opflashExt",&_f_mean_flashzcenterPE50_opflashExt);
TreeData -> SetBranchAddress("_f_mean_flashycenter_opflashInt",&_f_mean_flashycenter_opflashInt);
//TreeData -> SetBranchAddress("_f_mean_flashycenterPE0_20_opflashInt",&_f_mean_flashycenterPE0_20_opflashInt);
TreeData -> SetBranchAddress("_f_mean_flashycenterPE20_opflashInt",&_f_mean_flashycenterPE20_opflashInt);
TreeData -> SetBranchAddress("_f_mean_flashycenterPE50_opflashInt",&_f_mean_flashycenterPE50_opflashInt);
TreeData -> SetBranchAddress("_f_mean_flashzcenter_opflashInt",&_f_mean_flashzcenter_opflashInt);
//TreeData -> SetBranchAddress("_f_mean_flashzcenterPE0_20_opflashInt",&_f_mean_flashzcenterPE0_20_opflashInt);
TreeData -> SetBranchAddress("_f_mean_flashzcenterPE20_opflashInt",&_f_mean_flashzcenterPE20_opflashInt);
TreeData -> SetBranchAddress("_f_mean_flashzcenterPE50_opflashInt",&_f_mean_flashzcenterPE50_opflashInt);
TreeData -> SetBranchAddress("_f_mean_flashPE_opflashExt",&_f_mean_flashPE_opflashExt);
TreeData -> SetBranchAddress("_f_mean_flashPE_opflashInt",&_f_mean_flashPE_opflashInt);
TreeData -> SetBranchAddress("_f_mean_nvrtx_pmtrack",&_f_mean_nvrtx_pmtrack);
TreeData -> SetBranchAddress("_f_mean_nvrtx_pandora",&_f_mean_nvrtx_pandora);
TreeData -> SetBranchAddress("_f_mean_npfps_pmtrack",&_f_mean_npfps_pmtrack);
TreeData -> SetBranchAddress("_f_mean_npfps_pandora",&_f_mean_npfps_pandora);
TreeData -> SetBranchAddress("_f_mean_trackpos_beginx_pmtrack",&_f_mean_trackpos_beginx_pmtrack);
TreeData -> SetBranchAddress("_f_mean_trackpos_beginy_pmtrack",&_f_mean_trackpos_beginy_pmtrack);
TreeData -> SetBranchAddress("_f_mean_trackpos_beginz_pmtrack",&_f_mean_trackpos_beginz_pmtrack);
TreeData -> SetBranchAddress("_f_mean_trackpos_endx_pmtrack",&_f_mean_trackpos_endx_pmtrack);
TreeData -> SetBranchAddress("_f_mean_trackpos_endy_pmtrack",&_f_mean_trackpos_endy_pmtrack);
TreeData -> SetBranchAddress("_f_mean_trackpos_endz_pmtrack",&_f_mean_trackpos_endz_pmtrack);
TreeData -> SetBranchAddress("_f_mean_trackpos_beginx_pandoraTrack",&_f_mean_trackpos_beginx_pandoraTrack);
TreeData -> SetBranchAddress("_f_mean_trackpos_beginy_pandoraTrack",&_f_mean_trackpos_beginy_pandoraTrack);
TreeData -> SetBranchAddress("_f_mean_trackpos_beginz_pandoraTrack",&_f_mean_trackpos_beginz_pandoraTrack);
TreeData -> SetBranchAddress("_f_mean_trackpos_endx_pandoraTrack",&_f_mean_trackpos_endx_pandoraTrack);
TreeData -> SetBranchAddress("_f_mean_trackpos_endy_pandoraTrack",&_f_mean_trackpos_endy_pandoraTrack);
TreeData -> SetBranchAddress("_f_mean_trackpos_endz_pandoraTrack",&_f_mean_trackpos_endz_pandoraTrack);
TreeData -> SetBranchAddress("_f_mean_Intflash_ywidth",&_f_mean_Intflash_ywidth);
TreeData -> SetBranchAddress("_f_mean_Intflash_zwidth",&_f_mean_Intflash_zwidth);
TreeData -> SetBranchAddress("_f_mean_Extflash_ywidth",&_f_mean_Extflash_ywidth);
TreeData -> SetBranchAddress("_f_mean_Extflash_zwidth",&_f_mean_Extflash_zwidth);

TreeData -> SetBranchAddress("_f_rms_ntrack_pmtrack",&_f_rms_ntrack_pmtrack);
TreeData -> SetBranchAddress("_f_rms_ntrack_pandoraTrack",&_f_rms_ntrack_pandoraTrack);
TreeData -> SetBranchAddress("_f_rms_trklen_pmtrack",&_f_rms_trklen_pmtrack);
TreeData -> SetBranchAddress("_f_rms_trklen_pandoraTrack",&_f_rms_trklen_pandoraTrack);
TreeData -> SetBranchAddress("_f_rms_nshwr_pandoraShower",&_f_rms_nshwr_pandoraShower);
TreeData -> SetBranchAddress("_f_rms_shwrlen_pandoraShower",&_f_rms_shwrlen_pandoraShower);
TreeData -> SetBranchAddress("_f_rms_nhit_tot",&_f_rms_nhit_tot);
TreeData -> SetBranchAddress("_f_rms_nhit_U",&_f_rms_nhit_U);
TreeData -> SetBranchAddress("_f_rms_nhit_V",&_f_rms_nhit_V);
TreeData -> SetBranchAddress("_f_rms_nhit_Y",&_f_rms_nhit_Y);
TreeData -> SetBranchAddress("_f_rms_hit_ph",&_f_rms_hit_ph);
TreeData -> SetBranchAddress("_f_rms_hitph_U",&_f_rms_hitph_U);
TreeData -> SetBranchAddress("_f_rms_hitph_V",&_f_rms_hitph_V);
TreeData -> SetBranchAddress("_f_rms_hitph_Y",&_f_rms_hitph_Y);
TreeData -> SetBranchAddress("_f_rms_hit_charge",&_f_rms_hit_charge);
TreeData -> SetBranchAddress("_f_rms_hitcharge_U",&_f_rms_hitcharge_U);
TreeData -> SetBranchAddress("_f_rms_hitcharge_V",&_f_rms_hitcharge_V);
TreeData -> SetBranchAddress("_f_rms_hitcharge_Y",&_f_rms_hitcharge_Y);
TreeData -> SetBranchAddress("_f_rms_nflashTot_opflashExt",&_f_rms_nflashTot_opflashExt);
TreeData -> SetBranchAddress("_f_rms_nflashPE50_opflashExt",&_f_rms_nflashPE50_opflashExt);
TreeData -> SetBranchAddress("_f_rms_nflashPE20_opflashExt",&_f_rms_nflashPE20_opflashExt);
TreeData -> SetBranchAddress("_f_rms_nflashPE0_20_opflashExt",&_f_rms_nflashPE0_20_opflashExt);
TreeData -> SetBranchAddress("_f_rms_nflashTot_opflashInt",&_f_rms_nflashTot_opflashInt);
TreeData -> SetBranchAddress("_f_rms_nflashPE50_opflashInt",&_f_rms_nflashPE50_opflashInt);
TreeData -> SetBranchAddress("_f_rms_nflashPE20_opflashInt",&_f_rms_nflashPE20_opflashInt);
TreeData -> SetBranchAddress("_f_rms_nflashPE0_20_opflashInt",&_f_rms_nflashPE0_20_opflashInt);
TreeData -> SetBranchAddress("_f_rms_flashycenter_opflashExt",&_f_rms_flashycenter_opflashExt);
//TreeData -> SetBranchAddress("_f_rms_flashycenterPE0_20_opflashExt",&_f_rms_flashycenterPE0_20_opflashExt);
TreeData -> SetBranchAddress("_f_rms_flashycenterPE20_opflashExt",&_f_rms_flashycenterPE20_opflashExt);
TreeData -> SetBranchAddress("_f_rms_flashycenterPE50_opflashExt",&_f_rms_flashycenterPE50_opflashExt);
TreeData -> SetBranchAddress("_f_rms_flashzcenter_opflashExt",&_f_rms_flashzcenter_opflashExt);
//TreeData -> SetBranchAddress("_f_rms_flashzcenterPE0_20_opflashExt",&_f_rms_flashzcenterPE0_20_opflashExt);
TreeData -> SetBranchAddress("_f_rms_flashzcenterPE20_opflashExt",&_f_rms_flashzcenterPE20_opflashExt);
TreeData -> SetBranchAddress("_f_rms_flashzcenterPE50_opflashExt",&_f_rms_flashzcenterPE50_opflashExt);
TreeData -> SetBranchAddress("_f_rms_flashycenter_opflashInt",&_f_rms_flashycenter_opflashInt);
//TreeData -> SetBranchAddress("_f_rms_flashycenterPE0_20_opflashInt",&_f_rms_flashycenterPE0_20_opflashInt);
TreeData -> SetBranchAddress("_f_rms_flashycenterPE20_opflashInt",&_f_rms_flashycenterPE20_opflashInt);
TreeData -> SetBranchAddress("_f_rms_flashycenterPE50_opflashInt",&_f_rms_flashycenterPE50_opflashInt);
TreeData -> SetBranchAddress("_f_rms_flashzcenter_opflashInt",&_f_rms_flashzcenter_opflashInt);
//TreeData -> SetBranchAddress("_f_rms_flashzcenterPE0_20_opflashInt",&_f_rms_flashzcenterPE0_20_opflashInt);
TreeData -> SetBranchAddress("_f_rms_flashzcenterPE20_opflashInt",&_f_rms_flashzcenterPE20_opflashInt);
TreeData -> SetBranchAddress("_f_rms_flashzcenterPE50_opflashInt",&_f_rms_flashzcenterPE50_opflashInt);
TreeData -> SetBranchAddress("_f_rms_flashPE_opflashExt",&_f_rms_flashPE_opflashExt);
TreeData -> SetBranchAddress("_f_rms_flashPE_opflashInt",&_f_rms_flashPE_opflashInt);
TreeData -> SetBranchAddress("_f_rms_nvrtx_pmtrack",&_f_rms_nvrtx_pmtrack);
TreeData -> SetBranchAddress("_f_rms_nvrtx_pandora",&_f_rms_nvrtx_pandora);
TreeData -> SetBranchAddress("_f_rms_npfps_pmtrack",&_f_rms_npfps_pmtrack);
TreeData -> SetBranchAddress("_f_rms_npfps_pandora",&_f_rms_npfps_pandora);
TreeData -> SetBranchAddress("_f_rms_trackpos_beginx_pmtrack",&_f_rms_trackpos_beginx_pmtrack);
TreeData -> SetBranchAddress("_f_rms_trackpos_beginy_pmtrack",&_f_rms_trackpos_beginy_pmtrack);
TreeData -> SetBranchAddress("_f_rms_trackpos_beginz_pmtrack",&_f_rms_trackpos_beginz_pmtrack);
TreeData -> SetBranchAddress("_f_rms_trackpos_endx_pmtrack",&_f_rms_trackpos_endx_pmtrack);
TreeData -> SetBranchAddress("_f_rms_trackpos_endy_pmtrack",&_f_rms_trackpos_endy_pmtrack);
TreeData -> SetBranchAddress("_f_rms_trackpos_endz_pmtrack",&_f_rms_trackpos_endz_pmtrack);
TreeData -> SetBranchAddress("_f_rms_trackpos_beginx_pandoraTrack",&_f_rms_trackpos_beginx_pandoraTrack);
TreeData -> SetBranchAddress("_f_rms_trackpos_beginy_pandoraTrack",&_f_rms_trackpos_beginy_pandoraTrack);
TreeData -> SetBranchAddress("_f_rms_trackpos_beginz_pandoraTrack",&_f_rms_trackpos_beginz_pandoraTrack);
TreeData -> SetBranchAddress("_f_rms_trackpos_endx_pandoraTrack",&_f_rms_trackpos_endx_pandoraTrack);
TreeData -> SetBranchAddress("_f_rms_trackpos_endy_pandoraTrack",&_f_rms_trackpos_endy_pandoraTrack);
TreeData -> SetBranchAddress("_f_rms_trackpos_endz_pandoraTrack",&_f_rms_trackpos_endz_pandoraTrack);
TreeData -> SetBranchAddress("_f_rms_Intflash_ywidth",&_f_rms_Intflash_ywidth);
TreeData -> SetBranchAddress("_f_rms_Intflash_zwidth",&_f_rms_Intflash_zwidth);
TreeData -> SetBranchAddress("_f_rms_Extflash_ywidth",&_f_rms_Extflash_ywidth);
TreeData -> SetBranchAddress("_f_rms_Extflash_zwidth",&_f_rms_Extflash_zwidth);

MCData -> SetBranchAddress("_f_mean_ntrack_pmtrack",&_f_mean_ntrack_pmtrack_MC);
MCData -> SetBranchAddress("_f_mean_ntrack_pandoraTrack",&_f_mean_ntrack_pandoraTrack_MC);
MCData -> SetBranchAddress("_f_mean_trklen_pmtrack",&_f_mean_trklen_pmtrack_MC);
MCData -> SetBranchAddress("_f_mean_trklen_pandoraTrack",&_f_mean_trklen_pandoraTrack_MC);
MCData -> SetBranchAddress("_f_mean_nshwr_pandoraShower",&_f_mean_nshwr_pandoraShower_MC);
MCData -> SetBranchAddress("_f_mean_shwrlen_pandoraShower",&_f_mean_shwrlen_pandoraShower_MC);
MCData -> SetBranchAddress("_f_mean_nhit_tot",&_f_mean_nhit_tot_MC);
MCData -> SetBranchAddress("_f_mean_nhit_U",&_f_mean_nhit_U_MC);
MCData -> SetBranchAddress("_f_mean_nhit_V",&_f_mean_nhit_V_MC);
MCData -> SetBranchAddress("_f_mean_nhit_Y",&_f_mean_nhit_Y_MC);
MCData -> SetBranchAddress("_f_mean_hit_ph",&_f_mean_hit_ph_MC);
MCData -> SetBranchAddress("_f_mean_hitph_U",&_f_mean_hitph_U_MC);
MCData -> SetBranchAddress("_f_mean_hitph_V",&_f_mean_hitph_V_MC);
MCData -> SetBranchAddress("_f_mean_hitph_Y",&_f_mean_hitph_Y_MC);
MCData -> SetBranchAddress("_f_mean_hit_charge",&_f_mean_hit_charge_MC);
MCData -> SetBranchAddress("_f_mean_hitcharge_U",&_f_mean_hitcharge_U_MC);
MCData -> SetBranchAddress("_f_mean_hitcharge_V",&_f_mean_hitcharge_V_MC);
MCData -> SetBranchAddress("_f_mean_hitcharge_Y",&_f_mean_hitcharge_Y_MC);
MCData -> SetBranchAddress("_f_mean_nflashTot_opflashExt",&_f_mean_nflashTot_opflashExt_MC);
MCData -> SetBranchAddress("_f_mean_nflashPE50_opflashExt",&_f_mean_nflashPE50_opflashExt_MC);
MCData -> SetBranchAddress("_f_mean_nflashPE20_opflashExt",&_f_mean_nflashPE20_opflashExt_MC);
MCData -> SetBranchAddress("_f_mean_nflashPE0_20_opflashExt",&_f_mean_nflashPE0_20_opflashExt_MC);
MCData -> SetBranchAddress("_f_mean_nflashTot_opflashInt",&_f_mean_nflashTot_opflashInt_MC);
MCData -> SetBranchAddress("_f_mean_nflashPE50_opflashInt",&_f_mean_nflashPE50_opflashInt_MC);
MCData -> SetBranchAddress("_f_mean_nflashPE20_opflashInt",&_f_mean_nflashPE20_opflashInt_MC);
MCData -> SetBranchAddress("_f_mean_nflashPE0_20_opflashInt",&_f_mean_nflashPE0_20_opflashInt_MC);
MCData -> SetBranchAddress("_f_mean_flashycenter_opflashExt",&_f_mean_flashycenter_opflashExt_MC);
//MCData -> SetBranchAddress("_f_mean_flashycenterPE0_20_opflashExt",&_f_mean_flashycenterPE0_20_opflashExt_MC);
MCData -> SetBranchAddress("_f_mean_flashycenterPE20_opflashExt",&_f_mean_flashycenterPE20_opflashExt_MC);
MCData -> SetBranchAddress("_f_mean_flashycenterPE50_opflashExt",&_f_mean_flashycenterPE50_opflashExt_MC);
MCData -> SetBranchAddress("_f_mean_flashzcenter_opflashExt",&_f_mean_flashzcenter_opflashExt_MC);
//MCData -> SetBranchAddress("_f_mean_flashzcenterPE0_20_opflashExt",&_f_mean_flashzcenterPE0_20_opflashExt_MC);
MCData -> SetBranchAddress("_f_mean_flashzcenterPE20_opflashExt",&_f_mean_flashzcenterPE20_opflashExt_MC);
MCData -> SetBranchAddress("_f_mean_flashzcenterPE50_opflashExt",&_f_mean_flashzcenterPE50_opflashExt_MC);
MCData -> SetBranchAddress("_f_mean_flashycenter_opflashInt",&_f_mean_flashycenter_opflashInt_MC);
//MCData -> SetBranchAddress("_f_mean_flashycenterPE0_20_opflashInt",&_f_mean_flashycenterPE0_20_opflashInt_MC);
MCData -> SetBranchAddress("_f_mean_flashycenterPE20_opflashInt",&_f_mean_flashycenterPE20_opflashInt_MC);
MCData -> SetBranchAddress("_f_mean_flashycenterPE50_opflashInt",&_f_mean_flashycenterPE50_opflashInt_MC);
MCData -> SetBranchAddress("_f_mean_flashzcenter_opflashInt",&_f_mean_flashzcenter_opflashInt_MC);
//MCData -> SetBranchAddress("_f_mean_flashzcenterPE0_20_opflashInt",&_f_mean_flashzcenterPE0_20_opflashInt_MC);
MCData -> SetBranchAddress("_f_mean_flashzcenterPE20_opflashInt",&_f_mean_flashzcenterPE20_opflashInt_MC);
MCData -> SetBranchAddress("_f_mean_flashzcenterPE50_opflashInt",&_f_mean_flashzcenterPE50_opflashInt_MC);
MCData -> SetBranchAddress("_f_mean_flashPE_opflashExt",&_f_mean_flashPE_opflashExt_MC);
MCData -> SetBranchAddress("_f_mean_flashPE_opflashInt",&_f_mean_flashPE_opflashInt_MC);
MCData -> SetBranchAddress("_f_mean_nvrtx_pmtrack",&_f_mean_nvrtx_pmtrack_MC);
MCData -> SetBranchAddress("_f_mean_nvrtx_pandora",&_f_mean_nvrtx_pandora_MC);
MCData -> SetBranchAddress("_f_mean_npfps_pmtrack",&_f_mean_npfps_pmtrack_MC);
MCData -> SetBranchAddress("_f_mean_npfps_pandora",&_f_mean_npfps_pandora_MC);
MCData -> SetBranchAddress("_f_mean_trackpos_beginx_pmtrack",&_f_mean_trackpos_beginx_pmtrack_MC);
MCData -> SetBranchAddress("_f_mean_trackpos_beginy_pmtrack",&_f_mean_trackpos_beginy_pmtrack_MC);
MCData -> SetBranchAddress("_f_mean_trackpos_beginz_pmtrack",&_f_mean_trackpos_beginz_pmtrack_MC);
MCData -> SetBranchAddress("_f_mean_trackpos_endx_pmtrack",&_f_mean_trackpos_endx_pmtrack_MC);
MCData -> SetBranchAddress("_f_mean_trackpos_endy_pmtrack",&_f_mean_trackpos_endy_pmtrack_MC);
MCData -> SetBranchAddress("_f_mean_trackpos_endz_pmtrack",&_f_mean_trackpos_endz_pmtrack_MC);
MCData -> SetBranchAddress("_f_mean_trackpos_beginx_pandoraTrack",&_f_mean_trackpos_beginx_pandoraTrack_MC);
MCData -> SetBranchAddress("_f_mean_trackpos_beginy_pandoraTrack",&_f_mean_trackpos_beginy_pandoraTrack_MC);
MCData -> SetBranchAddress("_f_mean_trackpos_beginz_pandoraTrack",&_f_mean_trackpos_beginz_pandoraTrack_MC);
MCData -> SetBranchAddress("_f_mean_trackpos_endx_pandoraTrack",&_f_mean_trackpos_endx_pandoraTrack_MC);
MCData -> SetBranchAddress("_f_mean_trackpos_endy_pandoraTrack",&_f_mean_trackpos_endy_pandoraTrack_MC);
MCData -> SetBranchAddress("_f_mean_trackpos_endz_pandoraTrack",&_f_mean_trackpos_endz_pandoraTrack_MC);
MCData -> SetBranchAddress("_f_mean_Intflash_ywidth",&_f_mean_Intflash_ywidth_MC);
MCData -> SetBranchAddress("_f_mean_Intflash_zwidth",&_f_mean_Intflash_zwidth_MC);
MCData -> SetBranchAddress("_f_mean_Extflash_ywidth",&_f_mean_Extflash_ywidth_MC);
MCData -> SetBranchAddress("_f_mean_Extflash_zwidth",&_f_mean_Extflash_zwidth_MC);

MCData -> SetBranchAddress("_f_rms_ntrack_pmtrack",&_f_rms_ntrack_pmtrack_MC);
MCData -> SetBranchAddress("_f_rms_ntrack_pandoraTrack",&_f_rms_ntrack_pandoraTrack_MC);
MCData -> SetBranchAddress("_f_rms_trklen_pmtrack",&_f_rms_trklen_pmtrack_MC);
MCData -> SetBranchAddress("_f_rms_trklen_pandoraTrack",&_f_rms_trklen_pandoraTrack_MC);
MCData -> SetBranchAddress("_f_rms_nshwr_pandoraShower",&_f_rms_nshwr_pandoraShower_MC);
MCData -> SetBranchAddress("_f_rms_shwrlen_pandoraShower",&_f_rms_shwrlen_pandoraShower_MC);
MCData -> SetBranchAddress("_f_rms_nhit_tot",&_f_rms_nhit_tot_MC);
MCData -> SetBranchAddress("_f_rms_nhit_U",&_f_rms_nhit_U_MC);
MCData -> SetBranchAddress("_f_rms_nhit_V",&_f_rms_nhit_V_MC);
MCData -> SetBranchAddress("_f_rms_nhit_Y",&_f_rms_nhit_Y_MC);
MCData -> SetBranchAddress("_f_rms_hit_ph",&_f_rms_hit_ph_MC);
MCData -> SetBranchAddress("_f_rms_hitph_U",&_f_rms_hitph_U_MC);
MCData -> SetBranchAddress("_f_rms_hitph_V",&_f_rms_hitph_V_MC);
MCData -> SetBranchAddress("_f_rms_hitph_Y",&_f_rms_hitph_Y_MC);
MCData -> SetBranchAddress("_f_rms_hit_charge",&_f_rms_hit_charge_MC);
MCData -> SetBranchAddress("_f_rms_hitcharge_U",&_f_rms_hitcharge_U_MC);
MCData -> SetBranchAddress("_f_rms_hitcharge_V",&_f_rms_hitcharge_V_MC);
MCData -> SetBranchAddress("_f_rms_hitcharge_Y",&_f_rms_hitcharge_Y_MC);
MCData -> SetBranchAddress("_f_rms_nflashTot_opflashExt",&_f_rms_nflashTot_opflashExt_MC);
MCData -> SetBranchAddress("_f_rms_nflashPE50_opflashExt",&_f_rms_nflashPE50_opflashExt_MC);
MCData -> SetBranchAddress("_f_rms_nflashPE20_opflashExt",&_f_rms_nflashPE20_opflashExt_MC);
MCData -> SetBranchAddress("_f_rms_nflashPE0_20_opflashExt",&_f_rms_nflashPE0_20_opflashExt_MC);
MCData -> SetBranchAddress("_f_rms_nflashTot_opflashInt",&_f_rms_nflashTot_opflashInt_MC);
MCData -> SetBranchAddress("_f_rms_nflashPE50_opflashInt",&_f_rms_nflashPE50_opflashInt_MC);
MCData -> SetBranchAddress("_f_rms_nflashPE20_opflashInt",&_f_rms_nflashPE20_opflashInt_MC);
MCData -> SetBranchAddress("_f_rms_nflashPE0_20_opflashInt",&_f_rms_nflashPE0_20_opflashInt_MC);
MCData -> SetBranchAddress("_f_rms_flashycenter_opflashExt",&_f_rms_flashycenter_opflashExt_MC);
//MCData -> SetBranchAddress("_f_rms_flashycenterPE0_20_opflashExt",&_f_rms_flashycenterPE0_20_opflashExt_MC);
MCData -> SetBranchAddress("_f_rms_flashycenterPE20_opflashExt",&_f_rms_flashycenterPE20_opflashExt_MC);
MCData -> SetBranchAddress("_f_rms_flashycenterPE50_opflashExt",&_f_rms_flashycenterPE50_opflashExt_MC);
MCData -> SetBranchAddress("_f_rms_flashzcenter_opflashExt",&_f_rms_flashzcenter_opflashExt_MC);
//MCData -> SetBranchAddress("_f_rms_flashzcenterPE0_20_opflashExt",&_f_rms_flashzcenterPE0_20_opflashExt_MC);
MCData -> SetBranchAddress("_f_rms_flashzcenterPE20_opflashExt",&_f_rms_flashzcenterPE20_opflashExt_MC);
MCData -> SetBranchAddress("_f_rms_flashzcenterPE50_opflashExt",&_f_rms_flashzcenterPE50_opflashExt_MC);
MCData -> SetBranchAddress("_f_rms_flashycenter_opflashInt",&_f_rms_flashycenter_opflashInt_MC);
//MCData -> SetBranchAddress("_f_rms_flashycenterPE0_20_opflashInt",&_f_rms_flashycenterPE0_20_opflashInt_MC);
MCData -> SetBranchAddress("_f_rms_flashycenterPE20_opflashInt",&_f_rms_flashycenterPE20_opflashInt_MC);
MCData -> SetBranchAddress("_f_rms_flashycenterPE50_opflashInt",&_f_rms_flashycenterPE50_opflashInt_MC);
MCData -> SetBranchAddress("_f_rms_flashzcenter_opflashInt",&_f_rms_flashzcenter_opflashInt_MC);
//MCData -> SetBranchAddress("_f_rms_flashzcenterPE0_20_opflashInt",&_f_rms_flashzcenterPE0_20_opflashInt_MC);
MCData -> SetBranchAddress("_f_rms_flashzcenterPE20_opflashInt",&_f_rms_flashzcenterPE20_opflashInt_MC);
MCData -> SetBranchAddress("_f_rms_flashzcenterPE50_opflashInt",&_f_rms_flashzcenterPE50_opflashInt_MC);
MCData -> SetBranchAddress("_f_rms_flashPE_opflashExt",&_f_rms_flashPE_opflashExt_MC);
MCData -> SetBranchAddress("_f_rms_flashPE_opflashInt",&_f_rms_flashPE_opflashInt_MC);
MCData -> SetBranchAddress("_f_rms_nvrtx_pmtrack",&_f_rms_nvrtx_pmtrack_MC);
MCData -> SetBranchAddress("_f_rms_nvrtx_pandora",&_f_rms_nvrtx_pandora_MC);
MCData -> SetBranchAddress("_f_rms_npfps_pmtrack",&_f_rms_npfps_pmtrack_MC);
MCData -> SetBranchAddress("_f_rms_npfps_pandora",&_f_rms_npfps_pandora_MC);
MCData -> SetBranchAddress("_f_rms_trackpos_beginx_pmtrack",&_f_rms_trackpos_beginx_pmtrack_MC);
MCData -> SetBranchAddress("_f_rms_trackpos_beginy_pmtrack",&_f_rms_trackpos_beginy_pmtrack_MC);
MCData -> SetBranchAddress("_f_rms_trackpos_beginz_pmtrack",&_f_rms_trackpos_beginz_pmtrack_MC);
MCData -> SetBranchAddress("_f_rms_trackpos_endx_pmtrack",&_f_rms_trackpos_endx_pmtrack_MC);
MCData -> SetBranchAddress("_f_rms_trackpos_endy_pmtrack",&_f_rms_trackpos_endy_pmtrack_MC);
MCData -> SetBranchAddress("_f_rms_trackpos_endz_pmtrack",&_f_rms_trackpos_endz_pmtrack_MC);
MCData -> SetBranchAddress("_f_rms_trackpos_beginx_pandoraTrack",&_f_rms_trackpos_beginx_pandoraTrack_MC);
MCData -> SetBranchAddress("_f_rms_trackpos_beginy_pandoraTrack",&_f_rms_trackpos_beginy_pandoraTrack_MC);
MCData -> SetBranchAddress("_f_rms_trackpos_beginz_pandoraTrack",&_f_rms_trackpos_beginz_pandoraTrack_MC);
MCData -> SetBranchAddress("_f_rms_trackpos_endx_pandoraTrack",&_f_rms_trackpos_endx_pandoraTrack_MC);
MCData -> SetBranchAddress("_f_rms_trackpos_endy_pandoraTrack",&_f_rms_trackpos_endy_pandoraTrack_MC);
MCData -> SetBranchAddress("_f_rms_trackpos_endz_pandoraTrack",&_f_rms_trackpos_endz_pandoraTrack_MC);
MCData -> SetBranchAddress("_f_rms_Intflash_ywidth",&_f_rms_Intflash_ywidth_MC);
MCData -> SetBranchAddress("_f_rms_Intflash_zwidth",&_f_rms_Intflash_zwidth_MC);
MCData -> SetBranchAddress("_f_rms_Extflash_ywidth",&_f_rms_Extflash_ywidth_MC);
MCData -> SetBranchAddress("_f_rms_Extflash_zwidth",&_f_rms_Extflash_zwidth_MC);



//Fill histograms
nentries = TreeData->GetEntries();
for (int i=0; i<nentries;i++)
{
 TreeData->GetEntry(i);

mean_ntrack_pmtrack->Fill(_frun,_f_mean_ntrack_pmtrack);
mean_ntrack_pandoraTrack->Fill(_frun,_f_mean_ntrack_pandoraTrack);
mean_trklen_pmtrack->Fill(_frun,_f_mean_trklen_pmtrack);
mean_trklen_pandoraTrack->Fill(_frun,_f_mean_trklen_pandoraTrack);
mean_nshwr_pandoraShower->Fill(_frun,_f_mean_nshwr_pandoraShower);
mean_shwrlen_pandoraShower->Fill(_frun,_f_mean_shwrlen_pandoraShower);
mean_nhit_tot->Fill(_frun,_f_mean_nhit_tot);
mean_nhit_U->Fill(_frun,_f_mean_nhit_U);
mean_nhit_V->Fill(_frun,_f_mean_nhit_V);
mean_nhit_Y->Fill(_frun,_f_mean_nhit_Y);
mean_hit_ph->Fill(_frun,_f_mean_hit_ph);
mean_hitph_U->Fill(_frun,_f_mean_hitph_U);
mean_hitph_V->Fill(_frun,_f_mean_hitph_V);
mean_hitph_Y->Fill(_frun,_f_mean_hitph_Y);
mean_hit_charge->Fill(_frun,_f_mean_hit_charge);
mean_hitcharge_U->Fill(_frun,_f_mean_hitcharge_U);
mean_hitcharge_V->Fill(_frun,_f_mean_hitcharge_V);
mean_hitcharge_Y->Fill(_frun,_f_mean_hitcharge_Y);
mean_nflashTot_opflashExt->Fill(_frun,_f_mean_nflashTot_opflashExt);
mean_nflashPE50_opflashExt->Fill(_frun,_f_mean_nflashPE50_opflashExt);
mean_nflashPE20_opflashExt->Fill(_frun,_f_mean_nflashPE20_opflashExt);
mean_nflashPE0_20_opflashExt->Fill(_frun,_f_mean_nflashPE0_20_opflashExt);
mean_nflashTot_opflashInt->Fill(_frun,_f_mean_nflashTot_opflashInt);
mean_nflashPE50_opflashInt->Fill(_frun,_f_mean_nflashPE50_opflashInt);
mean_nflashPE20_opflashInt->Fill(_frun,_f_mean_nflashPE20_opflashInt);
mean_nflashPE0_20_opflashInt->Fill(_frun,_f_mean_nflashPE0_20_opflashInt);
mean_flashycenter_opflashExt->Fill(_frun,_f_mean_flashycenter_opflashExt);
mean_flashycenterPE50_opflashExt->Fill(_frun,_f_mean_flashycenterPE50_opflashExt);
mean_flashycenterPE20_opflashExt->Fill(_frun,_f_mean_flashycenterPE20_opflashExt);
mean_flashzcenter_opflashExt->Fill(_frun,_f_mean_flashzcenter_opflashExt);
mean_flashzcenterPE50_opflashExt->Fill(_frun,_f_mean_flashzcenterPE50_opflashExt);
mean_flashzcenterPE20_opflashExt->Fill(_frun,_f_mean_flashzcenterPE20_opflashExt);
mean_flashycenter_opflashInt->Fill(_frun,_f_mean_flashycenter_opflashInt);
mean_flashycenterPE50_opflashInt->Fill(_frun,_f_mean_flashycenterPE50_opflashInt);
mean_flashycenterPE20_opflashInt->Fill(_frun,_f_mean_flashycenterPE20_opflashInt);
mean_flashzcenter_opflashInt->Fill(_frun,_f_mean_flashzcenter_opflashInt);
mean_flashzcenterPE50_opflashInt->Fill(_frun,_f_mean_flashzcenterPE50_opflashInt);
mean_flashzcenterPE20_opflashInt->Fill(_frun,_f_mean_flashzcenterPE20_opflashInt);
mean_flashPE_opflashExt->Fill(_frun,_f_mean_flashPE_opflashExt);
mean_flashPE_opflashInt->Fill(_frun,_f_mean_flashPE_opflashInt);
mean_nvrtx_pmtrack->Fill(_frun,_f_mean_nvrtx_pmtrack);
mean_nvrtx_pandora->Fill(_frun,_f_mean_nvrtx_pandora);
mean_npfps_pmtrack->Fill(_frun,_f_mean_npfps_pmtrack);
mean_npfps_pandora->Fill(_frun,_f_mean_npfps_pandora);
mean_trackpos_beginx_pmtrack->Fill(_frun,_f_mean_trackpos_beginx_pmtrack);
mean_trackpos_beginy_pmtrack->Fill(_frun,_f_mean_trackpos_beginy_pmtrack);
mean_trackpos_beginz_pmtrack->Fill(_frun,_f_mean_trackpos_beginz_pmtrack);
mean_trackpos_endx_pmtrack->Fill(_frun,_f_mean_trackpos_endx_pmtrack);
mean_trackpos_endy_pmtrack->Fill(_frun,_f_mean_trackpos_endy_pmtrack);
mean_trackpos_endz_pmtrack->Fill(_frun,_f_mean_trackpos_endz_pmtrack);
mean_trackpos_beginx_pandoraTrack->Fill(_frun,_f_mean_trackpos_beginx_pandoraTrack);
mean_trackpos_beginy_pandoraTrack->Fill(_frun,_f_mean_trackpos_beginy_pandoraTrack);
mean_trackpos_beginz_pandoraTrack->Fill(_frun,_f_mean_trackpos_beginz_pandoraTrack);
mean_trackpos_endx_pandoraTrack->Fill(_frun,_f_mean_trackpos_endx_pandoraTrack);
mean_trackpos_endy_pandoraTrack->Fill(_frun,_f_mean_trackpos_endy_pandoraTrack);
mean_trackpos_endz_pandoraTrack->Fill(_frun,_f_mean_trackpos_endz_pandoraTrack);
mean_Intflash_ywidth->Fill(_frun,_f_mean_Intflash_ywidth);
mean_Intflash_zwidth->Fill(_frun,_f_mean_Intflash_zwidth);
mean_Extflash_ywidth->Fill(_frun,_f_mean_Extflash_ywidth);
mean_Extflash_zwidth->Fill(_frun,_f_mean_Extflash_zwidth);

rms_ntrack_pmtrack->Fill(_frun,_f_rms_ntrack_pmtrack);
rms_ntrack_pandoraTrack->Fill(_frun,_f_rms_ntrack_pandoraTrack);
rms_trklen_pmtrack->Fill(_frun,_f_rms_trklen_pmtrack);
rms_trklen_pandoraTrack->Fill(_frun,_f_rms_trklen_pandoraTrack);
rms_nshwr_pandoraShower->Fill(_frun,_f_rms_nshwr_pandoraShower);
rms_shwrlen_pandoraShower->Fill(_frun,_f_rms_shwrlen_pandoraShower);
rms_nhit_tot->Fill(_frun,_f_rms_nhit_tot);
rms_nhit_U->Fill(_frun,_f_rms_nhit_U);
rms_nhit_V->Fill(_frun,_f_rms_nhit_V);
rms_nhit_Y->Fill(_frun,_f_rms_nhit_Y);
rms_hit_ph->Fill(_frun,_f_rms_hit_ph);
rms_hitph_U->Fill(_frun,_f_rms_hitph_U);
rms_hitph_V->Fill(_frun,_f_rms_hitph_V);
rms_hitph_Y->Fill(_frun,_f_rms_hitph_Y);
rms_hit_charge->Fill(_frun,_f_rms_hit_charge);
rms_hitcharge_U->Fill(_frun,_f_rms_hitcharge_U);
rms_hitcharge_V->Fill(_frun,_f_rms_hitcharge_V);
rms_hitcharge_Y->Fill(_frun,_f_rms_hitcharge_Y);
rms_nflashTot_opflashExt->Fill(_frun,_f_rms_nflashTot_opflashExt);
rms_nflashPE50_opflashExt->Fill(_frun,_f_rms_nflashPE50_opflashExt);
rms_nflashPE20_opflashExt->Fill(_frun,_f_rms_nflashPE20_opflashExt);
rms_nflashPE0_20_opflashExt->Fill(_frun,_f_rms_nflashPE0_20_opflashExt);
rms_nflashTot_opflashInt->Fill(_frun,_f_rms_nflashTot_opflashInt);
rms_nflashPE50_opflashInt->Fill(_frun,_f_rms_nflashPE50_opflashInt);
rms_nflashPE20_opflashInt->Fill(_frun,_f_rms_nflashPE20_opflashInt);
rms_nflashPE0_20_opflashInt->Fill(_frun,_f_rms_nflashPE0_20_opflashInt);
rms_flashycenter_opflashExt->Fill(_frun,_f_rms_flashycenter_opflashExt);
rms_flashycenterPE50_opflashExt->Fill(_frun,_f_rms_flashycenterPE50_opflashExt);
rms_flashycenterPE20_opflashExt->Fill(_frun,_f_rms_flashycenterPE20_opflashExt);
rms_flashzcenter_opflashExt->Fill(_frun,_f_rms_flashzcenter_opflashExt);
rms_flashzcenterPE50_opflashExt->Fill(_frun,_f_rms_flashzcenterPE50_opflashExt);
rms_flashzcenterPE20_opflashExt->Fill(_frun,_f_rms_flashzcenterPE20_opflashExt);
rms_flashycenter_opflashInt->Fill(_frun,_f_rms_flashycenter_opflashInt);
rms_flashycenterPE50_opflashInt->Fill(_frun,_f_rms_flashycenterPE50_opflashInt);
rms_flashycenterPE20_opflashInt->Fill(_frun,_f_rms_flashycenterPE20_opflashInt);
rms_flashzcenter_opflashInt->Fill(_frun,_f_rms_flashzcenter_opflashInt);
rms_flashzcenterPE50_opflashInt->Fill(_frun,_f_rms_flashzcenterPE50_opflashInt);
rms_flashzcenterPE20_opflashInt->Fill(_frun,_f_rms_flashzcenterPE20_opflashInt);
rms_flashPE_opflashExt->Fill(_frun,_f_rms_flashPE_opflashExt);
rms_flashPE_opflashInt->Fill(_frun,_f_rms_flashPE_opflashInt);
rms_nvrtx_pmtrack->Fill(_frun,_f_rms_nvrtx_pmtrack);
rms_nvrtx_pandora->Fill(_frun,_f_rms_nvrtx_pandora);
rms_npfps_pmtrack->Fill(_frun,_f_rms_npfps_pmtrack);
rms_npfps_pandora->Fill(_frun,_f_rms_npfps_pandora);
rms_trackpos_beginx_pmtrack->Fill(_frun,_f_rms_trackpos_beginx_pmtrack);
rms_trackpos_beginy_pmtrack->Fill(_frun,_f_rms_trackpos_beginy_pmtrack);
rms_trackpos_beginz_pmtrack->Fill(_frun,_f_rms_trackpos_beginz_pmtrack);
rms_trackpos_endx_pmtrack->Fill(_frun,_f_rms_trackpos_endx_pmtrack);
rms_trackpos_endy_pmtrack->Fill(_frun,_f_rms_trackpos_endy_pmtrack);
rms_trackpos_endz_pmtrack->Fill(_frun,_f_rms_trackpos_endz_pmtrack);
rms_trackpos_beginx_pandoraTrack->Fill(_frun,_f_rms_trackpos_beginx_pandoraTrack);
rms_trackpos_beginy_pandoraTrack->Fill(_frun,_f_rms_trackpos_beginy_pandoraTrack);
rms_trackpos_beginz_pandoraTrack->Fill(_frun,_f_rms_trackpos_beginz_pandoraTrack);
rms_trackpos_endx_pandoraTrack->Fill(_frun,_f_rms_trackpos_endx_pandoraTrack);
rms_trackpos_endy_pandoraTrack->Fill(_frun,_f_rms_trackpos_endy_pandoraTrack);
rms_trackpos_endz_pandoraTrack->Fill(_frun,_f_rms_trackpos_endz_pandoraTrack);
rms_Intflash_ywidth->Fill(_frun,_f_rms_Intflash_ywidth);
rms_Intflash_zwidth->Fill(_frun,_f_rms_Intflash_zwidth);
rms_Extflash_ywidth->Fill(_frun,_f_rms_Extflash_ywidth);
rms_Extflash_zwidth->Fill(_frun,_f_rms_Extflash_zwidth);
}

MCData->GetEntry(0);



TCanvas *C1 = new TCanvas("C1","",1200,600);
C1->SetGridx(1);
C1->SetGridy(1);
C1->Draw();
mean_ntrack_pmtrack->SetTitle("Average number of tracks per event vs run number");
mean_ntrack_pmtrack->GetXaxis()->SetTitle("run number");
mean_ntrack_pmtrack->GetYaxis()->SetTitle("number of tracks per event");
mean_ntrack_pmtrack->SetMarkerColor(kRed);
mean_ntrack_pmtrack->SetMarkerStyle(20);
mean_ntrack_pmtrack->SetMarkerSize(0.8);
mean_ntrack_pmtrack->SetStats(0);
mean_ntrack_pmtrack->Draw("P");
C1->Update();
mean_ntrack_pandoraTrack->SetMarkerColor(kBlue);
mean_ntrack_pandoraTrack->SetMarkerStyle(20);
mean_ntrack_pandoraTrack->SetMarkerSize(0.8);
mean_ntrack_pandoraTrack->SetStats(0);
mean_ntrack_pandoraTrack->Draw("PSAME");

 C1->Update();
 TLine *trackMC_pmtrack=new TLine(C1->GetUxmin(),_f_mean_ntrack_pmtrack_MC,C1->GetUxmax(),_f_mean_ntrack_pmtrack_MC);
 trackMC_pmtrack->SetLineWidth(2);
 trackMC_pmtrack->SetLineColor(kRed);
 trackMC_pmtrack->Draw("SAME");
 C1->Update();
 TLine *trackMC_pandoraTrack=new TLine(C1->GetUxmin(),_f_mean_ntrack_pandoraTrack_MC,C1->GetUxmax(),_f_mean_ntrack_pandoraTrack_MC);
 trackMC_pandoraTrack->SetLineWidth(2);
 trackMC_pandoraTrack->SetLineColor(kBlue);
 trackMC_pandoraTrack->Draw("SAME");

C1->Update();
TLegend* leg_hist1 = new TLegend(0.80,0.70,0.95,0.95); //coordinates are fractions of pad dimensions
leg_hist1->AddEntry(mean_ntrack_pmtrack,"pmtrack data","P");
leg_hist1->AddEntry(mean_ntrack_pandoraTrack,"pandoraTrack data","P");
leg_hist1->AddEntry(trackMC_pmtrack,"pmtrack MC","L");
leg_hist1->AddEntry(trackMC_pandoraTrack,"pandoraTrack MC","L");

leg_hist1->SetFillColor(kWhite);
leg_hist1->Draw();

C1->Print("/Users/zhouyongshun/Desktop/Argonne/Module/StabilityDet/Plots_StabilityDet_V2.1/Plots_withMC/track numbers mean.png");



TCanvas *C2 = new TCanvas("C2","",1200,600);
C2->SetGridx(1);
C2->SetGridy(1);
C2->Draw();
rms_ntrack_pmtrack->SetTitle("Rms of number of tracks per event vs run number");
rms_ntrack_pmtrack->GetXaxis()->SetTitle("run number");
rms_ntrack_pmtrack->GetYaxis()->SetTitle("number of tracks per event");
rms_ntrack_pmtrack->SetMarkerColor(kRed);
rms_ntrack_pmtrack->SetMarkerStyle(20);
rms_ntrack_pmtrack->SetMarkerSize(0.8);
rms_ntrack_pmtrack->SetStats(0);
rms_ntrack_pmtrack->Draw("P");
C2->Update();
rms_ntrack_pandoraTrack->SetMarkerColor(kBlue);
rms_ntrack_pandoraTrack->SetMarkerStyle(20);
rms_ntrack_pandoraTrack->SetMarkerSize(0.8);
rms_ntrack_pandoraTrack->SetStats(0);
rms_ntrack_pandoraTrack->Draw("PSAME");

 C2->Update();
 TLine *trackMC_rms_pmtrack=new TLine(C2->GetUxmin(),_f_rms_ntrack_pmtrack_MC,C2->GetUxmax(),_f_rms_ntrack_pmtrack_MC);
 trackMC_rms_pmtrack->SetLineWidth(2);
 trackMC_rms_pmtrack->SetLineColor(kRed);
 trackMC_rms_pmtrack->Draw("SAME");
 C2->Update();
 TLine *trackMC_rms_pandoraTrack=new TLine(C2->GetUxmin(),_f_rms_ntrack_pandoraTrack_MC,C2->GetUxmax(),_f_rms_ntrack_pandoraTrack_MC);
 trackMC_rms_pandoraTrack->SetLineWidth(2);
 trackMC_rms_pandoraTrack->SetLineColor(kBlue);
 trackMC_rms_pandoraTrack->Draw("SAME");

C2->Update();
TLegend* leg_hist2 = new TLegend(0.80,0.70,0.95,0.95); //coordinates are fractions of pad dimensions
leg_hist2->AddEntry(rms_ntrack_pmtrack,"pmtrack data","P");
leg_hist2->AddEntry(rms_ntrack_pandoraTrack,"pandoraTrack data","P");
leg_hist2->AddEntry(trackMC_rms_pmtrack,"pmtrack MC","L");
leg_hist2->AddEntry(trackMC_rms_pandoraTrack,"pandoraTrack MC","L");

leg_hist2->SetFillColor(kWhite);
leg_hist2->Draw();

C2->Print("/Users/zhouyongshun/Desktop/Argonne/Module/StabilityDet/Plots_StabilityDet_V2.1/Plots_withMC/track numbers rms.png");



TCanvas *C3 = new TCanvas("C3","",1200,600);
C3->SetGridx(1);
C3->SetGridy(1);
C3->Draw();
mean_nshwr_pandoraShower->SetTitle("Average number of pandoraShower per event vs run number");
mean_nshwr_pandoraShower->GetXaxis()->SetTitle("run number");
mean_nshwr_pandoraShower->GetYaxis()->SetTitle("number of pandoraShower per event");
mean_nshwr_pandoraShower->SetMarkerColor(kBlue);
mean_nshwr_pandoraShower->SetMarkerStyle(20);
mean_nshwr_pandoraShower->SetMarkerSize(0.8);
mean_nshwr_pandoraShower->SetStats(0);
mean_nshwr_pandoraShower->Draw();

 C3->Update();
 TLine *trackMC_pandoraShower=new TLine(C3->GetUxmin(),_f_mean_nshwr_pandoraShower_MC,C3->GetUxmax(),_f_mean_nshwr_pandoraShower_MC);
 trackMC_pandoraShower->SetLineWidth(2);
 trackMC_pandoraShower->SetLineColor(kBlue);
 trackMC_pandoraShower->Draw("SAME");

C3->Update();
TLegend* leg_hist3 = new TLegend(0.80,0.70,0.95,0.95); //coordinates are fractions of pad dimensions
leg_hist3->AddEntry(mean_nshwr_pandoraShower,"pandoraShower data","P");
leg_hist3->AddEntry(trackMC_pandoraShower,"pandoraShower MC","L");

leg_hist3->SetFillColor(kWhite);
leg_hist3->Draw();

C3->Print("/Users/zhouyongshun/Desktop/Argonne/Module/StabilityDet/Plots_StabilityDet_V2.1/Plots_withMC/pandoraShower mean.png");



TCanvas *C4 = new TCanvas("C4","",1200,600);
C4->SetGridx(1);
C4->SetGridy(1);
C4->Draw();
rms_nshwr_pandoraShower->SetTitle("Rms of number of pandoraShower per event vs run number");
rms_nshwr_pandoraShower->GetXaxis()->SetTitle("run number");
rms_nshwr_pandoraShower->GetYaxis()->SetTitle("number of pandoraShower per event");
rms_nshwr_pandoraShower->SetMarkerColor(kBlue);
rms_nshwr_pandoraShower->SetMarkerStyle(20);
rms_nshwr_pandoraShower->SetMarkerSize(0.8);
rms_nshwr_pandoraShower->SetStats(0);
rms_nshwr_pandoraShower->Draw();

 C4->Update();
 TLine *trackMC_rms_pandoraShower=new TLine(C4->GetUxmin(),_f_rms_nshwr_pandoraShower,C4->GetUxmax(),_f_rms_nshwr_pandoraShower);
 trackMC_rms_pandoraShower->SetLineWidth(2);
 trackMC_rms_pandoraShower->SetLineColor(kBlue);
 trackMC_rms_pandoraShower->Draw("SAME");

C4->Update();
TLegend* leg_hist4 = new TLegend(0.80,0.70,0.95,0.95); //coordinates are fractions of pad dimensions
leg_hist4->AddEntry(rms_nshwr_pandoraShower,"pandoraShower data","P");
leg_hist4->AddEntry(trackMC_rms_pandoraShower,"pandoraShower MC","L");

leg_hist4->SetFillColor(kWhite);
leg_hist4->Draw();

C4->Print("/Users/zhouyongshun/Desktop/Argonne/Module/StabilityDet/Plots_StabilityDet_V2.1/Plots_withMC/pandoraShower rms.png");



TCanvas *C5 = new TCanvas("C5","",1200,600);
C5->SetGridx(1);
C5->SetGridy(1);
mean_trklen_pmtrack->SetTitle("Average track length per track vs run number");
mean_trklen_pmtrack->GetXaxis()->SetTitle("run number");
mean_trklen_pmtrack->GetYaxis()->SetTitle("track length per track (cm)");
mean_trklen_pmtrack->SetMarkerColor(kRed);
mean_trklen_pmtrack->SetMarkerStyle(20);
mean_trklen_pmtrack->SetMarkerSize(0.8);
mean_trklen_pmtrack->SetStats(0);
mean_trklen_pmtrack->Draw("P");
mean_trklen_pandoraTrack->SetMarkerColor(kBlue);
mean_trklen_pandoraTrack->SetMarkerStyle(20);
mean_trklen_pandoraTrack->SetMarkerSize(0.8);
mean_trklen_pandoraTrack->SetStats(0);
mean_trklen_pandoraTrack->Draw("PSAME");

 C5->Update();
 TLine *trklenMC_pmtrack=new TLine(C5->GetUxmin(),_f_mean_trklen_pmtrack_MC,C5->GetUxmax(),_f_mean_trklen_pmtrack_MC);
 trklenMC_pmtrack->SetLineWidth(2);
 trklenMC_pmtrack->SetLineColor(kRed);
 trklenMC_pmtrack->Draw("SAME");
 C5->Update();
 TLine *trklenMC_pandoraTrack=new TLine(C5->GetUxmin(),_f_mean_trklen_pandoraTrack_MC,C5->GetUxmax(),_f_mean_trklen_pandoraTrack_MC);
 trklenMC_pandoraTrack->SetLineWidth(2);
 trklenMC_pandoraTrack->SetLineColor(kBlue);
 trklenMC_pandoraTrack->Draw("SAME");

 C5->Update();
 TLegend* leg_hist5 = new TLegend(0.80,0.70,0.95,0.95); //coordinates are fractions of pad dimensions
 leg_hist5->AddEntry(mean_trklen_pmtrack,"pmtrack data","P");
 leg_hist5->AddEntry(mean_trklen_pandoraTrack,"pandoraTrack data","P");
 leg_hist5->AddEntry(trklenMC_pmtrack,"pmtrack MC","L");
 leg_hist5->AddEntry(trklenMC_pandoraTrack,"pandoraTrack MC","L");

 leg_hist5->SetFillColor(kWhite);
 leg_hist5->Draw();

C5->Print("/Users/zhouyongshun/Desktop/Argonne/Module/StabilityDet/Plots_StabilityDet_V2.1/Plots_withMC/track length mean.png");



TCanvas *C6 = new TCanvas("C6","",1200,600);
C6->SetGridx(1);
C6->SetGridy(1);
rms_trklen_pmtrack->SetTitle("Rms of track length per track vs run number");
rms_trklen_pmtrack->GetXaxis()->SetTitle("run number");
rms_trklen_pmtrack->GetYaxis()->SetTitle("track length per track (cm)");
rms_trklen_pmtrack->SetMarkerColor(kRed);
rms_trklen_pmtrack->SetMarkerStyle(20);
rms_trklen_pmtrack->SetMarkerSize(0.8);
rms_trklen_pmtrack->SetStats(0);
rms_trklen_pmtrack->Draw("P");
rms_trklen_pandoraTrack->SetMarkerColor(kBlue);
rms_trklen_pandoraTrack->SetMarkerStyle(20);
rms_trklen_pandoraTrack->SetMarkerSize(0.8);
rms_trklen_pandoraTrack->SetStats(0);
rms_trklen_pandoraTrack->Draw("PSAME");

 C6->Update();
 TLine *trklenMC_rms_pmtrack=new TLine(C6->GetUxmin(),_f_rms_trklen_pmtrack_MC,C6->GetUxmax(),_f_rms_trklen_pmtrack_MC);
 trklenMC_rms_pmtrack->SetLineWidth(2);
 trklenMC_rms_pmtrack->SetLineColor(kRed);
 trklenMC_rms_pmtrack->Draw("SAME");
 C6->Update();
 TLine *trklenMC_rms_pandoraTrack=new TLine(C6->GetUxmin(),_f_rms_trklen_pandoraTrack_MC,C6->GetUxmax(),_f_rms_trklen_pandoraTrack_MC);
 trklenMC_rms_pandoraTrack->SetLineWidth(2);
 trklenMC_rms_pandoraTrack->SetLineColor(kBlue);
 trklenMC_rms_pandoraTrack->Draw("SAME");

 C6->Update();
 TLegend* leg_hist6 = new TLegend(0.80,0.70,0.95,0.95); //coordinates are fractions of pad dimensions
 leg_hist6->AddEntry(rms_trklen_pmtrack,"pmtrack data","P");
 leg_hist6->AddEntry(rms_trklen_pandoraTrack,"pandoraTrack data","P");
 leg_hist6->AddEntry(trklenMC_rms_pmtrack,"pmtrack MC","L");
 leg_hist6->AddEntry(trklenMC_rms_pandoraTrack,"pandoraTrack MC","L");

 leg_hist6->SetFillColor(kWhite);
 leg_hist6->Draw();

C6->Print("/Users/zhouyongshun/Desktop/Argonne/Module/StabilityDet/Plots_StabilityDet_V2.1/Plots_withMC/track length rms.png");



TCanvas *C7 = new TCanvas("C7","",1200,600);
C7->SetGridx(1);
C7->SetGridy(1);
mean_nhit_tot->SetTitle("Average number of hits per event vs run number");
mean_nhit_tot->GetXaxis()->SetTitle("run number");
mean_nhit_tot->GetYaxis()->SetTitle("number of hits per event");
mean_nhit_tot->SetMarkerColor(kBlack);
mean_nhit_tot->SetMarkerStyle(20);
mean_nhit_tot->SetMarkerSize(0.8);
mean_nhit_tot->SetStats(0);
mean_nhit_tot->Draw("P");
mean_nhit_U->SetMarkerColor(kBlue);
mean_nhit_U->SetMarkerStyle(20);
mean_nhit_U->SetMarkerSize(0.8);
mean_nhit_U->SetStats(0);
mean_nhit_U->Draw("PSAME");
mean_nhit_V->SetMarkerColor(kGreen);
mean_nhit_V->SetMarkerStyle(20);
mean_nhit_V->SetMarkerSize(0.8);
mean_nhit_V->SetStats(0);
mean_nhit_V->Draw("PSAME");
mean_nhit_Y->SetMarkerColor(kRed);
mean_nhit_Y->SetMarkerStyle(20);
mean_nhit_Y->SetMarkerSize(0.8);
mean_nhit_Y->SetStats(0);
mean_nhit_Y->Draw("PSAME");

 C7->Update();
 TLine *hitMC=new TLine(C7->GetUxmin(),_f_mean_nhit_tot_MC,C7->GetUxmax(),_f_mean_nhit_tot_MC);
 hitMC->SetLineWidth(2);
 hitMC->SetLineColor(kBlack);
 hitMC->Draw("SAME");
 C7->Update();
 TLine *hitUMC=new TLine(C7->GetUxmin(),_f_mean_nhit_U_MC,C7->GetUxmax(),_f_mean_nhit_U_MC);
 hitUMC->SetLineWidth(2);
 hitUMC->SetLineColor(kBlue);
 hitUMC->Draw("SAME");
 C7->Update();
 TLine *hitVMC=new TLine(C7->GetUxmin(),_f_mean_nhit_V_MC,C7->GetUxmax(),_f_mean_nhit_V_MC);
 hitVMC->SetLineWidth(2);
 hitVMC->SetLineColor(kGreen);
 hitVMC->Draw("SAME");
 C7->Update();
 TLine *hitYMC=new TLine(C7->GetUxmin(),_f_mean_nhit_Y_MC,C7->GetUxmax(),_f_mean_nhit_Y_MC);
 hitYMC->SetLineWidth(2);
 hitYMC->SetLineColor(kRed);
 hitYMC->Draw("SAME");

 C7->Update();
 TLegend* leg_hist7 = new TLegend(0.80,0.70,0.95,0.95); //coordinates are fractions of pad dimensions
 leg_hist7->AddEntry(mean_nhit_tot,"all planes data","P");
 leg_hist7->AddEntry(mean_nhit_U,"U-plane data","P");
 leg_hist7->AddEntry(mean_nhit_V,"V-plane data","P");
 leg_hist7->AddEntry(mean_nhit_Y,"Y-plane data","P");
 leg_hist7->AddEntry(hitMC,"all planes MC","L");
 leg_hist7->AddEntry(hitUMC,"U-plane MC","L");
 leg_hist7->AddEntry(hitVMC,"V-plane MC","L");
 leg_hist7->AddEntry(hitYMC,"Y-plane MC","L");
 leg_hist7->SetFillColor(kWhite);
 leg_hist7->Draw();

C7->Print("/Users/zhouyongshun/Desktop/Argonne/Module/StabilityDet/Plots_StabilityDet_V2.1/Plots_withMC/number of hits mean.png");



TCanvas *C8 = new TCanvas("C8","",1200,600);
C8->SetGridx(1);
C8->SetGridy(1);
rms_nhit_tot->SetTitle("Rms of number of hits per event vs run number");
rms_nhit_tot->GetXaxis()->SetTitle("run number");
rms_nhit_tot->GetYaxis()->SetTitle("number of hits per event");
rms_nhit_tot->SetMarkerColor(kBlack);
rms_nhit_tot->SetMarkerStyle(20);
rms_nhit_tot->SetMarkerSize(0.8);
rms_nhit_tot->SetStats(0);
rms_nhit_tot->Draw("P");
rms_nhit_U->SetMarkerColor(kBlue);
rms_nhit_U->SetMarkerStyle(20);
rms_nhit_U->SetMarkerSize(0.8);
rms_nhit_U->SetStats(0);
rms_nhit_U->Draw("PSAME");
rms_nhit_V->SetMarkerColor(kGreen);
rms_nhit_V->SetMarkerStyle(20);
rms_nhit_V->SetMarkerSize(0.8);
rms_nhit_V->SetStats(0);
rms_nhit_V->Draw("PSAME");
rms_nhit_Y->SetMarkerColor(kRed);
rms_nhit_Y->SetMarkerStyle(20);
rms_nhit_Y->SetMarkerSize(0.8);
rms_nhit_Y->SetStats(0);
rms_nhit_Y->Draw("PSAME");

 C8->Update();
 TLine *hitMC_rms=new TLine(C8->GetUxmin(),_f_rms_nhit_tot_MC,C8->GetUxmax(),_f_rms_nhit_tot_MC);
 hitMC_rms->SetLineWidth(2);
 hitMC_rms->SetLineColor(kBlack);
 hitMC_rms->Draw("SAME");
 C8->Update();
 TLine *hitUMC_rms=new TLine(C8->GetUxmin(),_f_rms_nhit_U_MC,C8->GetUxmax(),_f_rms_nhit_U_MC);
 hitUMC_rms->SetLineWidth(2);
 hitUMC_rms->SetLineColor(kBlue);
 hitUMC_rms->Draw("SAME");
 C8->Update();
 TLine *hitVMC_rms=new TLine(C8->GetUxmin(),_f_rms_nhit_V_MC,C8->GetUxmax(),_f_rms_nhit_V_MC);
 hitVMC_rms->SetLineWidth(2);
 hitVMC_rms->SetLineColor(kGreen);
 hitVMC_rms->Draw("SAME");
 C8->Update();
 TLine *hitYMC_rms=new TLine(C8->GetUxmin(),_f_rms_nhit_Y_MC,C8->GetUxmax(),_f_rms_nhit_Y_MC);
 hitYMC_rms->SetLineWidth(2);
 hitYMC_rms->SetLineColor(kRed);
 hitYMC_rms->Draw("SAME");

 C8->Update();
 TLegend* leg_hist8 = new TLegend(0.80,0.70,0.95,0.95); //coordinates are fractions of pad dimensions
 leg_hist8->AddEntry(rms_nhit_tot,"all planes data","P");
 leg_hist8->AddEntry(rms_nhit_U,"U-plane data","P");
 leg_hist8->AddEntry(rms_nhit_V,"V-plane data","P");
 leg_hist8->AddEntry(rms_nhit_Y,"Y-plane data","P");
 leg_hist8->AddEntry(hitMC_rms,"all planes MC","L");
 leg_hist8->AddEntry(hitUMC_rms,"U-plane MC","L");
 leg_hist8->AddEntry(hitVMC_rms,"V-plane MC","L");
 leg_hist8->AddEntry(hitYMC_rms,"Y-plane MC","L");
 leg_hist8->SetFillColor(kWhite);
 leg_hist8->Draw();

C8->Print("/Users/zhouyongshun/Desktop/Argonne/Module/StabilityDet/Plots_StabilityDet_V2.1/Plots_withMC/number of hits rms.png");



TCanvas *C9 = new TCanvas("C9","",1200,600);
C9->SetGridx(1);
C9->SetGridy(1);
mean_hit_ph->SetTitle("Average hit peak amplitude per hit vs run number");
mean_hit_ph->GetXaxis()->SetTitle("run number");
mean_hit_ph->GetYaxis()->SetTitle("hit peak amplitude per hit (PE)");
mean_hit_ph->SetMarkerColor(kBlack);
mean_hit_ph->SetMarkerStyle(20);
mean_hit_ph->SetMarkerSize(0.8);
mean_hit_ph->SetStats(0);
mean_hit_ph->Draw("P");
mean_hitph_U->SetMarkerColor(kBlue);
mean_hitph_U->SetMarkerStyle(20);
mean_hitph_U->SetMarkerSize(0.8);
mean_hitph_U->SetStats(0);
mean_hitph_U->Draw("PSAME");
mean_hitph_V->SetMarkerColor(kGreen);
mean_hitph_V->SetMarkerStyle(20);
mean_hitph_V->SetMarkerSize(0.8);
mean_hitph_V->SetStats(0);
mean_hitph_V->Draw("PSAME");
mean_hitph_Y->SetMarkerColor(kRed);
mean_hitph_Y->SetMarkerStyle(20);
mean_hitph_Y->SetMarkerSize(0.8);
mean_hitph_Y->SetStats(0);
mean_hitph_Y->Draw("PSAME");

 C9->Update();
 TLine *hitphMC_mean=new TLine(C9->GetUxmin(),_f_mean_hit_ph_MC,C9->GetUxmax(),_f_mean_hit_ph_MC);
 hitphMC_mean->SetLineWidth(2);
 hitphMC_mean->SetLineColor(kBlack);
 hitphMC_mean->Draw("SAME");
 C9->Update();
 TLine *hitphUMC_mean=new TLine(C9->GetUxmin(),_f_mean_hitph_U_MC,C9->GetUxmax(),_f_mean_hitph_U_MC);
 hitphUMC_mean->SetLineWidth(2);
 hitphUMC_mean->SetLineColor(kBlue);
 hitphUMC_mean->Draw("SAME");
 C9->Update();
 TLine *hitphVMC_mean=new TLine(C9->GetUxmin(),_f_mean_hitph_V_MC,C9->GetUxmax(),_f_mean_hitph_V_MC);
 hitphVMC_mean->SetLineWidth(2);
 hitphVMC_mean->SetLineColor(kGreen);
 hitphVMC_mean->Draw("SAME");
 C9->Update();
 TLine *hitphYMC_mean=new TLine(C9->GetUxmin(),_f_mean_hitph_Y_MC,C9->GetUxmax(),_f_mean_hitph_Y_MC);
 hitphYMC_mean->SetLineWidth(2);
 hitphYMC_mean->SetLineColor(kRed);
 hitphYMC_mean->Draw("SAME");

 C9->Update();
 TLegend* leg_hist9 = new TLegend(0.80,0.70,0.95,0.95); //coordinates are fractions of pad dimensions
 leg_hist9->AddEntry(mean_hit_ph,"all planes data","P");
 leg_hist9->AddEntry(mean_hitph_U,"U-plane data","P");
 leg_hist9->AddEntry(mean_hitph_V,"V-plane data","P");
 leg_hist9->AddEntry(mean_hitph_Y,"Y-plane data","P");
 leg_hist9->AddEntry(hitphMC_mean,"all planes MC","L");
 leg_hist9->AddEntry(hitphUMC_mean,"U-plane MC","L");
 leg_hist9->AddEntry(hitphVMC_mean,"V-plane MC","L");
 leg_hist9->AddEntry(hitphYMC_mean,"Y-plane MC","L");
 leg_hist9->SetFillColor(kWhite);
 leg_hist9->Draw();

C9->Print("/Users/zhouyongshun/Desktop/Argonne/Module/StabilityDet/Plots_StabilityDet_V2.1/Plots_withMC/hitphs mean.png");



TCanvas *C10 = new TCanvas("C10","",1200,600);
C10->SetGridx(1);
C10->SetGridy(1);
rms_hit_ph->SetTitle("Rms of hit peak amplitude per hit vs run number");
rms_hit_ph->GetXaxis()->SetTitle("run number");
rms_hit_ph->GetYaxis()->SetTitle("hit peak amplitude per hit (PE)");
rms_hit_ph->SetMarkerColor(kBlack);
rms_hit_ph->SetMarkerStyle(20);
rms_hit_ph->SetMarkerSize(0.8);
rms_hit_ph->SetStats(0);
rms_hit_ph->Draw("P");
rms_hitph_U->SetMarkerColor(kBlue);
rms_hitph_U->SetMarkerStyle(20);
rms_hitph_U->SetMarkerSize(0.8);
rms_hitph_U->SetStats(0);
rms_hitph_U->Draw("PSAME");
rms_hitph_V->SetMarkerColor(kGreen);
rms_hitph_V->SetMarkerStyle(20);
rms_hitph_V->SetMarkerSize(0.8);
rms_hitph_V->SetStats(0);
rms_hitph_V->Draw("PSAME");
rms_hitph_Y->SetMarkerColor(kRed);
rms_hitph_Y->SetMarkerStyle(20);
rms_hitph_Y->SetMarkerSize(0.8);
rms_hitph_Y->SetStats(0);
rms_hitph_Y->Draw("PSAME");

 C10->Update();
 TLine *hitphMC_rms=new TLine(C10->GetUxmin(),_f_rms_hit_ph_MC,C10->GetUxmax(),_f_rms_hit_ph_MC);
 hitphMC_rms->SetLineWidth(2);
 hitphMC_rms->SetLineColor(kBlack);
 hitphMC_rms->Draw("SAME");
 C10->Update();
 TLine *hitphUMC_rms=new TLine(C10->GetUxmin(),_f_rms_hitph_U_MC,C10->GetUxmax(),_f_rms_hitph_U_MC);
 hitphUMC_rms->SetLineWidth(2);
 hitphUMC_rms->SetLineColor(kBlue);
 hitphUMC_rms->Draw("SAME");
 C10->Update();
 TLine *hitphVMC_rms=new TLine(C10->GetUxmin(),_f_rms_hitph_V_MC,C10->GetUxmax(),_f_rms_hitph_V_MC);
 hitphVMC_rms->SetLineWidth(2);
 hitphVMC_rms->SetLineColor(kGreen);
 hitphVMC_rms->Draw("SAME");
 C10->Update();
 TLine *hitphYMC_rms=new TLine(C10->GetUxmin(),_f_rms_hitph_Y_MC,C10->GetUxmax(),_f_rms_hitph_Y_MC);
 hitphYMC_rms->SetLineWidth(2);
 hitphYMC_rms->SetLineColor(kRed);
 hitphYMC_rms->Draw("SAME");

 C10->Update();
 TLegend* leg_hist10 = new TLegend(0.80,0.70,0.95,0.95); //coordinates are fractions of pad dimensions
 leg_hist10->AddEntry(rms_hit_ph,"all planes data","P");
 leg_hist10->AddEntry(rms_hitph_U,"U-plane data","P");
 leg_hist10->AddEntry(rms_hitph_V,"V-plane data","P");
 leg_hist10->AddEntry(rms_hitph_Y,"Y-plane data","P");
 leg_hist10->AddEntry(hitphMC_rms,"all planes MC","L");
 leg_hist10->AddEntry(hitphUMC_rms,"U-plane MC","L");
 leg_hist10->AddEntry(hitphVMC_rms,"V-plane MC","L");
 leg_hist10->AddEntry(hitphYMC_rms,"Y-plane MC","L");
 leg_hist10->SetFillColor(kWhite);
 leg_hist10->Draw();

C10->Print("/Users/zhouyongshun/Desktop/Argonne/Module/StabilityDet/Plots_StabilityDet_V2.1/Plots_withMC/hitphs rms.png");



TCanvas *C11 = new TCanvas("C11","",1200,600);
C11->SetGridx(1);
C11->SetGridy(1);
mean_hit_charge->SetTitle("Average hit charge per hit vs run number");
mean_hit_charge->GetXaxis()->SetTitle("run number");
mean_hit_charge->GetYaxis()->SetTitle("hit charge per hit (ADC)");
mean_hit_charge->SetMarkerColor(kBlack);
mean_hit_charge->SetMarkerStyle(20);
mean_hit_charge->SetMarkerSize(0.8);
mean_hit_charge->SetStats(0);
mean_hit_charge->Draw("P");
mean_hitcharge_U->SetMarkerColor(kBlue);
mean_hitcharge_U->SetMarkerStyle(20);
mean_hitcharge_U->SetMarkerSize(0.8);
mean_hitcharge_U->SetStats(0);
mean_hitcharge_U->Draw("PSAME");
mean_hitcharge_V->SetMarkerColor(kGreen);
mean_hitcharge_V->SetMarkerStyle(20);
mean_hitcharge_V->SetMarkerSize(0.8);
mean_hitcharge_V->SetStats(0);
mean_hitcharge_V->Draw("PSAME");
mean_hitcharge_Y->SetMarkerColor(kRed);
mean_hitcharge_Y->SetMarkerStyle(20);
mean_hitcharge_Y->SetMarkerSize(0.8);
mean_hitcharge_Y->SetStats(0);
mean_hitcharge_Y->Draw("PSAME");

 C11->Update();
 TLine *hitchargeMC_mean=new TLine(C11->GetUxmin(),_f_mean_hit_charge_MC,C11->GetUxmax(),_f_mean_hit_charge_MC);
 hitchargeMC_mean->SetLineWidth(2);
 hitchargeMC_mean->SetLineColor(kBlack);
 hitchargeMC_mean->Draw("SAME");
 C11->Update();
 TLine *hitchargeUMC_mean=new TLine(C11->GetUxmin(),_f_mean_hitcharge_U_MC,C11->GetUxmax(),_f_mean_hitcharge_U_MC);
 hitchargeUMC_mean->SetLineWidth(2);
 hitchargeUMC_mean->SetLineColor(kBlue);
 hitchargeUMC_mean->Draw("SAME");
 C11->Update();
 TLine *hitchargeVMC_mean=new TLine(C11->GetUxmin(),_f_mean_hitcharge_V_MC,C11->GetUxmax(),_f_mean_hitcharge_V_MC);
 hitchargeVMC_mean->SetLineWidth(2);
 hitchargeVMC_mean->SetLineColor(kGreen);
 hitchargeVMC_mean->Draw("SAME");
 C11->Update();
 TLine *hitchargeYMC_mean=new TLine(C11->GetUxmin(),_f_mean_hitcharge_Y_MC,C11->GetUxmax(),_f_mean_hitcharge_Y_MC);
 hitchargeYMC_mean->SetLineWidth(2);
 hitchargeYMC_mean->SetLineColor(kRed);
 hitchargeYMC_mean->Draw("SAME");

 C11->Update();
 TLegend* leg_hist11 = new TLegend(0.80,0.70,0.95,0.95); //coordinates are fractions of pad dimensions
 leg_hist11->AddEntry(mean_hit_charge,"all planes data","P");
 leg_hist11->AddEntry(mean_hitcharge_U,"U-plane data","P");
 leg_hist11->AddEntry(mean_hitcharge_V,"V-plane data","P");
 leg_hist11->AddEntry(mean_hitcharge_Y,"Y-plane data","P");
 leg_hist11->AddEntry(hitchargeMC_mean,"all planes MC","L");
 leg_hist11->AddEntry(hitchargeUMC_mean,"U-plane MC","L");
 leg_hist11->AddEntry(hitchargeVMC_mean,"V-plane MC","L");
 leg_hist11->AddEntry(hitchargeYMC_mean,"Y-plane MC","L");
 leg_hist11->SetFillColor(kWhite);
 leg_hist11->Draw();

C11->Print("/Users/zhouyongshun/Desktop/Argonne/Module/StabilityDet/Plots_StabilityDet_V2.1/Plots_withMC/hit charge mean.png");



TCanvas *C12 = new TCanvas("C12","",1200,600);
C12->SetGridx(1);
C12->SetGridy(1);
rms_hit_charge->SetTitle("Rms of hit charge per hit vs run number");
rms_hit_charge->GetXaxis()->SetTitle("run number");
rms_hit_charge->GetYaxis()->SetTitle("hit charge per hit (ADC)");
rms_hit_charge->SetMarkerColor(kBlack);
rms_hit_charge->SetMarkerStyle(20);
rms_hit_charge->SetMarkerSize(0.8);
rms_hit_charge->SetStats(0);
rms_hit_charge->Draw("P");
rms_hitcharge_U->SetMarkerColor(kBlue);
rms_hitcharge_U->SetMarkerStyle(20);
rms_hitcharge_U->SetMarkerSize(0.8);
rms_hitcharge_U->SetStats(0);
rms_hitcharge_U->Draw("PSAME");
rms_hitcharge_V->SetMarkerColor(kGreen);
rms_hitcharge_V->SetMarkerStyle(20);
rms_hitcharge_V->SetMarkerSize(0.8);
rms_hitcharge_V->SetStats(0);
rms_hitcharge_V->Draw("PSAME");
rms_hitcharge_Y->SetMarkerColor(kRed);
rms_hitcharge_Y->SetMarkerStyle(20);
rms_hitcharge_Y->SetMarkerSize(0.8);
rms_hitcharge_Y->SetStats(0);
rms_hitcharge_Y->Draw("PSAME");

 C12->Update();
 TLine *hitchargeMC_rms=new TLine(C12->GetUxmin(),_f_rms_hit_charge_MC,C12->GetUxmax(),_f_rms_hit_charge_MC);
 hitchargeMC_rms->SetLineWidth(2);
 hitchargeMC_rms->SetLineColor(kBlack);
 hitchargeMC_rms->Draw("SAME");
 C12->Update();
 TLine *hitchargeUMC_rms=new TLine(C12->GetUxmin(),_f_rms_hitcharge_U_MC,C12->GetUxmax(),_f_rms_hitcharge_U_MC);
 hitchargeUMC_rms->SetLineWidth(2);
 hitchargeUMC_rms->SetLineColor(kBlue);
 hitchargeUMC_rms->Draw("SAME");
 C12->Update();
 TLine *hitchargeVMC_rms=new TLine(C12->GetUxmin(),_f_rms_hitcharge_V_MC,C12->GetUxmax(),_f_rms_hitcharge_V_MC);
 hitchargeVMC_rms->SetLineWidth(2);
 hitchargeVMC_rms->SetLineColor(kGreen);
 hitchargeVMC_rms->Draw("SAME");
 C12->Update();
 TLine *hitchargeYMC_rms=new TLine(C12->GetUxmin(),_f_rms_hitcharge_Y_MC,C12->GetUxmax(),_f_rms_hitcharge_Y_MC);
 hitchargeYMC_rms->SetLineWidth(2);
 hitchargeYMC_rms->SetLineColor(kRed);
 hitchargeYMC_rms->Draw("SAME");

 C12->Update();
 TLegend* leg_hist12 = new TLegend(0.80,0.70,0.95,0.95); //coordinates are fractions of pad dimensions
 leg_hist12->AddEntry(rms_hit_charge,"all planes data","P");
 leg_hist12->AddEntry(rms_hitcharge_U,"U-plane data","P");
 leg_hist12->AddEntry(rms_hitcharge_V,"V-plane data","P");
 leg_hist12->AddEntry(rms_hitcharge_Y,"Y-plane data","P");
 leg_hist12->AddEntry(hitchargeMC_rms,"all planes MC","L");
 leg_hist12->AddEntry(hitchargeUMC_rms,"U-plane MC","L");
 leg_hist12->AddEntry(hitchargeVMC_rms,"V-plane MC","L");
 leg_hist12->AddEntry(hitchargeYMC_rms,"Y-plane MC","L");
 leg_hist12->SetFillColor(kWhite);
 leg_hist12->Draw();

C12->Print("/Users/zhouyongshun/Desktop/Argonne/Module/StabilityDet/Plots_StabilityDet_V2.1/Plots_withMC/hit charge rms.png");



TCanvas *C13 = new TCanvas("C13","",1200,600);
C13->SetGridx(1);
C13->SetGridy(1);
mean_nflashTot_opflashExt->SetTitle("Average number of external opflashes per event vs run number");
mean_nflashTot_opflashExt->GetXaxis()->SetTitle("run number");
mean_nflashTot_opflashExt->GetYaxis()->SetTitle("number of external opflashes per event");
mean_nflashTot_opflashExt->SetMarkerColor(kBlack);
mean_nflashTot_opflashExt->SetMarkerStyle(20);
mean_nflashTot_opflashExt->SetMarkerSize(0.8);
mean_nflashTot_opflashExt->SetStats(0);
mean_nflashTot_opflashExt->Draw("P");
mean_nflashPE50_opflashExt->SetMarkerColor(kBlue);
mean_nflashPE50_opflashExt->SetMarkerStyle(20);
mean_nflashPE50_opflashExt->SetMarkerSize(0.8);
mean_nflashPE50_opflashExt->SetStats(0);
mean_nflashPE50_opflashExt->Draw("PSAME");
mean_nflashPE20_opflashExt->SetMarkerColor(kGreen);
mean_nflashPE20_opflashExt->SetMarkerStyle(20);
mean_nflashPE20_opflashExt->SetMarkerSize(0.8);
mean_nflashPE20_opflashExt->SetStats(0);
mean_nflashPE20_opflashExt->Draw("PSAME");
mean_nflashPE0_20_opflashExt->SetMarkerColor(kRed);
mean_nflashPE0_20_opflashExt->SetMarkerStyle(20);
mean_nflashPE0_20_opflashExt->SetMarkerSize(0.8);
mean_nflashPE0_20_opflashExt->SetStats(0);
mean_nflashPE0_20_opflashExt->Draw("PSAME");

 /*C13->Update();
 TLine *nflashExtTotMC_mean=new TLine(C13->GetUxmin(),_f_mean_nflashTot_opflashExt_MC,C13->GetUxmax(),_f_mean_nflashTot_opflashExt_MC);
 nflashExtTotMC_mean->SetLineWidth(2);
 nflashExtTotMC_mean->SetLineColor(kBlack);
 nflashExtTotMC_mean->Draw("SAME");
 C13->Update();
 TLine *nflashExtPE50MC_mean=new TLine(C13->GetUxmin(),_f_mean_nflashPE50_opflashExt_MC,C13->GetUxmax(),_f_mean_nflashPE50_opflashExt_MC);
 nflashExtPE50MC_mean->SetLineWidth(2);
 nflashExtPE50MC_mean->SetLineColor(kBlue);
 nflashExtPE50MC_mean->Draw("SAME");
 C13->Update();
 TLine *nflashExtPE20MC_mean=new TLine(C13->GetUxmin(),_f_mean_nflashPE20_opflashExt_MC,C13->GetUxmax(),_f_mean_nflashPE20_opflashExt_MC);
 nflashExtPE20MC_mean->SetLineWidth(2);
 nflashExtPE20MC_mean->SetLineColor(kGreen);
 nflashExtPE20MC_mean->Draw("SAME");
 C13->Update();
 TLine *nflashExtPE0_20MC_mean=new TLine(C13->GetUxmin(),_f_mean_nflashPE0_20_opflashExt_MC,C13->GetUxmax(),_f_mean_nflashPE0_20_opflashExt_MC);
 nflashExtPE0_20MC_mean->SetLineWidth(2);
 nflashExtPE0_20MC_mean->SetLineColor(kRed);
 nflashExtPE0_20MC_mean->Draw("SAME");*/

 C13->Update();
 TLegend* leg_hist13 = new TLegend(0.80,0.70,0.95,0.95); //coordinates are fractions of pad dimensions
 leg_hist13->AddEntry(mean_nflashTot_opflashExt,"All PE data","P");
 leg_hist13->AddEntry(mean_nflashPE50_opflashExt,"> 50 PE data","P");
 leg_hist13->AddEntry(mean_nflashPE20_opflashExt,"> 20 PE data","P");
 leg_hist13->AddEntry(mean_nflashPE0_20_opflashExt,"< 20 PE data","P");
 /*leg_hist13->AddEntry(nflashExtTotMC_mean,"All PE MC","L");
 leg_hist13->AddEntry(nflashExtPE50MC_mean,"> 50 PE MC","L");
 leg_hist13->AddEntry(nflashExtPE20MC_mean,"> 20 PE MC","L");
 leg_hist13->AddEntry(nflashExtPE0_20MC_mean,"< 20 PE MC","L");*/
 leg_hist13->SetFillColor(kWhite);
 leg_hist13->Draw();

C13->Print("/Users/zhouyongshun/Desktop/Argonne/Module/StabilityDet/Plots_StabilityDet_V2.1/Plots_withMC/external opflashes mean.png");



TCanvas *C14 = new TCanvas("C14","",1200,600);
C14->SetGridx(1);
C14->SetGridy(1);
rms_nflashTot_opflashExt->SetTitle("Rms of number of external opflashes per event vs run number");
rms_nflashTot_opflashExt->GetXaxis()->SetTitle("run number");
rms_nflashTot_opflashExt->GetYaxis()->SetTitle("number of external opflashes per event");
rms_nflashTot_opflashExt->SetMarkerColor(kBlack);
rms_nflashTot_opflashExt->SetMarkerStyle(20);
rms_nflashTot_opflashExt->SetMarkerSize(0.8);
rms_nflashTot_opflashExt->SetStats(0);
rms_nflashTot_opflashExt->Draw("P");
rms_nflashPE50_opflashExt->SetMarkerColor(kBlue);
rms_nflashPE50_opflashExt->SetMarkerStyle(20);
rms_nflashPE50_opflashExt->SetMarkerSize(0.8);
rms_nflashPE50_opflashExt->SetStats(0);
rms_nflashPE50_opflashExt->Draw("PSAME");
rms_nflashPE20_opflashExt->SetMarkerColor(kGreen);
rms_nflashPE20_opflashExt->SetMarkerStyle(20);
rms_nflashPE20_opflashExt->SetMarkerSize(0.8);
rms_nflashPE20_opflashExt->SetStats(0);
rms_nflashPE20_opflashExt->Draw("PSAME");
rms_nflashPE0_20_opflashExt->SetMarkerColor(kRed);
rms_nflashPE0_20_opflashExt->SetMarkerStyle(20);
rms_nflashPE0_20_opflashExt->SetMarkerSize(0.8);
rms_nflashPE0_20_opflashExt->SetStats(0);
rms_nflashPE0_20_opflashExt->Draw("PSAME");

 /*C14->Update();
 TLine *nflashExtTotMC_rms=new TLine(C14->GetUxmin(),_f_rms_nflashTot_opflashExt_MC,C14->GetUxmax(),_f_rms_nflashTot_opflashExt_MC);
 nflashExtTotMC_rms->SetLineWidth(2);
 nflashExtTotMC_rms->SetLineColor(kBlack);
 nflashExtTotMC_rms->Draw("SAME");
 C14->Update();
 TLine *nflashExtPE50MC_rms=new TLine(C14->GetUxmin(),_f_rms_nflashPE50_opflashExt_MC,C14->GetUxmax(),_f_rms_nflashPE50_opflashExt_MC);
 nflashExtPE50MC_rms->SetLineWidth(2);
 nflashExtPE50MC_rms->SetLineColor(kBlue);
 nflashExtPE50MC_rms->Draw("SAME");
 C14->Update();
 TLine *nflashExtPE20MC_rms=new TLine(C14->GetUxmin(),_f_rms_nflashPE20_opflashExt_MC,C14->GetUxmax(),_f_rms_nflashPE20_opflashExt_MC);
 nflashExtPE20MC_rms->SetLineWidth(2);
 nflashExtPE20MC_rms->SetLineColor(kGreen);
 nflashExtPE20MC_rms->Draw("SAME");
 C14->Update();
 TLine *nflashExtPE0_20MC_rms=new TLine(C14->GetUxmin(),_f_rms_nflashPE0_20_opflashExt_MC,C14->GetUxmax(),_f_rms_nflashPE0_20_opflashExt_MC);
 nflashExtPE0_20MC_rms->SetLineWidth(2);
 nflashExtPE0_20MC_rms->SetLineColor(kRed);
 nflashExtPE0_20MC_rms->Draw("SAME");*/

 C14->Update();
 TLegend* leg_hist14 = new TLegend(0.80,0.70,0.95,0.95); //coordinates are fractions of pad dimensions
 leg_hist14->AddEntry(rms_nflashTot_opflashExt,"All PE data","P");
 leg_hist14->AddEntry(rms_nflashPE50_opflashExt,"> 50 PE data","P");
 leg_hist14->AddEntry(rms_nflashPE20_opflashExt,"> 20 PE data","P");
 leg_hist14->AddEntry(rms_nflashPE0_20_opflashExt,"< 20 PE data","P");
 /*leg_hist14->AddEntry(nflashExtTotMC_rms,"All PE MC","L");
 leg_hist14->AddEntry(nflashExtPE50MC_rms,"> 50 PE MC","L");
 leg_hist14->AddEntry(nflashExtPE20MC_rms,"> 20 PE MC","L");
 leg_hist14->AddEntry(nflashExtPE0_20MC_rms,"< 20 PE MC","L");*/
 leg_hist14->SetFillColor(kWhite);
 leg_hist14->Draw();

C14->Print("/Users/zhouyongshun/Desktop/Argonne/Module/StabilityDet/Plots_StabilityDet_V2.1/Plots_withMC/external opflashes rms.png");



TCanvas *C15 = new TCanvas("C15","",1200,600);
C15->SetGridx(1);
C15->SetGridy(1);
mean_nflashTot_opflashInt->SetTitle("Average number of internal opflashes per event vs run number");
mean_nflashTot_opflashInt->GetXaxis()->SetTitle("run number");
mean_nflashTot_opflashInt->GetYaxis()->SetTitle("number of internal opflashes per event");
mean_nflashTot_opflashInt->SetMarkerColor(kBlack);
mean_nflashTot_opflashInt->SetMarkerStyle(20);
mean_nflashTot_opflashInt->SetMarkerSize(0.8);
mean_nflashTot_opflashInt->SetStats(0);
mean_nflashTot_opflashInt->Draw("P");
mean_nflashPE50_opflashInt->SetMarkerColor(kBlue);
mean_nflashPE50_opflashInt->SetMarkerStyle(20);
mean_nflashPE50_opflashInt->SetMarkerSize(0.8);
mean_nflashPE50_opflashInt->SetStats(0);
mean_nflashPE50_opflashInt->Draw("PSAME");
mean_nflashPE20_opflashInt->SetMarkerColor(kGreen);
mean_nflashPE20_opflashInt->SetMarkerStyle(20);
mean_nflashPE20_opflashInt->SetMarkerSize(0.8);
mean_nflashPE20_opflashInt->SetStats(0);
mean_nflashPE20_opflashInt->Draw("PSAME");
mean_nflashPE0_20_opflashInt->SetMarkerColor(kRed);
mean_nflashPE0_20_opflashInt->SetMarkerStyle(20);
mean_nflashPE0_20_opflashInt->SetMarkerSize(0.8);
mean_nflashPE0_20_opflashInt->SetStats(0);
mean_nflashPE0_20_opflashInt->Draw("PSAME");

 C15->Update();
 TLine *nflashTotMC_mean=new TLine(C15->GetUxmin(),_f_mean_nflashTot_opflashInt_MC,C15->GetUxmax(),_f_mean_nflashTot_opflashInt_MC);
 nflashTotMC_mean->SetLineWidth(2);
 nflashTotMC_mean->SetLineColor(kBlack);
 nflashTotMC_mean->Draw("SAME");
 C15->Update();
 TLine *nflashPE50MC_mean=new TLine(C15->GetUxmin(),_f_mean_nflashPE50_opflashInt_MC,C15->GetUxmax(),_f_mean_nflashPE50_opflashInt_MC);
 nflashPE50MC_mean->SetLineWidth(2);
 nflashPE50MC_mean->SetLineColor(kBlue);
 nflashPE50MC_mean->Draw("SAME");
 C15->Update();
 TLine *nflashPE20MC_mean=new TLine(C15->GetUxmin(),_f_mean_nflashPE20_opflashInt_MC,C15->GetUxmax(),_f_mean_nflashPE20_opflashInt_MC);
 nflashPE20MC_mean->SetLineWidth(2);
 nflashPE20MC_mean->SetLineColor(kGreen);
 nflashPE20MC_mean->Draw("SAME");
 C15->Update();
 TLine *nflashPE0_20MC_mean=new TLine(C15->GetUxmin(),_f_mean_nflashPE0_20_opflashInt_MC,C15->GetUxmax(),_f_mean_nflashPE0_20_opflashInt_MC);
 nflashPE0_20MC_mean->SetLineWidth(2);
 nflashPE0_20MC_mean->SetLineColor(kRed);
 nflashPE0_20MC_mean->Draw("SAME");

 C15->Update();
 TLegend* leg_hist15 = new TLegend(0.80,0.70,0.95,0.95); //coordinates are fractions of pad dimensions
 leg_hist15->AddEntry(mean_nflashTot_opflashInt,"All PE data","P");
 leg_hist15->AddEntry(mean_nflashPE50_opflashInt,"> 50 PE data","P");
 leg_hist15->AddEntry(mean_nflashPE20_opflashInt,"> 20 PE data","P");
 leg_hist15->AddEntry(mean_nflashPE0_20_opflashInt,"< 20 PE data","P");
 leg_hist15->AddEntry(nflashTotMC_mean,"All PE MC","L");
 leg_hist15->AddEntry(nflashPE50MC_mean,"> 50 PE MC","L");
 leg_hist15->AddEntry(nflashPE20MC_mean,"> 20 PE MC","L");
 leg_hist15->AddEntry(nflashPE0_20MC_mean,"< 20 PE MC","L");
 leg_hist15->SetFillColor(kWhite);
 leg_hist15->Draw();

C15->Print("/Users/zhouyongshun/Desktop/Argonne/Module/StabilityDet/Plots_StabilityDet_V2.1/Plots_withMC/internal opflashes mean.png");



TCanvas *C16 = new TCanvas("C16","",1200,600);
C16->SetGridx(1);
C16->SetGridy(1);
rms_nflashTot_opflashInt->SetTitle("Rms of number of internal opflashes per event vs run number");
rms_nflashTot_opflashInt->GetXaxis()->SetTitle("run number");
rms_nflashTot_opflashInt->GetYaxis()->SetTitle("number of internal opflashes per event");
rms_nflashTot_opflashInt->SetMarkerColor(kBlack);
rms_nflashTot_opflashInt->SetMarkerStyle(20);
rms_nflashTot_opflashInt->SetMarkerSize(0.8);
rms_nflashTot_opflashInt->SetStats(0);
rms_nflashTot_opflashInt->Draw("P");
rms_nflashPE50_opflashInt->SetMarkerColor(kBlue);
rms_nflashPE50_opflashInt->SetMarkerStyle(20);
rms_nflashPE50_opflashInt->SetMarkerSize(0.8);
rms_nflashPE50_opflashInt->SetStats(0);
rms_nflashPE50_opflashInt->Draw("PSAME");
rms_nflashPE20_opflashInt->SetMarkerColor(kGreen);
rms_nflashPE20_opflashInt->SetMarkerStyle(20);
rms_nflashPE20_opflashInt->SetMarkerSize(0.8);
rms_nflashPE20_opflashInt->SetStats(0);
rms_nflashPE20_opflashInt->Draw("PSAME");
rms_nflashPE0_20_opflashInt->SetMarkerColor(kRed);
rms_nflashPE0_20_opflashInt->SetMarkerStyle(20);
rms_nflashPE0_20_opflashInt->SetMarkerSize(0.8);
rms_nflashPE0_20_opflashInt->SetStats(0);
rms_nflashPE0_20_opflashInt->Draw("PSAME");

 C16->Update();
 TLine *nflashTotMC_rms=new TLine(C16->GetUxmin(),_f_rms_nflashTot_opflashInt_MC,C16->GetUxmax(),_f_rms_nflashTot_opflashInt_MC);
 nflashTotMC_rms->SetLineWidth(2);
 nflashTotMC_rms->SetLineColor(kBlack);
 nflashTotMC_rms->Draw("SAME");
 C16->Update();
 TLine *nflashPE50MC_rms=new TLine(C16->GetUxmin(),_f_rms_nflashPE50_opflashInt_MC,C16->GetUxmax(),_f_rms_nflashPE50_opflashInt_MC);
 nflashPE50MC_rms->SetLineWidth(2);
 nflashPE50MC_rms->SetLineColor(kBlue);
 nflashPE50MC_rms->Draw("SAME");
 C16->Update();
 TLine *nflashPE20MC_rms=new TLine(C16->GetUxmin(),_f_rms_nflashPE20_opflashInt_MC,C16->GetUxmax(),_f_rms_nflashPE20_opflashInt_MC);
 nflashPE20MC_rms->SetLineWidth(2);
 nflashPE20MC_rms->SetLineColor(kGreen);
 nflashPE20MC_rms->Draw("SAME");
 C16->Update();
 TLine *nflashPE0_20MC_rms=new TLine(C16->GetUxmin(),_f_rms_nflashPE0_20_opflashInt_MC,C16->GetUxmax(),_f_rms_nflashPE0_20_opflashInt_MC);
 nflashPE0_20MC_rms->SetLineWidth(2);
 nflashPE0_20MC_rms->SetLineColor(kRed);
 nflashPE0_20MC_rms->Draw("SAME");

 C16->Update();
 TLegend* leg_hist16 = new TLegend(0.80,0.70,0.95,0.95); //coordinates are fractions of pad dimensions
 leg_hist16->AddEntry(rms_nflashTot_opflashInt,"All PE data","P");
 leg_hist16->AddEntry(rms_nflashPE50_opflashInt,"> 50 PE data","P");
 leg_hist16->AddEntry(rms_nflashPE20_opflashInt,"> 20 PE data","P");
 leg_hist16->AddEntry(rms_nflashPE0_20_opflashInt,"< 20 PE data","P");
 leg_hist16->AddEntry(nflashTotMC_rms,"All PE MC","L");
 leg_hist16->AddEntry(nflashPE50MC_rms,"> 50 PE MC","L");
 leg_hist16->AddEntry(nflashPE20MC_rms,"> 20 PE MC","L");
 leg_hist16->AddEntry(nflashPE0_20MC_rms,"< 20 PE MC","L");
 leg_hist16->SetFillColor(kWhite);
 leg_hist16->Draw();

C16->Print("/Users/zhouyongshun/Desktop/Argonne/Module/StabilityDet/Plots_StabilityDet_V2.1/Plots_withMC/internal opflashes rms.png");



TCanvas *C17 = new TCanvas("C17","",1200,600);
C17->SetGridx(1);
C17->SetGridy(1);
mean_flashycenter_opflashExt->SetTitle("Average ycenter position of external opflashes per flash vs run number");
mean_flashycenter_opflashExt->GetXaxis()->SetTitle("run number");
mean_flashycenter_opflashExt->GetYaxis()->SetTitle("ycenter position of external opflashes per flash (cm)");
mean_flashycenter_opflashExt->SetMarkerColor(kBlack);
mean_flashycenter_opflashExt->SetMarkerStyle(20);
mean_flashycenter_opflashExt->SetMarkerSize(0.8);
mean_flashycenter_opflashExt->SetStats(0);
mean_flashycenter_opflashExt->Draw("P");
mean_flashycenterPE50_opflashExt->SetMarkerColor(kBlue);
mean_flashycenterPE50_opflashExt->SetMarkerStyle(20);
mean_flashycenterPE50_opflashExt->SetMarkerSize(0.8);
mean_flashycenterPE50_opflashExt->SetStats(0);
mean_flashycenterPE50_opflashExt->Draw("PSAME");
mean_flashycenterPE20_opflashExt->SetMarkerColor(kGreen);
mean_flashycenterPE20_opflashExt->SetMarkerStyle(20);
mean_flashycenterPE20_opflashExt->SetMarkerSize(0.8);
mean_flashycenterPE20_opflashExt->SetStats(0);
mean_flashycenterPE20_opflashExt->Draw("PSAME");
/*mean_flashycenterPE0_20_opflashExt->SetMarkerColor(kRed);
mean_flashycenterPE0_20_opflashExt->SetMarkerStyle(20);
mean_flashycenterPE0_20_opflashExt->SetMarkerSize(0.8);
mean_flashycenterPE0_20_opflashExt->SetStats(0);
mean_flashycenterPE0_20_opflashExt->Draw("PSAME");*/

 /*C17->Update();
 TLine *flashycenterExtMC_mean=new TLine(C17->GetUxmin(),_f_mean_flashycenter_opflashExt_MC,C17->GetUxmax(),_f_mean_flashycenter_opflashExt_MC);
 flashycenterExtMC_mean->SetLineWidth(2);
 flashycenterExtMC_mean->SetLineColor(kBlack);
 flashycenterExtMC_mean->Draw("SAME");
 C17->Update();
 TLine *flashycenterExtPE50MC_mean=new TLine(C17->GetUxmin(),_f_mean_flashycenterPE50_opflashExt_MC,C17->GetUxmax(),_f_mean_flashycenterPE50_opflashExt_MC);
 flashycenterExtPE50MC_mean->SetLineWidth(2);
 flashycenterExtPE50MC_mean->SetLineColor(kBlue);
 flashycenterExtPE50MC_mean->Draw("SAME");
 C17->Update();
 TLine *flashycenterExtPE20MC_mean=new TLine(C17->GetUxmin(),_f_mean_flashycenterPE20_opflashExt_MC,C17->GetUxmax(),_f_mean_flashycenterPE20_opflashExt_MC);
 flashycenterExtPE20MC_mean->SetLineWidth(2);
 flashycenterExtPE20MC_mean->SetLineColor(kGreen);
 flashycenterExtPE20MC_mean->Draw("SAME");
 C17->Update();
 TLine *flashycenterPE0_20MC_mean=new TLine(C17->GetUxmin(),_f_mean_flashycenterPE0_20_opflashExt_MC,C17->GetUxmax(),_f_mean_flashycenterPE0_20_opflashExt_MC);
 flashycenterPE0_20MC_mean->SetLineWidth(2);
 flashycenterPE0_20MC_mean->SetLineColor(kRed);
 flashycenterPE0_20MC_mean->Draw("SAME");*/

 C17->Update();
 TLegend* leg_hist17 = new TLegend(0.80,0.70,0.95,0.95); //coordinates are fractions of pad dimensions
 leg_hist17->AddEntry(mean_flashycenter_opflashExt,"All PE data","P");
 leg_hist17->AddEntry(mean_flashycenterPE50_opflashExt,"> 50 PE data","P");
 leg_hist17->AddEntry(mean_flashycenterPE20_opflashExt,"> 20 PE data","P");
 //leg_hist17->AddEntry(mean_flashycenterPE0_20_opflashExt,"< 20 PE data","P");
 /*leg_hist17->AddEntry(flashycenterExtMC_mean,"All PE MC","L");
 leg_hist17->AddEntry(flashycenterExtPE50MC_mean,"> 50 PE MC","L");
 leg_hist17->AddEntry(flashycenterExtPE20MC_mean,"> 20 PE MC","L");
 //leg_hist17->AddEntry(flashycenterPE0_20MC_mean,"< 20 PE MC","L");*/
 leg_hist17->SetFillColor(kWhite);
 leg_hist17->Draw();

C17->Print("/Users/zhouyongshun/Desktop/Argonne/Module/StabilityDet/Plots_StabilityDet_V2.1/Plots_withMC/ycenter position of extflashes mean.png");



TCanvas *C18 = new TCanvas("C18","",1200,600);
C18->SetGridx(1);
C18->SetGridy(1);
rms_flashycenter_opflashExt->SetTitle("Rms of ycenter position of external opflashes per flash vs run number");
rms_flashycenter_opflashExt->GetXaxis()->SetTitle("run number");
rms_flashycenter_opflashExt->GetYaxis()->SetTitle("ycenter position of external opflashes per flash (cm)");
rms_flashycenter_opflashExt->SetMarkerColor(kBlack);
rms_flashycenter_opflashExt->SetMarkerStyle(20);
rms_flashycenter_opflashExt->SetMarkerSize(0.8);
rms_flashycenter_opflashExt->SetStats(0);
rms_flashycenter_opflashExt->Draw("P");
rms_flashycenterPE50_opflashExt->SetMarkerColor(kBlue);
rms_flashycenterPE50_opflashExt->SetMarkerStyle(20);
rms_flashycenterPE50_opflashExt->SetMarkerSize(0.8);
rms_flashycenterPE50_opflashExt->SetStats(0);
rms_flashycenterPE50_opflashExt->Draw("PSAME");
rms_flashycenterPE20_opflashExt->SetMarkerColor(kGreen);
rms_flashycenterPE20_opflashExt->SetMarkerStyle(20);
rms_flashycenterPE20_opflashExt->SetMarkerSize(0.8);
rms_flashycenterPE20_opflashExt->SetStats(0);
rms_flashycenterPE20_opflashExt->Draw("PSAME");
/*rms_flashycenterPE0_20_opflashExt->SetMarkerColor(kRed);
rms_flashycenterPE0_20_opflashExt->SetMarkerStyle(20);
rms_flashycenterPE0_20_opflashExt->SetMarkerSize(0.8);
rms_flashycenterPE0_20_opflashExt->SetStats(0);
rms_flashycenterPE0_20_opflashExt->Draw("PSAME");*/

 /*C18->Update();
 TLine *flashycenterExtMC_rms=new TLine(C18->GetUxmin(),_f_rms_flashycenter_opflashExt_MC,C18->GetUxmax(),_f_rms_flashycenter_opflashExt_MC);
 flashycenterExtMC_rms->SetLineWidth(2);
 flashycenterExtMC_rms->SetLineColor(kBlack);
 flashycenterExtMC_rms->Draw("SAME");
 C18->Update();
 TLine *flashycenterExtPE50MC_rms=new TLine(C18->GetUxmin(),_f_rms_flashycenterPE50_opflashExt_MC,C18->GetUxmax(),_f_rms_flashycenterPE50_opflashExt_MC);
 flashycenterExtPE50MC_rms->SetLineWidth(2);
 flashycenterExtPE50MC_rms->SetLineColor(kBlue);
 flashycenterExtPE50MC_rms->Draw("SAME");
 C18->Update();
 TLine *flashycenterExtPE20MC_rms=new TLine(C18->GetUxmin(),_f_rms_flashycenterPE20_opflashExt_MC,C18->GetUxmax(),_f_rms_flashycenterPE20_opflashExt_MC);
 flashycenterExtPE20MC_rms->SetLineWidth(2);
 flashycenterExtPE20MC_rms->SetLineColor(kGreen);
 flashycenterExtPE20MC_rms->Draw("SAME");
 C18->Update();
 TLine *flashycenterPE0_20MC_rms=new TLine(C18->GetUxmin(),_f_rms_flashycenterPE0_20_opflashExt_MC,C18->GetUxmax(),_f_rms_flashycenterPE0_20_opflashExt_MC);
 flashycenterPE0_20MC_rms->SetLineWidth(2);
 flashycenterPE0_20MC_rms->SetLineColor(kRed);
 flashycenterPE0_20MC_rms->Draw("SAME");*/

 C18->Update();
 TLegend* leg_hist18 = new TLegend(0.80,0.70,0.95,0.95); //coordinates are fractions of pad dimensions
 leg_hist18->AddEntry(rms_flashycenter_opflashExt,"All PE data","P");
 leg_hist18->AddEntry(rms_flashycenterPE50_opflashExt,"> 50 PE data","P");
 leg_hist18->AddEntry(rms_flashycenterPE20_opflashExt,"> 20 PE data","P");
 //leg_hist18->AddEntry(rms_flashycenterPE0_20_opflashExt,"< 20 PE data","P");
 /*leg_hist18->AddEntry(flashycenterExtMC_rms,"All PE MC","L");
 leg_hist18->AddEntry(flashycenterExtPE50MC_rms,"> 50 PE MC","L");
 leg_hist18->AddEntry(flashycenterExtPE20MC_rms,"> 20 PE MC","L");
 //leg_hist18->AddEntry(flashycenterPE0_20MC_rms,"< 20 PE MC","L");*/
 leg_hist18->SetFillColor(kWhite);
 leg_hist18->Draw();

C18->Print("/Users/zhouyongshun/Desktop/Argonne/Module/StabilityDet/Plots_StabilityDet_V2.1/Plots_withMC/ycenter position of extflashes rms.png");





TCanvas *C19 = new TCanvas("C19","",1200,600);
C19->SetGridx(1);
C19->SetGridy(1);
mean_flashzcenter_opflashExt->SetTitle("Average zcenter position of external opflashes per flash vs run number");
mean_flashzcenter_opflashExt->GetXaxis()->SetTitle("run number");
mean_flashzcenter_opflashExt->GetYaxis()->SetTitle("zcenter position of external opflashes per flash (cm)");
mean_flashzcenter_opflashExt->SetMarkerColor(kBlack);
mean_flashzcenter_opflashExt->SetMarkerStyle(20);
mean_flashzcenter_opflashExt->SetMarkerSize(0.8);
mean_flashzcenter_opflashExt->SetStats(0);
mean_flashzcenter_opflashExt->Draw("P");
mean_flashzcenterPE50_opflashExt->SetMarkerColor(kBlue);
mean_flashzcenterPE50_opflashExt->SetMarkerStyle(20);
mean_flashzcenterPE50_opflashExt->SetMarkerSize(0.8);
mean_flashzcenterPE50_opflashExt->SetStats(0);
mean_flashzcenterPE50_opflashExt->Draw("PSAME");
mean_flashzcenterPE20_opflashExt->SetMarkerColor(kGreen);
mean_flashzcenterPE20_opflashExt->SetMarkerStyle(20);
mean_flashzcenterPE20_opflashExt->SetMarkerSize(0.8);
mean_flashzcenterPE20_opflashExt->SetStats(0);
mean_flashzcenterPE20_opflashExt->Draw("PSAME");
/*mean_flashzcenterPE0_20_opflashExt->SetMarkerColor(kRed);
mean_flashzcenterPE0_20_opflashExt->SetMarkerStyle(20);
mean_flashzcenterPE0_20_opflashExt->SetMarkerSize(0.8);
mean_flashzcenterPE0_20_opflashExt->SetStats(0);
mean_flashzcenterPE0_20_opflashExt->Draw("PSAME");*/

 /*C19->Update();
 TLine *flashzcenterExtMC_mean=new TLine(C19->GetUxmin(),_f_mean_flashzcenter_opflashExt_MC,C19->GetUxmax(),_f_mean_flashzcenter_opflashExt_MC);
 flashzcenterExtMC_mean->SetLineWidth(2);
 flashzcenterExtMC_mean->SetLineColor(kBlack);
 flashzcenterExtMC_mean->Draw("SAME");
 C19->Update();
 TLine *flashzcenterExtPE50MC_mean=new TLine(C19->GetUxmin(),_f_mean_flashzcenterPE50_opflashExt_MC,C19->GetUxmax(),_f_mean_flashzcenterPE50_opflashExt_MC);
 flashzcenterExtPE50MC_mean->SetLineWidth(2);
 flashzcenterExtPE50MC_mean->SetLineColor(kBlue);
 flashzcenterExtPE50MC_mean->Draw("SAME");
 C19->Update();
 TLine *flashzcenterExtPE20MC_mean=new TLine(C19->GetUxmin(),_f_mean_flashzcenterPE20_opflashExt_MC,C19->GetUxmax(),_f_mean_flashzcenterPE20_opflashExt_MC);
 flashzcenterExtPE20MC_mean->SetLineWidth(2);
 flashzcenterExtPE20MC_mean->SetLineColor(kGreen);
 flashzcenterExtPE20MC_mean->Draw("SAME");
 C19->Update();
 TLine *flashzcenterPE0_20MC_mean=new TLine(C19->GetUxmin(),_f_mean_flashzcenterPE0_20_opflashExt_MC,C19->GetUxmax(),_f_mean_flashzcenterPE0_20_opflashExt_MC);
 flashzcenterPE0_20MC_mean->SetLineWidth(2);
 flashzcenterPE0_20MC_mean->SetLineColor(kRed);
 flashzcenterPE0_20MC_mean->Draw("SAME");*/

 C19->Update();
 TLegend* leg_hist19 = new TLegend(0.80,0.70,0.95,0.95); //coordinates are fractions of pad dimensions
 leg_hist19->AddEntry(mean_flashzcenter_opflashExt,"All PE data","P");
 leg_hist19->AddEntry(mean_flashzcenterPE50_opflashExt,"> 50 PE data","P");
 leg_hist19->AddEntry(mean_flashzcenterPE20_opflashExt,"> 20 PE data","P");
 //leg_hist19->AddEntry(mean_flashzcenterPE0_20_opflashExt,"< 20 PE data","P");
 /*leg_hist19->AddEntry(flashzcenterExtMC_mean,"All PE MC","L");
 leg_hist19->AddEntry(flashzcenterExtPE50MC_mean,"> 50 PE MC","L");
 leg_hist19->AddEntry(flashzcenterExtPE20MC_mean,"> 20 PE MC","L");
 //leg_hist19->AddEntry(flashzcenterPE0_20MC_mean,"< 20 PE MC","L");*/
 leg_hist19->SetFillColor(kWhite);
 leg_hist19->Draw();

C19->Print("/Users/zhouyongshun/Desktop/Argonne/Module/StabilityDet/Plots_StabilityDet_V2.1/Plots_withMC/zcenter position of extflashes mean.png");



TCanvas *C20 = new TCanvas("C20","",1200,600);
C20->SetGridx(1);
C20->SetGridy(1);
rms_flashzcenter_opflashExt->SetTitle("Rms of zcenter position of external opflashes per flash vs run number");
rms_flashzcenter_opflashExt->GetXaxis()->SetTitle("run number");
rms_flashzcenter_opflashExt->GetYaxis()->SetTitle("zcenter position of external opflashes per flash (cm)");
rms_flashzcenter_opflashExt->SetMarkerColor(kBlack);
rms_flashzcenter_opflashExt->SetMarkerStyle(20);
rms_flashzcenter_opflashExt->SetMarkerSize(0.8);
rms_flashzcenter_opflashExt->SetStats(0);
rms_flashzcenter_opflashExt->Draw("P");
rms_flashzcenterPE50_opflashExt->SetMarkerColor(kBlue);
rms_flashzcenterPE50_opflashExt->SetMarkerStyle(20);
rms_flashzcenterPE50_opflashExt->SetMarkerSize(0.8);
rms_flashzcenterPE50_opflashExt->SetStats(0);
rms_flashzcenterPE50_opflashExt->Draw("PSAME");
rms_flashzcenterPE20_opflashExt->SetMarkerColor(kGreen);
rms_flashzcenterPE20_opflashExt->SetMarkerStyle(20);
rms_flashzcenterPE20_opflashExt->SetMarkerSize(0.8);
rms_flashzcenterPE20_opflashExt->SetStats(0);
rms_flashzcenterPE20_opflashExt->Draw("PSAME");
/*rms_flashzcenterPE0_20_opflashExt->SetMarkerColor(kRed);
rms_flashzcenterPE0_20_opflashExt->SetMarkerStyle(20);
rms_flashzcenterPE0_20_opflashExt->SetMarkerSize(0.8);
rms_flashzcenterPE0_20_opflashExt->SetStats(0);
rms_flashzcenterPE0_20_opflashExt->Draw("PSAME");*/

 /*C20->Update();
 TLine *flashzcenterExtMC_rms=new TLine(C20->GetUxmin(),_f_rms_flashzcenter_opflashExt_MC,C20->GetUxmax(),_f_rms_flashzcenter_opflashExt_MC);
 flashzcenterExtMC_rms->SetLineWidth(2);
 flashzcenterExtMC_rms->SetLineColor(kBlack);
 flashzcenterExtMC_rms->Draw("SAME");
 C20->Update();
 TLine *flashzcenterExtPE50MC_rms=new TLine(C20->GetUxmin(),_f_rms_flashzcenterPE50_opflashExt_MC,C20->GetUxmax(),_f_rms_flashzcenterPE50_opflashExt_MC);
 flashzcenterExtPE50MC_rms->SetLineWidth(2);
 flashzcenterExtPE50MC_rms->SetLineColor(kBlue);
 flashzcenterExtPE50MC_rms->Draw("SAME");
 C20->Update();
 TLine *flashzcenterExtPE20MC_rms=new TLine(C20->GetUxmin(),_f_rms_flashzcenterPE20_opflashExt_MC,C20->GetUxmax(),_f_rms_flashzcenterPE20_opflashExt_MC);
 flashzcenterExtPE20MC_rms->SetLineWidth(2);
 flashzcenterExtPE20MC_rms->SetLineColor(kGreen);
 flashzcenterExtPE20MC_rms->Draw("SAME");
 C20->Update();
 TLine *flashzcenterPE0_20MC_rms=new TLine(C20->GetUxmin(),_f_rms_flashzcenterPE0_20_opflashExt_MC,C20->GetUxmax(),_f_rms_flashzcenterPE0_20_opflashExt_MC);
 flashzcenterPE0_20MC_rms->SetLineWidth(2);
 flashzcenterPE0_20MC_rms->SetLineColor(kRed);
 flashzcenterPE0_20MC_rms->Draw("SAME");*/

 C20->Update();
 TLegend* leg_hist20 = new TLegend(0.80,0.70,0.95,0.95); //coordinates are fractions of pad dimensions
 leg_hist20->AddEntry(rms_flashzcenter_opflashExt,"All PE data","P");
 leg_hist20->AddEntry(rms_flashzcenterPE50_opflashExt,"> 50 PE data","P");
 leg_hist20->AddEntry(rms_flashzcenterPE20_opflashExt,"> 20 PE data","P");
 //leg_hist20->AddEntry(rms_flashzcenterPE0_20_opflashExt,"< 20 PE data","P");
 /*leg_hist20->AddEntry(flashzcenterExtMC_rms,"All PE MC","L");
 leg_hist20->AddEntry(flashzcenterExtPE50MC_rms,"> 50 PE MC","L");
 leg_hist20->AddEntry(flashzcenterExtPE20MC_rms,"> 20 PE MC","L");
 //leg_hist20->AddEntry(flashzcenterPE0_20MC_rms,"< 20 PE MC","L");*/
 leg_hist20->SetFillColor(kWhite);
 leg_hist20->Draw();

C20->Print("/Users/zhouyongshun/Desktop/Argonne/Module/StabilityDet/Plots_StabilityDet_V2.1/Plots_withMC/zcenter position of extflashes rms.png");



TCanvas *C21 = new TCanvas("C21","",1200,600);
C21->SetGridx(1);
C21->SetGridy(1);
mean_flashycenter_opflashInt->SetTitle("Average ycenter position of internal opflashes per flash vs run number");
mean_flashycenter_opflashInt->GetXaxis()->SetTitle("run number");
mean_flashycenter_opflashInt->GetYaxis()->SetTitle("ycenter position of internal opflashes per flash (cm)");
mean_flashycenter_opflashInt->SetMarkerColor(kBlack);
mean_flashycenter_opflashInt->SetMarkerStyle(20);
mean_flashycenter_opflashInt->SetMarkerSize(0.8);
mean_flashycenter_opflashInt->SetStats(0);
mean_flashycenter_opflashInt->Draw("P");
mean_flashycenterPE50_opflashInt->SetMarkerColor(kBlue);
mean_flashycenterPE50_opflashInt->SetMarkerStyle(20);
mean_flashycenterPE50_opflashInt->SetMarkerSize(0.8);
mean_flashycenterPE50_opflashInt->SetStats(0);
mean_flashycenterPE50_opflashInt->Draw("PSAME");
mean_flashycenterPE20_opflashInt->SetMarkerColor(kGreen);
mean_flashycenterPE20_opflashInt->SetMarkerStyle(20);
mean_flashycenterPE20_opflashInt->SetMarkerSize(0.8);
mean_flashycenterPE20_opflashInt->SetStats(0);
mean_flashycenterPE20_opflashInt->Draw("PSAME");
/*mean_flashycenterPE0_20_opflashInt->SetMarkerColor(kRed);
mean_flashycenterPE0_20_opflashInt->SetMarkerStyle(20);
mean_flashycenterPE0_20_opflashInt->SetMarkerSize(0.8);
mean_flashycenterPE0_20_opflashInt->SetStats(0);
mean_flashycenterPE0_20_opflashInt->Draw("PSAME");*/

 C21->Update();
 TLine *flashycenterIntMC_mean=new TLine(C21->GetUxmin(),_f_mean_flashycenter_opflashInt_MC,C21->GetUxmax(),_f_mean_flashycenter_opflashInt_MC);
 flashycenterIntMC_mean->SetLineWidth(2);
 flashycenterIntMC_mean->SetLineColor(kBlack);
 flashycenterIntMC_mean->Draw("SAME");
 C21->Update();
 TLine *flashycenterIntPE50MC_mean=new TLine(C21->GetUxmin(),_f_mean_flashycenterPE50_opflashInt_MC,C21->GetUxmax(),_f_mean_flashycenterPE50_opflashInt_MC);
 flashycenterIntPE50MC_mean->SetLineWidth(2);
 flashycenterIntPE50MC_mean->SetLineColor(kBlue);
 flashycenterIntPE50MC_mean->Draw("SAME");
 C21->Update();
 TLine *flashycenterIntPE20MC_mean=new TLine(C21->GetUxmin(),_f_mean_flashycenterPE20_opflashInt_MC,C21->GetUxmax(),_f_mean_flashycenterPE20_opflashInt_MC);
 flashycenterIntPE20MC_mean->SetLineWidth(2);
 flashycenterIntPE20MC_mean->SetLineColor(kGreen);
 flashycenterIntPE20MC_mean->Draw("SAME");
 /*C21->Update();
 TLine *flashycenterPE0_20MC_mean=new TLine(C21->GetUxmin(),_f_mean_flashycenterPE0_20_opflashInt_MC,C21->GetUxmax(),_f_mean_flashycenterPE0_20_opflashInt_MC);
 flashycenterPE0_20MC_mean->SetLineWidth(2);
 flashycenterPE0_20MC_mean->SetLineColor(kRed);
 flashycenterPE0_20MC_mean->Draw("SAME");*/

 C21->Update();
 TLegend* leg_hist21 = new TLegend(0.80,0.70,0.95,0.95); //coordinates are fractions of pad dimensions
 leg_hist21->AddEntry(mean_flashycenter_opflashInt,"All PE data","P");
 leg_hist21->AddEntry(mean_flashycenterPE50_opflashInt,"> 50 PE data","P");
 leg_hist21->AddEntry(mean_flashycenterPE20_opflashInt,"> 20 PE data","P");
 //leg_hist21->AddEntry(mean_flashycenterPE0_20_opflashInt,"< 20 PE data","P");
 leg_hist21->AddEntry(flashycenterIntMC_mean,"All PE MC","L");
 leg_hist21->AddEntry(flashycenterIntPE50MC_mean,"> 50 PE MC","L");
 leg_hist21->AddEntry(flashycenterIntPE20MC_mean,"> 20 PE MC","L");
 //leg_hist21->AddEntry(flashycenterPE0_20MC_mean,"< 20 PE MC","L");
 leg_hist21->SetFillColor(kWhite);
 leg_hist21->Draw();

C21->Print("/Users/zhouyongshun/Desktop/Argonne/Module/StabilityDet/Plots_StabilityDet_V2.1/Plots_withMC/ycenter position of intflashes mean.png");



TCanvas *C22 = new TCanvas("C22","",1200,600);
C22->SetGridx(1);
C22->SetGridy(1);
rms_flashycenter_opflashInt->SetTitle("Rms of ycenter position of internal opflashes per flash vs run number");
rms_flashycenter_opflashInt->GetXaxis()->SetTitle("run number");
rms_flashycenter_opflashInt->GetYaxis()->SetTitle("ycenter position of internal opflashes per flash (cm)");
rms_flashycenter_opflashInt->SetMarkerColor(kBlack);
rms_flashycenter_opflashInt->SetMarkerStyle(20);
rms_flashycenter_opflashInt->SetMarkerSize(0.8);
rms_flashycenter_opflashInt->SetStats(0);
rms_flashycenter_opflashInt->Draw("P");
rms_flashycenterPE50_opflashInt->SetMarkerColor(kBlue);
rms_flashycenterPE50_opflashInt->SetMarkerStyle(20);
rms_flashycenterPE50_opflashInt->SetMarkerSize(0.8);
rms_flashycenterPE50_opflashInt->SetStats(0);
rms_flashycenterPE50_opflashInt->Draw("PSAME");
rms_flashycenterPE20_opflashInt->SetMarkerColor(kGreen);
rms_flashycenterPE20_opflashInt->SetMarkerStyle(20);
rms_flashycenterPE20_opflashInt->SetMarkerSize(0.8);
rms_flashycenterPE20_opflashInt->SetStats(0);
rms_flashycenterPE20_opflashInt->Draw("PSAME");
/*rms_flashycenterPE0_20_opflashInt->SetMarkerColor(kRed);
rms_flashycenterPE0_20_opflashInt->SetMarkerStyle(20);
rms_flashycenterPE0_20_opflashInt->SetMarkerSize(0.8);
rms_flashycenterPE0_20_opflashInt->SetStats(0);
rms_flashycenterPE0_20_opflashInt->Draw("PSAME");*/

 C22->Update();
 TLine *flashycenterIntMC_rms=new TLine(C22->GetUxmin(),_f_rms_flashycenter_opflashInt_MC,C22->GetUxmax(),_f_rms_flashycenter_opflashInt_MC);
 flashycenterIntMC_rms->SetLineWidth(2);
 flashycenterIntMC_rms->SetLineColor(kBlack);
 flashycenterIntMC_rms->Draw("SAME");
 C22->Update();
 TLine *flashycenterIntPE50MC_rms=new TLine(C22->GetUxmin(),_f_rms_flashycenterPE50_opflashInt_MC,C22->GetUxmax(),_f_rms_flashycenterPE50_opflashInt_MC);
 flashycenterIntPE50MC_rms->SetLineWidth(2);
 flashycenterIntPE50MC_rms->SetLineColor(kBlue);
 flashycenterIntPE50MC_rms->Draw("SAME");
 C22->Update();
 TLine *flashycenterIntPE20MC_rms=new TLine(C22->GetUxmin(),_f_rms_flashycenterPE20_opflashInt_MC,C22->GetUxmax(),_f_rms_flashycenterPE20_opflashInt_MC);
 flashycenterIntPE20MC_rms->SetLineWidth(2);
 flashycenterIntPE20MC_rms->SetLineColor(kGreen);
 flashycenterIntPE20MC_rms->Draw("SAME");
 /*C22->Update();
 TLine *flashycenterPE0_20MC_rms=new TLine(C22->GetUxmin(),_f_rms_flashycenterPE0_20_opflashInt_MC,C22->GetUxmax(),_f_rms_flashycenterPE0_20_opflashInt_MC);
 flashycenterPE0_20MC_rms->SetLineWidth(2);
 flashycenterPE0_20MC_rms->SetLineColor(kRed);
 flashycenterPE0_20MC_rms->Draw("SAME");*/

 C22->Update();
 TLegend* leg_hist22 = new TLegend(0.80,0.70,0.95,0.95); //coordinates are fractions of pad dimensions
 leg_hist22->AddEntry(rms_flashycenter_opflashInt,"All PE data","P");
 leg_hist22->AddEntry(rms_flashycenterPE50_opflashInt,"> 50 PE data","P");
 leg_hist22->AddEntry(rms_flashycenterPE20_opflashInt,"> 20 PE data","P");
 //leg_hist22->AddEntry(rms_flashycenterPE0_20_opflashInt,"< 20 PE data","P");
 leg_hist22->AddEntry(flashycenterIntMC_rms,"All PE MC","L");
 leg_hist22->AddEntry(flashycenterIntPE50MC_rms,"> 50 PE MC","L");
 leg_hist22->AddEntry(flashycenterIntPE20MC_rms,"> 20 PE MC","L");
 //leg_hist22->AddEntry(flashycenterPE0_20MC_rms,"< 20 PE MC","L");
 leg_hist22->SetFillColor(kWhite);
 leg_hist22->Draw();

C22->Print("/Users/zhouyongshun/Desktop/Argonne/Module/StabilityDet/Plots_StabilityDet_V2.1/Plots_withMC/ycenter position of intflashes rms.png");





TCanvas *C23 = new TCanvas("C23","",1200,600);
C23->SetGridx(1);
C23->SetGridy(1);
mean_flashzcenter_opflashInt->SetTitle("Average zcenter position of internal opflashes per flash vs run number");
mean_flashzcenter_opflashInt->GetXaxis()->SetTitle("run number");
mean_flashzcenter_opflashInt->GetYaxis()->SetTitle("zcenter position of internal opflashes per flash (cm)");
mean_flashzcenter_opflashInt->SetMarkerColor(kBlack);
mean_flashzcenter_opflashInt->SetMarkerStyle(20);
mean_flashzcenter_opflashInt->SetMarkerSize(0.8);
mean_flashzcenter_opflashInt->SetStats(0);
mean_flashzcenter_opflashInt->Draw("P");
mean_flashzcenterPE50_opflashInt->SetMarkerColor(kBlue);
mean_flashzcenterPE50_opflashInt->SetMarkerStyle(20);
mean_flashzcenterPE50_opflashInt->SetMarkerSize(0.8);
mean_flashzcenterPE50_opflashInt->SetStats(0);
mean_flashzcenterPE50_opflashInt->Draw("PSAME");
mean_flashzcenterPE20_opflashInt->SetMarkerColor(kGreen);
mean_flashzcenterPE20_opflashInt->SetMarkerStyle(20);
mean_flashzcenterPE20_opflashInt->SetMarkerSize(0.8);
mean_flashzcenterPE20_opflashInt->SetStats(0);
mean_flashzcenterPE20_opflashInt->Draw("PSAME");
/*mean_flashzcenterPE0_20_opflashInt->SetMarkerColor(kRed);
mean_flashzcenterPE0_20_opflashInt->SetMarkerStyle(20);
mean_flashzcenterPE0_20_opflashInt->SetMarkerSize(0.8);
mean_flashzcenterPE0_20_opflashInt->SetStats(0);
mean_flashzcenterPE0_20_opflashInt->Draw("PSAME");*/

 C23->Update();
 TLine *flashzcenterIntMC_mean=new TLine(C23->GetUxmin(),_f_mean_flashzcenter_opflashInt_MC,C23->GetUxmax(),_f_mean_flashzcenter_opflashInt_MC);
 flashzcenterIntMC_mean->SetLineWidth(2);
 flashzcenterIntMC_mean->SetLineColor(kBlack);
 flashzcenterIntMC_mean->Draw("SAME");
 C23->Update();
 TLine *flashzcenterIntPE50MC_mean=new TLine(C23->GetUxmin(),_f_mean_flashzcenterPE50_opflashInt_MC,C23->GetUxmax(),_f_mean_flashzcenterPE50_opflashInt_MC);
 flashzcenterIntPE50MC_mean->SetLineWidth(2);
 flashzcenterIntPE50MC_mean->SetLineColor(kBlue);
 flashzcenterIntPE50MC_mean->Draw("SAME");
 C23->Update();
 TLine *flashzcenterIntPE20MC_mean=new TLine(C23->GetUxmin(),_f_mean_flashzcenterPE20_opflashInt_MC,C23->GetUxmax(),_f_mean_flashzcenterPE20_opflashInt_MC);
 flashzcenterIntPE20MC_mean->SetLineWidth(2);
 flashzcenterIntPE20MC_mean->SetLineColor(kGreen);
 flashzcenterIntPE20MC_mean->Draw("SAME");
 /*C23->Update();
 TLine *flashzcenterPE0_20MC_mean=new TLine(C23->GetUxmin(),_f_mean_flashzcenterPE0_20_opflashInt_MC,C23->GetUxmax(),_f_mean_flashzcenterPE0_20_opflashInt_MC);
 flashzcenterPE0_20MC_mean->SetLineWidth(2);
 flashzcenterPE0_20MC_mean->SetLineColor(kRed);
 flashzcenterPE0_20MC_mean->Draw("SAME");*/

 C23->Update();
 TLegend* leg_hist23 = new TLegend(0.80,0.70,0.95,0.95); //coordinates are fractions of pad dimensions
 leg_hist23->AddEntry(mean_flashzcenter_opflashInt,"All PE data","P");
 leg_hist23->AddEntry(mean_flashzcenterPE50_opflashInt,"> 50 PE data","P");
 leg_hist23->AddEntry(mean_flashzcenterPE20_opflashInt,"> 20 PE data","P");
 //leg_hist23->AddEntry(mean_flashzcenterPE0_20_opflashInt,"< 20 PE data","P");
 leg_hist23->AddEntry(flashzcenterIntMC_mean,"All PE MC","L");
 leg_hist23->AddEntry(flashzcenterIntPE50MC_mean,"> 50 PE MC","L");
 leg_hist23->AddEntry(flashzcenterIntPE20MC_mean,"> 20 PE MC","L");
 //leg_hist23->AddEntry(flashzcenterPE0_20MC_mean,"< 20 PE MC","L");
 leg_hist23->SetFillColor(kWhite);
 leg_hist23->Draw();

C23->Print("/Users/zhouyongshun/Desktop/Argonne/Module/StabilityDet/Plots_StabilityDet_V2.1/Plots_withMC/zcenter position of intflashes mean.png");



TCanvas *C24 = new TCanvas("C24","",1200,600);
C24->SetGridx(1);
C24->SetGridy(1);
rms_flashzcenter_opflashInt->SetTitle("Rms of zcenter position of internal opflashes per flash vs run number");
rms_flashzcenter_opflashInt->GetXaxis()->SetTitle("run number");
rms_flashzcenter_opflashInt->GetYaxis()->SetTitle("zcenter position of internal opflashes per flash (cm)");
rms_flashzcenter_opflashInt->SetMarkerColor(kBlack);
rms_flashzcenter_opflashInt->SetMarkerStyle(20);
rms_flashzcenter_opflashInt->SetMarkerSize(0.8);
rms_flashzcenter_opflashInt->SetStats(0);
rms_flashzcenter_opflashInt->Draw("P");
rms_flashzcenterPE50_opflashInt->SetMarkerColor(kBlue);
rms_flashzcenterPE50_opflashInt->SetMarkerStyle(20);
rms_flashzcenterPE50_opflashInt->SetMarkerSize(0.8);
rms_flashzcenterPE50_opflashInt->SetStats(0);
rms_flashzcenterPE50_opflashInt->Draw("PSAME");
rms_flashzcenterPE20_opflashInt->SetMarkerColor(kGreen);
rms_flashzcenterPE20_opflashInt->SetMarkerStyle(20);
rms_flashzcenterPE20_opflashInt->SetMarkerSize(0.8);
rms_flashzcenterPE20_opflashInt->SetStats(0);
rms_flashzcenterPE20_opflashInt->Draw("PSAME");
/*rms_flashzcenterPE0_20_opflashInt->SetMarkerColor(kRed);
rms_flashzcenterPE0_20_opflashInt->SetMarkerStyle(20);
rms_flashzcenterPE0_20_opflashInt->SetMarkerSize(0.8);
rms_flashzcenterPE0_20_opflashInt->SetStats(0);
rms_flashzcenterPE0_20_opflashInt->Draw("PSAME");*/

 C24->Update();
 TLine *flashzcenterIntMC_rms=new TLine(C24->GetUxmin(),_f_rms_flashzcenter_opflashInt_MC,C24->GetUxmax(),_f_rms_flashzcenter_opflashInt_MC);
 flashzcenterIntMC_rms->SetLineWidth(2);
 flashzcenterIntMC_rms->SetLineColor(kBlack);
 flashzcenterIntMC_rms->Draw("SAME");
 C24->Update();
 TLine *flashzcenterIntPE50MC_rms=new TLine(C24->GetUxmin(),_f_rms_flashzcenterPE50_opflashInt_MC,C24->GetUxmax(),_f_rms_flashzcenterPE50_opflashInt_MC);
 flashzcenterIntPE50MC_rms->SetLineWidth(2);
 flashzcenterIntPE50MC_rms->SetLineColor(kBlue);
 flashzcenterIntPE50MC_rms->Draw("SAME");
 C24->Update();
 TLine *flashzcenterIntPE20MC_rms=new TLine(C24->GetUxmin(),_f_rms_flashzcenterPE20_opflashInt_MC,C24->GetUxmax(),_f_rms_flashzcenterPE20_opflashInt_MC);
 flashzcenterIntPE20MC_rms->SetLineWidth(2);
 flashzcenterIntPE20MC_rms->SetLineColor(kGreen);
 flashzcenterIntPE20MC_rms->Draw("SAME");
 /*C24->Update();
 TLine *flashzcenterPE0_20MC_rms=new TLine(C24->GetUxmin(),_f_rms_flashzcenterPE0_20_opflashInt_MC,C24->GetUxmax(),_f_rms_flashzcenterPE0_20_opflashInt_MC);
 flashzcenterPE0_20MC_rms->SetLineWidth(2);
 flashzcenterPE0_20MC_rms->SetLineColor(kRed);
 flashzcenterPE0_20MC_rms->Draw("SAME");*/

 C24->Update();
 TLegend* leg_hist24 = new TLegend(0.80,0.70,0.95,0.95); //coordinates are fractions of pad dimensions
 leg_hist24->AddEntry(rms_flashzcenter_opflashInt,"All PE data","P");
 leg_hist24->AddEntry(rms_flashzcenterPE50_opflashInt,"> 50 PE data","P");
 leg_hist24->AddEntry(rms_flashzcenterPE20_opflashInt,"> 20 PE data","P");
 //leg_hist24->AddEntry(rms_flashzcenterPE0_20_opflashInt,"< 20 PE data","P");
 leg_hist24->AddEntry(flashzcenterIntMC_rms,"All PE MC","L");
 leg_hist24->AddEntry(flashzcenterIntPE50MC_rms,"> 50 PE MC","L");
 leg_hist24->AddEntry(flashzcenterIntPE20MC_rms,"> 20 PE MC","L");
 //leg_hist24->AddEntry(flashzcenterPE0_20MC_rms,"< 20 PE MC","L");
 leg_hist24->SetFillColor(kWhite);
 leg_hist24->Draw();

C24->Print("/Users/zhouyongshun/Desktop/Argonne/Module/StabilityDet/Plots_StabilityDet_V2.1/Plots_withMC/zcenter position of intflashes rms.png");



TCanvas *C25 = new TCanvas("C25","",1200,600);
C25->SetGridx(1);
C25->SetGridy(1);
mean_flashPE_opflashExt->SetTitle("Average external opflash peak amplitude per flash vs run number");
mean_flashPE_opflashExt->GetXaxis()->SetTitle("run number");
mean_flashPE_opflashExt->GetYaxis()->SetTitle("external opflash peak amplitude per flash (PE)");
mean_flashPE_opflashExt->SetMarkerColor(kBlack);
mean_flashPE_opflashExt->SetMarkerStyle(20);
mean_flashPE_opflashExt->SetMarkerSize(0.8);
mean_flashPE_opflashExt->SetStats(0);
mean_flashPE_opflashExt->Draw("P");

 /*C25->Update();
 TLine *flashPE_opflashExtMC_mean=new TLine(C25->GetUxmin(),_f_mean_flashPE_opflashExt_MC,C25->GetUxmax(),_f_mean_flashPE_opflashExt_MC);
 flashPE_opflashExtMC_mean->SetLineWidth(2);
 flashPE_opflashExtMC_mean->SetLineColor(kBlack);
 flashPE_opflashExtMC_mean->Draw("SAME");

 C25->Update();
 TLegend* leg_hist25 = new TLegend(0.80,0.70,0.95,0.95); //coordinates are fractions of pad dimensions
 leg_hist25->AddEntry(mean_flashPE_opflashExt,"peak amplitude data","P");
 leg_hist25->AddEntry(flashPE_opflashExtMC_mean,"peak amplitude MC ","L");
 leg_hist25->SetFillColor(kWhite);
 leg_hist25->Draw();*/

C25->Print("/Users/zhouyongshun/Desktop/Argonne/Module/StabilityDet/Plots_StabilityDet_V2.1/Plots_withMC/extflash peak amplitude mean.png");



TCanvas *C26 = new TCanvas("C26","",1200,600);
C26->SetGridx(1);
C26->SetGridy(1);
rms_flashPE_opflashExt->SetTitle("Rms of external opflash peak amplitude per flash vs run number");
rms_flashPE_opflashExt->GetXaxis()->SetTitle("run number");
rms_flashPE_opflashExt->GetYaxis()->SetTitle("external opflash peak amplitude per flash (PE)");
rms_flashPE_opflashExt->SetMarkerColor(kBlack);
rms_flashPE_opflashExt->SetMarkerStyle(20);
rms_flashPE_opflashExt->SetMarkerSize(0.8);
rms_flashPE_opflashExt->SetStats(0);
rms_flashPE_opflashExt->Draw("P");

 /*C26->Update();
 TLine *flashPE_opflashExtMC_rms=new TLine(C26->GetUxmin(),_f_rms_flashPE_opflashExt_MC,C26->GetUxmax(),_f_rms_flashPE_opflashExt_MC);
 flashPE_opflashExtMC_rms->SetLineWidth(2);
 flashPE_opflashExtMC_rms->SetLineColor(kBlack);
 flashPE_opflashExtMC_rms->Draw("SAME");

 C26->Update();
 TLegend* leg_hist26 = new TLegend(0.80,0.70,0.95,0.95); //coordinates are fractions of pad dimensions
 leg_hist26->AddEntry(rms_flashPE_opflashExt,"Ext flash peak amplitude rms data","P");
 leg_hist26->AddEntry(flashPE_opflashExtMC_rms,"peak amplitude Data MC ","L");
 leg_hist26->SetFillColor(kWhite);
 leg_hist26->Draw();*/

C26->Print("/Users/zhouyongshun/Desktop/Argonne/Module/StabilityDet/Plots_StabilityDet_V2.1/Plots_withMC/extflash peak amplitude rms.png");



TCanvas *C27 = new TCanvas("C27","",1200,600);
C27->SetGridx(1);
C27->SetGridy(1);
mean_flashPE_opflashInt->SetTitle("Average internal opflash peak amplitude per flash vs run number");
mean_flashPE_opflashInt->GetXaxis()->SetTitle("run number");
mean_flashPE_opflashInt->GetYaxis()->SetTitle("internal opflash peak amplitude per flash (PE)");
mean_flashPE_opflashInt->SetMarkerColor(kBlack);
mean_flashPE_opflashInt->SetMarkerStyle(20);
mean_flashPE_opflashInt->SetMarkerSize(0.8);
mean_flashPE_opflashInt->SetStats(0);
mean_flashPE_opflashInt->Draw("P");

 C27->Update();
 TLine *flashPE_opflashIntMC_mean=new TLine(C27->GetUxmin(),_f_mean_flashPE_opflashInt_MC,C27->GetUxmax(),_f_mean_flashPE_opflashInt_MC);
 flashPE_opflashIntMC_mean->SetLineWidth(2);
 flashPE_opflashIntMC_mean->SetLineColor(kBlack);
 flashPE_opflashIntMC_mean->Draw("SAME");

 C27->Update();
 TLegend* leg_hist27 = new TLegend(0.80,0.70,0.95,0.95); //coordinates are fractions of pad dimensions
 leg_hist27->AddEntry(mean_flashPE_opflashInt,"peak amplitude data","P");
 leg_hist27->AddEntry(flashPE_opflashIntMC_mean,"peak amplitude MC ","L");
 leg_hist27->SetFillColor(kWhite);
 leg_hist27->Draw();

C27->Print("/Users/zhouyongshun/Desktop/Argonne/Module/StabilityDet/Plots_StabilityDet_V2.1/Plots_withMC/intflash peak amplitude mean.png");



TCanvas *C28 = new TCanvas("C28","",1200,600);
C28->SetGridx(1);
C28->SetGridy(1);
rms_flashPE_opflashInt->SetTitle("Rms of internal opflash peak amplitude per flash vs run number");
rms_flashPE_opflashInt->GetXaxis()->SetTitle("run number");
rms_flashPE_opflashInt->GetYaxis()->SetTitle("internal opflash peak amplitude per flash (PE)");
rms_flashPE_opflashInt->SetMarkerColor(kBlack);
rms_flashPE_opflashInt->SetMarkerStyle(20);
rms_flashPE_opflashInt->SetMarkerSize(0.8);
rms_flashPE_opflashInt->SetStats(0);
rms_flashPE_opflashInt->Draw("P");

 C28->Update();
 TLine *flashPE_opflashIntMC_rms=new TLine(C28->GetUxmin(),_f_rms_flashPE_opflashInt_MC,C28->GetUxmax(),_f_rms_flashPE_opflashInt_MC);
 flashPE_opflashIntMC_rms->SetLineWidth(2);
 flashPE_opflashIntMC_rms->SetLineColor(kBlack);
 flashPE_opflashIntMC_rms->Draw("SAME");

 C28->Update();
 TLegend* leg_hist28 = new TLegend(0.80,0.70,0.95,0.95); //coordinates are fractions of pad dimensions
 leg_hist28->AddEntry(rms_flashPE_opflashInt,"peak amplitude data","P");
 leg_hist28->AddEntry(flashPE_opflashIntMC_rms,"peak amplitude MC ","L");
 leg_hist28->SetFillColor(kWhite);
 leg_hist28->Draw();

C28->Print("/Users/zhouyongshun/Desktop/Argonne/Module/StabilityDet/Plots_StabilityDet_V2.1/Plots_withMC/intflash peak amplitude rms.png");



TCanvas *C29 = new TCanvas("C29","",1200,600);
C29->SetGridx(1);
C29->SetGridy(1);
C29->Draw();
mean_nvrtx_pmtrack->SetTitle("Average number of vertices per event vs run number");
mean_nvrtx_pmtrack->GetXaxis()->SetTitle("run number");
mean_nvrtx_pmtrack->GetYaxis()->SetTitle("number of vertices per event");
mean_nvrtx_pmtrack->SetMarkerColor(kRed);
mean_nvrtx_pmtrack->SetMarkerStyle(20);
mean_nvrtx_pmtrack->SetMarkerSize(0.8);
mean_nvrtx_pmtrack->SetStats(0);
mean_nvrtx_pmtrack->Draw("P");
C29->Update();
mean_nvrtx_pandora->SetMarkerColor(kBlue);
mean_nvrtx_pandora->SetMarkerStyle(20);
mean_nvrtx_pandora->SetMarkerSize(0.8);
mean_nvrtx_pandora->SetStats(0);
mean_nvrtx_pandora->Draw("PSAME");

 C29->Update();
 TLine *nvrtxMC_pmtrack=new TLine(C29->GetUxmin(),_f_mean_nvrtx_pmtrack_MC,C29->GetUxmax(),_f_mean_nvrtx_pmtrack_MC);
 nvrtxMC_pmtrack->SetLineWidth(2);
 nvrtxMC_pmtrack->SetLineColor(kRed);
 nvrtxMC_pmtrack->Draw("SAME");
 C29->Update();
 TLine *nvrtxMC_pandora=new TLine(C29->GetUxmin(),_f_mean_nvrtx_pandora_MC,C29->GetUxmax(),_f_mean_nvrtx_pandora_MC);
 nvrtxMC_pandora->SetLineWidth(2);
 nvrtxMC_pandora->SetLineColor(kBlue);
 nvrtxMC_pandora->Draw("SAME");

C29->Update();
TLegend* leg_hist29 = new TLegend(0.80,0.70,0.95,0.95); //coordinates are fractions of pad dimensions
leg_hist29->AddEntry(mean_nvrtx_pmtrack,"pmtrack data","P");
leg_hist29->AddEntry(mean_nvrtx_pandora,"pandoraTrack data","P");
leg_hist29->AddEntry(nvrtxMC_pmtrack,"pmtrack MC","L");
leg_hist29->AddEntry(nvrtxMC_pandora,"pandoraTrack MC","L");

leg_hist29->SetFillColor(kWhite);
leg_hist29->Draw();

C29->Print("/Users/zhouyongshun/Desktop/Argonne/Module/StabilityDet/Plots_StabilityDet_V2.1/Plots_withMC/vertices numbers mean.png");



TCanvas *C30 = new TCanvas("C30","",1200,600);
C30->SetGridx(1);
C30->SetGridy(1);
C30->Draw();
rms_nvrtx_pmtrack->SetTitle("Rms of number of vertices per event vs run number");
rms_nvrtx_pmtrack->GetXaxis()->SetTitle("run number");
rms_nvrtx_pmtrack->GetYaxis()->SetTitle("number of vertices per event");
rms_nvrtx_pmtrack->SetMarkerColor(kRed);
rms_nvrtx_pmtrack->SetMarkerStyle(20);
rms_nvrtx_pmtrack->SetMarkerSize(0.8);
rms_nvrtx_pmtrack->SetStats(0);
rms_nvrtx_pmtrack->Draw("P");
C30->Update();
rms_nvrtx_pandora->SetMarkerColor(kBlue);
rms_nvrtx_pandora->SetMarkerStyle(20);
rms_nvrtx_pandora->SetMarkerSize(0.8);
rms_nvrtx_pandora->SetStats(0);
rms_nvrtx_pandora->Draw("PSAME");

 C30->Update();
 TLine *nvrtxMC_rms_pmtrack=new TLine(C30->GetUxmin(),_f_rms_nvrtx_pmtrack_MC,C30->GetUxmax(),_f_rms_nvrtx_pmtrack_MC);
 nvrtxMC_rms_pmtrack->SetLineWidth(2);
 nvrtxMC_rms_pmtrack->SetLineColor(kRed);
 nvrtxMC_rms_pmtrack->Draw("SAME");
 C30->Update();
 TLine *nvrtxMC_rms_pandora=new TLine(C30->GetUxmin(),_f_rms_nvrtx_pandora_MC,C30->GetUxmax(),_f_rms_nvrtx_pandora_MC);
 nvrtxMC_rms_pandora->SetLineWidth(2);
 nvrtxMC_rms_pandora->SetLineColor(kBlue);
 nvrtxMC_rms_pandora->Draw("SAME");

C30->Update();
TLegend* leg_hist30 = new TLegend(0.80,0.70,0.95,0.95); //coordinates are fractions of pad dimensions
leg_hist30->AddEntry(rms_nvrtx_pmtrack,"pmtrack data","P");
leg_hist30->AddEntry(rms_nvrtx_pandora,"pandoraTrack data","P");
leg_hist30->AddEntry(nvrtxMC_rms_pmtrack,"pmtrack MC","L");
leg_hist30->AddEntry(nvrtxMC_rms_pandora,"pandoraTrack MC","L");

leg_hist30->SetFillColor(kWhite);
leg_hist30->Draw();

C30->Print("/Users/zhouyongshun/Desktop/Argonne/Module/StabilityDet/Plots_StabilityDet_V2.1/Plots_withMC/vertices numbers rms.png");



TCanvas *C31 = new TCanvas("C31","",1200,600);
C31->SetGridx(1);
C31->SetGridy(1);
C31->Draw();
mean_npfps_pmtrack->SetTitle("Average number of PFPs per event vs run number");
mean_npfps_pmtrack->GetXaxis()->SetTitle("run number");
mean_npfps_pmtrack->GetYaxis()->SetTitle("number of PFPs per event");
mean_npfps_pmtrack->SetMarkerColor(kRed);
mean_npfps_pmtrack->SetMarkerStyle(20);
mean_npfps_pmtrack->SetMarkerSize(0.8);
mean_npfps_pmtrack->SetStats(0);
mean_npfps_pmtrack->Draw("P");
C31->Update();
mean_npfps_pandora->SetMarkerColor(kBlue);
mean_npfps_pandora->SetMarkerStyle(20);
mean_npfps_pandora->SetMarkerSize(0.8);
mean_npfps_pandora->SetStats(0);
mean_npfps_pandora->Draw("PSAME");

 C31->Update();
 TLine *npfpsMC_pmtrack=new TLine(C31->GetUxmin(),_f_mean_npfps_pmtrack_MC,C31->GetUxmax(),_f_mean_npfps_pmtrack_MC);
 npfpsMC_pmtrack->SetLineWidth(2);
 npfpsMC_pmtrack->SetLineColor(kRed);
 npfpsMC_pmtrack->Draw("SAME");
 C31->Update();
 TLine *npfpsMC_pandora=new TLine(C31->GetUxmin(),_f_mean_npfps_pandora_MC,C31->GetUxmax(),_f_mean_npfps_pandora_MC);
 npfpsMC_pandora->SetLineWidth(2);
 npfpsMC_pandora->SetLineColor(kBlue);
 npfpsMC_pandora->Draw("SAME");

C31->Update();
TLegend* leg_hist31 = new TLegend(0.80,0.70,0.95,0.95); //coordinates are fractions of pad dimensions
leg_hist31->AddEntry(mean_npfps_pmtrack,"pmtrack data","P");
leg_hist31->AddEntry(mean_npfps_pandora,"pandoraTrack data","P");
leg_hist31->AddEntry(npfpsMC_pmtrack,"pmtrack MC","L");
leg_hist31->AddEntry(npfpsMC_pandora,"pandoraTrack MC","L");

leg_hist31->SetFillColor(kWhite);
leg_hist31->Draw();

C31->Print("/Users/zhouyongshun/Desktop/Argonne/Module/StabilityDet/Plots_StabilityDet_V2.1/Plots_withMC/PFPs numbers mean.png");



TCanvas *C32 = new TCanvas("C32","",1200,600);
C32->SetGridx(1);
C32->SetGridy(1);
C32->Draw();
rms_npfps_pmtrack->SetTitle("Rms of number of PFPs per event vs run number");
rms_npfps_pmtrack->GetXaxis()->SetTitle("run number");
rms_npfps_pmtrack->GetYaxis()->SetTitle("number of PFPs per event");
rms_npfps_pmtrack->SetMarkerColor(kRed);
rms_npfps_pmtrack->SetMarkerStyle(20);
rms_npfps_pmtrack->SetMarkerSize(0.8);
rms_npfps_pmtrack->SetStats(0);
rms_npfps_pmtrack->Draw("P");
C32->Update();
rms_npfps_pandora->SetMarkerColor(kBlue);
rms_npfps_pandora->SetMarkerStyle(20);
rms_npfps_pandora->SetMarkerSize(0.8);
rms_npfps_pandora->SetStats(0);
rms_npfps_pandora->Draw("PSAME");

 C32->Update();
 TLine *npfpsMC_rms_pmtrack=new TLine(C32->GetUxmin(),_f_rms_npfps_pmtrack_MC,C32->GetUxmax(),_f_rms_npfps_pmtrack_MC);
 npfpsMC_rms_pmtrack->SetLineWidth(2);
 npfpsMC_rms_pmtrack->SetLineColor(kRed);
 npfpsMC_rms_pmtrack->Draw("SAME");
 C32->Update();
 TLine *npfpsMC_rms_pandora=new TLine(C32->GetUxmin(),_f_rms_npfps_pandora_MC,C32->GetUxmax(),_f_rms_npfps_pandora_MC);
 npfpsMC_rms_pandora->SetLineWidth(2);
 npfpsMC_rms_pandora->SetLineColor(kBlue);
 npfpsMC_rms_pandora->Draw("SAME");

C32->Update();
TLegend* leg_hist32 = new TLegend(0.80,0.70,0.95,0.95); //coordinates are fractions of pad dimensions
leg_hist32->AddEntry(rms_npfps_pmtrack,"pmtrack data","P");
leg_hist32->AddEntry(rms_npfps_pandora,"pandoraTrack data","P");
leg_hist32->AddEntry(npfpsMC_rms_pmtrack,"pmtrack MC","L");
leg_hist32->AddEntry(npfpsMC_rms_pandora,"pandoraTrack MC","L");

leg_hist32->SetFillColor(kWhite);
leg_hist32->Draw();

C32->Print("/Users/zhouyongshun/Desktop/Argonne/Module/StabilityDet/Plots_StabilityDet_V2.1/Plots_withMC/PFPs numbers rms.png");



TCanvas *C33 = new TCanvas("C33","",1200,600);
C33->SetGridx(1);
C33->SetGridy(1);
C33->Draw();
mean_shwrlen_pandoraShower->SetTitle("Average pandoraShower length per shower vs run number");
mean_shwrlen_pandoraShower->GetXaxis()->SetTitle("run number");
mean_shwrlen_pandoraShower->GetYaxis()->SetTitle("pandoraShower length per shower (cm)");
mean_shwrlen_pandoraShower->SetMarkerColor(kBlue);
mean_shwrlen_pandoraShower->SetMarkerStyle(20);
mean_shwrlen_pandoraShower->SetMarkerSize(0.8);
mean_shwrlen_pandoraShower->SetStats(0);
mean_shwrlen_pandoraShower->Draw();

 C33->Update();
 TLine *trackMC_pandoraShowerlen=new TLine(C33->GetUxmin(),_f_mean_shwrlen_pandoraShower_MC,C33->GetUxmax(),_f_mean_shwrlen_pandoraShower_MC);
 trackMC_pandoraShowerlen->SetLineWidth(2);
 trackMC_pandoraShowerlen->SetLineColor(kBlue);
 trackMC_pandoraShowerlen->Draw("SAME");

C33->Update();
TLegend* leg_hist33 = new TLegend(0.80,0.70,0.95,0.95); //coordinates are fractions of pad dimensions
leg_hist33->AddEntry(mean_shwrlen_pandoraShower,"Shower length data","P");
leg_hist33->AddEntry(trackMC_pandoraShowerlen,"Shower length MC","L");

leg_hist33->SetFillColor(kWhite);
leg_hist33->Draw();

C33->Print("/Users/zhouyongshun/Desktop/Argonne/Module/StabilityDet/Plots_StabilityDet_V2.1/Plots_withMC/pandoraShower length mean.png");



TCanvas *C34 = new TCanvas("C34","",1200,600);
C34->SetGridx(1);
C34->SetGridy(1);
C34->Draw();
rms_shwrlen_pandoraShower->SetTitle("Rms of pandoraShower length per shower vs run number");
rms_shwrlen_pandoraShower->GetXaxis()->SetTitle("run number");
rms_shwrlen_pandoraShower->GetYaxis()->SetTitle("pandoraShower length per shower (cm)");
rms_shwrlen_pandoraShower->SetMarkerColor(kBlue);
rms_shwrlen_pandoraShower->SetMarkerStyle(20);
rms_shwrlen_pandoraShower->SetMarkerSize(0.8);
rms_shwrlen_pandoraShower->SetStats(0);
rms_shwrlen_pandoraShower->Draw();

 C34->Update();
 TLine *trackMC_rms_pandoraShowerlen=new TLine(C34->GetUxmin(),_f_rms_shwrlen_pandoraShower_MC,C34->GetUxmax(),_f_rms_shwrlen_pandoraShower_MC);
 trackMC_rms_pandoraShowerlen->SetLineWidth(2);
 trackMC_rms_pandoraShowerlen->SetLineColor(kBlue);
 trackMC_rms_pandoraShowerlen->Draw("SAME");

C34->Update();
TLegend* leg_hist34 = new TLegend(0.80,0.70,0.95,0.95); //coordinates are fractions of pad dimensions
leg_hist34->AddEntry(rms_shwrlen_pandoraShower,"Shower length data","P");
leg_hist34->AddEntry(trackMC_rms_pandoraShowerlen,"Shower length MC","L");

leg_hist34->SetFillColor(kWhite);
leg_hist34->Draw();

C34->Print("/Users/zhouyongshun/Desktop/Argonne/Module/StabilityDet/Plots_StabilityDet_V2.1/Plots_withMC/pandoraShower length rms.png");



TCanvas *C35 = new TCanvas("C35","",1200,600);
C35->SetGridx(1);
C35->SetGridy(1);
C35->Draw();
mean_trackpos_beginx_pmtrack->SetTitle("Average trackpos beginx per track vs run number");
mean_trackpos_beginx_pmtrack->GetXaxis()->SetTitle("run number");
mean_trackpos_beginx_pmtrack->GetYaxis()->SetTitle("trackpos beginx per track (cm)");
mean_trackpos_beginx_pmtrack->SetMarkerColor(kRed);
mean_trackpos_beginx_pmtrack->SetMarkerStyle(20);
mean_trackpos_beginx_pmtrack->SetMarkerSize(0.8);
mean_trackpos_beginx_pmtrack->SetStats(0);
mean_trackpos_beginx_pmtrack->Draw("P");

C35->Update();
mean_trackpos_beginx_pandoraTrack->SetMarkerColor(kBlue);
mean_trackpos_beginx_pandoraTrack->SetMarkerStyle(20);
mean_trackpos_beginx_pandoraTrack->SetMarkerSize(0.8);
mean_trackpos_beginx_pandoraTrack->SetStats(0);
mean_trackpos_beginx_pandoraTrack->Draw("PSAME");

 C35->Update();
 TLine *trackMC_mean_trackpos_beginx_pmtrack=new TLine(C35->GetUxmin(),_f_mean_trackpos_beginx_pmtrack_MC,C35->GetUxmax(),_f_mean_trackpos_beginx_pmtrack_MC);
 trackMC_mean_trackpos_beginx_pmtrack->SetLineWidth(2);
 trackMC_mean_trackpos_beginx_pmtrack->SetLineColor(kRed);
 trackMC_mean_trackpos_beginx_pmtrack->Draw("SAME");
 TLine *trackMC_mean_trackpos_beginx_pandoraTrack=new TLine(C35->GetUxmin(),_f_mean_trackpos_beginx_pandoraTrack_MC,C35->GetUxmax(),_f_mean_trackpos_beginx_pandoraTrack_MC);
 trackMC_mean_trackpos_beginx_pandoraTrack->SetLineWidth(2);
 trackMC_mean_trackpos_beginx_pandoraTrack->SetLineColor(kBlue);
 trackMC_mean_trackpos_beginx_pandoraTrack->Draw("SAME");

C35->Update();
TLegend* leg_hist35 = new TLegend(0.80,0.70,0.95,0.95); //coordinates are fractions of pad dimensions
leg_hist35->AddEntry(mean_trackpos_beginx_pmtrack,"pmtrack data","P");
leg_hist35->AddEntry(mean_trackpos_beginx_pandoraTrack,"pandoraTrack data","P");
leg_hist35->AddEntry(trackMC_mean_trackpos_beginx_pmtrack,"pmtrack MC","L");
leg_hist35->AddEntry(trackMC_mean_trackpos_beginx_pandoraTrack,"pandoraTrack MC","L");

leg_hist35->SetFillColor(kWhite);
leg_hist35->Draw();

C35->Print("/Users/zhouyongshun/Desktop/Argonne/Module/StabilityDet/Plots_StabilityDet_V2.1/Plots_withMC/trackpos beginx mean.png");



TCanvas *C36 = new TCanvas("C36","",1200,600);
C36->SetGridx(1);
C36->SetGridy(1);
C36->Draw();
mean_trackpos_beginy_pmtrack->SetTitle("Average trackpos beginy per track vs run number");
mean_trackpos_beginy_pmtrack->GetXaxis()->SetTitle("run number");
mean_trackpos_beginy_pmtrack->GetYaxis()->SetTitle("trackpos beginy per track (cm)");
mean_trackpos_beginy_pmtrack->SetMarkerColor(kRed);
mean_trackpos_beginy_pmtrack->SetMarkerStyle(20);
mean_trackpos_beginy_pmtrack->SetMarkerSize(0.8);
mean_trackpos_beginy_pmtrack->SetStats(0);
mean_trackpos_beginy_pmtrack->Draw("P");

C36->Update();
mean_trackpos_beginy_pandoraTrack->SetMarkerColor(kBlue);
mean_trackpos_beginy_pandoraTrack->SetMarkerStyle(20);
mean_trackpos_beginy_pandoraTrack->SetMarkerSize(0.8);
mean_trackpos_beginy_pandoraTrack->SetStats(0);
mean_trackpos_beginy_pandoraTrack->Draw("PSAME");

 C36->Update();
 TLine *trackMC_mean_trackpos_beginy_pmtrack=new TLine(C36->GetUxmin(),_f_mean_trackpos_beginy_pmtrack_MC,C36->GetUxmax(),_f_mean_trackpos_beginy_pmtrack_MC);
 trackMC_mean_trackpos_beginy_pmtrack->SetLineWidth(2);
 trackMC_mean_trackpos_beginy_pmtrack->SetLineColor(kRed);
 trackMC_mean_trackpos_beginy_pmtrack->Draw("SAME");
 TLine *trackMC_mean_trackpos_beginy_pandoraTrack=new TLine(C36->GetUxmin(),_f_mean_trackpos_beginy_pandoraTrack_MC,C36->GetUxmax(),_f_mean_trackpos_beginy_pandoraTrack_MC);
 trackMC_mean_trackpos_beginy_pandoraTrack->SetLineWidth(2);
 trackMC_mean_trackpos_beginy_pandoraTrack->SetLineColor(kBlue);
 trackMC_mean_trackpos_beginy_pandoraTrack->Draw("SAME");

C36->Update();
TLegend* leg_hist36 = new TLegend(0.80,0.70,0.95,0.95); //coordinates are fractions of pad dimensions
leg_hist36->AddEntry(mean_trackpos_beginy_pmtrack,"pmtrack data","P");
leg_hist36->AddEntry(mean_trackpos_beginy_pandoraTrack,"pandoraTrack data","P");
leg_hist36->AddEntry(trackMC_mean_trackpos_beginy_pmtrack,"pmtrack MC","L");
leg_hist36->AddEntry(trackMC_mean_trackpos_beginy_pandoraTrack,"pandoraTrack MC","L");

leg_hist36->SetFillColor(kWhite);
leg_hist36->Draw();

C36->Print("/Users/zhouyongshun/Desktop/Argonne/Module/StabilityDet/Plots_StabilityDet_V2.1/Plots_withMC/trackpos beginy mean.png");



TCanvas *C37 = new TCanvas("C37","",1200,600);
C37->SetGridx(1);
C37->SetGridy(1);
C37->Draw();
mean_trackpos_beginz_pmtrack->SetTitle("Average trackpos beginz per track vs run number");
mean_trackpos_beginz_pmtrack->GetXaxis()->SetTitle("run number");
mean_trackpos_beginz_pmtrack->GetYaxis()->SetTitle("trackpos beginz per track (cm)");
mean_trackpos_beginz_pmtrack->SetMarkerColor(kRed);
mean_trackpos_beginz_pmtrack->SetMarkerStyle(20);
mean_trackpos_beginz_pmtrack->SetMarkerSize(0.8);
mean_trackpos_beginz_pmtrack->SetStats(0);
mean_trackpos_beginz_pmtrack->Draw("P");

C37->Update();
mean_trackpos_beginz_pandoraTrack->SetMarkerColor(kBlue);
mean_trackpos_beginz_pandoraTrack->SetMarkerStyle(20);
mean_trackpos_beginz_pandoraTrack->SetMarkerSize(0.8);
mean_trackpos_beginz_pandoraTrack->SetStats(0);
mean_trackpos_beginz_pandoraTrack->Draw("PSAME");

 C37->Update();
 TLine *trackMC_mean_trackpos_beginz_pmtrack=new TLine(C37->GetUxmin(),_f_mean_trackpos_beginz_pmtrack_MC,C37->GetUxmax(),_f_mean_trackpos_beginz_pmtrack_MC);
 trackMC_mean_trackpos_beginz_pmtrack->SetLineWidth(2);
 trackMC_mean_trackpos_beginz_pmtrack->SetLineColor(kRed);
 trackMC_mean_trackpos_beginz_pmtrack->Draw("SAME");
 TLine *trackMC_mean_trackpos_beginz_pandoraTrack=new TLine(C37->GetUxmin(),_f_mean_trackpos_beginz_pandoraTrack_MC,C37->GetUxmax(),_f_mean_trackpos_beginz_pandoraTrack_MC);
 trackMC_mean_trackpos_beginz_pandoraTrack->SetLineWidth(2);
 trackMC_mean_trackpos_beginz_pandoraTrack->SetLineColor(kBlue);
 trackMC_mean_trackpos_beginz_pandoraTrack->Draw("SAME");

C37->Update();
TLegend* leg_hist37 = new TLegend(0.80,0.70,0.95,0.95); //coordinates are fractions of pad dimensions
leg_hist37->AddEntry(mean_trackpos_beginz_pmtrack,"pmtrack data","P");
leg_hist37->AddEntry(mean_trackpos_beginz_pandoraTrack,"pandoraTrack data","P");
leg_hist37->AddEntry(trackMC_mean_trackpos_beginz_pmtrack,"pmtrack MC","L");
leg_hist37->AddEntry(trackMC_mean_trackpos_beginz_pandoraTrack,"pandoraTrack MC","L");

leg_hist37->SetFillColor(kWhite);
leg_hist37->Draw();

C37->Print("/Users/zhouyongshun/Desktop/Argonne/Module/StabilityDet/Plots_StabilityDet_V2.1/Plots_withMC/trackpos beginz mean.png");



TCanvas *C38 = new TCanvas("C38","",1200,600);
C38->SetGridx(1);
C38->SetGridy(1);
C38->Draw();
mean_trackpos_endx_pmtrack->SetTitle("Average trackpos endx per track vs run number");
mean_trackpos_endx_pmtrack->GetXaxis()->SetTitle("run number");
mean_trackpos_endx_pmtrack->GetYaxis()->SetTitle("trackpos endx per track (cm)");
mean_trackpos_endx_pmtrack->SetMarkerColor(kRed);
mean_trackpos_endx_pmtrack->SetMarkerStyle(20);
mean_trackpos_endx_pmtrack->SetMarkerSize(0.8);
mean_trackpos_endx_pmtrack->SetStats(0);
mean_trackpos_endx_pmtrack->Draw("P");

C38->Update();
mean_trackpos_endx_pandoraTrack->SetMarkerColor(kBlue);
mean_trackpos_endx_pandoraTrack->SetMarkerStyle(20);
mean_trackpos_endx_pandoraTrack->SetMarkerSize(0.8);
mean_trackpos_endx_pandoraTrack->SetStats(0);
mean_trackpos_endx_pandoraTrack->Draw("PSAME");

 C38->Update();
 TLine *trackMC_mean_trackpos_endx_pmtrack=new TLine(C38->GetUxmin(),_f_mean_trackpos_endx_pmtrack_MC,C38->GetUxmax(),_f_mean_trackpos_endx_pmtrack_MC);
 trackMC_mean_trackpos_endx_pmtrack->SetLineWidth(2);
 trackMC_mean_trackpos_endx_pmtrack->SetLineColor(kRed);
 trackMC_mean_trackpos_endx_pmtrack->Draw("SAME");
 TLine *trackMC_mean_trackpos_endx_pandoraTrack=new TLine(C38->GetUxmin(),_f_mean_trackpos_endx_pandoraTrack_MC,C38->GetUxmax(),_f_mean_trackpos_endx_pandoraTrack_MC);
 trackMC_mean_trackpos_endx_pandoraTrack->SetLineWidth(2);
 trackMC_mean_trackpos_endx_pandoraTrack->SetLineColor(kBlue);
 trackMC_mean_trackpos_endx_pandoraTrack->Draw("SAME");

C38->Update();
TLegend* leg_hist38 = new TLegend(0.80,0.70,0.95,0.95); //coordinates are fractions of pad dimensions
leg_hist38->AddEntry(mean_trackpos_endx_pmtrack,"pmtrack data","P");
leg_hist38->AddEntry(mean_trackpos_endx_pandoraTrack,"pandoraTrack data","P");
leg_hist38->AddEntry(trackMC_mean_trackpos_endx_pmtrack,"pmtrack MC","L");
leg_hist38->AddEntry(trackMC_mean_trackpos_endx_pandoraTrack,"pandoraTrack MC","L");

leg_hist38->SetFillColor(kWhite);
leg_hist38->Draw();

C38->Print("/Users/zhouyongshun/Desktop/Argonne/Module/StabilityDet/Plots_StabilityDet_V2.1/Plots_withMC/trackpos endx mean.png");



TCanvas *C39 = new TCanvas("C39","",1200,600);
C39->SetGridx(1);
C39->SetGridy(1);
C39->Draw();
mean_trackpos_endy_pmtrack->SetTitle("Average trackpos endy per track vs run number");
mean_trackpos_endy_pmtrack->GetXaxis()->SetTitle("run number");
mean_trackpos_endy_pmtrack->GetYaxis()->SetTitle("trackpos endy per track (cm)");
mean_trackpos_endy_pmtrack->SetMarkerColor(kRed);
mean_trackpos_endy_pmtrack->SetMarkerStyle(20);
mean_trackpos_endy_pmtrack->SetMarkerSize(0.8);
mean_trackpos_endy_pmtrack->SetStats(0);
mean_trackpos_endy_pmtrack->Draw("P");

C39->Update();
mean_trackpos_endy_pandoraTrack->SetMarkerColor(kBlue);
mean_trackpos_endy_pandoraTrack->SetMarkerStyle(20);
mean_trackpos_endy_pandoraTrack->SetMarkerSize(0.8);
mean_trackpos_endy_pandoraTrack->SetStats(0);
mean_trackpos_endy_pandoraTrack->Draw("PSAME");

 C39->Update();
 TLine *trackMC_mean_trackpos_endy_pmtrack=new TLine(C39->GetUxmin(),_f_mean_trackpos_endy_pmtrack_MC,C39->GetUxmax(),_f_mean_trackpos_endy_pmtrack_MC);
 trackMC_mean_trackpos_endy_pmtrack->SetLineWidth(2);
 trackMC_mean_trackpos_endy_pmtrack->SetLineColor(kRed);
 trackMC_mean_trackpos_endy_pmtrack->Draw("SAME");
 TLine *trackMC_mean_trackpos_endy_pandoraTrack=new TLine(C39->GetUxmin(),_f_mean_trackpos_endy_pandoraTrack_MC,C39->GetUxmax(),_f_mean_trackpos_endy_pandoraTrack_MC);
 trackMC_mean_trackpos_endy_pandoraTrack->SetLineWidth(2);
 trackMC_mean_trackpos_endy_pandoraTrack->SetLineColor(kBlue);
 trackMC_mean_trackpos_endy_pandoraTrack->Draw("SAME");

C39->Update();
TLegend* leg_hist39 = new TLegend(0.80,0.70,0.95,0.95); //coordinates are fractions of pad dimensions
leg_hist39->AddEntry(mean_trackpos_endy_pmtrack,"pmtrack data","P");
leg_hist39->AddEntry(mean_trackpos_endy_pandoraTrack,"pandoraTrack data","P");
leg_hist39->AddEntry(trackMC_mean_trackpos_endy_pmtrack,"pmtrack MC","L");
leg_hist39->AddEntry(trackMC_mean_trackpos_endy_pandoraTrack,"pandoraTrack MC","L");

leg_hist39->SetFillColor(kWhite);
leg_hist39->Draw();

C39->Print("/Users/zhouyongshun/Desktop/Argonne/Module/StabilityDet/Plots_StabilityDet_V2.1/Plots_withMC/trackpos endy mean.png");



TCanvas *C40 = new TCanvas("C40","",1200,600);
C40->SetGridx(1);
C40->SetGridy(1);
C40->Draw();
mean_trackpos_endz_pmtrack->SetTitle("Average trackpos endz per track vs run number");
mean_trackpos_endz_pmtrack->GetXaxis()->SetTitle("run number");
mean_trackpos_endz_pmtrack->GetYaxis()->SetTitle("trackpos endz per track (cm)");
mean_trackpos_endz_pmtrack->SetMarkerColor(kRed);
mean_trackpos_endz_pmtrack->SetMarkerStyle(20);
mean_trackpos_endz_pmtrack->SetMarkerSize(0.8);
mean_trackpos_endz_pmtrack->SetStats(0);
mean_trackpos_endz_pmtrack->Draw("P");

C40->Update();
mean_trackpos_endz_pandoraTrack->SetMarkerColor(kBlue);
mean_trackpos_endz_pandoraTrack->SetMarkerStyle(20);
mean_trackpos_endz_pandoraTrack->SetMarkerSize(0.8);
mean_trackpos_endz_pandoraTrack->SetStats(0);
mean_trackpos_endz_pandoraTrack->Draw("PSAME");

 C40->Update();
 TLine *trackMC_mean_trackpos_endz_pmtrack=new TLine(C40->GetUxmin(),_f_mean_trackpos_endz_pmtrack_MC,C40->GetUxmax(),_f_mean_trackpos_endz_pmtrack_MC);
 trackMC_mean_trackpos_endz_pmtrack->SetLineWidth(2);
 trackMC_mean_trackpos_endz_pmtrack->SetLineColor(kRed);
 trackMC_mean_trackpos_endz_pmtrack->Draw("SAME");
 TLine *trackMC_mean_trackpos_endz_pandoraTrack=new TLine(C40->GetUxmin(),_f_mean_trackpos_endz_pandoraTrack_MC,C40->GetUxmax(),_f_mean_trackpos_endz_pandoraTrack_MC);
 trackMC_mean_trackpos_endz_pandoraTrack->SetLineWidth(2);
 trackMC_mean_trackpos_endz_pandoraTrack->SetLineColor(kBlue);
 trackMC_mean_trackpos_endz_pandoraTrack->Draw("SAME");

C40->Update();
TLegend* leg_hist40 = new TLegend(0.80,0.70,0.95,0.95); //coordinates are fractions of pad dimensions
leg_hist40->AddEntry(mean_trackpos_endz_pmtrack,"pmtrack data","P");
leg_hist40->AddEntry(mean_trackpos_endz_pandoraTrack,"pandoraTrack data","P");
leg_hist40->AddEntry(trackMC_mean_trackpos_endz_pmtrack,"pmtrack MC","L");
leg_hist40->AddEntry(trackMC_mean_trackpos_endz_pandoraTrack,"pandoraTrack MC","L");

leg_hist40->SetFillColor(kWhite);
leg_hist40->Draw();

C40->Print("/Users/zhouyongshun/Desktop/Argonne/Module/StabilityDet/Plots_StabilityDet_V2.1/Plots_withMC/trackpos endz mean.png");




TCanvas *C41 = new TCanvas("C41","",1200,600);
C41->SetGridx(1);
C41->SetGridy(1);
C41->Draw();
mean_Intflash_ywidth->SetTitle("Average opflash ywidth per flash vs run number");
mean_Intflash_ywidth->GetXaxis()->SetTitle("run number");
mean_Intflash_ywidth->GetYaxis()->SetTitle("opflash ywidth per flash (cm)");
mean_Intflash_ywidth->SetMarkerColor(kRed);
mean_Intflash_ywidth->SetMarkerStyle(20);
mean_Intflash_ywidth->SetMarkerSize(0.8);
mean_Intflash_ywidth->SetStats(0);
mean_Intflash_ywidth->Draw("P");

C41->Update();
mean_Extflash_ywidth->SetMarkerColor(kBlue);
mean_Extflash_ywidth->SetMarkerStyle(20);
mean_Extflash_ywidth->SetMarkerSize(0.8);
mean_Extflash_ywidth->SetStats(0);
mean_Extflash_ywidth->Draw("PSAME");

 C41->Update();
 TLine *trackMC_mean_Intflash_ywidth =new TLine(C41->GetUxmin(),_f_mean_Intflash_ywidth_MC,C41->GetUxmax(),_f_mean_Intflash_ywidth_MC);
 trackMC_mean_Intflash_ywidth ->SetLineWidth(2);
 trackMC_mean_Intflash_ywidth ->SetLineColor(kRed);
 trackMC_mean_Intflash_ywidth ->Draw("SAME");
 /*TLine *trackMC_mean_Extflash_ywidth =new TLine(C41->GetUxmin(),_f_mean_Extflash_ywidth_MC,C41->GetUxmax(),_f_mean_Extflash_ywidth_MC);
 trackMC_mean_Extflash_ywidth ->SetLineWidth(2);
 trackMC_mean_Extflash_ywidth ->SetLineColor(kBlue);
 trackMC_mean_Extflash_ywidth ->Draw("SAME");*/

C41->Update();
TLegend* leg_hist41 = new TLegend(0.80,0.70,0.95,0.95); //coordinates are fractions of pad dimensions
leg_hist41->AddEntry(mean_Intflash_ywidth,"Internal opflash data","P");
leg_hist41->AddEntry(mean_Extflash_ywidth,"External opflash data","P");
leg_hist41->AddEntry(trackMC_mean_Intflash_ywidth,"Internal opflash MC","L");
//leg_hist41->AddEntry(trackMC_mean_Extflash_ywidth,"External opflash MC","L");

leg_hist41->SetFillColor(kWhite);
leg_hist41->Draw();

C41->Print("/Users/zhouyongshun/Desktop/Argonne/Module/StabilityDet/Plots_StabilityDet_V2.1/Plots_withMC/flash ywidth mean.png");




TCanvas *C42 = new TCanvas("C42","",1200,600);
C42->SetGridx(1);
C42->SetGridy(1);
C42->Draw();
mean_Intflash_zwidth->SetTitle("Average opflash zwidth per flash vs run number");
mean_Intflash_zwidth->GetXaxis()->SetTitle("run number");
mean_Intflash_zwidth->GetYaxis()->SetTitle("opflash zwidth per flash (cm)");
mean_Intflash_zwidth->SetMarkerColor(kRed);
mean_Intflash_zwidth->SetMarkerStyle(20);
mean_Intflash_zwidth->SetMarkerSize(0.8);
mean_Intflash_zwidth->SetStats(0);
mean_Intflash_zwidth->Draw("P");

C42->Update();
mean_Extflash_zwidth->SetMarkerColor(kBlue);
mean_Extflash_zwidth->SetMarkerStyle(20);
mean_Extflash_zwidth->SetMarkerSize(0.8);
mean_Extflash_zwidth->SetStats(0);
mean_Extflash_zwidth->Draw("PSAME");

 C42->Update();
 TLine *trackMC_mean_Intflash_zwidth =new TLine(C42->GetUxmin(),_f_mean_Intflash_zwidth_MC,C42->GetUxmax(),_f_mean_Intflash_zwidth_MC);
 trackMC_mean_Intflash_zwidth ->SetLineWidth(2);
 trackMC_mean_Intflash_zwidth ->SetLineColor(kRed);
 trackMC_mean_Intflash_zwidth ->Draw("SAME");
 /*TLine *trackMC_mean_Extflash_zwidth =new TLine(C42->GetUxmin(),_f_mean_Extflash_zwidth_MC,C42->GetUxmax(),_f_mean_Extflash_zwidth_MC);
 trackMC_mean_Extflash_zwidth ->SetLineWidth(2);
 trackMC_mean_Extflash_zwidth ->SetLineColor(kBlue);
 trackMC_mean_Extflash_zwidth ->Draw("SAME");*/

C42->Update();
TLegend* leg_hist42 = new TLegend(0.80,0.70,0.95,0.95); //coordinates are fractions of pad dimensions
leg_hist42->AddEntry(mean_Intflash_zwidth,"Internal opflash data","P");
leg_hist42->AddEntry(mean_Extflash_zwidth,"External opflash data","P");
leg_hist42->AddEntry(trackMC_mean_Intflash_zwidth,"Internal opflash MC","L");
//leg_hist42->AddEntry(trackMC_mean_Extflash_zwidth,"External opflash MC","L");

leg_hist42->SetFillColor(kWhite);
leg_hist42->Draw();

C42->Print("/Users/zhouyongshun/Desktop/Argonne/Module/StabilityDet/Plots_StabilityDet_V2.1/Plots_withMC/flash zwidth mean.png");



TCanvas *C43 = new TCanvas("C43","",1200,600);
C43->SetGridx(1);
C43->SetGridy(1);
C43->Draw();
rms_trackpos_beginx_pmtrack->SetTitle("Rms of trackpos beginx per track vs run number");
rms_trackpos_beginx_pmtrack->GetXaxis()->SetTitle("run number");
rms_trackpos_beginx_pmtrack->GetYaxis()->SetTitle("trackpos beginx per track (cm)");
rms_trackpos_beginx_pmtrack->SetMarkerColor(kRed);
rms_trackpos_beginx_pmtrack->SetMarkerStyle(20);
rms_trackpos_beginx_pmtrack->SetMarkerSize(0.8);
rms_trackpos_beginx_pmtrack->SetStats(0);
rms_trackpos_beginx_pmtrack->Draw("P");

C43->Update();
rms_trackpos_beginx_pandoraTrack->SetMarkerColor(kBlue);
rms_trackpos_beginx_pandoraTrack->SetMarkerStyle(20);
rms_trackpos_beginx_pandoraTrack->SetMarkerSize(0.8);
rms_trackpos_beginx_pandoraTrack->SetStats(0);
rms_trackpos_beginx_pandoraTrack->Draw("PSAME");

 C43->Update();
 TLine *trackMC_rms_trackpos_beginx_pmtrack=new TLine(C43->GetUxmin(),_f_rms_trackpos_beginx_pmtrack_MC,C43->GetUxmax(),_f_rms_trackpos_beginx_pmtrack_MC);
 trackMC_rms_trackpos_beginx_pmtrack->SetLineWidth(2);
 trackMC_rms_trackpos_beginx_pmtrack->SetLineColor(kRed);
 trackMC_rms_trackpos_beginx_pmtrack->Draw("SAME");
 TLine *trackMC_rms_trackpos_beginx_pandoraTrack=new TLine(C43->GetUxmin(),_f_rms_trackpos_beginx_pandoraTrack_MC,C43->GetUxmax(),_f_rms_trackpos_beginx_pandoraTrack_MC);
 trackMC_rms_trackpos_beginx_pandoraTrack->SetLineWidth(2);
 trackMC_rms_trackpos_beginx_pandoraTrack->SetLineColor(kBlue);
 trackMC_rms_trackpos_beginx_pandoraTrack->Draw("SAME");

C43->Update();
TLegend* leg_hist43 = new TLegend(0.80,0.70,0.95,0.95); //coordinates are fractions of pad dimensions
leg_hist43->AddEntry(rms_trackpos_beginx_pmtrack,"pmtrack data","P");
leg_hist43->AddEntry(rms_trackpos_beginx_pandoraTrack,"pandoraTrack data","P");
leg_hist43->AddEntry(trackMC_rms_trackpos_beginx_pmtrack,"pmtrack MC","L");
leg_hist43->AddEntry(trackMC_rms_trackpos_beginx_pandoraTrack,"pandoraTrack MC","L");

leg_hist43->SetFillColor(kWhite);
leg_hist43->Draw();

C43->Print("/Users/zhouyongshun/Desktop/Argonne/Module/StabilityDet/Plots_StabilityDet_V2.1/Plots_withMC/trackpos beginx rms.png");



TCanvas *C44 = new TCanvas("C44","",1200,600);
C44->SetGridx(1);
C44->SetGridy(1);
C44->Draw();
rms_trackpos_beginy_pmtrack->SetTitle("Rms of trackpos beginy per track vs run number");
rms_trackpos_beginy_pmtrack->GetXaxis()->SetTitle("run number");
rms_trackpos_beginy_pmtrack->GetYaxis()->SetTitle("trackpos beginy per track (cm)");
rms_trackpos_beginy_pmtrack->SetMarkerColor(kRed);
rms_trackpos_beginy_pmtrack->SetMarkerStyle(20);
rms_trackpos_beginy_pmtrack->SetMarkerSize(0.8);
rms_trackpos_beginy_pmtrack->SetStats(0);
rms_trackpos_beginy_pmtrack->Draw("P");

C44->Update();
rms_trackpos_beginy_pandoraTrack->SetMarkerColor(kBlue);
rms_trackpos_beginy_pandoraTrack->SetMarkerStyle(20);
rms_trackpos_beginy_pandoraTrack->SetMarkerSize(0.8);
rms_trackpos_beginy_pandoraTrack->SetStats(0);
rms_trackpos_beginy_pandoraTrack->Draw("PSAME");

 C44->Update();
 TLine *trackMC_rms_trackpos_beginy_pmtrack=new TLine(C44->GetUxmin(),_f_rms_trackpos_beginy_pmtrack_MC,C44->GetUxmax(),_f_rms_trackpos_beginy_pmtrack_MC);
 trackMC_rms_trackpos_beginy_pmtrack->SetLineWidth(2);
 trackMC_rms_trackpos_beginy_pmtrack->SetLineColor(kRed);
 trackMC_rms_trackpos_beginy_pmtrack->Draw("SAME");
 TLine *trackMC_rms_trackpos_beginy_pandoraTrack=new TLine(C44->GetUxmin(),_f_rms_trackpos_beginy_pandoraTrack_MC,C44->GetUxmax(),_f_rms_trackpos_beginy_pandoraTrack_MC);
 trackMC_rms_trackpos_beginy_pandoraTrack->SetLineWidth(2);
 trackMC_rms_trackpos_beginy_pandoraTrack->SetLineColor(kBlue);
 trackMC_rms_trackpos_beginy_pandoraTrack->Draw("SAME");

C44->Update();
TLegend* leg_hist44 = new TLegend(0.80,0.70,0.95,0.95); //coordinates are fractions of pad dimensions
leg_hist44->AddEntry(rms_trackpos_beginy_pmtrack,"pmtrack data","P");
leg_hist44->AddEntry(rms_trackpos_beginy_pandoraTrack,"pandoraTrack data","P");
leg_hist44->AddEntry(trackMC_rms_trackpos_beginy_pmtrack,"pmtrack MC","L");
leg_hist44->AddEntry(trackMC_rms_trackpos_beginy_pandoraTrack,"pandoraTrack MC","L");

leg_hist44->SetFillColor(kWhite);
leg_hist44->Draw();

C44->Print("/Users/zhouyongshun/Desktop/Argonne/Module/StabilityDet/Plots_StabilityDet_V2.1/Plots_withMC/trackpos beginy rms.png");



TCanvas *C45 = new TCanvas("C45","",1200,600);
C45->SetGridx(1);
C45->SetGridy(1);
C45->Draw();
rms_trackpos_beginz_pmtrack->SetTitle("Rms of trackpos beginz per track vs run number");
rms_trackpos_beginz_pmtrack->GetXaxis()->SetTitle("run number");
rms_trackpos_beginz_pmtrack->GetYaxis()->SetTitle("trackpos beginz per track (cm)");
rms_trackpos_beginz_pmtrack->SetMarkerColor(kRed);
rms_trackpos_beginz_pmtrack->SetMarkerStyle(20);
rms_trackpos_beginz_pmtrack->SetMarkerSize(0.8);
rms_trackpos_beginz_pmtrack->SetStats(0);
rms_trackpos_beginz_pmtrack->Draw("P");

C45->Update();
rms_trackpos_beginz_pandoraTrack->SetMarkerColor(kBlue);
rms_trackpos_beginz_pandoraTrack->SetMarkerStyle(20);
rms_trackpos_beginz_pandoraTrack->SetMarkerSize(0.8);
rms_trackpos_beginz_pandoraTrack->SetStats(0);
rms_trackpos_beginz_pandoraTrack->Draw("PSAME");

 C45->Update();
 TLine *trackMC_rms_trackpos_beginz_pmtrack=new TLine(C45->GetUxmin(),_f_rms_trackpos_beginz_pmtrack_MC,C45->GetUxmax(),_f_rms_trackpos_beginz_pmtrack_MC);
 trackMC_rms_trackpos_beginz_pmtrack->SetLineWidth(2);
 trackMC_rms_trackpos_beginz_pmtrack->SetLineColor(kRed);
 trackMC_rms_trackpos_beginz_pmtrack->Draw("SAME");
 TLine *trackMC_rms_trackpos_beginz_pandoraTrack=new TLine(C45->GetUxmin(),_f_rms_trackpos_beginz_pandoraTrack_MC,C45->GetUxmax(),_f_rms_trackpos_beginz_pandoraTrack_MC);
 trackMC_rms_trackpos_beginz_pandoraTrack->SetLineWidth(2);
 trackMC_rms_trackpos_beginz_pandoraTrack->SetLineColor(kBlue);
 trackMC_rms_trackpos_beginz_pandoraTrack->Draw("SAME");

C45->Update();
TLegend* leg_hist45 = new TLegend(0.80,0.70,0.95,0.95); //coordinates are fractions of pad dimensions
leg_hist45->AddEntry(rms_trackpos_beginz_pmtrack,"pmtrack data","P");
leg_hist45->AddEntry(rms_trackpos_beginz_pandoraTrack,"pandoraTrack data","P");
leg_hist45->AddEntry(trackMC_rms_trackpos_beginz_pmtrack,"pmtrack MC","L");
leg_hist45->AddEntry(trackMC_rms_trackpos_beginz_pandoraTrack,"pandoraTrack MC","L");

leg_hist45->SetFillColor(kWhite);
leg_hist45->Draw();

C45->Print("/Users/zhouyongshun/Desktop/Argonne/Module/StabilityDet/Plots_StabilityDet_V2.1/Plots_withMC/trackpos beginz rms.png");



TCanvas *C46 = new TCanvas("C46","",1200,600);
C46->SetGridx(1);
C46->SetGridy(1);
C46->Draw();
rms_trackpos_endx_pmtrack->SetTitle("Rms of trackpos endx per track vs run number");
rms_trackpos_endx_pmtrack->GetXaxis()->SetTitle("run number");
rms_trackpos_endx_pmtrack->GetYaxis()->SetTitle("trackpos endx per track (cm)");
rms_trackpos_endx_pmtrack->SetMarkerColor(kRed);
rms_trackpos_endx_pmtrack->SetMarkerStyle(20);
rms_trackpos_endx_pmtrack->SetMarkerSize(0.8);
rms_trackpos_endx_pmtrack->SetStats(0);
rms_trackpos_endx_pmtrack->Draw("P");

C46->Update();
rms_trackpos_endx_pandoraTrack->SetMarkerColor(kBlue);
rms_trackpos_endx_pandoraTrack->SetMarkerStyle(20);
rms_trackpos_endx_pandoraTrack->SetMarkerSize(0.8);
rms_trackpos_endx_pandoraTrack->SetStats(0);
rms_trackpos_endx_pandoraTrack->Draw("PSAME");

 C46->Update();
 TLine *trackMC_rms_trackpos_endx_pmtrack=new TLine(C46->GetUxmin(),_f_rms_trackpos_endx_pmtrack_MC,C46->GetUxmax(),_f_rms_trackpos_endx_pmtrack_MC);
 trackMC_rms_trackpos_endx_pmtrack->SetLineWidth(2);
 trackMC_rms_trackpos_endx_pmtrack->SetLineColor(kRed);
 trackMC_rms_trackpos_endx_pmtrack->Draw("SAME");
 TLine *trackMC_rms_trackpos_endx_pandoraTrack=new TLine(C46->GetUxmin(),_f_rms_trackpos_endx_pandoraTrack_MC,C46->GetUxmax(),_f_rms_trackpos_endx_pandoraTrack_MC);
 trackMC_rms_trackpos_endx_pandoraTrack->SetLineWidth(2);
 trackMC_rms_trackpos_endx_pandoraTrack->SetLineColor(kBlue);
 trackMC_rms_trackpos_endx_pandoraTrack->Draw("SAME");

C46->Update();
TLegend* leg_hist46 = new TLegend(0.80,0.70,0.95,0.95); //coordinates are fractions of pad dimensions
leg_hist46->AddEntry(rms_trackpos_endx_pmtrack,"pmtrack data","P");
leg_hist46->AddEntry(rms_trackpos_endx_pandoraTrack,"pandoraTrack data","P");
leg_hist46->AddEntry(trackMC_rms_trackpos_endx_pmtrack,"pmtrack MC","L");
leg_hist46->AddEntry(trackMC_rms_trackpos_endx_pandoraTrack,"pandoraTrack MC","L");

leg_hist46->SetFillColor(kWhite);
leg_hist46->Draw();

C46->Print("/Users/zhouyongshun/Desktop/Argonne/Module/StabilityDet/Plots_StabilityDet_V2.1/Plots_withMC/trackpos endx rms.png");



TCanvas *C47 = new TCanvas("C47","",1200,600);
C47->SetGridx(1);
C47->SetGridy(1);
C47->Draw();
rms_trackpos_endy_pmtrack->SetTitle("Rms of trackpos endy per track vs run number");
rms_trackpos_endy_pmtrack->GetXaxis()->SetTitle("run number");
rms_trackpos_endy_pmtrack->GetYaxis()->SetTitle("trackpos endy per track (cm)");
rms_trackpos_endy_pmtrack->SetMarkerColor(kRed);
rms_trackpos_endy_pmtrack->SetMarkerStyle(20);
rms_trackpos_endy_pmtrack->SetMarkerSize(0.8);
rms_trackpos_endy_pmtrack->SetStats(0);
rms_trackpos_endy_pmtrack->Draw("P");

C47->Update();
rms_trackpos_endy_pandoraTrack->SetMarkerColor(kBlue);
rms_trackpos_endy_pandoraTrack->SetMarkerStyle(20);
rms_trackpos_endy_pandoraTrack->SetMarkerSize(0.8);
rms_trackpos_endy_pandoraTrack->SetStats(0);
rms_trackpos_endy_pandoraTrack->Draw("PSAME");

 C47->Update();
 TLine *trackMC_rms_trackpos_endy_pmtrack=new TLine(C47->GetUxmin(),_f_rms_trackpos_endy_pmtrack_MC,C47->GetUxmax(),_f_rms_trackpos_endy_pmtrack_MC);
 trackMC_rms_trackpos_endy_pmtrack->SetLineWidth(2);
 trackMC_rms_trackpos_endy_pmtrack->SetLineColor(kRed);
 trackMC_rms_trackpos_endy_pmtrack->Draw("SAME");
 TLine *trackMC_rms_trackpos_endy_pandoraTrack=new TLine(C47->GetUxmin(),_f_rms_trackpos_endy_pandoraTrack_MC,C47->GetUxmax(),_f_rms_trackpos_endy_pandoraTrack_MC);
 trackMC_rms_trackpos_endy_pandoraTrack->SetLineWidth(2);
 trackMC_rms_trackpos_endy_pandoraTrack->SetLineColor(kBlue);
 trackMC_rms_trackpos_endy_pandoraTrack->Draw("SAME");

C47->Update();
TLegend* leg_hist47 = new TLegend(0.80,0.70,0.95,0.95); //coordinates are fractions of pad dimensions
leg_hist47->AddEntry(rms_trackpos_endy_pmtrack,"pmtrack data","P");
leg_hist47->AddEntry(rms_trackpos_endy_pandoraTrack,"pandoraTrack data","P");
leg_hist47->AddEntry(trackMC_rms_trackpos_endy_pmtrack,"pmtrack MC","L");
leg_hist47->AddEntry(trackMC_rms_trackpos_endy_pandoraTrack,"pandoraTrack MC","L");

leg_hist47->SetFillColor(kWhite);
leg_hist47->Draw();

C47->Print("/Users/zhouyongshun/Desktop/Argonne/Module/StabilityDet/Plots_StabilityDet_V2.1/Plots_withMC/trackpos endy rms.png");



TCanvas *C48 = new TCanvas("C48","",1200,600);
C48->SetGridx(1);
C48->SetGridy(1);
C48->Draw();
rms_trackpos_endz_pmtrack->SetTitle("Rms of trackpos endz per track vs run number");
rms_trackpos_endz_pmtrack->GetXaxis()->SetTitle("run number");
rms_trackpos_endz_pmtrack->GetYaxis()->SetTitle("trackpos endz per track (cm)");
rms_trackpos_endz_pmtrack->SetMarkerColor(kRed);
rms_trackpos_endz_pmtrack->SetMarkerStyle(20);
rms_trackpos_endz_pmtrack->SetMarkerSize(0.8);
rms_trackpos_endz_pmtrack->SetStats(0);
rms_trackpos_endz_pmtrack->Draw("P");

C48->Update();
rms_trackpos_endz_pandoraTrack->SetMarkerColor(kBlue);
rms_trackpos_endz_pandoraTrack->SetMarkerStyle(20);
rms_trackpos_endz_pandoraTrack->SetMarkerSize(0.8);
rms_trackpos_endz_pandoraTrack->SetStats(0);
rms_trackpos_endz_pandoraTrack->Draw("PSAME");

 C48->Update();
 TLine *trackMC_rms_trackpos_endz_pmtrack=new TLine(C48->GetUxmin(),_f_rms_trackpos_endz_pmtrack_MC,C48->GetUxmax(),_f_rms_trackpos_endz_pmtrack_MC);
 trackMC_rms_trackpos_endz_pmtrack->SetLineWidth(2);
 trackMC_rms_trackpos_endz_pmtrack->SetLineColor(kRed);
 trackMC_rms_trackpos_endz_pmtrack->Draw("SAME");
 TLine *trackMC_rms_trackpos_endz_pandoraTrack=new TLine(C48->GetUxmin(),_f_rms_trackpos_endz_pandoraTrack_MC,C48->GetUxmax(),_f_rms_trackpos_endz_pandoraTrack_MC);
 trackMC_rms_trackpos_endz_pandoraTrack->SetLineWidth(2);
 trackMC_rms_trackpos_endz_pandoraTrack->SetLineColor(kBlue);
 trackMC_rms_trackpos_endz_pandoraTrack->Draw("SAME");

C48->Update();
TLegend* leg_hist48 = new TLegend(0.80,0.70,0.95,0.95); //coordinates are fractions of pad dimensions
leg_hist48->AddEntry(rms_trackpos_endz_pmtrack,"pmtrack data","P");
leg_hist48->AddEntry(rms_trackpos_endz_pandoraTrack,"pandoraTrack data","P");
leg_hist48->AddEntry(trackMC_rms_trackpos_endz_pmtrack,"pmtrack MC","L");
leg_hist48->AddEntry(trackMC_rms_trackpos_endz_pandoraTrack,"pandoraTrack MC","L");

leg_hist48->SetFillColor(kWhite);
leg_hist48->Draw();

C48->Print("/Users/zhouyongshun/Desktop/Argonne/Module/StabilityDet/Plots_StabilityDet_V2.1/Plots_withMC/trackpos endz rms.png");




TCanvas *C49 = new TCanvas("C49","",1200,600);
C49->SetGridx(1);
C49->SetGridy(1);
C49->Draw();
rms_Intflash_ywidth->SetTitle("Rms of opflash ywidth per flash vs run number");
rms_Intflash_ywidth->GetXaxis()->SetTitle("run number");
rms_Intflash_ywidth->GetYaxis()->SetTitle("opflash ywidth per flash (cm)");
rms_Intflash_ywidth->SetMarkerColor(kRed);
rms_Intflash_ywidth->SetMarkerStyle(20);
rms_Intflash_ywidth->SetMarkerSize(0.8);
rms_Intflash_ywidth->SetStats(0);
rms_Intflash_ywidth->Draw("P");

C49->Update();
rms_Extflash_ywidth->SetMarkerColor(kBlue);
rms_Extflash_ywidth->SetMarkerStyle(20);
rms_Extflash_ywidth->SetMarkerSize(0.8);
rms_Extflash_ywidth->SetStats(0);
rms_Extflash_ywidth->Draw("PSAME");

 C49->Update();
 TLine *trackMC_rms_Intflash_ywidth =new TLine(C49->GetUxmin(),_f_rms_Intflash_ywidth_MC,C49->GetUxmax(),_f_rms_Intflash_ywidth_MC);
 trackMC_rms_Intflash_ywidth ->SetLineWidth(2);
 trackMC_rms_Intflash_ywidth ->SetLineColor(kRed);
 trackMC_rms_Intflash_ywidth ->Draw("SAME");
 /*TLine *trackMC_rms_Extflash_ywidth =new TLine(C49->GetUxmin(),_f_rms_Extflash_ywidth_MC,C49->GetUxmax(),_f_rms_Extflash_ywidth_MC);
 trackMC_rms_Extflash_ywidth ->SetLineWidth(2);
 trackMC_rms_Extflash_ywidth ->SetLineColor(kBlue);
 trackMC_rms_Extflash_ywidth ->Draw("SAME");*/

C49->Update();
TLegend* leg_hist49 = new TLegend(0.80,0.70,0.95,0.95); //coordinates are fractions of pad dimensions
leg_hist49->AddEntry(rms_Intflash_ywidth,"Internal opflash data","P");
leg_hist49->AddEntry(rms_Extflash_ywidth,"External opflash data","P");
leg_hist49->AddEntry(trackMC_rms_Intflash_ywidth,"Internal opflash MC","L");
//leg_hist49->AddEntry(trackMC_rms_Extflash_ywidth,"External opflash MC","L");

leg_hist49->SetFillColor(kWhite);
leg_hist49->Draw();

C49->Print("/Users/zhouyongshun/Desktop/Argonne/Module/StabilityDet/Plots_StabilityDet_V2.1/Plots_withMC/flash ywidth rms.png");




TCanvas *C50 = new TCanvas("C50","",1200,600);
C50->SetGridx(1);
C50->SetGridy(1);
C50->Draw();
rms_Intflash_zwidth->SetTitle("Rms of opflash zwidth per flash vs run number");
rms_Intflash_zwidth->GetXaxis()->SetTitle("run number");
rms_Intflash_zwidth->GetYaxis()->SetTitle("opflash zwidth per flash (cm)");
rms_Intflash_zwidth->SetMarkerColor(kRed);
rms_Intflash_zwidth->SetMarkerStyle(20);
rms_Intflash_zwidth->SetMarkerSize(0.8);
rms_Intflash_zwidth->SetStats(0);
rms_Intflash_zwidth->Draw("P");

C50->Update();
rms_Extflash_zwidth->SetMarkerColor(kBlue);
rms_Extflash_zwidth->SetMarkerStyle(20);
rms_Extflash_zwidth->SetMarkerSize(0.8);
rms_Extflash_zwidth->SetStats(0);
rms_Extflash_zwidth->Draw("PSAME");

 C50->Update();
 TLine *trackMC_rms_Intflash_zwidth =new TLine(C50->GetUxmin(),_f_rms_Intflash_zwidth_MC,C50->GetUxmax(),_f_rms_Intflash_zwidth_MC);
 trackMC_rms_Intflash_zwidth ->SetLineWidth(2);
 trackMC_rms_Intflash_zwidth ->SetLineColor(kRed);
 trackMC_rms_Intflash_zwidth ->Draw("SAME");
 /*TLine *trackMC_rms_Extflash_zwidth =new TLine(C50->GetUxmin(),_f_rms_Extflash_zwidth_MC,C50->GetUxmax(),_f_rms_Extflash_zwidth_MC);
 trackMC_rms_Extflash_zwidth ->SetLineWidth(2);
 trackMC_rms_Extflash_zwidth ->SetLineColor(kBlue);
 trackMC_rms_Extflash_zwidth ->Draw("SAME");*/

C50->Update();
TLegend* leg_hist50 = new TLegend(0.80,0.70,0.95,0.95); //coordinates are fractions of pad dimensions
leg_hist50->AddEntry(rms_Intflash_zwidth,"Internal opflash data","P");
leg_hist50->AddEntry(rms_Extflash_zwidth,"External opflash data","P");
leg_hist50->AddEntry(trackMC_rms_Intflash_zwidth,"Internal opflash MC","L");
//leg_hist50->AddEntry(trackMC_rms_Extflash_zwidth,"External opflash MC","L");

leg_hist50->SetFillColor(kWhite);
leg_hist50->Draw();

C50->Print("/Users/zhouyongshun/Desktop/Argonne/Module/StabilityDet/Plots_StabilityDet_V2.1/Plots_withMC/flash zwidth rms.png");

}
