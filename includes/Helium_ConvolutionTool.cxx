#include "Helium_ConvolutionTool.h"

double return_AlWgt(CryoTank_REGIONS input_region , Material_type input_material){

if(input_material == kAluminium){
 if(input_region==kUpstream_head){return Al_wgts::upstream; }
   else if(input_region==kCenter){return Al_wgts::barrel; }
   else if(input_region==kDownstream_head){return Al_wgts::downstream; }
   else if(input_region==kDownstream_ConcaveCap){return Al_wgts::concave; }
   else{std::cout<<"unKnown Input for return_AlWgt something needs to be FIXED !!!  "<< std::endl; assert(false);}
 }

else {return 1.0;}

}


double return_shiftX(){return VertexShiftValues::Shift_X;}
double return_shiftY(){return VertexShiftValues::Shift_Y;}
double return_shiftZ(){return VertexShiftValues::Shift_Z;};
void PrintWgtsBeingUSED(){
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~Wgts Being applied ~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"UpStream Cap: "<< Al_wgts::upstream<< std::endl;
std::cout<<"Barrel : "<<Al_wgts::barrel << std::endl;
std::cout<<"DownStream Cap: "<< Al_wgts::downstream<< std::endl;
std::cout<<"Concave: "<< Al_wgts::concave<< std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;




}


void Fill_Convolution(ME_helium_Playlists playlist_name ,double &X_mean, double
  &X_sigma, double &Y_mean, double &Y_sigma, double &Z_mean, double &Z_sigma){

bool IsHelumFilled = ISTrueIFPlayListHeliumFUll(playlist_name);

if (IsHelumFilled == true){
X_mean = Convolution_Vertex_shift_Values::Full_vertex_X_mean;
X_sigma = Convolution_Vertex_shift_Values::Full_vertex_X_sigma;
Y_mean = Convolution_Vertex_shift_Values::Full_vertex_Y_mean;
Y_sigma = Convolution_Vertex_shift_Values::Full_vertex_Y_sigma;
Z_mean = Convolution_Vertex_shift_Values::Full_vertex_Z_mean;
Z_sigma = Convolution_Vertex_shift_Values::Full_vertex_Z_sigma;

}
else if (IsHelumFilled == false){
  X_mean = Convolution_Vertex_shift_Values::Empty_vertex_X_mean;
  X_sigma = Convolution_Vertex_shift_Values::Empty_vertex_X_sigma;
  Y_mean = Convolution_Vertex_shift_Values::Empty_vertex_Y_mean;
  Y_sigma = Convolution_Vertex_shift_Values::Empty_vertex_Y_sigma;
  Z_mean = Convolution_Vertex_shift_Values::Empty_vertex_Z_mean;
  Z_sigma = Convolution_Vertex_shift_Values::Empty_vertex_Z_sigma;

}

else{std::cout<<"Somethins is wrong with Fill_Convolution "<< std::endl; assert(false);}




}

void Fill_Convolution_BeforeShift(ME_helium_Playlists playlist_name ,double &X_mean, double
  &X_sigma, double &Y_mean, double &Y_sigma, double &Z_mean, double &Z_sigma){

bool IsHelumFilled = ISTrueIFPlayListHeliumFUll(playlist_name);

if (IsHelumFilled == true){
X_mean = Convolution_Vertex_shift_Values::Full_vertex_X_beforeShift_mean;
X_sigma = Convolution_Vertex_shift_Values::Full_vertex_X_beforeShift_sigma;
Y_mean = Convolution_Vertex_shift_Values::Full_vertex_Y_beforeShift_mean;
Y_sigma = Convolution_Vertex_shift_Values::Full_vertex_Y_beforeShift_sigma;
Z_mean = Convolution_Vertex_shift_Values::Full_vertex_Z_beforeShift_mean;
Z_sigma = Convolution_Vertex_shift_Values::Full_vertex_Z_beforeShift_sigma;

}
else if (IsHelumFilled == false){
  X_mean = Convolution_Vertex_shift_Values::Empty_vertex_X_beforeShift_mean;
  X_sigma = Convolution_Vertex_shift_Values::Empty_vertex_X_beforeShift_sigma;
  Y_mean = Convolution_Vertex_shift_Values::Empty_vertex_Y_beforeShift_mean;
  Y_sigma = Convolution_Vertex_shift_Values::Empty_vertex_Y_beforeShift_sigma;
  Z_mean = Convolution_Vertex_shift_Values::Empty_vertex_Z_beforeShift_mean;
  Z_sigma = Convolution_Vertex_shift_Values::Empty_vertex_Z_beforeShift_sigma;

}

else{std::cout<<"Somethins is wrong with Fill_Convolution "<< std::endl; assert(false);}




}


Convolution_Parameters_MAP CreateConvolutionParameterMap(){
Convolution_Parameters_MAP OutPutMap;

///////////////////////////////////////////////////////////////////////////////
Convolution_Parameters Z_totalRegion;

Z_totalRegion.Vertex_type = kZ;
Z_totalRegion.stddev_toRECO =  Convolution_shift_Values::vertex_Z_totalRegion_RECO_stddev;
Z_totalRegion.mean_toRECO   =  Convolution_shift_Values::vertex_Z_totalRegion_RECO_mean;
Z_totalRegion.stddev_toDATA  = Convolution_shift_Values::vertex_Z_totalRegion_DATA_stddev;
Z_totalRegion.mean_toDATA    = Convolution_shift_Values::vertex_Z_totalRegion_DATA_mean;
Z_totalRegion.stddev_toDATA2 = Convolution_shift_Values::vertex_Z_totalRegion_DATA_2_stddev;
Z_totalRegion.mean_toDATA2   = Convolution_shift_Values::vertex_Z_totalRegion_DATA_2_mean;
//OutPutMap[kvertex_Z_totalRegion] = Z_totalRegion;
OutPutMap.insert( std::pair<Convolution_shift, Convolution_Parameters>(kvertex_Z_totalRegion, Z_totalRegion) );
///////////////////////////////////////////////////////////////////////////////
Convolution_Parameters Z_totalRegion_RCut;
Z_totalRegion_RCut.Vertex_type = kZ;
Z_totalRegion_RCut.stddev_toRECO =  Convolution_shift_Values::vertex_Z_RCut_totalRegion_RECO_stddev;
Z_totalRegion_RCut.mean_toRECO   =  Convolution_shift_Values::vertex_Z_RCut_totalRegion_RECO_mean;
Z_totalRegion_RCut.stddev_toDATA  = Convolution_shift_Values::vertex_Z_RCut_totalRegion_DATA_stddev;
Z_totalRegion_RCut.mean_toDATA    = Convolution_shift_Values::vertex_Z_RCut_totalRegion_DATA_mean;
Z_totalRegion_RCut.stddev_toDATA2 = Convolution_shift_Values::vertex_Z_RCut_totalRegion_DATA_2_stddev;
Z_totalRegion_RCut.mean_toDATA2   = Convolution_shift_Values::vertex_Z_RCut_totalRegion_DATA_2_mean;
//OutPutMap[kvertex_Z_RCut_totalRegion] = Z_totalRegion_RCut;
OutPutMap.insert( std::pair<Convolution_shift, Convolution_Parameters>(kvertex_Z_RCut_totalRegion, Z_totalRegion_RCut) );
///////////////////////////////////////////////////////////////////////////////
Convolution_Parameters R_totalRegion;

R_totalRegion.Vertex_type = kR;
R_totalRegion.stddev_toRECO =  Convolution_shift_Values::vertex_R_totalRegion_RECO_stddev;
R_totalRegion.mean_toRECO   =  Convolution_shift_Values::vertex_R_totalRegion_RECO_mean;
R_totalRegion.stddev_toDATA  = Convolution_shift_Values::vertex_R_totalRegion_DATA_stddev;
R_totalRegion.mean_toDATA    = Convolution_shift_Values::vertex_R_totalRegion_DATA_mean;
R_totalRegion.stddev_toDATA2 = Convolution_shift_Values::vertex_R_totalRegion_DATA_2_stddev;
R_totalRegion.mean_toDATA2   = Convolution_shift_Values::vertex_R_totalRegion_DATA_2_mean;
//OutPutMap[kvertex_R_totalRegion] = R_totalRegion;
OutPutMap.insert( std::pair<Convolution_shift, Convolution_Parameters>(kvertex_R_totalRegion, R_totalRegion) );
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////

Convolution_Parameters RR_totalRegion;

RR_totalRegion.Vertex_type = kRR;
RR_totalRegion.stddev_toRECO =  Convolution_shift_Values::vertex_RR_totalRegion_RECO_stddev;
RR_totalRegion.mean_toRECO   =  Convolution_shift_Values::vertex_RR_totalRegion_RECO_mean;
RR_totalRegion.stddev_toDATA  = Convolution_shift_Values::vertex_RR_totalRegion_DATA_stddev;
RR_totalRegion.mean_toDATA    = Convolution_shift_Values::vertex_RR_totalRegion_DATA_mean;
RR_totalRegion.stddev_toDATA2 = Convolution_shift_Values::vertex_RR_totalRegion_DATA_2_stddev;
RR_totalRegion.mean_toDATA2   = Convolution_shift_Values::vertex_RR_totalRegion_DATA_2_mean;
//OutPutMap[kvertex_RR_totalRegion] = RR_totalRegion;
OutPutMap.insert( std::pair<Convolution_shift, Convolution_Parameters>(kvertex_RR_totalRegion, RR_totalRegion) );

///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////

Convolution_Parameters distancetowall_totalRegion;

distancetowall_totalRegion.Vertex_type = kdistance_edge;
distancetowall_totalRegion.stddev_toRECO =  Convolution_shift_Values::distancetowall_totalRegion_RECO_stddev;
distancetowall_totalRegion.mean_toRECO   =  Convolution_shift_Values::distancetowall_totalRegion_RECO_mean;
distancetowall_totalRegion.stddev_toDATA  = Convolution_shift_Values::distancetowall_totalRegion_DATA_stddev;
distancetowall_totalRegion.mean_toDATA    = Convolution_shift_Values::distancetowall_totalRegion_DATA_mean;
distancetowall_totalRegion.stddev_toDATA2 = Convolution_shift_Values::distancetowall_totalRegion_DATA_2_stddev;
distancetowall_totalRegion.mean_toDATA2   = Convolution_shift_Values::distancetowall_totalRegion_DATA_2_mean;
//OutPutMap[kdistancetowall_totalRegion] = distancetowall_totalRegion;
OutPutMap.insert( std::pair<Convolution_shift, Convolution_Parameters>(kdistancetowall_totalRegion, distancetowall_totalRegion) );
///////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//Upstream
///////////////////////////////////////////////////////////////////////////////
Convolution_Parameters Z_upstream;

Z_upstream.Vertex_type = kZ;
Z_upstream.stddev_toRECO =  Convolution_shift_Values::vertex_Z_upstream_RECO_stddev;
Z_upstream.mean_toRECO   =  Convolution_shift_Values::vertex_Z_upstream_RECO_mean;
Z_upstream.stddev_toDATA  = Convolution_shift_Values::vertex_Z_upstream_DATA_stddev;
Z_upstream.mean_toDATA    = Convolution_shift_Values::vertex_Z_upstream_DATA_mean;
Z_upstream.stddev_toDATA2 = Convolution_shift_Values::vertex_Z_upstream_DATA_2_stddev;
Z_upstream.mean_toDATA2   = Convolution_shift_Values::vertex_Z_upstream_DATA_2_mean;
//OutPutMap[kvertex_Z_upstream] = Z_upstream;
OutPutMap.insert( std::pair<Convolution_shift, Convolution_Parameters>(kvertex_Z_upstream, Z_upstream) );
///////////////////////////////////////////////////////////////////////////////
Convolution_Parameters Z_RCut_upstream;

Z_RCut_upstream.Vertex_type = kZ;
Z_RCut_upstream.stddev_toRECO =  Convolution_shift_Values::vertex_Z_RCut_upstream_RECO_stddev;
Z_RCut_upstream.mean_toRECO   =  Convolution_shift_Values::vertex_Z_RCut_upstream_RECO_mean;
Z_RCut_upstream.stddev_toDATA  = Convolution_shift_Values::vertex_Z_RCut_upstream_DATA_stddev;
Z_RCut_upstream.mean_toDATA    = Convolution_shift_Values::vertex_Z_RCut_upstream_DATA_mean;
Z_RCut_upstream.stddev_toDATA2 = Convolution_shift_Values::vertex_Z_RCut_upstream_DATA_2_stddev;
Z_RCut_upstream.mean_toDATA2   = Convolution_shift_Values::vertex_Z_RCut_upstream_DATA_2_mean;
//OutPutMap[kvertex_Z_RCut_upstream] = Z_RCut_upstream;
OutPutMap.insert( std::pair<Convolution_shift, Convolution_Parameters>(kvertex_Z_RCut_upstream,  Z_RCut_upstream) );

///////////////////////////////////////////////////////////////////////////////
Convolution_Parameters R_upstream;

R_upstream.Vertex_type = kR;
R_upstream.stddev_toRECO =  Convolution_shift_Values::vertex_R_upstream_RECO_stddev;
R_upstream.mean_toRECO   =  Convolution_shift_Values::vertex_R_upstream_RECO_mean;
R_upstream.stddev_toDATA  = Convolution_shift_Values::vertex_R_upstream_DATA_stddev;
R_upstream.mean_toDATA    = Convolution_shift_Values::vertex_R_upstream_DATA_mean;
R_upstream.stddev_toDATA2 = Convolution_shift_Values::vertex_R_upstream_DATA_2_stddev;
R_upstream.mean_toDATA2   = Convolution_shift_Values::vertex_R_upstream_DATA_2_mean;
//OutPutMap[kvertex_R_upstream] = R_upstream;
OutPutMap.insert( std::pair<Convolution_shift, Convolution_Parameters>(kvertex_R_upstream,  R_upstream) );
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////

Convolution_Parameters RR_upstream;

RR_upstream.Vertex_type = kRR;
RR_upstream.stddev_toRECO =  Convolution_shift_Values::vertex_RR_upstream_RECO_stddev;
RR_upstream.mean_toRECO   =  Convolution_shift_Values::vertex_RR_upstream_RECO_mean;
RR_upstream.stddev_toDATA  = Convolution_shift_Values::vertex_RR_upstream_DATA_stddev;
RR_upstream.mean_toDATA    = Convolution_shift_Values::vertex_RR_upstream_DATA_mean;
RR_upstream.stddev_toDATA2 = Convolution_shift_Values::vertex_RR_upstream_DATA_2_stddev;
RR_upstream.mean_toDATA2   = Convolution_shift_Values::vertex_RR_upstream_DATA_2_mean;
//OutPutMap[kvertex_RR_upstream] = RR_upstream;
OutPutMap.insert( std::pair<Convolution_shift, Convolution_Parameters>(kvertex_RR_upstream,  RR_upstream) );

///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////

Convolution_Parameters distancetowall_upstream;

distancetowall_upstream.Vertex_type = kdistance_edge;
distancetowall_upstream.stddev_toRECO =  Convolution_shift_Values::distancetowall_upstream_RECO_stddev;
distancetowall_upstream.mean_toRECO   =  Convolution_shift_Values::distancetowall_upstream_RECO_mean;
distancetowall_upstream.stddev_toDATA  = Convolution_shift_Values::distancetowall_upstream_DATA_stddev;
distancetowall_upstream.mean_toDATA    = Convolution_shift_Values::distancetowall_upstream_DATA_mean;
distancetowall_upstream.stddev_toDATA2 = Convolution_shift_Values::distancetowall_upstream_DATA_2_stddev;
distancetowall_upstream.mean_toDATA2   = Convolution_shift_Values::distancetowall_upstream_DATA_2_mean;
//OutPutMap[kdistancetowall_upstream] = distancetowall_upstream;
OutPutMap.insert( std::pair<Convolution_shift, Convolution_Parameters>(kdistancetowall_upstream,  distancetowall_upstream) );
///////////////////////////////////////////////////////////////////////////////
// Barrel
////////////////////////////////////////////////////////////////////////////////

Convolution_Parameters Z_barrel;

Z_barrel.Vertex_type = kZ;
Z_barrel.stddev_toRECO =  Convolution_shift_Values::vertex_Z_barrel_RECO_stddev;
Z_barrel.mean_toRECO   =  Convolution_shift_Values::vertex_Z_barrel_RECO_mean;
Z_barrel.stddev_toDATA  = Convolution_shift_Values::vertex_Z_barrel_DATA_stddev;
Z_barrel.mean_toDATA    = Convolution_shift_Values::vertex_Z_barrel_DATA_mean;
Z_barrel.stddev_toDATA2 = Convolution_shift_Values::vertex_Z_barrel_DATA_2_stddev;
Z_barrel.mean_toDATA2   = Convolution_shift_Values::vertex_Z_barrel_DATA_2_mean;
//OutPutMap[kvertex_Z_barrel] = Z_barrel;
OutPutMap.insert( std::pair<Convolution_shift, Convolution_Parameters>(kvertex_Z_barrel,  Z_barrel) );
////////////////////////////////////////////////////////////////////////////////

Convolution_Parameters Z_RCut_barrel;

Z_RCut_barrel.Vertex_type = kZ;
Z_RCut_barrel.stddev_toRECO =  Convolution_shift_Values::vertex_Z_RCut_barrel_RECO_stddev;
Z_RCut_barrel.mean_toRECO   =  Convolution_shift_Values::vertex_Z_RCut_barrel_RECO_mean;
Z_RCut_barrel.stddev_toDATA  = Convolution_shift_Values::vertex_Z_RCut_barrel_DATA_stddev;
Z_RCut_barrel.mean_toDATA    = Convolution_shift_Values::vertex_Z_RCut_barrel_DATA_mean;
Z_RCut_barrel.stddev_toDATA2 = Convolution_shift_Values::vertex_Z_RCut_barrel_DATA_2_stddev;
Z_RCut_barrel.mean_toDATA2   = Convolution_shift_Values::vertex_Z_RCut_barrel_DATA_2_mean;
//OutPutMap[kvertex_Z_RCut_barrel] = Z_RCut_barrel;
OutPutMap.insert( std::pair<Convolution_shift, Convolution_Parameters>(kvertex_Z_RCut_barrel,  Z_RCut_barrel) );


///////////////////////////////////////////////////////////////////////////////

Convolution_Parameters R_barrel;

R_barrel.Vertex_type = kR;
R_barrel.stddev_toRECO =  Convolution_shift_Values::vertex_R_barrel_RECO_stddev;
R_barrel.mean_toRECO   =  Convolution_shift_Values::vertex_R_barrel_RECO_mean;
R_barrel.stddev_toDATA  = Convolution_shift_Values::vertex_R_barrel_DATA_stddev;
R_barrel.mean_toDATA    = Convolution_shift_Values::vertex_R_barrel_DATA_mean;
R_barrel.stddev_toDATA2 = Convolution_shift_Values::vertex_R_barrel_DATA_2_stddev;
R_barrel.mean_toDATA2   = Convolution_shift_Values::vertex_R_barrel_DATA_2_mean;
//OutPutMap[kvertex_R_barrel] = R_barrel;
OutPutMap.insert( std::pair<Convolution_shift, Convolution_Parameters>(kvertex_R_barrel,  R_barrel) );

///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////

Convolution_Parameters RR_barrel;

RR_barrel.Vertex_type = kRR;
RR_barrel.stddev_toRECO =  Convolution_shift_Values::vertex_RR_barrel_RECO_stddev;
RR_barrel.mean_toRECO   =  Convolution_shift_Values::vertex_RR_barrel_RECO_mean;
RR_barrel.stddev_toDATA  = Convolution_shift_Values::vertex_RR_barrel_DATA_stddev;
RR_barrel.mean_toDATA    = Convolution_shift_Values::vertex_RR_barrel_DATA_mean;
RR_barrel.stddev_toDATA2 = Convolution_shift_Values::vertex_RR_barrel_DATA_2_stddev;
RR_barrel.mean_toDATA2   = Convolution_shift_Values::vertex_RR_barrel_DATA_2_mean;
//OutPutMap[kvertex_RR_barrel] = RR_barrel;
OutPutMap.insert( std::pair<Convolution_shift, Convolution_Parameters>(kvertex_RR_barrel,  RR_barrel) );

///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////

Convolution_Parameters distancetowall_barrel;

distancetowall_barrel.Vertex_type = kdistance_edge;
distancetowall_barrel.stddev_toRECO =  Convolution_shift_Values::distancetowall_barrel_RECO_stddev;
distancetowall_barrel.mean_toRECO   =  Convolution_shift_Values::distancetowall_barrel_RECO_mean;
distancetowall_barrel.stddev_toDATA  = Convolution_shift_Values::distancetowall_barrel_DATA_stddev;
distancetowall_barrel.mean_toDATA    = Convolution_shift_Values::distancetowall_barrel_DATA_mean;
distancetowall_barrel.stddev_toDATA2 = Convolution_shift_Values::distancetowall_barrel_DATA_2_stddev;
distancetowall_barrel.mean_toDATA2   = Convolution_shift_Values::distancetowall_barrel_DATA_2_mean;
//OutPutMap[kdistancetowall_barrel] = distancetowall_barrel;

OutPutMap.insert( std::pair<Convolution_shift, Convolution_Parameters>(kdistancetowall_barrel,  distancetowall_barrel) );

///////////////////////////////////////////
// downstream Cap
//////////////////////////////////////////

Convolution_Parameters Z_downstream;

Z_downstream.Vertex_type = kZ;
Z_downstream.stddev_toRECO =  Convolution_shift_Values::vertex_Z_downstream_RECO_stddev;
Z_downstream.mean_toRECO   =  Convolution_shift_Values::vertex_Z_downstream_RECO_mean;
Z_downstream.stddev_toDATA  = Convolution_shift_Values::vertex_Z_downstream_DATA_stddev;
Z_downstream.mean_toDATA    = Convolution_shift_Values::vertex_Z_downstream_DATA_mean;
Z_downstream.stddev_toDATA2 = Convolution_shift_Values::vertex_Z_downstream_DATA_2_stddev;
Z_downstream.mean_toDATA2   = Convolution_shift_Values::vertex_Z_downstream_DATA_2_mean;
//OutPutMap[kvertex_Z_downstream] = Z_downstream;
OutPutMap.insert( std::pair<Convolution_shift, Convolution_Parameters>(kvertex_Z_downstream,  Z_downstream) );

///////////////////////////////////////////////////////////////////////////////
Convolution_Parameters Z_RCut_downstream;

Z_RCut_downstream.Vertex_type = kZ;
Z_RCut_downstream.stddev_toRECO =  Convolution_shift_Values::vertex_Z_RCut_downstream_RECO_stddev;
Z_RCut_downstream.mean_toRECO   =  Convolution_shift_Values::vertex_Z_RCut_downstream_RECO_mean;
Z_RCut_downstream.stddev_toDATA  = Convolution_shift_Values::vertex_Z_RCut_downstream_DATA_stddev;
Z_RCut_downstream.mean_toDATA    = Convolution_shift_Values::vertex_Z_RCut_downstream_DATA_mean;
Z_RCut_downstream.stddev_toDATA2 = Convolution_shift_Values::vertex_Z_RCut_downstream_DATA_2_stddev;
Z_RCut_downstream.mean_toDATA2   = Convolution_shift_Values::vertex_Z_RCut_downstream_DATA_2_mean;
//OutPutMap[kvertex_Z_RCut_downstream] = Z_RCut_downstream;
OutPutMap.insert( std::pair<Convolution_shift, Convolution_Parameters>(kvertex_Z_RCut_downstream,  Z_RCut_downstream) );

///////////////////////////////////////////////////////////////////////////////
Convolution_Parameters R_downstream;

R_downstream.Vertex_type = kR;
R_downstream.stddev_toRECO =  Convolution_shift_Values::vertex_R_downstream_RECO_stddev;
R_downstream.mean_toRECO   =  Convolution_shift_Values::vertex_R_downstream_RECO_mean;
R_downstream.stddev_toDATA  = Convolution_shift_Values::vertex_R_downstream_DATA_stddev;
R_downstream.mean_toDATA    = Convolution_shift_Values::vertex_R_downstream_DATA_mean;
R_downstream.stddev_toDATA2 = Convolution_shift_Values::vertex_R_downstream_DATA_2_stddev;
R_downstream.mean_toDATA2   = Convolution_shift_Values::vertex_R_downstream_DATA_2_mean;
//OutPutMap[kvertex_R_downstream] = R_downstream;
OutPutMap.insert( std::pair<Convolution_shift, Convolution_Parameters>(kvertex_R_downstream,  R_downstream) );

///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////

Convolution_Parameters RR_downstream;

RR_downstream.Vertex_type = kRR;
RR_downstream.stddev_toRECO =  Convolution_shift_Values::vertex_RR_downstream_RECO_stddev;
RR_downstream.mean_toRECO   =  Convolution_shift_Values::vertex_RR_downstream_RECO_mean;
RR_downstream.stddev_toDATA  = Convolution_shift_Values::vertex_RR_downstream_DATA_stddev;
RR_downstream.mean_toDATA    = Convolution_shift_Values::vertex_RR_downstream_DATA_mean;
RR_downstream.stddev_toDATA2 = Convolution_shift_Values::vertex_RR_downstream_DATA_2_stddev;
RR_downstream.mean_toDATA2   = Convolution_shift_Values::vertex_RR_downstream_DATA_2_mean;
//OutPutMap[kvertex_RR_downstream] = RR_downstream;
OutPutMap.insert( std::pair<Convolution_shift, Convolution_Parameters>(kvertex_RR_downstream,  RR_downstream) );

///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////

Convolution_Parameters distancetowall_downstream;

distancetowall_downstream.Vertex_type = kdistance_edge;
distancetowall_downstream.stddev_toRECO =  Convolution_shift_Values::distancetowall_downstream_RECO_stddev;
distancetowall_downstream.mean_toRECO   =  Convolution_shift_Values::distancetowall_downstream_RECO_mean;
distancetowall_downstream.stddev_toDATA  = Convolution_shift_Values::distancetowall_downstream_DATA_stddev;
distancetowall_downstream.mean_toDATA    = Convolution_shift_Values::distancetowall_downstream_DATA_mean;
distancetowall_downstream.stddev_toDATA2 = Convolution_shift_Values::distancetowall_downstream_DATA_2_stddev;
distancetowall_downstream.mean_toDATA2   = Convolution_shift_Values::distancetowall_downstream_DATA_2_mean;
//OutPutMap[kdistancetowall_downstream] = distancetowall_downstream;
OutPutMap.insert( std::pair<Convolution_shift, Convolution_Parameters>(kdistancetowall_downstream,  distancetowall_downstream) );

////////////////////////////
/// downstream Concave
///////////////////////////


Convolution_Parameters Z_downstreamConcave;

Z_downstreamConcave.Vertex_type = kZ;
Z_downstreamConcave.stddev_toRECO =  Convolution_shift_Values::vertex_Z_downstreamConcave_RECO_stddev;
Z_downstreamConcave.mean_toRECO   =  Convolution_shift_Values::vertex_Z_downstreamConcave_RECO_mean;
Z_downstreamConcave.stddev_toDATA  = Convolution_shift_Values::vertex_Z_downstreamConcave_DATA_stddev;
Z_downstreamConcave.mean_toDATA    = Convolution_shift_Values::vertex_Z_downstreamConcave_DATA_mean;
Z_downstreamConcave.stddev_toDATA2 = Convolution_shift_Values::vertex_Z_downstreamConcave_DATA_2_stddev;
Z_downstreamConcave.mean_toDATA2   = Convolution_shift_Values::vertex_Z_downstreamConcave_DATA_2_mean;
//OutPutMap[kvertex_Z_downstreamConcave] = Z_downstreamConcave;
OutPutMap.insert( std::pair<Convolution_shift, Convolution_Parameters>(kvertex_Z_downstreamConcave,  Z_downstreamConcave) );

///////////////////////////////////////////////////////////////////////////////
Convolution_Parameters Z_RCut_downstreamConcave;

Z_RCut_downstreamConcave.Vertex_type = kZ;
Z_RCut_downstreamConcave.stddev_toRECO =  Convolution_shift_Values::vertex_Z_RCut_downstreamConcave_RECO_stddev;
Z_RCut_downstreamConcave.mean_toRECO   =  Convolution_shift_Values::vertex_Z_RCut_downstreamConcave_RECO_mean;
Z_RCut_downstreamConcave.stddev_toDATA  = Convolution_shift_Values::vertex_Z_RCut_downstreamConcave_DATA_stddev;
Z_RCut_downstreamConcave.mean_toDATA    = Convolution_shift_Values::vertex_Z_RCut_downstreamConcave_DATA_mean;
Z_RCut_downstreamConcave.stddev_toDATA2 = Convolution_shift_Values::vertex_Z_RCut_downstreamConcave_DATA_2_stddev;
Z_RCut_downstreamConcave.mean_toDATA2   = Convolution_shift_Values::vertex_Z_RCut_downstreamConcave_DATA_2_mean;
//OutPutMap[kvertex_Z_RCut_downstreamConcave] = Z_RCut_downstreamConcave;
OutPutMap.insert( std::pair<Convolution_shift, Convolution_Parameters>(kvertex_Z_RCut_downstreamConcave,  Z_RCut_downstreamConcave) );

///////////////////////////////////////////////////////////////////////////////
Convolution_Parameters R_downstreamConcave;

R_downstreamConcave.Vertex_type = kR;
R_downstreamConcave.stddev_toRECO =  Convolution_shift_Values::vertex_R_downstreamConcave_RECO_stddev;
R_downstreamConcave.mean_toRECO   =  Convolution_shift_Values::vertex_R_downstreamConcave_RECO_mean;
R_downstreamConcave.stddev_toDATA  = Convolution_shift_Values::vertex_R_downstreamConcave_DATA_stddev;
R_downstreamConcave.mean_toDATA    = Convolution_shift_Values::vertex_R_downstreamConcave_DATA_mean;
R_downstreamConcave.stddev_toDATA2 = Convolution_shift_Values::vertex_R_downstreamConcave_DATA_2_stddev;
R_downstreamConcave.mean_toDATA2   = Convolution_shift_Values::vertex_R_downstreamConcave_DATA_2_mean;
//OutPutMap[kvertex_R_downstreamConcave] = R_downstreamConcave;
OutPutMap.insert( std::pair<Convolution_shift, Convolution_Parameters>(kvertex_R_downstreamConcave,  R_downstreamConcave) );

///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////

Convolution_Parameters RR_downstreamConcave;

RR_downstreamConcave.Vertex_type = kRR;
RR_downstreamConcave.stddev_toRECO =  Convolution_shift_Values::vertex_RR_downstreamConcave_RECO_stddev;
RR_downstreamConcave.mean_toRECO   =  Convolution_shift_Values::vertex_RR_downstreamConcave_RECO_mean;
RR_downstreamConcave.stddev_toDATA  = Convolution_shift_Values::vertex_RR_downstreamConcave_DATA_stddev;
RR_downstreamConcave.mean_toDATA    = Convolution_shift_Values::vertex_RR_downstreamConcave_DATA_mean;
RR_downstreamConcave.stddev_toDATA2 = Convolution_shift_Values::vertex_RR_downstreamConcave_DATA_2_stddev;
RR_downstreamConcave.mean_toDATA2   = Convolution_shift_Values::vertex_RR_downstreamConcave_DATA_2_mean;
//OutPutMap[kvertex_RR_downstreamConcave] = RR_downstreamConcave;
OutPutMap.insert( std::pair<Convolution_shift, Convolution_Parameters>(kvertex_RR_downstreamConcave,  RR_downstreamConcave) );

///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////

Convolution_Parameters distancetowall_downstreamConcave;

distancetowall_downstreamConcave.Vertex_type = kdistance_edge;
distancetowall_downstreamConcave.stddev_toRECO =  Convolution_shift_Values::distancetowall_downstreamConcave_RECO_stddev;
distancetowall_downstreamConcave.mean_toRECO   =  Convolution_shift_Values::distancetowall_downstreamConcave_RECO_mean;
distancetowall_downstreamConcave.stddev_toDATA  = Convolution_shift_Values::distancetowall_downstreamConcave_DATA_stddev;
distancetowall_downstreamConcave.mean_toDATA    = Convolution_shift_Values::distancetowall_downstreamConcave_DATA_mean;
distancetowall_downstreamConcave.stddev_toDATA2 = Convolution_shift_Values::distancetowall_downstreamConcave_DATA_2_stddev;
distancetowall_downstreamConcave.mean_toDATA2   = Convolution_shift_Values::distancetowall_downstreamConcave_DATA_2_mean;
//OutPutMap[kdistancetowall_downstreamConcave] = distancetowall_downstreamConcave;
OutPutMap.insert( std::pair<Convolution_shift, Convolution_Parameters>(kdistancetowall_downstreamConcave,  distancetowall_downstreamConcave) );

/////////////////////////
Convolution_Parameters distance_UpstreamCap;
distance_UpstreamCap.Vertex_type = kDistanceto_UpstreamCap;
distance_UpstreamCap.stddev_toRECO =  Convolution_shift_Values::Distance_to_upstreamCap_RECO_stddev;
distance_UpstreamCap.mean_toRECO   =  Convolution_shift_Values::Distance_to_upstreamCap_RECO_mean;
distance_UpstreamCap.stddev_toDATA  = Convolution_shift_Values::Distance_to_upstreamCap_DATA_stddev;
distance_UpstreamCap.mean_toDATA    = Convolution_shift_Values::Distance_to_upstreamCap_DATA_mean;
distance_UpstreamCap.stddev_toDATA2 = Convolution_shift_Values::Distance_to_upstreamCap_DATA_2_stddev;
distance_UpstreamCap.mean_toDATA2   = Convolution_shift_Values::Distance_to_upstreamCap_DATA_2_mean;
//OutPutMap[kDistancetoCap_upstream] = distance_UpstreamCap;
OutPutMap.insert( std::pair<Convolution_shift, Convolution_Parameters>(kDistancetoCap_upstream,  distance_UpstreamCap) );

//////////////////////////////////

Convolution_Parameters distance_DownstreamstreamCap;
distance_DownstreamstreamCap.Vertex_type = kDistanceto_DownstreamCap;
distance_DownstreamstreamCap.stddev_toRECO =  Convolution_shift_Values::Distance_to_downstreamCap_RECO_stddev;
distance_DownstreamstreamCap.mean_toRECO   =  Convolution_shift_Values::Distance_to_downstreamCap_RECO_mean;
distance_DownstreamstreamCap.stddev_toDATA  = Convolution_shift_Values::Distance_to_downstreamCap_DATA_stddev;
distance_DownstreamstreamCap.mean_toDATA    = Convolution_shift_Values::Distance_to_downstreamCap_DATA_mean;
distance_DownstreamstreamCap.stddev_toDATA2 = Convolution_shift_Values::Distance_to_downstreamCap_DATA_2_stddev;
distance_DownstreamstreamCap.mean_toDATA2   = Convolution_shift_Values::Distance_to_downstreamCap_DATA_2_mean;
//OutPutMap[kDistancetoCap_upstream] = distance_DownstreamstreamCap;
OutPutMap.insert( std::pair<Convolution_shift, Convolution_Parameters>(kDistancetoCap_downstream,  distance_DownstreamstreamCap) );




  return OutPutMap;
}


Best4IndexFit init_defaultBest4IndexFit(){

  Best4IndexFit output;


  Index4 best_Chisqrt_X{9999,9999,9999,9999};
  Index4 best_Chisqrt_Y{9999,9999,9999,9999};
  Index4 best_Chisqrt_Z{9999,9999,9999,9999};
  Index4 best_Chisqrt_R{9999,9999,9999,9999};

  Normal_Fit_Parameters FitXpars = init_default_Normal_Fit_Parameters();
  Normal_Fit_Parameters FitYpars = init_default_Normal_Fit_Parameters();
  Normal_Fit_Parameters FitZpars = init_default_Normal_Fit_Parameters();
  Normal_Fit_Parameters FitRpars = init_default_Normal_Fit_Parameters();

  output.best_Chisqrt_X = best_Chisqrt_X;
  output.best_Chisqrt_Y = best_Chisqrt_Y;
  output.best_Chisqrt_Z = best_Chisqrt_Z;
  output.best_Chisqrt_R = best_Chisqrt_R;

  output.FitXpars = FitXpars;
  output.FitYpars = FitYpars;
  output.FitZpars = FitZpars;
  output.FitRpars = FitRpars;

  return output;

}




   //////////////////////////////////////////////////////
   // Convolution_Tool
   /////////////////////////////////////////////////////
Convolution_Tool::Convolution_Tool(){
  std::cout<<"initialized Convolution_Tool but did nothing !!! "<<std::endl;
}

Convolution_Tool::~Convolution_Tool()
{
}

void Convolution_Tool::Intialize_dataHistNames(){
  assign_CryoVertex_type();
  assign_TotalRegionHist_dataName();
  assign_RegionsHist_dataName();
}


void Convolution_Tool::assign_CryoVertex_dataHistName(std::string name , Convolution_hist &input_hist){
  input_hist.Data_name = name;
}


void Convolution_Tool::printDATAhistname(Convolution_hist input_hist){
  std::cout<< input_hist.Data_name <<std::endl;
}

void Convolution_Tool::print_Total_DATAhistname(ConvolutionShiftMap input_Map){
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~Total Data Names " << std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << std::endl;
  std::cout << "Vertex_X_TotalRegion                    = ";  printDATAhistname(input_Map.Vertex_X_TotalRegion);
  std::cout << "Vertex_Y_TotalRegion                    = ";  printDATAhistname(input_Map.Vertex_Y_TotalRegion);
  std::cout << "Vertex_R_TotalRegion                    = ";  printDATAhistname(input_Map.Vertex_R_TotalRegion);
  //std::cout << "Vertex_RR_TotalRegion                   = ";  printDATAhistname(input_Map.Vertex_RR_TotalRegion);
  std::cout << "Vertex_Z_TotalRegion                    = ";  printDATAhistname(input_Map.Vertex_Z_TotalRegion);
  std::cout << "Vertex_Z_TotalRegion_RCut               = ";  printDATAhistname(input_Map.Vertex_Z_TotalRegion_RCut);
  std::cout << "NearestWall_TotalRegion                 = ";  printDATAhistname(input_Map.NearestWall_TotalRegion);
  std::cout << "DistanceUpstreamCap_TotalRegion         = ";  printDATAhistname(input_Map.DistanceUpstreamCap_TotalRegion);
  std::cout << "DistanceDownstreamCap_TotalRegion       = ";  printDATAhistname(input_Map.DistanceDownstreamCap_TotalRegion);
  std::cout << "DistanceUpstreamCap_TotalRegion_RCut    = ";  printDATAhistname(input_Map.DistanceUpstreamCap_TotalRegion_RCut);
  std::cout << "DistanceDownstreamCap_TotalRegion_RCut  = ";  printDATAhistname(input_Map.DistanceDownstreamCap_TotalRegion_RCut);
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << std::endl;
}

void Convolution_Tool::print_Total_RECOhistname(ConvolutionShiftMap input_Map){
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~Total RECO Names " << std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << std::endl;
  std::cout << "Vertex_X_TotalRegion                    =   ";  printRECOhistname(input_Map.Vertex_X_TotalRegion);
  std::cout << "Vertex_Y_TotalRegion                    =   ";  printRECOhistname(input_Map.Vertex_Y_TotalRegion);
  std::cout << "Vertex_R_TotalRegion                    =   ";  printRECOhistname(input_Map.Vertex_R_TotalRegion);
  //std::cout << "Vertex_RR_TotalRegion                   =   ";  printRECOhistname(input_Map.Vertex_RR_TotalRegion);
  std::cout << "Vertex_Z_TotalRegion                    =   ";  printRECOhistname(input_Map.Vertex_Z_TotalRegion);
  std::cout << "Vertex_Z_TotalRegion_RCut               =   ";  printRECOhistname(input_Map.Vertex_Z_TotalRegion_RCut);
  std::cout << "NearestWall_TotalRegion                 =   ";  printRECOhistname(input_Map.NearestWall_TotalRegion);
  std::cout << "DistanceUpstreamCap_TotalRegion         =   ";  printRECOhistname(input_Map.DistanceUpstreamCap_TotalRegion);
  std::cout << "DistanceDownstreamCap_TotalRegion       =   ";  printRECOhistname(input_Map.DistanceDownstreamCap_TotalRegion);
  std::cout << "DistanceUpstreamCap_TotalRegion_RCut    =   ";  printRECOhistname(input_Map.DistanceUpstreamCap_TotalRegion_RCut);
  std::cout << "DistanceDownstreamCap_TotalRegion_RCut  =   ";  printRECOhistname(input_Map.DistanceDownstreamCap_TotalRegion_RCut);
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << std::endl;
}

void Convolution_Tool::assign_CryoVertex_RecoHistName(std::string name , Convolution_hist &input_hist){
  input_hist.Reco_name = name;
}

void Convolution_Tool::assign_CryoVertex_Material_RecoHistName(std::string name , Convolution_hist &input_hist){
  input_hist.Reco_Material_name = name;
}

void Convolution_Tool::SetZeroshift4index(Index4 input ){

ZeroShift4index = input;

}



void Convolution_Tool::printRECOhistname(Convolution_hist input_hist){
  std::cout<< input_hist.Reco_name<<std::endl;
}

void Convolution_Tool::assign_CryoVertex_TRUEHistName(std::string name , Convolution_hist &input_hist){
  input_hist.TRUE_name = name;
}

void Convolution_Tool::printTRUEhistname(Convolution_hist input_hist){
  std::cout<< input_hist.TRUE_name<<std::endl;
}


void Convolution_Tool::print_Total_TRUEhistname(ConvolutionShiftMap input_Map){

  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~Total TRUE Names~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << std::endl;
  std::cout << "Vertex_X_TotalRegion                    = ";  printTRUEhistname(input_Map.Vertex_X_TotalRegion);
  std::cout << "Vertex_Y_TotalRegion                    = ";  printTRUEhistname(input_Map.Vertex_Y_TotalRegion);
  std::cout << "Vertex_R_TotalRegion                    = ";  printTRUEhistname(input_Map.Vertex_R_TotalRegion);
  //std::cout << "Vertex_RR_TotalRegion                   = ";  printTRUEhistname(input_Map.Vertex_RR_TotalRegion);
  std::cout << "Vertex_Z_TotalRegion                    = ";  printTRUEhistname(input_Map.Vertex_Z_TotalRegion);
  std::cout << "Vertex_Z_TotalRegion_RCut               = ";  printTRUEhistname(input_Map.Vertex_Z_TotalRegion_RCut);
  std::cout << "NearestWall_TotalRegion                 = ";  printTRUEhistname(input_Map.NearestWall_TotalRegion);
  std::cout << "DistanceUpstreamCap_TotalRegion         = ";  printTRUEhistname(input_Map.DistanceUpstreamCap_TotalRegion);
  std::cout << "DistanceDownstreamCap_TotalRegion       = ";  printTRUEhistname(input_Map.DistanceDownstreamCap_TotalRegion);
  std::cout << "DistanceUpstreamCap_TotalRegion_RCut    = ";  printTRUEhistname(input_Map.DistanceUpstreamCap_TotalRegion_RCut);
  std::cout << "DistanceDownstreamCap_TotalRegion_RCut  = ";  printTRUEhistname(input_Map.DistanceDownstreamCap_TotalRegion_RCut);
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << std::endl;
}




void Convolution_Tool::Print_initNames(ConvolutionShiftMap input_histmap){

  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~Printing Names " << std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << std::endl;
  print_Total_DATAhistname(input_histmap);
  print_Total_RECOhistname(input_histmap);
  print_Total_TRUEhistname(input_histmap);
  print_Total_ConvolutedTRUEhistname(input_histmap);
}


void Convolution_Tool::Print_initNames_Empty(){
  Print_initNames(Empty);
}

void Convolution_Tool::assign_CryoVertex_ConvolutedTRUEHistName(std::string name , Convolution_hist &input_hist){
  input_hist.TRUE_Convoluted_name = name;
}

void Convolution_Tool::printConvolutedTRUEhistname(Convolution_hist input_hist){
  std::cout<< input_hist.TRUE_Convoluted_name<<std::endl;
}

void Convolution_Tool::print_Total_ConvolutedTRUEhistname(ConvolutionShiftMap input_Map){

  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~Total TRUE Convoluted Names~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << std::endl;
  std::cout << "Vertex_X_TotalRegion                    = ";  printConvolutedTRUEhistname(input_Map.Vertex_X_TotalRegion);
  std::cout << "Vertex_Y_TotalRegion                    = ";  printConvolutedTRUEhistname(input_Map.Vertex_Y_TotalRegion);
  std::cout << "Vertex_R_TotalRegion                    = ";  printConvolutedTRUEhistname(input_Map.Vertex_R_TotalRegion);
  //std::cout << "Vertex_RR_TotalRegion                   = ";  printConvolutedTRUEhistname(input_Map.Vertex_RR_TotalRegion);
  std::cout << "Vertex_Z_TotalRegion                    = ";  printConvolutedTRUEhistname(input_Map.Vertex_Z_TotalRegion);
  std::cout << "Vertex_Z_TotalRegion_RCut               = ";  printConvolutedTRUEhistname(input_Map.Vertex_Z_TotalRegion_RCut);
  std::cout << "NearestWall_TotalRegion                 = ";  printConvolutedTRUEhistname(input_Map.NearestWall_TotalRegion);
  std::cout << "DistanceUpstreamCap_TotalRegion         = ";  printConvolutedTRUEhistname(input_Map.DistanceUpstreamCap_TotalRegion);
  std::cout << "DistanceDownstreamCap_TotalRegion       = ";  printConvolutedTRUEhistname(input_Map.DistanceDownstreamCap_TotalRegion);
  std::cout << "DistanceUpstreamCap_TotalRegion_RCut    = ";  printConvolutedTRUEhistname(input_Map.DistanceUpstreamCap_TotalRegion_RCut);
  std::cout << "DistanceDownstreamCap_TotalRegion_RCut  = ";  printConvolutedTRUEhistname(input_Map.DistanceDownstreamCap_TotalRegion_RCut);
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << std::endl;
}



void Convolution_Tool::assign_CryoVertexTotalRegion_ConvolutedTRUEHistName(ConvolutionShiftMap &input_Map){

  assign_CryoVertex_ConvolutedTRUEHistName("h_offset_Vertex_X",      input_Map.Vertex_X_TotalRegion);
  assign_CryoVertex_ConvolutedTRUEHistName("h_offset_Vertex_Y",      input_Map.Vertex_Y_TotalRegion);
  assign_CryoVertex_ConvolutedTRUEHistName("h_offset_Vertex_Z",      input_Map.Vertex_Z_TotalRegion);
  assign_CryoVertex_ConvolutedTRUEHistName("h_offset_Vertex_Z_RCut", input_Map.Vertex_Z_TotalRegion_RCut);
  assign_CryoVertex_ConvolutedTRUEHistName("h_offset_Vertex_R",      input_Map.Vertex_R_TotalRegion);
  assign_CryoVertex_ConvolutedTRUEHistName("h_offset_DistanceEdge",  input_Map.NearestWall_TotalRegion);

  assign_CryoVertex_ConvolutedTRUEHistName("h_Map_DistanceupstreamCap_RCut",   input_Map.DistanceUpstreamCap_TotalRegion_RCut);
  assign_CryoVertex_ConvolutedTRUEHistName("h_Map_DistanceupstreamCap",        input_Map.DistanceUpstreamCap_TotalRegion);
  assign_CryoVertex_ConvolutedTRUEHistName("h_Map_DistancedownstreamCap_RCut", input_Map.DistanceDownstreamCap_TotalRegion_RCut);
  assign_CryoVertex_ConvolutedTRUEHistName("h_Map_DistancedownstreamCap",      input_Map.DistanceDownstreamCap_TotalRegion);

  assign_Convolution_CryoRegions_ConvolutedTRUEName(input_Map.Vertex_X_Regions,                  "h_offset_Vertex_X");
  assign_Convolution_CryoRegions_ConvolutedTRUEName(input_Map.Vertex_Y_Regions,                  "h_offset_Vertex_Y");
  assign_Convolution_CryoRegions_ConvolutedTRUEName(input_Map.Vertex_Z_Regions,                  "h_offset_Vertex_Z");
  assign_Convolution_CryoRegions_ConvolutedTRUEName(input_Map.Vertex_Z_Regions_RCut,             "h_offset_Vertex_Z_RCut");
  assign_Convolution_CryoRegions_ConvolutedTRUEName(input_Map.Vertex_R_Regions,                  "h_offset_Vertex_R");
  assign_Convolution_CryoRegions_ConvolutedTRUEName(input_Map.NearestWall_Regions,               "h_Map_DistanceEdge");
  assign_Convolution_CryoRegions_ConvolutedTRUEName(input_Map.DistanceUpstreamCap_Regions,       "h_Map_DistanceupstreamCap");
  assign_Convolution_CryoRegions_ConvolutedTRUEName(input_Map.DistanceDownstreamCap_Regions,     "h_Map_DistancedownstreamCap");
  assign_Convolution_CryoRegions_ConvolutedTRUEName(input_Map.DistanceUpstreamCap_Regions_RCut,  "h_Map_DistanceupstreamCap_RCut");
  assign_Convolution_CryoRegions_ConvolutedTRUEName(input_Map.DistanceDownstreamCap_Regions_RCut,"h_Map_DistancedownstreamCap_RCut");
}


void Convolution_Tool::assign_CryoVertex_RecoandTRUEHistName(std::string name, std::string AddString, Convolution_hist &input_hist){
  std::string inputname;
  inputname = name + AddString;
  assign_CryoVertex_RecoHistName(inputname , input_hist);
  inputname = name + AddString + "_TRUE";
  assign_CryoVertex_TRUEHistName(inputname , input_hist);
}


void Convolution_Tool::assign_CryoVertex_RecoandTRUEHistName(CryoVertex type, std::string AddString, Convolution_hist &input_hist){
   std::string histname = GetVertexCryoVarHistName(type);
   assign_CryoVertex_RecoandTRUEHistName(histname, AddString, input_hist);
 }


 void Convolution_Tool::assign_CryoVertex_TotalRegion_RecoandTRUEHistName(ConvolutionShiftMap &input_histmap){

   assign_CryoVertex_RecoandTRUEHistName(input_histmap.Vertex_X_TotalRegion.CryoVertex_type,             "",input_histmap.Vertex_X_TotalRegion);
   assign_CryoVertex_RecoandTRUEHistName(input_histmap.Vertex_Y_TotalRegion.CryoVertex_type,             "",input_histmap.Vertex_Y_TotalRegion);
   assign_CryoVertex_RecoandTRUEHistName(input_histmap.Vertex_R_TotalRegion.CryoVertex_type,             "",input_histmap.Vertex_R_TotalRegion);
   //assign_CryoVertex_RecoandTRUEHistName(input_histmap.Vertex_RR_TotalRegion.CryoVertex_type,            "",input_histmap.Vertex_RR_TotalRegion);
   assign_CryoVertex_RecoandTRUEHistName(input_histmap.Vertex_Z_TotalRegion.CryoVertex_type,             "",input_histmap.Vertex_Z_TotalRegion);
   assign_CryoVertex_RecoandTRUEHistName(input_histmap.Vertex_Z_TotalRegion_RCut.CryoVertex_type,        "_RCut",input_histmap.Vertex_Z_TotalRegion_RCut);
   assign_CryoVertex_RecoandTRUEHistName(input_histmap.NearestWall_TotalRegion.CryoVertex_type,          "",input_histmap.NearestWall_TotalRegion);
   assign_CryoVertex_RecoandTRUEHistName(input_histmap.DistanceUpstreamCap_TotalRegion.CryoVertex_type,  "",input_histmap.DistanceUpstreamCap_TotalRegion);
   assign_CryoVertex_RecoandTRUEHistName(input_histmap.DistanceDownstreamCap_TotalRegion.CryoVertex_type,"",input_histmap.DistanceDownstreamCap_TotalRegion);
   assign_CryoVertex_RecoandTRUEHistName(input_histmap.DistanceUpstreamCap_TotalRegion.CryoVertex_type,  "_RCut",input_histmap.DistanceUpstreamCap_TotalRegion_RCut);
   assign_CryoVertex_RecoandTRUEHistName(input_histmap.DistanceDownstreamCap_TotalRegion.CryoVertex_type,"_RCut",input_histmap.DistanceDownstreamCap_TotalRegion_RCut);
 }



void Convolution_Tool::assign_Convolution_CryoRegions_HistName(Convolution_CryoRegions &input_histmap, std::string inputname){
   std::string histname;
   histname = inputname + "_upstreamCap";
   assign_CryoVertex_RecoandTRUEHistName(histname, "", input_histmap.Upstream);
   histname = inputname + "_barrel";
   assign_CryoVertex_RecoandTRUEHistName(histname, "", input_histmap.Barrel);
   histname = inputname + "_downstreamCap";
   assign_CryoVertex_RecoandTRUEHistName(histname, "", input_histmap.Downstream);
   histname = inputname + "_downstreamConcaveCap";
   assign_CryoVertex_RecoandTRUEHistName(histname, "", input_histmap.Concave);
 }

 void Convolution_Tool::assign_Convolution_CryoRegions_Hist_MaterialName(Convolution_CryoRegions &input_histmap, std::string inputname){
    std::string histname;
    histname = inputname + "_upstreamcap_Material";
    assign_CryoVertex_Material_RecoHistName(histname, input_histmap.Upstream);
    histname = inputname + "_barrel_Material";
    assign_CryoVertex_Material_RecoHistName(histname, input_histmap.Barrel);
    histname = inputname + "_downstreamcap_Material";
    assign_CryoVertex_Material_RecoHistName(histname, input_histmap.Downstream);
    histname = inputname + "_downstreamconcavecap_Material";
    assign_CryoVertex_Material_RecoHistName(histname, input_histmap.Concave);
  }

void Convolution_Tool::assign_Convolution_CryoRegions_HistName(ConvolutionShiftMap &inputMap){

  std::string histname;
  histname = GetVertexCryoVarHistName(kX);

  assign_Convolution_CryoRegions_HistName(inputMap.Vertex_X_Regions, histname);
  histname = GetVertexCryoVarHistName(kY);

  assign_Convolution_CryoRegions_HistName(inputMap.Vertex_Y_Regions, histname);
  histname = GetVertexCryoVarHistName(kZ);
  assign_Convolution_CryoRegions_HistName(inputMap.Vertex_Z_Regions, histname);

  histname = GetVertexCryoVarHistName(kZ)+ "_RCut";
  assign_Convolution_CryoRegions_HistName(inputMap.Vertex_Z_Regions_RCut, histname);

  histname = GetVertexCryoVarHistName(kR);
  assign_Convolution_CryoRegions_HistName(inputMap.Vertex_R_Regions, histname);
  //histname = GetVertexCryoVarHistName(kRR);
  //assign_Convolution_CryoRegions_HistName(inputMap.Vertex_RR_Regions,histname);
  histname = GetVertexCryoVarHistName(kdistance_edge);
  assign_Convolution_CryoRegions_HistName(inputMap.NearestWall_Regions,histname);
  histname = GetVertexCryoVarHistName(kdistance_upstreamcap);
  assign_Convolution_CryoRegions_HistName(inputMap.DistanceUpstreamCap_Regions,histname);
  histname = GetVertexCryoVarHistName(kdistance_downstreamcap);
  assign_Convolution_CryoRegions_HistName(inputMap.DistanceDownstreamCap_Regions,histname);
  histname = GetVertexCryoVarHistName(kdistance_upstreamcap) + "_RCut";
  assign_Convolution_CryoRegions_HistName(inputMap.DistanceUpstreamCap_Regions_RCut,histname);
  histname = GetVertexCryoVarHistName(kdistance_downstreamcap)+ "_RCut";
  assign_Convolution_CryoRegions_HistName(inputMap.DistanceDownstreamCap_Regions_RCut,histname);
}

void Convolution_Tool::assign_Convolution_CryoRegions_Material_XYZR_HistName(ConvolutionShiftMap &inputMap){
  std::string histname;
  histname = "h_offset_Vertex_X";
  assign_Convolution_CryoRegions_Hist_MaterialName(inputMap.Vertex_X_Regions, histname);
  histname = "h_offset_Vertex_Y";
  assign_Convolution_CryoRegions_Hist_MaterialName(inputMap.Vertex_Y_Regions, histname);
  histname = "h_offset_Vertex_Z";
  assign_Convolution_CryoRegions_Hist_MaterialName(inputMap.Vertex_Z_Regions, histname);
  histname = "h_offset_Vertex_R";
  assign_Convolution_CryoRegions_Hist_MaterialName(inputMap.Vertex_R_Regions, histname);

  histname = "h_offset_Vertex_TRUE_X";
  assign_Convolution_CryoRegions_Hist_MaterialName(inputMap.Vertex_TRUE_X_Regions, histname);
  histname = "h_offset_Vertex_TRUE_Y";
  assign_Convolution_CryoRegions_Hist_MaterialName(inputMap.Vertex_TRUE_Y_Regions, histname);
  histname = "h_offset_Vertex_TRUE_Z";
  assign_Convolution_CryoRegions_Hist_MaterialName(inputMap.Vertex_TRUE_Z_Regions, histname);
  histname = "h_offset_Vertex_TRUE_R";
  assign_Convolution_CryoRegions_Hist_MaterialName(inputMap.Vertex_TRUE_R_Regions, histname);


}

void Convolution_Tool::assign_Convolution_CryoRegions_Material_nonVertexVars_HistName(ConvolutionShiftMap &inputMap){
  std::string histname;
  histname = "h_offset_muonPT";
  assign_Convolution_CryoRegions_Hist_MaterialName(inputMap.muonPT_Regions, histname);
  histname = "h_offset_muonPz";
  assign_Convolution_CryoRegions_Hist_MaterialName(inputMap.muonPZ_Regions, histname);
  histname = "h_offset_muontheta";
  assign_Convolution_CryoRegions_Hist_MaterialName(inputMap.muontheta_Regions, histname);
  histname = "h_offset_muonE";
  assign_Convolution_CryoRegions_Hist_MaterialName(inputMap.muonE_Regions, histname);
  histname = "h_offset_muonDOCA";
  assign_Convolution_CryoRegions_Hist_MaterialName(inputMap.muonDOCA_Regions, histname);
  histname = "h_offset_nearestwall";
  assign_Convolution_CryoRegions_Hist_MaterialName(inputMap.NearestWall_Regions, histname);
  histname = "h_offset_recoilDOCA";
  assign_Convolution_CryoRegions_Hist_MaterialName(inputMap.recoilDOCA_Regions, histname);
  histname = "h_offset_recoilangle";
  assign_Convolution_CryoRegions_Hist_MaterialName(inputMap.recoilAngle_Regions, histname);
  histname = "h_offset_tracklength";
  assign_Convolution_CryoRegions_Hist_MaterialName(inputMap.tracklength_Regions, histname);

}

////


void Convolution_Tool::assign_Convolution_CryoRegions_Material_XYZR_HistName_Fiducial(ConvolutionShiftMap &inputMap){
  std::string histname;
  histname = "h_offset_Vertex_X_Fiducial";
  assign_Convolution_CryoRegions_Hist_MaterialName(inputMap.Vertex_X_Regions, histname);
  histname = "h_offset_Vertex_Y_Fiducial";
  assign_Convolution_CryoRegions_Hist_MaterialName(inputMap.Vertex_Y_Regions, histname);
  histname = "h_offset_Vertex_Z_Fiducial";
  assign_Convolution_CryoRegions_Hist_MaterialName(inputMap.Vertex_Z_Regions, histname);
  histname = "h_offset_Vertex_R_Fiducial";
  assign_Convolution_CryoRegions_Hist_MaterialName(inputMap.Vertex_R_Regions, histname);

  histname = "h_offset_Vertex_TRUE_X_Fiducial";
  assign_Convolution_CryoRegions_Hist_MaterialName(inputMap.Vertex_TRUE_X_Regions, histname);
  histname = "h_offset_Vertex_TRUE_Y_Fiducial";
  assign_Convolution_CryoRegions_Hist_MaterialName(inputMap.Vertex_TRUE_Y_Regions, histname);
  histname = "h_offset_Vertex_TRUE_Z_Fiducial";
  assign_Convolution_CryoRegions_Hist_MaterialName(inputMap.Vertex_TRUE_Z_Regions, histname);
  histname = "h_offset_Vertex_TRUE_R_Fiducial";
  assign_Convolution_CryoRegions_Hist_MaterialName(inputMap.Vertex_TRUE_R_Regions, histname);


}

void Convolution_Tool::assign_Convolution_CryoRegions_Material_nonVertexVars_HistName_Fiducial(ConvolutionShiftMap &inputMap){
  std::string histname;
  histname = "h_offset_muonPT_Fiducial";
  assign_Convolution_CryoRegions_Hist_MaterialName(inputMap.muonPT_Regions, histname);
  histname = "h_offset_muonPz_Fiducial";
  assign_Convolution_CryoRegions_Hist_MaterialName(inputMap.muonPZ_Regions, histname);
  histname = "h_offset_muontheta_Fiducial";
  assign_Convolution_CryoRegions_Hist_MaterialName(inputMap.muontheta_Regions, histname);
  histname = "h_offset_muonE_Fiducial";
  assign_Convolution_CryoRegions_Hist_MaterialName(inputMap.muonE_Regions, histname);
  histname = "h_offset_muonDOCA_Fiducial";
  assign_Convolution_CryoRegions_Hist_MaterialName(inputMap.muonDOCA_Regions, histname);
  histname = "h_offset_nearestwall_Fiducial";
  assign_Convolution_CryoRegions_Hist_MaterialName(inputMap.NearestWall_Regions, histname);
  histname = "h_offset_recoilDOCA_Fiducial";
  assign_Convolution_CryoRegions_Hist_MaterialName(inputMap.recoilDOCA_Regions, histname);
  histname = "h_offset_recoilangle_Fiducial";
  assign_Convolution_CryoRegions_Hist_MaterialName(inputMap.recoilAngle_Regions, histname);
  histname = "h_offset_tracklength_Fiducial";
  assign_Convolution_CryoRegions_Hist_MaterialName(inputMap.tracklength_Regions, histname);

}



void Convolution_Tool::assign_Material_XYZR_HistName(){
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<"Assigning Material Hist Names for X , Y , Z , and R for Full , Empty , F-E"<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;

assign_Convolution_CryoRegions_Material_XYZR_HistName(Full);
assign_Convolution_CryoRegions_Material_nonVertexVars_HistName(Full);
assign_Convolution_CryoRegions_dataHistName_nonVertexVars(Full);
assign_Convolution_CryoRegions_Material_XYZR_HistName(Empty);
assign_Convolution_CryoRegions_Material_nonVertexVars_HistName(Empty);
assign_Convolution_CryoRegions_dataHistName_nonVertexVars(Empty);
assign_Convolution_CryoRegions_Material_XYZR_HistName(Full_Empty);

assign_Convolution_CryoRegions_Material_XYZR_HistName_Fiducial(Full_Fid);
assign_Convolution_CryoRegions_Material_nonVertexVars_HistName_Fiducial(Full_Fid);
assign_Convolution_CryoRegions_dataHistName_nonVertexVars_Fiducial(Full_Fid);
assign_Convolution_CryoRegions_Material_XYZR_HistName_Fiducial(Empty_Fid);
assign_Convolution_CryoRegions_Material_nonVertexVars_HistName_Fiducial(Empty_Fid);
assign_Convolution_CryoRegions_dataHistName_nonVertexVars_Fiducial(Empty_Fid);
assign_Convolution_CryoRegions_Material_XYZR_HistName_Fiducial(Full_Empty_Fid);

}




void Convolution_Tool::assign_CryoVertex_dataHistName(CryoVertex type,
   std::string AddString,  Convolution_hist &input_hist){
  std::string histname = GetVertexCryoVarHist_DATA_Name(type) + AddString;
  //std::cout<<"assign_CryoVertex_dataHistName = "  << histname << std::endl;
  assign_CryoVertex_dataHistName(histname ,  input_hist);
}


void Convolution_Tool::assign_Convolution_CryoRegions_dataHistName(
  Convolution_CryoRegions &input_histmap, std::string inputname){
  std::string HistName;
  HistName = inputname + "_upstreamCap";
  assign_CryoVertex_dataHistName(HistName , input_histmap.Upstream);
  HistName = inputname + "_barrel";
  assign_CryoVertex_dataHistName(HistName , input_histmap.Barrel);
  HistName = inputname + "_downstreamCap";
  assign_CryoVertex_dataHistName(HistName , input_histmap.Downstream);
  HistName = inputname + "_downstreamConcaveCap";
  assign_CryoVertex_dataHistName(HistName , input_histmap.Concave);
}


void Convolution_Tool::assign_Convolution_CryoRegions_dataHistName_nonVertexVars(ConvolutionShiftMap &input_histmap){


assign_Convolution_CryoRegions_dataHistName(input_histmap.muonPT_Regions,      "h_Data_MuonPT");
assign_Convolution_CryoRegions_dataHistName(input_histmap.muonPZ_Regions,      "h_Data_MuonPZ");
assign_Convolution_CryoRegions_dataHistName(input_histmap.muonE_Regions,       "h_Data_MuonE");
assign_Convolution_CryoRegions_dataHistName(input_histmap.muontheta_Regions,   "h_Data_MuonTheta");
assign_Convolution_CryoRegions_dataHistName(input_histmap.muonDOCA_Regions,    "h_Data_MuonDOCA");
assign_Convolution_CryoRegions_dataHistName(input_histmap.NearestWall_Regions, "h_Data_Distance_to_InnerTank");
assign_Convolution_CryoRegions_dataHistName(input_histmap.recoilDOCA_Regions,  "h_Data_secTrk_DOCA");
assign_Convolution_CryoRegions_dataHistName(input_histmap.recoilAngle_Regions,  "h_Data_secTrk_angle");
assign_Convolution_CryoRegions_dataHistName(input_histmap.tracklength_Regions, "h_Data_secTrkLength");


}





void Convolution_Tool::assign_Convolution_CryoRegions_dataHistName_nonVertexVars_Fiducial(ConvolutionShiftMap &input_histmap){


assign_Convolution_CryoRegions_dataHistName(input_histmap.muonPT_Regions,      "h_Data_MuonPT_Fiducial");
assign_Convolution_CryoRegions_dataHistName(input_histmap.muonPZ_Regions,      "h_Data_MuonPZ_Fiducial");
assign_Convolution_CryoRegions_dataHistName(input_histmap.muonE_Regions,       "h_Data_MuonE_Fiducial");
assign_Convolution_CryoRegions_dataHistName(input_histmap.muontheta_Regions,   "h_Data_MuonTheta_Fiducial");
assign_Convolution_CryoRegions_dataHistName(input_histmap.muonDOCA_Regions,    "h_Data_MuonDOCA_Fiducial");
assign_Convolution_CryoRegions_dataHistName(input_histmap.NearestWall_Regions, "h_Data_Distance_to_InnerTank_Fiducial");
assign_Convolution_CryoRegions_dataHistName(input_histmap.recoilDOCA_Regions,  "h_Data_secTrk_DOCA_Fiducial");
assign_Convolution_CryoRegions_dataHistName(input_histmap.recoilAngle_Regions,  "h_Data_secTrk_angle_Fiducial");
assign_Convolution_CryoRegions_dataHistName(input_histmap.tracklength_Regions, "h_Data_secTrkLength_Fiducial");


}






void Convolution_Tool::assign_Convolution_CryoRegions_ConvolutedTRUEName(Convolution_CryoRegions &input_histmap, std::string inputname){
  std::string HistName;
  HistName = inputname + "_upstreamCap";
  assign_CryoVertex_ConvolutedTRUEHistName(HistName , input_histmap.Upstream);
  HistName = inputname + "_barrel";
  assign_CryoVertex_ConvolutedTRUEHistName(HistName , input_histmap.Barrel);
  HistName = inputname + "_downstreamCap";
  assign_CryoVertex_ConvolutedTRUEHistName(HistName , input_histmap.Downstream);
  HistName = inputname + "_downstreamConcaveCap";
  assign_CryoVertex_ConvolutedTRUEHistName(HistName , input_histmap.Concave);
}


void Convolution_Tool::assign_CryoVertex_dataHistName(CryoVertex type,
   std::string AddString, Convolution_CryoRegions &input_histmap){
  std::string histname = GetVertexCryoVarHist_DATA_Name(type) + AddString;
  assign_Convolution_CryoRegions_dataHistName(input_histmap, histname);
}


void Convolution_Tool::assign_Xaxis_title(Convolution_hist &input){
 input.Xaxis_Title = GetVertexCryoVarAxisTitle(input.CryoVertex_type);
}

void Convolution_Tool::assign_Xaxis_CryoVertex_type_Regions(
  Convolution_CryoRegions &input_region_hist)
{
  assign_Xaxis_title(input_region_hist.Upstream);
  assign_Xaxis_title(input_region_hist.Barrel);
  assign_Xaxis_title(input_region_hist.Downstream);
  assign_Xaxis_title(input_region_hist.Concave);
}

void Convolution_Tool::assign_Xaxis_title(ConvolutionShiftMap &input_histmap){

  assign_Xaxis_title(input_histmap.Vertex_X_TotalRegion);
  assign_Xaxis_title(input_histmap.Vertex_Y_TotalRegion);
  assign_Xaxis_title(input_histmap.Vertex_R_TotalRegion);
  //assign_Xaxis_title(input_histmap.Vertex_RR_TotalRegion);
  assign_Xaxis_title(input_histmap.Vertex_Z_TotalRegion);
  assign_Xaxis_title(input_histmap.Vertex_Z_TotalRegion_RCut);
  assign_Xaxis_title(input_histmap.NearestWall_TotalRegion);
  assign_Xaxis_title(input_histmap.DistanceUpstreamCap_TotalRegion);
  assign_Xaxis_title(input_histmap.DistanceDownstreamCap_TotalRegion);
  assign_Xaxis_title(input_histmap.DistanceUpstreamCap_TotalRegion_RCut);
  assign_Xaxis_title(input_histmap.DistanceDownstreamCap_TotalRegion_RCut);


  assign_Xaxis_CryoVertex_type_Regions(input_histmap.Vertex_X_Regions);
  assign_Xaxis_CryoVertex_type_Regions(input_histmap.Vertex_Y_Regions);
  assign_Xaxis_CryoVertex_type_Regions(input_histmap.Vertex_Z_Regions);
  assign_Xaxis_CryoVertex_type_Regions(input_histmap.Vertex_Z_Regions_RCut);
  assign_Xaxis_CryoVertex_type_Regions(input_histmap.Vertex_R_Regions);
  //assign_Xaxis_CryoVertex_type_Regions(input_histmap.Vertex_RR_Regions);
  assign_Xaxis_CryoVertex_type_Regions(input_histmap.NearestWall_Regions);
  assign_Xaxis_CryoVertex_type_Regions(input_histmap.DistanceUpstreamCap_Regions);
  assign_Xaxis_CryoVertex_type_Regions(input_histmap.DistanceDownstreamCap_Regions);
  assign_Xaxis_CryoVertex_type_Regions(input_histmap.DistanceUpstreamCap_Regions_RCut);
  assign_Xaxis_CryoVertex_type_Regions(input_histmap.DistanceDownstreamCap_Regions_RCut);

}

void Convolution_Tool::assignTotalRegion_dataHistName(ConvolutionShiftMap &input_histmap){

  assign_CryoVertex_dataHistName( input_histmap.Vertex_X_TotalRegion.CryoVertex_type,             "",     input_histmap.Vertex_X_TotalRegion);
  assign_CryoVertex_dataHistName( input_histmap.Vertex_Y_TotalRegion.CryoVertex_type,             "",     input_histmap.Vertex_Y_TotalRegion);
  assign_CryoVertex_dataHistName( input_histmap.Vertex_R_TotalRegion.CryoVertex_type,             "",     input_histmap.Vertex_R_TotalRegion);
//assign_CryoVertex_dataHistName( input_histmap.Vertex_RR_TotalRegion.CryoVertex_type,            "",input_histmap.Vertex_RR_TotalRegion);
  assign_CryoVertex_dataHistName( input_histmap.Vertex_Z_TotalRegion.CryoVertex_type,             "",      input_histmap.Vertex_Z_TotalRegion);
  assign_CryoVertex_dataHistName( input_histmap.Vertex_Z_TotalRegion_RCut.CryoVertex_type,        "_RCut", input_histmap.Vertex_Z_TotalRegion_RCut);
  assign_CryoVertex_dataHistName( input_histmap.NearestWall_TotalRegion.CryoVertex_type,          "",      input_histmap.NearestWall_TotalRegion);
  assign_CryoVertex_dataHistName( input_histmap.DistanceUpstreamCap_TotalRegion.CryoVertex_type,  "",      input_histmap.DistanceUpstreamCap_TotalRegion);
  assign_CryoVertex_dataHistName( input_histmap.DistanceDownstreamCap_TotalRegion.CryoVertex_type, "",     input_histmap.DistanceDownstreamCap_TotalRegion);
  assign_CryoVertex_dataHistName( input_histmap.DistanceUpstreamCap_TotalRegion_RCut.CryoVertex_type,   "_RCut",input_histmap.DistanceUpstreamCap_TotalRegion_RCut);
  assign_CryoVertex_dataHistName( input_histmap.DistanceDownstreamCap_TotalRegion_RCut.CryoVertex_type, "_RCut",input_histmap.DistanceDownstreamCap_TotalRegion_RCut);
}


void Convolution_Tool::assignRegions_dataHistName(ConvolutionShiftMap &input_histmap){

  assign_CryoVertex_dataHistName(kX,                     "",input_histmap.Vertex_X_Regions);
  assign_CryoVertex_dataHistName(kY,                     "",input_histmap.Vertex_Y_Regions);
  assign_CryoVertex_dataHistName(kZ,                     "",input_histmap.Vertex_Z_Regions);
  assign_CryoVertex_dataHistName(kZ,                 "_RCut",input_histmap.Vertex_Z_Regions_RCut);
  assign_CryoVertex_dataHistName(kR,                      "",input_histmap.Vertex_R_Regions);
  //assign_CryoVertex_dataHistName(kRR,                     "",input_histmap.Vertex_RR_Regions);
  assign_CryoVertex_dataHistName(kdistance_edge,          "",input_histmap.NearestWall_Regions);
  assign_CryoVertex_dataHistName(kdistance_upstreamcap,   "",input_histmap.DistanceUpstreamCap_Regions);
  assign_CryoVertex_dataHistName(kdistance_downstreamcap, "",input_histmap.DistanceDownstreamCap_Regions);
  assign_CryoVertex_dataHistName(kdistance_upstreamcap,   "_RCut",input_histmap.DistanceUpstreamCap_Regions_RCut);
  assign_CryoVertex_dataHistName(kdistance_downstreamcap, "_RCut",input_histmap.DistanceDownstreamCap_Regions_RCut);
}

void Convolution_Tool::assignRegions_dataHistName_Fiducial(ConvolutionShiftMap &input_histmap){

  assign_CryoVertex_dataHistName(kX,   "_Fiducial",input_histmap.Vertex_X_Regions);
  assign_CryoVertex_dataHistName(kY,   "_Fiducial",input_histmap.Vertex_Y_Regions);
  assign_CryoVertex_dataHistName(kZ,   "_Fiducial",input_histmap.Vertex_Z_Regions);
  assign_CryoVertex_dataHistName(kR,   "_Fiducial",input_histmap.Vertex_R_Regions);

  }

void Convolution_Tool::assign_CryoVertex_type(CryoVertex type , Convolution_hist &input_hist){
  input_hist.CryoVertex_type = type;
}

void Convolution_Tool::assign_CryoVertex_type_Regions(CryoVertex type,
   Convolution_CryoRegions &input_region_hist){
  assign_CryoVertex_type(type, input_region_hist.Upstream);
  assign_CryoVertex_type(type, input_region_hist.Barrel);
  assign_CryoVertex_type(type, input_region_hist.Downstream);
  assign_CryoVertex_type(type, input_region_hist.Concave);
}

void Convolution_Tool::assign_xAxis(){
std::cout<<"assign_xAxis():full"<<std::endl;
assign_Xaxis_title(Full);
std::cout<<"assign_xAxis():full:Finished"<<std::endl;
std::cout<<"assign_xAxis():Empty"<<std::endl;
assign_Xaxis_title(Empty);
std::cout<<"assign_xAxis():Empty:Finished"<<std::endl;
std::cout<<"assign_xAxis():Full - Empty"<<std::endl;
assign_Xaxis_title(Full_Empty);
std::cout<<"assign_xAxis():Full - Empty:Finished"<<std::endl;


std::cout<<"assign_xAxis():full _Fiducial"<<std::endl;
assign_Xaxis_title(Full_Fid);
std::cout<<"assign_xAxis():full:Finished"<<std::endl;
std::cout<<"assign_xAxis():Empty"<<std::endl;
assign_Xaxis_title(Empty_Fid);
std::cout<<"assign_xAxis():Empty:Finished"<<std::endl;
std::cout<<"assign_xAxis():Full - Empty"<<std::endl;
assign_Xaxis_title(Full_Empty_Fid);
std::cout<<"assign_xAxis():Full - Empty:Finished"<<std::endl;

}

void Convolution_Tool::assign_CryoVertex_type(ConvolutionShiftMap &Shift_Map){

  assign_CryoVertex_type(kX, Shift_Map.Vertex_X_TotalRegion);
  assign_CryoVertex_type(kY, Shift_Map.Vertex_Y_TotalRegion);
  assign_CryoVertex_type(kZ, Shift_Map.Vertex_Z_TotalRegion);
  assign_CryoVertex_type(kZ, Shift_Map.Vertex_Z_TotalRegion_RCut);
  assign_CryoVertex_type(kR, Shift_Map.Vertex_R_TotalRegion);
  //assign_CryoVertex_type( kRR, Shift_Map.Vertex_RR_TotalRegion);
  assign_CryoVertex_type(kdistance_edge,          Shift_Map.NearestWall_TotalRegion);
  assign_CryoVertex_type(kdistance_upstreamcap,   Shift_Map.DistanceUpstreamCap_TotalRegion);
  assign_CryoVertex_type(kdistance_downstreamcap, Shift_Map.DistanceDownstreamCap_TotalRegion);

  assign_CryoVertex_type(kdistance_upstreamcap,   Shift_Map.DistanceUpstreamCap_TotalRegion_RCut);
  assign_CryoVertex_type(kdistance_downstreamcap, Shift_Map.DistanceDownstreamCap_TotalRegion_RCut);

  assign_CryoVertex_type_Regions(kX, Shift_Map.Vertex_X_Regions);
  assign_CryoVertex_type_Regions(kY, Shift_Map.Vertex_Y_Regions);
  assign_CryoVertex_type_Regions(kZ, Shift_Map.Vertex_Z_Regions);
  assign_CryoVertex_type_Regions(kZ, Shift_Map.Vertex_Z_Regions_RCut);
  assign_CryoVertex_type_Regions(kR, Shift_Map.Vertex_R_Regions);
  //assign_CryoVertex_type_Regions(kRR ,Shift_Map.Vertex_RR_Regions);
  assign_CryoVertex_type_Regions(kdistance_edge,          Shift_Map.NearestWall_Regions);
  assign_CryoVertex_type_Regions(kdistance_upstreamcap,   Shift_Map.DistanceUpstreamCap_Regions);
  assign_CryoVertex_type_Regions(kdistance_downstreamcap, Shift_Map.DistanceDownstreamCap_Regions);

  assign_CryoVertex_type_Regions(kdistance_upstreamcap,   Shift_Map.DistanceUpstreamCap_Regions_RCut);
  assign_CryoVertex_type_Regions(kdistance_downstreamcap, Shift_Map.DistanceDownstreamCap_Regions_RCut);


}

void Convolution_Tool::assign_CryoVertex_type(){
  assign_CryoVertex_type(Full);
  assign_CryoVertex_type(Empty);
  assign_CryoVertex_type(Full_Empty);

  assign_CryoVertex_type(Full_Fid);
  assign_CryoVertex_type(Empty_Fid);
  assign_CryoVertex_type(Full_Empty_Fid);

}

void Convolution_Tool::assign_TotalRegionHist_dataName(){
  assignTotalRegion_dataHistName(Full);
  assignTotalRegion_dataHistName(Empty);
  assignTotalRegion_dataHistName(Full_Empty);
}

void Convolution_Tool::assign_RegionsHist_dataName(){
  assignRegions_dataHistName(Full);
  assignRegions_dataHistName(Empty);
  assignRegions_dataHistName(Full_Empty);

  assignRegions_dataHistName_Fiducial(Full_Fid);
  assignRegions_dataHistName_Fiducial(Empty_Fid);
  assignRegions_dataHistName_Fiducial(Full_Empty_Fid);


}

void Convolution_Tool::assign_RegionsHist_RecoandTRUEName(){

  assign_CryoVertex_TotalRegion_RecoandTRUEHistName(Full);
  assign_CryoVertex_TotalRegion_RecoandTRUEHistName(Empty);
  assign_CryoVertex_TotalRegion_RecoandTRUEHistName(Full_Empty);
  assign_Convolution_CryoRegions_HistName(Full);
  assign_Convolution_CryoRegions_HistName(Empty);
  assign_Convolution_CryoRegions_HistName(Full_Empty);
}





void Convolution_Tool::assign_CryoVertexTotalRegion_ConvolutedTRUEHistName(){

  assign_CryoVertexTotalRegion_ConvolutedTRUEHistName(Full);
  assign_CryoVertexTotalRegion_ConvolutedTRUEHistName(Empty);
  assign_CryoVertexTotalRegion_ConvolutedTRUEHistName(Full_Empty);

}

void Convolution_Tool::init_DataHists_Total_PlaylistCombined(Convolution_hist& input, ME_playlist_TFileMAP TFile_Map_Data, ME_helium_Playlists StartingPlaylist )
{
  std::string var;
  var = input.Data_name;
  std::cout<<"init data name: "<< var << std::endl;
  Playlist_MnvH1D_Map  Map_data = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_Data, var );
  input.MnvH1D_data =  Combine_Hists_fromMAP(Map_data , StartingPlaylist ,"h_data");

}

void Convolution_Tool::init_DataHists_Regions_PlaylistCombined(Convolution_CryoRegions& input, ME_playlist_TFileMAP TFile_Map_Data, ME_helium_Playlists StartingPlaylist )
{
  init_DataHists_Total_PlaylistCombined(input.Upstream,    TFile_Map_Data,  StartingPlaylist );
  init_DataHists_Total_PlaylistCombined(input.Barrel,      TFile_Map_Data,  StartingPlaylist );
  init_DataHists_Total_PlaylistCombined(input.Downstream,  TFile_Map_Data,  StartingPlaylist );
  init_DataHists_Total_PlaylistCombined(input.Concave,     TFile_Map_Data,  StartingPlaylist );
}


void Convolution_Tool::init_DataHists_Total_PlaylistCombined(ConvolutionShiftMap &input,
   ME_playlist_TFileMAP TFile_Map_Data, ME_helium_Playlists StartingPlaylist ){
  init_DataHists_Total_PlaylistCombined(input.Vertex_X_TotalRegion,                   TFile_Map_Data, StartingPlaylist);
  init_DataHists_Total_PlaylistCombined(input.Vertex_Y_TotalRegion,                   TFile_Map_Data, StartingPlaylist);
  init_DataHists_Total_PlaylistCombined(input.Vertex_R_TotalRegion,                   TFile_Map_Data, StartingPlaylist);
  //init_DataHists_Total_PlaylistCombined(input.Vertex_RR_TotalRegion,                TFile_Map_Data, StartingPlaylist);
  init_DataHists_Total_PlaylistCombined(input.Vertex_Z_TotalRegion,                   TFile_Map_Data, StartingPlaylist);
  init_DataHists_Total_PlaylistCombined(input.Vertex_Z_TotalRegion_RCut,              TFile_Map_Data, StartingPlaylist);
  init_DataHists_Total_PlaylistCombined(input.NearestWall_TotalRegion,                TFile_Map_Data, StartingPlaylist);
  init_DataHists_Total_PlaylistCombined(input.DistanceUpstreamCap_TotalRegion,        TFile_Map_Data, StartingPlaylist);
  init_DataHists_Total_PlaylistCombined(input.DistanceDownstreamCap_TotalRegion,      TFile_Map_Data, StartingPlaylist);
  init_DataHists_Total_PlaylistCombined(input.DistanceUpstreamCap_TotalRegion_RCut,   TFile_Map_Data, StartingPlaylist);
  init_DataHists_Total_PlaylistCombined(input.DistanceDownstreamCap_TotalRegion_RCut, TFile_Map_Data, StartingPlaylist);
}

void Convolution_Tool::init_DataHists_Regions_PlaylistCombined(ConvolutionShiftMap &input, ME_playlist_TFileMAP TFile_Map_Data, ME_helium_Playlists StartingPlaylist ){

  init_DataHists_Regions_PlaylistCombined(input.Vertex_X_Regions,                    TFile_Map_Data, StartingPlaylist);
  init_DataHists_Regions_PlaylistCombined(input.Vertex_Y_Regions,                    TFile_Map_Data, StartingPlaylist);
  init_DataHists_Regions_PlaylistCombined(input.Vertex_Z_Regions,                    TFile_Map_Data, StartingPlaylist);
  init_DataHists_Regions_PlaylistCombined(input.Vertex_Z_Regions_RCut,               TFile_Map_Data, StartingPlaylist);
  init_DataHists_Regions_PlaylistCombined(input.Vertex_R_Regions,                    TFile_Map_Data, StartingPlaylist);
  //init_DataHists_Regions_PlaylistCombined(input.Vertex_RR_Regions,                 TFile_Map_Data, StartingPlaylist);
  init_DataHists_Regions_PlaylistCombined(input.NearestWall_Regions,                 TFile_Map_Data, StartingPlaylist);
  init_DataHists_Regions_PlaylistCombined(input.DistanceUpstreamCap_Regions,         TFile_Map_Data, StartingPlaylist);
  init_DataHists_Regions_PlaylistCombined(input.DistanceDownstreamCap_Regions,       TFile_Map_Data, StartingPlaylist);
  init_DataHists_Regions_PlaylistCombined(input.DistanceUpstreamCap_Regions_RCut,    TFile_Map_Data, StartingPlaylist);
  init_DataHists_Regions_PlaylistCombined(input.DistanceDownstreamCap_Regions_RCut,  TFile_Map_Data, StartingPlaylist);
}

void Convolution_Tool::init_DataHists_Regions_PlaylistCombined_Fitonly(
  ConvolutionShiftMap &input, ME_playlist_TFileMAP TFile_Map_Data, ME_helium_Playlists StartingPlaylist ){

  init_DataHists_Regions_PlaylistCombined(input.Vertex_X_Regions,                    TFile_Map_Data, StartingPlaylist);
  init_DataHists_Regions_PlaylistCombined(input.Vertex_Y_Regions,                    TFile_Map_Data, StartingPlaylist);
  init_DataHists_Regions_PlaylistCombined(input.Vertex_Z_Regions,                    TFile_Map_Data, StartingPlaylist);
  init_DataHists_Regions_PlaylistCombined(input.Vertex_R_Regions,                    TFile_Map_Data, StartingPlaylist);
}

void Convolution_Tool::init_DataHists_Regions_nonVertexVars_PlaylistCombined(
  ConvolutionShiftMap &input, ME_playlist_TFileMAP TFile_Map_Data,
   ME_helium_Playlists StartingPlaylist ){

  init_DataHists_Regions_PlaylistCombined(input.muonPT_Regions, TFile_Map_Data, StartingPlaylist);
  init_DataHists_Regions_PlaylistCombined(input.muonPZ_Regions, TFile_Map_Data, StartingPlaylist);
  init_DataHists_Regions_PlaylistCombined(input.muonE_Regions, TFile_Map_Data, StartingPlaylist);
  init_DataHists_Regions_PlaylistCombined(input.muontheta_Regions, TFile_Map_Data, StartingPlaylist);
  init_DataHists_Regions_PlaylistCombined(input.muonDOCA_Regions, TFile_Map_Data, StartingPlaylist);
  init_DataHists_Regions_PlaylistCombined(input.NearestWall_Regions, TFile_Map_Data, StartingPlaylist);
  init_DataHists_Regions_PlaylistCombined(input.recoilDOCA_Regions, TFile_Map_Data, StartingPlaylist);
  init_DataHists_Regions_PlaylistCombined(input.recoilAngle_Regions, TFile_Map_Data, StartingPlaylist);
  init_DataHists_Regions_PlaylistCombined(input.tracklength_Regions, TFile_Map_Data, StartingPlaylist);

}



void Convolution_Tool::init_All_DataHists(){
std::cout<<"~~~~~~~~~~~Initizing Data Hist~~~~~~~~~~``"<< std::endl;
init_DataHists_Total_PlaylistCombined(Full,   TFile_Map_Full_Data,  StartingPlaylist_Full);
init_DataHists_Regions_PlaylistCombined(Full, TFile_Map_Full_Data,  StartingPlaylist_Full);
std::cout<<"~~~~~~~~~~~Initizing Data Hist:Regions_nonVertexVars~~~~~~~~~~``"<< std::endl;
init_DataHists_Regions_nonVertexVars_PlaylistCombined(Full, TFile_Map_Full_Data,  StartingPlaylist_Full );

init_DataHists_Regions_PlaylistCombined_Fitonly(Full_Fid, TFile_Map_Full_Data,  StartingPlaylist_Full);
std::cout<<"~~~~~~~~~~~Initizing Data Hist:Regions_nonVertexVars~~~~~~~~~~``"<< std::endl;
init_DataHists_Regions_nonVertexVars_PlaylistCombined(Full_Fid, TFile_Map_Full_Data,  StartingPlaylist_Full );


init_DataHists_Total_PlaylistCombined( Full_Empty,   TFile_Map_Full_Data,  StartingPlaylist_Full);
init_DataHists_Regions_PlaylistCombined(Full_Empty, TFile_Map_Full_Data,  StartingPlaylist_Full);


init_DataHists_Total_PlaylistCombined(  Empty,   TFile_Map_Empty_Data, StartingPlaylist_Empty);
init_DataHists_Regions_PlaylistCombined(Empty, TFile_Map_Empty_Data, StartingPlaylist_Empty);
init_DataHists_Regions_nonVertexVars_PlaylistCombined(Empty, TFile_Map_Empty_Data, StartingPlaylist_Empty );

POTscaleData_Total(Empty,   Empty.POT_Data);
POTscaleData_Regions(Empty, Empty.POT_Data);
POTscaleData_Regions_nonVertexVars(Empty, Empty.POT_Data);
///

init_DataHists_Regions_PlaylistCombined_Fitonly(Empty_Fid, TFile_Map_Empty_Data, StartingPlaylist_Empty);
init_DataHists_Regions_nonVertexVars_PlaylistCombined(Empty_Fid, TFile_Map_Empty_Data, StartingPlaylist_Empty );

POTscaleData_Regions_Fitonly(Empty_Fid, Empty.POT_Data);
POTscaleData_Regions_nonVertexVars(Empty_Fid, Empty.POT_Data);


Subtract_DataHists_Regions(Full_Empty,  Empty);
Subtract_DataHists_Total(  Full_Empty,    Empty);
std::cout<<"~~~~~~~~Finished Data Hist~~~~~~~~~~~~``"<< std::endl;

}


void Convolution_Tool::init_All_DataEmptyHists(){
std::cout<<"~~~~~~~~~~~Initizing Data Hist~~~~~~~~~~``"<< std::endl;
//init_DataHists_Total_PlaylistCombined(  Empty,   TFile_Map_Empty_Data, StartingPlaylist_Empty);
init_DataHists_Regions_PlaylistCombined_Fitonly(Empty, TFile_Map_Empty_Data, StartingPlaylist_Empty);

//POTscaleData_Total(Empty,   Empty.POT_Data);
POTscaleData_Regions_Fitonly(Empty, Empty.POT_Data);

}



void Convolution_Tool::init_All_DataFullHists(){
std::cout<<"~~~~~~~~~~~Initizing Data Hist~~~~~~~~~~``"<< std::endl;
//init_DataHists_Total_PlaylistCombined(  Empty,   TFile_Map_Empty_Data, StartingPlaylist_Empty);
init_DataHists_Regions_PlaylistCombined_Fitonly(Full, TFile_Map_Full_Data, StartingPlaylist_Full);

//POTscaleData_Total(Empty,   Empty.POT_Data);
//POTscaleData_Regions_Fitonly(Empty, Empty.POT_Data);

}

void Convolution_Tool::init_RecoHists_PlaylistCombinedMC(Convolution_hist &input,
   ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist )
{
  std::string var;
  var = input.Reco_name;
  Playlist_MnvH1D_Map  Map_Reco = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
  input.MnvH1D_mc_Reco =  Combine_Hists_fromMAP(Map_Reco , StartingPlaylist ,"Map_Reco");

}


void Convolution_Tool::init_RecoHists_PlaylistCombinedMC(Convolution_CryoRegions& input,
   ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist )
{
  init_RecoHists_PlaylistCombinedMC(input.Upstream   ,TFile_Map_MC, StartingPlaylist);
  init_RecoHists_PlaylistCombinedMC(input.Barrel     ,TFile_Map_MC, StartingPlaylist);
  init_RecoHists_PlaylistCombinedMC(input.Downstream ,TFile_Map_MC, StartingPlaylist);
  init_RecoHists_PlaylistCombinedMC(input.Concave    ,TFile_Map_MC, StartingPlaylist);
}


void Convolution_Tool::init_RecoHists_Total_PlaylistCombinedMC(ConvolutionShiftMap &input,
   ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist )
{
  init_RecoHists_PlaylistCombinedMC(input.Vertex_X_TotalRegion,                   TFile_Map_MC, StartingPlaylist);
  init_RecoHists_PlaylistCombinedMC(input.Vertex_Y_TotalRegion,                   TFile_Map_MC, StartingPlaylist);
  init_RecoHists_PlaylistCombinedMC(input.Vertex_R_TotalRegion,                   TFile_Map_MC, StartingPlaylist);
  //init_RecoHists_PlaylistCombinedMC(input.Vertex_RR_TotalRegion,                  TFile_Map_MC, StartingPlaylist);
  init_RecoHists_PlaylistCombinedMC(input.Vertex_Z_TotalRegion,                   TFile_Map_MC, StartingPlaylist);
  init_RecoHists_PlaylistCombinedMC(input.Vertex_Z_TotalRegion_RCut,              TFile_Map_MC, StartingPlaylist);
  init_RecoHists_PlaylistCombinedMC(input.NearestWall_TotalRegion,                TFile_Map_MC, StartingPlaylist);
  init_RecoHists_PlaylistCombinedMC(input.DistanceUpstreamCap_TotalRegion,        TFile_Map_MC, StartingPlaylist);
  init_RecoHists_PlaylistCombinedMC(input.DistanceDownstreamCap_TotalRegion,      TFile_Map_MC, StartingPlaylist);
  init_RecoHists_PlaylistCombinedMC(input.DistanceUpstreamCap_TotalRegion_RCut,   TFile_Map_MC, StartingPlaylist);
  init_RecoHists_PlaylistCombinedMC(input.DistanceDownstreamCap_TotalRegion_RCut, TFile_Map_MC, StartingPlaylist);
}

void Convolution_Tool::init_RecoHists_Regions_PlaylistCombinedMC(ConvolutionShiftMap &input,
   ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist )
{
  init_RecoHists_PlaylistCombinedMC(input.Vertex_X_Regions,                   TFile_Map_MC, StartingPlaylist);
  init_RecoHists_PlaylistCombinedMC(input.Vertex_Y_Regions,                   TFile_Map_MC, StartingPlaylist);
  init_RecoHists_PlaylistCombinedMC(input.Vertex_Z_Regions,                   TFile_Map_MC, StartingPlaylist);
  init_RecoHists_PlaylistCombinedMC(input.Vertex_Z_Regions_RCut,              TFile_Map_MC, StartingPlaylist);
  init_RecoHists_PlaylistCombinedMC(input.Vertex_R_Regions,                   TFile_Map_MC, StartingPlaylist);
  //init_RecoHists_PlaylistCombinedMC(input.Vertex_RR_Regions,                TFile_Map_MC, StartingPlaylist);
  init_RecoHists_PlaylistCombinedMC(input.NearestWall_Regions,                TFile_Map_MC, StartingPlaylist);
  init_RecoHists_PlaylistCombinedMC(input.DistanceUpstreamCap_Regions,        TFile_Map_MC, StartingPlaylist);
  init_RecoHists_PlaylistCombinedMC(input.DistanceDownstreamCap_Regions,      TFile_Map_MC, StartingPlaylist);
  init_RecoHists_PlaylistCombinedMC(input.DistanceUpstreamCap_Regions_RCut,   TFile_Map_MC, StartingPlaylist);
  init_RecoHists_PlaylistCombinedMC(input.DistanceDownstreamCap_Regions_RCut, TFile_Map_MC, StartingPlaylist);
}


void Convolution_Tool::init_All_RecoHists(){
std::cout<<"~~~~~~~~~~Intializing RECO Hist ~~~~~~~~~~~~"<<std::endl;
  init_RecoHists_Total_PlaylistCombinedMC(Full,   TFile_Map_Full_MC,  StartingPlaylist_Full);
  init_RecoHists_Regions_PlaylistCombinedMC(Full, TFile_Map_Full_MC,  StartingPlaylist_Full);

  POTscale_MCReco_Total(Full,   Full.POT_MC);
  POTscale_MCReco_Regions(Full, Full.POT_MC);

  init_RecoHists_Total_PlaylistCombinedMC(Full_Empty,   TFile_Map_Full_MC,  StartingPlaylist_Full);
  init_RecoHists_Regions_PlaylistCombinedMC(Full_Empty, TFile_Map_Full_MC,  StartingPlaylist_Full);

  POTscale_MCReco_Total(Full_Empty,   Full.POT_MC);
  POTscale_MCReco_Regions(Full_Empty, Full.POT_MC);

  init_RecoHists_Total_PlaylistCombinedMC(Empty,   TFile_Map_Empty_MC, StartingPlaylist_Empty);
  init_RecoHists_Regions_PlaylistCombinedMC(Empty, TFile_Map_Empty_MC, StartingPlaylist_Empty);

  POTscale_MCReco_Total(Empty,   Empty.POT_MC);
  POTscale_MCReco_Regions(Empty, Empty.POT_MC);

  Subtract_RecoHists_Total(Full_Empty, Empty);
  Subtract_RecoHists_Regions(Full_Empty, Empty);

  std::cout<<"~~~~~~~~~~Finished RECO Hist ~~~~~~~~~~~~"<<std::endl;

}


void Convolution_Tool::init_Total_RecoHists(){
  std::cout << "nit_Total_RecoHists()"<<std::endl;
  init_RecoHists_Total_PlaylistCombinedMC(Full,   TFile_Map_Full_MC,  StartingPlaylist_Full);
  std::cout<<"init_RecoHists_Total_PlaylistCombinedMC::Finshied initalize  total"<< std::endl;
  POTscale_MCReco_Total(Full , Full.POT_MC);
  std::cout<<"Finished POT RECO total"<< std::endl;
  init_RecoHists_Total_PlaylistCombinedMC(Full_Empty,   TFile_Map_Full_MC,  StartingPlaylist_Full);
  std::cout<<"int F - E "<< std::endl;
  POTscale_MCReco_Total(Full_Empty , Full.POT_MC);
  std::cout<<"Finished POT RECO total F - E"<< std::endl;
  init_RecoHists_Total_PlaylistCombinedMC(Empty,   TFile_Map_Empty_MC, StartingPlaylist_Empty);
  std::cout<<"Finished init E"<< std::endl;

  POTscale_MCReco_Total(Empty , Empty.POT_MC);
  std::cout<<"Finished POT E"<< std::endl;
  Subtract_RecoHists_Total(Full_Empty, Empty);
  std::cout<<"Finished Subtraction "<< std::endl;
}
void Convolution_Tool::init_Regions_RecoHists(){
  init_RecoHists_Regions_PlaylistCombinedMC(Full, TFile_Map_Full_MC,  StartingPlaylist_Full);
  POTscale_MCReco_Regions(Full , Full.POT_MC);
  init_RecoHists_Regions_PlaylistCombinedMC(Full_Empty, TFile_Map_Full_MC,  StartingPlaylist_Full);
  POTscale_MCReco_Regions(Full_Empty , Full.POT_MC);
  init_RecoHists_Regions_PlaylistCombinedMC(Empty, TFile_Map_Empty_MC, StartingPlaylist_Empty);
  POTscale_MCReco_Regions(Empty , Empty.POT_MC);
  Subtract_RecoHists_Regions(Full_Empty, Empty);
}


void Convolution_Tool::init_TRUEHists_PlaylistCombinedMC(Convolution_hist& input,
   ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist )
{
  std::string var;
  var = input.TRUE_name;
  Playlist_MnvH1D_Map  Map_TRUE = Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
  input.MnvH1D_mc_TRUTH =  Combine_Hists_fromMAP(Map_TRUE , StartingPlaylist ,"h_TRUE");

}

void Convolution_Tool::init_TRUEHists_PlaylistCombinedMC(Convolution_CryoRegions& input,
   ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist )
{
  init_TRUEHists_PlaylistCombinedMC(input.Upstream ,  TFile_Map_MC, StartingPlaylist);
  init_TRUEHists_PlaylistCombinedMC(input.Barrel ,    TFile_Map_MC, StartingPlaylist);
  init_TRUEHists_PlaylistCombinedMC(input.Downstream ,TFile_Map_MC, StartingPlaylist);
  init_TRUEHists_PlaylistCombinedMC(input.Concave ,   TFile_Map_MC, StartingPlaylist);
}


void Convolution_Tool::init_TRUEHists_Total_PlaylistCombinedMC(ConvolutionShiftMap &input,
   ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist )
{std::cout<<"inside::init_TRUEHists_Total_PlaylistCombinedMC"<<std::endl;
  init_TRUEHists_PlaylistCombinedMC(input.Vertex_X_TotalRegion,                    TFile_Map_MC , StartingPlaylist);
  init_TRUEHists_PlaylistCombinedMC(input.Vertex_Y_TotalRegion,                    TFile_Map_MC , StartingPlaylist);
  init_TRUEHists_PlaylistCombinedMC(input.Vertex_R_TotalRegion,                    TFile_Map_MC , StartingPlaylist);
  //init_TRUEHists_PlaylistCombinedMC(input.Vertex_RR_TotalRegion,                   TFile_Map_MC , StartingPlaylist);
  init_TRUEHists_PlaylistCombinedMC(input.Vertex_Z_TotalRegion,                    TFile_Map_MC , StartingPlaylist);
  init_TRUEHists_PlaylistCombinedMC(input.Vertex_Z_TotalRegion_RCut ,              TFile_Map_MC , StartingPlaylist);
  init_TRUEHists_PlaylistCombinedMC(input.NearestWall_TotalRegion,                 TFile_Map_MC , StartingPlaylist);
  init_TRUEHists_PlaylistCombinedMC(input.DistanceUpstreamCap_TotalRegion ,        TFile_Map_MC , StartingPlaylist);
  init_TRUEHists_PlaylistCombinedMC(input.DistanceDownstreamCap_TotalRegion ,      TFile_Map_MC , StartingPlaylist);
  init_TRUEHists_PlaylistCombinedMC(input.DistanceUpstreamCap_TotalRegion_RCut ,   TFile_Map_MC , StartingPlaylist);
  init_TRUEHists_PlaylistCombinedMC(input.DistanceDownstreamCap_TotalRegion_RCut , TFile_Map_MC , StartingPlaylist);

}

void Convolution_Tool::init_TRUEHists_Regions_PlaylistCombinedMC(ConvolutionShiftMap &input,
   ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist )
{
  init_TRUEHists_PlaylistCombinedMC(input.Vertex_X_Regions,                   TFile_Map_MC, StartingPlaylist);
  init_TRUEHists_PlaylistCombinedMC(input.Vertex_Y_Regions,                   TFile_Map_MC, StartingPlaylist);
  init_TRUEHists_PlaylistCombinedMC(input.Vertex_Z_Regions,                   TFile_Map_MC, StartingPlaylist);
  init_TRUEHists_PlaylistCombinedMC(input.Vertex_Z_Regions_RCut,              TFile_Map_MC, StartingPlaylist);
  init_TRUEHists_PlaylistCombinedMC(input.Vertex_R_Regions,                   TFile_Map_MC, StartingPlaylist);
  //init_TRUEHists_PlaylistCombinedMC(input.Vertex_RR_Regions,                TFile_Map_MC, StartingPlaylist);
  init_TRUEHists_PlaylistCombinedMC(input.NearestWall_Regions,                TFile_Map_MC, StartingPlaylist);
  init_TRUEHists_PlaylistCombinedMC(input.DistanceUpstreamCap_Regions,        TFile_Map_MC, StartingPlaylist);
  init_TRUEHists_PlaylistCombinedMC(input.DistanceDownstreamCap_Regions,      TFile_Map_MC, StartingPlaylist);
  init_TRUEHists_PlaylistCombinedMC(input.DistanceUpstreamCap_Regions_RCut,   TFile_Map_MC, StartingPlaylist);
  init_TRUEHists_PlaylistCombinedMC(input.DistanceDownstreamCap_Regions_RCut, TFile_Map_MC, StartingPlaylist);
}

void Convolution_Tool::init_All_TRUEHists(){
  std::cout<< "init_All_TRUEHists::init FUll  "<< std::endl;
  init_TRUEHists_Total_PlaylistCombinedMC(Full,   TFile_Map_Full_MC,  StartingPlaylist_Full);
  init_TRUEHists_Regions_PlaylistCombinedMC(Full, TFile_Map_Full_MC,  StartingPlaylist_Full);

  std::cout<< "Finished init "<< std::endl;
  std::cout << "Starting to POT Scale: FUll"<<std::endl;
  POTscale_MCTRUTH_Total(Full , Full.POT_MC);
  POTscale_MCTRUTH_Regions(Full , Full.POT_MC);


    std::cout<< "init F - E  "<< std::endl;
  init_TRUEHists_Total_PlaylistCombinedMC(Full_Empty,   TFile_Map_Full_MC,  StartingPlaylist_Full);
  init_TRUEHists_Regions_PlaylistCombinedMC(Full_Empty, TFile_Map_Full_MC,  StartingPlaylist_Full);

    std::cout<< "Scaling F - E  "<< std::endl;
  POTscale_MCTRUTH_Total(Full_Empty , Full.POT_MC);
  POTscale_MCTRUTH_Regions(Full_Empty , Full.POT_MC);

  std::cout<< "init E  "<< std::endl;
  init_TRUEHists_Total_PlaylistCombinedMC(Empty,   TFile_Map_Empty_MC,  StartingPlaylist_Empty);
  init_TRUEHists_Regions_PlaylistCombinedMC(Empty, TFile_Map_Empty_MC,  StartingPlaylist_Empty);

  std::cout << "Starting to POT Scale: Empty"<<std::endl;
  POTscale_MCTRUTH_Total(Empty , Empty.POT_MC);
  POTscale_MCTRUTH_Regions(Empty , Empty.POT_MC);

  std::cout << "Subtraction Total "<<std::endl;
  Subtract_TRUEHists_Total(Full_Empty, Empty);
    std::cout << "Subtraction Regions "<<std::endl;
  Subtract_TRUEHists_Regions(Full_Empty, Empty);
  std::cout<< "~~~~~~~~~~~ Finished  TRUEHists ~~~~~~~~~~~~"<< std::endl;
}

void Convolution_Tool::init_Total_TRUEHists(){

  init_TRUEHists_Total_PlaylistCombinedMC(Full,   TFile_Map_Full_MC,  StartingPlaylist_Full);
  POTscale_MCTRUTH_Total(Full , Full.POT_MC);
  init_TRUEHists_Total_PlaylistCombinedMC(Full_Empty,   TFile_Map_Full_MC,  StartingPlaylist_Full);
  POTscale_MCTRUTH_Total(Full_Empty , Full.POT_MC);
  init_TRUEHists_Total_PlaylistCombinedMC(Empty,   TFile_Map_Empty_MC,  StartingPlaylist_Empty);
  POTscale_MCTRUTH_Total(Empty , Empty.POT_MC);
  Subtract_TRUEHists_Total(Full_Empty, Empty);

}

void Convolution_Tool::init_Regions_TRUEHists(){

  init_TRUEHists_Regions_PlaylistCombinedMC(Full, TFile_Map_Full_MC,  StartingPlaylist_Full);
  POTscale_MCTRUTH_Regions(Full , Full.POT_MC);
  init_TRUEHists_Regions_PlaylistCombinedMC(Full_Empty, TFile_Map_Full_MC,  StartingPlaylist_Full);
  POTscale_MCTRUTH_Regions(Full_Empty , Full.POT_MC);
  init_TRUEHists_Regions_PlaylistCombinedMC(Empty, TFile_Map_Empty_MC,  StartingPlaylist_Empty);
  POTscale_MCTRUTH_Regions(Empty , Empty.POT_MC);
  Subtract_TRUEHists_Regions(Full_Empty, Empty);

}



void Convolution_Tool::init_TRUTHConvolutionHist_MCShifted_PlaylistCombined(Convolution_hist& input,
   std::string ExtraString, ME_playlist_TFileMAP TFile_Map_MC,
    ME_helium_Playlists StartingPlaylist, int i, int j, int k )
{
  std::string string_i = std::to_string(i);
  std::string string_j = std::to_string(j);
  std::string string_k = std::to_string(k);
  std::string var;

  var = input.TRUE_Convoluted_name + ExtraString+ "_TRUE" + "_i_j_k_" + string_i + "_" +  string_j + "_" + string_k;
  Playlist_MnvH1D_Map  Convolution_toData_Map_0 =    Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
  input.MnvH1D_mc_Convoluted[0] =  Combine_Hists_fromMAP(Convolution_toData_Map_0 , StartingPlaylist ,"Convolution_toData_0");

}

void Convolution_Tool::init_TRUTHConvolution_RegionsHists_MCShifted_PlaylistCombined(
  Convolution_CryoRegions& input, std::string ExtraString,
  ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist , int i, int j, int k)
{
  init_TRUTHConvolutionHist_MCShifted_PlaylistCombined(input.Upstream,   "", TFile_Map_MC, StartingPlaylist, i,  j,  k);
  init_TRUTHConvolutionHist_MCShifted_PlaylistCombined(input.Barrel,     "", TFile_Map_MC, StartingPlaylist, i,  j,  k);
  init_TRUTHConvolutionHist_MCShifted_PlaylistCombined(input.Downstream, "", TFile_Map_MC, StartingPlaylist, i,  j,  k);
  init_TRUTHConvolutionHist_MCShifted_PlaylistCombined(input.Concave,    "", TFile_Map_MC, StartingPlaylist, i,  j,  k);
}



void Convolution_Tool::init_TRUTHConvolution_RegionsHists_MCShifted_PlaylistCombined(ConvolutionShiftMap &input, std::string ExtraString, ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist, int i, int j, int k )
{
init_TRUTHConvolution_RegionsHists_MCShifted_PlaylistCombined(input.Vertex_X_Regions,                  "", TFile_Map_MC, StartingPlaylist, i, j, k);
init_TRUTHConvolution_RegionsHists_MCShifted_PlaylistCombined(input.Vertex_Y_Regions,                  "", TFile_Map_MC, StartingPlaylist, i, j, k);
init_TRUTHConvolution_RegionsHists_MCShifted_PlaylistCombined(input.Vertex_Z_Regions,                  "", TFile_Map_MC, StartingPlaylist, i, j, k);
init_TRUTHConvolution_RegionsHists_MCShifted_PlaylistCombined(input.Vertex_Z_Regions_RCut,             "", TFile_Map_MC, StartingPlaylist, i, j, k);
init_TRUTHConvolution_RegionsHists_MCShifted_PlaylistCombined(input.Vertex_R_Regions,                  "", TFile_Map_MC, StartingPlaylist, i, j, k);
//init_TRUTHConvolution_RegionsHists_MCShifted_PlaylistCombined(input.Vertex_RR_Regions,                 "", TFile_Map_MC, i,j,k, StartingPlaylist);
init_TRUTHConvolution_RegionsHists_MCShifted_PlaylistCombined(input.NearestWall_Regions,               "", TFile_Map_MC, StartingPlaylist, i, j, k);
init_TRUTHConvolution_RegionsHists_MCShifted_PlaylistCombined(input.DistanceUpstreamCap_Regions,       "", TFile_Map_MC, StartingPlaylist, i, j, k);
init_TRUTHConvolution_RegionsHists_MCShifted_PlaylistCombined(input.DistanceDownstreamCap_Regions,     "", TFile_Map_MC, StartingPlaylist, i, j, k);
init_TRUTHConvolution_RegionsHists_MCShifted_PlaylistCombined(input.DistanceUpstreamCap_Regions_RCut,  "", TFile_Map_MC, StartingPlaylist, i, j, k);
init_TRUTHConvolution_RegionsHists_MCShifted_PlaylistCombined(input.DistanceDownstreamCap_Regions_RCut,"", TFile_Map_MC, StartingPlaylist, i, j, k);
}


void Convolution_Tool::init_TRUE_ConvolutionTotalHists_PlaylistCombinedMC(ConvolutionShiftMap &input, ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist, int i, int j, int k )
{
init_TRUTHConvolutionHist_MCShifted_PlaylistCombined(input.Vertex_X_TotalRegion,                    "",  TFile_Map_MC, StartingPlaylist, i , j, k );
init_TRUTHConvolutionHist_MCShifted_PlaylistCombined(input.Vertex_Y_TotalRegion,                    "",  TFile_Map_MC, StartingPlaylist, i , j, k );
init_TRUTHConvolutionHist_MCShifted_PlaylistCombined(input.Vertex_R_TotalRegion,                    "",  TFile_Map_MC, StartingPlaylist, i , j, k );
//init_TRUTHConvolutionHist_MCShifted_PlaylistCombined(input.Vertex_RR_TotalRegion,                   "",  TFile_Map_MC, i , j, k, StartingPlaylist );
init_TRUTHConvolutionHist_MCShifted_PlaylistCombined(input.Vertex_Z_TotalRegion,                    "",  TFile_Map_MC, StartingPlaylist, i, j, k);
init_TRUTHConvolutionHist_MCShifted_PlaylistCombined(input.Vertex_Z_TotalRegion_RCut,               "",  TFile_Map_MC, StartingPlaylist, i, j, k);
init_TRUTHConvolutionHist_MCShifted_PlaylistCombined(input.NearestWall_TotalRegion,                 "",  TFile_Map_MC, StartingPlaylist, i, j, k);
init_TRUTHConvolutionHist_MCShifted_PlaylistCombined(input.DistanceUpstreamCap_TotalRegion,         "",  TFile_Map_MC, StartingPlaylist, i, j, k);
init_TRUTHConvolutionHist_MCShifted_PlaylistCombined(input.DistanceDownstreamCap_TotalRegion,       "",  TFile_Map_MC, StartingPlaylist, i, j, k);
init_TRUTHConvolutionHist_MCShifted_PlaylistCombined(input.DistanceUpstreamCap_TotalRegion_RCut,    "",  TFile_Map_MC, StartingPlaylist, i, j, k);
init_TRUTHConvolutionHist_MCShifted_PlaylistCombined(input.DistanceDownstreamCap_TotalRegion_RCut,  "",  TFile_Map_MC, StartingPlaylist, i, j, k);
//std::cout<<"Finished:init_TRUE_ConvolutionTotalHists_PlaylistCombinedMC"<<std::endl;
}

void Convolution_Tool::init_TRUE_Total_and_Regions_Hists_PlaylistCombinedMC(ConvolutionShiftMap &input, ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist, int i, int j, int k ){

init_TRUE_ConvolutionTotalHists_PlaylistCombinedMC(input, TFile_Map_MC,  StartingPlaylist,  i ,  j,  k );
init_TRUTHConvolution_RegionsHists_MCShifted_PlaylistCombined(input, "",  TFile_Map_MC , StartingPlaylist,  i ,  j,  k );

}

void  Convolution_Tool::init_TRUE_Convolution_TotalHists_PlaylistCombinedMC(int i, int j, int k){
// Ful
init_TRUE_ConvolutionTotalHists_PlaylistCombinedMC(Full,         TFile_Map_Full_MC,   StartingPlaylist_Full,  i,  j,  k);
//std::cout<<"Finished Full"<<std::endl;
init_TRUE_ConvolutionTotalHists_PlaylistCombinedMC(Full_Empty,   TFile_Map_Full_MC,   StartingPlaylist_Full,  i,  j,  k);
//std::cout<<"Finished Full - Empty"<<std::endl;
init_TRUE_ConvolutionTotalHists_PlaylistCombinedMC(Empty,        TFile_Map_Empty_MC,  StartingPlaylist_Empty, i,  j,  k);
//std::cout<<"Empty"<<std::endl;
//std::cout<<"Finished Intializes now to POT scale"<<std::endl;

POTscale_MC_Convoluted_Total(Full,        Full.POT_MC, 0);
POTscale_MC_Convoluted_Total(Full_Empty , Full.POT_MC, 0);
POTscale_MC_Convoluted_Total(Empty,      Empty.POT_MC, 0);
//std::cout<<"Now to Scale"<<std::endl;

Subtract_TRUEConvolutionHists_Total(Full_Empty , Empty, 0);

}

void  Convolution_Tool::init_TRUE_Convolution_Regions_Hists_PlaylistCombinedMC(int i, int j, int k){
// Full
init_TRUTHConvolution_RegionsHists_MCShifted_PlaylistCombined(Full,  "",       TFile_Map_Full_MC,   StartingPlaylist_Full,  i ,  j,  k );
init_TRUTHConvolution_RegionsHists_MCShifted_PlaylistCombined(Full_Empty,"",   TFile_Map_Full_MC,   StartingPlaylist_Full,  i ,  j,  k );
init_TRUTHConvolution_RegionsHists_MCShifted_PlaylistCombined(Empty, "",       TFile_Map_Empty_MC,  StartingPlaylist_Empty,  i ,  j,  k );

POTscale_MC_Convoluted_Regions(Full,        Full.POT_MC, 0);
POTscale_MC_Convoluted_Regions(Full_Empty , Full.POT_MC, 0);
POTscale_MC_Convoluted_Regions(Empty,      Empty.POT_MC, 0);

Subtract_TRUEConvolutionHists_Regions(Full_Empty , Empty, 0);

}


void Convolution_Tool::init_RECOConvolutionHist_MCShifted_PlaylistCombined(Convolution_hist& input, std::string ExtraString, ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist, int i, int j, int k )
{
  std::string string_i = std::to_string(i);
  std::string string_j = std::to_string(j);
  std::string string_k = std::to_string(k);
  std::string var;

  var = input.TRUE_Convoluted_name + ExtraString  + "_i_j_k_" + string_i + "_" +  string_j + "_" + string_k;
  Playlist_MnvH1D_Map  Convolution_toData_Map_1 =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
  input.MnvH1D_mc_Convoluted[1] =  Combine_Hists_fromMAP(Convolution_toData_Map_1 , StartingPlaylist ,"Convolution_toData_1");


}


void Convolution_Tool::init_DataConvolutionHists(TFile *inputfile, Convolution_hist& input, std::string Histname){
  input.MnvH1D_data = Get1DHist(*inputfile, Histname );
}


void Convolution_Tool::init_MaterialType(TFile *inputfile, Convolution_hist& input,int ind, std::string histname){
std::string name;

name = histname + "_Helium";
input.MnvH1D_mc_Convoluted_Helium[ind] = Get1DHist(*inputfile, name );
name = histname + "_Aluminium";
input.MnvH1D_mc_Convoluted_Aluminium[ind] = Get1DHist(*inputfile, name );
name = histname + "_Carbon";
input.MnvH1D_mc_Convoluted_Carbon[ind] = Get1DHist(*inputfile, name );
name = histname + "_Iron";
input.MnvH1D_mc_Convoluted_Iron[ind] = Get1DHist(*inputfile, name );
name = histname + "_Lead";
input.MnvH1D_mc_Convoluted_Lead[ind] = Get1DHist(*inputfile, name );
name = histname + "_Other";
input.MnvH1D_mc_Convoluted_Other[ind] = Get1DHist(*inputfile, name );

}



void Convolution_Tool::init_MaterialType_Regions(TFile *inputfile, Convolution_CryoRegions &input,int ind, std::string histname){

std::string var_name;

var_name = histname + "Upstream_Convoluted";
init_MaterialType(inputfile, input.Upstream, ind , var_name);
var_name = histname + "Barrel_Convoluted";
init_MaterialType(inputfile, input.Barrel, ind , var_name);
var_name = histname + "Downstream_Convoluted";
init_MaterialType(inputfile, input.Downstream, ind , var_name);
var_name = histname + "Concave_Convoluted";
init_MaterialType(inputfile, input.Concave, ind , var_name);

}

void Convolution_Tool::init_DataType_Regions(TFile *inputfile, Convolution_CryoRegions &input, std::string histname){
std::string var;
var = histname + "Upstream";
init_DataConvolutionHists(inputfile, input.Upstream , var);
var = histname + "Barrel";
init_DataConvolutionHists(inputfile, input.Barrel , var);
var = histname + "Downstream";
init_DataConvolutionHists(inputfile, input.Downstream , var);
var = histname + "Concave";
init_DataConvolutionHists(inputfile, input.Concave , var);


}







void Convolution_Tool::init_RECOConvolutionHist_MCShifted_PlaylistCombined(Convolution_hist& input, std::string ExtraString, ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist, int i, int j, int k, int m )
{
  std::string string_i = std::to_string(i);
  std::string string_j = std::to_string(j);
  std::string string_k = std::to_string(k);
  std::string string_m = std::to_string(m);
  std::string var;

  var = input.TRUE_Convoluted_name + ExtraString  + "_i_j_k_m_" + string_i + "_" +  string_j + "_" + string_k + "_" + string_m ;
  Playlist_MnvH1D_Map  Convolution_toData_Map_1 =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
  input.MnvH1D_mc_Convoluted[1] =  Combine_Hists_fromMAP(Convolution_toData_Map_1 , StartingPlaylist ,"Convolution_toData_1");

}


void Convolution_Tool::init_RECOConvolution_MaterialHist_MCShifted_PlaylistCombined(Convolution_hist& input, std::string ExtraString, ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist, int i, int j, int k )
{
  std::string string_i = std::to_string(i);
  std::string string_j = std::to_string(j);
  std::string string_k = std::to_string(k);
  std::string var;

  var = input.Reco_Material_name + ExtraString  + "_i_j_k_" + string_i + "_" +  string_j + "_" + string_k + "_Helium";
  //std::cout<<"Initizing hist name : "<< var<<std::endl;
  Playlist_MnvH1D_Map  Convolution_toData_Helium =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
  input.MnvH1D_mc_Convoluted_Helium[0] =  Combine_Hists_fromMAP(Convolution_toData_Helium , StartingPlaylist ,"Convolution_toData_Helium");

  var = input.Reco_Material_name + ExtraString  + "_i_j_k_" + string_i + "_" +  string_j + "_" + string_k + "_Aluminium";
  //std::cout<<"Initizing hist name : "<< var<<std::endl;
  Playlist_MnvH1D_Map  Convolution_toData_Aluminium =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
  input.MnvH1D_mc_Convoluted_Aluminium[0] =  Combine_Hists_fromMAP(Convolution_toData_Aluminium , StartingPlaylist ,"Convolution_toData_Aluminium");

  var = input.Reco_Material_name + ExtraString  + "_i_j_k_" + string_i + "_" +  string_j + "_" + string_k + "_Carbon";
  //std::cout<<"Initizing hist name : "<< var<<std::endl;
  Playlist_MnvH1D_Map  Convolution_toData_Carbon =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
  input.MnvH1D_mc_Convoluted_Carbon[0] =  Combine_Hists_fromMAP(Convolution_toData_Carbon , StartingPlaylist ,"Convolution_toData_Carbon");

  var = input.Reco_Material_name + ExtraString  + "_i_j_k_" + string_i + "_" +  string_j + "_" + string_k + "_Iron";
  //std::cout<<"Initizing hist name : "<< var<<std::endl;
  Playlist_MnvH1D_Map  Convolution_toData_Iron =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
  input.MnvH1D_mc_Convoluted_Iron[0] =  Combine_Hists_fromMAP(Convolution_toData_Iron , StartingPlaylist ,"Convolution_toData_Iron");

  var = input.Reco_Material_name + ExtraString  + "_i_j_k_" + string_i + "_" +  string_j + "_" + string_k + "_Lead";
  //std::cout<<"Initizing hist name : "<< var<<std::endl;
  Playlist_MnvH1D_Map  Convolution_toData_Lead =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
  input.MnvH1D_mc_Convoluted_Lead[0] =  Combine_Hists_fromMAP(Convolution_toData_Lead , StartingPlaylist ,"Convolution_toData_Lead");

  var = input.Reco_Material_name + ExtraString  + "_i_j_k_" + string_i + "_" +  string_j + "_" + string_k + "_Other";
  //std::cout<<"Initizing hist name : "<< var<<std::endl;
  Playlist_MnvH1D_Map  Convolution_toData_Other =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
  input.MnvH1D_mc_Convoluted_Other[0] =  Combine_Hists_fromMAP(Convolution_toData_Other , StartingPlaylist ,"Convolution_toData_Other");





}


void Convolution_Tool::init_RECOConvolution_MaterialHist_MCShifted_PlaylistCombined(Convolution_hist& input, std::string ExtraString, ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist, int i, int j, int k, int m )
{
  std::string string_i = std::to_string(i);
  std::string string_j = std::to_string(j);
  std::string string_k = std::to_string(k);
  std::string string_m = std::to_string(m);
  std::string var;

  var = input.Reco_Material_name + ExtraString  + "_i_j_k_m_" + string_i + "_" +  string_j + "_" + string_k + "_" + string_m + "_Helium";
  Playlist_MnvH1D_Map  Convolution_toData_Helium =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
  input.MnvH1D_mc_Convoluted_Helium[0] =  Combine_Hists_fromMAP(Convolution_toData_Helium , StartingPlaylist ,"Convolution_toData_Helium");

  var = input.Reco_Material_name + ExtraString  + "_i_j_k_m_" + string_i + "_" +  string_j + "_" + string_k + "_" + string_m +"_Aluminium";
  Playlist_MnvH1D_Map  Convolution_toData_Aluminium =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
  input.MnvH1D_mc_Convoluted_Aluminium[0] =  Combine_Hists_fromMAP(Convolution_toData_Aluminium , StartingPlaylist ,"Convolution_toData_Aluminium");

  var = input.Reco_Material_name + ExtraString  + "_i_j_k_m_" + string_i + "_" +  string_j + "_" + string_k + "_" + string_m + "_Carbon";
  Playlist_MnvH1D_Map  Convolution_toData_Carbon =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
  input.MnvH1D_mc_Convoluted_Carbon[0] =  Combine_Hists_fromMAP(Convolution_toData_Carbon , StartingPlaylist ,"Convolution_toData_Carbon");

  var = input.Reco_Material_name + ExtraString  + "_i_j_k_m_" + string_i + "_" +  string_j + "_" + string_k + "_" + string_m +"_Iron";
  Playlist_MnvH1D_Map  Convolution_toData_Iron =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
  input.MnvH1D_mc_Convoluted_Iron[0] =  Combine_Hists_fromMAP(Convolution_toData_Iron , StartingPlaylist ,"Convolution_toData_Iron");

  var = input.Reco_Material_name + ExtraString  + "_i_j_k_m_" + string_i + "_" +  string_j + "_" + string_k + "_" + string_m +"_Lead";
  Playlist_MnvH1D_Map  Convolution_toData_Lead =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
  input.MnvH1D_mc_Convoluted_Lead[0] =  Combine_Hists_fromMAP(Convolution_toData_Lead , StartingPlaylist ,"Convolution_toData_Lead");

  var = input.Reco_Material_name + ExtraString  + "_i_j_k_m_" + string_i + "_" +  string_j + "_" + string_k + "_" + string_m + "_Other";
  Playlist_MnvH1D_Map  Convolution_toData_Other =  Constuct_mvnH1DMap_FromME_playlist_TFileMAP(TFile_Map_MC, var );
  input.MnvH1D_mc_Convoluted_Other[0] =  Combine_Hists_fromMAP(Convolution_toData_Other , StartingPlaylist ,"Convolution_toData_Other");

  Convolution_toData_Helium.clear();
  Convolution_toData_Aluminium.clear();
  Convolution_toData_Carbon.clear();
  Convolution_toData_Iron.clear();
  Convolution_toData_Lead.clear();
  Convolution_toData_Other.clear();


}



void Convolution_Tool::init_MaterialConvolutionForPlotting(TFile *inputTFile, Convolution_hist& input, std::string inputname ,std::string Region, bool fullorempty, bool isinit,  int rank, int i, int j, int k , bool isFiducial )
{

  std::string varFinal;
  std::string varName = constuctString_forHist(inputname,  isinit,   fullorempty, rank,  i, j, k, isFiducial);
  varFinal = varName + Region + "_Helium";
  input.MnvH1D_mc_Convoluted_Helium[0] = Get1DHist(*inputTFile, varFinal );
  varFinal = varName + Region + "_Aluminium";
  input.MnvH1D_mc_Convoluted_Aluminium[0] = Get1DHist(*inputTFile, varFinal );
  varFinal = varName + Region + "_Carbon";
  input.MnvH1D_mc_Convoluted_Carbon[0] = Get1DHist(*inputTFile, varFinal );
  varFinal = varName + Region + "_Iron";
  input.MnvH1D_mc_Convoluted_Iron[0] =  Get1DHist(*inputTFile, varFinal );
  varFinal = varName + Region + "_Lead";
  input.MnvH1D_mc_Convoluted_Lead[0] =  Get1DHist(*inputTFile, varFinal );
  varFinal = varName + Region + "_Other";
  input.MnvH1D_mc_Convoluted_Other[0] =  Get1DHist(*inputTFile, varFinal );

}

void Convolution_Tool::init_DataConvolutionForPlotting(TFile *inputTFile, Convolution_hist& input, std::string inputname ,std::string Region, bool fullorempty, bool isinit,  int rank, int i, int j, int k , bool isFiducial )
{
  std::string varFinal;
  std::string varName = constuctString_forHist(inputname,  isinit,   fullorempty, rank,  i, j, k, isFiducial);
  varFinal = varName + Region + "_Data";
   input.MnvH1D_data  = Get1DHist(*inputTFile, varFinal );

}




void Convolution_Tool::init_RECOConvolution_Material_Regions_PlaylistCombined(Convolution_CryoRegions& input, std::string ExtraString, ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist , int i, int j, int k)
{
  init_RECOConvolution_MaterialHist_MCShifted_PlaylistCombined(input.Upstream,   ExtraString, TFile_Map_MC, StartingPlaylist, i,  j,  k);
  init_RECOConvolution_MaterialHist_MCShifted_PlaylistCombined(input.Barrel,     ExtraString, TFile_Map_MC, StartingPlaylist, i,  j,  k);
  init_RECOConvolution_MaterialHist_MCShifted_PlaylistCombined(input.Downstream, ExtraString, TFile_Map_MC, StartingPlaylist, i,  j,  k);
  init_RECOConvolution_MaterialHist_MCShifted_PlaylistCombined(input.Concave,    ExtraString, TFile_Map_MC, StartingPlaylist, i,  j,  k);
}


void Convolution_Tool::init_RECOConvolution_Material_Regions_PlaylistCombined(Convolution_CryoRegions& input, std::string ExtraString, ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist , int i, int j, int k, int m)
{
  init_RECOConvolution_MaterialHist_MCShifted_PlaylistCombined(input.Upstream,   ExtraString, TFile_Map_MC, StartingPlaylist, i,  j,  k, m);
  init_RECOConvolution_MaterialHist_MCShifted_PlaylistCombined(input.Barrel,     ExtraString, TFile_Map_MC, StartingPlaylist, i,  j,  k, m);
  init_RECOConvolution_MaterialHist_MCShifted_PlaylistCombined(input.Downstream, ExtraString, TFile_Map_MC, StartingPlaylist, i,  j,  k, m);
  init_RECOConvolution_MaterialHist_MCShifted_PlaylistCombined(input.Concave,    ExtraString, TFile_Map_MC, StartingPlaylist, i,  j,  k, m);
}

void Convolution_Tool::init_ConvolutionREGIONSForPlotting(TFile *inputTFile, Convolution_CryoRegions& Regioninput, std::string inputname , bool fullorempty, bool isinit,  int rank, int i, int j, int k, bool isFiducial)
{
  init_MaterialConvolutionForPlotting(inputTFile, Regioninput.Upstream,   inputname, "Upstream",   fullorempty,  isinit,   rank,  i,  j,  k, isFiducial);
  init_MaterialConvolutionForPlotting(inputTFile, Regioninput.Barrel,     inputname, "Barrel",     fullorempty,  isinit,   rank,  i,  j,  k, isFiducial);
  init_MaterialConvolutionForPlotting(inputTFile, Regioninput.Downstream, inputname, "Downstream", fullorempty,  isinit,   rank,  i,  j,  k, isFiducial);
  init_MaterialConvolutionForPlotting(inputTFile, Regioninput.Concave,    inputname, "Concave",    fullorempty,  isinit,   rank,  i,  j,  k, isFiducial);
}

void Convolution_Tool::init_Data_Regions_Plotting(TFile *inputTFile, Convolution_CryoRegions& input,  std::string inputname , bool fullorempty, bool isinit,  int rank, int i, int j, int k, bool isFiducial)
{
  init_DataConvolutionForPlotting(inputTFile, input.Upstream,     inputname, "Upstream",     fullorempty,  isinit,   rank,  i,  j,  k ,isFiducial);
  init_DataConvolutionForPlotting(inputTFile, input.Barrel,       inputname, "Barrel",       fullorempty,  isinit,   rank,  i,  j,  k ,isFiducial);
  init_DataConvolutionForPlotting(inputTFile, input.Downstream,   inputname, "Downstream",   fullorempty,  isinit,   rank,  i,  j,  k ,isFiducial);
  init_DataConvolutionForPlotting(inputTFile, input.Concave,      inputname, "Concave",      fullorempty,  isinit,   rank,  i,  j,  k ,isFiducial);

}


void Convolution_Tool::init_ConvolutionREGIONSForVertexPostionsPlotting(TFile *inputTFile, ConvolutionShiftMap &input, bool fullorempty, bool isinit,  int rank, int i, int j, int k, bool isFiducial )
{
init_ConvolutionREGIONSForPlotting(inputTFile, input.Vertex_X_Regions, "Vertex_X" , fullorempty, isinit,   rank,  i,  j,  k, isFiducial);
init_ConvolutionREGIONSForPlotting(inputTFile, input.Vertex_Y_Regions, "Vertex_Y" , fullorempty, isinit,   rank,  i,  j,  k, isFiducial);
init_ConvolutionREGIONSForPlotting(inputTFile, input.Vertex_Z_Regions, "Vertex_Z" , fullorempty, isinit,   rank,  i,  j,  k, isFiducial);
init_ConvolutionREGIONSForPlotting(inputTFile, input.Vertex_R_Regions, "Vertex_R" , fullorempty, isinit,   rank,  i,  j,  k, isFiducial);
}

void Convolution_Tool::init_ConvolutionREGIONSForVertexPostionsPlotting_Fiducial(TFile *inputTFile, ConvolutionShiftMap &input, bool fullorempty, bool isinit,  int rank, int i, int j, int k)
{
init_ConvolutionREGIONSForVertexPostionsPlotting(inputTFile, input,  fullorempty,  isinit,   rank,  i,  j,  k,  true );
}

void Convolution_Tool::init_Data_Vertex_Plotting(TFile *inputTFile, ConvolutionShiftMap &input, bool fullorempty, bool isinit,  int rank, int i, int j, int k)
{
init_Data_Regions_Plotting(inputTFile,  input.Vertex_X_Regions,  "Vertex_X" ,  fullorempty,  isinit,  rank,  i,  j,  k);
init_Data_Regions_Plotting(inputTFile,  input.Vertex_Y_Regions,  "Vertex_Y" ,  fullorempty,  isinit,  rank,  i,  j,  k);
init_Data_Regions_Plotting(inputTFile,  input.Vertex_Z_Regions,  "Vertex_Z" ,  fullorempty,  isinit,  rank,  i,  j,  k);
init_Data_Regions_Plotting(inputTFile,  input.Vertex_R_Regions,  "Vertex_R" ,  fullorempty,  isinit,  rank,  i,  j,  k);

init_Data_Regions_Plotting(inputTFile,  input.Vertex_TRUE_X_Regions,  "Vertex_X" ,  fullorempty,  isinit,  rank,  i,  j,  k);
init_Data_Regions_Plotting(inputTFile,  input.Vertex_TRUE_Y_Regions,  "Vertex_Y" ,  fullorempty,  isinit,  rank,  i,  j,  k);
init_Data_Regions_Plotting(inputTFile,  input.Vertex_TRUE_Z_Regions,  "Vertex_Z" ,  fullorempty,  isinit,  rank,  i,  j,  k);
init_Data_Regions_Plotting(inputTFile,  input.Vertex_TRUE_R_Regions,  "Vertex_R" ,  fullorempty,  isinit,  rank,  i,  j,  k);
}

void Convolution_Tool::init_Data_Vertex_Plotting_Fiducial(TFile *inputTFile, ConvolutionShiftMap &input, bool fullorempty, bool isinit,  int rank, int i, int j, int k)
{
init_Data_Regions_Plotting(inputTFile,  input.Vertex_X_Regions,  "Vertex_X" ,  fullorempty,  isinit,  rank,  i,  j,  k, true);
init_Data_Regions_Plotting(inputTFile,  input.Vertex_Y_Regions,  "Vertex_Y" ,  fullorempty,  isinit,  rank,  i,  j,  k, true);
init_Data_Regions_Plotting(inputTFile,  input.Vertex_Z_Regions,  "Vertex_Z" ,  fullorempty,  isinit,  rank,  i,  j,  k, true);
init_Data_Regions_Plotting(inputTFile,  input.Vertex_R_Regions,  "Vertex_R" ,  fullorempty,  isinit,  rank,  i,  j,  k, true);

init_Data_Regions_Plotting(inputTFile,  input.Vertex_TRUE_X_Regions,  "Vertex_X" ,  fullorempty,  isinit,  rank,  i,  j,  k, true);
init_Data_Regions_Plotting(inputTFile,  input.Vertex_TRUE_Y_Regions,  "Vertex_Y" ,  fullorempty,  isinit,  rank,  i,  j,  k, true);
init_Data_Regions_Plotting(inputTFile,  input.Vertex_TRUE_Z_Regions,  "Vertex_Z" ,  fullorempty,  isinit,  rank,  i,  j,  k, true);
init_Data_Regions_Plotting(inputTFile,  input.Vertex_TRUE_R_Regions,  "Vertex_R" ,  fullorempty,  isinit,  rank,  i,  j,  k, true);
}



void Convolution_Tool::init_ConvolutionREGIONSForTRUEVertexPostionsPlotting(TFile *inputTFile, ConvolutionShiftMap &input, bool fullorempty, bool isinit,  int rank, int i, int j, int k)
{
init_ConvolutionREGIONSForPlotting(inputTFile, input.Vertex_TRUE_X_Regions, "TRUE_Vertex_X" , fullorempty, isinit,   rank,  i,  j,  k);
init_ConvolutionREGIONSForPlotting(inputTFile, input.Vertex_TRUE_Y_Regions, "TRUE_Vertex_Y" , fullorempty, isinit,   rank,  i,  j,  k);
init_ConvolutionREGIONSForPlotting(inputTFile, input.Vertex_TRUE_Z_Regions, "TRUE_Vertex_Z" , fullorempty, isinit,   rank,  i,  j,  k);
init_ConvolutionREGIONSForPlotting(inputTFile, input.Vertex_TRUE_R_Regions, "TRUE_Vertex_R" , fullorempty, isinit,   rank,  i,  j,  k);
}


void Convolution_Tool::init_ConvolutionREGIONSForTRUEVertexPostionsPlotting_Fiducial(TFile *inputTFile, ConvolutionShiftMap &input, bool fullorempty, bool isinit,  int rank, int i, int j, int k)
{
init_ConvolutionREGIONSForPlotting(inputTFile, input.Vertex_TRUE_X_Regions, "TRUE_Vertex_X" , fullorempty, isinit,   rank,  i,  j,  k, true);
init_ConvolutionREGIONSForPlotting(inputTFile, input.Vertex_TRUE_Y_Regions, "TRUE_Vertex_Y" , fullorempty, isinit,   rank,  i,  j,  k, true);
init_ConvolutionREGIONSForPlotting(inputTFile, input.Vertex_TRUE_Z_Regions, "TRUE_Vertex_Z" , fullorempty, isinit,   rank,  i,  j,  k, true);
init_ConvolutionREGIONSForPlotting(inputTFile, input.Vertex_TRUE_R_Regions, "TRUE_Vertex_R" , fullorempty, isinit,   rank,  i,  j,  k, true);
}

void Convolution_Tool::init_ConvolutionREGIONSForVarsPlotting(TFile *inputTFile, ConvolutionShiftMap &input, bool fullorempty, bool isinit,  int rank, int i, int j, int k)
{

init_ConvolutionREGIONSForPlotting(inputTFile, input.muonPT_Regions     , "muonPT"            , fullorempty, isinit,   rank,  i,  j,  k);
init_ConvolutionREGIONSForPlotting(inputTFile, input.muonPZ_Regions     , "muonPZ"            , fullorempty, isinit,   rank,  i,  j,  k);
init_ConvolutionREGIONSForPlotting(inputTFile, input.muonE_Regions      , "muonE"             , fullorempty, isinit,   rank,  i,  j,  k);
init_ConvolutionREGIONSForPlotting(inputTFile, input.muontheta_Regions  , "muontheta"         , fullorempty, isinit,   rank,  i,  j,  k);
init_ConvolutionREGIONSForPlotting(inputTFile, input.muonDOCA_Regions   , "muondoca"          , fullorempty, isinit,   rank,  i,  j,  k);
init_ConvolutionREGIONSForPlotting(inputTFile, input.NearestWall_Regions, "nearestwall"       , fullorempty, isinit,   rank,  i,  j,  k);
init_ConvolutionREGIONSForPlotting(inputTFile, input.recoilDOCA_Regions , "recoildoca"        , fullorempty, isinit,   rank,  i,  j,  k);
init_ConvolutionREGIONSForPlotting(inputTFile, input.recoilAngle_Regions, "recoilangle"       , fullorempty, isinit,   rank,  i,  j,  k);
init_ConvolutionREGIONSForPlotting(inputTFile, input.tracklength_Regions, "recoiltracklength" , fullorempty, isinit,   rank,  i,  j,  k);


}

void Convolution_Tool::init_ConvolutionREGIONSForVarsPlotting_Fiducial(TFile *inputTFile, ConvolutionShiftMap &input, bool fullorempty, bool isinit,  int rank, int i, int j, int k)
{

init_ConvolutionREGIONSForPlotting(inputTFile, input.muonPT_Regions     , "muonPT"            , fullorempty, isinit,   rank,  i,  j,  k, true);
init_ConvolutionREGIONSForPlotting(inputTFile, input.muonPZ_Regions     , "muonPZ"            , fullorempty, isinit,   rank,  i,  j,  k, true);
init_ConvolutionREGIONSForPlotting(inputTFile, input.muonE_Regions      , "muonE"             , fullorempty, isinit,   rank,  i,  j,  k, true);
init_ConvolutionREGIONSForPlotting(inputTFile, input.muontheta_Regions  , "muontheta"         , fullorempty, isinit,   rank,  i,  j,  k, true);
init_ConvolutionREGIONSForPlotting(inputTFile, input.muonDOCA_Regions   , "muondoca"          , fullorempty, isinit,   rank,  i,  j,  k, true);
init_ConvolutionREGIONSForPlotting(inputTFile, input.NearestWall_Regions, "nearestwall"       , fullorempty, isinit,   rank,  i,  j,  k, true);
init_ConvolutionREGIONSForPlotting(inputTFile, input.recoilDOCA_Regions , "recoildoca"        , fullorempty, isinit,   rank,  i,  j,  k, true);
init_ConvolutionREGIONSForPlotting(inputTFile, input.recoilAngle_Regions, "recoilangle"       , fullorempty, isinit,   rank,  i,  j,  k, true);
init_ConvolutionREGIONSForPlotting(inputTFile, input.tracklength_Regions, "recoiltracklength" , fullorempty, isinit,   rank,  i,  j,  k, true);


}


void Convolution_Tool::init_Data_var_Plotting(TFile *inputTFile, ConvolutionShiftMap &input, bool fullorempty, bool isinit,  int rank, int i, int j, int k)
{

init_Data_Regions_Plotting(inputTFile,input.muonPT_Regions ,      "muonPT",            fullorempty,  isinit,  rank,  i,  j,  k);
init_Data_Regions_Plotting(inputTFile,input.muonPZ_Regions ,      "muonPZ",            fullorempty,  isinit,  rank,  i,  j,  k);
init_Data_Regions_Plotting(inputTFile,input.muonE_Regions ,       "muonE",             fullorempty,  isinit,  rank,  i,  j,  k);
init_Data_Regions_Plotting(inputTFile,input.muontheta_Regions ,   "muontheta",         fullorempty,  isinit,  rank,  i,  j,  k);
init_Data_Regions_Plotting(inputTFile,input.muonDOCA_Regions ,    "muondoca",          fullorempty,  isinit,  rank,  i,  j,  k);
init_Data_Regions_Plotting(inputTFile,input.NearestWall_Regions , "nearestwall",       fullorempty,  isinit,  rank,  i,  j,  k);
init_Data_Regions_Plotting(inputTFile,input.recoilDOCA_Regions ,  "recoildoca",        fullorempty,  isinit,  rank,  i,  j,  k);
init_Data_Regions_Plotting(inputTFile,input.recoilAngle_Regions , "recoilangle",       fullorempty,  isinit,  rank,  i,  j,  k);
init_Data_Regions_Plotting(inputTFile,input.tracklength_Regions , "recoiltracklength", fullorempty,  isinit,  rank,  i,  j,  k);

}


void Convolution_Tool::init_Data_var_Plotting_Fiducial(TFile *inputTFile, ConvolutionShiftMap &input, bool fullorempty, bool isinit,  int rank, int i, int j, int k)
{

init_Data_Regions_Plotting(inputTFile,input.muonPT_Regions ,      "muonPT",            fullorempty,  isinit,  rank,  i,  j,  k, true);
init_Data_Regions_Plotting(inputTFile,input.muonPZ_Regions ,      "muonPZ",            fullorempty,  isinit,  rank,  i,  j,  k, true);
init_Data_Regions_Plotting(inputTFile,input.muonE_Regions ,       "muonE",             fullorempty,  isinit,  rank,  i,  j,  k, true);
init_Data_Regions_Plotting(inputTFile,input.muontheta_Regions ,   "muontheta",         fullorempty,  isinit,  rank,  i,  j,  k, true);
init_Data_Regions_Plotting(inputTFile,input.muonDOCA_Regions ,    "muondoca",          fullorempty,  isinit,  rank,  i,  j,  k, true);
init_Data_Regions_Plotting(inputTFile,input.NearestWall_Regions , "nearestwall",       fullorempty,  isinit,  rank,  i,  j,  k, true);
init_Data_Regions_Plotting(inputTFile,input.recoilDOCA_Regions ,  "recoildoca",        fullorempty,  isinit,  rank,  i,  j,  k, true);
init_Data_Regions_Plotting(inputTFile,input.recoilAngle_Regions , "recoilangle",       fullorempty,  isinit,  rank,  i,  j,  k, true);
init_Data_Regions_Plotting(inputTFile,input.tracklength_Regions , "recoiltracklength", fullorempty,  isinit,  rank,  i,  j,  k, true);

}


void Convolution_Tool::init_Full_Plotting_PlaylistCombined(bool isinit,  int rank, int i, int j, int k){
init_ConvolutionREGIONSForVertexPostionsPlotting(InputFull_Plotting, Full, true ,  isinit,   rank, i, j, k);
init_ConvolutionREGIONSForVarsPlotting(InputFull_Plotting, Full, true ,  isinit,   rank, i, j, k);
init_ConvolutionREGIONSForTRUEVertexPostionsPlotting(InputFull_Plotting, Full, true ,  isinit,   rank, i, j, k);
init_Data_var_Plotting(InputFull_Plotting, Full, true ,  isinit,   rank, i, j, k);
init_Data_Vertex_Plotting(InputFull_Plotting, Full, true ,  isinit,   rank, i, j, k);
}





void Convolution_Tool::init_Full_Plotting_PlaylistCombined_Fiducial(bool isinit,  int rank, int i, int j, int k){

init_ConvolutionREGIONSForVertexPostionsPlotting_Fiducial(    InputFull_Plotting,     Full_Fid, true ,  isinit,   rank, i, j, k);
init_ConvolutionREGIONSForVarsPlotting_Fiducial(              InputFull_Plotting,     Full_Fid, true ,  isinit,   rank, i, j, k);
init_ConvolutionREGIONSForTRUEVertexPostionsPlotting_Fiducial(InputFull_Plotting,     Full_Fid, true ,  isinit,   rank, i, j, k);
init_Data_var_Plotting_Fiducial(                              InputFull_Plotting,     Full_Fid, true ,  isinit,   rank, i, j, k);
init_Data_Vertex_Plotting_Fiducial(                           InputFull_Plotting,     Full_Fid, true ,  isinit,   rank, i, j, k);

}


void Convolution_Tool::init_Empty_Plotting_PlaylistCombined(bool isinit,  int rank, int i, int j, int k){
init_ConvolutionREGIONSForVertexPostionsPlotting(InputEmpty_Plotting, Empty,     false ,  isinit,   rank, i, j, k);
init_ConvolutionREGIONSForVarsPlotting(InputEmpty_Plotting, Empty,               false ,  isinit,   rank, i, j, k);
init_ConvolutionREGIONSForTRUEVertexPostionsPlotting(InputEmpty_Plotting, Empty, false ,  isinit,   rank, i, j, k);
init_Data_var_Plotting(InputEmpty_Plotting, Empty,                               false ,  isinit,   rank, i, j, k);
init_Data_Vertex_Plotting(InputEmpty_Plotting, Empty,                            false ,  isinit,   rank, i, j, k);
}


void Convolution_Tool::init_Empty_Plotting_PlaylistCombined_Fiducial(bool isinit,  int rank, int i, int j, int k){
init_ConvolutionREGIONSForVertexPostionsPlotting_Fiducial(InputEmpty_Plotting, Empty_Fid, false ,  isinit,   rank, i, j, k);
init_ConvolutionREGIONSForVarsPlotting_Fiducial(InputEmpty_Plotting, Empty_Fid, false ,  isinit,   rank, i, j, k);
init_ConvolutionREGIONSForTRUEVertexPostionsPlotting_Fiducial(InputEmpty_Plotting, Empty_Fid, false ,  isinit,   rank, i, j, k);

init_Data_var_Plotting_Fiducial(InputEmpty_Plotting, Empty_Fid, false ,  isinit,   rank, i, j, k);
init_Data_Vertex_Plotting_Fiducial(InputEmpty_Plotting, Empty_Fid, false ,  isinit,   rank, i, j, k);
}


void Convolution_Tool::init_RECOConvolution_Material_Regions_PlaylistCombined(ConvolutionShiftMap &input, std::string ExtraString, ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist, int i, int j, int k ){

  init_RECOConvolution_Material_Regions_PlaylistCombined(input.Vertex_X_Regions,"", TFile_Map_MC, StartingPlaylist, i, j, k);
  init_RECOConvolution_Material_Regions_PlaylistCombined(input.Vertex_Y_Regions,"", TFile_Map_MC, StartingPlaylist, i, j, k);
  init_RECOConvolution_Material_Regions_PlaylistCombined(input.Vertex_Z_Regions,"", TFile_Map_MC, StartingPlaylist, i, j, k);
  init_RECOConvolution_Material_Regions_PlaylistCombined(input.Vertex_R_Regions,"", TFile_Map_MC, StartingPlaylist, i, j, k);

}


void Convolution_Tool::init_RECOConvolution_Material_Regions_PlaylistCombined_TRUE_vertex(ConvolutionShiftMap &input, std::string ExtraString, ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist, int i, int j, int k ){

  init_RECOConvolution_Material_Regions_PlaylistCombined(input.Vertex_TRUE_X_Regions,"", TFile_Map_MC, StartingPlaylist, i, j, k);
  init_RECOConvolution_Material_Regions_PlaylistCombined(input.Vertex_TRUE_Y_Regions,"", TFile_Map_MC, StartingPlaylist, i, j, k);
  init_RECOConvolution_Material_Regions_PlaylistCombined(input.Vertex_TRUE_Z_Regions,"", TFile_Map_MC, StartingPlaylist, i, j, k);
  init_RECOConvolution_Material_Regions_PlaylistCombined(input.Vertex_TRUE_R_Regions,"", TFile_Map_MC, StartingPlaylist, i, j, k);

}


void Convolution_Tool::init_RECOConvolution_Material_Regions_PlaylistCombined_nonVertexVars(ConvolutionShiftMap &input, std::string ExtraString, ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist, int i, int j, int k ){

  init_RECOConvolution_Material_Regions_PlaylistCombined(input.muonPT_Regions,     "", TFile_Map_MC, StartingPlaylist, i, j, k);
  init_RECOConvolution_Material_Regions_PlaylistCombined(input.muonPZ_Regions,     "", TFile_Map_MC, StartingPlaylist, i, j, k);
  init_RECOConvolution_Material_Regions_PlaylistCombined(input.muonE_Regions,      "", TFile_Map_MC, StartingPlaylist, i, j, k);
  init_RECOConvolution_Material_Regions_PlaylistCombined(input.muontheta_Regions,  "", TFile_Map_MC, StartingPlaylist, i, j, k);
  init_RECOConvolution_Material_Regions_PlaylistCombined(input.muonDOCA_Regions,   "", TFile_Map_MC, StartingPlaylist, i, j, k);
  init_RECOConvolution_Material_Regions_PlaylistCombined(input.NearestWall_Regions,"", TFile_Map_MC, StartingPlaylist, i, j, k);
  init_RECOConvolution_Material_Regions_PlaylistCombined(input.recoilDOCA_Regions, "", TFile_Map_MC, StartingPlaylist, i, j, k);
  init_RECOConvolution_Material_Regions_PlaylistCombined(input.recoilAngle_Regions,"", TFile_Map_MC, StartingPlaylist, i, j, k);
  init_RECOConvolution_Material_Regions_PlaylistCombined(input.tracklength_Regions,"", TFile_Map_MC, StartingPlaylist, i, j, k);


}


void Convolution_Tool::init_RECOConvolution_Material_Regions_PlaylistCombined(ConvolutionShiftMap &input, std::string ExtraString, ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist, int i, int j, int k , int m ){

  init_RECOConvolution_Material_Regions_PlaylistCombined(input.Vertex_X_Regions,"", TFile_Map_MC, StartingPlaylist, i, j, k, m);
  init_RECOConvolution_Material_Regions_PlaylistCombined(input.Vertex_Y_Regions,"", TFile_Map_MC, StartingPlaylist, i, j, k, m);
  init_RECOConvolution_Material_Regions_PlaylistCombined(input.Vertex_Z_Regions,"", TFile_Map_MC, StartingPlaylist, i, j, k, m);
  init_RECOConvolution_Material_Regions_PlaylistCombined(input.Vertex_R_Regions,"", TFile_Map_MC, StartingPlaylist, i, j, k, m);

}


void  Convolution_Tool::init_RECO_Convolution_Material_Regions_Hists_PlaylistCombinedMC(int i, int j, int k){
// Full
init_RECOConvolution_Material_Regions_PlaylistCombined(Full,  "",       TFile_Map_Full_MC,   StartingPlaylist_Full,  i ,  j,  k );
init_RECOConvolution_Material_Regions_PlaylistCombined(Full_Empty,"",   TFile_Map_Full_MC,   StartingPlaylist_Full,  i ,  j,  k );
init_RECOConvolution_Material_Regions_PlaylistCombined(Empty, "",       TFile_Map_Empty_MC,  StartingPlaylist_Empty, i ,  j,  k );

POTscale_MCReco_Material_Regions(Full ,       Full.POT_MC, 0);
POTscale_MCReco_Material_Regions(Full_Empty,  Full.POT_MC, 0);
POTscale_MCReco_Material_Regions(Empty,       Empty.POT_MC, 0);

Subtract_Convolution_Material_Hists_Regions(Full_Empty , Empty, 0);
}

void  Convolution_Tool::init_RECO_Convolution_Material_Regions_Hists_PlaylistCombinedMC(int i, int j, int k , int m){
// Full
init_RECOConvolution_Material_Regions_PlaylistCombined(Full,  "",       TFile_Map_Full_MC,   StartingPlaylist_Full,  i ,  j,  k, m );
init_RECOConvolution_Material_Regions_PlaylistCombined(Full_Empty,"",   TFile_Map_Full_MC,   StartingPlaylist_Full,  i ,  j,  k, m );
init_RECOConvolution_Material_Regions_PlaylistCombined(Empty, "",       TFile_Map_Empty_MC,  StartingPlaylist_Empty, i ,  j,  k, m );

POTscale_MCReco_Material_Regions(Full ,       Full.POT_MC, 0);
POTscale_MCReco_Material_Regions(Full_Empty,  Full.POT_MC, 0);
POTscale_MCReco_Material_Regions(Empty,       Empty.POT_MC, 0);

Subtract_Convolution_Material_Hists_Regions(Full_Empty , Empty, 0);
}



void  Convolution_Tool::initEMPTYONLY_RECO_Convolution_Material_Regions_Hists_PlaylistCombinedMC(int i, int j, int k){
//  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
//std::cout<<"initizing Empty Material Hist"<<std::endl;
//std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
init_RECOConvolution_Material_Regions_PlaylistCombined(Empty, "",       TFile_Map_Empty_MC,  StartingPlaylist_Empty, i ,  j,  k );
POTscale_MCReco_Material_Regions(Empty,       Empty.POT_MC, 0);
}

void  Convolution_Tool::initEMPTYONLY_RECO_Convolution_Material_Regions_Hists_PlaylistCombinedMC_Fiducial(int i, int j, int k){
//  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
//std::cout<<"initizing Empty Material Hist"<<std::endl;
//std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
init_RECOConvolution_Material_Regions_PlaylistCombined(Empty_Fid, "_Fiducial",       TFile_Map_Empty_MC,  StartingPlaylist_Empty, i ,  j,  k );
POTscale_MCReco_Material_Regions(Empty_Fid,       Empty.POT_MC, 0);
}

void  Convolution_Tool::initFULLONLY_RECO_Convolution_Material_Regions_Hists_PlaylistCombinedMC_Fiducial(int i, int j, int k){
//  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
//std::cout<<"initizing Empty Material Hist"<<std::endl;
//std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
init_RECOConvolution_Material_Regions_PlaylistCombined(Full_Fid, "_Fiducial",       TFile_Map_Full_MC,  StartingPlaylist_Full, i ,  j,  k );
POTscale_MCReco_Material_Regions(Full_Fid,       Full.POT_MC, 0);
}


void  Convolution_Tool::initEMPTYONLY_RECO_Convolution_Material_Regions_TRUEHists_PlaylistCombinedMC(int i, int j, int k){
//  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
//std::cout<<"initizing Empty Material Hist"<<std::endl;
//std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
init_RECOConvolution_Material_Regions_PlaylistCombined_TRUE_vertex(Empty, "",       TFile_Map_Empty_MC,  StartingPlaylist_Empty, i ,  j,  k );
POTscale_MCReco_Material_Regions_TRUEvertex(Empty,       Empty.POT_MC, 0);
}

void  Convolution_Tool::initEMPTYONLY_RECO_Convolution_Material_Regions_TRUEHists_PlaylistCombinedMC_Fiducial(int i, int j, int k){
//  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
//std::cout<<"initizing Empty Material Hist"<<std::endl;
//std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
init_RECOConvolution_Material_Regions_PlaylistCombined_TRUE_vertex(Empty_Fid, "_Fiducial",       TFile_Map_Empty_MC,  StartingPlaylist_Empty, i ,  j,  k );
POTscale_MCReco_Material_Regions_TRUEvertex(Empty_Fid,       Empty.POT_MC, 0);
}


void  Convolution_Tool::initEMPTYONLY_RECO_Convolution_Material_Regions_NON_vertex_varsHists_PlaylistCombinedMC(int i, int j, int k){
//  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
//std::cout<<"initizing Empty Material Hist"<<std::endl;
//std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
init_RECOConvolution_Material_Regions_PlaylistCombined_nonVertexVars(Empty, "",       TFile_Map_Empty_MC,  StartingPlaylist_Empty, i ,  j,  k );
POTscale_MCReco_Material_Regions_nonVertexVar(Empty,       Empty.POT_MC, 0);

}


void  Convolution_Tool::initEMPTYONLY_RECO_Convolution_Material_Regions_NON_vertex_varsHists_PlaylistCombinedMC_Fiducial(int i, int j, int k){
//  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
//std::cout<<"initizing Empty Material Hist"<<std::endl;
//std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
init_RECOConvolution_Material_Regions_PlaylistCombined_nonVertexVars(Empty_Fid, "_Fiducial",       TFile_Map_Empty_MC,  StartingPlaylist_Empty, i ,  j,  k );
POTscale_MCReco_Material_Regions_nonVertexVar(Empty_Fid,       Empty.POT_MC, 0);

}


void  Convolution_Tool::initEMPTYONLY_RECO_Convolution_Material_Regions_Hists_PlaylistCombinedMC(int i, int j, int k , int m){
//  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
//std::cout<<"initizing Empty Material Hist"<<std::endl;
//std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
init_RECOConvolution_Material_Regions_PlaylistCombined(Empty, "",       TFile_Map_Empty_MC,  StartingPlaylist_Empty, i ,  j,  k, m );
POTscale_MCReco_Material_Regions(Empty,       Empty.POT_MC, 0);
}

void  Convolution_Tool::initFULLONLY_RECO_Convolution_Material_Regions_Hists_PlaylistCombinedMC(int i, int j, int k){
//  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
//std::cout<<"initizing Empty Material Hist"<<std::endl;
//std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
init_RECOConvolution_Material_Regions_PlaylistCombined(Full, "",       TFile_Map_Full_MC,  StartingPlaylist_Full, i ,  j,  k );
POTscale_MCReco_Material_Regions(Full,       Full.POT_MC, 0);
}

void  Convolution_Tool::initFULLONLY_RECO_Convolution_Material_Regions_Hists_PlaylistCombinedMC(int i, int j, int k, int m){
//  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
//std::cout<<"initizing Empty Material Hist"<<std::endl;
//std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
init_RECOConvolution_Material_Regions_PlaylistCombined(Full, "",       TFile_Map_Full_MC,  StartingPlaylist_Full, i ,  j,  k, m );
POTscale_MCReco_Material_Regions(Full,       Full.POT_MC, 0);
}


void  Convolution_Tool::initFULLONLY_RECO_Convolution_Material_Regions_TRUEHists_PlaylistCombinedMC(int i, int j, int k){
//  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
//std::cout<<"initizing Empty Material Hist"<<std::endl;
//std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
init_RECOConvolution_Material_Regions_PlaylistCombined_TRUE_vertex(Full, "",       TFile_Map_Full_MC,  StartingPlaylist_Full, i ,  j,  k );
POTscale_MCReco_Material_Regions_TRUEvertex(Full,       Full.POT_MC, 0);
}

void  Convolution_Tool::initFULLONLY_RECO_Convolution_Material_Regions_TRUEHists_PlaylistCombinedMC_Fiducial(int i, int j, int k){
//  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
//std::cout<<"initizing Empty Material Hist"<<std::endl;
//std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
init_RECOConvolution_Material_Regions_PlaylistCombined_TRUE_vertex(Full_Fid, "_Fiducial",       TFile_Map_Full_MC,  StartingPlaylist_Full, i ,  j,  k );
POTscale_MCReco_Material_Regions_TRUEvertex(Full_Fid,       Full.POT_MC, 0);
}


void  Convolution_Tool::initFULLONLY_RECO_Convolution_Material_Regions_NON_vertex_varsHists_PlaylistCombinedMC(int i, int j, int k){
//  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
//std::cout<<"initizing Empty Material Hist"<<std::endl;
//std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
init_RECOConvolution_Material_Regions_PlaylistCombined_nonVertexVars(Full, "",       TFile_Map_Full_MC,  StartingPlaylist_Full, i ,  j,  k );
POTscale_MCReco_Material_Regions_nonVertexVar(Full,       Full.POT_MC, 0);
}

void  Convolution_Tool::initFULLONLY_RECO_Convolution_Material_Regions_NON_vertex_varsHists_PlaylistCombinedMC_Fiducial(int i, int j, int k){
//  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
//std::cout<<"initizing Empty Material Hist"<<std::endl;
//std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
init_RECOConvolution_Material_Regions_PlaylistCombined_nonVertexVars(Full_Fid, "_Fiducial",       TFile_Map_Full_MC,  StartingPlaylist_Full, i ,  j,  k );
POTscale_MCReco_Material_Regions_nonVertexVar(Full_Fid,       Full.POT_MC, 0);
}


void Convolution_Tool::init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(Convolution_CryoRegions& input, std::string ExtraString, ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist , int i, int j, int k)
{
  init_RECOConvolutionHist_MCShifted_PlaylistCombined(input.Upstream,   "", TFile_Map_MC, StartingPlaylist, i,  j,  k);
  init_RECOConvolutionHist_MCShifted_PlaylistCombined(input.Barrel,     "", TFile_Map_MC, StartingPlaylist, i,  j,  k);
  init_RECOConvolutionHist_MCShifted_PlaylistCombined(input.Downstream, "", TFile_Map_MC, StartingPlaylist, i,  j,  k);
  init_RECOConvolutionHist_MCShifted_PlaylistCombined(input.Concave,    "", TFile_Map_MC, StartingPlaylist, i,  j,  k);
}

void Convolution_Tool::init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(Convolution_CryoRegions& input, std::string ExtraString, ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist , int i, int j, int k, int m)
{
  init_RECOConvolutionHist_MCShifted_PlaylistCombined(input.Upstream,   "", TFile_Map_MC, StartingPlaylist, i,  j,  k, m);
  init_RECOConvolutionHist_MCShifted_PlaylistCombined(input.Barrel,     "", TFile_Map_MC, StartingPlaylist, i,  j,  k, m);
  init_RECOConvolutionHist_MCShifted_PlaylistCombined(input.Downstream, "", TFile_Map_MC, StartingPlaylist, i,  j,  k, m);
  init_RECOConvolutionHist_MCShifted_PlaylistCombined(input.Concave,    "", TFile_Map_MC, StartingPlaylist, i,  j,  k, m);
}




void Convolution_Tool::init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(Convolution_CryoRegions& input, std::string ExtraString, ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist, Index3 upstream, Index3 barrel,Index3 downstream,Index3 concave )
{
  init_RECOConvolutionHist_MCShifted_PlaylistCombined(input.Upstream,   "", TFile_Map_MC, StartingPlaylist, upstream.i,   upstream.j,    upstream.k);
  init_RECOConvolutionHist_MCShifted_PlaylistCombined(input.Barrel,     "", TFile_Map_MC, StartingPlaylist, barrel.i,     barrel.j,      barrel.k);
  init_RECOConvolutionHist_MCShifted_PlaylistCombined(input.Downstream, "", TFile_Map_MC, StartingPlaylist, downstream.i, downstream.j,  downstream.k);
  init_RECOConvolutionHist_MCShifted_PlaylistCombined(input.Concave,    "", TFile_Map_MC, StartingPlaylist, concave.i,    concave.j,     concave.k);
}






void Convolution_Tool::init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(ConvolutionShiftMap &input, std::string ExtraString, ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist, int i, int j, int k )
{
init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(input.Vertex_X_Regions,                  "", TFile_Map_MC, StartingPlaylist, i, j, k);
init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(input.Vertex_Y_Regions,                  "", TFile_Map_MC, StartingPlaylist, i, j, k);
init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(input.Vertex_Z_Regions,                  "", TFile_Map_MC, StartingPlaylist, i, j, k);
init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(input.Vertex_Z_Regions_RCut,             "", TFile_Map_MC, StartingPlaylist, i, j, k);
init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(input.Vertex_R_Regions,                  "", TFile_Map_MC, StartingPlaylist, i, j, k);
//init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(input.Vertex_RR_Regions,                 "", TFile_Map_MC, i,j,k, StartingPlaylist);
init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(input.NearestWall_Regions,               "", TFile_Map_MC, StartingPlaylist, i, j, k);
init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(input.DistanceUpstreamCap_Regions,       "", TFile_Map_MC, StartingPlaylist, i, j, k);
init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(input.DistanceDownstreamCap_Regions,     "", TFile_Map_MC, StartingPlaylist, i, j, k);
init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(input.DistanceUpstreamCap_Regions_RCut,  "", TFile_Map_MC, StartingPlaylist, i, j, k);
init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(input.DistanceDownstreamCap_Regions_RCut,"", TFile_Map_MC, StartingPlaylist, i, j, k);
}





void Convolution_Tool::init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(ConvolutionShiftMap &input, std::string ExtraString, ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist, int i, int j, int k, int m )
{
init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(input.Vertex_X_Regions,                  "", TFile_Map_MC, StartingPlaylist, i, j, k, m);
init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(input.Vertex_Y_Regions,                  "", TFile_Map_MC, StartingPlaylist, i, j, k, m);
init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(input.Vertex_Z_Regions,                  "", TFile_Map_MC, StartingPlaylist, i, j, k, m);
init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(input.Vertex_Z_Regions_RCut,             "", TFile_Map_MC, StartingPlaylist, i, j, k, m);
init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(input.Vertex_R_Regions,                  "", TFile_Map_MC, StartingPlaylist, i, j, k, m);
//init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(input.Vertex_RR_Regions,                 "", TFile_Map_MC, i,j,k, StartingPlaylist);
init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(input.NearestWall_Regions,               "", TFile_Map_MC, StartingPlaylist, i, j, k, m);
init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(input.DistanceUpstreamCap_Regions,       "", TFile_Map_MC, StartingPlaylist, i, j, k, m);
init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(input.DistanceDownstreamCap_Regions,     "", TFile_Map_MC, StartingPlaylist, i, j, k, m);
init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(input.DistanceUpstreamCap_Regions_RCut,  "", TFile_Map_MC, StartingPlaylist, i, j, k, m);
init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(input.DistanceDownstreamCap_Regions_RCut,"", TFile_Map_MC, StartingPlaylist, i, j, k, m);
}

void Convolution_Tool::init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined_FittingVar(ConvolutionShiftMap &input, std::string ExtraString, ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist, int i, int j, int k, int m )
{
init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(input.Vertex_X_Regions,                  "", TFile_Map_MC, StartingPlaylist, i, j, k, m);
init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(input.Vertex_Y_Regions,                  "", TFile_Map_MC, StartingPlaylist, i, j, k, m);
init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(input.Vertex_Z_Regions,                  "", TFile_Map_MC, StartingPlaylist, i, j, k, m);
init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(input.Vertex_R_Regions,                  "", TFile_Map_MC, StartingPlaylist, i, j, k, m);
}


void Convolution_Tool::init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(ConvolutionShiftMap &input, std::string ExtraString, ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist, BestIndex_Regions indexMap   )
{
init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(input.Vertex_X_Regions,                  "", TFile_Map_MC, StartingPlaylist, indexMap.upstream.best_Chisqrt_X,     indexMap.barrel.best_Chisqrt_X,     indexMap.downstream.best_Chisqrt_X,     indexMap.concave.best_Chisqrt_X      );
init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(input.Vertex_Y_Regions,                  "", TFile_Map_MC, StartingPlaylist, indexMap.upstream.best_Chisqrt_Y,     indexMap.barrel.best_Chisqrt_Y,     indexMap.downstream.best_Chisqrt_Y,     indexMap.concave.best_Chisqrt_Y      );
init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(input.Vertex_Z_Regions,                  "", TFile_Map_MC, StartingPlaylist, indexMap.upstream.best_Chisqrt_Z,     indexMap.barrel.best_Chisqrt_Z,     indexMap.downstream.best_Chisqrt_Z,     indexMap.concave.best_Chisqrt_Z      );
init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(input.Vertex_Z_Regions_RCut,             "", TFile_Map_MC, StartingPlaylist, indexMap.upstream.best_Chisqrt_Z_RCut,indexMap.barrel.best_Chisqrt_Z_RCut,indexMap.downstream.best_Chisqrt_Z_RCut,indexMap.concave.best_Chisqrt_Z_RCut );
init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(input.Vertex_R_Regions,                  "", TFile_Map_MC, StartingPlaylist, indexMap.upstream.best_Chisqrt_R,     indexMap.barrel.best_Chisqrt_R,     indexMap.downstream.best_Chisqrt_R,     indexMap.concave.best_Chisqrt_R      );
//init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(input.Vertex_RR_Regions,                 "", TFile_Map_MC, i,j,k, StartingPlaylist);
init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(input.NearestWall_Regions,               "", TFile_Map_MC, StartingPlaylist, indexMap.upstream.best_Chisqrt_NearestWall,                  indexMap.barrel.best_Chisqrt_NearestWall,                 indexMap.downstream.best_Chisqrt_NearestWall,                 indexMap.concave.best_Chisqrt_NearestWall                  );
init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(input.DistanceUpstreamCap_Regions,       "", TFile_Map_MC, StartingPlaylist, indexMap.upstream.best_Chisqrt_DistancetoUpstreamCap,        indexMap.barrel.best_Chisqrt_DistancetoUpstreamCap,       indexMap.downstream.best_Chisqrt_DistancetoUpstreamCap,       indexMap.concave.best_Chisqrt_DistancetoUpstreamCap        );
init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(input.DistanceDownstreamCap_Regions,     "", TFile_Map_MC, StartingPlaylist, indexMap.upstream.best_Chisqrt_DistancetoDownstreamCap,      indexMap.barrel.best_Chisqrt_DistancetoDownstreamCap,     indexMap.downstream.best_Chisqrt_DistancetoDownstreamCap,     indexMap.concave.best_Chisqrt_DistancetoDownstreamCap      );
init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(input.DistanceUpstreamCap_Regions_RCut,  "", TFile_Map_MC, StartingPlaylist, indexMap.upstream.best_Chisqrt_DistancetoUpstreamCap_RCut,   indexMap.barrel.best_Chisqrt_DistancetoUpstreamCap_RCut,  indexMap.downstream.best_Chisqrt_DistancetoUpstreamCap_RCut,  indexMap.concave.best_Chisqrt_DistancetoUpstreamCap_RCut   );
init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(input.DistanceDownstreamCap_Regions_RCut,"", TFile_Map_MC, StartingPlaylist, indexMap.upstream.best_Chisqrt_DistancetoDownstreamCap_RCut, indexMap.barrel.best_Chisqrt_DistancetoDownstreamCap_RCut,indexMap.downstream.best_Chisqrt_DistancetoDownstreamCap_RCut,indexMap.concave.best_Chisqrt_DistancetoDownstreamCap_RCut );

}







void Convolution_Tool::init_RECO_ConvolutionTotalHists_PlaylistCombinedMC(ConvolutionShiftMap &input, ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist, int i, int j, int k )
{
init_RECOConvolutionHist_MCShifted_PlaylistCombined(input.Vertex_X_TotalRegion,                    "",  TFile_Map_MC, StartingPlaylist, i , j, k );
init_RECOConvolutionHist_MCShifted_PlaylistCombined(input.Vertex_Y_TotalRegion,                    "",  TFile_Map_MC, StartingPlaylist, i , j, k );
init_RECOConvolutionHist_MCShifted_PlaylistCombined(input.Vertex_R_TotalRegion,                    "",  TFile_Map_MC, StartingPlaylist, i , j, k );
//init_RECOConvolutionHist_MCShifted_PlaylistCombined(input.Vertex_RR_TotalRegion,                   "",  TFile_Map_MC, i , j, k, StartingPlaylist );
init_RECOConvolutionHist_MCShifted_PlaylistCombined(input.Vertex_Z_TotalRegion,                    "",  TFile_Map_MC, StartingPlaylist, i, j, k);
init_RECOConvolutionHist_MCShifted_PlaylistCombined(input.Vertex_Z_TotalRegion_RCut,               "",  TFile_Map_MC, StartingPlaylist, i, j, k);
init_RECOConvolutionHist_MCShifted_PlaylistCombined(input.NearestWall_TotalRegion,                 "",  TFile_Map_MC, StartingPlaylist, i, j, k);
init_RECOConvolutionHist_MCShifted_PlaylistCombined(input.DistanceUpstreamCap_TotalRegion,         "",  TFile_Map_MC, StartingPlaylist, i, j, k);
init_RECOConvolutionHist_MCShifted_PlaylistCombined(input.DistanceDownstreamCap_TotalRegion,       "",  TFile_Map_MC, StartingPlaylist, i, j, k);
init_RECOConvolutionHist_MCShifted_PlaylistCombined(input.DistanceUpstreamCap_TotalRegion_RCut,    "",  TFile_Map_MC, StartingPlaylist, i, j, k);
init_RECOConvolutionHist_MCShifted_PlaylistCombined(input.DistanceDownstreamCap_TotalRegion_RCut,  "",  TFile_Map_MC, StartingPlaylist, i, j, k);
//std::cout<<"Finished:init_TRUE_ConvolutionTotalHists_PlaylistCombinedMC"<<std::endl;
}




void Convolution_Tool::init_BestFitHist_RECO_ConvolutionTotalHists_PlaylistCombinedMC(ConvolutionShiftMap &input, ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist, BestIndex bestindex_input  )
{
init_RECOConvolutionHist_MCShifted_PlaylistCombined(input.Vertex_X_TotalRegion,                    "",  TFile_Map_MC, StartingPlaylist, bestindex_input.best_Chisqrt_X.i , bestindex_input.best_Chisqrt_X.j, bestindex_input.best_Chisqrt_X.k);
init_RECOConvolutionHist_MCShifted_PlaylistCombined(input.Vertex_Y_TotalRegion,                    "",  TFile_Map_MC, StartingPlaylist, bestindex_input.best_Chisqrt_Y.i , bestindex_input.best_Chisqrt_Y.j, bestindex_input.best_Chisqrt_Y.k );
init_RECOConvolutionHist_MCShifted_PlaylistCombined(input.Vertex_R_TotalRegion,                    "",  TFile_Map_MC, StartingPlaylist, bestindex_input.best_Chisqrt_R.i , bestindex_input.best_Chisqrt_R.j, bestindex_input.best_Chisqrt_R.k );
//init_RECOConvolutionHist_MCShifted_PlaylistCombined(input.Vertex_RR_TotalRegion,                   "",  TFile_Map_MC, i , j, k, StartingPlaylist );
init_RECOConvolutionHist_MCShifted_PlaylistCombined(input.Vertex_Z_TotalRegion,                    "",  TFile_Map_MC, StartingPlaylist, bestindex_input.best_Chisqrt_Z.i,                            bestindex_input.best_Chisqrt_Z.j,                            bestindex_input.best_Chisqrt_Z.k);
init_RECOConvolutionHist_MCShifted_PlaylistCombined(input.Vertex_Z_TotalRegion_RCut,               "",  TFile_Map_MC, StartingPlaylist, bestindex_input.best_Chisqrt_Z_RCut.i,                       bestindex_input.best_Chisqrt_Z_RCut.j,                       bestindex_input.best_Chisqrt_Z_RCut.k);
init_RECOConvolutionHist_MCShifted_PlaylistCombined(input.NearestWall_TotalRegion,                 "",  TFile_Map_MC, StartingPlaylist, bestindex_input.best_Chisqrt_NearestWall.i,                  bestindex_input.best_Chisqrt_NearestWall.j,                  bestindex_input.best_Chisqrt_NearestWall.k);
init_RECOConvolutionHist_MCShifted_PlaylistCombined(input.DistanceUpstreamCap_TotalRegion,         "",  TFile_Map_MC, StartingPlaylist, bestindex_input.best_Chisqrt_DistancetoUpstreamCap.i,        bestindex_input.best_Chisqrt_DistancetoUpstreamCap.j,        bestindex_input.best_Chisqrt_DistancetoUpstreamCap.k);
init_RECOConvolutionHist_MCShifted_PlaylistCombined(input.DistanceDownstreamCap_TotalRegion,       "",  TFile_Map_MC, StartingPlaylist, bestindex_input.best_Chisqrt_DistancetoDownstreamCap.i,      bestindex_input.best_Chisqrt_DistancetoDownstreamCap.j,      bestindex_input.best_Chisqrt_DistancetoDownstreamCap.k);
init_RECOConvolutionHist_MCShifted_PlaylistCombined(input.DistanceUpstreamCap_TotalRegion_RCut,    "",  TFile_Map_MC, StartingPlaylist, bestindex_input.best_Chisqrt_DistancetoUpstreamCap_RCut.i,   bestindex_input.best_Chisqrt_DistancetoUpstreamCap_RCut.j,   bestindex_input.best_Chisqrt_DistancetoUpstreamCap_RCut.k);
init_RECOConvolutionHist_MCShifted_PlaylistCombined(input.DistanceDownstreamCap_TotalRegion_RCut,  "",  TFile_Map_MC, StartingPlaylist, bestindex_input.best_Chisqrt_DistancetoDownstreamCap_RCut.i, bestindex_input.best_Chisqrt_DistancetoDownstreamCap_RCut.j, bestindex_input.best_Chisqrt_DistancetoDownstreamCap_RCut.k);
//std::cout<<"Finished:init_TRUE_ConvolutionTotalHists_PlaylistCombinedMC"<<std::endl;

}



void Convolution_Tool::init_Clone_data(Convolution_hist &input,Convolution_hist &inputClone )
{
inputClone.MnvH1D_data = (PlotUtils::MnvH1D*)input.MnvH1D_data->Clone("data");

}


void Convolution_Tool::init_Clone_Material(Convolution_hist &input,Convolution_hist &inputClone )
{

  inputClone.MnvH1D_mc_Convoluted_Helium[0] = (MnvH1D*) input.MnvH1D_mc_Convoluted_Helium[0]->Clone();
  inputClone.MnvH1D_mc_Convoluted_Aluminium[0] = (MnvH1D*) input.MnvH1D_mc_Convoluted_Aluminium[0]->Clone();
  inputClone.MnvH1D_mc_Convoluted_Carbon[0] = (MnvH1D*) input.MnvH1D_mc_Convoluted_Carbon[0]->Clone();
  inputClone.MnvH1D_mc_Convoluted_Iron[0] = (MnvH1D*) input.MnvH1D_mc_Convoluted_Iron[0]->Clone();
  inputClone.MnvH1D_mc_Convoluted_Lead[0] = (MnvH1D*) input.MnvH1D_mc_Convoluted_Lead[0]->Clone();
  inputClone.MnvH1D_mc_Convoluted_Other[0] =(MnvH1D*) input.MnvH1D_mc_Convoluted_Other[0]->Clone();

}

void Convolution_Tool::init_Clone_Material(Convolution_hist &input,Convolution_hist &inputClone , int indnew , int indtoclone )
{

  inputClone.MnvH1D_mc_Convoluted_Helium[indnew] = (MnvH1D*) input.MnvH1D_mc_Convoluted_Helium[indtoclone]->Clone();
  inputClone.MnvH1D_mc_Convoluted_Aluminium[indnew] = (MnvH1D*) input.MnvH1D_mc_Convoluted_Aluminium[indtoclone]->Clone();
  inputClone.MnvH1D_mc_Convoluted_Carbon[indnew] = (MnvH1D*) input.MnvH1D_mc_Convoluted_Carbon[indtoclone]->Clone();
  inputClone.MnvH1D_mc_Convoluted_Iron[indnew] = (MnvH1D*) input.MnvH1D_mc_Convoluted_Iron[indtoclone]->Clone();
  inputClone.MnvH1D_mc_Convoluted_Lead[indnew] = (MnvH1D*) input.MnvH1D_mc_Convoluted_Lead[indtoclone]->Clone();
  inputClone.MnvH1D_mc_Convoluted_Other[indnew] =(MnvH1D*) input.MnvH1D_mc_Convoluted_Other[indtoclone]->Clone();

}



void Convolution_Tool::init_Clone_Plotting(Convolution_hist &input,Convolution_hist &inputClone )
{
init_Clone_data(input,inputClone );
init_Clone_Material(input,inputClone );

}


void Convolution_Tool::CloneRegions(Convolution_CryoRegions& input, Convolution_CryoRegions& inputClone){
init_Clone_Plotting(input.Upstream,inputClone.Upstream );
init_Clone_Plotting(input.Barrel,inputClone.Barrel );
init_Clone_Plotting(input.Downstream,inputClone.Downstream );
init_Clone_Plotting(input.Concave,inputClone.Concave );
}

void Convolution_Tool::CloneRegions_Material(Convolution_CryoRegions& input, Convolution_CryoRegions& inputClone, int indnew , int indtoclone ){
init_Clone_Material(input.Upstream,   inputClone.Upstream,        indnew, indtoclone  );
init_Clone_Material(input.Barrel,    inputClone.Barrel,          indnew, indtoclone  );
init_Clone_Material(input.Downstream,inputClone.Downstream,      indnew, indtoclone  );
init_Clone_Material(input.Concave,   inputClone.Concave,         indnew, indtoclone  );
}






void Convolution_Tool::CloneVertex(ConvolutionShiftMap &input, ConvolutionShiftMap &inputClone){

  CloneRegions(input.Vertex_X_Regions, inputClone.Vertex_X_Regions);
  CloneRegions(input.Vertex_Y_Regions, inputClone.Vertex_Y_Regions);
  CloneRegions(input.Vertex_Z_Regions, inputClone.Vertex_Z_Regions);
  CloneRegions(input.Vertex_R_Regions, inputClone.Vertex_R_Regions);

}
void Convolution_Tool::CloneTRUEVertex(ConvolutionShiftMap &input, ConvolutionShiftMap &inputClone){

  //CloneRegions(input.Vertex_TRUE_X_Regions, inputClone.Vertex_TRUE_X_Regions);
  //CloneRegions(input.Vertex_TRUE_Y_Regions, inputClone.Vertex_TRUE_Y_Regions);
  //CloneRegions(input.Vertex_TRUE_Z_Regions, inputClone.Vertex_TRUE_Z_Regions);
  //CloneRegions(input.Vertex_TRUE_R_Regions, inputClone.Vertex_TRUE_R_Regions);

  CloneRegions(input.Vertex_TRUE_X_Regions, inputClone.Vertex_TRUE_X_Regions);
  CloneRegions(input.Vertex_TRUE_Y_Regions, inputClone.Vertex_TRUE_Y_Regions);
  CloneRegions(input.Vertex_TRUE_Z_Regions, inputClone.Vertex_TRUE_Z_Regions);
  CloneRegions(input.Vertex_TRUE_R_Regions, inputClone.Vertex_TRUE_R_Regions);

}


void Convolution_Tool::CloneVertex(ConvolutionShiftMap &input, ConvolutionShiftMap &inputClone,int indnew , int indtoclone){

  CloneRegions_Material(input.Vertex_X_Regions, inputClone.Vertex_X_Regions, indnew, indtoclone);
  CloneRegions_Material(input.Vertex_Y_Regions, inputClone.Vertex_Y_Regions, indnew, indtoclone);
  CloneRegions_Material(input.Vertex_Z_Regions, inputClone.Vertex_Z_Regions, indnew, indtoclone);
  CloneRegions_Material(input.Vertex_R_Regions, inputClone.Vertex_R_Regions, indnew, indtoclone);
}


void Convolution_Tool::CloneTRUEVertex(ConvolutionShiftMap &input, ConvolutionShiftMap &inputClone,int indnew , int indtoclone){

  CloneRegions_Material(input.Vertex_TRUE_X_Regions, inputClone.Vertex_TRUE_X_Regions, indnew, indtoclone);
  CloneRegions_Material(input.Vertex_TRUE_Y_Regions, inputClone.Vertex_TRUE_Y_Regions, indnew, indtoclone);
  CloneRegions_Material(input.Vertex_TRUE_Z_Regions, inputClone.Vertex_TRUE_Z_Regions, indnew, indtoclone);
  CloneRegions_Material(input.Vertex_TRUE_R_Regions, inputClone.Vertex_TRUE_R_Regions, indnew, indtoclone);
}


void Convolution_Tool::CloneVars(ConvolutionShiftMap &input, ConvolutionShiftMap &inputClone, int indnew , int indtoclone){

  CloneRegions_Material(input.muonPT_Regions , inputClone.muonPT_Regions, indnew, indtoclone);
  CloneRegions_Material(input.muonPZ_Regions , inputClone.muonPZ_Regions, indnew, indtoclone);
  CloneRegions_Material(input.muonE_Regions , inputClone.muonE_Regions, indnew, indtoclone);
  CloneRegions_Material(input.muontheta_Regions , inputClone.muontheta_Regions, indnew, indtoclone);
  CloneRegions_Material(input.muonDOCA_Regions , inputClone.muonDOCA_Regions, indnew, indtoclone);
  CloneRegions_Material(input.NearestWall_Regions , inputClone.NearestWall_Regions, indnew, indtoclone);
  CloneRegions_Material(input.recoilDOCA_Regions , inputClone.recoilDOCA_Regions, indnew, indtoclone);
  CloneRegions_Material(input.recoilAngle_Regions , inputClone.recoilAngle_Regions, indnew, indtoclone);
  CloneRegions_Material(input.tracklength_Regions , inputClone.tracklength_Regions, indnew, indtoclone);


}

void Convolution_Tool::ClonetoFull_EMPTY(int indnew , int indtoclone){
  std::cout<<"inside:ClonetoFull_EMPTY "<<std::endl;
  std::cout<<"CloneVertex"<<std::endl;
CloneVertex(Full, Full_Empty, indnew , indtoclone);
std::cout<<"CloneVars"<<std::endl;
CloneVars(Full, Full_Empty,  indnew , indtoclone);
std::cout<<"clone true vertex "<< std::endl;
CloneTRUEVertex(Full, Full_Empty,  indnew , indtoclone);

}

void Convolution_Tool::ClonetoFull_EMPTY_Fiducial(int indnew , int indtoclone){
CloneVertex(Full_Fid, Full_Empty_Fid, indnew , indtoclone);

CloneVars(Full_Fid, Full_Empty_Fid,  indnew , indtoclone);

CloneTRUEVertex(Full_Fid, Full_Empty_Fid,  indnew , indtoclone);
}



void Convolution_Tool::CloneVars(ConvolutionShiftMap &input, ConvolutionShiftMap &inputClone){


  CloneRegions(input.muonPT_Regions , inputClone.muonPT_Regions);
  CloneRegions(input.muonPZ_Regions , inputClone.muonPZ_Regions);
  CloneRegions(input.muonE_Regions , inputClone.muonE_Regions);
  CloneRegions(input.muontheta_Regions , inputClone.muontheta_Regions);
  CloneRegions(input.muonDOCA_Regions , inputClone.muonDOCA_Regions);
  CloneRegions(input.NearestWall_Regions , inputClone.NearestWall_Regions);
  CloneRegions(input.recoilDOCA_Regions , inputClone.recoilDOCA_Regions);
  CloneRegions(input.recoilAngle_Regions , inputClone.recoilAngle_Regions);
  CloneRegions(input.tracklength_Regions , inputClone.tracklength_Regions);

}


void Convolution_Tool::CloneFulltoFull_Empty(){

CloneVars(Full, Full_Empty);
CloneVertex(Full, Full_Empty);
CloneTRUEVertex(Full, Full_Empty);


}
void Convolution_Tool::CloneFulltoFull_Empty_TRUE(){

CloneTRUEVertex(Full, Full_Empty);
}
void Convolution_Tool::CloneFulltoFull_Empty_TRUE_Fiducial(){
CloneTRUEVertex(Full_Fid, Full_Empty_Fid);
}


void Convolution_Tool::CloneFulltoFull_Empty_Fiducial(){

CloneVars(Full_Fid, Full_Empty_Fid);
CloneVertex(Full_Fid, Full_Empty_Fid);
CloneTRUEVertex(Full_Fid, Full_Empty_Fid);

}

void Convolution_Tool::init_RECO_Total_and_Regions_Hists_PlaylistCombinedMC(ConvolutionShiftMap &input, ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist, int i, int j, int k ){

init_RECO_ConvolutionTotalHists_PlaylistCombinedMC(input, TFile_Map_MC,  StartingPlaylist,  i ,  j,  k );
init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(input, "",  TFile_Map_MC , StartingPlaylist,  i ,  j,  k );


}

void  Convolution_Tool::init_RECO_Convolution_TotalHists_PlaylistCombinedMC(int i, int j, int k){
// Ful
init_RECO_ConvolutionTotalHists_PlaylistCombinedMC(Full,         TFile_Map_Full_MC,   StartingPlaylist_Full,  i,  j,  k);
//std::cout<<"Finished Full"<<std::endl;
init_RECO_ConvolutionTotalHists_PlaylistCombinedMC(Full_Empty,   TFile_Map_Full_MC,   StartingPlaylist_Full,  i,  j,  k);
//std::cout<<"Finished Full - Empty"<<std::endl;
init_RECO_ConvolutionTotalHists_PlaylistCombinedMC(Empty,        TFile_Map_Empty_MC,  StartingPlaylist_Empty, i,  j,  k);
//std::cout<<"Empty"<<std::endl;
//std::cout<<"Finished Intializes now to POT scale"<<std::endl;

POTscale_MC_Convoluted_Total(Full,        Full.POT_MC, 1);
POTscale_MC_Convoluted_Total(Full_Empty , Full.POT_MC, 1);
POTscale_MC_Convoluted_Total(Empty,      Empty.POT_MC, 1);
//std::cout<<"Now to Scale"<<std::endl;

Subtract_TRUEConvolutionHists_Total(Full_Empty , Empty, 1);

}




void  Convolution_Tool::init_RECO_Convolution_Regions_Hists_PlaylistCombinedMC(int i, int j, int k){
// Full
init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(Full,  "",       TFile_Map_Full_MC,   StartingPlaylist_Full,  i ,  j,  k );
init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(Full_Empty,"",   TFile_Map_Full_MC,   StartingPlaylist_Full,  i ,  j,  k );
init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(Empty, "",       TFile_Map_Empty_MC,  StartingPlaylist_Empty, i ,  j,  k );

POTscale_MC_Convoluted_Regions(Full,        Full.POT_MC,  1);
POTscale_MC_Convoluted_Regions(Full_Empty , Full.POT_MC,  1);
POTscale_MC_Convoluted_Regions(Empty,       Empty.POT_MC, 1);

Subtract_TRUEConvolutionHists_Regions(Full_Empty , Empty, 1);

}


void  Convolution_Tool::init_RECO_Convolution_Regions_Hists_PlaylistCombinedMC_ForFit(int i, int j, int k, int m ){
// Full
init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined_FittingVar(Full,  "",       TFile_Map_Full_MC,   StartingPlaylist_Full,  i ,  j,  k, m);
init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined_FittingVar(Full_Empty,"",   TFile_Map_Full_MC,   StartingPlaylist_Full,  i ,  j,  k, m);
init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined_FittingVar(Empty, "",       TFile_Map_Empty_MC,  StartingPlaylist_Empty, i ,  j,  k, m);

POTscale_MC_Convoluted_Regions_fitRegionsOnly(Full,        Full.POT_MC,  1);
POTscale_MC_Convoluted_Regions_fitRegionsOnly(Full_Empty , Full.POT_MC,  1);
POTscale_MC_Convoluted_Regions_fitRegionsOnly(Empty,       Empty.POT_MC, 1);

Subtract_TRUEConvolutionHists_Regions_FitVars(Full_Empty , Empty, 1);

}


void  Convolution_Tool::init_RECO_Convolution_Regions_Hists_PlaylistCombinedMC_ForFit_Empty(int i, int j, int k, int m ){
// Full
init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined_FittingVar(Empty, "",       TFile_Map_Empty_MC,  StartingPlaylist_Empty, i ,  j,  k, m);
POTscale_MC_Convoluted_Regions_fitRegionsOnly(Empty,       Empty.POT_MC, 1);
}



void  Convolution_Tool::init_RECO_Convolution_Regions_Hists_PlaylistCombinedMC_ForFit_Full(int i, int j, int k, int m ){
// Full
init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined_FittingVar(Full, "",       TFile_Map_Empty_MC,  StartingPlaylist_Empty, i ,  j,  k, m);
POTscale_MC_Convoluted_Regions_fitRegionsOnly(Full,       Empty.POT_MC, 1);
}

void  Convolution_Tool::init_RECO_Convolution_TotalHists_PlaylistCombinedMC(BestIndex bestindex_Full, BestIndex bestindex_Empty){
// Full

init_BestFitHist_RECO_ConvolutionTotalHists_PlaylistCombinedMC(Full,       TFile_Map_Full_MC,   StartingPlaylist_Full, bestindex_Full  );
init_BestFitHist_RECO_ConvolutionTotalHists_PlaylistCombinedMC(Full_Empty, TFile_Map_Full_MC,   StartingPlaylist_Full, bestindex_Full  );
init_BestFitHist_RECO_ConvolutionTotalHists_PlaylistCombinedMC(Empty,      TFile_Map_Empty_MC,  StartingPlaylist_Empty, bestindex_Empty  );


POTscale_MC_Convoluted_Total(Full,        Full.POT_MC, 1);
POTscale_MC_Convoluted_Total(Full_Empty , Full.POT_MC, 1);
POTscale_MC_Convoluted_Total(Empty,      Empty.POT_MC, 1);

Subtract_TRUEConvolutionHists_Total(Full_Empty , Empty, 1);
}

void  Convolution_Tool::init_RECO_Convolution_RegonsHists_PlaylistCombinedMC(BestIndex_Regions bestindex_Full, BestIndex_Regions bestindex_Empty){
// Full

init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(Full,      "", TFile_Map_Full_MC,   StartingPlaylist_Full, bestindex_Full  );
init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(Full_Empty,"", TFile_Map_Full_MC,   StartingPlaylist_Full, bestindex_Full  );
init_RECOConvolution_RegionsHists_MCShifted_PlaylistCombined(Empty,     "", TFile_Map_Empty_MC,  StartingPlaylist_Empty, bestindex_Empty  );

POTscale_MC_Convoluted_Regions(Full,        Full.POT_MC, 1);
POTscale_MC_Convoluted_Regions(Full_Empty , Full.POT_MC, 1);
POTscale_MC_Convoluted_Regions(Empty,      Empty.POT_MC, 1);

Subtract_TRUEConvolutionHists_Regions(Full_Empty , Empty, 1);


}

void  Convolution_Tool::init_ALL_RECOConvolution_Regions_Hists_PlaylistCombinedMC(int i, int j, int k){
//.std::cout<<"Inside:init_ALL_Convolution_Regions_Hists_PlaylistCombinedMC"<<std::endl;
init_RECO_Convolution_TotalHists_PlaylistCombinedMC( i, j, k);
//.std::cout<<"Finished: init_TRUE_Convolution_TotalHists_PlaylistCombinedMC"<<std::endl;
init_RECO_Convolution_Regions_Hists_PlaylistCombinedMC( i, j, k);
}







void  Convolution_Tool::init_ALL_Convolution_Regions_Hists_PlaylistCombinedMC(int i, int j, int k){
//std::cout<<"Inside:init_ALL_Convolution_Regions_Hists_PlaylistCombinedMC"<<std::endl;
init_TRUE_Convolution_TotalHists_PlaylistCombinedMC( i, j, k);
//std::cout<<"Finished: init_TRUE_Convolution_TotalHists_PlaylistCombinedMC"<<std::endl;
init_TRUE_Convolution_Regions_Hists_PlaylistCombinedMC( i, j, k);
}


void  Convolution_Tool::init_ZeroShift_TRUE_Convolution_Regions_Hists_PlaylistCombinedMC(){

init_TRUE_Convolution_Regions_Hists_PlaylistCombinedMC(ZeroShift3index.i , ZeroShift3index.j, ZeroShift3index.k);
init_TRUE_Convolution_TotalHists_PlaylistCombinedMC(ZeroShift3index.i , ZeroShift3index.j, ZeroShift3index.k);

}

void  Convolution_Tool::init_ZeroShift_RECO_Convolution_Regions_Hists_PlaylistCombinedMC(){

init_RECO_Convolution_Regions_Hists_PlaylistCombinedMC(ZeroShift3index.i , ZeroShift3index.j, ZeroShift3index.k);
init_RECO_Convolution_TotalHists_PlaylistCombinedMC(ZeroShift3index.i , ZeroShift3index.j, ZeroShift3index.k);

}



void Convolution_Tool::init_TRUTHConvolution_MCZEROShifted_PlaylistCombined_Histograms(ConvolutionShiftMap &input, ME_playlist_TFileMAP TFile_Map_MC, ME_helium_Playlists StartingPlaylist ){

  init_TRUE_ConvolutionTotalHists_PlaylistCombinedMC(input, TFile_Map_MC,  StartingPlaylist, ZeroShift3index.i , ZeroShift3index.j, ZeroShift3index.k );

}




void Convolution_Tool::FillDataPOT(double inputPOT, ConvolutionShiftMap &inputMap){
  inputMap.POT_Data = inputPOT;
}
void Convolution_Tool::FillMCPOT(double inputPOT, ConvolutionShiftMap &inputMap){
  inputMap.POT_MC = inputPOT;
}


void Convolution_Tool::ConstuctandFill_Complete_NuMEPlaylist_POT(std::vector<ME_helium_Playlists> FullPlaylist , std::vector<ME_helium_Playlists> EmptyPlaylist){

  double Total_MCFull_POT  = 0.0;
  double Total_MCEmpty_POT = 0.0;
  double Total_DataFull_POT  = 0.0;
  double Total_DataEmpty_POT  = 0.0;

  for(auto cat:FullPlaylist){
    Total_MCFull_POT+=POTMap_Full_MC[cat];
    Total_DataFull_POT+=POTMap_Full_Data[cat];
  }

  for(auto cat:EmptyPlaylist){
    Total_MCEmpty_POT+=POTMap_Empty_MC[cat];
    Total_DataEmpty_POT+=POTMap_Empty_Data[cat];
  }

  double FullMC_toFullData = Total_DataFull_POT / Total_MCFull_POT;
  double EmptyMC_toFullData = Total_DataFull_POT / Total_MCEmpty_POT;
  double EmptyData_toFullData = Total_DataFull_POT / Total_DataEmpty_POT;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
std::cout<<" FullMC_toFullData = "<< FullMC_toFullData<<std::endl;
std::cout<<" EmptyMC_toFullData = "<< EmptyMC_toFullData<<std::endl;
std::cout<<" EmptyData_toFullData = "<< EmptyData_toFullData<<std::endl;
std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;


  FillDataPOT(EmptyData_toFullData, Empty);
  FillMCPOT(EmptyMC_toFullData, Empty);
  FillMCPOT(FullMC_toFullData, Full);
}

void Convolution_Tool::init_NuMEPlaylist_POT(){
  ConstuctandFill_Complete_NuMEPlaylist_POT(FullPlaylist_vector , EmptyPlaylist_vector);
}


void Convolution_Tool::POTscaleData(Convolution_hist &input , double POTscaler){
input.MnvH1D_data->Scale(POTscaler);
}
void Convolution_Tool::POTscaleMC_Reco(Convolution_hist &input , double POTscaler){
input.MnvH1D_mc_Reco->Scale(POTscaler);
}
void Convolution_Tool::POTscaleMC_TRUTH(Convolution_hist &input , double POTscaler){
input.MnvH1D_mc_TRUTH->Scale(POTscaler);
}
void Convolution_Tool::POTscaleMC_ConvoluteTRUTH(Convolution_hist &input , double POTscaler, int ind){
input.MnvH1D_mc_Convoluted[ind]->Scale(POTscaler);
}

void Convolution_Tool::POTscaleMC_Convolute_Material(Convolution_hist &input , double POTscaler, int ind){
input.MnvH1D_mc_Convoluted_Helium[ind]->Scale(POTscaler);
input.MnvH1D_mc_Convoluted_Aluminium[ind]->Scale(POTscaler);
input.MnvH1D_mc_Convoluted_Carbon[ind]->Scale(POTscaler);
input.MnvH1D_mc_Convoluted_Iron[ind]->Scale(POTscaler);
input.MnvH1D_mc_Convoluted_Lead[ind]->Scale(POTscaler);
input.MnvH1D_mc_Convoluted_Other[ind]->Scale(POTscaler);
}

void Convolution_Tool::POTscale_MCReco_Material_Regions(Convolution_CryoRegions &input , double POTscaler, int ind){
POTscaleMC_Convolute_Material(input.Upstream,  POTscaler, ind);
POTscaleMC_Convolute_Material(input.Barrel,    POTscaler, ind);
POTscaleMC_Convolute_Material(input.Downstream,POTscaler, ind);
POTscaleMC_Convolute_Material(input.Concave,   POTscaler, ind);
}

void Convolution_Tool::POTscale_MCReco_Material_Regions(ConvolutionShiftMap &input , double POTscaler, int ind){

  POTscale_MCReco_Material_Regions(input.Vertex_X_Regions, POTscaler, ind);
  POTscale_MCReco_Material_Regions(input.Vertex_Y_Regions, POTscaler, ind);
  POTscale_MCReco_Material_Regions(input.Vertex_R_Regions, POTscaler, ind);
  POTscale_MCReco_Material_Regions(input.Vertex_Z_Regions, POTscaler, ind);
}

void Convolution_Tool::POTscale_MCReco_Material_Regions_TRUEvertex(ConvolutionShiftMap &input , double POTscaler, int ind){

  POTscale_MCReco_Material_Regions(input.Vertex_TRUE_X_Regions, POTscaler, ind);
  POTscale_MCReco_Material_Regions(input.Vertex_TRUE_Y_Regions, POTscaler, ind);
  POTscale_MCReco_Material_Regions(input.Vertex_TRUE_R_Regions, POTscaler, ind);
  POTscale_MCReco_Material_Regions(input.Vertex_TRUE_Z_Regions, POTscaler, ind);
}

void Convolution_Tool::POTscale_MCReco_Material_Regions_nonVertexVar(ConvolutionShiftMap &input , double POTscaler, int ind){

  POTscale_MCReco_Material_Regions(input.muonPT_Regions, POTscaler, ind);
  POTscale_MCReco_Material_Regions(input.muonPZ_Regions, POTscaler, ind);
  POTscale_MCReco_Material_Regions(input.muonE_Regions, POTscaler, ind);
  POTscale_MCReco_Material_Regions(input.muontheta_Regions, POTscaler, ind);
  POTscale_MCReco_Material_Regions(input.muonDOCA_Regions, POTscaler, ind);
  POTscale_MCReco_Material_Regions(input.NearestWall_Regions, POTscaler, ind);
  POTscale_MCReco_Material_Regions(input.recoilDOCA_Regions, POTscaler, ind);
  POTscale_MCReco_Material_Regions(input.recoilAngle_Regions, POTscaler, ind);
  POTscale_MCReco_Material_Regions(input.tracklength_Regions, POTscaler, ind);

}






void Convolution_Tool::POTscaleData_Regions(Convolution_CryoRegions &input , double POTscaler){
POTscaleData(input.Upstream,   POTscaler);
POTscaleData(input.Barrel,     POTscaler);
POTscaleData(input.Downstream, POTscaler);
POTscaleData(input.Concave,    POTscaler);
}



void Convolution_Tool::POTscale_MCReco_Regions(Convolution_CryoRegions &input , double POTscaler){
POTscaleMC_Reco(input.Upstream,  POTscaler);
POTscaleMC_Reco(input.Barrel,    POTscaler);
POTscaleMC_Reco(input.Downstream,POTscaler);
POTscaleMC_Reco(input.Concave,   POTscaler);
}

void Convolution_Tool::POTscale_MCTRUTH_Regions(Convolution_CryoRegions &input , double POTscaler){
POTscaleMC_TRUTH(input.Upstream,   POTscaler);
POTscaleMC_TRUTH(input.Barrel,     POTscaler);
POTscaleMC_TRUTH(input.Downstream, POTscaler);
POTscaleMC_TRUTH(input.Concave,    POTscaler);
}
void Convolution_Tool::POTscaleMC_ConvoluteTRUTH_Regions(Convolution_CryoRegions &input , double POTscaler, int ind){
POTscaleMC_ConvoluteTRUTH(input.Upstream,   POTscaler, ind);
POTscaleMC_ConvoluteTRUTH(input.Barrel,     POTscaler, ind);
POTscaleMC_ConvoluteTRUTH(input.Downstream, POTscaler, ind);
POTscaleMC_ConvoluteTRUTH(input.Concave,    POTscaler, ind);
}
void Convolution_Tool::POTscaleData_Total(ConvolutionShiftMap &input , double POTscaler){

  POTscaleData(input.Vertex_X_TotalRegion,                  POTscaler);
  POTscaleData(input.Vertex_Y_TotalRegion,                  POTscaler);
  POTscaleData(input.Vertex_R_TotalRegion,                  POTscaler);
  //POTscaleData(input.Vertex_RR_TotalRegion,                 POTscaler);
  POTscaleData(input.Vertex_Z_TotalRegion,                  POTscaler);
  POTscaleData(input.Vertex_Z_TotalRegion_RCut,             POTscaler);
  POTscaleData(input.NearestWall_TotalRegion,               POTscaler);
  POTscaleData(input.DistanceUpstreamCap_TotalRegion,       POTscaler);
  POTscaleData(input.DistanceDownstreamCap_TotalRegion,     POTscaler);
  POTscaleData(input.DistanceUpstreamCap_TotalRegion_RCut,  POTscaler);
  POTscaleData(input.DistanceDownstreamCap_TotalRegion_RCut,POTscaler);
}

void Convolution_Tool::POTscaleData_Regions(ConvolutionShiftMap &input , double POTscaler){

  POTscaleData_Regions(input.Vertex_X_Regions,                  POTscaler);
  POTscaleData_Regions(input.Vertex_Y_Regions,                  POTscaler);
  POTscaleData_Regions(input.Vertex_R_Regions,                  POTscaler);
  //POTscaleData_Regions(input.Vertex_RR_TotalRegion,                 POTscaler);
  POTscaleData_Regions(input.Vertex_Z_Regions,                  POTscaler);
  POTscaleData_Regions(input.Vertex_Z_Regions_RCut,             POTscaler);
  POTscaleData_Regions(input.NearestWall_Regions,               POTscaler);
  POTscaleData_Regions(input.DistanceUpstreamCap_Regions,       POTscaler);
  POTscaleData_Regions(input.DistanceDownstreamCap_Regions,     POTscaler);
  POTscaleData_Regions(input.DistanceUpstreamCap_Regions_RCut,  POTscaler);
  POTscaleData_Regions(input.DistanceDownstreamCap_Regions_RCut,POTscaler);
}


void Convolution_Tool::POTscaleData_Regions_nonVertexVars(ConvolutionShiftMap &input , double POTscaler){


  POTscaleData_Regions(input.muonPT_Regions,  POTscaler);
  POTscaleData_Regions(input.muonPZ_Regions,  POTscaler);
  POTscaleData_Regions(input.muonE_Regions,  POTscaler);
  POTscaleData_Regions(input.muontheta_Regions,  POTscaler);
  POTscaleData_Regions(input.muonDOCA_Regions,  POTscaler);
  POTscaleData_Regions(input.NearestWall_Regions,  POTscaler);
  POTscaleData_Regions(input.recoilDOCA_Regions,  POTscaler);
  POTscaleData_Regions(input.recoilAngle_Regions,  POTscaler);
  POTscaleData_Regions(input.tracklength_Regions,  POTscaler);



}

void Convolution_Tool::POTscaleData_Regions_Fitonly(ConvolutionShiftMap &input , double POTscaler){

  POTscaleData_Regions(input.Vertex_X_Regions,                  POTscaler);
  POTscaleData_Regions(input.Vertex_Y_Regions,                  POTscaler);
  POTscaleData_Regions(input.Vertex_R_Regions,                  POTscaler);
  POTscaleData_Regions(input.Vertex_Z_Regions,                  POTscaler);
}


void Convolution_Tool::POTscale_MCReco_Total(ConvolutionShiftMap &input , double POTscaler){

  POTscaleMC_Reco(input.Vertex_X_TotalRegion,                  POTscaler);
  POTscaleMC_Reco(input.Vertex_Y_TotalRegion,                  POTscaler);
  POTscaleMC_Reco(input.Vertex_R_TotalRegion,                  POTscaler);
  //POTscaleMC_Reco(input.Vertex_RR_TotalRegion,                 POTscaler);
  POTscaleMC_Reco(input.Vertex_Z_TotalRegion,                  POTscaler);
  POTscaleMC_Reco(input.Vertex_Z_TotalRegion_RCut,             POTscaler);
  POTscaleMC_Reco(input.NearestWall_TotalRegion,               POTscaler);
  POTscaleMC_Reco(input.DistanceUpstreamCap_TotalRegion,       POTscaler);
  POTscaleMC_Reco(input.DistanceDownstreamCap_TotalRegion,     POTscaler);
  POTscaleMC_Reco(input.DistanceUpstreamCap_TotalRegion_RCut,  POTscaler);
  POTscaleMC_Reco(input.DistanceDownstreamCap_TotalRegion_RCut,POTscaler);
}

void Convolution_Tool::POTscale_MCReco_Regions(ConvolutionShiftMap &input , double POTscaler){

  POTscale_MCReco_Regions(input.Vertex_X_Regions,                  POTscaler);
  POTscale_MCReco_Regions(input.Vertex_Y_Regions,                  POTscaler);
  POTscale_MCReco_Regions(input.Vertex_R_Regions,                  POTscaler);
  //POTscale_MCReco_Regions(input.Vertex_RR_Regions,                 POTscaler);
  POTscale_MCReco_Regions(input.Vertex_Z_Regions,                  POTscaler);
  POTscale_MCReco_Regions(input.Vertex_Z_Regions_RCut,             POTscaler);
  POTscale_MCReco_Regions(input.NearestWall_Regions,               POTscaler);
  POTscale_MCReco_Regions(input.DistanceUpstreamCap_Regions,       POTscaler);
  POTscale_MCReco_Regions(input.DistanceDownstreamCap_Regions,     POTscaler);
  POTscale_MCReco_Regions(input.DistanceUpstreamCap_Regions_RCut,  POTscaler);
  POTscale_MCReco_Regions(input.DistanceDownstreamCap_Regions_RCut,POTscaler);
}



void Convolution_Tool::POTscale_MCTRUTH_Total(ConvolutionShiftMap &input , double POTscaler){

  POTscaleMC_TRUTH(input.Vertex_X_TotalRegion,                  POTscaler);
  POTscaleMC_TRUTH(input.Vertex_Y_TotalRegion,                  POTscaler);
  POTscaleMC_TRUTH(input.Vertex_R_TotalRegion,                  POTscaler);
  //POTscaleMC_TRUTH(input.Vertex_RR_TotalRegion,                 POTscaler);
  POTscaleMC_TRUTH(input.Vertex_Z_TotalRegion,                  POTscaler);
  POTscaleMC_TRUTH(input.Vertex_Z_TotalRegion_RCut,             POTscaler);
  POTscaleMC_TRUTH(input.NearestWall_TotalRegion,               POTscaler);
  POTscaleMC_TRUTH(input.DistanceUpstreamCap_TotalRegion,       POTscaler);
  POTscaleMC_TRUTH(input.DistanceDownstreamCap_TotalRegion,     POTscaler);
  POTscaleMC_TRUTH(input.DistanceUpstreamCap_TotalRegion_RCut,  POTscaler);
  POTscaleMC_TRUTH(input.DistanceDownstreamCap_TotalRegion_RCut,POTscaler);
}
void Convolution_Tool::POTscale_MCTRUTH_Regions(ConvolutionShiftMap &input , double POTscaler){

  POTscale_MCTRUTH_Regions(input.Vertex_X_Regions,                  POTscaler);
  POTscale_MCTRUTH_Regions(input.Vertex_Y_Regions,                  POTscaler);
  POTscale_MCTRUTH_Regions(input.Vertex_R_Regions,                  POTscaler);
  //POTscale_MCTRUTH_Regions(input.Vertex_RR_Region,                 POTscaler);
  POTscale_MCTRUTH_Regions(input.Vertex_Z_Regions,                  POTscaler);
  POTscale_MCTRUTH_Regions(input.Vertex_Z_Regions_RCut,             POTscaler);
  POTscale_MCTRUTH_Regions(input.NearestWall_Regions,               POTscaler);
  POTscale_MCTRUTH_Regions(input.DistanceUpstreamCap_Regions,       POTscaler);
  POTscale_MCTRUTH_Regions(input.DistanceDownstreamCap_Regions,     POTscaler);
  POTscale_MCTRUTH_Regions(input.DistanceUpstreamCap_Regions_RCut,  POTscaler);
  POTscale_MCTRUTH_Regions(input.DistanceDownstreamCap_Regions_RCut,POTscaler);
}

void Convolution_Tool::POTscale_MC_Convoluted_Total(ConvolutionShiftMap &input , double POTscaler, int ind){

  POTscaleMC_ConvoluteTRUTH(input.Vertex_X_TotalRegion,                  POTscaler, ind);
  POTscaleMC_ConvoluteTRUTH(input.Vertex_Y_TotalRegion,                  POTscaler, ind);
  POTscaleMC_ConvoluteTRUTH(input.Vertex_R_TotalRegion,                  POTscaler, ind);
  //POTscaleMC_ConvoluteTRUTH(input.Vertex_RR_TotalRegion,                 POTscaler, ind);
  POTscaleMC_ConvoluteTRUTH(input.Vertex_Z_TotalRegion,                  POTscaler, ind);
  POTscaleMC_ConvoluteTRUTH(input.Vertex_Z_TotalRegion_RCut,             POTscaler, ind);
  POTscaleMC_ConvoluteTRUTH(input.NearestWall_TotalRegion,               POTscaler, ind);
  POTscaleMC_ConvoluteTRUTH(input.DistanceUpstreamCap_TotalRegion,       POTscaler, ind);
  POTscaleMC_ConvoluteTRUTH(input.DistanceDownstreamCap_TotalRegion,     POTscaler, ind);
  POTscaleMC_ConvoluteTRUTH(input.DistanceUpstreamCap_TotalRegion_RCut,  POTscaler, ind);
  POTscaleMC_ConvoluteTRUTH(input.DistanceDownstreamCap_TotalRegion_RCut,POTscaler, ind);
}

void Convolution_Tool::POTscale_MC_Convoluted_Regions(ConvolutionShiftMap &input , double POTscaler, int ind){

  POTscaleMC_ConvoluteTRUTH_Regions(input.Vertex_X_Regions,                  POTscaler, ind);
  POTscaleMC_ConvoluteTRUTH_Regions(input.Vertex_Y_Regions,                  POTscaler, ind);
  POTscaleMC_ConvoluteTRUTH_Regions(input.Vertex_R_Regions,                  POTscaler, ind);
  //POTscaleMC_ConvoluteTRUTH_Regions(input.Vertex_RR_Regions,                 POTscaler, ind);
  POTscaleMC_ConvoluteTRUTH_Regions(input.Vertex_Z_Regions,                  POTscaler, ind);
  POTscaleMC_ConvoluteTRUTH_Regions(input.Vertex_Z_Regions_RCut,             POTscaler, ind);
  POTscaleMC_ConvoluteTRUTH_Regions(input.NearestWall_Regions,               POTscaler, ind);
  POTscaleMC_ConvoluteTRUTH_Regions(input.DistanceUpstreamCap_Regions,       POTscaler, ind);
  POTscaleMC_ConvoluteTRUTH_Regions(input.DistanceDownstreamCap_Regions,     POTscaler, ind);
  POTscaleMC_ConvoluteTRUTH_Regions(input.DistanceUpstreamCap_Regions_RCut,  POTscaler, ind);
  POTscaleMC_ConvoluteTRUTH_Regions(input.DistanceDownstreamCap_Regions_RCut,POTscaler, ind);
}


void Convolution_Tool::POTscale_MC_Convoluted_Regions_fitRegionsOnly(ConvolutionShiftMap &input , double POTscaler, int ind){

  POTscaleMC_ConvoluteTRUTH_Regions(input.Vertex_X_Regions,                  POTscaler, ind);
  POTscaleMC_ConvoluteTRUTH_Regions(input.Vertex_Y_Regions,                  POTscaler, ind);
  POTscaleMC_ConvoluteTRUTH_Regions(input.Vertex_R_Regions,                  POTscaler, ind);
  POTscaleMC_ConvoluteTRUTH_Regions(input.Vertex_Z_Regions,                  POTscaler, ind);

}


void Convolution_Tool::Subtract_DataHists(Convolution_hist &Subtract_from , Convolution_hist &input ){
  Subtract_from.MnvH1D_data->Add(input.MnvH1D_data, -1.0);
}

void Convolution_Tool::Subtract_CryoRegions_DataHists(Convolution_CryoRegions &Subtract_from , Convolution_CryoRegions &input ){
Subtract_DataHists(Subtract_from.Upstream,    input.Upstream );
Subtract_DataHists(Subtract_from.Barrel,      input.Barrel );
Subtract_DataHists(Subtract_from.Downstream,  input.Downstream );
Subtract_DataHists(Subtract_from.Concave,     input.Concave );
}

void Convolution_Tool::PrintPOT(){
  std::cout<<"~~~~~~~~~~~~~~~~PRINTING POT~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<" POT MC FUll = " << Full.POT_MC<<std::endl;
  std::cout<<" POT Data FUll = " << Full.POT_Data<<std::endl;

  std::cout<<" POT MC Empty = " << Empty.POT_MC<<std::endl;
  std::cout<<" POT Data Empty = " << Empty.POT_Data<<std::endl;
  std::cout<<"~~~~~~~~~~~~~~~~ Finished ~~~~~~~~~~~~~~~~~~~"<<std::endl;

}



void Convolution_Tool::Subtract_DataHists_Total(ConvolutionShiftMap &Subtract_from , ConvolutionShiftMap &input)
{

Subtract_DataHists( Subtract_from.Vertex_X_TotalRegion,                   input.Vertex_X_TotalRegion);
Subtract_DataHists( Subtract_from.Vertex_Y_TotalRegion,                   input.Vertex_Y_TotalRegion);
Subtract_DataHists( Subtract_from.Vertex_R_TotalRegion,                   input.Vertex_R_TotalRegion);
//Subtract_DataHists( Subtract_from.Vertex_RR_TotalRegion,                  input.Vertex_RR_TotalRegion);
Subtract_DataHists( Subtract_from.Vertex_Z_TotalRegion,                   input.Vertex_Z_TotalRegion);
Subtract_DataHists( Subtract_from.Vertex_Z_TotalRegion_RCut,              input.Vertex_Z_TotalRegion_RCut);
Subtract_DataHists( Subtract_from.NearestWall_TotalRegion,                input.NearestWall_TotalRegion);
Subtract_DataHists( Subtract_from.DistanceUpstreamCap_TotalRegion,        input.DistanceUpstreamCap_TotalRegion);
Subtract_DataHists( Subtract_from.DistanceDownstreamCap_TotalRegion,      input.DistanceDownstreamCap_TotalRegion);
Subtract_DataHists( Subtract_from.DistanceUpstreamCap_TotalRegion_RCut,   input.DistanceUpstreamCap_TotalRegion_RCut);
Subtract_DataHists( Subtract_from.DistanceDownstreamCap_TotalRegion_RCut, input.DistanceDownstreamCap_TotalRegion_RCut);
}

void Convolution_Tool::Subtract_DataHists_Regions(ConvolutionShiftMap &Subtract_from , ConvolutionShiftMap &input)
{
  Subtract_CryoRegions_DataHists(Subtract_from.Vertex_X_Regions,                   input.Vertex_X_Regions);
  Subtract_CryoRegions_DataHists(Subtract_from.Vertex_Y_Regions,                   input.Vertex_Y_Regions);
  Subtract_CryoRegions_DataHists(Subtract_from.Vertex_Z_Regions,                   input.Vertex_Z_Regions);
  Subtract_CryoRegions_DataHists(Subtract_from.Vertex_Z_Regions_RCut,              input.Vertex_Z_Regions_RCut);
  Subtract_CryoRegions_DataHists(Subtract_from.Vertex_R_Regions,                   input.Vertex_R_Regions);
  //Subtract_CryoRegions_DataHists(Subtract_from.Vertex_RR_Regions,                  input.Vertex_RR_Regions);
  Subtract_CryoRegions_DataHists(Subtract_from.NearestWall_Regions,                input.NearestWall_Regions);
  Subtract_CryoRegions_DataHists(Subtract_from.DistanceUpstreamCap_Regions,        input.DistanceUpstreamCap_Regions);
  Subtract_CryoRegions_DataHists(Subtract_from.DistanceDownstreamCap_Regions,      input.DistanceDownstreamCap_Regions);
  Subtract_CryoRegions_DataHists(Subtract_from.DistanceUpstreamCap_Regions_RCut,   input.DistanceUpstreamCap_Regions_RCut);
  Subtract_CryoRegions_DataHists(Subtract_from.DistanceDownstreamCap_Regions_RCut, input.DistanceDownstreamCap_Regions_RCut);
}

void Convolution_Tool::Subtract_DataHists_Regions_Vertex(ConvolutionShiftMap &Subtract_from , ConvolutionShiftMap &input)
{
  Subtract_CryoRegions_DataHists(Subtract_from.Vertex_X_Regions,                   input.Vertex_X_Regions);
  Subtract_CryoRegions_DataHists(Subtract_from.Vertex_Y_Regions,                   input.Vertex_Y_Regions);
  Subtract_CryoRegions_DataHists(Subtract_from.Vertex_Z_Regions,                   input.Vertex_Z_Regions);
  Subtract_CryoRegions_DataHists(Subtract_from.Vertex_R_Regions,                   input.Vertex_R_Regions);

  Subtract_CryoRegions_DataHists(Subtract_from.Vertex_TRUE_X_Regions,                   input.Vertex_TRUE_X_Regions);
  Subtract_CryoRegions_DataHists(Subtract_from.Vertex_TRUE_Y_Regions,                   input.Vertex_TRUE_Y_Regions);
  Subtract_CryoRegions_DataHists(Subtract_from.Vertex_TRUE_Z_Regions,                   input.Vertex_TRUE_Z_Regions);
  Subtract_CryoRegions_DataHists(Subtract_from.Vertex_TRUE_R_Regions,                   input.Vertex_TRUE_R_Regions);


}


void Convolution_Tool::Subtract_DataHists_Regions_TRUEVertex(ConvolutionShiftMap &Subtract_from , ConvolutionShiftMap &input)
{

  Subtract_CryoRegions_DataHists(Subtract_from.Vertex_TRUE_X_Regions,                   input.Vertex_TRUE_X_Regions);
  Subtract_CryoRegions_DataHists(Subtract_from.Vertex_TRUE_Y_Regions,                   input.Vertex_TRUE_Y_Regions);
  Subtract_CryoRegions_DataHists(Subtract_from.Vertex_TRUE_Z_Regions,                   input.Vertex_TRUE_Z_Regions);
  Subtract_CryoRegions_DataHists(Subtract_from.Vertex_TRUE_R_Regions,                   input.Vertex_TRUE_R_Regions);


}


void Convolution_Tool::Subtract_DataHists_Regions_Vars(ConvolutionShiftMap &Subtract_from , ConvolutionShiftMap &input)
{

  Subtract_CryoRegions_DataHists(Subtract_from.muonPT_Regions, input.muonPT_Regions ) ;
  Subtract_CryoRegions_DataHists(Subtract_from.muonPZ_Regions, input.muonPZ_Regions ) ;
  Subtract_CryoRegions_DataHists(Subtract_from.muonE_Regions, input.muonE_Regions ) ;
  Subtract_CryoRegions_DataHists(Subtract_from.muontheta_Regions, input.muontheta_Regions ) ;
  Subtract_CryoRegions_DataHists(Subtract_from.muonDOCA_Regions, input.muonDOCA_Regions ) ;
  Subtract_CryoRegions_DataHists(Subtract_from.NearestWall_Regions, input.NearestWall_Regions ) ;
  Subtract_CryoRegions_DataHists(Subtract_from.recoilDOCA_Regions, input.recoilDOCA_Regions ) ;
  Subtract_CryoRegions_DataHists(Subtract_from.recoilAngle_Regions, input.recoilAngle_Regions ) ;
  Subtract_CryoRegions_DataHists(Subtract_from.tracklength_Regions, input.tracklength_Regions ) ;
}




void Convolution_Tool::Subtract_RecoHists(Convolution_hist &Subtract_from , Convolution_hist &input ){
  Subtract_from.MnvH1D_mc_Reco->Add(input.MnvH1D_mc_Reco, -1.0);
}

void Convolution_Tool::Subtract_CryoRegions_RecoHists(Convolution_CryoRegions &Subtract_from , Convolution_CryoRegions &input ){
  Subtract_RecoHists(Subtract_from.Upstream,    input.Upstream );
  Subtract_RecoHists(Subtract_from.Barrel,      input.Barrel );
  Subtract_RecoHists(Subtract_from.Downstream,  input.Downstream );
  Subtract_RecoHists(Subtract_from.Concave,     input.Concave );
}

void Convolution_Tool::Subtract_RecoHists_Total(ConvolutionShiftMap &Subtract_from , ConvolutionShiftMap &input)
{
  Subtract_RecoHists(Subtract_from.Vertex_X_TotalRegion,                   input.Vertex_X_TotalRegion);
  Subtract_RecoHists(Subtract_from.Vertex_Y_TotalRegion,                   input.Vertex_Y_TotalRegion);
  Subtract_RecoHists(Subtract_from.Vertex_R_TotalRegion,                   input.Vertex_R_TotalRegion);
  //Subtract_RecoHists(Subtract_from.Vertex_RR_TotalRegion,                   input.Vertex_RR_TotalRegion);
  Subtract_RecoHists(Subtract_from.Vertex_Z_TotalRegion,                   input.Vertex_Z_TotalRegion);
  Subtract_RecoHists(Subtract_from.Vertex_Z_TotalRegion_RCut,              input.Vertex_Z_TotalRegion_RCut);
  Subtract_RecoHists(Subtract_from.NearestWall_TotalRegion,                input.NearestWall_TotalRegion);
  Subtract_RecoHists(Subtract_from.DistanceUpstreamCap_TotalRegion,        input.DistanceUpstreamCap_TotalRegion);
  Subtract_RecoHists(Subtract_from.DistanceDownstreamCap_TotalRegion,      input.DistanceDownstreamCap_TotalRegion);
  Subtract_RecoHists(Subtract_from.DistanceUpstreamCap_TotalRegion_RCut,   input.DistanceUpstreamCap_TotalRegion_RCut);
  Subtract_RecoHists(Subtract_from.DistanceDownstreamCap_TotalRegion_RCut, input.DistanceDownstreamCap_TotalRegion_RCut);
}

void Convolution_Tool::Subtract_RecoHists_Regions(ConvolutionShiftMap &Subtract_from , ConvolutionShiftMap &input)
{
  Subtract_CryoRegions_RecoHists(Subtract_from.Vertex_X_Regions,                   input.Vertex_X_Regions);
  Subtract_CryoRegions_RecoHists(Subtract_from.Vertex_Y_Regions,                   input.Vertex_Y_Regions);
  Subtract_CryoRegions_RecoHists(Subtract_from.Vertex_Z_Regions,                   input.Vertex_Z_Regions);
  Subtract_CryoRegions_RecoHists(Subtract_from.Vertex_Z_Regions_RCut,              input.Vertex_Z_Regions_RCut);
  Subtract_CryoRegions_RecoHists(Subtract_from.Vertex_R_Regions,                   input.Vertex_R_Regions);
  //Subtract_CryoRegions_RecoHists(Subtract_from.Vertex_RR_Regions,                  input.Vertex_RR_Regions);
  Subtract_CryoRegions_RecoHists(Subtract_from.NearestWall_Regions,                input.NearestWall_Regions);
  Subtract_CryoRegions_RecoHists(Subtract_from.DistanceUpstreamCap_Regions,        input.DistanceUpstreamCap_Regions);
  Subtract_CryoRegions_RecoHists(Subtract_from.DistanceDownstreamCap_Regions,      input.DistanceDownstreamCap_Regions);
  Subtract_CryoRegions_RecoHists(Subtract_from.DistanceUpstreamCap_Regions_RCut,   input.DistanceUpstreamCap_Regions_RCut);
  Subtract_CryoRegions_RecoHists(Subtract_from.DistanceDownstreamCap_Regions_RCut, input.DistanceDownstreamCap_Regions_RCut);
}



void Convolution_Tool::Subtract_TrueHists(Convolution_hist &Subtract_from , Convolution_hist &input ){
  Subtract_from.MnvH1D_mc_TRUTH->Add(input.MnvH1D_mc_TRUTH, -1.0);
}
void Convolution_Tool::Subtract_TrueConvoluedHists(Convolution_hist &Subtract_from , Convolution_hist &input, int ind ){
  Subtract_from.MnvH1D_mc_Convoluted[ind]->Add(input.MnvH1D_mc_Convoluted[ind], -1.0);
}
void Convolution_Tool::Subtract_Material_ConvoluedHists(Convolution_hist &Subtract_from , Convolution_hist &input, int ind ){

Subtract_from.MnvH1D_mc_Convoluted_Helium[ind]->Add(input.MnvH1D_mc_Convoluted_Helium[ind], -1.0);
Subtract_from.MnvH1D_mc_Convoluted_Aluminium[ind]->Add(input.MnvH1D_mc_Convoluted_Aluminium[ind], -1.0);
Subtract_from.MnvH1D_mc_Convoluted_Carbon[ind]->Add(input.MnvH1D_mc_Convoluted_Carbon[ind], -1.0);
Subtract_from.MnvH1D_mc_Convoluted_Iron[ind]->Add(input.MnvH1D_mc_Convoluted_Iron[ind], -1.0);
Subtract_from.MnvH1D_mc_Convoluted_Lead[ind]->Add(input.MnvH1D_mc_Convoluted_Lead[ind], -1.0);
Subtract_from.MnvH1D_mc_Convoluted_Other[ind]->Add(input.MnvH1D_mc_Convoluted_Other[ind], -1.0);
}


void Convolution_Tool::Subtract_CryoRegions_Material_Hists(Convolution_CryoRegions &Subtract_from , Convolution_CryoRegions &input , int ind ){
  Subtract_Material_ConvoluedHists(Subtract_from.Upstream,    input.Upstream ,ind);
  Subtract_Material_ConvoluedHists(Subtract_from.Barrel,      input.Barrel ,ind);
  Subtract_Material_ConvoluedHists(Subtract_from.Downstream,  input.Downstream ,ind);
  Subtract_Material_ConvoluedHists(Subtract_from.Concave,     input.Concave ,ind);
}

void Convolution_Tool::Subtract_Convolution_Material_Hists_Regions(ConvolutionShiftMap &Subtract_from , ConvolutionShiftMap &input, int ind)
{
  Subtract_CryoRegions_Material_Hists(Subtract_from.Vertex_X_Regions,  input.Vertex_X_Regions, ind);
  Subtract_CryoRegions_Material_Hists(Subtract_from.Vertex_Y_Regions,  input.Vertex_Y_Regions, ind);
  Subtract_CryoRegions_Material_Hists(Subtract_from.Vertex_Z_Regions,  input.Vertex_Z_Regions, ind);
  Subtract_CryoRegions_Material_Hists(Subtract_from.Vertex_R_Regions,  input.Vertex_R_Regions, ind);

}

void Convolution_Tool::Subtract_Convolution_Material_Hists_TrueRegions(ConvolutionShiftMap &Subtract_from , ConvolutionShiftMap &input, int ind)
{
  Subtract_CryoRegions_Material_Hists(Subtract_from.Vertex_TRUE_X_Regions,  input.Vertex_TRUE_X_Regions, ind);
  Subtract_CryoRegions_Material_Hists(Subtract_from.Vertex_TRUE_Y_Regions,  input.Vertex_TRUE_Y_Regions, ind);
  Subtract_CryoRegions_Material_Hists(Subtract_from.Vertex_TRUE_Z_Regions,  input.Vertex_TRUE_Z_Regions, ind);
  Subtract_CryoRegions_Material_Hists(Subtract_from.Vertex_TRUE_R_Regions,  input.Vertex_TRUE_R_Regions, ind);

}


void Convolution_Tool::Subtract_Convolution_Material_Hists_Regions_Vars(ConvolutionShiftMap &Subtract_from , ConvolutionShiftMap &input, int ind)
{

  Subtract_CryoRegions_Material_Hists(Subtract_from.muonPT_Regions, input.muonPT_Regions, ind);
  Subtract_CryoRegions_Material_Hists(Subtract_from.muonPZ_Regions, input.muonPZ_Regions, ind);
  Subtract_CryoRegions_Material_Hists(Subtract_from.muonE_Regions, input.muonE_Regions, ind);
  Subtract_CryoRegions_Material_Hists(Subtract_from.muontheta_Regions, input.muontheta_Regions, ind);
  Subtract_CryoRegions_Material_Hists(Subtract_from.muonDOCA_Regions, input.muonDOCA_Regions, ind);
  Subtract_CryoRegions_Material_Hists(Subtract_from.NearestWall_Regions, input.NearestWall_Regions, ind);
  Subtract_CryoRegions_Material_Hists(Subtract_from.recoilDOCA_Regions, input.recoilDOCA_Regions, ind);
  Subtract_CryoRegions_Material_Hists(Subtract_from.recoilAngle_Regions, input.recoilAngle_Regions, ind);
  Subtract_CryoRegions_Material_Hists(Subtract_from.tracklength_Regions, input.tracklength_Regions, ind);

}


void Convolution_Tool::Subtract_Full_Empty(int ind){
if(ind ==0){
Subtract_Convolution_Material_Hists_Regions_Vars(Full_Empty , Empty, 0);
Subtract_Convolution_Material_Hists_Regions(Full_Empty , Empty, 0);
Subtract_Convolution_Material_Hists_TrueRegions(Full_Empty , Empty, 0);

Subtract_DataHists_Regions_Vertex(Full_Empty , Empty);
Subtract_DataHists_Regions_Vars(Full_Empty , Empty);
}

else {
  Subtract_Convolution_Material_Hists_Regions_Vars(Full_Empty , Empty, ind);
  Subtract_Convolution_Material_Hists_Regions(Full_Empty , Empty, ind);
  Subtract_Convolution_Material_Hists_TrueRegions(Full_Empty , Empty, ind);
}




}

void Convolution_Tool::Subtract_Full_Empty_Fiducial(int ind){
if(ind ==0){
Subtract_Convolution_Material_Hists_Regions_Vars(Full_Empty_Fid , Empty_Fid, 0);
Subtract_Convolution_Material_Hists_Regions(Full_Empty_Fid , Empty_Fid, 0);
Subtract_Convolution_Material_Hists_TrueRegions(Full_Empty_Fid , Empty_Fid, 0);
Subtract_DataHists_Regions_Vertex(Full_Empty_Fid , Empty_Fid);
Subtract_DataHists_Regions_Vars(Full_Empty_Fid , Empty_Fid);
}
else{
  Subtract_Convolution_Material_Hists_Regions_Vars(Full_Empty_Fid , Empty_Fid, ind);
  Subtract_Convolution_Material_Hists_Regions(Full_Empty_Fid , Empty_Fid, ind);
  Subtract_Convolution_Material_Hists_TrueRegions(Full_Empty_Fid , Empty_Fid, ind);
}

}





void Convolution_Tool::Subtract_CryoRegions_TRUEHists(Convolution_CryoRegions &Subtract_from , Convolution_CryoRegions &input ){
  Subtract_TrueHists(Subtract_from.Upstream,    input.Upstream );
  Subtract_TrueHists(Subtract_from.Barrel,      input.Barrel );
  Subtract_TrueHists(Subtract_from.Downstream,  input.Downstream );
  Subtract_TrueHists(Subtract_from.Concave,     input.Concave );
}

void Convolution_Tool::Subtract_CryoRegions_TRUEConvolutionHists(Convolution_CryoRegions &Subtract_from , Convolution_CryoRegions &input, int ind ){
  Subtract_TrueConvoluedHists(Subtract_from.Upstream,    input.Upstream,   ind);
  Subtract_TrueConvoluedHists(Subtract_from.Barrel,      input.Barrel,     ind);
  Subtract_TrueConvoluedHists(Subtract_from.Downstream,  input.Downstream, ind);
  Subtract_TrueConvoluedHists(Subtract_from.Concave,     input.Concave,    ind);
}

void Convolution_Tool::Subtract_TRUEConvolutionHists_Total(ConvolutionShiftMap &Subtract_from , ConvolutionShiftMap &input, int ind)
{
  Subtract_TrueConvoluedHists(Subtract_from.Vertex_X_TotalRegion,                   input.Vertex_X_TotalRegion,                   ind);
  Subtract_TrueConvoluedHists(Subtract_from.Vertex_Y_TotalRegion,                   input.Vertex_Y_TotalRegion,                   ind);
  Subtract_TrueConvoluedHists(Subtract_from.Vertex_R_TotalRegion,                   input.Vertex_R_TotalRegion,                   ind);
  //Subtract_TrueConvoluedHists(Subtract_from.Vertex_RR_TotalRegion,                  input.Vertex_RR_TotalRegion,                  ind);
  Subtract_TrueConvoluedHists(Subtract_from.Vertex_Z_TotalRegion,                   input.Vertex_Z_TotalRegion,                   ind);
  Subtract_TrueConvoluedHists(Subtract_from.Vertex_Z_TotalRegion_RCut,              input.Vertex_Z_TotalRegion_RCut,              ind);
  Subtract_TrueConvoluedHists(Subtract_from.NearestWall_TotalRegion,                input.NearestWall_TotalRegion,                ind);
  Subtract_TrueConvoluedHists(Subtract_from.DistanceUpstreamCap_TotalRegion,        input.DistanceUpstreamCap_TotalRegion,        ind);
  Subtract_TrueConvoluedHists(Subtract_from.DistanceDownstreamCap_TotalRegion,      input.DistanceDownstreamCap_TotalRegion,      ind);
  Subtract_TrueConvoluedHists(Subtract_from.DistanceUpstreamCap_TotalRegion_RCut,   input.DistanceUpstreamCap_TotalRegion_RCut,   ind);
  Subtract_TrueConvoluedHists(Subtract_from.DistanceDownstreamCap_TotalRegion_RCut, input.DistanceDownstreamCap_TotalRegion_RCut, ind);
}

void Convolution_Tool::Subtract_TRUEConvolutionHists_Regions(ConvolutionShiftMap &Subtract_from , ConvolutionShiftMap &input, int ind)
{
  Subtract_CryoRegions_TRUEConvolutionHists(Subtract_from.Vertex_X_Regions,                   input.Vertex_X_Regions, ind);
  Subtract_CryoRegions_TRUEConvolutionHists(Subtract_from.Vertex_Y_Regions,                   input.Vertex_Y_Regions, ind);
  Subtract_CryoRegions_TRUEConvolutionHists(Subtract_from.Vertex_Z_Regions,                   input.Vertex_Z_Regions, ind);
  Subtract_CryoRegions_TRUEConvolutionHists(Subtract_from.Vertex_Z_Regions_RCut,              input.Vertex_Z_Regions_RCut, ind);
  Subtract_CryoRegions_TRUEConvolutionHists(Subtract_from.Vertex_R_Regions,                   input.Vertex_R_Regions, ind);
  //Subtract_CryoRegions_TRUEConvolutionHists(Subtract_from.Vertex_RR_Regions,                  input.Vertex_RR_Regions, ind);
  Subtract_CryoRegions_TRUEConvolutionHists(Subtract_from.NearestWall_Regions,                input.NearestWall_Regions, ind);
  Subtract_CryoRegions_TRUEConvolutionHists(Subtract_from.DistanceUpstreamCap_Regions,        input.DistanceUpstreamCap_Regions, ind);
  Subtract_CryoRegions_TRUEConvolutionHists(Subtract_from.DistanceDownstreamCap_Regions,      input.DistanceDownstreamCap_Regions, ind);
  Subtract_CryoRegions_TRUEConvolutionHists(Subtract_from.DistanceUpstreamCap_Regions_RCut,   input.DistanceUpstreamCap_Regions_RCut, ind);
  Subtract_CryoRegions_TRUEConvolutionHists(Subtract_from.DistanceDownstreamCap_Regions_RCut, input.DistanceDownstreamCap_Regions_RCut, ind);
}


void Convolution_Tool::Subtract_TRUEConvolutionHists_Regions_FitVars(ConvolutionShiftMap &Subtract_from , ConvolutionShiftMap &input, int ind)
{
  Subtract_CryoRegions_TRUEConvolutionHists(Subtract_from.Vertex_X_Regions,                   input.Vertex_X_Regions, ind);
  Subtract_CryoRegions_TRUEConvolutionHists(Subtract_from.Vertex_Y_Regions,                   input.Vertex_Y_Regions, ind);
  Subtract_CryoRegions_TRUEConvolutionHists(Subtract_from.Vertex_Z_Regions,                   input.Vertex_Z_Regions, ind);
  Subtract_CryoRegions_TRUEConvolutionHists(Subtract_from.Vertex_R_Regions,                   input.Vertex_R_Regions, ind);

}

void Convolution_Tool::Subtract_TRUEHists_Total(ConvolutionShiftMap &Subtract_from , ConvolutionShiftMap &input)
{
  Subtract_TrueHists(Subtract_from.Vertex_X_TotalRegion,                   input.Vertex_X_TotalRegion);
  Subtract_TrueHists(Subtract_from.Vertex_Y_TotalRegion,                   input.Vertex_Y_TotalRegion);
  Subtract_TrueHists(Subtract_from.Vertex_R_TotalRegion,                   input.Vertex_R_TotalRegion);
  //Subtract_TrueHists(Subtract_from.Vertex_RR_TotalRegion,                  input.Vertex_RR_TotalRegion);
  Subtract_TrueHists(Subtract_from.Vertex_Z_TotalRegion,                   input.Vertex_Z_TotalRegion);
  Subtract_TrueHists(Subtract_from.Vertex_Z_TotalRegion_RCut,              input.Vertex_Z_TotalRegion_RCut);
  Subtract_TrueHists(Subtract_from.NearestWall_TotalRegion,                input.NearestWall_TotalRegion);
  Subtract_TrueHists(Subtract_from.DistanceUpstreamCap_TotalRegion,        input.DistanceUpstreamCap_TotalRegion);
  Subtract_TrueHists(Subtract_from.DistanceDownstreamCap_TotalRegion,      input.DistanceDownstreamCap_TotalRegion);
  Subtract_TrueHists(Subtract_from.DistanceUpstreamCap_TotalRegion_RCut,   input.DistanceUpstreamCap_TotalRegion_RCut);
  Subtract_TrueHists(Subtract_from.DistanceDownstreamCap_TotalRegion_RCut, input.DistanceDownstreamCap_TotalRegion_RCut);
}
void Convolution_Tool::Subtract_TRUEHists_Regions(ConvolutionShiftMap &Subtract_from , ConvolutionShiftMap &input)
{
  Subtract_CryoRegions_TRUEHists(Subtract_from.Vertex_X_Regions,                   input.Vertex_X_Regions);
  Subtract_CryoRegions_TRUEHists(Subtract_from.Vertex_Y_Regions,                   input.Vertex_Y_Regions);
  Subtract_CryoRegions_TRUEHists(Subtract_from.Vertex_Z_Regions,                   input.Vertex_Z_Regions);
  Subtract_CryoRegions_TRUEHists(Subtract_from.Vertex_Z_Regions_RCut,              input.Vertex_Z_Regions_RCut);
  Subtract_CryoRegions_TRUEHists(Subtract_from.Vertex_R_Regions,                   input.Vertex_R_Regions);
  //Subtract_CryoRegions_TRUEHists(Subtract_from.Vertex_RR_Regions,                  input.Vertex_RR_Regions);
  Subtract_CryoRegions_TRUEHists(Subtract_from.NearestWall_Regions,                input.NearestWall_Regions);
  Subtract_CryoRegions_TRUEHists(Subtract_from.DistanceUpstreamCap_Regions,        input.DistanceUpstreamCap_Regions);
  Subtract_CryoRegions_TRUEHists(Subtract_from.DistanceDownstreamCap_Regions,      input.DistanceDownstreamCap_Regions);
  Subtract_CryoRegions_TRUEHists(Subtract_from.DistanceUpstreamCap_Regions_RCut,   input.DistanceUpstreamCap_Regions_RCut);
  Subtract_CryoRegions_TRUEHists(Subtract_from.DistanceDownstreamCap_Regions_RCut, input.DistanceDownstreamCap_Regions_RCut);
}







void Convolution_Tool::input_pdfLabel(std::string input_name){
globalpdf_label = input_name;
globalpdf_labelwithpdf = input_name+ ".pdf";
}

void Convolution_Tool::Plot_Eventdistrubution
(MnvH1D *hist_Data,
  MnvH1D *hist_RecoMC,
  MnvH1D *hist_TRUTH_Convolution, MnvH1D *hist_TRUTH,
  std::string Playlist_name,
  std::string histotitle,
  std::string playlist_status,
  std::string xaxislabel,
  std::string yaxislabel,
  double Ymax, double Convoluted_Mean,
  double Convoluted_stddev,
  double &ChiSqrt_Truth_toReco,
  double &ChiSqrt_Truth_toData,
  double &ChiSqrt_Reco_toData)
  {

     char playlist_status_char[playlist_status.length()+1];
     strcpy(playlist_status_char,playlist_status.c_str());

     char Playlist_name_char[Playlist_name.length()+1];
     strcpy(Playlist_name_char,Playlist_name.c_str());

     char histotitle_char[histotitle.length()+1];
     strcpy(histotitle_char,histotitle.c_str());

     char xaxislabel_char[xaxislabel.length()+1];
     strcpy(xaxislabel_char,xaxislabel.c_str());

     char yaxislabel_char[yaxislabel.length()+1];
     strcpy(yaxislabel_char,yaxislabel.c_str());

     Draw_Data_RECO_TRUTH_Hist_withConvolution_fromPointers(
      hist_Data,
      hist_RecoMC,
      hist_TRUTH_Convolution,
      hist_TRUTH,
      Playlist_name_char,
      globalpdf_label,
      histotitle_char,
      playlist_status_char,
      xaxislabel_char,
      yaxislabel_char,
      global_DoBinwidthNorm,
      global_MakeXaxisLOG,
      Ymax,
      Convoluted_Mean,
      Convoluted_stddev,
      ChiSqrt_Truth_toReco,
      ChiSqrt_Truth_toData,
      ChiSqrt_Reco_toData );

}


void Convolution_Tool::Plot_Eventdistrubution_RECOCol(
  MnvH1D *hist_Data,
  MnvH1D *hist_RECOMC,
  MnvH1D *hist_RECO_Convolution,
  MnvH1D *hist_TRUTH,
  std::string Playlist_name,
  std::string histotitle,
  std::string playlist_status,
  std::string xaxislabel,
  std::string yaxislabel,
  double Ymax,
  double Convoluted_Mean,
  double Convoluted_stddev,
  double &ChiSqrt_ConvolRECOtoRECO,
  double &ChiSqrt_ConvolRECOtoData,
  double &ChiSqrt_RECO_toData)
  {

     char playlist_status_char[playlist_status.length()+1];
     strcpy(playlist_status_char,playlist_status.c_str());

     char Playlist_name_char[Playlist_name.length()+1];
     strcpy(Playlist_name_char,Playlist_name.c_str());

     char histotitle_char[histotitle.length()+1];
     strcpy(histotitle_char,histotitle.c_str());

     char xaxislabel_char[xaxislabel.length()+1];
     strcpy(xaxislabel_char,xaxislabel.c_str());

     char yaxislabel_char[yaxislabel.length()+1];
     strcpy(yaxislabel_char,yaxislabel.c_str());


     Draw_Data_RECO_TRUTH_Hist_withConvolutionRECO_fromPointers(
       hist_Data,
       hist_RECOMC,
       hist_RECO_Convolution,
       hist_TRUTH,
       global_MakeAreaNorm_todata,
       Playlist_name_char,
       globalpdf_label,
       histotitle_char,
       playlist_status_char,
       xaxislabel_char,
       yaxislabel_char,
       global_DoBinwidthNorm,
       global_MakeXaxisLOG,
       Ymax,
       Convoluted_Mean,
       Convoluted_stddev,
       ChiSqrt_ConvolRECOtoRECO,
       ChiSqrt_ConvolRECOtoData,
        ChiSqrt_RECO_toData);


}

void Convolution_Tool::Plot_Eventdistrubution_RECOCol(
  MnvH1D *hist_Data,
  MnvH1D *hist_RECOMC,
  MnvH1D *hist_RECO_Convolution,
  MnvH1D *hist_TRUTH,
  std::string Playlist_name,
  std::string histotitle,
  std::string playlist_status,
  std::string xaxislabel,
  std::string yaxislabel,
  double Ymax,
  double Convoluted_MeanF,
  double Convoluted_stddevF,
  double Convoluted_MeanE,
  double Convoluted_stddevE,
  double &ChiSqrt_ConvolRECOtoRECO,
  double &ChiSqrt_ConvolRECOtoData,
  double &ChiSqrt_RECO_toData)
  {

     char playlist_status_char[playlist_status.length()+1];
     strcpy(playlist_status_char,playlist_status.c_str());

     char Playlist_name_char[Playlist_name.length()+1];
     strcpy(Playlist_name_char,Playlist_name.c_str());

     char histotitle_char[histotitle.length()+1];
     strcpy(histotitle_char,histotitle.c_str());

     char xaxislabel_char[xaxislabel.length()+1];
     strcpy(xaxislabel_char,xaxislabel.c_str());

     char yaxislabel_char[yaxislabel.length()+1];
     strcpy(yaxislabel_char,yaxislabel.c_str());


     Draw_Data_RECO_TRUTH_Hist_withConvolutionRECO_fromPointers(
       hist_Data,
       hist_RECOMC,
       hist_RECO_Convolution,
       hist_TRUTH,
       global_MakeAreaNorm_todata,
       Playlist_name_char,
       globalpdf_label,
       histotitle_char,
       playlist_status_char,
       xaxislabel_char,
       yaxislabel_char,
       global_DoBinwidthNorm,
       global_MakeXaxisLOG,
       Ymax,
       Convoluted_MeanF,
       Convoluted_stddevF,
       Convoluted_MeanE,
       Convoluted_stddevE,
       ChiSqrt_ConvolRECOtoRECO,
       ChiSqrt_ConvolRECOtoData,
        ChiSqrt_RECO_toData);


}


void Convolution_Tool::Plot_Eventdistrubution_RECOCol(
  Convolution_hist &histsInput,
  std::string Playlist_name,
  std::string histotitle,
  std::string playlist_status,
  double Ymax, double Convoluted_Mean,
  double Convoluted_stddev,
  double &ChiSqrt_ConvolRECOtoRECO,
  double &ChiSqrt_ConvolRECOtoData,
  double &ChiSqrt_RECO_toData  ){


    Plot_Eventdistrubution_RECOCol(histsInput.MnvH1D_data,
      histsInput.MnvH1D_mc_Reco,
      histsInput.MnvH1D_mc_Convoluted[1],
      histsInput.MnvH1D_mc_TRUTH,
      Playlist_name,
      histotitle,
      playlist_status,
      histsInput.Xaxis_Title,
      "mm",  Ymax,  Convoluted_Mean,  Convoluted_stddev,
      ChiSqrt_ConvolRECOtoRECO,
      ChiSqrt_ConvolRECOtoData,
      ChiSqrt_RECO_toData);

    }

    void Convolution_Tool::Plot_Eventdistrubution_RECOCol(
      Convolution_hist &histsInput,
      std::string Playlist_name,
      std::string histotitle,
      std::string playlist_status,
      double Ymax,
      double Convoluted_MeanF,
      double Convoluted_stddevF,
      double Convoluted_MeanE,
      double Convoluted_stddevE,
      double &ChiSqrt_ConvolRECOtoRECO,
      double &ChiSqrt_ConvolRECOtoData,
      double &ChiSqrt_RECO_toData  ){


        Plot_Eventdistrubution_RECOCol(histsInput.MnvH1D_data,
          histsInput.MnvH1D_mc_Reco,
          histsInput.MnvH1D_mc_Convoluted[1],
          histsInput.MnvH1D_mc_TRUTH,
          Playlist_name,
          histotitle,
          playlist_status,
          histsInput.Xaxis_Title,
          "mm",  Ymax,  Convoluted_MeanF,  Convoluted_stddevF,
          Convoluted_MeanE,  Convoluted_stddevE,
          ChiSqrt_ConvolRECOtoRECO,
          ChiSqrt_ConvolRECOtoData,
          ChiSqrt_RECO_toData);

        }


void Convolution_Tool::Plot_Eventdistrubution(
  Convolution_hist &histsInput,
  std::string Playlist_name,
  std::string histotitle,
  std::string playlist_status,
  double Ymax, double Convoluted_Mean,
  double Convoluted_stddev, int ind,
   double &ChiSqrt_Truth_toReco,
   double &ChiSqrt_Truth_toData,
   double &ChiSqrt_Reco_toData)
  {

    Plot_Eventdistrubution(histsInput.MnvH1D_data,
      histsInput.MnvH1D_mc_Reco,
      histsInput.MnvH1D_mc_Convoluted[ind],
      histsInput.MnvH1D_mc_TRUTH,
      Playlist_name,
      histotitle,
      playlist_status,
      histsInput.Xaxis_Title,
      "mm",  Ymax,  Convoluted_Mean,  Convoluted_stddev,
      ChiSqrt_Truth_toReco,
      ChiSqrt_Truth_toData,
      ChiSqrt_Reco_toData);

}

void Convolution_Tool::Plot_Eventdistrubution_Regions(Convolution_CryoRegions &histsInput,
   std::string Playlist_name,  std::string histotitle, std::string playlist_status,
  double Ymax, double Convoluted_Mean, double Convoluted_stddev, int ind)
  {
    double chisqrt1 = 10;
    double chisqrt2 = 10;
    double chisqrt3 = 10;


std::string Title = "[USCap]" + histotitle;

Plot_Eventdistrubution(histsInput.Upstream.MnvH1D_data,
      histsInput.Upstream.MnvH1D_mc_Reco,
      histsInput.Upstream.MnvH1D_mc_Convoluted[ind],
      histsInput.Upstream.MnvH1D_mc_TRUTH,
      Playlist_name,
      Title,
      playlist_status,
      histsInput.Upstream.Xaxis_Title,
      "mm",  Ymax,  Convoluted_Mean,  Convoluted_stddev,
      chisqrt1,
      chisqrt2,
      chisqrt3);

 Title = "[barrel]" + histotitle;

Plot_Eventdistrubution(histsInput.Barrel.MnvH1D_data,
  histsInput.Barrel.MnvH1D_mc_Reco,
  histsInput.Barrel.MnvH1D_mc_Convoluted[ind],
  histsInput.Barrel.MnvH1D_mc_TRUTH,
  Playlist_name,
  Title,
  playlist_status,
  histsInput.Barrel.Xaxis_Title,
  "mm",  Ymax,  Convoluted_Mean,  Convoluted_stddev,
  chisqrt1,
  chisqrt2,
  chisqrt3);

 Title = "[DSCap]" + histotitle;

Plot_Eventdistrubution(histsInput.Downstream.MnvH1D_data,
  histsInput.Downstream.MnvH1D_mc_Reco,
  histsInput.Downstream.MnvH1D_mc_Convoluted[ind],
  histsInput.Downstream.MnvH1D_mc_TRUTH,
  Playlist_name,
  Title,
  playlist_status,
  histsInput.Downstream.Xaxis_Title,
  "mm",  Ymax,  Convoluted_Mean,  Convoluted_stddev,
  chisqrt1,
  chisqrt2,
  chisqrt3);

 Title = "[DSConcave]" + histotitle;

Plot_Eventdistrubution(histsInput.Concave.MnvH1D_data,
  histsInput.Concave.MnvH1D_mc_Reco,
  histsInput.Concave.MnvH1D_mc_Convoluted[ind],
  histsInput.Concave.MnvH1D_mc_TRUTH,
  Playlist_name,
  Title,
  playlist_status,
  histsInput.Concave.Xaxis_Title,
  "mm",  Ymax,  Convoluted_Mean,  Convoluted_stddev,
  chisqrt1,
  chisqrt2,
  chisqrt3);



}

void Convolution_Tool::Plot_ConvolRECO_Eventdistrubution_Regions(
  Convolution_CryoRegions &histsInput,
   std::string Playlist_name,
    std::string histotitle,
    std::string playlist_status,
  double Ymax, double Convoluted_Mean, double Convoluted_stddev)
  {
    double chisqrt1 = 10;
    double chisqrt2 = 10;
    double chisqrt3 = 10;

std::string Title = "[USCap]" + histotitle;

Plot_Eventdistrubution_RECOCol(histsInput.Upstream.MnvH1D_data,
      histsInput.Upstream.MnvH1D_mc_Reco,
      histsInput.Upstream.MnvH1D_mc_Convoluted[1],
      histsInput.Upstream.MnvH1D_mc_TRUTH,
      Playlist_name,
      Title,
      playlist_status,
      histsInput.Upstream.Xaxis_Title,
      "mm",  Ymax,  Convoluted_Mean,  Convoluted_stddev,
      chisqrt1,
      chisqrt2,
      chisqrt3);

 Title = "[barrel]" + histotitle;

Plot_Eventdistrubution_RECOCol(histsInput.Barrel.MnvH1D_data,
  histsInput.Barrel.MnvH1D_mc_Reco,
  histsInput.Barrel.MnvH1D_mc_Convoluted[1],
  histsInput.Barrel.MnvH1D_mc_TRUTH,
  Playlist_name,
  Title,
  playlist_status,
  histsInput.Barrel.Xaxis_Title,
  "mm",  Ymax,  Convoluted_Mean,  Convoluted_stddev,
  chisqrt1,
  chisqrt2,
  chisqrt3);

 Title = "[DSCap]" + histotitle;

Plot_Eventdistrubution_RECOCol(histsInput.Downstream.MnvH1D_data,
  histsInput.Downstream.MnvH1D_mc_Reco,
  histsInput.Downstream.MnvH1D_mc_Convoluted[1],
  histsInput.Downstream.MnvH1D_mc_TRUTH,
  Playlist_name,
  Title,
  playlist_status,
  histsInput.Downstream.Xaxis_Title,
  "mm",  Ymax,  Convoluted_Mean,  Convoluted_stddev,
  chisqrt1,
  chisqrt2,
  chisqrt3);

 Title = "[DSConcave]" + histotitle;

Plot_Eventdistrubution_RECOCol(histsInput.Concave.MnvH1D_data,
  histsInput.Concave.MnvH1D_mc_Reco,
  histsInput.Concave.MnvH1D_mc_Convoluted[1],
  histsInput.Concave.MnvH1D_mc_TRUTH,
  Playlist_name,
  Title,
  playlist_status,
  histsInput.Concave.Xaxis_Title,
  "mm",  Ymax,  Convoluted_Mean,  Convoluted_stddev,
  chisqrt1,
  chisqrt2,
  chisqrt3);



}

void Convolution_Tool::Plot_ConvolRECO_Eventdistrubution_Regions(
  Convolution_CryoRegions &histsInput,
  std::string Playlist_name,
  std::string histotitle,
  std::string playlist_status,
  double Ymax, double Convoluted_Mean_USCap, double Convoluted_stddev_USCap,
  double Convoluted_Mean_barrel, double Convoluted_stddev_barrel,
  double Convoluted_Mean_DSCap, double Convoluted_stddev_DSCap,
  double Convoluted_Mean_concave, double Convoluted_stddev_concave)
  {
    double chisqrt1 = 10;
    double chisqrt2 = 10;
    double chisqrt3 = 10;

std::string Title = "[USCap]" + histotitle;

Plot_Eventdistrubution_RECOCol(histsInput.Upstream.MnvH1D_data,
      histsInput.Upstream.MnvH1D_mc_Reco,
      histsInput.Upstream.MnvH1D_mc_Convoluted[1],
      histsInput.Upstream.MnvH1D_mc_TRUTH,
      Playlist_name,
      Title,
      playlist_status,
      histsInput.Upstream.Xaxis_Title,
      "mm",  Ymax,  Convoluted_Mean_USCap,  Convoluted_stddev_USCap,
      chisqrt1,
      chisqrt2,
      chisqrt3);

 Title = "[barrel]" + histotitle;

Plot_Eventdistrubution_RECOCol(histsInput.Barrel.MnvH1D_data,
  histsInput.Barrel.MnvH1D_mc_Reco,
  histsInput.Barrel.MnvH1D_mc_Convoluted[1],
  histsInput.Barrel.MnvH1D_mc_TRUTH,
  Playlist_name,
  Title,
  playlist_status,
  histsInput.Barrel.Xaxis_Title,
  "mm",  Ymax,  Convoluted_Mean_barrel,  Convoluted_stddev_barrel,
  chisqrt1,
  chisqrt2,
  chisqrt3);

 Title = "[DSCap]" + histotitle;

Plot_Eventdistrubution_RECOCol(histsInput.Downstream.MnvH1D_data,
  histsInput.Downstream.MnvH1D_mc_Reco,
  histsInput.Downstream.MnvH1D_mc_Convoluted[1],
  histsInput.Downstream.MnvH1D_mc_TRUTH,
  Playlist_name,
  Title,
  playlist_status,
  histsInput.Downstream.Xaxis_Title,
  "mm",  Ymax,  Convoluted_Mean_DSCap,  Convoluted_stddev_DSCap,
  chisqrt1,
  chisqrt2,
  chisqrt3);

 Title = "[DSConcave]" + histotitle;

Plot_Eventdistrubution_RECOCol(histsInput.Concave.MnvH1D_data,
  histsInput.Concave.MnvH1D_mc_Reco,
  histsInput.Concave.MnvH1D_mc_Convoluted[1],
  histsInput.Concave.MnvH1D_mc_TRUTH,
  Playlist_name,
  Title,
  playlist_status,
  histsInput.Concave.Xaxis_Title,
  "mm",  Ymax,  Convoluted_Mean_concave,  Convoluted_stddev_concave,
  chisqrt1,
  chisqrt2,
  chisqrt3);



}

void Convolution_Tool::Plot_Full(double Convoluted_Mean, double Convoluted_stddev){

  Plot_EventDistrubution_TotalRegion(Full,"Combined", "Full",  Convoluted_Mean,  Convoluted_stddev, 0);
  Plot_EventDistrubution_TotalRegion(Empty,"Combined", "Empty",  Convoluted_Mean,  Convoluted_stddev, 0);
  Plot_EventDistrubution_TotalRegion(Full_Empty,"Combined", "F-E",  Convoluted_Mean,  Convoluted_stddev, 0);

}

void Convolution_Tool::Plot_Full_ConvolRECO(double Convoluted_Mean, double Convoluted_stddev){
std::cout<<"Ploting FUll "<<std::endl;
  Plot_EventDistrubution_ConvolRECO_TotalRegion(Full,      "Combined", "Full",  Convoluted_Mean,  Convoluted_stddev, 1);
  std::cout<<"Ploting Empty "<<std::endl;
  Plot_EventDistrubution_ConvolRECO_TotalRegion(Empty,     "Combined", "Empty",  Convoluted_Mean,  Convoluted_stddev, 1);
  std::cout<<"Ploting FUll - Empty "<<std::endl;
  Plot_EventDistrubution_ConvolRECO_TotalRegion(Full_Empty,"Combined", "F-E",  Convoluted_Mean,  Convoluted_stddev, 1);

}


void Convolution_Tool::Plot_EmptyOnly_ConvolRECO(double Convoluted_Mean, double Convoluted_stddev){
  std::cout<<"Ploting Empty "<<std::endl;
  Plot_EventDistrubution_ConvolRECO_TotalRegion(Empty,     "Combined", "Empty",  Convoluted_Mean,  Convoluted_stddev, 1);

}


void Convolution_Tool::Plot_FullOnly_ConvolRECO(double Convoluted_Mean, double Convoluted_stddev){
  std::cout<<"Ploting Empty "<<std::endl;
  Plot_EventDistrubution_ConvolRECO_TotalRegion(Full,     "Combined", "Full",  Convoluted_Mean,  Convoluted_stddev, 1);

}


void Convolution_Tool::Plot_EventDistrubution_TotalRegion(ConvolutionShiftMap &inputMap, std::string Playlist_name,
   std::string playlist_status, double Convoluted_Mean, double Convoluted_stddev, int ind){

  double chisqrt1 = 10;
  double chisqrt2 = 10;
  double chisqrt3 = 10;

  std::string Title_WithExtra;

Plot_Eventdistrubution(inputMap.Vertex_X_TotalRegion,   Playlist_name,  PlotTitle , playlist_status,
  1.0,  Convoluted_Mean,  Convoluted_stddev, ind, chisqrt1, chisqrt2, chisqrt3);

Plot_Eventdistrubution(inputMap.Vertex_Y_TotalRegion, Playlist_name,  PlotTitle , playlist_status,
  1.0,  Convoluted_Mean,  Convoluted_stddev, ind, chisqrt1, chisqrt2, chisqrt3);

Plot_Eventdistrubution(inputMap.Vertex_R_TotalRegion, Playlist_name,  PlotTitle , playlist_status,
  1.0,  Convoluted_Mean,  Convoluted_stddev, ind, chisqrt1, chisqrt2, chisqrt3);

//Plot_Eventdistrubution(inputMap.Vertex_RR_TotalRegion, Playlist_name,  PlotTitle , playlist_status,
//  1.0,  Convoluted_Mean,  Convoluted_stddev, ind, chisqrt1, chisqrt2, chisqrt3);

Plot_Eventdistrubution(inputMap.Vertex_Z_TotalRegion, Playlist_name,  PlotTitle , playlist_status,
  1.0,  Convoluted_Mean,  Convoluted_stddev, ind, chisqrt1, chisqrt2, chisqrt3);

Title_WithExtra = "[RCut]  " + PlotTitle;
Plot_Eventdistrubution(inputMap.Vertex_Z_TotalRegion_RCut, Playlist_name,  Title_WithExtra , playlist_status,
  1.0,  Convoluted_Mean,  Convoluted_stddev, ind, chisqrt1, chisqrt2, chisqrt3);

Plot_Eventdistrubution(inputMap.NearestWall_TotalRegion, Playlist_name,  PlotTitle , playlist_status,
  1.0,  Convoluted_Mean,  Convoluted_stddev, ind, chisqrt1, chisqrt2, chisqrt3);

Plot_Eventdistrubution(inputMap.DistanceUpstreamCap_TotalRegion, Playlist_name,  PlotTitle , playlist_status,
  1.0,  Convoluted_Mean,  Convoluted_stddev, ind, chisqrt1, chisqrt2, chisqrt3);

Plot_Eventdistrubution(inputMap.DistanceDownstreamCap_TotalRegion, Playlist_name,  PlotTitle , playlist_status,
  1.0,  Convoluted_Mean,  Convoluted_stddev, ind, chisqrt1, chisqrt2, chisqrt3);

Plot_Eventdistrubution(inputMap.DistanceUpstreamCap_TotalRegion_RCut, Playlist_name,  Title_WithExtra , playlist_status,
  1.0,  Convoluted_Mean,  Convoluted_stddev, ind, chisqrt1, chisqrt2, chisqrt3);

Plot_Eventdistrubution(inputMap.DistanceDownstreamCap_TotalRegion_RCut, Playlist_name,  Title_WithExtra , playlist_status,
  1.0,  Convoluted_Mean,  Convoluted_stddev, ind, chisqrt1, chisqrt2, chisqrt3);

}

void Convolution_Tool::Plot_EventDistrubution_ConvolRECO_TotalRegion(ConvolutionShiftMap &inputMap, std::string Playlist_name,
   std::string playlist_status, double Convoluted_Mean, double Convoluted_stddev, int ind){

  double chisqrt1 = 10;
  double chisqrt2 = 10;
  double chisqrt3 = 10;

  std::string Title_WithExtra;

Plot_Eventdistrubution_RECOCol(inputMap.Vertex_X_TotalRegion,   Playlist_name,  PlotTitle , playlist_status,
  1.0,  Convoluted_Mean,  Convoluted_stddev,  chisqrt1, chisqrt2, chisqrt3);

Plot_Eventdistrubution_RECOCol(inputMap.Vertex_Y_TotalRegion, Playlist_name,  PlotTitle , playlist_status,
  1.0,  Convoluted_Mean,  Convoluted_stddev,  chisqrt1, chisqrt2, chisqrt3);

Plot_Eventdistrubution_RECOCol(inputMap.Vertex_R_TotalRegion, Playlist_name,  PlotTitle , playlist_status,
  1.0,  Convoluted_Mean,  Convoluted_stddev,  chisqrt1, chisqrt2, chisqrt3);

//Plot_Eventdistrubution(inputMap.Vertex_RR_TotalRegion, Playlist_name,  PlotTitle , playlist_status,
//  1.0,  Convoluted_Mean,  Convoluted_stddev, ind, chisqrt1, chisqrt2, chisqrt3);

Plot_Eventdistrubution_RECOCol(inputMap.Vertex_Z_TotalRegion, Playlist_name,  PlotTitle , playlist_status,
  1.0,  Convoluted_Mean,  Convoluted_stddev,  chisqrt1, chisqrt2, chisqrt3);

Title_WithExtra = "[RCut]  " + PlotTitle;
Plot_Eventdistrubution_RECOCol(inputMap.Vertex_Z_TotalRegion_RCut, Playlist_name,  Title_WithExtra , playlist_status,
  1.0,  Convoluted_Mean,  Convoluted_stddev,  chisqrt1, chisqrt2, chisqrt3);

Plot_Eventdistrubution_RECOCol(inputMap.NearestWall_TotalRegion, Playlist_name,  PlotTitle , playlist_status,
  1.0,  Convoluted_Mean,  Convoluted_stddev,  chisqrt1, chisqrt2, chisqrt3);

Plot_Eventdistrubution_RECOCol(inputMap.DistanceUpstreamCap_TotalRegion, Playlist_name,  PlotTitle , playlist_status,
  1.0,  Convoluted_Mean,  Convoluted_stddev, chisqrt1, chisqrt2, chisqrt3);

Plot_Eventdistrubution_RECOCol(inputMap.DistanceDownstreamCap_TotalRegion, Playlist_name,  PlotTitle , playlist_status,
  1.0,  Convoluted_Mean,  Convoluted_stddev, chisqrt1, chisqrt2, chisqrt3);

Plot_Eventdistrubution_RECOCol(inputMap.DistanceUpstreamCap_TotalRegion_RCut, Playlist_name,  Title_WithExtra , playlist_status,
  1.0,  Convoluted_Mean,  Convoluted_stddev, chisqrt1, chisqrt2, chisqrt3);

Plot_Eventdistrubution_RECOCol(inputMap.DistanceDownstreamCap_TotalRegion_RCut, Playlist_name,  Title_WithExtra , playlist_status,
  1.0,  Convoluted_Mean,  Convoluted_stddev, chisqrt1, chisqrt2, chisqrt3);

}

void Convolution_Tool::Plot_EventDistrubution_ConvolRECO_TotalRegion(ConvolutionShiftMap &inputMap, std::string Playlist_name,
   std::string playlist_status,  BestIndex Index_input, NormalParaFit_Map ZShifts ){

  double chisqrt1 = 10;
  double chisqrt2 = 10;
  double chisqrt3 = 10;

double Convoluted_Mean;
double Convoluted_stddev;

  Index3 inputbest_Chisqrt_X{Index_input.best_Chisqrt_X.i,Index_input.best_Chisqrt_X.j,Index_input.best_Chisqrt_X.k};
  Convoluted_Mean = ZShifts[inputbest_Chisqrt_X].mean;
  Convoluted_stddev = ZShifts[inputbest_Chisqrt_X].stddev;
  std::string Title_WithExtra;

Plot_Eventdistrubution_RECOCol(inputMap.Vertex_X_TotalRegion,   Playlist_name,  PlotTitle , playlist_status,
  1.0,  Convoluted_Mean,  Convoluted_stddev,  chisqrt1, chisqrt2, chisqrt3);

  Index3 inputbest_Chisqrt_Y{Index_input.best_Chisqrt_Y.i,Index_input.best_Chisqrt_Y.j,Index_input.best_Chisqrt_Y.k};
  Convoluted_Mean = ZShifts[inputbest_Chisqrt_Y].mean;
  Convoluted_stddev = ZShifts[inputbest_Chisqrt_Y].stddev;

Plot_Eventdistrubution_RECOCol(inputMap.Vertex_Y_TotalRegion, Playlist_name,  PlotTitle , playlist_status,
  1.0,  Convoluted_Mean,  Convoluted_stddev,  chisqrt1, chisqrt2, chisqrt3);

  Index3 inputbest_Chisqrt_R{Index_input.best_Chisqrt_R.i,Index_input.best_Chisqrt_R.j,Index_input.best_Chisqrt_R.k};
  Convoluted_Mean = ZShifts[inputbest_Chisqrt_R].mean;
  Convoluted_stddev = ZShifts[inputbest_Chisqrt_R].stddev;

Plot_Eventdistrubution_RECOCol(inputMap.Vertex_R_TotalRegion, Playlist_name,  PlotTitle , playlist_status,
  1.0,  Convoluted_Mean,  Convoluted_stddev,  chisqrt1, chisqrt2, chisqrt3);

//Plot_Eventdistrubution(inputMap.Vertex_RR_TotalRegion, Playlist_name,  PlotTitle , playlist_status,
//  1.0,  Convoluted_Mean,  Convoluted_stddev, ind, chisqrt1, chisqrt2, chisqrt3);

Index3 inputbest_Chisqrt_Z{Index_input.best_Chisqrt_Z.i,Index_input.best_Chisqrt_Z.j,Index_input.best_Chisqrt_Z.k};
Convoluted_Mean = ZShifts[inputbest_Chisqrt_Z].mean;
Convoluted_stddev = ZShifts[inputbest_Chisqrt_Z].stddev;

Plot_Eventdistrubution_RECOCol(inputMap.Vertex_Z_TotalRegion, Playlist_name,  PlotTitle , playlist_status,
  1.0,  Convoluted_Mean,  Convoluted_stddev,  chisqrt1, chisqrt2, chisqrt3);

  Index3 inputbest_Chisqrt_Z_RCut{Index_input.best_Chisqrt_Z_RCut.i,Index_input.best_Chisqrt_Z_RCut.j,Index_input.best_Chisqrt_Z_RCut.k};
  Convoluted_Mean = ZShifts[inputbest_Chisqrt_Z_RCut].mean;
  Convoluted_stddev = ZShifts[inputbest_Chisqrt_Z_RCut].stddev;

Title_WithExtra = "[RCut]  " + PlotTitle;
Plot_Eventdistrubution_RECOCol(inputMap.Vertex_Z_TotalRegion_RCut, Playlist_name,  Title_WithExtra , playlist_status,
  1.0,  Convoluted_Mean,  Convoluted_stddev,  chisqrt1, chisqrt2, chisqrt3);

  Index3 inputbest_NearestWall{Index_input.best_Chisqrt_NearestWall.i,Index_input.best_Chisqrt_NearestWall.j,Index_input.best_Chisqrt_NearestWall.k};
  Convoluted_Mean = ZShifts[inputbest_NearestWall].mean;
  Convoluted_stddev = ZShifts[inputbest_NearestWall].stddev;

Plot_Eventdistrubution_RECOCol(inputMap.NearestWall_TotalRegion, Playlist_name,  PlotTitle , playlist_status,
  1.0,  Convoluted_Mean,  Convoluted_stddev,  chisqrt1, chisqrt2, chisqrt3);

  Index3 inputbest_DistancetoUpstreamCap{Index_input.best_Chisqrt_DistancetoUpstreamCap.i,Index_input.best_Chisqrt_DistancetoUpstreamCap.j,Index_input.best_Chisqrt_DistancetoUpstreamCap.k};
  Convoluted_Mean = ZShifts[inputbest_DistancetoUpstreamCap].mean;
  Convoluted_stddev = ZShifts[inputbest_DistancetoUpstreamCap].stddev;

Plot_Eventdistrubution_RECOCol(inputMap.DistanceUpstreamCap_TotalRegion, Playlist_name,  PlotTitle , playlist_status,
  1.0,  Convoluted_Mean,  Convoluted_stddev, chisqrt1, chisqrt2, chisqrt3);

  Index3 inputbest_DistancetoDownstreamCap{Index_input.best_Chisqrt_DistancetoDownstreamCap.i,Index_input.best_Chisqrt_DistancetoDownstreamCap.j,Index_input.best_Chisqrt_DistancetoDownstreamCap.k};
  Convoluted_Mean = ZShifts[inputbest_DistancetoDownstreamCap].mean;
  Convoluted_stddev = ZShifts[inputbest_DistancetoDownstreamCap].stddev;

Plot_Eventdistrubution_RECOCol(inputMap.DistanceDownstreamCap_TotalRegion, Playlist_name,  PlotTitle , playlist_status,
  1.0,  Convoluted_Mean,  Convoluted_stddev, chisqrt1, chisqrt2, chisqrt3);

  Index3 inputbest_DistancetoUpstreamCap_RCut{Index_input.best_Chisqrt_DistancetoUpstreamCap_RCut.i,Index_input.best_Chisqrt_DistancetoUpstreamCap_RCut.j,Index_input.best_Chisqrt_DistancetoUpstreamCap_RCut.k};
  Convoluted_Mean = ZShifts[inputbest_DistancetoUpstreamCap_RCut].mean;
  Convoluted_stddev = ZShifts[inputbest_DistancetoUpstreamCap_RCut].stddev;

Plot_Eventdistrubution_RECOCol(inputMap.DistanceUpstreamCap_TotalRegion_RCut, Playlist_name,  Title_WithExtra , playlist_status,
  1.0,  Convoluted_Mean,  Convoluted_stddev, chisqrt1, chisqrt2, chisqrt3);

  Index3 inputbest_DistancetoDownstreamCap_RCut{Index_input.best_Chisqrt_DistancetoDownstreamCap_RCut.i,Index_input.best_Chisqrt_DistancetoDownstreamCap_RCut.j,Index_input.best_Chisqrt_DistancetoDownstreamCap_RCut.k};
  Convoluted_Mean = ZShifts[inputbest_DistancetoDownstreamCap_RCut].mean;
  Convoluted_stddev = ZShifts[inputbest_DistancetoDownstreamCap_RCut].stddev;

Plot_Eventdistrubution_RECOCol(inputMap.DistanceDownstreamCap_TotalRegion_RCut, Playlist_name,  Title_WithExtra , playlist_status,
  1.0,  Convoluted_Mean,  Convoluted_stddev, chisqrt1, chisqrt2, chisqrt3);

}
//~~~~~~~~~~~~~~~~~~~~~
void Convolution_Tool::Plot_EventDistrubution_ConvolRECO_TotalRegion_F_E(ConvolutionShiftMap &inputMap, std::string Playlist_name,
   std::string playlist_status,  BestIndex Index_input_Full, BestIndex Index_input_Empty, NormalParaFit_Map ZShifts ){

  double chisqrt1 = 10;
  double chisqrt2 = 10;
  double chisqrt3 = 10;

double Convoluted_MeanF;
double Convoluted_stddevF;

double Convoluted_MeanE;
double Convoluted_stddevE;

  Index3 inputbest_Chisqrt_XFULL{Index_input_Full.best_Chisqrt_X.i,Index_input_Full.best_Chisqrt_X.j,Index_input_Full.best_Chisqrt_X.k};
  Convoluted_MeanF = ZShifts[inputbest_Chisqrt_XFULL].mean;
  Convoluted_stddevF = ZShifts[inputbest_Chisqrt_XFULL].stddev;

  Index3 inputbest_Chisqrt_XEmpty{Index_input_Empty.best_Chisqrt_X.i,Index_input_Empty.best_Chisqrt_X.j,Index_input_Empty.best_Chisqrt_X.k};
  Convoluted_MeanE = ZShifts[inputbest_Chisqrt_XEmpty].mean;
  Convoluted_stddevE = ZShifts[inputbest_Chisqrt_XEmpty].stddev;

  std::string Title_WithExtra;

Plot_Eventdistrubution_RECOCol(inputMap.Vertex_X_TotalRegion,   Playlist_name,  PlotTitle , playlist_status,
  1.0,  Convoluted_MeanF,  Convoluted_stddevF, Convoluted_MeanE,  Convoluted_stddevE,  chisqrt1, chisqrt2, chisqrt3);

  Index3 inputbest_Chisqrt_Y_Full{Index_input_Full.best_Chisqrt_Y.i,Index_input_Full.best_Chisqrt_Y.j,Index_input_Full.best_Chisqrt_Y.k};
  Convoluted_MeanF = ZShifts[inputbest_Chisqrt_Y_Full].mean;
  Convoluted_stddevF = ZShifts[inputbest_Chisqrt_Y_Full].stddev;

  Index3 inputbest_Chisqrt_Y_Empty{Index_input_Empty.best_Chisqrt_Y.i,Index_input_Empty.best_Chisqrt_Y.j,Index_input_Empty.best_Chisqrt_Y.k};
  Convoluted_MeanE = ZShifts[inputbest_Chisqrt_Y_Empty].mean;
  Convoluted_stddevE = ZShifts[inputbest_Chisqrt_Y_Empty].stddev;


Plot_Eventdistrubution_RECOCol(inputMap.Vertex_Y_TotalRegion, Playlist_name,  PlotTitle , playlist_status,
  1.0,  Convoluted_MeanF,  Convoluted_stddevF, Convoluted_MeanE,  Convoluted_stddevE,  chisqrt1, chisqrt2, chisqrt3);

  Index3 inputbest_Chisqrt_R_Full{Index_input_Full.best_Chisqrt_R.i,Index_input_Full.best_Chisqrt_R.j,Index_input_Full.best_Chisqrt_R.k};
  Convoluted_MeanF = ZShifts[inputbest_Chisqrt_R_Full].mean;
  Convoluted_stddevF = ZShifts[inputbest_Chisqrt_R_Full].stddev;

  Index3 inputbest_Chisqrt_R_Empty{Index_input_Empty.best_Chisqrt_R.i,Index_input_Empty.best_Chisqrt_R.j,Index_input_Empty.best_Chisqrt_R.k};
  Convoluted_MeanE = ZShifts[inputbest_Chisqrt_R_Empty].mean;
  Convoluted_stddevE = ZShifts[inputbest_Chisqrt_R_Empty].stddev;

Plot_Eventdistrubution_RECOCol(inputMap.Vertex_R_TotalRegion, Playlist_name,  PlotTitle , playlist_status,
  1.0,  Convoluted_MeanF,  Convoluted_stddevF, Convoluted_MeanE,  Convoluted_stddevE,  chisqrt1, chisqrt2, chisqrt3);

//Plot_Eventdistrubution(inputMap.Vertex_RR_TotalRegion, Playlist_name,  PlotTitle , playlist_status,
//  1.0,  Convoluted_Mean,  Convoluted_stddev, ind, chisqrt1, chisqrt2, chisqrt3);

Index3 inputbest_Chisqrt_Z_Full{Index_input_Full.best_Chisqrt_Z.i,Index_input_Full.best_Chisqrt_Z.j,Index_input_Full.best_Chisqrt_Z.k};
Convoluted_MeanF = ZShifts[inputbest_Chisqrt_Z_Full].mean;
Convoluted_stddevF = ZShifts[inputbest_Chisqrt_Z_Full].stddev;

Index3 inputbest_Chisqrt_Z_Empty{Index_input_Empty.best_Chisqrt_Z.i,Index_input_Empty.best_Chisqrt_Z.j,Index_input_Empty.best_Chisqrt_Z.k};
Convoluted_MeanE = ZShifts[inputbest_Chisqrt_Z_Empty].mean;
Convoluted_stddevE = ZShifts[inputbest_Chisqrt_Z_Empty].stddev;

Plot_Eventdistrubution_RECOCol(inputMap.Vertex_Z_TotalRegion, Playlist_name,  PlotTitle , playlist_status,
  1.0,  Convoluted_MeanF,  Convoluted_stddevF, Convoluted_MeanE,  Convoluted_stddevE,  chisqrt1, chisqrt2, chisqrt3);

  Index3 inputbest_Chisqrt_Z_RCut_Full{Index_input_Full.best_Chisqrt_Z_RCut.i,Index_input_Full.best_Chisqrt_Z_RCut.j,Index_input_Full.best_Chisqrt_Z_RCut.k};
  Convoluted_MeanF = ZShifts[inputbest_Chisqrt_Z_RCut_Full].mean;
  Convoluted_stddevF = ZShifts[inputbest_Chisqrt_Z_RCut_Full].stddev;

  Index3 inputbest_Chisqrt_Z_RCut_Empty{Index_input_Empty.best_Chisqrt_Z_RCut.i,Index_input_Empty.best_Chisqrt_Z_RCut.j,Index_input_Empty.best_Chisqrt_Z_RCut.k};
  Convoluted_MeanE = ZShifts[inputbest_Chisqrt_Z_RCut_Empty].mean;
  Convoluted_stddevE = ZShifts[inputbest_Chisqrt_Z_RCut_Empty].stddev;

Title_WithExtra = "[RCut]  " + PlotTitle;
Plot_Eventdistrubution_RECOCol(inputMap.Vertex_Z_TotalRegion_RCut, Playlist_name,  Title_WithExtra , playlist_status,
  1.0,  Convoluted_MeanF,  Convoluted_stddevF, Convoluted_MeanE,  Convoluted_stddevE,  chisqrt1, chisqrt2, chisqrt3);

  Index3 inputbest_NearestWall_Full{Index_input_Full.best_Chisqrt_NearestWall.i,Index_input_Full.best_Chisqrt_NearestWall.j,Index_input_Full.best_Chisqrt_NearestWall.k};
  Convoluted_MeanF = ZShifts[inputbest_NearestWall_Full].mean;
  Convoluted_stddevF = ZShifts[inputbest_NearestWall_Full].stddev;

  Index3 inputbest_NearestWall_Empty{Index_input_Empty.best_Chisqrt_NearestWall.i,Index_input_Empty.best_Chisqrt_NearestWall.j,Index_input_Empty.best_Chisqrt_NearestWall.k};
  Convoluted_MeanE = ZShifts[inputbest_NearestWall_Empty].mean;
  Convoluted_stddevE = ZShifts[inputbest_NearestWall_Empty].stddev;

Plot_Eventdistrubution_RECOCol(inputMap.NearestWall_TotalRegion, Playlist_name,  PlotTitle , playlist_status,
  1.0,  Convoluted_MeanF,  Convoluted_stddevF, Convoluted_MeanE,  Convoluted_stddevE,  chisqrt1, chisqrt2, chisqrt3);

  Index3 inputbest_DistancetoUpstreamCap_Full{Index_input_Full.best_Chisqrt_DistancetoUpstreamCap.i,Index_input_Full.best_Chisqrt_DistancetoUpstreamCap.j,Index_input_Full.best_Chisqrt_DistancetoUpstreamCap.k};
  Convoluted_MeanF = ZShifts[inputbest_DistancetoUpstreamCap_Full].mean;
  Convoluted_stddevF = ZShifts[inputbest_DistancetoUpstreamCap_Full].stddev;

  Index3 inputbest_DistancetoUpstreamCap_Empty{Index_input_Empty.best_Chisqrt_DistancetoUpstreamCap.i,Index_input_Empty.best_Chisqrt_DistancetoUpstreamCap.j,Index_input_Empty.best_Chisqrt_DistancetoUpstreamCap.k};
  Convoluted_MeanE = ZShifts[inputbest_DistancetoUpstreamCap_Empty].mean;
  Convoluted_stddevE = ZShifts[inputbest_DistancetoUpstreamCap_Empty].stddev;

Plot_Eventdistrubution_RECOCol(inputMap.DistanceUpstreamCap_TotalRegion, Playlist_name,  PlotTitle , playlist_status,
  1.0,  Convoluted_MeanF,  Convoluted_stddevF, Convoluted_MeanE,  Convoluted_stddevE, chisqrt1, chisqrt2, chisqrt3);

  Index3 inputbest_DistancetoDownstreamCap_Full{Index_input_Full.best_Chisqrt_DistancetoDownstreamCap.i,Index_input_Full.best_Chisqrt_DistancetoDownstreamCap.j,Index_input_Full.best_Chisqrt_DistancetoDownstreamCap.k};
  Convoluted_MeanF = ZShifts[inputbest_DistancetoDownstreamCap_Full].mean;
  Convoluted_stddevF = ZShifts[inputbest_DistancetoDownstreamCap_Full].stddev;

  Index3 inputbest_DistancetoDownstreamCap_Empty{Index_input_Empty.best_Chisqrt_DistancetoDownstreamCap.i,Index_input_Empty.best_Chisqrt_DistancetoDownstreamCap.j,Index_input_Empty.best_Chisqrt_DistancetoDownstreamCap.k};
  Convoluted_MeanE = ZShifts[inputbest_DistancetoDownstreamCap_Empty].mean;
  Convoluted_stddevE = ZShifts[inputbest_DistancetoDownstreamCap_Empty].stddev;

Plot_Eventdistrubution_RECOCol(inputMap.DistanceDownstreamCap_TotalRegion, Playlist_name,  PlotTitle , playlist_status,
  1.0,  Convoluted_MeanF,  Convoluted_stddevF, Convoluted_MeanE,  Convoluted_stddevE, chisqrt1, chisqrt2, chisqrt3);

  Index3 inputbest_DistancetoUpstreamCap_RCut_Full{Index_input_Full.best_Chisqrt_DistancetoUpstreamCap_RCut.i,Index_input_Full.best_Chisqrt_DistancetoUpstreamCap_RCut.j,Index_input_Full.best_Chisqrt_DistancetoUpstreamCap_RCut.k};
  Convoluted_MeanF = ZShifts[inputbest_DistancetoUpstreamCap_RCut_Full].mean;
  Convoluted_stddevF = ZShifts[inputbest_DistancetoUpstreamCap_RCut_Full].stddev;

  Index3 inputbest_DistancetoUpstreamCap_RCut_Empty{Index_input_Empty.best_Chisqrt_DistancetoUpstreamCap_RCut.i,Index_input_Empty.best_Chisqrt_DistancetoUpstreamCap_RCut.j,Index_input_Empty.best_Chisqrt_DistancetoUpstreamCap_RCut.k};
  Convoluted_MeanE = ZShifts[inputbest_DistancetoUpstreamCap_RCut_Empty].mean;
  Convoluted_stddevE = ZShifts[inputbest_DistancetoUpstreamCap_RCut_Empty].stddev;

Plot_Eventdistrubution_RECOCol(inputMap.DistanceUpstreamCap_TotalRegion_RCut, Playlist_name,  Title_WithExtra , playlist_status,
  1.0,  Convoluted_MeanF,  Convoluted_stddevF, Convoluted_MeanE,  Convoluted_stddevE, chisqrt1, chisqrt2, chisqrt3);

  Index3 inputbest_DistancetoDownstreamCap_RCut_Full{Index_input_Full.best_Chisqrt_DistancetoDownstreamCap_RCut.i,Index_input_Full.best_Chisqrt_DistancetoDownstreamCap_RCut.j,Index_input_Full.best_Chisqrt_DistancetoDownstreamCap_RCut.k};
  Convoluted_MeanF = ZShifts[inputbest_DistancetoDownstreamCap_RCut_Full].mean;
  Convoluted_stddevF = ZShifts[inputbest_DistancetoDownstreamCap_RCut_Full].stddev;

  Index3 inputbest_DistancetoDownstreamCap_RCut_Empty{Index_input_Empty.best_Chisqrt_DistancetoDownstreamCap_RCut.i,Index_input_Empty.best_Chisqrt_DistancetoDownstreamCap_RCut.j,Index_input_Empty.best_Chisqrt_DistancetoDownstreamCap_RCut.k};
  Convoluted_MeanE = ZShifts[inputbest_DistancetoDownstreamCap_RCut_Empty].mean;
  Convoluted_stddevE = ZShifts[inputbest_DistancetoDownstreamCap_RCut_Empty].stddev;

Plot_Eventdistrubution_RECOCol(inputMap.DistanceDownstreamCap_TotalRegion_RCut, Playlist_name,  Title_WithExtra , playlist_status,
  1.0,  Convoluted_MeanF,  Convoluted_stddevF, Convoluted_MeanE,  Convoluted_stddevE, chisqrt1, chisqrt2, chisqrt3);

}

void Convolution_Tool::Plot_Full_ConvolRECO(NormalParaFit_Map ZShifts, BestIndex Index_input_Full, BestIndex Index_input_Empty){
std::cout<<"Ploting FUll "<<std::endl;
Plot_EventDistrubution_ConvolRECO_TotalRegion(Full,    "Combined", "Full",  Index_input_Full,  ZShifts );
  std::cout<<"Ploting Empty "<<std::endl;
Plot_EventDistrubution_ConvolRECO_TotalRegion(Empty,     "Combined", "Empty",  Index_input_Empty,  ZShifts);
  std::cout<<"Ploting FUll - Empty "<<std::endl;
Plot_EventDistrubution_ConvolRECO_TotalRegion_F_E(Full_Empty,     "Combined", "F-E", Index_input_Full,  Index_input_Empty,  ZShifts);
}



void Convolution_Tool::Plot_EventDistrubution_Regions(ConvolutionShiftMap &inputMap, std::string Playlist_name,
   std::string playlist_status, double Convoluted_Mean, double Convoluted_stddev, int ind){

std::string TitleExtra = "[RCut] " + PlotTitle;
Plot_Eventdistrubution_Regions(inputMap.Vertex_X_Regions,                   Playlist_name, PlotTitle,  playlist_status, 1.0,  Convoluted_Mean,  Convoluted_stddev, ind);
Plot_Eventdistrubution_Regions(inputMap.Vertex_Y_Regions,                   Playlist_name, PlotTitle,  playlist_status, 1.0,  Convoluted_Mean,  Convoluted_stddev, ind);
Plot_Eventdistrubution_Regions(inputMap.Vertex_Z_Regions,                   Playlist_name, PlotTitle,  playlist_status, 1.0,  Convoluted_Mean,  Convoluted_stddev, ind);
Plot_Eventdistrubution_Regions(inputMap.Vertex_Z_Regions_RCut,              Playlist_name, TitleExtra,  playlist_status, 1.0,  Convoluted_Mean,  Convoluted_stddev, ind);
Plot_Eventdistrubution_Regions(inputMap.Vertex_R_Regions,                   Playlist_name, PlotTitle,  playlist_status, 1.0,  Convoluted_Mean,  Convoluted_stddev, ind);
//Plot_Eventdistrubution_Regions(inputMap.Vertex_RR_Regions,                  Playlist_name, PlotTitle,  playlist_status, 1.0,  Convoluted_Mean,  Convoluted_stddev, ind);
Plot_Eventdistrubution_Regions(inputMap.NearestWall_Regions,                Playlist_name, PlotTitle,  playlist_status, 1.0,  Convoluted_Mean,  Convoluted_stddev, ind);
Plot_Eventdistrubution_Regions(inputMap.DistanceUpstreamCap_Regions,        Playlist_name, PlotTitle,  playlist_status, 1.0,  Convoluted_Mean,  Convoluted_stddev, ind);
Plot_Eventdistrubution_Regions(inputMap.DistanceDownstreamCap_Regions,      Playlist_name, PlotTitle,  playlist_status, 1.0,  Convoluted_Mean,  Convoluted_stddev, ind);
Plot_Eventdistrubution_Regions(inputMap.DistanceUpstreamCap_Regions_RCut,   Playlist_name, TitleExtra,  playlist_status, 1.0,  Convoluted_Mean,  Convoluted_stddev, ind);
Plot_Eventdistrubution_Regions(inputMap.DistanceDownstreamCap_Regions_RCut, Playlist_name, TitleExtra,  playlist_status, 1.0,  Convoluted_Mean,  Convoluted_stddev, ind);

}



void Convolution_Tool::Plot_EventDistrubution_BestRegionsXYRZ(ConvolutionShiftMap &inputMap, Normal_Fit_ParametersXY &inputMapParametersXY, std::string Playlist_name,
   std::string playlist_status, int ind){


std::string TitleExtra =  Playlist_name;
Plot_Eventdistrubution_Regions(inputMap.Vertex_X_Regions,  Playlist_name, PlotTitle,  playlist_status, 1.0,  inputMapParametersXY[kX].mean,  inputMapParametersXY[kX].stddev, ind);
Plot_Eventdistrubution_Regions(inputMap.Vertex_Y_Regions,  Playlist_name, PlotTitle,  playlist_status, 1.0,  inputMapParametersXY[kY].mean,  inputMapParametersXY[kY].stddev, ind);
Plot_Eventdistrubution_Regions(inputMap.Vertex_Z_Regions,  Playlist_name, PlotTitle,  playlist_status, 1.0,  0,0, ind);
Plot_Eventdistrubution_Regions(inputMap.Vertex_R_Regions,  Playlist_name, PlotTitle,  playlist_status, 1.0,  0,0, ind);
}






void Convolution_Tool::Plot_EventDistrubution_Regions_F_E(Convolution_CryoRegions &inputMap, std::string Playlist_name, std::string xaxislabel, std::string PlotTitle,
   std::string playlist_status,
   Index3 bestupstreamF,   Index3 bestupstreamE,
   Index3 bestbarrelF,     Index3 bestbarrelE,
   Index3 bestdownstreamF, Index3 bestdownstreamE,
   Index3 bestconcaveF,    Index3 bestconcaveE,
    NormalParaFit_Map ShiftsMap  ){

std::string TitleExtra = "[USCap] " +  PlotTitle;

double chi1=0;
double chi2=0;
double chi3=0;


Plot_Eventdistrubution_RECOCol(
  inputMap.Upstream.MnvH1D_data,
  inputMap.Upstream.MnvH1D_mc_Reco,
  inputMap.Upstream.MnvH1D_mc_Convoluted[1],
  inputMap.Upstream.MnvH1D_mc_TRUTH,
  Playlist_name,
  TitleExtra,
  playlist_status,
  xaxislabel,
  "NEvent",
  1.0,
  ShiftsMap[bestupstreamF].mean,
  ShiftsMap[bestupstreamF].stddev,
  ShiftsMap[bestupstreamE].mean,
  ShiftsMap[bestupstreamE].stddev,
  chi1,
  chi2,
  chi3);

  Plot_Eventdistrubution_RECOCol(
    inputMap.Barrel.MnvH1D_data,
    inputMap.Barrel.MnvH1D_mc_Reco,
    inputMap.Barrel.MnvH1D_mc_Convoluted[1],
    inputMap.Barrel.MnvH1D_mc_TRUTH,
    Playlist_name,
    TitleExtra,
    playlist_status,
    xaxislabel,
    "NEvent",
    1.0,
    ShiftsMap[bestbarrelF].mean,
    ShiftsMap[bestbarrelF].stddev,
    ShiftsMap[bestbarrelE].mean,
    ShiftsMap[bestbarrelE].stddev,
    chi1,
    chi2,
    chi3);


    Plot_Eventdistrubution_RECOCol(
      inputMap.Downstream.MnvH1D_data,
      inputMap.Downstream.MnvH1D_mc_Reco,
      inputMap.Downstream.MnvH1D_mc_Convoluted[1],
      inputMap.Downstream.MnvH1D_mc_TRUTH,
      Playlist_name,
      TitleExtra,
      playlist_status,
      xaxislabel,
      "NEvent",
      1.0,
      ShiftsMap[bestdownstreamF].mean,
      ShiftsMap[bestdownstreamF].stddev,
      ShiftsMap[bestdownstreamE].mean,
      ShiftsMap[bestdownstreamE].stddev,
      chi1,
      chi2,
      chi3);

      Plot_Eventdistrubution_RECOCol(
        inputMap.Concave.MnvH1D_data,
        inputMap.Concave.MnvH1D_mc_Reco,
        inputMap.Concave.MnvH1D_mc_Convoluted[1],
        inputMap.Concave.MnvH1D_mc_TRUTH,
        Playlist_name,
        TitleExtra,
        playlist_status,
        xaxislabel,
        "NEvent",
        1.0,
        ShiftsMap[bestconcaveF].mean,
        ShiftsMap[bestconcaveF].stddev,
        ShiftsMap[bestconcaveE].mean,
        ShiftsMap[bestconcaveE].stddev,
        chi1,
        chi2,
        chi3);



}








void Convolution_Tool::Plot_EventDistrubution_Regions_ConvolRECO(ConvolutionShiftMap &inputMap, std::string Playlist_name,
   std::string playlist_status, double Convoluted_Mean, double Convoluted_stddev){

std::string TitleExtra = "[RCut] " + PlotTitle;
Plot_ConvolRECO_Eventdistrubution_Regions(inputMap.Vertex_X_Regions,                   Playlist_name, PlotTitle,  playlist_status, 1.0,  Convoluted_Mean,  Convoluted_stddev);
Plot_ConvolRECO_Eventdistrubution_Regions(inputMap.Vertex_Y_Regions,                   Playlist_name, PlotTitle,  playlist_status, 1.0,  Convoluted_Mean,  Convoluted_stddev);
Plot_ConvolRECO_Eventdistrubution_Regions(inputMap.Vertex_Z_Regions,                   Playlist_name, PlotTitle,  playlist_status, 1.0,  Convoluted_Mean,  Convoluted_stddev);
Plot_ConvolRECO_Eventdistrubution_Regions(inputMap.Vertex_Z_Regions_RCut,              Playlist_name, TitleExtra,  playlist_status, 1.0,  Convoluted_Mean,  Convoluted_stddev);
Plot_ConvolRECO_Eventdistrubution_Regions(inputMap.Vertex_R_Regions,                   Playlist_name, PlotTitle,  playlist_status, 1.0,  Convoluted_Mean,  Convoluted_stddev);
//Plot_EventDistrubution_Regions_ConvolRECO(inputMap.Vertex_RR_Regions,                  Playlist_name, PlotTitle,  playlist_status, 1.0,  Convoluted_Mean,  Convoluted_stddev, ind);
Plot_ConvolRECO_Eventdistrubution_Regions(inputMap.NearestWall_Regions,                Playlist_name, PlotTitle,  playlist_status, 1.0,  Convoluted_Mean,  Convoluted_stddev);
Plot_ConvolRECO_Eventdistrubution_Regions(inputMap.DistanceUpstreamCap_Regions,        Playlist_name, PlotTitle,  playlist_status, 1.0,  Convoluted_Mean,  Convoluted_stddev);
Plot_ConvolRECO_Eventdistrubution_Regions(inputMap.DistanceDownstreamCap_Regions,      Playlist_name, PlotTitle,  playlist_status, 1.0,  Convoluted_Mean,  Convoluted_stddev);
Plot_ConvolRECO_Eventdistrubution_Regions(inputMap.DistanceUpstreamCap_Regions_RCut,   Playlist_name, TitleExtra,  playlist_status, 1.0,  Convoluted_Mean,  Convoluted_stddev);
Plot_ConvolRECO_Eventdistrubution_Regions(inputMap.DistanceDownstreamCap_Regions_RCut, Playlist_name, TitleExtra,  playlist_status, 1.0,  Convoluted_Mean,  Convoluted_stddev);

}

void Convolution_Tool::Plot_EventDistrubution_FITRegionsOnly_ConvolRECO(ConvolutionShiftMap &inputMap, std::string Playlist_name,
   std::string playlist_status, double Convoluted_Mean, double Convoluted_stddev){

Plot_ConvolRECO_Eventdistrubution_Regions(inputMap.Vertex_X_Regions,                   Playlist_name, PlotTitle,  playlist_status, 1.0,  Convoluted_Mean,  Convoluted_stddev);
Plot_ConvolRECO_Eventdistrubution_Regions(inputMap.Vertex_Y_Regions,                   Playlist_name, PlotTitle,  playlist_status, 1.0,  Convoluted_Mean,  Convoluted_stddev);
Plot_ConvolRECO_Eventdistrubution_Regions(inputMap.Vertex_Z_Regions,                   Playlist_name, PlotTitle,  playlist_status, 1.0,  Convoluted_Mean,  Convoluted_stddev);
Plot_ConvolRECO_Eventdistrubution_Regions(inputMap.Vertex_R_Regions,                   Playlist_name, PlotTitle,  playlist_status, 1.0,  Convoluted_Mean,  Convoluted_stddev);

}

void Convolution_Tool::Plot_EventDistrubution_FITRegionsOnly_ConvolRECO_Empty(double Convoluted_Mean, double Convoluted_stddev){

  Plot_EventDistrubution_FITRegionsOnly_ConvolRECO(Empty, "E", "",  Convoluted_Mean,  Convoluted_stddev);


}






 void Convolution_Tool::PlotFull(double Convoluted_Mean, double Convoluted_stddev, int ind ){
  Plot_EventDistrubution_TotalRegion(Full, "Combined",
  "F",  Convoluted_Mean,  Convoluted_stddev,  ind);
}

void Convolution_Tool::PlotFull_ConvolRECO(double Convoluted_Mean, double Convoluted_stddev, int ind ){
 Plot_EventDistrubution_ConvolRECO_TotalRegion(Full, "Combined",
 "F",  Convoluted_Mean,  Convoluted_stddev,  ind);
}



void Convolution_Tool::PlotFull_Regions(double Convoluted_Mean, double Convoluted_stddev, int ind ){
 Plot_EventDistrubution_Regions(Full, "Combined",
 "F",  Convoluted_Mean,  Convoluted_stddev,  ind);
}

void Convolution_Tool::PlotFull_Regions_ConvolRECO(double Convoluted_Mean, double Convoluted_stddev){
 Plot_EventDistrubution_Regions_ConvolRECO(Full, "Combined",
 "F",  Convoluted_Mean,  Convoluted_stddev);
}

 void Convolution_Tool::PlotEmpty(double Convoluted_Mean, double Convoluted_stddev, int ind ){
  Plot_EventDistrubution_TotalRegion(Empty, "Combined",
  "E",  Convoluted_Mean,  Convoluted_stddev,  ind);
}

void Convolution_Tool::PlotEmpty_Regions(double Convoluted_Mean, double Convoluted_stddev, int ind ){
 Plot_EventDistrubution_Regions(Empty, "Combined",
 "E",  Convoluted_Mean,  Convoluted_stddev,  ind);
}

void Convolution_Tool::PlotEmpty_Regions_ConvolRECO(double Convoluted_Mean, double Convoluted_stddev ){
  Plot_EventDistrubution_Regions_ConvolRECO(Empty, "Combined",
 "E",  Convoluted_Mean,  Convoluted_stddev);
}


void Convolution_Tool::PlotFull_Empty(double Convoluted_Mean, double Convoluted_stddev, int ind ){
  Plot_EventDistrubution_TotalRegion(Full_Empty, "Combined",
  "F-E",  Convoluted_Mean,  Convoluted_stddev,  ind);
}

void Convolution_Tool::PlotFull_Empty_Regions(double Convoluted_Mean, double Convoluted_stddev, int ind ){
 Plot_EventDistrubution_Regions(Full_Empty, "Combined",
 "F-E",  Convoluted_Mean,  Convoluted_stddev,  ind);
}

void Convolution_Tool::PlotFull_Empty_Regions_ConvolRECO(double Convoluted_Mean, double Convoluted_stddev ){
 Plot_EventDistrubution_Regions_ConvolRECO(Full_Empty, "Combined",
 "F-E",  Convoluted_Mean,  Convoluted_stddev);
}




void Convolution_Tool::Plot_Regions(double Convoluted_Mean, double Convoluted_stddev){
PlotFull_Regions( Convoluted_Mean, Convoluted_stddev,  0 );
PlotEmpty_Regions( Convoluted_Mean, Convoluted_stddev,  0 );
PlotFull_Empty_Regions( Convoluted_Mean, Convoluted_stddev,  0 );
}

void Convolution_Tool::Plot_Regions_ConvolRECO(double Convoluted_Mean, double Convoluted_stddev){
PlotFull_Regions_ConvolRECO( Convoluted_Mean, Convoluted_stddev );
PlotEmpty_Regions_ConvolRECO( Convoluted_Mean, Convoluted_stddev );
PlotFull_Empty_Regions_ConvolRECO( Convoluted_Mean, Convoluted_stddev );
}



void Convolution_Tool::SetBinWidthNorm(bool input){global_DoBinwidthNorm = input;}
void Convolution_Tool::SetXaxis_toLog(bool input){global_MakeXaxisLOG = input;}


void Convolution_Tool::Cal_Chisqrt_ConvolutionTruth_ToData(MnvPlotter *MnvPlotter,
  Convolution_hist input,
  double &Chi2DataMC_DatatoTRUTH, int &ndf_Chi2DataMC_DatatoTRUTH, int ind )
  {
     Chi2DataMC_DatatoTRUTH       =  MnvPlotter->Chi2DataMC(input.MnvH1D_data,    input.MnvH1D_mc_Convoluted[ind], ndf_Chi2DataMC_DatatoTRUTH);
     //Chi2DataMC_DatatoTRUTH       = CalChiSqrt(input, ind );
  }



  void Convolution_Tool::Cal_Chisqrt_ConvolutionTruth_ToData_Regions(MnvPlotter *MnvPlotter,
    Convolution_CryoRegions &Hist_input, int ind,
    double &Chi2DataMC_DatatoTRUTH_upstream,   int &ndf_Chi2DataMC_DatatoTRUTH_upstream,
    double &Chi2DataMC_DatatoTRUTH_barrel,     int &ndf_Chi2DataMC_DatatoTRUTH_barrel,
    double &Chi2DataMC_DatatoTRUTH_downstream, int &ndf_Chi2DataMC_DatatoTRUTH_downstream,
    double &Chi2DataMC_DatatoTRUTH_concave,    int &ndf_Chi2DataMC_DatatoTRUTH_concave){

      Cal_Chisqrt_ConvolutionTruth_ToData(MnvPlotter, Hist_input.Upstream,
      Chi2DataMC_DatatoTRUTH_upstream, ndf_Chi2DataMC_DatatoTRUTH_upstream,  ind );

      Cal_Chisqrt_ConvolutionTruth_ToData(MnvPlotter,  Hist_input.Barrel,
        Chi2DataMC_DatatoTRUTH_barrel, ndf_Chi2DataMC_DatatoTRUTH_barrel,  ind );

      Cal_Chisqrt_ConvolutionTruth_ToData(MnvPlotter, Hist_input.Downstream,
        Chi2DataMC_DatatoTRUTH_downstream, ndf_Chi2DataMC_DatatoTRUTH_downstream,  ind );

      Cal_Chisqrt_ConvolutionTruth_ToData(MnvPlotter, Hist_input.Concave,
        Chi2DataMC_DatatoTRUTH_concave, ndf_Chi2DataMC_DatatoTRUTH_concave,  ind );

  }

  void Convolution_Tool::Cal_Chisqrt_ConvolutionTruth_ToData_Regions(MnvPlotter *MnvPlotter,
    Convolution_CryoRegions &Hist_input, int ind,
    double &Chi2DataMC_DatatoTRUTH_upstream,
    double &Chi2DataMC_DatatoTRUTH_barrel,
    double &Chi2DataMC_DatatoTRUTH_downstream,
    double &Chi2DataMC_DatatoTRUTH_concave ){

      int ndf1= 0; int ndf2= 0; int ndf3= 0; int  ndf4= 0;

      Cal_Chisqrt_ConvolutionTruth_ToData_Regions(MnvPlotter, Hist_input, ind,
        Chi2DataMC_DatatoTRUTH_upstream,   ndf1,
        Chi2DataMC_DatatoTRUTH_barrel,     ndf2,
        Chi2DataMC_DatatoTRUTH_downstream, ndf3,
        Chi2DataMC_DatatoTRUTH_concave,    ndf4);

  }




void Convolution_Tool::Cal_Chisqrt_ConvolutionTruth_ToData_Regions(MnvPlotter *MnvPlotter,
    ConvolutionShiftMap &Hist_Map, ChiSqrt_CryoTankRegions &Chi_Sqt_Map, int ind)
  {

Cal_Chisqrt_ConvolutionTruth_ToData_Regions(MnvPlotter,
  Hist_Map.Vertex_X_Regions, ind,
  Chi_Sqt_Map.upstream.Chisqrt_X,
  Chi_Sqt_Map.barrel.Chisqrt_X,
  Chi_Sqt_Map.downstream.Chisqrt_X,
  Chi_Sqt_Map.concave.Chisqrt_X);

Cal_Chisqrt_ConvolutionTruth_ToData_Regions(MnvPlotter,
  Hist_Map.Vertex_Y_Regions, ind,
  Chi_Sqt_Map.upstream.Chisqrt_Y,
  Chi_Sqt_Map.barrel.Chisqrt_Y,
  Chi_Sqt_Map.downstream.Chisqrt_Y,
  Chi_Sqt_Map.concave.Chisqrt_Y);

Cal_Chisqrt_ConvolutionTruth_ToData_Regions(MnvPlotter,
  Hist_Map.Vertex_Z_Regions, ind,
  Chi_Sqt_Map.upstream.Chisqrt_Z,
  Chi_Sqt_Map.barrel.Chisqrt_Z,
  Chi_Sqt_Map.downstream.Chisqrt_Z,
  Chi_Sqt_Map.concave.Chisqrt_Z);

Cal_Chisqrt_ConvolutionTruth_ToData_Regions(MnvPlotter,
  Hist_Map.Vertex_Z_Regions_RCut, ind,
  Chi_Sqt_Map.upstream.Chisqrt_Z_RCut,
  Chi_Sqt_Map.barrel.Chisqrt_Z_RCut,
  Chi_Sqt_Map.downstream.Chisqrt_Z_RCut,
  Chi_Sqt_Map.concave.Chisqrt_Z_RCut);

Cal_Chisqrt_ConvolutionTruth_ToData_Regions(MnvPlotter,
  Hist_Map.Vertex_R_Regions, ind,
  Chi_Sqt_Map.upstream.Chisqrt_R,
  Chi_Sqt_Map.barrel.Chisqrt_R,
  Chi_Sqt_Map.downstream.Chisqrt_R,
  Chi_Sqt_Map.concave.Chisqrt_R);
/*
Cal_Chisqrt_ConvolutionTruth_ToData_Regions(MnvPlotter,
Hist_Map.Vertex_RR_Regions, 0
Chi_Sqt_Map.upstream.Chisqrt_RR,
Chi_Sqt_Map.barrel.Chisqrt_RR,
Chi_Sqt_Map.downstream.Chisqrt_RR,
Chi_Sqt_Map.concave.Chisqrt_RR);*/

Cal_Chisqrt_ConvolutionTruth_ToData_Regions(MnvPlotter,
  Hist_Map.NearestWall_Regions, ind,
  Chi_Sqt_Map.upstream.Chisqrt_NearestWall,
  Chi_Sqt_Map.barrel.Chisqrt_NearestWall,
  Chi_Sqt_Map.downstream.Chisqrt_NearestWall,
  Chi_Sqt_Map.concave.Chisqrt_NearestWall);

Cal_Chisqrt_ConvolutionTruth_ToData_Regions(MnvPlotter,
  Hist_Map.DistanceUpstreamCap_Regions, ind,
  Chi_Sqt_Map.upstream.Chisqrt_DistancetoUpstreamCap,
  Chi_Sqt_Map.barrel.Chisqrt_DistancetoUpstreamCap,
  Chi_Sqt_Map.downstream.Chisqrt_DistancetoUpstreamCap,
  Chi_Sqt_Map.concave.Chisqrt_DistancetoUpstreamCap);

Cal_Chisqrt_ConvolutionTruth_ToData_Regions(MnvPlotter,
  Hist_Map.DistanceDownstreamCap_Regions, ind,
  Chi_Sqt_Map.upstream.Chisqrt_DistancetoDownstreamCap,
  Chi_Sqt_Map.barrel.Chisqrt_DistancetoDownstreamCap,
  Chi_Sqt_Map.downstream.Chisqrt_DistancetoDownstreamCap,
  Chi_Sqt_Map.concave.Chisqrt_DistancetoDownstreamCap);

Cal_Chisqrt_ConvolutionTruth_ToData_Regions(MnvPlotter,
  Hist_Map.DistanceUpstreamCap_Regions_RCut, ind,
  Chi_Sqt_Map.upstream.Chisqrt_DistancetoUpstreamCap_RCut,
  Chi_Sqt_Map.barrel.Chisqrt_DistancetoUpstreamCap_RCut,
  Chi_Sqt_Map.downstream.Chisqrt_DistancetoUpstreamCap_RCut,
  Chi_Sqt_Map.concave.Chisqrt_DistancetoUpstreamCap_RCut);

Cal_Chisqrt_ConvolutionTruth_ToData_Regions(MnvPlotter,
  Hist_Map.DistanceDownstreamCap_Regions_RCut, ind,
  Chi_Sqt_Map.upstream.Chisqrt_DistancetoDownstreamCap_RCut,
  Chi_Sqt_Map.barrel.Chisqrt_DistancetoDownstreamCap_RCut,
  Chi_Sqt_Map.downstream.Chisqrt_DistancetoDownstreamCap_RCut,
  Chi_Sqt_Map.concave.Chisqrt_DistancetoDownstreamCap_RCut);
}


void   Convolution_Tool::Cal_Chisqrt_ConvolutionTruth_ToData_Regions(MnvPlotter *MnvPlotter,
  ChiSqrt_CryoTankRegions &inputFull,
  ChiSqrt_CryoTankRegions &inputEmpty,
  ChiSqrt_CryoTankRegions &input_Full_Empty, int ind ){

    Cal_Chisqrt_ConvolutionTruth_ToData_Regions(MnvPlotter, Full, inputFull, ind);
    Cal_Chisqrt_ConvolutionTruth_ToData_Regions(MnvPlotter, Empty, inputEmpty, ind);
    Cal_Chisqrt_ConvolutionTruth_ToData_Regions(MnvPlotter, Full_Empty, input_Full_Empty, ind);

  }




void Convolution_Tool::Cal_Chisqt_Total(ConvolutionShiftMap &Hist_Map, ChiSqrt_results &input, MnvPlotter *MnvPlotter , int ind){
int ndf;

//std::cout<<"inside:Cal_Chisqt_Total"<<std::endl;

Cal_Chisqrt_ConvolutionTruth_ToData(MnvPlotter,Hist_Map.Vertex_X_TotalRegion, input.Chisqrt_X, ndf, ind);
Cal_Chisqrt_ConvolutionTruth_ToData(MnvPlotter,Hist_Map.Vertex_Y_TotalRegion, input.Chisqrt_Y, ndf, ind);
Cal_Chisqrt_ConvolutionTruth_ToData(MnvPlotter,Hist_Map.Vertex_R_TotalRegion, input.Chisqrt_R, ndf, ind);
//Cal_Chisqrt_ConvolutionTruth_ToData(MnvPlotter,Hist_Map.Vertex_RR_TotalRegion, input., 0);
Cal_Chisqrt_ConvolutionTruth_ToData(MnvPlotter,Hist_Map.Vertex_Z_TotalRegion,                   input.Chisqrt_Z,                            ndf, ind);
Cal_Chisqrt_ConvolutionTruth_ToData(MnvPlotter,Hist_Map.Vertex_Z_TotalRegion_RCut,              input.Chisqrt_Z_RCut,                       ndf, ind);
Cal_Chisqrt_ConvolutionTruth_ToData(MnvPlotter,Hist_Map.NearestWall_TotalRegion,                input.Chisqrt_NearestWall,                  ndf, ind);
Cal_Chisqrt_ConvolutionTruth_ToData(MnvPlotter,Hist_Map.DistanceUpstreamCap_TotalRegion,        input.Chisqrt_DistancetoUpstreamCap,        ndf, ind);
Cal_Chisqrt_ConvolutionTruth_ToData(MnvPlotter,Hist_Map.DistanceDownstreamCap_TotalRegion,      input.Chisqrt_DistancetoDownstreamCap,      ndf, ind);
Cal_Chisqrt_ConvolutionTruth_ToData(MnvPlotter,Hist_Map.DistanceUpstreamCap_TotalRegion_RCut,   input.Chisqrt_DistancetoUpstreamCap_RCut,   ndf, ind);
Cal_Chisqrt_ConvolutionTruth_ToData(MnvPlotter,Hist_Map.DistanceDownstreamCap_TotalRegion_RCut, input.Chisqrt_DistancetoDownstreamCap_RCut, ndf, ind);

}








void Convolution_Tool::Cal_Chisqt_Total(ChiSqrt_results &inputFull, ChiSqrt_results &inputEmpty, ChiSqrt_results &input_Full_Empty, MnvPlotter *MnvPlotter, int ind ){


Cal_Chisqt_Total(Full, inputFull, MnvPlotter , ind);
Cal_Chisqt_Total(Empty, inputEmpty, MnvPlotter , ind);
Cal_Chisqt_Total(Full_Empty, input_Full_Empty, MnvPlotter , ind);

}



void Convolution_Tool::SaveBestChiSqrt_Total(ChiSqrt_results &inputFull_best,
                                             ChiSqrt_results &inputEmpty_best,
                                             ChiSqrt_results &input_Full_Empty_best,

                                             ChiSqrt_results &inputFull_input,
                                             ChiSqrt_results &inputEmpty_input,
                                             ChiSqrt_results &input_Full_Empty_input,
BestIndex &bestindex_Full, BestIndex &bestindex_Empty, BestIndex &bestindex_Full_Empty,
 Index3 input){

SaveBestChisqt_Total(inputFull_best, bestindex_Full, inputFull_input, input);
SaveBestChisqt_Total(inputEmpty_best, bestindex_Empty, inputEmpty_input, input);
SaveBestChisqt_Total(input_Full_Empty_best, bestindex_Full_Empty, input_Full_Empty_input, input);
}



void Convolution_Tool::Fill_bestIndex3_default(BestIndex &input){

  Index3 Zero_index{0,0,0};

  input.best_Chisqrt_X = Zero_index;
  input.best_Chisqrt_Y = Zero_index;
  input.best_Chisqrt_Z = Zero_index;
  input.best_Chisqrt_Z_RCut = Zero_index;
  input.best_Chisqrt_R = Zero_index;
  input.best_Chisqrt_NearestWall = Zero_index;
  input.best_Chisqrt_DistancetoUpstreamCap = Zero_index;
  input.best_Chisqrt_DistancetoUpstreamCap_RCut = Zero_index;
  input.best_Chisqrt_DistancetoDownstreamCap = Zero_index;
  input.best_Chisqrt_DistancetoDownstreamCap_RCut = Zero_index;

}



void Convolution_Tool::Fill_ChiSqrt_results_default(ChiSqrt_results &inputMap){

  double inputValue = 999999;

  inputMap.Chisqrt_X = inputValue;
  inputMap.Chisqrt_Y = inputValue;
  inputMap.Chisqrt_Z = inputValue;
  inputMap.Chisqrt_Z_RCut = inputValue;
  inputMap.Chisqrt_R = inputValue;
  inputMap.Chisqrt_NearestWall = inputValue;
  inputMap.Chisqrt_DistancetoUpstreamCap = inputValue;
  inputMap.Chisqrt_DistancetoUpstreamCap_RCut = inputValue;
  inputMap.Chisqrt_DistancetoDownstreamCap = inputValue;
  inputMap.Chisqrt_DistancetoDownstreamCap_RCut = inputValue;

}



void Convolution_Tool::Fill_Regions_bestindex3_default(BestIndex_Regions inputMap){

Fill_bestIndex3_default(inputMap.upstream);
Fill_bestIndex3_default(inputMap.barrel);
Fill_bestIndex3_default(inputMap.downstream);
Fill_bestIndex3_default(inputMap.concave);

}


void Convolution_Tool::Fill_Regions_ChiSqrt_results_default(ChiSqrt_CryoTankRegions &inputMap){

Fill_ChiSqrt_results_default(inputMap.upstream);
Fill_ChiSqrt_results_default(inputMap.barrel);
Fill_ChiSqrt_results_default(inputMap.downstream);
Fill_ChiSqrt_results_default(inputMap.concave);

}



 void Convolution_Tool::SaveBestChisqt_Total(ChiSqrt_results &Best, BestIndex &bestindex, ChiSqrt_results &Compare , Index3 input ){

 if(Best.Chisqrt_X  > Compare.Chisqrt_X){
 Best.Chisqrt_X = Compare.Chisqrt_X;
 bestindex.best_Chisqrt_X = input;
 }

 if(Best.Chisqrt_Y  > Compare.Chisqrt_Y){
 Best.Chisqrt_Y = Compare.Chisqrt_Y;
 bestindex.best_Chisqrt_Y = input;
 }

 if(Best.Chisqrt_Z  > Compare.Chisqrt_Z){
 Best.Chisqrt_Z = Compare.Chisqrt_Z;
 bestindex.best_Chisqrt_Z = input;
 }

 if(Best.Chisqrt_Z_RCut  > Compare.Chisqrt_Z_RCut){
 Best.Chisqrt_Z_RCut = Compare.Chisqrt_Z_RCut;
 bestindex.best_Chisqrt_Z_RCut = input;
 }

 if(Best.Chisqrt_R  > Compare.Chisqrt_R){
 Best.Chisqrt_R = Compare.Chisqrt_R;
 bestindex.best_Chisqrt_R = input;
 }


 if(Best.Chisqrt_NearestWall  > Compare.Chisqrt_NearestWall){
 Best.Chisqrt_NearestWall = Compare.Chisqrt_NearestWall;
 bestindex.best_Chisqrt_NearestWall = input;
 }


 if(Best.Chisqrt_DistancetoUpstreamCap  > Compare.Chisqrt_DistancetoUpstreamCap){
 Best.Chisqrt_DistancetoUpstreamCap = Compare.Chisqrt_DistancetoUpstreamCap;
 bestindex.best_Chisqrt_DistancetoUpstreamCap = input;
 }

 if(Best.Chisqrt_DistancetoUpstreamCap_RCut  > Compare.Chisqrt_DistancetoUpstreamCap_RCut){
 Best.Chisqrt_DistancetoUpstreamCap_RCut = Compare.Chisqrt_DistancetoUpstreamCap_RCut;
 bestindex.best_Chisqrt_DistancetoUpstreamCap_RCut = input;
 }

 if(Best.Chisqrt_DistancetoDownstreamCap  > Compare.Chisqrt_DistancetoDownstreamCap){
 Best.Chisqrt_DistancetoDownstreamCap = Compare.Chisqrt_DistancetoDownstreamCap;
 bestindex.best_Chisqrt_DistancetoDownstreamCap = input;
 }

 if(Best.Chisqrt_DistancetoDownstreamCap_RCut  > Compare.Chisqrt_DistancetoDownstreamCap_RCut){
 Best.Chisqrt_DistancetoDownstreamCap_RCut = Compare.Chisqrt_DistancetoDownstreamCap_RCut;
 bestindex.best_Chisqrt_DistancetoDownstreamCap_RCut = input;
 }

 }



 void Convolution_Tool::SaveBestChisqt_Regions(ChiSqrt_CryoTankRegions &Best_Map, BestIndex_Regions &bestindex, ChiSqrt_CryoTankRegions &Compare_Map , Index3 input ){

   SaveBestChisqt_Total(Best_Map.upstream,   bestindex.upstream,   Compare_Map.upstream,   input);
   SaveBestChisqt_Total(Best_Map.barrel,     bestindex.barrel,     Compare_Map.barrel,     input);
   SaveBestChisqt_Total(Best_Map.downstream, bestindex.downstream, Compare_Map.downstream, input);
   SaveBestChisqt_Total(Best_Map.concave,    bestindex.concave,    Compare_Map.concave,    input);

 }

  void Convolution_Tool::SaveBestChiSqrt_Regions(
    ChiSqrt_CryoTankRegions &input_Full_best,
    ChiSqrt_CryoTankRegions &input_Empty_best,
    ChiSqrt_CryoTankRegions &input_Full_Empty_best,
    ChiSqrt_CryoTankRegions &input_Full,
    ChiSqrt_CryoTankRegions &input_Empty,
    ChiSqrt_CryoTankRegions &input_Full_Empty,
    BestIndex_Regions &bestindex_Full,
    BestIndex_Regions &bestindex_Empty,
    BestIndex_Regions &bestindex_Full_Empty, Index3 input)
    {

      SaveBestChisqt_Regions(input_Full_best,       bestindex_Full,       input_Full,       input);
      SaveBestChisqt_Regions(input_Empty_best,      bestindex_Empty,      input_Empty ,     input);
      SaveBestChisqt_Regions(input_Full_Empty_best, bestindex_Full_Empty, input_Full_Empty, input);


    }



    double Convolution_Tool::ChiSqrt(
      MnvH1D* data_Region1, MnvH1D* Helium_Region1,
      MnvH1D* Aluminium_Region1, MnvH1D* Carbon_Region1,
      MnvH1D* Iron_Region1, MnvH1D* Lead_Region1, MnvH1D* Other_Region1,

      MnvH1D* data_Region2, MnvH1D* Helium_Region2, MnvH1D* Aluminium_Region2, MnvH1D* Carbon_Region2,
      MnvH1D* Iron_Region2, MnvH1D* Lead_Region2, MnvH1D* Other_Region2,

      MnvH1D* data_Region3, MnvH1D* Helium_Region3, MnvH1D* Aluminium_Region3, MnvH1D* Carbon_Region3,
      MnvH1D* Iron_Region3, MnvH1D* Lead_Region3, MnvH1D* Other_Region3,

      MnvH1D* data_Region4, MnvH1D* Helium_Region4, MnvH1D* Aluminium_Region4,
      MnvH1D* Carbon_Region4,
      MnvH1D* Iron_Region4, MnvH1D* Lead_Region4, MnvH1D* Other_Region4)
      {

        TH1D* h_data_Combined = new TH1D(data_Region1->GetCVHistoWithError());
        TH1D* h_Helium_Region1 = new TH1D(Helium_Region1->GetCVHistoWithError());
        TH1D* h_Aluminium_Region1 = new TH1D(Aluminium_Region1->GetCVHistoWithError());

        TH1D* h_Carbon_Combined = new TH1D(Carbon_Region1->GetCVHistoWithError());
        TH1D* h_Iron_Combined = new TH1D(Iron_Region1->GetCVHistoWithError());
        TH1D* h_Lead_Combined = new TH1D(Lead_Region1->GetCVHistoWithError());
        TH1D* h_Other_Combined = new TH1D(Other_Region1->GetCVHistoWithError());

        TH1D* h_data_Region2 = new TH1D(data_Region2->GetCVHistoWithError());
        TH1D* h_Helium_Region2 = new TH1D(Helium_Region2->GetCVHistoWithError());
        TH1D* h_Aluminium_Region2 = new TH1D(Aluminium_Region2->GetCVHistoWithError());
        TH1D* h_Carbon_Region2 = new TH1D(Carbon_Region2->GetCVHistoWithError());
        TH1D* h_Iron_Region2 = new TH1D(Iron_Region2->GetCVHistoWithError());
        TH1D* h_Lead_Region2 = new TH1D(Lead_Region2->GetCVHistoWithError());
        TH1D* h_Other_Region2 = new TH1D(Other_Region2->GetCVHistoWithError());

        h_Carbon_Combined->Add(h_Carbon_Region2);
        h_Iron_Combined->Add(h_Iron_Region2);
        h_Lead_Combined->Add(h_Lead_Region2);
        h_Other_Combined->Add(h_Other_Region2);
        h_data_Combined->Add(h_data_Region2);


        TH1D* h_data_Region3 = new TH1D(data_Region3->GetCVHistoWithError());
        TH1D* h_Helium_Region3 = new TH1D(Helium_Region3->GetCVHistoWithError());
        TH1D* h_Aluminium_Region3 = new TH1D(Aluminium_Region3->GetCVHistoWithError());

        TH1D* h_Carbon_Region3 = new TH1D(Carbon_Region3->GetCVHistoWithError());
        TH1D* h_Iron_Region3 = new TH1D(Iron_Region3->GetCVHistoWithError());
        TH1D* h_Lead_Region3 = new TH1D(Lead_Region3->GetCVHistoWithError());
        TH1D* h_Other_Region3 = new TH1D(Other_Region3->GetCVHistoWithError());

        h_Carbon_Combined->Add(h_Carbon_Region3);
        h_Iron_Combined->Add(h_Iron_Region3);
        h_Lead_Combined->Add(h_Lead_Region3);
        h_Other_Combined->Add(h_Other_Region3);
        h_data_Combined->Add(h_data_Region3);

        TH1D* h_data_Region4 = new TH1D(data_Region4->GetCVHistoWithError());
        TH1D* h_Helium_Region4 = new TH1D(Helium_Region4->GetCVHistoWithError());
        TH1D* h_Aluminium_Region4 = new TH1D(Aluminium_Region4->GetCVHistoWithError());

        TH1D* h_Carbon_Region4 = new TH1D(Carbon_Region4->GetCVHistoWithError());
        TH1D* h_Iron_Region4 = new TH1D(Iron_Region4->GetCVHistoWithError());
        TH1D* h_Lead_Region4 = new TH1D(Lead_Region4->GetCVHistoWithError());
        TH1D* h_Other_Region4 = new TH1D(Other_Region4->GetCVHistoWithError());


        h_Carbon_Combined->Add(h_Carbon_Region4);
        h_Iron_Combined->Add(h_Iron_Region4);
        h_Lead_Combined->Add(h_Lead_Region4);
        h_Other_Combined->Add(h_Other_Region4);
        h_data_Combined->Add(h_data_Region4);

        double plot_chisq = calc_ChiSq(h_data_Combined,
        h_Helium_Region1,
        h_Helium_Region2,
        h_Helium_Region3,
        h_Helium_Region4,
        h_Aluminium_Region1,
        h_Aluminium_Region2,
        h_Aluminium_Region3,
        h_Aluminium_Region4,
        h_Carbon_Combined, h_Lead_Combined, h_Iron_Combined, h_Other_Combined);

        delete h_data_Combined;
        delete h_Helium_Region1;
        delete h_Aluminium_Region1;
        delete h_Carbon_Combined;
        delete h_Iron_Combined;
        delete h_Lead_Combined;
        delete h_Other_Combined;
        delete h_data_Region2;
        delete h_Helium_Region2;
        delete h_Aluminium_Region2;
        delete h_Carbon_Region2;
        delete h_Iron_Region2;
        delete h_Lead_Region2;
        delete h_Other_Region2;
        delete h_data_Region3;
        delete h_Helium_Region3;
        delete h_Aluminium_Region3;
        delete h_Carbon_Region3;
        delete h_Iron_Region3;
        delete h_Lead_Region3;
        delete h_Other_Region3;
        delete h_data_Region4;
        delete h_Helium_Region4;
        delete h_Aluminium_Region4;
        delete h_Carbon_Region4;
        delete h_Iron_Region4;
        delete h_Lead_Region4;
        delete h_Other_Region4;



        return plot_chisq;

}

void Convolution_Tool::CalMaterial_ChiSqrt(ConvolutionShiftMap inputMap,
   int ind,  double &chisqrt_x, double &chisqrt_y,
    double &chisqrt_z, double &chisqrt_r){



chisqrt_x = ChiSqrt(
  inputMap.Vertex_X_Regions.Upstream.MnvH1D_data,
  inputMap.Vertex_X_Regions.Upstream.MnvH1D_mc_Convoluted_Helium[ind],
  inputMap.Vertex_X_Regions.Upstream.MnvH1D_mc_Convoluted_Aluminium[ind],
  inputMap.Vertex_X_Regions.Upstream.MnvH1D_mc_Convoluted_Carbon[ind],
  inputMap.Vertex_X_Regions.Upstream.MnvH1D_mc_Convoluted_Iron[ind],
  inputMap.Vertex_X_Regions.Upstream.MnvH1D_mc_Convoluted_Lead[ind],
  inputMap.Vertex_X_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],

  inputMap.Vertex_X_Regions.Barrel.MnvH1D_data,
  inputMap.Vertex_X_Regions.Barrel.MnvH1D_mc_Convoluted_Helium[ind],
  inputMap.Vertex_X_Regions.Barrel.MnvH1D_mc_Convoluted_Aluminium[ind],
  inputMap.Vertex_X_Regions.Barrel.MnvH1D_mc_Convoluted_Carbon[ind],
  inputMap.Vertex_X_Regions.Barrel.MnvH1D_mc_Convoluted_Iron[ind],
  inputMap.Vertex_X_Regions.Barrel.MnvH1D_mc_Convoluted_Lead[ind],
  inputMap.Vertex_X_Regions.Barrel.MnvH1D_mc_Convoluted_Other[ind],


  inputMap.Vertex_X_Regions.Downstream.MnvH1D_data,
  inputMap.Vertex_X_Regions.Downstream.MnvH1D_mc_Convoluted_Helium[ind],
  inputMap.Vertex_X_Regions.Downstream.MnvH1D_mc_Convoluted_Aluminium[ind],
  inputMap.Vertex_X_Regions.Downstream.MnvH1D_mc_Convoluted_Carbon[ind],
  inputMap.Vertex_X_Regions.Downstream.MnvH1D_mc_Convoluted_Iron[ind],
  inputMap.Vertex_X_Regions.Downstream.MnvH1D_mc_Convoluted_Lead[ind],
  inputMap.Vertex_X_Regions.Downstream.MnvH1D_mc_Convoluted_Other[ind],


  inputMap.Vertex_X_Regions.Concave.MnvH1D_data,
  inputMap.Vertex_X_Regions.Concave.MnvH1D_mc_Convoluted_Helium[ind],
  inputMap.Vertex_X_Regions.Concave.MnvH1D_mc_Convoluted_Aluminium[ind],
  inputMap.Vertex_X_Regions.Concave.MnvH1D_mc_Convoluted_Carbon[ind],
  inputMap.Vertex_X_Regions.Concave.MnvH1D_mc_Convoluted_Iron[ind],
  inputMap.Vertex_X_Regions.Concave.MnvH1D_mc_Convoluted_Lead[ind],
  inputMap.Vertex_X_Regions.Concave.MnvH1D_mc_Convoluted_Other[ind]);
/////////////////////////////////////////////////////
// y
//////////////////////////////////

chisqrt_y = ChiSqrt(
  inputMap.Vertex_Y_Regions.Upstream.MnvH1D_data,
  inputMap.Vertex_Y_Regions.Upstream.MnvH1D_mc_Convoluted_Helium[ind],
  inputMap.Vertex_Y_Regions.Upstream.MnvH1D_mc_Convoluted_Aluminium[ind],
  inputMap.Vertex_Y_Regions.Upstream.MnvH1D_mc_Convoluted_Carbon[ind],
  inputMap.Vertex_Y_Regions.Upstream.MnvH1D_mc_Convoluted_Iron[ind],
  inputMap.Vertex_Y_Regions.Upstream.MnvH1D_mc_Convoluted_Lead[ind],
  inputMap.Vertex_Y_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],

  inputMap.Vertex_Y_Regions.Barrel.MnvH1D_data,
  inputMap.Vertex_Y_Regions.Barrel.MnvH1D_mc_Convoluted_Helium[ind],
  inputMap.Vertex_Y_Regions.Barrel.MnvH1D_mc_Convoluted_Aluminium[ind],
  inputMap.Vertex_Y_Regions.Barrel.MnvH1D_mc_Convoluted_Carbon[ind],
  inputMap.Vertex_Y_Regions.Barrel.MnvH1D_mc_Convoluted_Iron[ind],
  inputMap.Vertex_Y_Regions.Barrel.MnvH1D_mc_Convoluted_Lead[ind],
  inputMap.Vertex_Y_Regions.Barrel.MnvH1D_mc_Convoluted_Other[ind],


  inputMap.Vertex_Y_Regions.Downstream.MnvH1D_data,
  inputMap.Vertex_Y_Regions.Downstream.MnvH1D_mc_Convoluted_Helium[ind],
  inputMap.Vertex_Y_Regions.Downstream.MnvH1D_mc_Convoluted_Aluminium[ind],
  inputMap.Vertex_Y_Regions.Downstream.MnvH1D_mc_Convoluted_Carbon[ind],
  inputMap.Vertex_Y_Regions.Downstream.MnvH1D_mc_Convoluted_Iron[ind],
  inputMap.Vertex_Y_Regions.Downstream.MnvH1D_mc_Convoluted_Lead[ind],
  inputMap.Vertex_Y_Regions.Downstream.MnvH1D_mc_Convoluted_Other[ind],


  inputMap.Vertex_Y_Regions.Concave.MnvH1D_data,
  inputMap.Vertex_Y_Regions.Concave.MnvH1D_mc_Convoluted_Helium[ind],
  inputMap.Vertex_Y_Regions.Concave.MnvH1D_mc_Convoluted_Aluminium[ind],
  inputMap.Vertex_Y_Regions.Concave.MnvH1D_mc_Convoluted_Carbon[ind],
  inputMap.Vertex_Y_Regions.Concave.MnvH1D_mc_Convoluted_Iron[ind],
  inputMap.Vertex_Y_Regions.Concave.MnvH1D_mc_Convoluted_Lead[ind],
  inputMap.Vertex_Y_Regions.Concave.MnvH1D_mc_Convoluted_Other[ind]);


chisqrt_z = ChiSqrt(
  inputMap.Vertex_Z_Regions.Upstream.MnvH1D_data,
  inputMap.Vertex_Z_Regions.Upstream.MnvH1D_mc_Convoluted_Helium[ind],
  inputMap.Vertex_Z_Regions.Upstream.MnvH1D_mc_Convoluted_Aluminium[ind],
  inputMap.Vertex_Z_Regions.Upstream.MnvH1D_mc_Convoluted_Carbon[ind],
  inputMap.Vertex_Z_Regions.Upstream.MnvH1D_mc_Convoluted_Iron[ind],
  inputMap.Vertex_Z_Regions.Upstream.MnvH1D_mc_Convoluted_Lead[ind],
  inputMap.Vertex_Z_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],

  inputMap.Vertex_Z_Regions.Barrel.MnvH1D_data,
  inputMap.Vertex_Z_Regions.Barrel.MnvH1D_mc_Convoluted_Helium[ind],
  inputMap.Vertex_Z_Regions.Barrel.MnvH1D_mc_Convoluted_Aluminium[ind],
  inputMap.Vertex_Z_Regions.Barrel.MnvH1D_mc_Convoluted_Carbon[ind],
  inputMap.Vertex_Z_Regions.Barrel.MnvH1D_mc_Convoluted_Iron[ind],
  inputMap.Vertex_Z_Regions.Barrel.MnvH1D_mc_Convoluted_Lead[ind],
  inputMap.Vertex_Z_Regions.Barrel.MnvH1D_mc_Convoluted_Other[ind],

  inputMap.Vertex_Z_Regions.Downstream.MnvH1D_data,
  inputMap.Vertex_Z_Regions.Downstream.MnvH1D_mc_Convoluted_Helium[ind],
  inputMap.Vertex_Z_Regions.Downstream.MnvH1D_mc_Convoluted_Aluminium[ind],
  inputMap.Vertex_Z_Regions.Downstream.MnvH1D_mc_Convoluted_Carbon[ind],
  inputMap.Vertex_Z_Regions.Downstream.MnvH1D_mc_Convoluted_Iron[ind],
  inputMap.Vertex_Z_Regions.Downstream.MnvH1D_mc_Convoluted_Lead[ind],
  inputMap.Vertex_Z_Regions.Downstream.MnvH1D_mc_Convoluted_Other[ind],

  inputMap.Vertex_Z_Regions.Concave.MnvH1D_data,
  inputMap.Vertex_Z_Regions.Concave.MnvH1D_mc_Convoluted_Helium[ind],
  inputMap.Vertex_Z_Regions.Concave.MnvH1D_mc_Convoluted_Aluminium[ind],
  inputMap.Vertex_Z_Regions.Concave.MnvH1D_mc_Convoluted_Carbon[ind],
  inputMap.Vertex_Z_Regions.Concave.MnvH1D_mc_Convoluted_Iron[ind],
  inputMap.Vertex_Z_Regions.Concave.MnvH1D_mc_Convoluted_Lead[ind],
  inputMap.Vertex_Z_Regions.Concave.MnvH1D_mc_Convoluted_Other[ind]);

chisqrt_r = ChiSqrt(
  inputMap.Vertex_R_Regions.Upstream.MnvH1D_data,
  inputMap.Vertex_R_Regions.Upstream.MnvH1D_mc_Convoluted_Helium[ind],
  inputMap.Vertex_R_Regions.Upstream.MnvH1D_mc_Convoluted_Aluminium[ind],
  inputMap.Vertex_R_Regions.Upstream.MnvH1D_mc_Convoluted_Carbon[ind],
  inputMap.Vertex_R_Regions.Upstream.MnvH1D_mc_Convoluted_Iron[ind],
  inputMap.Vertex_R_Regions.Upstream.MnvH1D_mc_Convoluted_Lead[ind],
  inputMap.Vertex_R_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],

  inputMap.Vertex_R_Regions.Barrel.MnvH1D_data,
  inputMap.Vertex_R_Regions.Barrel.MnvH1D_mc_Convoluted_Helium[ind],
  inputMap.Vertex_R_Regions.Barrel.MnvH1D_mc_Convoluted_Aluminium[ind],
  inputMap.Vertex_R_Regions.Barrel.MnvH1D_mc_Convoluted_Carbon[ind],
  inputMap.Vertex_R_Regions.Barrel.MnvH1D_mc_Convoluted_Iron[ind],
  inputMap.Vertex_R_Regions.Barrel.MnvH1D_mc_Convoluted_Lead[ind],
  inputMap.Vertex_R_Regions.Barrel.MnvH1D_mc_Convoluted_Other[ind],

  inputMap.Vertex_R_Regions.Downstream.MnvH1D_data,
  inputMap.Vertex_R_Regions.Downstream.MnvH1D_mc_Convoluted_Helium[ind],
  inputMap.Vertex_R_Regions.Downstream.MnvH1D_mc_Convoluted_Aluminium[ind],
  inputMap.Vertex_R_Regions.Downstream.MnvH1D_mc_Convoluted_Carbon[ind],
  inputMap.Vertex_R_Regions.Downstream.MnvH1D_mc_Convoluted_Iron[ind],
  inputMap.Vertex_R_Regions.Downstream.MnvH1D_mc_Convoluted_Lead[ind],
  inputMap.Vertex_R_Regions.Downstream.MnvH1D_mc_Convoluted_Other[ind],

  inputMap.Vertex_R_Regions.Concave.MnvH1D_data,
  inputMap.Vertex_R_Regions.Concave.MnvH1D_mc_Convoluted_Helium[ind],
  inputMap.Vertex_R_Regions.Concave.MnvH1D_mc_Convoluted_Aluminium[ind],
  inputMap.Vertex_R_Regions.Concave.MnvH1D_mc_Convoluted_Carbon[ind],
  inputMap.Vertex_R_Regions.Concave.MnvH1D_mc_Convoluted_Iron[ind],
  inputMap.Vertex_R_Regions.Concave.MnvH1D_mc_Convoluted_Lead[ind],
  inputMap.Vertex_R_Regions.Concave.MnvH1D_mc_Convoluted_Other[ind]
);


}

void Convolution_Tool::CalMaterial_ChiSqrtEmptyAfter( double &chisqrt_x, double &chisqrt_y, double &chisqrt_z, double &chisqrt_r){

CalMaterial_ChiSqrt(Empty, 1,  chisqrt_x, chisqrt_y, chisqrt_z, chisqrt_r);
}
void Convolution_Tool::CalMaterial_ChiSqrtFullAfter( double &chisqrt_x, double &chisqrt_y, double &chisqrt_z, double &chisqrt_r){

CalMaterial_ChiSqrt(Full, 1,  chisqrt_x, chisqrt_y, chisqrt_z, chisqrt_r);
}




void Convolution_Tool::Fill_TotalChiSqrts(ChiSqrt_results &ChiSqrt_input, double mean,
  double stddev,
  MnvH2D *h2_Vertex_X_TotalRegion[],
  MnvH2D *h2_Vertex_Y_TotalRegion[],
  MnvH2D *h2_Vertex_R_TotalRegion[],
  /*MnvH2D &h2_Vertex_RR_TotalRegion,*/
  MnvH2D *h2_Vertex_Z_TotalRegion[],
  MnvH2D *h2_Vertex_Z_TotalRegion_RCut[],
  MnvH2D *h2_NearestWall_TotalRegion[],
  MnvH2D *h2_DistanceUpstreamCap_TotalRegion[],
  MnvH2D *h2_DistanceDownstreamCap_TotalRegion[],
  MnvH2D *h2_DistanceUpstreamCap_TotalRegion_RCut[],
  MnvH2D *h2_DistanceDownstreamCap_TotalRegion_RCut[])
  {
    h2_Vertex_X_TotalRegion[0]->Fill(                  mean,stddev,ChiSqrt_input.Chisqrt_X);
    h2_Vertex_Y_TotalRegion[0]->Fill(                  mean,stddev,ChiSqrt_input.Chisqrt_Y);
    h2_Vertex_R_TotalRegion[0]->Fill(                  mean,stddev,ChiSqrt_input.Chisqrt_R);
    //h2_Vertex_RR_TotalRegion.Fill(mean,stddev,);
    h2_Vertex_Z_TotalRegion[0]->Fill(                  mean,stddev,ChiSqrt_input.Chisqrt_Z);
    h2_Vertex_Z_TotalRegion_RCut[0]->Fill(             mean,stddev,ChiSqrt_input.Chisqrt_Z_RCut);
    h2_NearestWall_TotalRegion[0]->Fill(               mean,stddev,ChiSqrt_input.Chisqrt_NearestWall);
    h2_DistanceUpstreamCap_TotalRegion[0]->Fill(       mean,stddev,ChiSqrt_input.Chisqrt_DistancetoUpstreamCap);
    h2_DistanceDownstreamCap_TotalRegion[0]->Fill(     mean,stddev,ChiSqrt_input.Chisqrt_DistancetoDownstreamCap);
    h2_DistanceUpstreamCap_TotalRegion_RCut[0]->Fill(  mean,stddev,ChiSqrt_input.Chisqrt_DistancetoUpstreamCap_RCut);
    h2_DistanceDownstreamCap_TotalRegion_RCut[0]->Fill(mean,stddev,ChiSqrt_input.Chisqrt_DistancetoDownstreamCap_RCut);
  };



  void Convolution_Tool::Fill_TotalChiSqrts_Regions(ChiSqrt_CryoTankRegions &ChiSqrt_input, double mean,
    double stddev,
    MnvH2D *h2_Vertex_X_Regions[],
    MnvH2D *h2_Vertex_Y_Regions[],
    MnvH2D *h2_Vertex_R_Regions[],
    /*MnvH2D &h2_Vertex_RR_Regions[5],*/
    MnvH2D *h2_Vertex_Z_Regions[],
    MnvH2D *h2_Vertex_Z_Regions_RCut[],
    MnvH2D *h2_NearestWall_Regions[],
    MnvH2D *h2_DistanceUpstreamCap_Regions[],
    MnvH2D *h2_DistanceDownstreamCap_Regions[],
    MnvH2D *h2_DistanceUpstreamCap_Regions_RCut[],
    MnvH2D *h2_DistanceDownstreamCap_Regions_RCut[])
    {

      //std::cout<<"Inside:: Fill_TotalChiSqrts_Regions : 1"<<std::endl;

      //  std::cout<<"Filling values mean = "<< mean << " stddev = " << stddev<< " ChiSqrt_input.upstream.Chisqrt_X = " << ChiSqrt_input.upstream.Chisqrt_X  << std::endl;
      //  std::cout<< "h2_Vertex_X_Regions->size() = " <<  sizeof(h2_Vertex_X_Regions)<<std::endl;
      h2_Vertex_X_Regions[1]->Fill(mean,                   stddev,ChiSqrt_input.upstream.Chisqrt_X);
      h2_Vertex_Y_Regions[1]->Fill(mean,                   stddev,ChiSqrt_input.upstream.Chisqrt_Y);
      h2_Vertex_R_Regions[1]->Fill(mean,                   stddev,ChiSqrt_input.upstream.Chisqrt_R);
      //h2_Vertex_RR_TotalRegion.Fill(mean,stddev,);
      h2_Vertex_Z_Regions[1]->Fill(mean,                  stddev,ChiSqrt_input.upstream.Chisqrt_Z);
      h2_Vertex_Z_Regions_RCut[1]->Fill(mean,             stddev,ChiSqrt_input.upstream.Chisqrt_Z_RCut);
      h2_NearestWall_Regions[1]->Fill(mean,               stddev,ChiSqrt_input.upstream.Chisqrt_NearestWall);
      h2_DistanceUpstreamCap_Regions[1]->Fill(mean,       stddev,ChiSqrt_input.upstream.Chisqrt_DistancetoUpstreamCap);
      h2_DistanceDownstreamCap_Regions[1]->Fill(mean,     stddev,ChiSqrt_input.upstream.Chisqrt_DistancetoDownstreamCap);
      h2_DistanceUpstreamCap_Regions_RCut[1]->Fill(mean,  stddev,ChiSqrt_input.upstream.Chisqrt_DistancetoUpstreamCap_RCut);
      h2_DistanceDownstreamCap_Regions_RCut[1]->Fill(mean,stddev,ChiSqrt_input.upstream.Chisqrt_DistancetoDownstreamCap_RCut);


  //  std::cout<<"Inside:: Fill_TotalChiSqrts_Regions : 2"<<std::endl;

      h2_Vertex_X_Regions[2]->Fill(           mean,        stddev,ChiSqrt_input.barrel.Chisqrt_X);
      h2_Vertex_Y_Regions[2]->Fill(            mean,        stddev,ChiSqrt_input.barrel.Chisqrt_Y);
      h2_Vertex_R_Regions[2]->Fill(           mean,        stddev,ChiSqrt_input.barrel.Chisqrt_R);
      //h2_Vertex_RR_TotalRegion.Fill(mean,stddev,);
      h2_Vertex_Z_Regions[2]->Fill(           mean,       stddev,ChiSqrt_input.barrel.Chisqrt_Z);
      h2_Vertex_Z_Regions_RCut[2]->Fill(      mean,       stddev,ChiSqrt_input.barrel.Chisqrt_Z_RCut);
      h2_NearestWall_Regions[2]->Fill(        mean,       stddev,ChiSqrt_input.barrel.Chisqrt_NearestWall);
      h2_DistanceUpstreamCap_Regions[2]->Fill(mean,       stddev,ChiSqrt_input.barrel.Chisqrt_DistancetoUpstreamCap);
      h2_DistanceDownstreamCap_Regions[2]->Fill(mean,     stddev,ChiSqrt_input.barrel.Chisqrt_DistancetoDownstreamCap);
      h2_DistanceUpstreamCap_Regions_RCut[2]->Fill(mean,  stddev,ChiSqrt_input.barrel.Chisqrt_DistancetoUpstreamCap_RCut);
      h2_DistanceDownstreamCap_Regions_RCut[2]->Fill(mean,stddev,ChiSqrt_input.barrel.Chisqrt_DistancetoDownstreamCap_RCut);


//    std::cout<<"Inside:: Fill_TotalChiSqrts_Regions : 3"<<std::endl;

      h2_Vertex_X_Regions[3]->Fill(mean,                   stddev,ChiSqrt_input.downstream.Chisqrt_X);
      h2_Vertex_Y_Regions[3]->Fill(mean,                   stddev,ChiSqrt_input.downstream.Chisqrt_Y);
      h2_Vertex_R_Regions[3]->Fill(mean,                   stddev,ChiSqrt_input.downstream.Chisqrt_R);
      //h2_Vertex_RR_TotalRegion.Fill(mean,stddev,);
      h2_Vertex_Z_Regions[3]->Fill(mean,                  stddev,ChiSqrt_input.downstream.Chisqrt_Z);
      h2_Vertex_Z_Regions_RCut[3]->Fill(mean,             stddev,ChiSqrt_input.downstream.Chisqrt_Z_RCut);
      h2_NearestWall_Regions[3]->Fill(mean,               stddev,ChiSqrt_input.downstream.Chisqrt_NearestWall);
      h2_DistanceUpstreamCap_Regions[3]->Fill(mean,       stddev,ChiSqrt_input.downstream.Chisqrt_DistancetoUpstreamCap);
      h2_DistanceDownstreamCap_Regions[3]->Fill(mean,     stddev,ChiSqrt_input.downstream.Chisqrt_DistancetoDownstreamCap);
      h2_DistanceUpstreamCap_Regions_RCut[3]->Fill(mean,  stddev,ChiSqrt_input.downstream.Chisqrt_DistancetoUpstreamCap_RCut);
      h2_DistanceDownstreamCap_Regions_RCut[3]->Fill(mean,stddev,ChiSqrt_input.downstream.Chisqrt_DistancetoDownstreamCap_RCut);


    //std::cout<<"Inside:: Fill_TotalChiSqrts_Regions : 4"<<std::endl;

      h2_Vertex_X_Regions[4]->Fill(mean,                   stddev,ChiSqrt_input.concave.Chisqrt_X);
      h2_Vertex_Y_Regions[4]->Fill(mean,                   stddev,ChiSqrt_input.concave.Chisqrt_Y);
      h2_Vertex_R_Regions[4]->Fill(mean,                   stddev,ChiSqrt_input.concave.Chisqrt_R);
      //h2_Vertex_RR_TotalRegion.Fill(mean,stddev,);
      h2_Vertex_Z_Regions[4]->Fill(mean,                  stddev,ChiSqrt_input.concave.Chisqrt_Z);
      h2_Vertex_Z_Regions_RCut[4]->Fill(mean,             stddev,ChiSqrt_input.concave.Chisqrt_Z_RCut);
      h2_NearestWall_Regions[4]->Fill(mean,               stddev,ChiSqrt_input.concave.Chisqrt_NearestWall);
      h2_DistanceUpstreamCap_Regions[4]->Fill(mean,       stddev,ChiSqrt_input.concave.Chisqrt_DistancetoUpstreamCap);
      h2_DistanceDownstreamCap_Regions[4]->Fill(mean,     stddev,ChiSqrt_input.concave.Chisqrt_DistancetoDownstreamCap);
      h2_DistanceUpstreamCap_Regions_RCut[4]->Fill(mean,  stddev,ChiSqrt_input.concave.Chisqrt_DistancetoUpstreamCap_RCut);
      h2_DistanceDownstreamCap_Regions_RCut[4]->Fill(mean,stddev,ChiSqrt_input.concave.Chisqrt_DistancetoDownstreamCap_RCut);
    };


double Convolution_Tool::CalChiSqrt(Convolution_hist InputHistMap, int ind, bool isPartial, int min_bin, int max_bin ){

  //std::cout<<"inside:calc_ChiSq_SideBand"<<std::endl;
      if (!isPartial){
          min_bin = 1;
          max_bin = InputHistMap.MnvH1D_data->GetNbinsX();
      }

      if (min_bin == max_bin){
          cout<<"Wrong Range for Fit"<<endl;
          exit(EXIT_FAILURE);
      }


      double ChiSq = 0.0;

      for (int i = 1; i <= InputHistMap.MnvH1D_data->GetNbinsX(); ++i){
          // Get N(Events) in Single Bin
          double err = InputHistMap.MnvH1D_data->GetBinError(i);
          double nData = InputHistMap.MnvH1D_data->GetBinContent(i);
          if (nData == 0) continue;
          double nMC_total = InputHistMap.MnvH1D_mc_Convoluted[ind]->GetBinContent(i);

          double delta = pow((nMC_total - nData),2) / pow(err,2);
          ChiSq += delta;
        }
      return ChiSq;
  }



double Convolution_Tool::CalLogChiSqrt(Convolution_hist InputHistMap, int ind, bool isPartial , int min_bin, int max_bin){

  //std::cout<<"inside:calc_ChiSq_SideBand"<<std::endl;
      if (!isPartial){
          min_bin = 1;
          max_bin = InputHistMap.MnvH1D_data->GetNbinsX();
      }

      if (min_bin == max_bin){
          cout<<"Wrong Range for Fit"<<endl;
          exit(EXIT_FAILURE);
      }


      double ChiSq = 0.0;

      for (int i = 1; i <= InputHistMap.MnvH1D_data->GetNbinsX(); ++i){
          // Get N(Events) in Single Bin
          //double err = InputHistMap.MnvH1D_data->GetBinError(i);
          double nData = InputHistMap.MnvH1D_data->GetBinContent(i);
          if (nData == 0) continue;
          double nMC_total = InputHistMap.MnvH1D_mc_Convoluted[1]->GetBinContent(i);

          double c = nData * log(nMC_total);
          double delta = 2 * (nMC_total - c);
          ChiSq += delta;
        }
      return ChiSq;
  }


  void Convolution_Tool::Plot_regions_Material(std::string pdf_label, int ind,
         MnvH1D* data_region1, MnvH1D* Helium_region1, MnvH1D* Aluminium_region1, MnvH1D* Carbon_region1,
         MnvH1D* Iron_region1, MnvH1D* Lead_region1, MnvH1D* Other_region1,
         MnvH1D* data_region2, MnvH1D* Helium_region2, MnvH1D* Aluminium_region2, MnvH1D* Carbon_region2,
         MnvH1D* Iron_region2, MnvH1D* Lead_region2, MnvH1D* Other_region2,
         MnvH1D* data_region3, MnvH1D* Helium_region3, MnvH1D* Aluminium_region3, MnvH1D* Carbon_region3,
         MnvH1D* Iron_region3, MnvH1D* Lead_region3, MnvH1D* Other_region3,
         MnvH1D* data_region4,  MnvH1D* Helium_region4, MnvH1D* Aluminium_region4, MnvH1D* Carbon_region4,
         MnvH1D* Iron_region4, MnvH1D* Lead_region4, MnvH1D* Other_region4,

         std::string Hist_title, std::string xaxislabel, double &ChiSqrt,
         double &ChiSqrtAfter, int FitType, bool UseLogChi, bool doAreaNormalized, bool applyMaxY , double MaxY)
         {

          std::string type;
          if (ind == 0) type = "Nominal";
          else type = "Fitted";
          //std::cout<<"Ploting type: Combined CryoRegions  "<< type<<std::endl;

          //PlotUtils::MnvPlotter* plotter= new mnvPlotter();
           MnvPlotter* plotter = new MnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
          //plotter(PlotUtils::kCCInclusiveHeliumStyle);
          MnvH1D *data = (PlotUtils::MnvH1D*)data_region1->Clone("data");

          data->Add(data_region2);

          data->Add(data_region3);

          data->Add(data_region4);


          MnvH1D *mc_total = (PlotUtils::MnvH1D*)Helium_region1->Clone("mc_total");

          mc_total->Add(Aluminium_region1 );

          mc_total->Add(Carbon_region1);

          mc_total->Add(Iron_region1 );

          mc_total->Add(Lead_region1 );

          mc_total->Add(Other_region1);


          mc_total->Add(Helium_region2 );

          mc_total->Add(Aluminium_region2 );

          mc_total->Add(Carbon_region2);

          mc_total->Add(Iron_region2 );

          mc_total->Add(Lead_region2 );

          mc_total->Add(Other_region2);


          mc_total->Add(Helium_region3 );

          mc_total->Add(Aluminium_region3 );

          mc_total->Add(Carbon_region3);

          mc_total->Add(Iron_region3 );

          mc_total->Add(Lead_region3 );

          mc_total->Add(Other_region3);


          mc_total->Add(Helium_region4 );


          mc_total->Add(Aluminium_region4 );


          mc_total->Add(Carbon_region4);


          mc_total->Add(Iron_region4 );


          mc_total->Add(Lead_region4 );


          mc_total->Add(Other_region4);



          data->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
          mc_total->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));


          TH1D* h_data_Combined = new TH1D(data_region1->GetCVHistoWithError());
          TH1D* h_Helium_region1 = new TH1D(Helium_region1->GetCVHistoWithError());
          TH1D* h_Aluminium_region1 = new TH1D(Aluminium_region1->GetCVHistoWithError());

          TH1D* h_Carbon_Combined = new TH1D(Carbon_region1->GetCVHistoWithError());
          TH1D* h_Iron_Combined = new TH1D(Iron_region1->GetCVHistoWithError());
          TH1D* h_Lead_Combined = new TH1D(Lead_region1->GetCVHistoWithError());
          TH1D* h_Other_Combined = new TH1D(Other_region1->GetCVHistoWithError());

          TH1D* h_data_region2 = new TH1D(data_region2->GetCVHistoWithError());
          TH1D* h_Helium_region2 = new TH1D(Helium_region2->GetCVHistoWithError());
          TH1D* h_Aluminium_region2 = new TH1D(Aluminium_region2->GetCVHistoWithError());
          TH1D* h_Carbon_region2 = new TH1D(Carbon_region2->GetCVHistoWithError());
          TH1D* h_Iron_region2 = new TH1D(Iron_region2->GetCVHistoWithError());
          TH1D* h_Lead_region2 = new TH1D(Lead_region2->GetCVHistoWithError());
          TH1D* h_Other_region2 = new TH1D(Other_region2->GetCVHistoWithError());

          h_Carbon_Combined->Add(h_Carbon_region2);
          h_Iron_Combined->Add(h_Iron_region2);
          h_Lead_Combined->Add(h_Lead_region2);
          h_Other_Combined->Add(h_Other_region2);

          h_data_Combined->Add(h_data_region2);

          TH1D* h_data_region3 = new TH1D(data_region3->GetCVHistoWithError());
          TH1D* h_Helium_region3 = new TH1D(Helium_region3->GetCVHistoWithError());
          TH1D* h_Aluminium_region3 = new TH1D(Aluminium_region3->GetCVHistoWithError());

          TH1D* h_Carbon_region3 = new TH1D(Carbon_region3->GetCVHistoWithError());
          TH1D* h_Iron_region3 = new TH1D(Iron_region3->GetCVHistoWithError());
          TH1D* h_Lead_region3 = new TH1D(Lead_region3->GetCVHistoWithError());
          TH1D* h_Other_region3 = new TH1D(Other_region3->GetCVHistoWithError());

          h_Carbon_Combined->Add(h_Carbon_region3);
          h_Iron_Combined->Add(  h_Iron_region3);
          h_Lead_Combined->Add(  h_Lead_region3);
          h_Other_Combined->Add( h_Other_region3);
          h_data_Combined->Add(  h_data_region3);

          TH1D* h_data_region4 = new TH1D(data_region4->GetCVHistoWithError());
          TH1D* h_Helium_region4 = new TH1D(Helium_region4->GetCVHistoWithError());
          TH1D* h_Aluminium_region4 = new TH1D(Aluminium_region4->GetCVHistoWithError());

          TH1D* h_Carbon_region4 = new TH1D(Carbon_region4->GetCVHistoWithError());
          TH1D* h_Iron_region4 = new TH1D(Iron_region4->GetCVHistoWithError());
          TH1D* h_Lead_region4 = new TH1D(Lead_region4->GetCVHistoWithError());
          TH1D* h_Other_region4 = new TH1D(Other_region4->GetCVHistoWithError());


          h_Carbon_Combined->Add(h_Carbon_region4);
          h_Iron_Combined->Add(h_Iron_region4);
          h_Lead_Combined->Add(h_Lead_region4);
          h_Other_Combined->Add(h_Other_region4);

          h_data_Combined->Add(h_data_region4);

          ColorHists(h_Carbon_Combined, h_Iron_Combined, h_Lead_Combined,  h_Other_Combined);
          ColorData(h_data_Combined);
          Color_HeliumHists(h_Helium_region1, h_Helium_region2, h_Helium_region3, h_Helium_region4);
          Color_AluminiumHists(h_Aluminium_region1, h_Aluminium_region2, h_Aluminium_region3, h_Aluminium_region4);

          // MC Total depend on the Modification
          //      If Raws - take the mc_total directly
          //      If Modified - Add all mc models;

          TH1D* h_mc_total = new TH1D(mc_total->GetCVHistoWithError());

          h_mc_total->SetName("h_mc_total");

          double plot_chisq;
          //double plot_chisq = calc_ChiSq(data, signal, WithPi0, QELike, SinglePiPlus, Other);

          if(UseLogChi == false){plot_chisq = calc_ChiSq(h_data_Combined,
            h_Helium_region1,
            h_Helium_region2,
            h_Helium_region3,
            h_Helium_region4,
            h_Aluminium_region1,
            h_Aluminium_region2,
            h_Aluminium_region3,
            h_Aluminium_region4,
            h_Carbon_Combined, h_Lead_Combined, h_Iron_Combined, h_Other_Combined);}
          else if(UseLogChi == true){plot_chisq = calc_LogChiSq(h_data_Combined,
            h_Helium_region1,
            h_Helium_region2,
            h_Helium_region3,
            h_Helium_region4,
            h_Aluminium_region1,
            h_Aluminium_region2,
            h_Aluminium_region3,
            h_Aluminium_region4,
            h_Carbon_Combined, h_Lead_Combined, h_Iron_Combined, h_Other_Combined);}


            h_Other_Combined->Add(h_Carbon_Combined);
            h_Other_Combined->Add(h_Iron_Combined);
            h_Other_Combined->Add(h_Lead_Combined);


            if(doAreaNormalized == true){

              if(h_mc_total->GetNbinsX() !=h_data_Combined->GetNbinsX()){std::cout<<"~~~ Whoah Data and MC have different number of Bins HistTitle : "<< Hist_title<<std::endl; assert(false); }
              double MCArea = h_mc_total->Integral(1,h_mc_total->GetNbinsX());
              double DataArea = h_data_Combined->Integral(1,h_data_Combined->GetNbinsX());
              double areascaler = DataArea / MCArea;

              h_mc_total->Scale(areascaler);

              h_Helium_region1->Scale(areascaler);
              h_Aluminium_region1->Scale(areascaler);

              h_Helium_region2->Scale(areascaler);
              h_Aluminium_region2->Scale(areascaler);

              h_Helium_region3->Scale(areascaler);
              h_Aluminium_region3->Scale(areascaler);

              h_Helium_region4->Scale(areascaler);
              h_Aluminium_region4->Scale(areascaler);

              //h_Carbon_Combined->Scale(areascaler);
              //h_Iron_Combined->Scale(areascaler);
              //h_Lead_Combined->Scale(areascaler);
              h_Other_Combined->Scale(areascaler);

            }

            //////////////////////////////////////
            //// Combining All Other
            //////////////////////////////////////



          std::string yaxis;
          if(MakeBinWidth==true){

            h_mc_total->Scale(1.0, "width");

            h_Helium_region1->Scale(1.0, "width");
            h_Aluminium_region1->Scale(1.0, "width");

            h_Helium_region2->Scale(1.0, "width");
            h_Aluminium_region2->Scale(1.0, "width");

            h_Helium_region3->Scale(1.0, "width");
            h_Aluminium_region3->Scale(1.0, "width");

            h_Helium_region4->Scale(1.0, "width");
            h_Aluminium_region4->Scale(1.0, "width");

            //h_Carbon_Combined->Scale(1.0, "width");
            //h_Iron_Combined->Scale(1.0, "width");
            //h_Lead_Combined->Scale(1.0, "width");
            h_Other_Combined->Scale(1.0, "width");
            h_data_Combined->Scale(1.0, "width");

            double binwidth_title = h_mc_total -> GetBinWidth(3);
            yaxis = Form("NEvents / %.2f",binwidth_title);
            if(doAreaNormalized == true){yaxis = Form("[DataAreaNorm] NEvents / %.2f",binwidth_title);}
            //std::cout<< "yaxis = "<< yaxis<<std::endl;
            //std::cout<<"Finished Bin width Norm"<<std::endl;
          }
          else{
            yaxis = "NEvents";
          //  std::cout<<"FInished Bin NOT width Norm"<<std::endl;
          }

          // ------------------------------------------------------------------------
          // Unique Plot for Single Error Band, Single Universe
          //      Comment this section out
          // ------------------------------------------------------------------------


          // Create Canvas and Divide it into two
          TCanvas* c = new TCanvas("c","c",800, 800);
          //TCanvas cE("cE","cE", 800, 800);
          // Upper Pad is the Data vs MC
          //OLDTPad *pad1 = new TPad("pad1", "pad1", 0.05, 0.3, 1, 1.0);
          TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
          pad1->SetBottomMargin(0); // Top and Bottom Plots attached
          pad1->Draw();
          pad1->cd(); // pad1 is the current pad
            // Plot MC Models as THStack
          THStack* hs = new THStack("hs","");
          h_Helium_region1->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
          hs->Add(h_Helium_region1);
          hs->Add(h_Helium_region2);
          hs->Add(h_Helium_region3);
          hs->Add(h_Helium_region4);
          hs->Add(h_Aluminium_region1);
          hs->Add(h_Aluminium_region2);
          hs->Add(h_Aluminium_region3);
          hs->Add(h_Aluminium_region4);
        //  hs->Add(h_Carbon_Combined);
          //hs->Add(h_Iron_Combined);
          //hs->Add(h_Lead_Combined);
          hs->Add(h_Other_Combined);

          //std::cout<<"Finished adding hist to hs II"<<std::endl;

          // Styling
          hs->Draw("HIST");
          hs->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
          hs->GetYaxis()->SetTitle(Form("%s",yaxis.c_str()));
          hs->GetYaxis()->SetTitleFont(62);
          hs->GetYaxis()->SetTitleSize(0.06);
          hs->GetXaxis()->SetTitleSize(0.06);
          hs->GetXaxis()->CenterTitle();
          //hs->GetYaxis()->SetTitleOffset(1.2);
          hs->GetYaxis()->SetLabelFont(42);
          hs->GetYaxis()->SetLabelSize(0.05);

        if(applyMaxY==false){
          if(h_mc_total->GetMaximum()>h_data_Combined->GetMaximum()  ){
            hs->SetMaximum(h_mc_total->GetMaximum() * 1.45);
          }
          else { hs->SetMaximum(h_data_Combined->GetMaximum() * 1.45);}
         }
        else if (applyMaxY==true){
         hs->SetMaximum(MaxY);
        }


  //        hs->SetMaximum(hist_max * 1.45);

          h_mc_total->SetMarkerStyle(0);
          h_mc_total->SetLineWidth(2);
          h_mc_total->SetLineColor(kBlack);
          h_mc_total->SetFillStyle(0);
          h_mc_total->Draw("Same hist");


          //std::cout<<"Finshed Drawing Hist "<<std::endl;

          // Add Data Plot
          h_data_Combined->Draw("SAME E1 X0");
          //std::cout<<"FInished Drawing h_data"<<std::endl;

          // Add Legend
          TLegend *legend = new TLegend(0.85,0.4,0.95,0.92);
          legend->AddEntry(h_data_Combined, "Data");
          legend->AddEntry(h_mc_total, "Total MC");
          // Add Weights as Text to Modified Plot
          int nPoints = h_data_Combined->GetNbinsX();
          //int nPoints_Fit = nPoints - 4;
          //std::cout<<"nPoints = "<<nPoints<< std::endl;

          // Add Plot-ChiSq
          TLatex* text = new TLatex;
          text->SetNDC();
          text->SetTextSize(0.035);
          text->SetTextColor(kRed);




            if (ind == 0){
              //ChiSq_before_fit_var.push_back(plot_chisq);
              ChiSqrt = plot_chisq;
            }


              legend->AddEntry(h_Helium_region1,    "^{4}He USCap ",        "f");
              legend->AddEntry(h_Helium_region2,    "^{4}He Barrel ",       "f");
              legend->AddEntry(h_Helium_region3,    "^{4}He DSCap ",         "f");
              legend->AddEntry(h_Helium_region4,    "^{4}He DScave", "f");
              legend->AddEntry(h_Aluminium_region1, "^{27}Al USCap ",        "f");
              legend->AddEntry(h_Aluminium_region2, "^{27}Al Barrel ",       "f");
              legend->AddEntry(h_Aluminium_region3, "^{27}Al DSCap ",         "f");
              legend->AddEntry(h_Aluminium_region4, "^{27}Al DScave", "f");

              double xplace = .2;
              double y_place_saved = .86;
            //legend->AddEntry(h_Carbon_Combined, "C: ",    "f");
            //legend->AddEntry(h_Iron_Combined,   "Fe: ",   "f");
            //legend->AddEntry(h_Lead_Combined,   "Pb: ",   "f");
            legend->AddEntry(h_Other_Combined,  "Other","f");
            legend->SetBorderSize(0);
            text->SetTextSize(0.03);
            text->DrawLatex(0.2, 0.85, Form("Plot #chi^{2} = %3.2f", plot_chisq));
            text->DrawLatex(0.2, 0.82, Form("Plot #chi^{2}/dof = %3.2f", plot_chisq / (double) nPoints));
            legend->SetTextSize(0.032);
            legend->SetTextFont(42);
            legend->Draw();
            text->SetTextSize(0.02);
            text->SetTextColor(kBlack);

            if(includeboundary==true){
              text->SetTextSize(0.03);
              text->DrawLatex(xplace + .31 , y_place_saved, Form("Boundaries"));
              y_place_saved-=.022;
              text->SetTextSize(0.025);
              text->DrawLatex(xplace + .28 , y_place_saved, Form("#color[4]{upstream/barrel = %3.2f [mm]}",boundary_upstream_barrel  ));
              y_place_saved-=.022;
              text->DrawLatex(xplace + .28 , y_place_saved, Form("#color[4]{barrel/downstream = %3.2f [mm]}",boundary_barrel_downstream  ));
              y_place_saved-=.022;
              text->DrawLatex(xplace + .28 , y_place_saved, Form("#color[4]{downstream/concave = %3.2f [mm]}",boundary_downstream_concave ));
            }




          if (ind != 0 &&  FitType== 1){
          int nPars = 4;
          double yplace = 0.80;
          text->DrawLatex(xplace, yplace, Form("Fit Results with %d points, %d pars", nPoints, nPars));
          yplace-=.02;
          text->DrawLatex(xplace, yplace , Form("Before Fit #chi^{2} = %3.2f", ChiSqrt));
          yplace-=.02;
          text->DrawLatex(xplace, yplace, Form("Before Fit #chi^{2}/dof = %3.2f", ChiSqrt/(nPoints-nPars)));
          yplace-=.02;
          text->DrawLatex(xplace, yplace, Form("After Fit #chi^{2} = %3.2f", plot_chisq));
          yplace-=.02;
          text->DrawLatex(xplace, yplace, Form("After Fit #chi^{2}/dof = %3.2f", plot_chisq/(double)(nPoints-nPars)));
          yplace-=.02;
          text->DrawLatex(xplace, yplace, Form("#color[4]{USCap wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[0], err_Aluminium[0]));
          yplace-=.02;
          y_place_saved = yplace;
          text->DrawLatex(xplace, yplace, Form("#color[4]{Barrel wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[1], err_Aluminium[1]));
          yplace-=.02;
          text->DrawLatex(xplace, yplace, Form("#color[4]{DSCap wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[2], err_Aluminium[2]));
          yplace-=.02;
          text->DrawLatex(xplace, yplace, Form("#color[4]{DSConcave  wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[3], err_Aluminium[3]));
          yplace-=.02;
          ChiSqrtAfter = plot_chisq;

          }






          else if (ind != 0 && FitType == 2){
          int nPars = 4;
            double xplace = .2;
            double yplace = 0.80;
            text->DrawLatex(xplace, yplace, Form("Fit Results with %d points, %d pars", nPoints, nPars));
            yplace-=.02;
            text->DrawLatex(xplace, yplace , Form("Before Fit #chi^{2} = %3.2f", ChiSqrt));
            yplace-=.02;
            text->DrawLatex(xplace, yplace, Form("Before Fit #chi^{2}/dof = %3.2f", ChiSqrt/(nPoints-nPars)));
            yplace-=.02;
            text->DrawLatex(xplace, yplace, Form("After Fit #chi^{2} = %3.2f", plot_chisq));
            yplace-=.02;
            text->DrawLatex(xplace, yplace, Form("After Fit #chi^{2}/dof = %3.2f", plot_chisq/(double)(nPoints-nPars)));
            yplace-=.02;
            text->DrawLatex(xplace, yplace, Form("#color[4]{USCap wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[0], err_Aluminium[0]));
            yplace-=.02;
            text->DrawLatex(xplace, yplace, Form("#color[4]{Barrel wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[1], err_Aluminium[1]));
            yplace-=.02;
            text->DrawLatex(xplace, yplace, Form("#color[4]{DSCap wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[2], err_Aluminium[2]));
            yplace-=.02;
            text->DrawLatex(xplace, yplace, Form("#color[4]{DScave  wgt(He) = %3.2f #pm %3.2f}", wgt_Aluminium[3], err_Aluminium[3]));
            yplace-=.02;
            text->DrawLatex(xplace, yplace, Form("#color[4]{USCap wgt(He) = %3.2f #pm %3.2f}", wgt_Helium[0], err_Helium[0]));
            yplace-=.02;
            text->DrawLatex(xplace, yplace, Form("#color[4]{barrel wgt(He) = %3.2f #pm %3.2f}", wgt_Helium[1], err_Helium[1]));
            yplace-=.02;
            text->DrawLatex(xplace, yplace, Form("#color[4]{DSCap wgt(He) = %3.2f #pm %3.2f}", wgt_Helium[2], err_Helium[2]));
            yplace-=.02;
            text->DrawLatex(xplace, yplace, Form("#color[4]{DScave  wgt(He) = %3.2f #pm %3.2f}", wgt_Helium[3], err_Helium[3]));

            ChiSqrtAfter = plot_chisq;

          }



          delete text;
          plotter->AddHistoTitle(Hist_title.c_str(),.04);
          plotter->WritePreliminary("TL", .025, 0, 0, false);
          // Plot Lower Plot: Data vs MC Ratio
          c->cd(); // Go back to default Canvas before creating 2nd Pad
          //TPad *pad2 = new TPad("pad2", "pad2", 0.05, 0.05, 1, 0.3);

          //pad2->SetTopMargin(0);
          //pad2->SetBottomMargin(0.2);
          c->Modified();
          TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
          pad2->SetTopMargin(0);
          pad2->SetBottomMargin(0.25); //.2
          pad2->SetGridx(); // vertical grid
          pad2->Draw();
          pad2->cd();

          // Calculate the Ratio

          //h_data_mc_ratio->Draw("HIST");
          plotter->axis_title_size_x = 0.1;
          plotter->axis_title_offset_y = .4;
          plotter->axis_title_offset_x = 1.2;
          plotter->axis_title_size_y = 0.12;
          plotter->axis_label_size = 0.1;
          plotter->axis_maximum = 2.5;
          plotter->axis_minimum = .5;
          plotter->DrawDataMCRatio(data, mc_total, 1.0, false, false , -.5, 3, "#frac{Data}{MC}", false);
          // Add Ratio = 1 Line
          TLine ratio_1;
          ratio_1.SetLineWidth(2);
          ratio_1.SetLineStyle(7);
          ratio_1.SetLineColor(kBlue);
          double line_min = h_data_Combined->GetBinLowEdge(1);
          double line_max = h_data_Combined->GetBinLowEdge(h_data_Combined->GetNbinsX()+1);
          ratio_1.DrawLine(line_min,1,line_max,1);
          // Plot Output
          c->Update();
          c->cd();
          c->Print(pdf_label.c_str(),"pdf");
          delete plotter;
          delete legend;
          delete hs;
          delete pad1;
          delete pad2;
          delete c;
          delete data;
          delete mc_total;
          delete h_data_Combined;
          delete h_Helium_region1;
          delete h_Aluminium_region1;
          delete h_Carbon_Combined;
          delete h_Iron_Combined;
          delete h_Lead_Combined;
          delete h_Other_Combined;
          delete h_data_region2;
          delete h_Helium_region2;
          delete h_Aluminium_region2;
          delete h_Carbon_region2;
          delete h_Iron_region2;
          delete h_Lead_region2;
          delete h_Other_region2;
          delete h_data_region3;
          delete h_Helium_region3;
          delete h_Aluminium_region3;
          delete h_Carbon_region3;
          delete h_Iron_region3;
          delete h_Lead_region3;
          delete h_Other_region3;
          delete h_data_region4;
          delete h_Helium_region4;
          delete h_Aluminium_region4;
          delete h_Carbon_region4;
          delete h_Iron_region4;
          delete h_Lead_region4;
          delete h_Other_region4;
        }

void Convolution_Tool::Plot_regions(ConvolutionShiftMap inputMap, int ind,
  int FitType, std::string Hist_title,
  bool doAreaNormalized, bool applyMaxY) {
    std::string Title_output;

    double Chisqrt = 999;
    double ChisqrtAfter = 999;

    Title_output = Hist_title + "";

    Plot_regions_Material(
      globalpdf_labelwithpdf, ind,
      inputMap.Vertex_X_Regions.Upstream.MnvH1D_data,
      inputMap.Vertex_X_Regions.Upstream.MnvH1D_mc_Convoluted_Helium[ind],
      inputMap.Vertex_X_Regions.Upstream.MnvH1D_mc_Convoluted_Aluminium[ind],
      inputMap.Vertex_X_Regions.Upstream.MnvH1D_mc_Convoluted_Carbon[ind],
      inputMap.Vertex_X_Regions.Upstream.MnvH1D_mc_Convoluted_Iron[ind],
      inputMap.Vertex_X_Regions.Upstream.MnvH1D_mc_Convoluted_Lead[ind],
      inputMap.Vertex_X_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
      inputMap.Vertex_X_Regions.Barrel.MnvH1D_data,
      inputMap.Vertex_X_Regions.Barrel.MnvH1D_mc_Convoluted_Helium[ind],
      inputMap.Vertex_X_Regions.Barrel.MnvH1D_mc_Convoluted_Aluminium[ind],
      inputMap.Vertex_X_Regions.Barrel.MnvH1D_mc_Convoluted_Carbon[ind],
      inputMap.Vertex_X_Regions.Barrel.MnvH1D_mc_Convoluted_Iron[ind],
      inputMap.Vertex_X_Regions.Barrel.MnvH1D_mc_Convoluted_Lead[ind],
      inputMap.Vertex_X_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
      inputMap.Vertex_X_Regions.Downstream.MnvH1D_data,
      inputMap.Vertex_X_Regions.Downstream.MnvH1D_mc_Convoluted_Helium[ind],
      inputMap.Vertex_X_Regions.Downstream.MnvH1D_mc_Convoluted_Aluminium[ind],
      inputMap.Vertex_X_Regions.Downstream.MnvH1D_mc_Convoluted_Carbon[ind],
      inputMap.Vertex_X_Regions.Downstream.MnvH1D_mc_Convoluted_Iron[ind],
      inputMap.Vertex_X_Regions.Downstream.MnvH1D_mc_Convoluted_Lead[ind],
      inputMap.Vertex_X_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
      inputMap.Vertex_X_Regions.Concave.MnvH1D_data,
      inputMap.Vertex_X_Regions.Concave.MnvH1D_mc_Convoluted_Helium[ind],
      inputMap.Vertex_X_Regions.Concave.MnvH1D_mc_Convoluted_Aluminium[ind],
      inputMap.Vertex_X_Regions.Concave.MnvH1D_mc_Convoluted_Carbon[ind],
      inputMap.Vertex_X_Regions.Concave.MnvH1D_mc_Convoluted_Iron[ind],
      inputMap.Vertex_X_Regions.Concave.MnvH1D_mc_Convoluted_Lead[ind],
      inputMap.Vertex_X_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
      Title_output, "Vertex X", Chisqrt, ChisqrtAfter, FitType, UseLogChi_Tool,
      global_doAreaNormalized_Tool, set_ymax_forFitVars, YaxisMax_X);
  /////
  // Y
  ////

  Plot_regions_Material(
    globalpdf_labelwithpdf, ind,
    inputMap.Vertex_Y_Regions.Upstream.MnvH1D_data,
    inputMap.Vertex_Y_Regions.Upstream.MnvH1D_mc_Convoluted_Helium[ind],
    inputMap.Vertex_Y_Regions.Upstream.MnvH1D_mc_Convoluted_Aluminium[ind],
    inputMap.Vertex_Y_Regions.Upstream.MnvH1D_mc_Convoluted_Carbon[ind],
    inputMap.Vertex_Y_Regions.Upstream.MnvH1D_mc_Convoluted_Iron[ind],
    inputMap.Vertex_Y_Regions.Upstream.MnvH1D_mc_Convoluted_Lead[ind],
    inputMap.Vertex_Y_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
    inputMap.Vertex_Y_Regions.Barrel.MnvH1D_data,
    inputMap.Vertex_Y_Regions.Barrel.MnvH1D_mc_Convoluted_Helium[ind],
    inputMap.Vertex_Y_Regions.Barrel.MnvH1D_mc_Convoluted_Aluminium[ind],
    inputMap.Vertex_Y_Regions.Barrel.MnvH1D_mc_Convoluted_Carbon[ind],
    inputMap.Vertex_Y_Regions.Barrel.MnvH1D_mc_Convoluted_Iron[ind],
    inputMap.Vertex_Y_Regions.Barrel.MnvH1D_mc_Convoluted_Lead[ind],
    inputMap.Vertex_Y_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
    inputMap.Vertex_Y_Regions.Downstream.MnvH1D_data,
    inputMap.Vertex_Y_Regions.Downstream.MnvH1D_mc_Convoluted_Helium[ind],
    inputMap.Vertex_Y_Regions.Downstream.MnvH1D_mc_Convoluted_Aluminium[ind],
    inputMap.Vertex_Y_Regions.Downstream.MnvH1D_mc_Convoluted_Carbon[ind],
    inputMap.Vertex_Y_Regions.Downstream.MnvH1D_mc_Convoluted_Iron[ind],
    inputMap.Vertex_Y_Regions.Downstream.MnvH1D_mc_Convoluted_Lead[ind],
    inputMap.Vertex_Y_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
    inputMap.Vertex_Y_Regions.Concave.MnvH1D_data,
    inputMap.Vertex_Y_Regions.Concave.MnvH1D_mc_Convoluted_Helium[ind],
    inputMap.Vertex_Y_Regions.Concave.MnvH1D_mc_Convoluted_Aluminium[ind],
    inputMap.Vertex_Y_Regions.Concave.MnvH1D_mc_Convoluted_Carbon[ind],
    inputMap.Vertex_Y_Regions.Concave.MnvH1D_mc_Convoluted_Iron[ind],
    inputMap.Vertex_Y_Regions.Concave.MnvH1D_mc_Convoluted_Lead[ind],
    inputMap.Vertex_Y_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
    Title_output, "Vertex Y [mm]", Chisqrt, ChisqrtAfter, FitType,
    UseLogChi_Tool, global_doAreaNormalized_Tool, set_ymax_forFitVars,
    YaxisMax_Y);
  /////
  // Z
  /////

  Plot_regions_Material(
    globalpdf_labelwithpdf, ind,
    inputMap.Vertex_Z_Regions.Upstream.MnvH1D_data,
    inputMap.Vertex_Z_Regions.Upstream.MnvH1D_mc_Convoluted_Helium[ind],
    inputMap.Vertex_Z_Regions.Upstream.MnvH1D_mc_Convoluted_Aluminium[ind],
    inputMap.Vertex_Z_Regions.Upstream.MnvH1D_mc_Convoluted_Carbon[ind],
    inputMap.Vertex_Z_Regions.Upstream.MnvH1D_mc_Convoluted_Iron[ind],
    inputMap.Vertex_Z_Regions.Upstream.MnvH1D_mc_Convoluted_Lead[ind],
    inputMap.Vertex_Z_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
    inputMap.Vertex_Z_Regions.Barrel.MnvH1D_data,
    inputMap.Vertex_Z_Regions.Barrel.MnvH1D_mc_Convoluted_Helium[ind],
    inputMap.Vertex_Z_Regions.Barrel.MnvH1D_mc_Convoluted_Aluminium[ind],
    inputMap.Vertex_Z_Regions.Barrel.MnvH1D_mc_Convoluted_Carbon[ind],
    inputMap.Vertex_Z_Regions.Barrel.MnvH1D_mc_Convoluted_Iron[ind],
    inputMap.Vertex_Z_Regions.Barrel.MnvH1D_mc_Convoluted_Lead[ind],
    inputMap.Vertex_Z_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
    inputMap.Vertex_Z_Regions.Downstream.MnvH1D_data,
    inputMap.Vertex_Z_Regions.Downstream.MnvH1D_mc_Convoluted_Helium[ind],
    inputMap.Vertex_Z_Regions.Downstream.MnvH1D_mc_Convoluted_Aluminium[ind],
    inputMap.Vertex_Z_Regions.Downstream.MnvH1D_mc_Convoluted_Carbon[ind],
    inputMap.Vertex_Z_Regions.Downstream.MnvH1D_mc_Convoluted_Iron[ind],
    inputMap.Vertex_Z_Regions.Downstream.MnvH1D_mc_Convoluted_Lead[ind],
    inputMap.Vertex_Z_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
    inputMap.Vertex_Z_Regions.Concave.MnvH1D_data,
    inputMap.Vertex_Z_Regions.Concave.MnvH1D_mc_Convoluted_Helium[ind],
    inputMap.Vertex_Z_Regions.Concave.MnvH1D_mc_Convoluted_Aluminium[ind],
    inputMap.Vertex_Z_Regions.Concave.MnvH1D_mc_Convoluted_Carbon[ind],
    inputMap.Vertex_Z_Regions.Concave.MnvH1D_mc_Convoluted_Iron[ind],
    inputMap.Vertex_Z_Regions.Concave.MnvH1D_mc_Convoluted_Lead[ind],
    inputMap.Vertex_Z_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
    Title_output, "Vertex Z [mm]", Chisqrt, ChisqrtAfter, FitType,
    UseLogChi_Tool, global_doAreaNormalized_Tool, set_ymax_forFitVars,
    YaxisMax_Z);
  ////
  // R
  ////

  Plot_regions_Material(
    globalpdf_labelwithpdf, ind,
    inputMap.Vertex_R_Regions.Upstream.MnvH1D_data,
    inputMap.Vertex_R_Regions.Upstream.MnvH1D_mc_Convoluted_Helium[ind],
    inputMap.Vertex_R_Regions.Upstream.MnvH1D_mc_Convoluted_Aluminium[ind],
    inputMap.Vertex_R_Regions.Upstream.MnvH1D_mc_Convoluted_Carbon[ind],
    inputMap.Vertex_R_Regions.Upstream.MnvH1D_mc_Convoluted_Iron[ind],
    inputMap.Vertex_R_Regions.Upstream.MnvH1D_mc_Convoluted_Lead[ind],
    inputMap.Vertex_R_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
    inputMap.Vertex_R_Regions.Barrel.MnvH1D_data,
    inputMap.Vertex_R_Regions.Barrel.MnvH1D_mc_Convoluted_Helium[ind],
    inputMap.Vertex_R_Regions.Barrel.MnvH1D_mc_Convoluted_Aluminium[ind],
    inputMap.Vertex_R_Regions.Barrel.MnvH1D_mc_Convoluted_Carbon[ind],
    inputMap.Vertex_R_Regions.Barrel.MnvH1D_mc_Convoluted_Iron[ind],
    inputMap.Vertex_R_Regions.Barrel.MnvH1D_mc_Convoluted_Lead[ind],
    inputMap.Vertex_R_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
    inputMap.Vertex_R_Regions.Downstream.MnvH1D_data,
    inputMap.Vertex_R_Regions.Downstream.MnvH1D_mc_Convoluted_Helium[ind],
    inputMap.Vertex_R_Regions.Downstream.MnvH1D_mc_Convoluted_Aluminium[ind],
    inputMap.Vertex_R_Regions.Downstream.MnvH1D_mc_Convoluted_Carbon[ind],
    inputMap.Vertex_R_Regions.Downstream.MnvH1D_mc_Convoluted_Iron[ind],
    inputMap.Vertex_R_Regions.Downstream.MnvH1D_mc_Convoluted_Lead[ind],
    inputMap.Vertex_R_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
    inputMap.Vertex_R_Regions.Concave.MnvH1D_data,
    inputMap.Vertex_R_Regions.Concave.MnvH1D_mc_Convoluted_Helium[ind],
    inputMap.Vertex_R_Regions.Concave.MnvH1D_mc_Convoluted_Aluminium[ind],
    inputMap.Vertex_R_Regions.Concave.MnvH1D_mc_Convoluted_Carbon[ind],
    inputMap.Vertex_R_Regions.Concave.MnvH1D_mc_Convoluted_Iron[ind],
    inputMap.Vertex_R_Regions.Concave.MnvH1D_mc_Convoluted_Lead[ind],
    inputMap.Vertex_R_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
    Title_output, "Vertex R", Chisqrt, ChisqrtAfter, FitType, UseLogChi_Tool,
    global_doAreaNormalized_Tool, set_ymax_forFitVars, YaxisMax_R);
  }


void Convolution_Tool::Plot_regions_XYFit(
  ConvolutionShiftMap inputMap, Normal_Fit_ParametersXY inputMapParametersXY,
  int ind, int FitType, std::string Hist_title, bool doAreaNormalized,
  bool applyMaxY, bool isFiduical) {
    std::string Title_output;

    std::stringstream stream;
    double meanX = inputMapParametersXY[kX].mean;
    stream << std::fixed << std::setprecision(1) << meanX;
    std::string meanX_string = stream.str();
    stream.str(std::string());

    double stddevX = inputMapParametersXY[kX].stddev;
    stream << std::fixed << std::setprecision(1) << stddevX;
    std::string stddevX_string = stream.str();
    stream.str(std::string());

    double meanY = inputMapParametersXY[kY].mean;
    stream << std::fixed << std::setprecision(1) << meanY;
    std::string meanY_string = stream.str();
    stream.str(std::string());

    double stddevY = inputMapParametersXY[kY].stddev;
    stream << std::fixed << std::setprecision(1) << stddevY;
    std::string stddevY_string = stream.str();
    stream.str(std::string());

    double Chisqrt = 999;
    double ChisqrtAfter = 999;

    Title_output = Hist_title + " X(#mu,#sigma) = (" + meanX_string + ", " +
    stddevX_string + ") " + " Y(#mu,#sigma) = (" + meanY_string +
    ", " + stddevY_string + ") ";

    Plot_regions_Material(
      globalpdf_labelwithpdf, ind,
      inputMap.Vertex_X_Regions.Upstream.MnvH1D_data,
      inputMap.Vertex_X_Regions.Upstream.MnvH1D_mc_Convoluted_Helium[ind],
      inputMap.Vertex_X_Regions.Upstream.MnvH1D_mc_Convoluted_Aluminium[ind],
      inputMap.Vertex_X_Regions.Upstream.MnvH1D_mc_Convoluted_Carbon[ind],
      inputMap.Vertex_X_Regions.Upstream.MnvH1D_mc_Convoluted_Iron[ind],
      inputMap.Vertex_X_Regions.Upstream.MnvH1D_mc_Convoluted_Lead[ind],
      inputMap.Vertex_X_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
      inputMap.Vertex_X_Regions.Barrel.MnvH1D_data,
      inputMap.Vertex_X_Regions.Barrel.MnvH1D_mc_Convoluted_Helium[ind],
      inputMap.Vertex_X_Regions.Barrel.MnvH1D_mc_Convoluted_Aluminium[ind],
      inputMap.Vertex_X_Regions.Barrel.MnvH1D_mc_Convoluted_Carbon[ind],
      inputMap.Vertex_X_Regions.Barrel.MnvH1D_mc_Convoluted_Iron[ind],
      inputMap.Vertex_X_Regions.Barrel.MnvH1D_mc_Convoluted_Lead[ind],
      inputMap.Vertex_X_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
      inputMap.Vertex_X_Regions.Downstream.MnvH1D_data,
      inputMap.Vertex_X_Regions.Downstream.MnvH1D_mc_Convoluted_Helium[ind],
      inputMap.Vertex_X_Regions.Downstream.MnvH1D_mc_Convoluted_Aluminium[ind],
      inputMap.Vertex_X_Regions.Downstream.MnvH1D_mc_Convoluted_Carbon[ind],
      inputMap.Vertex_X_Regions.Downstream.MnvH1D_mc_Convoluted_Iron[ind],
      inputMap.Vertex_X_Regions.Downstream.MnvH1D_mc_Convoluted_Lead[ind],
      inputMap.Vertex_X_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
      inputMap.Vertex_X_Regions.Concave.MnvH1D_data,
      inputMap.Vertex_X_Regions.Concave.MnvH1D_mc_Convoluted_Helium[ind],
      inputMap.Vertex_X_Regions.Concave.MnvH1D_mc_Convoluted_Aluminium[ind],
      inputMap.Vertex_X_Regions.Concave.MnvH1D_mc_Convoluted_Carbon[ind],
      inputMap.Vertex_X_Regions.Concave.MnvH1D_mc_Convoluted_Iron[ind],
      inputMap.Vertex_X_Regions.Concave.MnvH1D_mc_Convoluted_Lead[ind],
      inputMap.Vertex_X_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
      Title_output, "Vertex X", Chisqrt, ChisqrtAfter, FitType, UseLogChi_Tool,
      global_doAreaNormalized_Tool, set_ymax_forFitVars,
      isFiduical ? YaxisMax_X_Fid : YaxisMax_X);

      ChiSq_after_fit.push_back(ChisqrtAfter);
      ChiSq_before_fit.push_back(Chisqrt);
  /////
  // Y
  ////

  Plot_regions_Material(
    globalpdf_labelwithpdf, ind,
    inputMap.Vertex_Y_Regions.Upstream.MnvH1D_data,
    inputMap.Vertex_Y_Regions.Upstream.MnvH1D_mc_Convoluted_Helium[ind],
    inputMap.Vertex_Y_Regions.Upstream.MnvH1D_mc_Convoluted_Aluminium[ind],
    inputMap.Vertex_Y_Regions.Upstream.MnvH1D_mc_Convoluted_Carbon[ind],
    inputMap.Vertex_Y_Regions.Upstream.MnvH1D_mc_Convoluted_Iron[ind],
    inputMap.Vertex_Y_Regions.Upstream.MnvH1D_mc_Convoluted_Lead[ind],
    inputMap.Vertex_Y_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
    inputMap.Vertex_Y_Regions.Barrel.MnvH1D_data,
    inputMap.Vertex_Y_Regions.Barrel.MnvH1D_mc_Convoluted_Helium[ind],
    inputMap.Vertex_Y_Regions.Barrel.MnvH1D_mc_Convoluted_Aluminium[ind],
    inputMap.Vertex_Y_Regions.Barrel.MnvH1D_mc_Convoluted_Carbon[ind],
    inputMap.Vertex_Y_Regions.Barrel.MnvH1D_mc_Convoluted_Iron[ind],
    inputMap.Vertex_Y_Regions.Barrel.MnvH1D_mc_Convoluted_Lead[ind],
    inputMap.Vertex_Y_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
    inputMap.Vertex_Y_Regions.Downstream.MnvH1D_data,
    inputMap.Vertex_Y_Regions.Downstream.MnvH1D_mc_Convoluted_Helium[ind],
    inputMap.Vertex_Y_Regions.Downstream.MnvH1D_mc_Convoluted_Aluminium[ind],
    inputMap.Vertex_Y_Regions.Downstream.MnvH1D_mc_Convoluted_Carbon[ind],
    inputMap.Vertex_Y_Regions.Downstream.MnvH1D_mc_Convoluted_Iron[ind],
    inputMap.Vertex_Y_Regions.Downstream.MnvH1D_mc_Convoluted_Lead[ind],
    inputMap.Vertex_Y_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
    inputMap.Vertex_Y_Regions.Concave.MnvH1D_data,
    inputMap.Vertex_Y_Regions.Concave.MnvH1D_mc_Convoluted_Helium[ind],
    inputMap.Vertex_Y_Regions.Concave.MnvH1D_mc_Convoluted_Aluminium[ind],
    inputMap.Vertex_Y_Regions.Concave.MnvH1D_mc_Convoluted_Carbon[ind],
    inputMap.Vertex_Y_Regions.Concave.MnvH1D_mc_Convoluted_Iron[ind],
    inputMap.Vertex_Y_Regions.Concave.MnvH1D_mc_Convoluted_Lead[ind],
    inputMap.Vertex_Y_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
    Title_output, "Vertex Y [mm]", Chisqrt, ChisqrtAfter, FitType,
    UseLogChi_Tool, global_doAreaNormalized_Tool, set_ymax_forFitVars,
    isFiduical ? YaxisMax_Y_Fid : YaxisMax_Y);
  /////
  // Z
  /////
  ChiSq_after_fit.push_back(ChisqrtAfter);
  ChiSq_before_fit.push_back(Chisqrt);

  Plot_regions_Material(
    globalpdf_labelwithpdf, ind,
    inputMap.Vertex_Z_Regions.Upstream.MnvH1D_data,
    inputMap.Vertex_Z_Regions.Upstream.MnvH1D_mc_Convoluted_Helium[ind],
    inputMap.Vertex_Z_Regions.Upstream.MnvH1D_mc_Convoluted_Aluminium[ind],
    inputMap.Vertex_Z_Regions.Upstream.MnvH1D_mc_Convoluted_Carbon[ind],
    inputMap.Vertex_Z_Regions.Upstream.MnvH1D_mc_Convoluted_Iron[ind],
    inputMap.Vertex_Z_Regions.Upstream.MnvH1D_mc_Convoluted_Lead[ind],
    inputMap.Vertex_Z_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
    inputMap.Vertex_Z_Regions.Barrel.MnvH1D_data,
    inputMap.Vertex_Z_Regions.Barrel.MnvH1D_mc_Convoluted_Helium[ind],
    inputMap.Vertex_Z_Regions.Barrel.MnvH1D_mc_Convoluted_Aluminium[ind],
    inputMap.Vertex_Z_Regions.Barrel.MnvH1D_mc_Convoluted_Carbon[ind],
    inputMap.Vertex_Z_Regions.Barrel.MnvH1D_mc_Convoluted_Iron[ind],
    inputMap.Vertex_Z_Regions.Barrel.MnvH1D_mc_Convoluted_Lead[ind],
    inputMap.Vertex_Z_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
    inputMap.Vertex_Z_Regions.Downstream.MnvH1D_data,
    inputMap.Vertex_Z_Regions.Downstream.MnvH1D_mc_Convoluted_Helium[ind],
    inputMap.Vertex_Z_Regions.Downstream.MnvH1D_mc_Convoluted_Aluminium[ind],
    inputMap.Vertex_Z_Regions.Downstream.MnvH1D_mc_Convoluted_Carbon[ind],
    inputMap.Vertex_Z_Regions.Downstream.MnvH1D_mc_Convoluted_Iron[ind],
    inputMap.Vertex_Z_Regions.Downstream.MnvH1D_mc_Convoluted_Lead[ind],
    inputMap.Vertex_Z_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
    inputMap.Vertex_Z_Regions.Concave.MnvH1D_data,
    inputMap.Vertex_Z_Regions.Concave.MnvH1D_mc_Convoluted_Helium[ind],
    inputMap.Vertex_Z_Regions.Concave.MnvH1D_mc_Convoluted_Aluminium[ind],
    inputMap.Vertex_Z_Regions.Concave.MnvH1D_mc_Convoluted_Carbon[ind],
    inputMap.Vertex_Z_Regions.Concave.MnvH1D_mc_Convoluted_Iron[ind],
    inputMap.Vertex_Z_Regions.Concave.MnvH1D_mc_Convoluted_Lead[ind],
    inputMap.Vertex_Z_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
    Title_output, "Vertex Z [mm]", Chisqrt, ChisqrtAfter, FitType,
    UseLogChi_Tool, global_doAreaNormalized_Tool, set_ymax_forFitVars,
    isFiduical ? YaxisMax_Z_Fid : YaxisMax_Z);
 ////
 // R
 ////

 ChiSq_after_fit.push_back(ChisqrtAfter);
 ChiSq_before_fit.push_back(Chisqrt);

 Title_output = Hist_title + " X(#mu,#sigma) = (" + meanX_string + ", " +
 stddevX_string + ") " + " Y(#mu,#sigma) = (" + meanY_string +
 ", " + stddevY_string + ") ";

 Plot_regions_Material(
   globalpdf_labelwithpdf, ind,
   inputMap.Vertex_R_Regions.Upstream.MnvH1D_data,
   inputMap.Vertex_R_Regions.Upstream.MnvH1D_mc_Convoluted_Helium[ind],
   inputMap.Vertex_R_Regions.Upstream.MnvH1D_mc_Convoluted_Aluminium[ind],
   inputMap.Vertex_R_Regions.Upstream.MnvH1D_mc_Convoluted_Carbon[ind],
   inputMap.Vertex_R_Regions.Upstream.MnvH1D_mc_Convoluted_Iron[ind],
   inputMap.Vertex_R_Regions.Upstream.MnvH1D_mc_Convoluted_Lead[ind],
   inputMap.Vertex_R_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
   inputMap.Vertex_R_Regions.Barrel.MnvH1D_data,
   inputMap.Vertex_R_Regions.Barrel.MnvH1D_mc_Convoluted_Helium[ind],
   inputMap.Vertex_R_Regions.Barrel.MnvH1D_mc_Convoluted_Aluminium[ind],
   inputMap.Vertex_R_Regions.Barrel.MnvH1D_mc_Convoluted_Carbon[ind],
   inputMap.Vertex_R_Regions.Barrel.MnvH1D_mc_Convoluted_Iron[ind],
   inputMap.Vertex_R_Regions.Barrel.MnvH1D_mc_Convoluted_Lead[ind],
   inputMap.Vertex_R_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
   inputMap.Vertex_R_Regions.Downstream.MnvH1D_data,
   inputMap.Vertex_R_Regions.Downstream.MnvH1D_mc_Convoluted_Helium[ind],
   inputMap.Vertex_R_Regions.Downstream.MnvH1D_mc_Convoluted_Aluminium[ind],
   inputMap.Vertex_R_Regions.Downstream.MnvH1D_mc_Convoluted_Carbon[ind],
   inputMap.Vertex_R_Regions.Downstream.MnvH1D_mc_Convoluted_Iron[ind],
   inputMap.Vertex_R_Regions.Downstream.MnvH1D_mc_Convoluted_Lead[ind],
   inputMap.Vertex_R_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
   inputMap.Vertex_R_Regions.Concave.MnvH1D_data,
   inputMap.Vertex_R_Regions.Concave.MnvH1D_mc_Convoluted_Helium[ind],
   inputMap.Vertex_R_Regions.Concave.MnvH1D_mc_Convoluted_Aluminium[ind],
   inputMap.Vertex_R_Regions.Concave.MnvH1D_mc_Convoluted_Carbon[ind],
   inputMap.Vertex_R_Regions.Concave.MnvH1D_mc_Convoluted_Iron[ind],
   inputMap.Vertex_R_Regions.Concave.MnvH1D_mc_Convoluted_Lead[ind],
   inputMap.Vertex_R_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
   Title_output, "Vertex R", Chisqrt, ChisqrtAfter, FitType, UseLogChi_Tool,
   global_doAreaNormalized_Tool, set_ymax_forFitVars,
   isFiduical ? YaxisMax_R_Fid : YaxisMax_R);

   ChiSq_after_fit.push_back(ChisqrtAfter);
   ChiSq_before_fit.push_back(Chisqrt);

   if (ind == 0) {
     ChiSq_after_fit.clear();
   }
 }

void Convolution_Tool::Plot_regions_XYZFit(
  ConvolutionShiftMap inputMap, Normal_Fit_ParametersXY inputMapParametersXY,
  double Zmean, double Zsigma, int ind, int FitType, std::string Hist_title,
  bool doAreaNormalized, bool applyMaxY, bool isFiduical, bool isFull_Empty,
  double ZmeanE, double ZsigmaE) {
    std::string Title_output;

    std::stringstream stream;
    double meanX = inputMapParametersXY[kX].mean;
    stream << std::fixed << std::setprecision(1) << meanX;
    std::string meanX_string = stream.str();
    stream.str(std::string());

    double stddevX = inputMapParametersXY[kX].stddev;
    stream << std::fixed << std::setprecision(1) << stddevX;
    std::string stddevX_string = stream.str();
    stream.str(std::string());

    double meanY = inputMapParametersXY[kY].mean;
    stream << std::fixed << std::setprecision(1) << meanY;
    std::string meanY_string = stream.str();
    stream.str(std::string());

    double stddevY = inputMapParametersXY[kY].stddev;
    stream << std::fixed << std::setprecision(1) << stddevY;
    std::string stddevY_string = stream.str();
    stream.str(std::string());

    stream << std::fixed << std::setprecision(1) << Zmean;
    std::string meanZ_string = stream.str();
    stream.str(std::string());

    stream << std::fixed << std::setprecision(1) << Zsigma;
    std::string stddevZ_string = stream.str();
    stream.str(std::string());

    std::string meanZ_string_E;
    std::string stddevZ_string_E;

    if (isFull_Empty == true) {
      stream << std::fixed << std::setprecision(1) << ZmeanE;
      meanZ_string_E = stream.str();
      stream.str(std::string());

      stream << std::fixed << std::setprecision(1) << ZsigmaE;
      stddevZ_string_E = stream.str();
      stream.str(std::string());
    }

    double Chisqrt = 999;
    double ChisqrtAfter = 999;

    if (isFull_Empty == true) {
      Title_output = Hist_title + " X(#mu,#sigma),Y(),Z_{Full},Z_{Empty}  = (" +
      meanX_string + ", " + stddevX_string + "), (" +
      meanY_string + ", " + stddevY_string + "), (" +
      meanZ_string + ", " + stddevZ_string + "),(" +
      meanZ_string_E + ", " + stddevZ_string_E + ")";
    } else {
      Title_output =
      Hist_title + " X(#mu,#sigma),Y(#mu,#sigma),Z(#mu,#sigma)  = (" +
      meanX_string + ", " + stddevX_string + "), (" + meanY_string + ", " +
      stddevY_string + "), (" + meanZ_string + ", " + stddevZ_string + ")";
    }

    Plot_regions_Material(
      globalpdf_labelwithpdf, ind,
      inputMap.Vertex_X_Regions.Upstream.MnvH1D_data,
      inputMap.Vertex_X_Regions.Upstream.MnvH1D_mc_Convoluted_Helium[ind],
      inputMap.Vertex_X_Regions.Upstream.MnvH1D_mc_Convoluted_Aluminium[ind],
      inputMap.Vertex_X_Regions.Upstream.MnvH1D_mc_Convoluted_Carbon[ind],
      inputMap.Vertex_X_Regions.Upstream.MnvH1D_mc_Convoluted_Iron[ind],
      inputMap.Vertex_X_Regions.Upstream.MnvH1D_mc_Convoluted_Lead[ind],
      inputMap.Vertex_X_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
      inputMap.Vertex_X_Regions.Barrel.MnvH1D_data,
      inputMap.Vertex_X_Regions.Barrel.MnvH1D_mc_Convoluted_Helium[ind],
      inputMap.Vertex_X_Regions.Barrel.MnvH1D_mc_Convoluted_Aluminium[ind],
      inputMap.Vertex_X_Regions.Barrel.MnvH1D_mc_Convoluted_Carbon[ind],
      inputMap.Vertex_X_Regions.Barrel.MnvH1D_mc_Convoluted_Iron[ind],
      inputMap.Vertex_X_Regions.Barrel.MnvH1D_mc_Convoluted_Lead[ind],
      inputMap.Vertex_X_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
      inputMap.Vertex_X_Regions.Downstream.MnvH1D_data,
      inputMap.Vertex_X_Regions.Downstream.MnvH1D_mc_Convoluted_Helium[ind],
      inputMap.Vertex_X_Regions.Downstream.MnvH1D_mc_Convoluted_Aluminium[ind],
      inputMap.Vertex_X_Regions.Downstream.MnvH1D_mc_Convoluted_Carbon[ind],
      inputMap.Vertex_X_Regions.Downstream.MnvH1D_mc_Convoluted_Iron[ind],
      inputMap.Vertex_X_Regions.Downstream.MnvH1D_mc_Convoluted_Lead[ind],
      inputMap.Vertex_X_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
      inputMap.Vertex_X_Regions.Concave.MnvH1D_data,
      inputMap.Vertex_X_Regions.Concave.MnvH1D_mc_Convoluted_Helium[ind],
      inputMap.Vertex_X_Regions.Concave.MnvH1D_mc_Convoluted_Aluminium[ind],
      inputMap.Vertex_X_Regions.Concave.MnvH1D_mc_Convoluted_Carbon[ind],
      inputMap.Vertex_X_Regions.Concave.MnvH1D_mc_Convoluted_Iron[ind],
      inputMap.Vertex_X_Regions.Concave.MnvH1D_mc_Convoluted_Lead[ind],
      inputMap.Vertex_X_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
      Title_output, "Vertex X", Chisqrt, ChisqrtAfter, FitType, UseLogChi_Tool,
      global_doAreaNormalized_Tool, set_ymax_forFitVars,
      isFiduical ? YaxisMax_X_Fid : YaxisMax_X);

      ChiSq_after_fit.push_back(ChisqrtAfter);
      ChiSq_before_fit.push_back(Chisqrt);

  /////
  // Y
  ////

  Plot_regions_Material(
    globalpdf_labelwithpdf, ind,
    inputMap.Vertex_Y_Regions.Upstream.MnvH1D_data,
    inputMap.Vertex_Y_Regions.Upstream.MnvH1D_mc_Convoluted_Helium[ind],
    inputMap.Vertex_Y_Regions.Upstream.MnvH1D_mc_Convoluted_Aluminium[ind],
    inputMap.Vertex_Y_Regions.Upstream.MnvH1D_mc_Convoluted_Carbon[ind],
    inputMap.Vertex_Y_Regions.Upstream.MnvH1D_mc_Convoluted_Iron[ind],
    inputMap.Vertex_Y_Regions.Upstream.MnvH1D_mc_Convoluted_Lead[ind],
    inputMap.Vertex_Y_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
    inputMap.Vertex_Y_Regions.Barrel.MnvH1D_data,
    inputMap.Vertex_Y_Regions.Barrel.MnvH1D_mc_Convoluted_Helium[ind],
    inputMap.Vertex_Y_Regions.Barrel.MnvH1D_mc_Convoluted_Aluminium[ind],
    inputMap.Vertex_Y_Regions.Barrel.MnvH1D_mc_Convoluted_Carbon[ind],
    inputMap.Vertex_Y_Regions.Barrel.MnvH1D_mc_Convoluted_Iron[ind],
    inputMap.Vertex_Y_Regions.Barrel.MnvH1D_mc_Convoluted_Lead[ind],
    inputMap.Vertex_Y_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
    inputMap.Vertex_Y_Regions.Downstream.MnvH1D_data,
    inputMap.Vertex_Y_Regions.Downstream.MnvH1D_mc_Convoluted_Helium[ind],
    inputMap.Vertex_Y_Regions.Downstream.MnvH1D_mc_Convoluted_Aluminium[ind],
    inputMap.Vertex_Y_Regions.Downstream.MnvH1D_mc_Convoluted_Carbon[ind],
    inputMap.Vertex_Y_Regions.Downstream.MnvH1D_mc_Convoluted_Iron[ind],
    inputMap.Vertex_Y_Regions.Downstream.MnvH1D_mc_Convoluted_Lead[ind],
    inputMap.Vertex_Y_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
    inputMap.Vertex_Y_Regions.Concave.MnvH1D_data,
    inputMap.Vertex_Y_Regions.Concave.MnvH1D_mc_Convoluted_Helium[ind],
    inputMap.Vertex_Y_Regions.Concave.MnvH1D_mc_Convoluted_Aluminium[ind],
    inputMap.Vertex_Y_Regions.Concave.MnvH1D_mc_Convoluted_Carbon[ind],
    inputMap.Vertex_Y_Regions.Concave.MnvH1D_mc_Convoluted_Iron[ind],
    inputMap.Vertex_Y_Regions.Concave.MnvH1D_mc_Convoluted_Lead[ind],
    inputMap.Vertex_Y_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
    Title_output, "Vertex Y [mm]", Chisqrt, ChisqrtAfter, FitType,
    UseLogChi_Tool, global_doAreaNormalized_Tool, set_ymax_forFitVars,
    isFiduical ? YaxisMax_Y_Fid : YaxisMax_Y);

    ChiSq_after_fit.push_back(ChisqrtAfter);
    ChiSq_before_fit.push_back(Chisqrt);

  /////
  // Z
  /////

  Plot_regions_Material(
    globalpdf_labelwithpdf, ind,
    inputMap.Vertex_Z_Regions.Upstream.MnvH1D_data,
    inputMap.Vertex_Z_Regions.Upstream.MnvH1D_mc_Convoluted_Helium[ind],
    inputMap.Vertex_Z_Regions.Upstream.MnvH1D_mc_Convoluted_Aluminium[ind],
    inputMap.Vertex_Z_Regions.Upstream.MnvH1D_mc_Convoluted_Carbon[ind],
    inputMap.Vertex_Z_Regions.Upstream.MnvH1D_mc_Convoluted_Iron[ind],
    inputMap.Vertex_Z_Regions.Upstream.MnvH1D_mc_Convoluted_Lead[ind],
    inputMap.Vertex_Z_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
    inputMap.Vertex_Z_Regions.Barrel.MnvH1D_data,
    inputMap.Vertex_Z_Regions.Barrel.MnvH1D_mc_Convoluted_Helium[ind],
    inputMap.Vertex_Z_Regions.Barrel.MnvH1D_mc_Convoluted_Aluminium[ind],
    inputMap.Vertex_Z_Regions.Barrel.MnvH1D_mc_Convoluted_Carbon[ind],
    inputMap.Vertex_Z_Regions.Barrel.MnvH1D_mc_Convoluted_Iron[ind],
    inputMap.Vertex_Z_Regions.Barrel.MnvH1D_mc_Convoluted_Lead[ind],
    inputMap.Vertex_Z_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
    inputMap.Vertex_Z_Regions.Downstream.MnvH1D_data,
    inputMap.Vertex_Z_Regions.Downstream.MnvH1D_mc_Convoluted_Helium[ind],
    inputMap.Vertex_Z_Regions.Downstream.MnvH1D_mc_Convoluted_Aluminium[ind],
    inputMap.Vertex_Z_Regions.Downstream.MnvH1D_mc_Convoluted_Carbon[ind],
    inputMap.Vertex_Z_Regions.Downstream.MnvH1D_mc_Convoluted_Iron[ind],
    inputMap.Vertex_Z_Regions.Downstream.MnvH1D_mc_Convoluted_Lead[ind],
    inputMap.Vertex_Z_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
    inputMap.Vertex_Z_Regions.Concave.MnvH1D_data,
    inputMap.Vertex_Z_Regions.Concave.MnvH1D_mc_Convoluted_Helium[ind],
    inputMap.Vertex_Z_Regions.Concave.MnvH1D_mc_Convoluted_Aluminium[ind],
    inputMap.Vertex_Z_Regions.Concave.MnvH1D_mc_Convoluted_Carbon[ind],
    inputMap.Vertex_Z_Regions.Concave.MnvH1D_mc_Convoluted_Iron[ind],
    inputMap.Vertex_Z_Regions.Concave.MnvH1D_mc_Convoluted_Lead[ind],
    inputMap.Vertex_Z_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
    Title_output, "Vertex Z [mm]", Chisqrt, ChisqrtAfter, FitType,
    UseLogChi_Tool, global_doAreaNormalized_Tool, set_ymax_forFitVars,
    isFiduical ? YaxisMax_Z_Fid : YaxisMax_Z);

    ChiSq_after_fit.push_back(ChisqrtAfter);
    ChiSq_before_fit.push_back(Chisqrt);

  ////
  // R
  ////

  Plot_regions_Material(
    globalpdf_labelwithpdf, ind,
    inputMap.Vertex_R_Regions.Upstream.MnvH1D_data,
    inputMap.Vertex_R_Regions.Upstream.MnvH1D_mc_Convoluted_Helium[ind],
    inputMap.Vertex_R_Regions.Upstream.MnvH1D_mc_Convoluted_Aluminium[ind],
    inputMap.Vertex_R_Regions.Upstream.MnvH1D_mc_Convoluted_Carbon[ind],
    inputMap.Vertex_R_Regions.Upstream.MnvH1D_mc_Convoluted_Iron[ind],
    inputMap.Vertex_R_Regions.Upstream.MnvH1D_mc_Convoluted_Lead[ind],
    inputMap.Vertex_R_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
    inputMap.Vertex_R_Regions.Barrel.MnvH1D_data,
    inputMap.Vertex_R_Regions.Barrel.MnvH1D_mc_Convoluted_Helium[ind],
    inputMap.Vertex_R_Regions.Barrel.MnvH1D_mc_Convoluted_Aluminium[ind],
    inputMap.Vertex_R_Regions.Barrel.MnvH1D_mc_Convoluted_Carbon[ind],
    inputMap.Vertex_R_Regions.Barrel.MnvH1D_mc_Convoluted_Iron[ind],
    inputMap.Vertex_R_Regions.Barrel.MnvH1D_mc_Convoluted_Lead[ind],
    inputMap.Vertex_R_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
    inputMap.Vertex_R_Regions.Downstream.MnvH1D_data,
    inputMap.Vertex_R_Regions.Downstream.MnvH1D_mc_Convoluted_Helium[ind],
    inputMap.Vertex_R_Regions.Downstream.MnvH1D_mc_Convoluted_Aluminium[ind],
    inputMap.Vertex_R_Regions.Downstream.MnvH1D_mc_Convoluted_Carbon[ind],
    inputMap.Vertex_R_Regions.Downstream.MnvH1D_mc_Convoluted_Iron[ind],
    inputMap.Vertex_R_Regions.Downstream.MnvH1D_mc_Convoluted_Lead[ind],
    inputMap.Vertex_R_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
    inputMap.Vertex_R_Regions.Concave.MnvH1D_data,
    inputMap.Vertex_R_Regions.Concave.MnvH1D_mc_Convoluted_Helium[ind],
    inputMap.Vertex_R_Regions.Concave.MnvH1D_mc_Convoluted_Aluminium[ind],
    inputMap.Vertex_R_Regions.Concave.MnvH1D_mc_Convoluted_Carbon[ind],
    inputMap.Vertex_R_Regions.Concave.MnvH1D_mc_Convoluted_Iron[ind],
    inputMap.Vertex_R_Regions.Concave.MnvH1D_mc_Convoluted_Lead[ind],
    inputMap.Vertex_R_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
    Title_output, "Vertex R", Chisqrt, ChisqrtAfter, FitType, UseLogChi_Tool,
    global_doAreaNormalized_Tool, set_ymax_forFitVars,
    isFiduical ? YaxisMax_R_Fid : YaxisMax_R);

    ChiSq_after_fit.push_back(ChisqrtAfter);
    ChiSq_before_fit.push_back(Chisqrt);

    if (ind == 0) {
      ChiSq_after_fit.clear();
    }
  }




void Convolution_Tool::Plot_regions_XYZFit_TRUE(
  ConvolutionShiftMap inputMap, Normal_Fit_ParametersXY inputMapParametersXY,
  double Zmean, double Zsigma, int ind, int FitType, std::string Hist_title,
  bool doAreaNormalized, bool applyMaxY, bool isFiduical) {
    std::string Title_output;

    std::stringstream stream;
    double meanX = inputMapParametersXY[kX].mean;
    stream << std::fixed << std::setprecision(1) << meanX;
    std::string meanX_string = stream.str();
    stream.str(std::string());

    double stddevX = inputMapParametersXY[kX].stddev;
    stream << std::fixed << std::setprecision(1) << stddevX;
    std::string stddevX_string = stream.str();
    stream.str(std::string());

    double meanY = inputMapParametersXY[kY].mean;
    stream << std::fixed << std::setprecision(1) << meanY;
    std::string meanY_string = stream.str();
    stream.str(std::string());

    double stddevY = inputMapParametersXY[kY].stddev;
    stream << std::fixed << std::setprecision(1) << stddevY;
    std::string stddevY_string = stream.str();
    stream.str(std::string());

    stream << std::fixed << std::setprecision(1) << Zmean;
    std::string meanZ_string = stream.str();
    stream.str(std::string());

    stream << std::fixed << std::setprecision(1) << Zsigma;
    std::string stddevZ_string = stream.str();
    stream.str(std::string());

    double Chisqrt = 999;
    double ChisqrtAfter = 999;

    Title_output =
    Hist_title + " X(#mu,#sigma),Y(#mu,#sigma),Z(#mu,#sigma)  = (" +
    meanX_string + ", " + stddevX_string + "), (" + meanY_string + ", " +
    stddevY_string + "), (" + meanZ_string + ", " + stddevZ_string + ")";

    std::cout << "trying to plot True x" << std::endl;

    Plot_regions_Material(
      globalpdf_labelwithpdf, ind,
      inputMap.Vertex_X_Regions.Upstream.MnvH1D_data,
      inputMap.Vertex_TRUE_X_Regions.Upstream.MnvH1D_mc_Convoluted_Helium[ind],
      inputMap.Vertex_TRUE_X_Regions.Upstream.MnvH1D_mc_Convoluted_Aluminium[ind],
      inputMap.Vertex_TRUE_X_Regions.Upstream.MnvH1D_mc_Convoluted_Carbon[ind],
      inputMap.Vertex_TRUE_X_Regions.Upstream.MnvH1D_mc_Convoluted_Iron[ind],
      inputMap.Vertex_TRUE_X_Regions.Upstream.MnvH1D_mc_Convoluted_Lead[ind],
      inputMap.Vertex_TRUE_X_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
      inputMap.Vertex_X_Regions.Barrel.MnvH1D_data,
      inputMap.Vertex_TRUE_X_Regions.Barrel.MnvH1D_mc_Convoluted_Helium[ind],
      inputMap.Vertex_TRUE_X_Regions.Barrel.MnvH1D_mc_Convoluted_Aluminium[ind],
      inputMap.Vertex_TRUE_X_Regions.Barrel.MnvH1D_mc_Convoluted_Carbon[ind],
      inputMap.Vertex_TRUE_X_Regions.Barrel.MnvH1D_mc_Convoluted_Iron[ind],
      inputMap.Vertex_TRUE_X_Regions.Barrel.MnvH1D_mc_Convoluted_Lead[ind],
      inputMap.Vertex_TRUE_X_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
      inputMap.Vertex_X_Regions.Downstream.MnvH1D_data,
      inputMap.Vertex_TRUE_X_Regions.Downstream.MnvH1D_mc_Convoluted_Helium[ind],
      inputMap.Vertex_TRUE_X_Regions.Downstream.MnvH1D_mc_Convoluted_Aluminium[ind],
      inputMap.Vertex_TRUE_X_Regions.Downstream.MnvH1D_mc_Convoluted_Carbon[ind],
      inputMap.Vertex_TRUE_X_Regions.Downstream.MnvH1D_mc_Convoluted_Iron[ind],
      inputMap.Vertex_TRUE_X_Regions.Downstream.MnvH1D_mc_Convoluted_Lead[ind],
      inputMap.Vertex_TRUE_X_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
      inputMap.Vertex_X_Regions.Concave.MnvH1D_data,
      inputMap.Vertex_TRUE_X_Regions.Concave.MnvH1D_mc_Convoluted_Helium[ind],
      inputMap.Vertex_TRUE_X_Regions.Concave.MnvH1D_mc_Convoluted_Aluminium[ind],
      inputMap.Vertex_TRUE_X_Regions.Concave.MnvH1D_mc_Convoluted_Carbon[ind],
      inputMap.Vertex_TRUE_X_Regions.Concave.MnvH1D_mc_Convoluted_Iron[ind],
      inputMap.Vertex_TRUE_X_Regions.Concave.MnvH1D_mc_Convoluted_Lead[ind],
      inputMap.Vertex_TRUE_X_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
      Title_output, "TRUE Vertex X", Chisqrt, ChisqrtAfter, FitType,
      UseLogChi_Tool, global_doAreaNormalized_Tool, set_ymax_forFitVars,
      isFiduical ? YaxisMax_X_Fid : YaxisMax_X);
      /////
      // Y
      ////
      std::cout << "trying to plot True y" << std::endl;

    Plot_regions_Material(
      globalpdf_labelwithpdf, ind,
      inputMap.Vertex_Y_Regions.Upstream.MnvH1D_data,
      inputMap.Vertex_TRUE_Y_Regions.Upstream.MnvH1D_mc_Convoluted_Helium[ind],
      inputMap.Vertex_TRUE_Y_Regions.Upstream.MnvH1D_mc_Convoluted_Aluminium[ind],
      inputMap.Vertex_TRUE_Y_Regions.Upstream.MnvH1D_mc_Convoluted_Carbon[ind],
      inputMap.Vertex_TRUE_Y_Regions.Upstream.MnvH1D_mc_Convoluted_Iron[ind],
      inputMap.Vertex_TRUE_Y_Regions.Upstream.MnvH1D_mc_Convoluted_Lead[ind],
      inputMap.Vertex_TRUE_Y_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
      inputMap.Vertex_Y_Regions.Barrel.MnvH1D_data,
      inputMap.Vertex_TRUE_Y_Regions.Barrel.MnvH1D_mc_Convoluted_Helium[ind],
      inputMap.Vertex_TRUE_Y_Regions.Barrel.MnvH1D_mc_Convoluted_Aluminium[ind],
      inputMap.Vertex_TRUE_Y_Regions.Barrel.MnvH1D_mc_Convoluted_Carbon[ind],
      inputMap.Vertex_TRUE_Y_Regions.Barrel.MnvH1D_mc_Convoluted_Iron[ind],
      inputMap.Vertex_TRUE_Y_Regions.Barrel.MnvH1D_mc_Convoluted_Lead[ind],
      inputMap.Vertex_TRUE_Y_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
      inputMap.Vertex_Y_Regions.Downstream.MnvH1D_data,
      inputMap.Vertex_TRUE_Y_Regions.Downstream.MnvH1D_mc_Convoluted_Helium[ind],
      inputMap.Vertex_TRUE_Y_Regions.Downstream.MnvH1D_mc_Convoluted_Aluminium[ind],
      inputMap.Vertex_TRUE_Y_Regions.Downstream.MnvH1D_mc_Convoluted_Carbon[ind],
      inputMap.Vertex_TRUE_Y_Regions.Downstream.MnvH1D_mc_Convoluted_Iron[ind],
      inputMap.Vertex_TRUE_Y_Regions.Downstream.MnvH1D_mc_Convoluted_Lead[ind],
      inputMap.Vertex_TRUE_Y_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
      inputMap.Vertex_Y_Regions.Concave.MnvH1D_data,
      inputMap.Vertex_TRUE_Y_Regions.Concave.MnvH1D_mc_Convoluted_Helium[ind],
      inputMap.Vertex_TRUE_Y_Regions.Concave.MnvH1D_mc_Convoluted_Aluminium[ind],
      inputMap.Vertex_TRUE_Y_Regions.Concave.MnvH1D_mc_Convoluted_Carbon[ind],
      inputMap.Vertex_TRUE_Y_Regions.Concave.MnvH1D_mc_Convoluted_Iron[ind],
      inputMap.Vertex_TRUE_Y_Regions.Concave.MnvH1D_mc_Convoluted_Lead[ind],
      inputMap.Vertex_TRUE_Y_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
      Title_output, "TRUE Vertex Y [mm]", Chisqrt, ChisqrtAfter, FitType,
      UseLogChi_Tool, global_doAreaNormalized_Tool, set_ymax_forFitVars,
      isFiduical ? YaxisMax_Y_Fid : YaxisMax_Y);
        /////
        // Z
        /////
        std::cout << "trying to plot True Z" << std::endl;

    Plot_regions_Material(
      globalpdf_labelwithpdf, ind,
      inputMap.Vertex_Z_Regions.Upstream.MnvH1D_data,
      inputMap.Vertex_TRUE_Z_Regions.Upstream.MnvH1D_mc_Convoluted_Helium[ind],
      inputMap.Vertex_TRUE_Z_Regions.Upstream.MnvH1D_mc_Convoluted_Aluminium[ind],
      inputMap.Vertex_TRUE_Z_Regions.Upstream.MnvH1D_mc_Convoluted_Carbon[ind],
      inputMap.Vertex_TRUE_Z_Regions.Upstream.MnvH1D_mc_Convoluted_Iron[ind],
      inputMap.Vertex_TRUE_Z_Regions.Upstream.MnvH1D_mc_Convoluted_Lead[ind],
      inputMap.Vertex_TRUE_Z_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
      inputMap.Vertex_Z_Regions.Barrel.MnvH1D_data,
      inputMap.Vertex_TRUE_Z_Regions.Barrel.MnvH1D_mc_Convoluted_Helium[ind],
      inputMap.Vertex_TRUE_Z_Regions.Barrel.MnvH1D_mc_Convoluted_Aluminium[ind],
      inputMap.Vertex_TRUE_Z_Regions.Barrel.MnvH1D_mc_Convoluted_Carbon[ind],
      inputMap.Vertex_TRUE_Z_Regions.Barrel.MnvH1D_mc_Convoluted_Iron[ind],
      inputMap.Vertex_TRUE_Z_Regions.Barrel.MnvH1D_mc_Convoluted_Lead[ind],
      inputMap.Vertex_TRUE_Z_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
      inputMap.Vertex_Z_Regions.Downstream.MnvH1D_data,
      inputMap.Vertex_TRUE_Z_Regions.Downstream.MnvH1D_mc_Convoluted_Helium[ind],
      inputMap.Vertex_TRUE_Z_Regions.Downstream.MnvH1D_mc_Convoluted_Aluminium[ind],
      inputMap.Vertex_TRUE_Z_Regions.Downstream.MnvH1D_mc_Convoluted_Carbon[ind],
      inputMap.Vertex_TRUE_Z_Regions.Downstream.MnvH1D_mc_Convoluted_Iron[ind],
      inputMap.Vertex_TRUE_Z_Regions.Downstream.MnvH1D_mc_Convoluted_Lead[ind],
      inputMap.Vertex_TRUE_Z_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
      inputMap.Vertex_Z_Regions.Concave.MnvH1D_data,
      inputMap.Vertex_TRUE_Z_Regions.Concave.MnvH1D_mc_Convoluted_Helium[ind],
      inputMap.Vertex_TRUE_Z_Regions.Concave.MnvH1D_mc_Convoluted_Aluminium[ind],
      inputMap.Vertex_TRUE_Z_Regions.Concave.MnvH1D_mc_Convoluted_Carbon[ind],
      inputMap.Vertex_TRUE_Z_Regions.Concave.MnvH1D_mc_Convoluted_Iron[ind],
      inputMap.Vertex_TRUE_Z_Regions.Concave.MnvH1D_mc_Convoluted_Lead[ind],
      inputMap.Vertex_TRUE_Z_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
      Title_output, "TRUE Vertex Z [mm]", Chisqrt, ChisqrtAfter, FitType,
      UseLogChi_Tool, global_doAreaNormalized_Tool, set_ymax_forFitVars,
      isFiduical ? YaxisMax_Z_Fid : YaxisMax_Z);
      ////
      // R
      ////

      std::cout << "trying to plot True r" << std::endl;
      Plot_regions_Material(
        globalpdf_labelwithpdf, ind,
        inputMap.Vertex_R_Regions.Upstream.MnvH1D_data,
        inputMap.Vertex_TRUE_R_Regions.Upstream.MnvH1D_mc_Convoluted_Helium[ind],
        inputMap.Vertex_TRUE_R_Regions.Upstream.MnvH1D_mc_Convoluted_Aluminium[ind],
        inputMap.Vertex_TRUE_R_Regions.Upstream.MnvH1D_mc_Convoluted_Carbon[ind],
        inputMap.Vertex_TRUE_R_Regions.Upstream.MnvH1D_mc_Convoluted_Iron[ind],
        inputMap.Vertex_TRUE_R_Regions.Upstream.MnvH1D_mc_Convoluted_Lead[ind],
        inputMap.Vertex_TRUE_R_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
        inputMap.Vertex_R_Regions.Barrel.MnvH1D_data,
        inputMap.Vertex_TRUE_R_Regions.Barrel.MnvH1D_mc_Convoluted_Helium[ind],
        inputMap.Vertex_TRUE_R_Regions.Barrel.MnvH1D_mc_Convoluted_Aluminium[ind],
        inputMap.Vertex_TRUE_R_Regions.Barrel.MnvH1D_mc_Convoluted_Carbon[ind],
        inputMap.Vertex_TRUE_R_Regions.Barrel.MnvH1D_mc_Convoluted_Iron[ind],
        inputMap.Vertex_TRUE_R_Regions.Barrel.MnvH1D_mc_Convoluted_Lead[ind],
        inputMap.Vertex_TRUE_R_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
        inputMap.Vertex_R_Regions.Downstream.MnvH1D_data,
        inputMap.Vertex_TRUE_R_Regions.Downstream.MnvH1D_mc_Convoluted_Helium[ind],
        inputMap.Vertex_TRUE_R_Regions.Downstream.MnvH1D_mc_Convoluted_Aluminium[ind],
        inputMap.Vertex_TRUE_R_Regions.Downstream.MnvH1D_mc_Convoluted_Carbon[ind],
        inputMap.Vertex_TRUE_R_Regions.Downstream.MnvH1D_mc_Convoluted_Iron[ind],
        inputMap.Vertex_TRUE_R_Regions.Downstream.MnvH1D_mc_Convoluted_Lead[ind],
        inputMap.Vertex_TRUE_R_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
        inputMap.Vertex_R_Regions.Concave.MnvH1D_data,
        inputMap.Vertex_TRUE_R_Regions.Concave.MnvH1D_mc_Convoluted_Helium[ind],
        inputMap.Vertex_TRUE_R_Regions.Concave.MnvH1D_mc_Convoluted_Aluminium[ind],
        inputMap.Vertex_TRUE_R_Regions.Concave.MnvH1D_mc_Convoluted_Carbon[ind],
        inputMap.Vertex_TRUE_R_Regions.Concave.MnvH1D_mc_Convoluted_Iron[ind],
        inputMap.Vertex_TRUE_R_Regions.Concave.MnvH1D_mc_Convoluted_Lead[ind],
        inputMap.Vertex_TRUE_R_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
        Title_output, "TRUE Vertex R", Chisqrt, ChisqrtAfter, FitType,
        UseLogChi_Tool, global_doAreaNormalized_Tool, set_ymax_forFitVars,
        isFiduical ? YaxisMax_R_Fid : YaxisMax_R);

}

void Convolution_Tool::Plot_regions_XYZFit_Full( double Zmean ,
  double Zsigma, int ind, int FitType,std::string Hist_title ){

    Plot_regions_XYZFit(Full,
      global_MapParametersXY_Full,  Zmean , Zsigma,  ind,  FitType,
      Hist_title,  global_doAreaNormalized_Tool, set_ymax_forFitVars  );

    }

    void Convolution_Tool::Plot_regions_XYZFit_Full_Fiducial( double Zmean ,
      double Zsigma, int ind, int FitType,std::string Hist_title ){

        Plot_regions_XYZFit(Full_Fid,
          global_MapParametersXY_Full,  Zmean , Zsigma,  ind,  FitType,
          Hist_title,  global_doAreaNormalized_Tool, set_ymax_forFitVars, true  );
        }



void Convolution_Tool::Plot_regions_XYZFit_Empty( double Zmean , double Zsigma,
   int ind, int FitType,std::string Hist_title ){

     Plot_regions_XYZFit(Empty,
       global_MapParametersXY_Empty,  Zmean , Zsigma,  ind,  FitType,
       Hist_title,  global_doAreaNormalized_Tool, set_ymax_forFitVars  );

  }


  void Convolution_Tool::Plot_regions_XYZFit_Empty_Fiducial( double Zmean , double Zsigma,
     int ind, int FitType,std::string Hist_title ){
       Plot_regions_XYZFit(Empty_Fid,
         global_MapParametersXY_Empty,  Zmean , Zsigma,  ind,  FitType,
         Hist_title,  global_doAreaNormalized_Tool, set_ymax_forFitVars, true );

    }

  void Convolution_Tool::Plot_regions_XYZFit_Full_Empty( double ZmeanF , double ZsigmaF, double ZmeanE , double ZsigmaE,
     int ind, int FitType,std::string Hist_title ){
       Plot_regions_XYZFit(Full_Empty,
         global_MapParametersXY_Empty,  ZmeanF , ZsigmaF,  ind,  FitType,
         Hist_title,  global_doAreaNormalized_Tool, set_ymax_forFitVars, true , true, ZmeanE , ZsigmaE  );

    }

    void Convolution_Tool::Plot_regions_XYZFit_Full_Empty_Fiducial(  double ZmeanF , double ZsigmaF, double ZmeanE , double ZsigmaE,
       int ind, int FitType,std::string Hist_title ){

         Plot_regions_XYZFit(Full_Empty_Fid,
           global_MapParametersXY_Empty,  ZmeanF , ZsigmaF,  ind,  FitType,
           Hist_title,  global_doAreaNormalized_Tool, set_ymax_forFitVars , true, true, ZmeanE ,ZsigmaE );

      }


void Convolution_Tool::Plot_regions_TRUEXYZFit_Empty( double Zmean , double Zsigma, int ind, int FitType,
  std::string Hist_title ){

    std::cout<<"Trying to Plot true"<< std::endl;

    Plot_regions_XYZFit_TRUE(Empty,
      global_MapParametersXY_Empty,  Zmean , Zsigma,  ind,  FitType,
      Hist_title,  global_doAreaNormalized_Tool, set_ymax_forFitVars  );
      std::cout<<"Trying to plot true plots "<<std::endl;

    }


    void Convolution_Tool::Plot_regions_TRUEXYZFit_Empty_Fiducial( double Zmean , double Zsigma, int ind, int FitType,
      std::string Hist_title ){

        std::cout<<"Trying to Plot true"<< std::endl;

        Plot_regions_XYZFit_TRUE(Empty_Fid,
          global_MapParametersXY_Empty,  Zmean , Zsigma,  ind,  FitType,
          Hist_title,  global_doAreaNormalized_Tool, set_ymax_forFitVars, true  );
          std::cout<<"Trying to plot true plots "<<std::endl;

        }

    void Convolution_Tool::Plot_regions_NonFitVars_Empty( double Zmean , double Zsigma,
      int ind, int FitType, std::string Hist_title ){
        std::cout<<"Trying to Plot Non Fit Vars "<< std::endl;

        Plot_regions_nonFitVarsFit(Empty,
          global_MapParametersXY_Empty,  Zmean , Zsigma,  ind,  FitType,
      Hist_title,  global_doAreaNormalized_Tool, false  );


    }
    void Convolution_Tool::Plot_regions_NonFitVars_Empty_Fiducial( double Zmean , double Zsigma,
      int ind, int FitType, std::string Hist_title ){
        std::cout<<"Trying to Plot Non Fit Vars "<< std::endl;

        Plot_regions_nonFitVarsFit(Empty_Fid,
          global_MapParametersXY_Empty,  Zmean , Zsigma,  ind,  FitType,
      Hist_title,  global_doAreaNormalized_Tool, false  );


    }

void Convolution_Tool::Plot_regions_TRUEXYZFit_Full( double Zmean , double Zsigma,
  int ind, int FitType, std::string Hist_title ){
    std::cout<<"Trying to Plot true"<< std::endl;

    Plot_regions_XYZFit_TRUE(Full,
      global_MapParametersXY_Full,  Zmean , Zsigma,  ind,  FitType,
      Hist_title,  global_doAreaNormalized_Tool, set_ymax_forFitVars  );
      std::cout<<"Trying to plot true plots "<<std::endl;

    }


    void Convolution_Tool::Plot_regions_TRUEXYZFit_Full_Fiducial( double Zmean , double Zsigma,
      int ind, int FitType, std::string Hist_title ){
        std::cout<<"Trying to Plot true"<< std::endl;

        Plot_regions_XYZFit_TRUE(Full_Fid,
          global_MapParametersXY_Full,  Zmean , Zsigma,  ind,  FitType,
          Hist_title,  global_doAreaNormalized_Tool, set_ymax_forFitVars , true );
          std::cout<<"Trying to plot true plots "<<std::endl;

        }


        void Convolution_Tool::Plot_regions_TRUEXYZFit_Full_Empty( double Zmean , double Zsigma,
          int ind, int FitType, std::string Hist_title ){
            std::cout<<"Trying to Plot true"<< std::endl;

            Plot_regions_XYZFit_TRUE(Full_Empty,
              global_MapParametersXY_Full,  Zmean , Zsigma,  ind,  FitType,
              Hist_title,  global_doAreaNormalized_Tool, set_ymax_forFitVars  );
              std::cout<<"Trying to plot true plots "<<std::endl;

            }

void Convolution_Tool::Plot_regions_TRUEXYZFit_Full_Empty_Fiducial( double Zmean , double Zsigma,
  int ind, int FitType, std::string Hist_title ){
                std::cout<<"Trying to Plot true"<< std::endl;

                Plot_regions_XYZFit_TRUE(Full_Empty_Fid,
                  global_MapParametersXY_Full,  Zmean , Zsigma,  ind,  FitType,
                  Hist_title,  global_doAreaNormalized_Tool, set_ymax_forFitVars  );
                  std::cout<<"Trying to plot true plots "<<std::endl;

}



void Convolution_Tool::Plot_regions_NonFitVars_Full( double Zmean , double Zsigma,
  int ind, int FitType, std::string Hist_title ){
    std::cout<<"Trying to Plot Non Fit Vars "<< std::endl;
    Plot_regions_nonFitVarsFit(Full,
      global_MapParametersXY_Full,  Zmean , Zsigma,  ind,  FitType,
      Hist_title,  global_doAreaNormalized_Tool, false  );
    }

void Convolution_Tool::Plot_regions_NonFitVars_Full_Fiducial( double Zmean , double Zsigma,
  int ind, int FitType, std::string Hist_title ){
    std::cout<<"Trying to Plot Non Fit Vars "<< std::endl;
    Plot_regions_nonFitVarsFit(Full_Fid,
      global_MapParametersXY_Full,  Zmean , Zsigma,  ind,  FitType,
      Hist_title,  global_doAreaNormalized_Tool, false  );
    }




void Convolution_Tool::Plot_regions_NonFitVars_Full_Empty(double ZmeanF,
  double ZsigmaF,double ZmeanE , double ZsigmaE,
  int ind, int FitType, std::string Hist_title ){
    std::cout<<"Trying to Plot Non Fit Vars "<< std::endl;
    Plot_regions_nonFitVarsFit(Full_Empty,
      global_MapParametersXY_Full,  ZmeanF , ZsigmaF,  ind,  FitType,
      Hist_title,  global_doAreaNormalized_Tool, false, true, ZmeanE , ZsigmaE  );
  }

void Convolution_Tool::Plot_regions_NonFitVars_Full_Empty_Fiducial( double ZmeanF,
   double ZsigmaF,double ZmeanE , double ZsigmaE,
  int ind, int FitType, std::string Hist_title ){
    std::cout<<"Trying to Plot Non Fit Vars "<< std::endl;
    Plot_regions_nonFitVarsFit(Full_Empty_Fid,
      global_MapParametersXY_Full,  ZmeanF , ZsigmaF,  ind,  FitType,
      Hist_title,  global_doAreaNormalized_Tool, false, true, ZmeanE , ZsigmaE  );
  }



void Convolution_Tool::Plot_regions_nonFitVarsFit(ConvolutionShiftMap inputMap,
  Normal_Fit_ParametersXY inputMapParametersXY, double Zmean , double Zsigma,
  int ind, int FitType,std::string Hist_title, bool doAreaNormalized,
  bool applyMaxY,  bool isFull_Empty  ,  double ZmeanE , double ZsigmaE   )
  {

    std::string Title_output;

    std::stringstream stream;
    double meanX = inputMapParametersXY[kX].mean;
    stream << std::fixed << std::setprecision(1) << meanX;
    std::string meanX_string = stream.str();
    stream.str(std::string());

    double stddevX = inputMapParametersXY[kX].stddev;
    stream << std::fixed << std::setprecision(1) << stddevX;
    std::string stddevX_string = stream.str();
    stream.str(std::string());

    double meanY = inputMapParametersXY[kY].mean;
    stream << std::fixed << std::setprecision(1) << meanY;
    std::string meanY_string = stream.str();stream.str(std::string());


    double stddevY = inputMapParametersXY[kY].stddev;
    stream << std::fixed << std::setprecision(1) << stddevY;
    std::string stddevY_string = stream.str();stream.str(std::string());

    stream << std::fixed << std::setprecision(1) << Zmean;
    std::string meanZ_string = stream.str();stream.str(std::string());

    stream << std::fixed << std::setprecision(1) << Zsigma;
    std::string stddevZ_string = stream.str();stream.str(std::string());


    std::string meanZ_stringE;
    std::string stddevZ_stringE;


   if(isFull_Empty==true){


     stream << std::fixed << std::setprecision(1) << ZmeanE;
      meanZ_stringE = stream.str();stream.str(std::string());

     stream << std::fixed << std::setprecision(1) << ZsigmaE;
      stddevZ_stringE = stream.str();stream.str(std::string());

   }



   bool UseMaxY = false;

   double Chisqrt = 999;
   double ChisqrtAfter = 999;

   if (isFull_Empty == true) {
     Title_output = Hist_title + " F(#mu,#sigma),Y(),Z_{Full},Z_{Empty} = (" +
                    meanX_string + ", " + stddevX_string + "),(" + meanY_string +
                    ", " + stddevY_string + "),(" + meanZ_string + ", " +
                    stddevZ_string + "),(" + meanZ_stringE + ", " +
                    stddevZ_stringE + ")";
   } else {
     Title_output =
         Hist_title + " X(#mu,#sigma), Y(#mu,#sigma), Z(#mu,#sigma)  = (" +
         meanX_string + ", " + stddevX_string + "), (" + meanY_string + ", " +
         stddevY_string + "), (" + meanZ_string + ", " + stddevZ_string + ")";
   }
   std::cout << "PT" << std::endl;

   Plot_regions_Material(
       globalpdf_labelwithpdf, ind, inputMap.muonPT_Regions.Upstream.MnvH1D_data,
       inputMap.muonPT_Regions.Upstream.MnvH1D_mc_Convoluted_Helium[ind],
       inputMap.muonPT_Regions.Upstream.MnvH1D_mc_Convoluted_Aluminium[ind],
       inputMap.muonPT_Regions.Upstream.MnvH1D_mc_Convoluted_Carbon[ind],
       inputMap.muonPT_Regions.Upstream.MnvH1D_mc_Convoluted_Iron[ind],
       inputMap.muonPT_Regions.Upstream.MnvH1D_mc_Convoluted_Lead[ind],
       inputMap.muonPT_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
       inputMap.muonPT_Regions.Barrel.MnvH1D_data,
       inputMap.muonPT_Regions.Barrel.MnvH1D_mc_Convoluted_Helium[ind],
       inputMap.muonPT_Regions.Barrel.MnvH1D_mc_Convoluted_Aluminium[ind],
       inputMap.muonPT_Regions.Barrel.MnvH1D_mc_Convoluted_Carbon[ind],
       inputMap.muonPT_Regions.Barrel.MnvH1D_mc_Convoluted_Iron[ind],
       inputMap.muonPT_Regions.Barrel.MnvH1D_mc_Convoluted_Lead[ind],
       inputMap.muonPT_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
       inputMap.muonPT_Regions.Downstream.MnvH1D_data,
       inputMap.muonPT_Regions.Downstream.MnvH1D_mc_Convoluted_Helium[ind],
       inputMap.muonPT_Regions.Downstream.MnvH1D_mc_Convoluted_Aluminium[ind],
       inputMap.muonPT_Regions.Downstream.MnvH1D_mc_Convoluted_Carbon[ind],
       inputMap.muonPT_Regions.Downstream.MnvH1D_mc_Convoluted_Iron[ind],
       inputMap.muonPT_Regions.Downstream.MnvH1D_mc_Convoluted_Lead[ind],
       inputMap.muonPT_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
       inputMap.muonPT_Regions.Concave.MnvH1D_data,
       inputMap.muonPT_Regions.Concave.MnvH1D_mc_Convoluted_Helium[ind],
       inputMap.muonPT_Regions.Concave.MnvH1D_mc_Convoluted_Aluminium[ind],
       inputMap.muonPT_Regions.Concave.MnvH1D_mc_Convoluted_Carbon[ind],
       inputMap.muonPT_Regions.Concave.MnvH1D_mc_Convoluted_Iron[ind],
       inputMap.muonPT_Regions.Concave.MnvH1D_mc_Convoluted_Lead[ind],
       inputMap.muonPT_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
       Title_output, "Muon P_{T} [GeV]", Chisqrt, ChisqrtAfter, FitType,
       UseLogChi_Tool, global_doAreaNormalized_Tool, UseMaxY, YaxisMax_X);
   /////
   // Y
   ////
   ChiSq_before_fit_var.push_back(Chisqrt);
   ChiSq_after_fit_var.push_back(ChisqrtAfter);
   std::cout << "PZ" << std::endl;
   Plot_regions_Material(
       globalpdf_labelwithpdf, ind, inputMap.muonPZ_Regions.Upstream.MnvH1D_data,
       inputMap.muonPZ_Regions.Upstream.MnvH1D_mc_Convoluted_Helium[ind],
       inputMap.muonPZ_Regions.Upstream.MnvH1D_mc_Convoluted_Aluminium[ind],
       inputMap.muonPZ_Regions.Upstream.MnvH1D_mc_Convoluted_Carbon[ind],
       inputMap.muonPZ_Regions.Upstream.MnvH1D_mc_Convoluted_Iron[ind],
       inputMap.muonPZ_Regions.Upstream.MnvH1D_mc_Convoluted_Lead[ind],
       inputMap.muonPZ_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
       inputMap.muonPZ_Regions.Barrel.MnvH1D_data,
       inputMap.muonPZ_Regions.Barrel.MnvH1D_mc_Convoluted_Helium[ind],
       inputMap.muonPZ_Regions.Barrel.MnvH1D_mc_Convoluted_Aluminium[ind],
       inputMap.muonPZ_Regions.Barrel.MnvH1D_mc_Convoluted_Carbon[ind],
       inputMap.muonPZ_Regions.Barrel.MnvH1D_mc_Convoluted_Iron[ind],
       inputMap.muonPZ_Regions.Barrel.MnvH1D_mc_Convoluted_Lead[ind],
       inputMap.muonPZ_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
       inputMap.muonPZ_Regions.Downstream.MnvH1D_data,
       inputMap.muonPZ_Regions.Downstream.MnvH1D_mc_Convoluted_Helium[ind],
       inputMap.muonPZ_Regions.Downstream.MnvH1D_mc_Convoluted_Aluminium[ind],
       inputMap.muonPZ_Regions.Downstream.MnvH1D_mc_Convoluted_Carbon[ind],
       inputMap.muonPZ_Regions.Downstream.MnvH1D_mc_Convoluted_Iron[ind],
       inputMap.muonPZ_Regions.Downstream.MnvH1D_mc_Convoluted_Lead[ind],
       inputMap.muonPZ_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
       inputMap.muonPZ_Regions.Concave.MnvH1D_data,
       inputMap.muonPZ_Regions.Concave.MnvH1D_mc_Convoluted_Helium[ind],
       inputMap.muonPZ_Regions.Concave.MnvH1D_mc_Convoluted_Aluminium[ind],
       inputMap.muonPZ_Regions.Concave.MnvH1D_mc_Convoluted_Carbon[ind],
       inputMap.muonPZ_Regions.Concave.MnvH1D_mc_Convoluted_Iron[ind],
       inputMap.muonPZ_Regions.Concave.MnvH1D_mc_Convoluted_Lead[ind],
       inputMap.muonPZ_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
       Title_output, "Muon P_{Z} [GeV]", Chisqrt, ChisqrtAfter, FitType,
       UseLogChi_Tool, global_doAreaNormalized_Tool, UseMaxY, YaxisMax_Y);
   /////
   // Z
   /////
   ChiSq_before_fit_var.push_back(Chisqrt);
   ChiSq_after_fit_var.push_back(ChisqrtAfter);

   std::cout << "Emu" << std::endl;
   Plot_regions_Material(
       globalpdf_labelwithpdf, ind, inputMap.muonE_Regions.Upstream.MnvH1D_data,
       inputMap.muonE_Regions.Upstream.MnvH1D_mc_Convoluted_Helium[ind],
       inputMap.muonE_Regions.Upstream.MnvH1D_mc_Convoluted_Aluminium[ind],
       inputMap.muonE_Regions.Upstream.MnvH1D_mc_Convoluted_Carbon[ind],
       inputMap.muonE_Regions.Upstream.MnvH1D_mc_Convoluted_Iron[ind],
       inputMap.muonE_Regions.Upstream.MnvH1D_mc_Convoluted_Lead[ind],
       inputMap.muonE_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
       inputMap.muonE_Regions.Barrel.MnvH1D_data,
       inputMap.muonE_Regions.Barrel.MnvH1D_mc_Convoluted_Helium[ind],
       inputMap.muonE_Regions.Barrel.MnvH1D_mc_Convoluted_Aluminium[ind],
       inputMap.muonE_Regions.Barrel.MnvH1D_mc_Convoluted_Carbon[ind],
       inputMap.muonE_Regions.Barrel.MnvH1D_mc_Convoluted_Iron[ind],
       inputMap.muonE_Regions.Barrel.MnvH1D_mc_Convoluted_Lead[ind],
       inputMap.muonE_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
       inputMap.muonE_Regions.Downstream.MnvH1D_data,
       inputMap.muonE_Regions.Downstream.MnvH1D_mc_Convoluted_Helium[ind],
       inputMap.muonE_Regions.Downstream.MnvH1D_mc_Convoluted_Aluminium[ind],
       inputMap.muonE_Regions.Downstream.MnvH1D_mc_Convoluted_Carbon[ind],
       inputMap.muonE_Regions.Downstream.MnvH1D_mc_Convoluted_Iron[ind],
       inputMap.muonE_Regions.Downstream.MnvH1D_mc_Convoluted_Lead[ind],
       inputMap.muonE_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
       inputMap.muonE_Regions.Concave.MnvH1D_data,
       inputMap.muonE_Regions.Concave.MnvH1D_mc_Convoluted_Helium[ind],
       inputMap.muonE_Regions.Concave.MnvH1D_mc_Convoluted_Aluminium[ind],
       inputMap.muonE_Regions.Concave.MnvH1D_mc_Convoluted_Carbon[ind],
       inputMap.muonE_Regions.Concave.MnvH1D_mc_Convoluted_Iron[ind],
       inputMap.muonE_Regions.Concave.MnvH1D_mc_Convoluted_Lead[ind],
       inputMap.muonE_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
       Title_output, "E_{#mu} [GeV]", Chisqrt, ChisqrtAfter, FitType,
       UseLogChi_Tool, global_doAreaNormalized_Tool, UseMaxY, YaxisMax_Z);

   ChiSq_before_fit_var.push_back(Chisqrt);
   ChiSq_after_fit_var.push_back(ChisqrtAfter);
   ////
   // Muon theta
   ////

   //  Title_output = Hist_title + " X(#mu,#sigma) = (" + meanX_string  + ", " +
   //  stddevX_string  + ") " + " Y(#mu,#sigma) = (" +meanY_string  + ", "
   //  +stddevY_string  + ") "  ;
   std::cout << "thetamu" << std::endl;
   Plot_regions_Material(
       globalpdf_labelwithpdf, ind,
       inputMap.muontheta_Regions.Upstream.MnvH1D_data,
       inputMap.muontheta_Regions.Upstream.MnvH1D_mc_Convoluted_Helium[ind],
       inputMap.muontheta_Regions.Upstream.MnvH1D_mc_Convoluted_Aluminium[ind],
       inputMap.muontheta_Regions.Upstream.MnvH1D_mc_Convoluted_Carbon[ind],
       inputMap.muontheta_Regions.Upstream.MnvH1D_mc_Convoluted_Iron[ind],
       inputMap.muontheta_Regions.Upstream.MnvH1D_mc_Convoluted_Lead[ind],
       inputMap.muontheta_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
       inputMap.muontheta_Regions.Barrel.MnvH1D_data,
       inputMap.muontheta_Regions.Barrel.MnvH1D_mc_Convoluted_Helium[ind],
       inputMap.muontheta_Regions.Barrel.MnvH1D_mc_Convoluted_Aluminium[ind],
       inputMap.muontheta_Regions.Barrel.MnvH1D_mc_Convoluted_Carbon[ind],
       inputMap.muontheta_Regions.Barrel.MnvH1D_mc_Convoluted_Iron[ind],
       inputMap.muontheta_Regions.Barrel.MnvH1D_mc_Convoluted_Lead[ind],
       inputMap.muontheta_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
       inputMap.muontheta_Regions.Downstream.MnvH1D_data,
       inputMap.muontheta_Regions.Downstream.MnvH1D_mc_Convoluted_Helium[ind],
       inputMap.muontheta_Regions.Downstream.MnvH1D_mc_Convoluted_Aluminium[ind],
       inputMap.muontheta_Regions.Downstream.MnvH1D_mc_Convoluted_Carbon[ind],
       inputMap.muontheta_Regions.Downstream.MnvH1D_mc_Convoluted_Iron[ind],
       inputMap.muontheta_Regions.Downstream.MnvH1D_mc_Convoluted_Lead[ind],
       inputMap.muontheta_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
       inputMap.muontheta_Regions.Concave.MnvH1D_data,
       inputMap.muontheta_Regions.Concave.MnvH1D_mc_Convoluted_Helium[ind],
       inputMap.muontheta_Regions.Concave.MnvH1D_mc_Convoluted_Aluminium[ind],
       inputMap.muontheta_Regions.Concave.MnvH1D_mc_Convoluted_Carbon[ind],
       inputMap.muontheta_Regions.Concave.MnvH1D_mc_Convoluted_Iron[ind],
       inputMap.muontheta_Regions.Concave.MnvH1D_mc_Convoluted_Lead[ind],
       inputMap.muontheta_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
       Title_output, "#theta_{#mu}", Chisqrt, ChisqrtAfter, FitType,
       UseLogChi_Tool, global_doAreaNormalized_Tool, UseMaxY, YaxisMax_R);
   std::cout << "mu doca" << std::endl;

   ChiSq_before_fit_var.push_back(Chisqrt);
   ChiSq_after_fit_var.push_back(ChisqrtAfter);

   Plot_regions_Material(
       globalpdf_labelwithpdf, ind, inputMap.muonDOCA_Regions.Upstream.MnvH1D_data,
       inputMap.muonDOCA_Regions.Upstream.MnvH1D_mc_Convoluted_Helium[ind],
       inputMap.muonDOCA_Regions.Upstream.MnvH1D_mc_Convoluted_Aluminium[ind],
       inputMap.muonDOCA_Regions.Upstream.MnvH1D_mc_Convoluted_Carbon[ind],
       inputMap.muonDOCA_Regions.Upstream.MnvH1D_mc_Convoluted_Iron[ind],
       inputMap.muonDOCA_Regions.Upstream.MnvH1D_mc_Convoluted_Lead[ind],
       inputMap.muonDOCA_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
       inputMap.muonDOCA_Regions.Barrel.MnvH1D_data,
       inputMap.muonDOCA_Regions.Barrel.MnvH1D_mc_Convoluted_Helium[ind],
       inputMap.muonDOCA_Regions.Barrel.MnvH1D_mc_Convoluted_Aluminium[ind],
       inputMap.muonDOCA_Regions.Barrel.MnvH1D_mc_Convoluted_Carbon[ind],
       inputMap.muonDOCA_Regions.Barrel.MnvH1D_mc_Convoluted_Iron[ind],
       inputMap.muonDOCA_Regions.Barrel.MnvH1D_mc_Convoluted_Lead[ind],
       inputMap.muonDOCA_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
       inputMap.muonDOCA_Regions.Downstream.MnvH1D_data,
       inputMap.muonDOCA_Regions.Downstream.MnvH1D_mc_Convoluted_Helium[ind],
       inputMap.muonDOCA_Regions.Downstream.MnvH1D_mc_Convoluted_Aluminium[ind],
       inputMap.muonDOCA_Regions.Downstream.MnvH1D_mc_Convoluted_Carbon[ind],
       inputMap.muonDOCA_Regions.Downstream.MnvH1D_mc_Convoluted_Iron[ind],
       inputMap.muonDOCA_Regions.Downstream.MnvH1D_mc_Convoluted_Lead[ind],
       inputMap.muonDOCA_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
       inputMap.muonDOCA_Regions.Concave.MnvH1D_data,
       inputMap.muonDOCA_Regions.Concave.MnvH1D_mc_Convoluted_Helium[ind],
       inputMap.muonDOCA_Regions.Concave.MnvH1D_mc_Convoluted_Aluminium[ind],
       inputMap.muonDOCA_Regions.Concave.MnvH1D_mc_Convoluted_Carbon[ind],
       inputMap.muonDOCA_Regions.Concave.MnvH1D_mc_Convoluted_Iron[ind],
       inputMap.muonDOCA_Regions.Concave.MnvH1D_mc_Convoluted_Lead[ind],
       inputMap.muonDOCA_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
       Title_output, "#mu_{DOCA}", Chisqrt, ChisqrtAfter, FitType, UseLogChi_Tool,
       global_doAreaNormalized_Tool, UseMaxY, YaxisMax_R);
   std::cout << "nearest wall" << std::endl;

   ChiSq_before_fit_var.push_back(Chisqrt);
   ChiSq_after_fit_var.push_back(ChisqrtAfter);

   Plot_regions_Material(
       globalpdf_labelwithpdf, ind,
       inputMap.NearestWall_Regions.Upstream.MnvH1D_data,
       inputMap.NearestWall_Regions.Upstream.MnvH1D_mc_Convoluted_Helium[ind],
       inputMap.NearestWall_Regions.Upstream.MnvH1D_mc_Convoluted_Aluminium[ind],
       inputMap.NearestWall_Regions.Upstream.MnvH1D_mc_Convoluted_Carbon[ind],
       inputMap.NearestWall_Regions.Upstream.MnvH1D_mc_Convoluted_Iron[ind],
       inputMap.NearestWall_Regions.Upstream.MnvH1D_mc_Convoluted_Lead[ind],
       inputMap.NearestWall_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
       inputMap.NearestWall_Regions.Barrel.MnvH1D_data,
       inputMap.NearestWall_Regions.Barrel.MnvH1D_mc_Convoluted_Helium[ind],
       inputMap.NearestWall_Regions.Barrel.MnvH1D_mc_Convoluted_Aluminium[ind],
       inputMap.NearestWall_Regions.Barrel.MnvH1D_mc_Convoluted_Carbon[ind],
       inputMap.NearestWall_Regions.Barrel.MnvH1D_mc_Convoluted_Iron[ind],
       inputMap.NearestWall_Regions.Barrel.MnvH1D_mc_Convoluted_Lead[ind],
       inputMap.NearestWall_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
       inputMap.NearestWall_Regions.Downstream.MnvH1D_data,
       inputMap.NearestWall_Regions.Downstream.MnvH1D_mc_Convoluted_Helium[ind],
       inputMap.NearestWall_Regions.Downstream.MnvH1D_mc_Convoluted_Aluminium[ind],
       inputMap.NearestWall_Regions.Downstream.MnvH1D_mc_Convoluted_Carbon[ind],
       inputMap.NearestWall_Regions.Downstream.MnvH1D_mc_Convoluted_Iron[ind],
       inputMap.NearestWall_Regions.Downstream.MnvH1D_mc_Convoluted_Lead[ind],
       inputMap.NearestWall_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
       inputMap.NearestWall_Regions.Concave.MnvH1D_data,
       inputMap.NearestWall_Regions.Concave.MnvH1D_mc_Convoluted_Helium[ind],
       inputMap.NearestWall_Regions.Concave.MnvH1D_mc_Convoluted_Aluminium[ind],
       inputMap.NearestWall_Regions.Concave.MnvH1D_mc_Convoluted_Carbon[ind],
       inputMap.NearestWall_Regions.Concave.MnvH1D_mc_Convoluted_Iron[ind],
       inputMap.NearestWall_Regions.Concave.MnvH1D_mc_Convoluted_Lead[ind],
       inputMap.NearestWall_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
       Title_output, "Distance to Nearest Wall [mm]", Chisqrt, ChisqrtAfter,
       FitType, UseLogChi_Tool, global_doAreaNormalized_Tool, UseMaxY, YaxisMax_R);
   std::cout << "recoil Doca" << std::endl;

   ChiSq_before_fit_var.push_back(Chisqrt);
   ChiSq_after_fit_var.push_back(ChisqrtAfter);

   Plot_regions_Material(
       globalpdf_labelwithpdf, ind,
       inputMap.recoilDOCA_Regions.Upstream.MnvH1D_data,
       inputMap.recoilDOCA_Regions.Upstream.MnvH1D_mc_Convoluted_Helium[ind],
       inputMap.recoilDOCA_Regions.Upstream.MnvH1D_mc_Convoluted_Aluminium[ind],
       inputMap.recoilDOCA_Regions.Upstream.MnvH1D_mc_Convoluted_Carbon[ind],
       inputMap.recoilDOCA_Regions.Upstream.MnvH1D_mc_Convoluted_Iron[ind],
       inputMap.recoilDOCA_Regions.Upstream.MnvH1D_mc_Convoluted_Lead[ind],
       inputMap.recoilDOCA_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
       inputMap.recoilDOCA_Regions.Barrel.MnvH1D_data,
       inputMap.recoilDOCA_Regions.Barrel.MnvH1D_mc_Convoluted_Helium[ind],
       inputMap.recoilDOCA_Regions.Barrel.MnvH1D_mc_Convoluted_Aluminium[ind],
       inputMap.recoilDOCA_Regions.Barrel.MnvH1D_mc_Convoluted_Carbon[ind],
       inputMap.recoilDOCA_Regions.Barrel.MnvH1D_mc_Convoluted_Iron[ind],
       inputMap.recoilDOCA_Regions.Barrel.MnvH1D_mc_Convoluted_Lead[ind],
       inputMap.recoilDOCA_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
       inputMap.recoilDOCA_Regions.Downstream.MnvH1D_data,
       inputMap.recoilDOCA_Regions.Downstream.MnvH1D_mc_Convoluted_Helium[ind],
       inputMap.recoilDOCA_Regions.Downstream.MnvH1D_mc_Convoluted_Aluminium[ind],
       inputMap.recoilDOCA_Regions.Downstream.MnvH1D_mc_Convoluted_Carbon[ind],
       inputMap.recoilDOCA_Regions.Downstream.MnvH1D_mc_Convoluted_Iron[ind],
       inputMap.recoilDOCA_Regions.Downstream.MnvH1D_mc_Convoluted_Lead[ind],
       inputMap.recoilDOCA_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
       inputMap.recoilDOCA_Regions.Concave.MnvH1D_data,
       inputMap.recoilDOCA_Regions.Concave.MnvH1D_mc_Convoluted_Helium[ind],
       inputMap.recoilDOCA_Regions.Concave.MnvH1D_mc_Convoluted_Aluminium[ind],
       inputMap.recoilDOCA_Regions.Concave.MnvH1D_mc_Convoluted_Carbon[ind],
       inputMap.recoilDOCA_Regions.Concave.MnvH1D_mc_Convoluted_Iron[ind],
       inputMap.recoilDOCA_Regions.Concave.MnvH1D_mc_Convoluted_Lead[ind],
       inputMap.recoilDOCA_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
       Title_output, "Recoil_{DOCA} [mm]", Chisqrt, ChisqrtAfter, FitType,
       UseLogChi_Tool, global_doAreaNormalized_Tool, UseMaxY, YaxisMax_R);
   std::cout << "recoil Angle" << std::endl;

   ChiSq_before_fit_var.push_back(Chisqrt);
   ChiSq_after_fit_var.push_back(ChisqrtAfter);

   Plot_regions_Material(
       globalpdf_labelwithpdf, ind,
       inputMap.recoilAngle_Regions.Upstream.MnvH1D_data,
       inputMap.recoilAngle_Regions.Upstream.MnvH1D_mc_Convoluted_Helium[ind],
       inputMap.recoilAngle_Regions.Upstream.MnvH1D_mc_Convoluted_Aluminium[ind],
       inputMap.recoilAngle_Regions.Upstream.MnvH1D_mc_Convoluted_Carbon[ind],
       inputMap.recoilAngle_Regions.Upstream.MnvH1D_mc_Convoluted_Iron[ind],
       inputMap.recoilAngle_Regions.Upstream.MnvH1D_mc_Convoluted_Lead[ind],
       inputMap.recoilAngle_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
       inputMap.recoilAngle_Regions.Barrel.MnvH1D_data,
       inputMap.recoilAngle_Regions.Barrel.MnvH1D_mc_Convoluted_Helium[ind],
       inputMap.recoilAngle_Regions.Barrel.MnvH1D_mc_Convoluted_Aluminium[ind],
       inputMap.recoilAngle_Regions.Barrel.MnvH1D_mc_Convoluted_Carbon[ind],
       inputMap.recoilAngle_Regions.Barrel.MnvH1D_mc_Convoluted_Iron[ind],
       inputMap.recoilAngle_Regions.Barrel.MnvH1D_mc_Convoluted_Lead[ind],
       inputMap.recoilAngle_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
       inputMap.recoilAngle_Regions.Downstream.MnvH1D_data,
       inputMap.recoilAngle_Regions.Downstream.MnvH1D_mc_Convoluted_Helium[ind],
       inputMap.recoilAngle_Regions.Downstream.MnvH1D_mc_Convoluted_Aluminium[ind],
       inputMap.recoilAngle_Regions.Downstream.MnvH1D_mc_Convoluted_Carbon[ind],
       inputMap.recoilAngle_Regions.Downstream.MnvH1D_mc_Convoluted_Iron[ind],
       inputMap.recoilAngle_Regions.Downstream.MnvH1D_mc_Convoluted_Lead[ind],
       inputMap.recoilAngle_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
       inputMap.recoilAngle_Regions.Concave.MnvH1D_data,
       inputMap.recoilAngle_Regions.Concave.MnvH1D_mc_Convoluted_Helium[ind],
       inputMap.recoilAngle_Regions.Concave.MnvH1D_mc_Convoluted_Aluminium[ind],
       inputMap.recoilAngle_Regions.Concave.MnvH1D_mc_Convoluted_Carbon[ind],
       inputMap.recoilAngle_Regions.Concave.MnvH1D_mc_Convoluted_Iron[ind],
       inputMap.recoilAngle_Regions.Concave.MnvH1D_mc_Convoluted_Lead[ind],
       inputMap.recoilAngle_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
       Title_output, "#theta_{Recoil} (wrtb) [Degs]", Chisqrt, ChisqrtAfter,
       FitType, UseLogChi_Tool, global_doAreaNormalized_Tool, UseMaxY, YaxisMax_R);
   std::cout << "trackLength" << std::endl;

   ChiSq_before_fit_var.push_back(Chisqrt);
   ChiSq_after_fit_var.push_back(ChisqrtAfter);

   Plot_regions_Material(
       globalpdf_labelwithpdf, ind,
       inputMap.tracklength_Regions.Upstream.MnvH1D_data,
       inputMap.tracklength_Regions.Upstream.MnvH1D_mc_Convoluted_Helium[ind],
       inputMap.tracklength_Regions.Upstream.MnvH1D_mc_Convoluted_Aluminium[ind],
       inputMap.tracklength_Regions.Upstream.MnvH1D_mc_Convoluted_Carbon[ind],
       inputMap.tracklength_Regions.Upstream.MnvH1D_mc_Convoluted_Iron[ind],
       inputMap.tracklength_Regions.Upstream.MnvH1D_mc_Convoluted_Lead[ind],
       inputMap.tracklength_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
       inputMap.tracklength_Regions.Barrel.MnvH1D_data,
       inputMap.tracklength_Regions.Barrel.MnvH1D_mc_Convoluted_Helium[ind],
       inputMap.tracklength_Regions.Barrel.MnvH1D_mc_Convoluted_Aluminium[ind],
       inputMap.tracklength_Regions.Barrel.MnvH1D_mc_Convoluted_Carbon[ind],
       inputMap.tracklength_Regions.Barrel.MnvH1D_mc_Convoluted_Iron[ind],
       inputMap.tracklength_Regions.Barrel.MnvH1D_mc_Convoluted_Lead[ind],
       inputMap.tracklength_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
       inputMap.tracklength_Regions.Downstream.MnvH1D_data,
       inputMap.tracklength_Regions.Downstream.MnvH1D_mc_Convoluted_Helium[ind],
       inputMap.tracklength_Regions.Downstream.MnvH1D_mc_Convoluted_Aluminium[ind],
       inputMap.tracklength_Regions.Downstream.MnvH1D_mc_Convoluted_Carbon[ind],
       inputMap.tracklength_Regions.Downstream.MnvH1D_mc_Convoluted_Iron[ind],
       inputMap.tracklength_Regions.Downstream.MnvH1D_mc_Convoluted_Lead[ind],
       inputMap.tracklength_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
       inputMap.tracklength_Regions.Concave.MnvH1D_data,
       inputMap.tracklength_Regions.Concave.MnvH1D_mc_Convoluted_Helium[ind],
       inputMap.tracklength_Regions.Concave.MnvH1D_mc_Convoluted_Aluminium[ind],
       inputMap.tracklength_Regions.Concave.MnvH1D_mc_Convoluted_Carbon[ind],
       inputMap.tracklength_Regions.Concave.MnvH1D_mc_Convoluted_Iron[ind],
       inputMap.tracklength_Regions.Concave.MnvH1D_mc_Convoluted_Lead[ind],
       inputMap.tracklength_Regions.Upstream.MnvH1D_mc_Convoluted_Other[ind],
       Title_output, "MINERVA Tracklength_{Recoil} (wrtb) [Degs]", Chisqrt,
       ChisqrtAfter, FitType, UseLogChi_Tool, global_doAreaNormalized_Tool,
       UseMaxY, YaxisMax_R);

   ChiSq_before_fit_var.push_back(Chisqrt);
   ChiSq_after_fit_var.push_back(ChisqrtAfter);

   if (ind == 0) {
     ChiSq_after_fit_var.clear();
   }
   }



  void Convolution_Tool::Plot_regions_XYFit_Empty(
    Normal_Fit_ParametersXY inputMapParametersXY , int ind, int FitType,
    std::string  Hist_title  ){

      Plot_regions_XYFit(Empty, inputMapParametersXY ,  ind,  FitType,
        Hist_title, global_doAreaNormalized_Tool, set_ymax_forFitVars );



      }

      void Convolution_Tool::Plot_regions_XYFit_Full(
        Normal_Fit_ParametersXY inputMapParametersXY , int ind, int FitType,
        std::string  Hist_title  ){

          Plot_regions_XYFit(Full, inputMapParametersXY ,  ind,  FitType,
            Hist_title, global_doAreaNormalized_Tool, set_ymax_forFitVars );



          }




       void Convolution_Tool::Plot_init_material_Empty(std::string title){

         Plot_regions(Empty , 0, 0, title,  global_doAreaNormalized_Tool, set_ymax_forFitVars  );

       }

       void Convolution_Tool::Plot_init_material_Full(std::string title){

         Plot_regions(Full , 0, 0, title,  global_doAreaNormalized_Tool, set_ymax_forFitVars  );

       }
       void Convolution_Tool::Plot_AfterFit_material_Empty(std::string title){

         Plot_regions(Empty , 1, 1, title,  global_doAreaNormalized_Tool, set_ymax_forFitVars  );


       }
       void Convolution_Tool::Plot_AfterFit_material_Full(std::string title){

         Plot_regions(Full , 1, 1, title,  global_doAreaNormalized_Tool, set_ymax_forFitVars  );


       }

void Convolution_Tool::Plot_regions_noStack(std::string pdf_label, int ind,
  MnvH1D* data_region1, MnvH1D* Helium_region1, MnvH1D* Aluminium_region1, MnvH1D* Carbon_region1,
  MnvH1D* Iron_region1, MnvH1D* Lead_region1, MnvH1D* Other_region1,
  MnvH1D* data_region2, MnvH1D* Helium_region2, MnvH1D* Aluminium_region2, MnvH1D* Carbon_region2,
  MnvH1D* Iron_region2, MnvH1D* Lead_region2, MnvH1D* Other_region2,
  MnvH1D* data_region3, MnvH1D* Helium_region3, MnvH1D* Aluminium_region3, MnvH1D* Carbon_region3,
  MnvH1D* Iron_region3, MnvH1D* Lead_region3, MnvH1D* Other_region3,
  MnvH1D* data_region4, MnvH1D* Helium_region4, MnvH1D* Aluminium_region4, MnvH1D* Carbon_region4,
  MnvH1D* Iron_region4, MnvH1D* Lead_region4, MnvH1D* Other_region4,

  std::string Hist_title, std::string xaxislabel, double &ChiSqrt,
  double &ChiSqrtAfter, int FitType, bool UseLogChi, bool doAreaNormalized)
  {

    std::string type;
    if (ind == 0) type = "Nominal";
    else type = "Fitted";
    //std::cout<1029<"Ploting type: Combined CryoRegions  "<< type<<std::endl;

    //PlotUtils::MnvPlotter* plotter= new mnvPlotter();
    MnvPlotter* plotter = new MnvPlotter(PlotUtils::kCCInclusiveHeliumStyle);
    //plotter(PlotUtils::kCCInclusiveHeliumStyle);
    MnvH1D *data = (PlotUtils::MnvH1D*)data_region1->Clone("data");
    data->Add(data_region2);
    data->Add(data_region3);
    data->Add(data_region4);

    MnvH1D *mc_total = (PlotUtils::MnvH1D*)Helium_region1->Clone("mc_total");

    mc_total->Add(Aluminium_region1 );
    mc_total->Add(Carbon_region1);
    mc_total->Add(Iron_region1 );
    mc_total->Add(Lead_region1 );
    mc_total->Add(Other_region1);

    mc_total->Add(Helium_region2 );
    mc_total->Add(Aluminium_region2 );
    mc_total->Add(Carbon_region2);
    mc_total->Add(Iron_region2 );
    mc_total->Add(Lead_region2 );
    mc_total->Add(Other_region2);

    mc_total->Add(Helium_region3 );
    mc_total->Add(Aluminium_region3 );
    mc_total->Add(Carbon_region3);
    mc_total->Add(Iron_region3 );
    mc_total->Add(Lead_region3 );
    mc_total->Add(Other_region3);

    mc_total->Add(Helium_region4 );
    mc_total->Add(Aluminium_region4 );
    mc_total->Add(Carbon_region4);
    mc_total->Add(Iron_region4 );
    mc_total->Add(Lead_region4 );
    mc_total->Add(Other_region4);

    data->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
    mc_total->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));


    TH1D* h_data_Combined = new TH1D(data_region1->GetCVHistoWithError());
    TH1D* h_Helium_region1 = new TH1D(Helium_region1->GetCVHistoWithError());
    TH1D* h_Aluminium_region1 = new TH1D(Aluminium_region1->GetCVHistoWithError());

    TH1D* h_Carbon_Combined = new TH1D(Carbon_region1->GetCVHistoWithError());
    TH1D* h_Iron_Combined = new TH1D(Iron_region1->GetCVHistoWithError());
    TH1D* h_Lead_Combined = new TH1D(Lead_region1->GetCVHistoWithError());
    TH1D* h_Other_Combined = new TH1D(Other_region1->GetCVHistoWithError());

    TH1D* h_data_region2 = new TH1D(data_region2->GetCVHistoWithError());
    TH1D* h_Helium_region2 = new TH1D(Helium_region2->GetCVHistoWithError());

    TH1D* h_Aluminium_region2 = new TH1D(Aluminium_region2->GetCVHistoWithError());
    TH1D* h_Carbon_region2 = new TH1D(Carbon_region2->GetCVHistoWithError());
    TH1D* h_Iron_region2 = new TH1D(Iron_region2->GetCVHistoWithError());
    TH1D* h_Lead_region2 = new TH1D(Lead_region2->GetCVHistoWithError());
    TH1D* h_Other_region2 = new TH1D(Other_region2->GetCVHistoWithError());

    h_Carbon_Combined->Add(h_Carbon_region2);
    h_Iron_Combined->Add(  h_Iron_region2);
    h_Lead_Combined->Add(  h_Lead_region2);
    h_Other_Combined->Add( h_Other_region2);
    h_data_Combined->Add(  h_data_region2);

    TH1D* h_data_region3 = new TH1D(data_region3->GetCVHistoWithError());
    TH1D* h_Helium_region3 = new TH1D(Helium_region3->GetCVHistoWithError());
    TH1D* h_Aluminium_region3 = new TH1D(Aluminium_region3->GetCVHistoWithError());

    TH1D* h_Carbon_region3 = new TH1D(Carbon_region3->GetCVHistoWithError());
    TH1D* h_Iron_region3 = new TH1D(Iron_region3->GetCVHistoWithError());
    TH1D* h_Lead_region3 = new TH1D(Lead_region3->GetCVHistoWithError());
    TH1D* h_Other_region3 = new TH1D(Other_region3->GetCVHistoWithError());

    h_Carbon_Combined->Add(h_Carbon_region3);
    h_Iron_Combined->Add(  h_Iron_region3);
    h_Lead_Combined->Add(  h_Lead_region3);
    h_Other_Combined->Add( h_Other_region3);
    h_data_Combined->Add(  h_data_region3);

    TH1D* h_data_region4 = new TH1D(data_region4->GetCVHistoWithError());
    TH1D* h_Helium_region4 = new TH1D(Helium_region4->GetCVHistoWithError());
    TH1D* h_Aluminium_region4 = new TH1D(Aluminium_region4->GetCVHistoWithError());

    TH1D* h_Carbon_region4 = new TH1D(Carbon_region4->GetCVHistoWithError());
    TH1D* h_Iron_region4 = new TH1D(Iron_region4->GetCVHistoWithError());
    TH1D* h_Lead_region4 = new TH1D(Lead_region4->GetCVHistoWithError());
    TH1D* h_Other_region4 = new TH1D(Other_region4->GetCVHistoWithError());


    h_Carbon_Combined->Add(h_Carbon_region4);
    h_Iron_Combined->Add(  h_Iron_region4);
    h_Lead_Combined->Add(  h_Lead_region4);
    h_Other_Combined->Add( h_Other_region4);

    ///////////////// Combining all others to Other
    h_data_Combined->Add(  h_data_region4);


    ColorHistsForLines(h_Carbon_Combined, h_Iron_Combined, h_Lead_Combined,  h_Other_Combined);
    ColorData(h_data_Combined);
    Color_HeliumHistsForLines(h_Helium_region1, h_Helium_region2, h_Helium_region3, h_Helium_region4);
    Color_AluminiumHistsForLines(h_Aluminium_region1, h_Aluminium_region2, h_Aluminium_region3, h_Aluminium_region4);

    // MC Total depend on the Modification
    // If Raws - take the mc_total directly
    // If Modified - Add all mc models;

    TH1D* h_mc_total = new TH1D(mc_total->GetCVHistoWithError());

    double plot_chisq;
    //double plot_chisq = calc_ChiSq(data, signal, WithPi0, QELike, SinglePiPlus, Other);
    if(UseLogChi==false){
      plot_chisq = calc_ChiSq(h_data_Combined,
        h_Helium_region1,
        h_Helium_region2,
        h_Helium_region3,
        h_Helium_region4,
        h_Aluminium_region1,
        h_Aluminium_region2,
        h_Aluminium_region3,
        h_Aluminium_region4,
        h_Carbon_Combined, h_Lead_Combined, h_Iron_Combined, h_Other_Combined);
      }
    else if(UseLogChi==true){
      plot_chisq = calc_LogChiSq(h_data_Combined,
        h_Helium_region1,
        h_Helium_region2,
        h_Helium_region3,
        h_Helium_region4,
        h_Aluminium_region1,
        h_Aluminium_region2,
        h_Aluminium_region3,
        h_Aluminium_region4,
        h_Carbon_Combined, h_Lead_Combined, h_Iron_Combined, h_Other_Combined);
      }

      h_Other_Combined->Add(h_Carbon_Combined);
      h_Other_Combined->Add(h_Iron_Combined);
      h_Other_Combined->Add(h_Lead_Combined);

    if(doAreaNormalized == true){
      if(h_mc_total->GetNbinsX() !=h_data_Combined->GetNbinsX()){
        std::cout<<"~~~ Whoah Data and MC have different number of Bins HistTitle : "
        << Hist_title<<std::endl; assert(false); }

      double MCArea = h_mc_total->Integral(1,h_mc_total->GetNbinsX());
      double DataArea = h_data_Combined->Integral(1,h_data_Combined->GetNbinsX());
      double areascaler = DataArea / MCArea;

      h_mc_total->Scale(areascaler);

      h_Helium_region1->Scale(areascaler);
      h_Aluminium_region1->Scale(areascaler);

      h_Helium_region2->Scale(areascaler);
      h_Aluminium_region2->Scale(areascaler);

      h_Helium_region3->Scale(areascaler);
      h_Aluminium_region3->Scale(areascaler);

      h_Helium_region4->Scale(areascaler);
      h_Aluminium_region4->Scale(areascaler);

      //  h_Carbon_Combined->Scale(areascaler);
      //  h_Iron_Combined->Scale(areascaler);
      //  h_Lead_Combined->Scale(areascaler);
      h_Other_Combined->Scale(areascaler);


    }

    ////////////////////////////
    // going to combined the Carbon , Tron , Lead , Other
    ////////////////////////////



    ////////////////////////////

    std::string yaxis;
    if(MakeBinWidth==true){

      h_mc_total->Scale(1.0, "width");

      h_Helium_region1->Scale(1.0, "width");
      h_Aluminium_region1->Scale(1.0, "width");

      h_Helium_region2->Scale(1.0, "width");
      h_Aluminium_region2->Scale(1.0, "width");

      h_Helium_region3->Scale(1.0, "width");
      h_Aluminium_region3->Scale(1.0, "width");

      h_Helium_region4->Scale(1.0, "width");
      h_Aluminium_region4->Scale(1.0, "width");

      //h_Carbon_Combined->Scale(1.0, "width");
      //h_Iron_Combined->Scale(1.0, "width");
      //h_Lead_Combined->Scale(1.0, "width");
      h_Other_Combined->Scale(1.0, "width");
      h_data_Combined->Scale(1.0, "width");

      double binwidth_title = h_mc_total -> GetBinWidth(3);
      yaxis = Form("NEvents / %.2f",binwidth_title);
      if(doAreaNormalized == true){yaxis = Form("[DataAreaNorm] NEvents / %.2f",binwidth_title);}
      //std::cout<< "yaxis = "<< yaxis<<std::endl;
      //std::cout<<"Finished Bin width Norm"<<std::endl;
    }
    else{
      yaxis = "NEvents";
      //  std::cout<<"FInished Bin NOT width Norm"<<std::endl;
    }

    // ------------------------------------------------------------------------
    // Unique Plot for Single Error Band, Single Universe
    //      Comment this section out
    // ------------------------------------------------------------------------


    // Create Canvas and Divide it into two
    TCanvas* c = new TCanvas("c","c",800, 800);
    //TCanvas cE("cE","cE", 800, 800);
    // Upper Pad is the Data vs MC
    //OLDTPad *pad1 = new TPad("pad1", "pad1", 0.05, 0.3, 1, 1.0);
    TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
    pad1->SetBottomMargin(0); // Top and Bottom Plots attached
    pad1->Draw();
    pad1->cd(); // pad1 is the current pad
    // Styling
    data->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
    h_mc_total->GetXaxis()->SetTitle(Form("%s",xaxislabel.c_str()));
    h_mc_total->GetYaxis()->SetTitle(Form("%s",yaxis.c_str()));
    h_mc_total->GetYaxis()->SetTitleFont(62);
    h_mc_total->GetYaxis()->SetTitleSize(0.06);
    //hs->GetYaxis()->CenterTitle();
    //hs->GetYaxis()->SetTitleOffset(1.2);
    h_mc_total->GetXaxis()->SetTitleFont(62);
    h_mc_total->GetXaxis()->SetTitleSize(0.06);

    h_mc_total->GetYaxis()->SetLabelFont(42);
    h_mc_total->GetYaxis()->SetLabelSize(0.05);

    //double hist_max_data = h_data_Combined->GetMaximum();
    //double hist_max_mc = h_mc_total->GetMaximum();

    if(h_mc_total->GetMaximum()>h_data_Combined->GetMaximum()){
      h_mc_total->SetMaximum(h_mc_total->GetMaximum() * 1.45);
    }
    else { h_mc_total->SetMaximum(h_data_Combined->GetMaximum() * 1.45);}

    h_mc_total->SetMarkerStyle(0);
    h_mc_total->SetLineWidth(2);
    h_mc_total->SetLineColor(kBlack);
    h_mc_total->SetFillColor(41);

    // Styling
    h_mc_total->Draw("HIST");
    h_Helium_region1->Draw("SAME L");
    h_Helium_region2->Draw("SAME L");
    h_Helium_region3->Draw("SAME L");
    h_Helium_region4->Draw("SAME L");
    h_Aluminium_region1->Draw("SAME L");
    h_Aluminium_region2->Draw("SAME L");
    h_Aluminium_region3->Draw("SAME L");
    h_Aluminium_region4->Draw("SAME L");
    //h_Carbon_Combined->Draw("SAME L");
    //h_Iron_Combined->Draw("SAME L");
    //h_Lead_Combined->Draw("SAME L");
    h_Other_Combined->Draw("SAME L");


    c->Modified();

    //std::cout<<"Finshed Drawing Hist "<<std::endl;

    // Add Data Plot
    h_data_Combined->Draw("SAME E1 X0");
    //std::cout<<"FInished Drawing h_data"<<std::endl;

    // Add Legend
    TLegend *legend = new TLegend(0.85,0.55,0.95,0.92);              //0.56,0.50,0.9,0.94);
    legend->AddEntry(h_data_Combined, "Data");
    // Add Weights as Text to Modified Plot
    int nPoints = h_data_Combined->GetNbinsX()-1;

    //std::cout<<"nPoints = "<<nPoints<< std::endl;

    // Add Plot-ChiSq
    TLatex* text = new TLatex;
    text->SetNDC();
    text->SetTextColor(kBlue);
    text->SetTextSize(0.025);
    text->DrawLatex(0.2, 0.85, Form("Plot #chi^{2} = %3.2f", plot_chisq));
    text->DrawLatex(0.2, 0.82, Form("Plot #chi^{2}/dof = %3.2f", plot_chisq / (double) nPoints));

    if (ind == 0){
      //ChiSq_before_fit_var.push_back(plot_chisq);
      ChiSqrt = plot_chisq;
    }


    if(FitType == 3){
      legend->AddEntry(h_Helium_region1,          "XCenter He: ",           "f");
      legend->AddEntry(h_Helium_region2,          "XLeftShelf He: ",        "f");
      legend->AddEntry(h_Helium_region3,          "XRightShelf He: ",       "f");
      legend->AddEntry(h_Helium_region4,          "XoutsideEdges He: ",     "f");
      legend->AddEntry(h_Aluminium_region1,       "XCenter Al: ",           "f");
      legend->AddEntry(h_Aluminium_region2,       "XLeftShelf Al: ",       "f");
      legend->AddEntry(h_Aluminium_region3,       "XRightShelf Al: ",      "f");
      legend->AddEntry(h_Aluminium_region4,       "XoutsideEdges Al: ", "f");
    }
    else if(FitType == 4){
      legend->AddEntry(h_Helium_region1,          "XCenter He: ",           "f");
      legend->AddEntry(h_Helium_region2,          "XLeftShelf He: ",        "f");
      legend->AddEntry(h_Helium_region3,          "XRightShelf He: ",       "f");
      legend->AddEntry(h_Helium_region4,          "^{4}He DSConcave ",     "f");
      legend->AddEntry(h_Aluminium_region1,       "XCenter Al: ",           "f");
      legend->AddEntry(h_Aluminium_region2,       "XLeftShelf Al: ",       "f");
      legend->AddEntry(h_Aluminium_region3,       "XRightShelf Al: ",      "f");
      legend->AddEntry(h_Aluminium_region4,       "^{27}Al DSConcave ", "f");
    }

    else{
      legend->AddEntry(h_mc_total,    "Total MC ",        "l");
      legend->AddEntry(h_Helium_region1,    "^{4}He USCap ",        "l");
      legend->AddEntry(h_Helium_region2,    "^{4}He Barrel ",       "l");
      legend->AddEntry(h_Helium_region3,    "^{4}He DSCap ",         "l");
      legend->AddEntry(h_Helium_region4,    "^{4}He DSConcave ", "l");
      legend->AddEntry(h_Aluminium_region1, "^{27}Al USCap ",        "l");
      legend->AddEntry(h_Aluminium_region2, "^{27}Al Barrel ",       "l");
      legend->AddEntry(h_Aluminium_region3, "^{27}Al DSCap ",         "l");
      legend->AddEntry(h_Aluminium_region4, "^{27}Al DSConcave ", "l");
    }


    //legend->AddEntry(h_Carbon_Combined, "C: ",    "l");
    //legend->AddEntry(h_Iron_Combined,   "Fe: ",   "l");
    //legend->AddEntry(h_Lead_Combined,   "Pb: ",   "l");
    legend->AddEntry(h_Other_Combined,  "Other","l");

    legend->SetTextSize(0.025);
    legend->SetTextFont(42);
    legend->Draw();
    text->SetTextSize(0.02);
    text->SetTextColor(kBlack);
    if (ind != 0 &&  FitType== 1){
      int nPars = 4;
      //std::cout<<"making Fit info" <<  std::endl;
      //std::cout<<"ChiSq_before_fit[0] = "<< ChiSq_before_fit[0]<<std::endl;
      //  std::cout<<"ChiSq_after_fit[0] = "<< plot_chisq<<std::endl;
      double xplace = .2;
      double yplace = 0.80;
      text->DrawLatex(xplace, yplace, Form("Fit Results with %d points, %d pars", nPoints, nPars));
      yplace-=.02;
      text->DrawLatex(xplace, yplace , Form("Before Fit #chi^{2} = %3.2f", ChiSqrt));
      yplace-=.02;
      text->DrawLatex(xplace, yplace, Form("Before Fit #chi^{2}/dof = %3.2f", ChiSqrt/(nPoints-nPars)));
      yplace-=.02;
      text->DrawLatex(xplace, yplace, Form("After Fit #chi^{2} = %3.2f", plot_chisq));
      yplace-=.02;
      text->DrawLatex(xplace, yplace, Form("After Fit #chi^{2}/dof = %3.2f", plot_chisq/(double)(nPoints-nPars)));
      yplace-=.02;
      text->DrawLatex(xplace, yplace, Form("#color[4]{USCap wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[0], err_Aluminium[0]));
      yplace-=.02;
      text->DrawLatex(xplace, yplace, Form("#color[4]{Barrel wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[1], err_Aluminium[1]));
      yplace-=.02;
      text->DrawLatex(xplace, yplace, Form("#color[4]{DSCap wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[2], err_Aluminium[2]));
      yplace-=.02;
      text->DrawLatex(xplace, yplace, Form("#color[4]{DSConcave  wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[3], err_Aluminium[3]));
      yplace-=.02;
      ChiSqrtAfter = plot_chisq;

    }
    else if (ind != 0 && FitType == 2){
      int nPars = 4;
      double xplace = .2;
      double yplace = 0.80;
      text->DrawLatex(xplace, yplace, Form("Fit Results with %d points, %d pars", nPoints, nPars));
      yplace-=.02;
      text->DrawLatex(xplace, yplace , Form("Before Fit #chi^{2} = %3.2f", ChiSqrt));
      yplace-=.02;
      text->DrawLatex(xplace, yplace, Form("Before Fit #chi^{2}/dof = %3.2f", ChiSqrt/(nPoints-nPars)));
      yplace-=.02;
      text->DrawLatex(xplace, yplace, Form("After Fit #chi^{2} = %3.2f", plot_chisq));
      yplace-=.02;
      text->DrawLatex(xplace, yplace, Form("After Fit #chi^{2}/dof = %3.2f", plot_chisq/(double)(nPoints-nPars)));
      yplace-=.02;
      text->DrawLatex(xplace, yplace, Form("#color[4]{USCap wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[0], err_Aluminium[0]));
      yplace-=.02;
      text->DrawLatex(xplace, yplace, Form("#color[4]{Barrel wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[1], err_Aluminium[1]));
      yplace-=.02;
      text->DrawLatex(xplace, yplace, Form("#color[4]{DSCap wgt(Al) = %3.2f #pm %3.2f}", wgt_Aluminium[2], err_Aluminium[2]));
      yplace-=.02;
      text->DrawLatex(xplace, yplace, Form("#color[4]{DSConcave  wgt(He) = %3.2f #pm %3.2f}", wgt_Aluminium[3], err_Aluminium[3]));
      yplace-=.02;
      text->DrawLatex(xplace, yplace, Form("#color[4]{USCap wgt(He) = %3.2f #pm %3.2f}", wgt_Helium[0], err_Helium[0]));
      yplace-=.02;
      text->DrawLatex(xplace, yplace, Form("#color[4]{barrel wgt(He) = %3.2f #pm %3.2f}", wgt_Helium[1], err_Helium[1]));
      yplace-=.02;
      text->DrawLatex(xplace, yplace, Form("#color[4]{DSCap wgt(He) = %3.2f #pm %3.2f}", wgt_Helium[2], err_Helium[2]));
      yplace-=.02;
      text->DrawLatex(xplace, yplace, Form("#color[4]{DSConcave  wgt(He) = %3.2f #pm %3.2f}", wgt_Helium[3], err_Helium[3]));

      ChiSqrtAfter = plot_chisq;

    }


    //std::cout<<"FInished Drawing legend"<<std::endl;
    delete text;
    plotter->AddHistoTitle(Hist_title.c_str(),.04);
    plotter->WritePreliminary("TL", .025, 0, 0, false);
    // Plot Lower Plot: Data vs MC Ratio
    c->cd(); // Go back to default Canvas before creating 2nd Pad
    //TPad *pad2 = new TPad("pad2", "pad2", 0.05, 0.05, 1, 0.3);

    //pad2->SetTopMargin(0);
    //pad2->SetBottomMargin(0.2);
    c->Modified();
    TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
    pad2->SetTopMargin(0);
    pad2->SetBottomMargin(0.2);
    pad2->SetGridx(); // vertical grid
    pad2->Draw();
    pad2->cd();

    // Calculate the Ratio

    //h_data_mc_ratio->Draw("HIST");
    plotter->axis_title_size_x = 0.1;
    plotter->axis_title_offset_y = .4;
    plotter->axis_title_offset_x = 1.35;
    plotter->axis_title_size_y = 0.12;
    plotter->axis_label_size = 0.1;
    plotter->axis_maximum = 2.5;
    plotter->axis_minimum = .5;

    plotter->DrawDataMCRatio(data, mc_total, 1.0, false, false , -.5, 3, "#frac{Data}{MC}", false);
    // Add Ratio = 1 Line
    TLine ratio_1;
    ratio_1.SetLineWidth(2);
    ratio_1.SetLineStyle(7);
    ratio_1.SetLineColor(kBlue);
    double line_min = h_data_Combined->GetBinLowEdge(1);
    double line_max = h_data_Combined->GetBinLowEdge(h_data_Combined->GetNbinsX()+1);
    ratio_1.DrawLine(line_min,1,line_max,1);
    // Plot Output
    c->Update();
    c->cd();
    c->Print(pdf_label.c_str(),"pdf");

    delete legend;
    delete pad1;
    delete pad2;
    delete c;
    delete data;
    delete mc_total;
    delete h_data_Combined;
    delete h_Helium_region1;
    delete h_Aluminium_region1;
    delete h_Carbon_Combined;
    delete h_Iron_Combined;
    delete h_Lead_Combined;
    delete h_Other_Combined;
    delete h_data_region2;
    delete h_Helium_region2;
    delete h_Aluminium_region2;
    delete h_Carbon_region2;
    delete h_Iron_region2;
    delete h_Lead_region2;
    delete h_Other_region2;
    delete h_data_region3;
    delete h_Helium_region3;
    delete h_Aluminium_region3;
    delete h_Carbon_region3;
    delete h_Iron_region3;
    delete h_Lead_region3;
    delete h_Other_region3;
    delete h_data_region4;
    delete h_Helium_region4;
    delete h_Aluminium_region4;
    delete h_Carbon_region4;
    delete h_Iron_region4;
    delete h_Lead_region4;
    delete h_Other_region4;
  }




  void Convolution_Tool::ColorHists(TH1D* data, TH1D* Helium,
     TH1D* Aluminium, TH1D* Carbon, TH1D* Iron, TH1D* Lead,  TH1D* Other)
  {
    // MC
    Helium->SetFillColor(Helium9_colorScheme.at(1));
    Helium->SetFillStyle(1001);

    Aluminium->SetFillColor(Helium9_colorScheme.at(4));
    Aluminium->SetFillStyle(1001);

    Carbon->SetFillColor(Helium9_colorScheme.at(2));
    Carbon->SetFillStyle(1001);

    Iron->SetFillColor(Helium9_colorScheme.at(0));
    Iron->SetFillStyle(1001);

    Lead->SetFillColor(Helium9_colorScheme.at(3));
    Lead->SetFillStyle(1001);

    Other->SetFillColor(Helium9_colorScheme.at(5));
    Other->SetFillStyle(1001);

    // Data
    data->SetMarkerColor(kBlack);
    data->SetMarkerStyle(20);
    data->SetMarkerSize(1);
    data->SetLineWidth(1);
    data->SetLineColor(kBlack);
    data->SetFillStyle(0);
  }

  void Convolution_Tool::ColorHistsForLines(TH1D* data, TH1D* Helium,
    TH1D* Aluminium, TH1D* Carbon, TH1D* Iron, TH1D* Lead,  TH1D* Other)
  {
    // MC
    Helium->SetLineColor(Helium9_colorScheme.at(1));
    Aluminium->SetLineColor(Helium9_colorScheme.at(4));
    Carbon->SetLineColor(Helium9_colorScheme.at(2));
    Iron->SetLineColor(Helium9_colorScheme.at(0));
    Lead->SetLineColor(Helium9_colorScheme.at(3));
    Other->SetLineColor(Helium9_colorScheme.at(5));

    Helium->SetMarkerStyle(0);
    Aluminium->SetMarkerStyle(0);
    Carbon->SetMarkerStyle(0);
    Iron->SetMarkerStyle(0);
    Lead->SetMarkerStyle(0);
    Other->SetMarkerStyle(0);


    Helium->SetLineWidth(4);
    Aluminium->SetLineWidth(4);
    Carbon->SetLineWidth(4);
    Iron->SetLineWidth(4);
    Lead->SetLineWidth(4);
    Other->SetLineWidth(4);

    // Data
    data->SetMarkerColor(kBlack);
    data->SetMarkerStyle(20);
    data->SetMarkerSize(1);
    data->SetLineWidth(1);
    data->SetLineColor(kBlack);
    data->SetFillStyle(0);
  }

  void Convolution_Tool::ColorHists(TH1D* Carbon, TH1D* Iron, TH1D* Lead,  TH1D* Other)
  {

    Carbon->SetFillColor(Helium9_colorScheme.at(2));
    Carbon->SetFillStyle(1001);

    Iron->SetFillColor(Helium9_colorScheme.at(0));
    Iron->SetFillStyle(1001);

    Lead->SetFillColor(Helium9_colorScheme.at(3));
    Lead->SetFillStyle(1001);

    Other->SetFillColor(Helium9_colorScheme.at(5));
    Other->SetFillStyle(1001);


  }
  void Convolution_Tool::ColorHistsForLines(TH1D* Carbon, TH1D* Iron, TH1D* Lead,  TH1D* Other)
  {

    Carbon->SetLineColor(Helium9_colorScheme.at(2));
    Iron->SetLineColor(41);
    Lead->SetLineColor(47);
    Other->SetLineColor(Helium9_colorScheme.at(5));

    Carbon->SetMarkerStyle(0);
    Iron->SetMarkerStyle(0);
    Lead->SetMarkerStyle(0);
    Other->SetMarkerStyle(0);


    Carbon->SetLineWidth(4);
    Iron->SetLineWidth(4);
    Lead->SetLineWidth(4);
    Other->SetLineWidth(4);

  }


  void Convolution_Tool::ColorData(TH1D* data){
    data->SetMarkerColor(kBlack);
    data->SetMarkerStyle(20);
    data->SetMarkerSize(1);
    data->SetLineWidth(1);
    data->SetLineColor(kBlack);
    data->SetFillStyle(0);
  }

  void Convolution_Tool::Color_HeliumHists(TH1D* Helium_UpsteamCap,
    TH1D* Helium_Barrel, TH1D* Helium_DownstreamCap, TH1D* Helium_DownstreamConcaveCap)
  {
    // MC
    Helium_UpsteamCap->SetFillColor(TColor::GetColor("#be29ec"));
    Helium_UpsteamCap->SetFillStyle(1001);

    Helium_Barrel->SetFillColor(TColor::GetColor("#d24f09"));
    Helium_Barrel->SetFillStyle(1001);

    Helium_DownstreamCap->SetFillColor(TColor::GetColor("#b8be10"));
    Helium_DownstreamCap->SetFillStyle(1001);

    Helium_DownstreamConcaveCap->SetFillColor(TColor::GetColor("#274e13"));
    Helium_DownstreamConcaveCap->SetFillStyle(1001);

  }
  void Convolution_Tool::Color_HeliumHistsForLines(TH1D* Helium_UpsteamCap,
    TH1D* Helium_Barrel, TH1D* Helium_DownstreamCap, TH1D* Helium_DownstreamConcaveCap)
  {

    // MC
    Helium_UpsteamCap->SetLineColor(TColor::GetColor("#be29ec"));
    Helium_UpsteamCap->SetMarkerStyle(0);
    Helium_UpsteamCap->SetLineWidth(4);
    Helium_Barrel->SetLineColor(TColor::GetColor("#d24f09"));
    Helium_Barrel->SetMarkerStyle(0);
    Helium_Barrel->SetLineWidth(4);
    Helium_DownstreamCap->SetLineColor(TColor::GetColor("#b8be10"));
    Helium_DownstreamCap->SetMarkerStyle(0);
    Helium_DownstreamCap->SetLineWidth(4);
    Helium_DownstreamConcaveCap->SetLineColor(TColor::GetColor("#274e13"));
    Helium_DownstreamConcaveCap->SetMarkerStyle(0);
    Helium_DownstreamConcaveCap->SetLineWidth(4);

  }
  void Convolution_Tool::Color_AluminiumHists(TH1D* Aluminium_UpsteamCap, TH1D* Aluminium_Barrel, TH1D* Aluminium_DownstreamCap, TH1D* Aluminium_DownstreamConcaveCap)
  {
    // MC
    Aluminium_UpsteamCap->SetFillColor(TColor::GetColor("#09ae51"));  //Helium9_colorScheme.at(4));
    Aluminium_UpsteamCap->SetFillStyle(1001);

    Aluminium_Barrel->SetFillColor( TColor::GetColor("#098cd2"));///Helium9_colorScheme.at(3));
    Aluminium_Barrel->SetFillStyle(1001);

    Aluminium_DownstreamCap->SetFillColor(Helium9_colorScheme.at(10));
    Aluminium_DownstreamCap->SetFillStyle(1001);

    Aluminium_DownstreamConcaveCap->SetFillColor(Helium9_colorScheme.at(15));
    Aluminium_DownstreamConcaveCap->SetFillStyle(1001);

  }
  void Convolution_Tool::Color_AluminiumHistsForLines(TH1D* Aluminium_UpsteamCap,
     TH1D* Aluminium_Barrel, TH1D* Aluminium_DownstreamCap,
     TH1D* Aluminium_DownstreamConcaveCap)
  {
    // MC

    Aluminium_UpsteamCap->SetLineColor(TColor::GetColor("#09ae51"));
    Aluminium_UpsteamCap->SetMarkerStyle(0);
    Aluminium_UpsteamCap->SetLineWidth(4);
    Aluminium_Barrel->SetLineColor(TColor::GetColor("#098cd2"));
    Aluminium_Barrel->SetMarkerStyle(0);
    Aluminium_Barrel->SetLineWidth(4);
    Aluminium_DownstreamCap->SetLineColor(Helium9_colorScheme.at(10));
    Aluminium_DownstreamCap->SetMarkerStyle(0);
    Aluminium_DownstreamCap->SetLineWidth(4);
    Aluminium_DownstreamConcaveCap->SetLineColor(Helium9_colorScheme.at(15));
    Aluminium_DownstreamConcaveCap->SetMarkerStyle(0);
    Aluminium_DownstreamConcaveCap->SetLineWidth(4);
  }
  double Convolution_Tool::calc_ChiSq(TH1D* data, TH1D* Helium, TH1D* Aluminium, TH1D* Carbon, TH1D* Lead, TH1D* Iron, TH1D* Other)
  {
    //double mc_ratio = POT_ratio;
    double mc_ratio = 1.0;
    double chi_sq = 0.0;

    for (int i = 1; i <= data->GetNbinsX(); ++i){
      // Get N(Events) in Single Bin
      double err = data->GetBinError(i);
      double nData = data->GetBinContent(i);
      if (nData == 0) continue;
      double nHelium = Helium->GetBinContent(i);
      double nAluminium = Aluminium->GetBinContent(i);
      double nCarbon = Carbon->GetBinContent(i);
      double nLead = Lead->GetBinContent(i);
      double nIron = Iron->GetBinContent(i);
      double nOther = Other->GetBinContent(i);

      // Add All MC and scale them
      double nMC_total = (nHelium + nAluminium + nCarbon + nLead + nIron  + nOther) * mc_ratio;

      double delta = pow((nData-nMC_total),2) / pow(err,2);
      chi_sq += delta;
    }
    return chi_sq;
  }
  /////////

  double Convolution_Tool::calc_ChiSq(TH1D* data, TH1D* Helium_upstream,
    TH1D* Helium_barrel, TH1D* Helium_downstream,TH1D* Helium_downstreamconcave, TH1D* Aluminium_upstream,
    TH1D* Aluminium_barrel, TH1D* Aluminium_downstream,TH1D* Aluminium_downstreamconcave,
    TH1D* Carbon, TH1D* Lead, TH1D* Iron, TH1D* Other)
    {
      //double mc_ratio = POT_ratio;
      double mc_ratio = 1.0;
      double chi_sq = 0.0;

      for (int i = 1; i <= data->GetNbinsX(); ++i){
        // Get N(Events) in Single Bin
        double err = data->GetBinError(i);
        double nData = data->GetBinContent(i);
        if (nData == 0) continue;
        double nHelium_upstream = Helium_upstream->GetBinContent(i);
        double nHelium_barrel = Helium_barrel->GetBinContent(i);
        double nHelium_downstream = Helium_downstream->GetBinContent(i);
        double nHelium_downstreamconcave = Helium_downstreamconcave->GetBinContent(i);

        double nAluminium_upstream = Aluminium_upstream->GetBinContent(i);
        double nAluminium_barrel = Aluminium_barrel->GetBinContent(i);
        double nAluminium_downstream = Aluminium_downstream->GetBinContent(i);
        double nAluminium_downstreamconcave = Aluminium_downstreamconcave->GetBinContent(i);

        double nCarbon = Carbon->GetBinContent(i);
        double nLead = Lead->GetBinContent(i);
        double nIron = Iron->GetBinContent(i);
        double nOther = Other->GetBinContent(i);

        // Add All MC and scale them
        double nMC_total = (nHelium_upstream +  nHelium_barrel + nHelium_downstream +
          nHelium_downstreamconcave + nAluminium_upstream + nAluminium_barrel + nAluminium_downstream +
          nAluminium_downstreamconcave  + nCarbon + nLead + nIron  + nOther) * mc_ratio;

          double delta = pow((nData-nMC_total),2) / pow(err,2);
          chi_sq += delta;
        }
        return chi_sq;
      }
      double Convolution_Tool::calc_LogChiSq(TH1D* data, TH1D* Helium,
         TH1D* Aluminium, TH1D* Carbon, TH1D* Lead, TH1D* Iron, TH1D* Other)
      {
        //double mc_ratio = POT_ratio;
        double mc_ratio = 1.0;
        double chi_sq = 0.0;


        for (int i = 1; i <= data->GetNbinsX(); ++i){
          // Get N(Events) in Single Bin
          double nData = data->GetBinContent(i);
          if (nData == 0) continue;
          double nHelium = Helium->GetBinContent(i);
          double nAluminium = Aluminium->GetBinContent(i);
          double nCarbon = Carbon->GetBinContent(i);
          double nLead = Lead->GetBinContent(i);
          double nIron = Iron->GetBinContent(i);
          double nOther = Other->GetBinContent(i);

          // Add All MC and scale them
          double nMC_total = (nHelium + nAluminium + nCarbon + nLead + nIron  + nOther) * mc_ratio;
          if (nMC_total <= 0) continue;
          double c = nData * log(nMC_total);
          double delta = 2 * (nMC_total - c);
          chi_sq += delta;
        }

        return chi_sq;
      }

  double Convolution_Tool::calc_LogChiSq(TH1D* data, TH1D* Helium_upstream,
    TH1D* Helium_barrel, TH1D* Helium_downstream,TH1D* Helium_downstreamconcave, TH1D* Aluminium_upstream,
    TH1D* Aluminium_barrel, TH1D* Aluminium_downstream,TH1D* Aluminium_downstreamconcave,
    TH1D* Carbon, TH1D* Lead, TH1D* Iron, TH1D* Other)
    {
      //double mc_ratio = POT_ratio;
      double mc_ratio = 1.0;
      double chi_sq = 0.0;

      for (int i = 1; i <= data->GetNbinsX(); ++i){
        // Get N(Events) in Single Bin
        double nData = data->GetBinContent(i);
        if (nData == 0) continue;
        double nHelium_upstream = Helium_upstream->GetBinContent(i);
        double nHelium_barrel = Helium_barrel->GetBinContent(i);
        double nHelium_downstream = Helium_downstream->GetBinContent(i);
        double nHelium_downstreamconcave = Helium_downstreamconcave->GetBinContent(i);

        double nAluminium_upstream = Aluminium_upstream->GetBinContent(i);
        double nAluminium_barrel = Aluminium_barrel->GetBinContent(i);
        double nAluminium_downstream = Aluminium_downstream->GetBinContent(i);
        double nAluminium_downstreamconcave = Aluminium_downstreamconcave->GetBinContent(i);

        double nCarbon = Carbon->GetBinContent(i);
        double nLead = Lead->GetBinContent(i);
        double nIron = Iron->GetBinContent(i);
        double nOther = Other->GetBinContent(i);

        // Add All MC and scale them
        double nMC_total = (nHelium_upstream +  nHelium_barrel + nHelium_downstream +
          nHelium_downstreamconcave + nAluminium_upstream + nAluminium_barrel + nAluminium_downstream +
          nAluminium_downstreamconcave  + nCarbon + nLead + nIron  + nOther) * mc_ratio;
          if (nMC_total <= 0) continue;
          double c = nData * log(nMC_total);
          double delta = 2 * (nMC_total - c);
          chi_sq += delta;
        }

        return chi_sq;
      }

  void Convolution_Tool::ApplyFitResults(Convolution_hist &hist, double Alwgt)
  {
    //std::cout<<"Applying Fit Result to "<<sb.name<<std::endl;
    // Clone Original Histograms

    hist.MnvH1D_mc_Convoluted_Helium[1] = (MnvH1D*) hist.MnvH1D_mc_Convoluted_Helium[0]->Clone();
    hist.MnvH1D_mc_Convoluted_Aluminium[1] = (MnvH1D*) hist.MnvH1D_mc_Convoluted_Aluminium[0]->Clone();
    hist.MnvH1D_mc_Convoluted_Carbon[1] = (MnvH1D*) hist.MnvH1D_mc_Convoluted_Carbon[0]->Clone();
    hist.MnvH1D_mc_Convoluted_Iron[1] = (MnvH1D*) hist.MnvH1D_mc_Convoluted_Iron[0]->Clone();
    hist.MnvH1D_mc_Convoluted_Lead[1] = (MnvH1D*) hist.MnvH1D_mc_Convoluted_Lead[0]->Clone();
    hist.MnvH1D_mc_Convoluted_Other[1] =(MnvH1D*) hist.MnvH1D_mc_Convoluted_Other[0]->Clone();

    // Scale
    //auto NXbins = sb.MnvH1D_mc_Convoluted_Aluminium[1]->GetNbinsX();
    //std::cout<<"applying scaler vertex X: "<< Alwgt<< std::endl;
    //std::cout<<"Checking bins  = " << NXbins<<std::endl;
    hist.MnvH1D_mc_Convoluted_Aluminium[1]->Scale(Alwgt);
  }

  void Convolution_Tool::ApplyFitResults_toRegions(Convolution_CryoRegions &hist, double Alwgt_Upstream,
    double Alwgt_Barrel,double Alwgt_Downstream, double Alwgt_Concave ){

      ApplyFitResults(hist.Upstream,   Alwgt_Upstream);
      ApplyFitResults(hist.Barrel,     Alwgt_Barrel);
      ApplyFitResults(hist.Downstream, Alwgt_Downstream);
      ApplyFitResults(hist.Concave,    Alwgt_Concave);

    }

    void Convolution_Tool::ApplyFitResults_toMaterialVertex(ConvolutionShiftMap &RegionMap, double Alwgt_Upstream,double Alwgt_Barrel,double Alwgt_Downstream, double Alwgt_Concave ){

      ApplyFitResults_toRegions(RegionMap.Vertex_X_Regions, Alwgt_Upstream, Alwgt_Barrel, Alwgt_Downstream,  Alwgt_Concave );
      ApplyFitResults_toRegions(RegionMap.Vertex_Y_Regions, Alwgt_Upstream, Alwgt_Barrel, Alwgt_Downstream,  Alwgt_Concave );
      ApplyFitResults_toRegions(RegionMap.Vertex_Z_Regions, Alwgt_Upstream, Alwgt_Barrel, Alwgt_Downstream,  Alwgt_Concave );
      ApplyFitResults_toRegions(RegionMap.Vertex_R_Regions, Alwgt_Upstream, Alwgt_Barrel, Alwgt_Downstream,  Alwgt_Concave );

    }

    void Convolution_Tool::ApplyFitResults_toMaterialTRUEVertex(ConvolutionShiftMap &RegionMap, double Alwgt_Upstream,double Alwgt_Barrel,double Alwgt_Downstream, double Alwgt_Concave ){

      ApplyFitResults_toRegions(RegionMap.Vertex_TRUE_X_Regions, Alwgt_Upstream, Alwgt_Barrel, Alwgt_Downstream,  Alwgt_Concave );
      ApplyFitResults_toRegions(RegionMap.Vertex_TRUE_Y_Regions, Alwgt_Upstream, Alwgt_Barrel, Alwgt_Downstream,  Alwgt_Concave );
      ApplyFitResults_toRegions(RegionMap.Vertex_TRUE_Z_Regions, Alwgt_Upstream, Alwgt_Barrel, Alwgt_Downstream,  Alwgt_Concave );
      ApplyFitResults_toRegions(RegionMap.Vertex_TRUE_R_Regions, Alwgt_Upstream, Alwgt_Barrel, Alwgt_Downstream,  Alwgt_Concave );

    }


    void Convolution_Tool::ApplyFitResults_toMaterialNonVertexVars(ConvolutionShiftMap &RegionMap, double Alwgt_Upstream,double Alwgt_Barrel,double Alwgt_Downstream, double Alwgt_Concave ){

      ApplyFitResults_toRegions(RegionMap.muonPT_Regions, Alwgt_Upstream, Alwgt_Barrel, Alwgt_Downstream,  Alwgt_Concave );
      ApplyFitResults_toRegions(RegionMap.muonPZ_Regions, Alwgt_Upstream, Alwgt_Barrel, Alwgt_Downstream,  Alwgt_Concave );
      ApplyFitResults_toRegions(RegionMap.muonE_Regions, Alwgt_Upstream, Alwgt_Barrel, Alwgt_Downstream,  Alwgt_Concave );
      ApplyFitResults_toRegions(RegionMap.muontheta_Regions, Alwgt_Upstream, Alwgt_Barrel, Alwgt_Downstream,  Alwgt_Concave );
      ApplyFitResults_toRegions(RegionMap.muonDOCA_Regions, Alwgt_Upstream, Alwgt_Barrel, Alwgt_Downstream,  Alwgt_Concave );
      ApplyFitResults_toRegions(RegionMap.NearestWall_Regions, Alwgt_Upstream, Alwgt_Barrel, Alwgt_Downstream,  Alwgt_Concave );
      ApplyFitResults_toRegions(RegionMap.recoilDOCA_Regions, Alwgt_Upstream, Alwgt_Barrel, Alwgt_Downstream,  Alwgt_Concave );
      ApplyFitResults_toRegions(RegionMap.recoilAngle_Regions, Alwgt_Upstream, Alwgt_Barrel, Alwgt_Downstream,  Alwgt_Concave );
      ApplyFitResults_toRegions(RegionMap.tracklength_Regions, Alwgt_Upstream, Alwgt_Barrel, Alwgt_Downstream,  Alwgt_Concave );


    }

void Convolution_Tool::ApplyFitResults_toEmpty(){

ApplyFitResults_toMaterialVertex(Empty, wgt_Aluminium.at(0),
wgt_Aluminium.at(1),wgt_Aluminium.at(2), wgt_Aluminium.at(3) );

}

void Convolution_Tool::ApplyFitResults_toEmpty_Fiducial(){

ApplyFitResults_toMaterialVertex(Empty_Fid, wgt_Aluminium.at(0),
wgt_Aluminium.at(1),wgt_Aluminium.at(2), wgt_Aluminium.at(3) );

}

void Convolution_Tool::ApplyFitResults_toTRUEEmpty(){

ApplyFitResults_toMaterialTRUEVertex(Empty, wgt_Aluminium.at(0),
wgt_Aluminium.at(1),wgt_Aluminium.at(2), wgt_Aluminium.at(3)  );

}

void Convolution_Tool::ApplyFitResults_toTRUEEmpty_Fiducial(){

ApplyFitResults_toMaterialTRUEVertex(Empty_Fid, wgt_Aluminium.at(0),
wgt_Aluminium.at(1),wgt_Aluminium.at(2), wgt_Aluminium.at(3)  );

}

void Convolution_Tool::ApplyFitResults_tononFitVarEmpty(){

ApplyFitResults_toMaterialNonVertexVars(Empty, wgt_Aluminium.at(0),
wgt_Aluminium.at(1),wgt_Aluminium.at(2), wgt_Aluminium.at(3)  );

}

void Convolution_Tool::ApplyFitResults_tononFitVarEmpty_Fiducial(){

ApplyFitResults_toMaterialNonVertexVars(Empty_Fid, wgt_Aluminium.at(0),
wgt_Aluminium.at(1),wgt_Aluminium.at(2), wgt_Aluminium.at(3)  );

}


void Convolution_Tool::ApplyFitResults_toTRUEFull(){

ApplyFitResults_toMaterialTRUEVertex(Full, wgt_Aluminium.at(0),
wgt_Aluminium.at(1),wgt_Aluminium.at(2), wgt_Aluminium.at(3)  );

}

void Convolution_Tool::ApplyFitResults_toTRUEFull_Fiducial(){

ApplyFitResults_toMaterialTRUEVertex(Full_Fid, wgt_Aluminium.at(0),
wgt_Aluminium.at(1),wgt_Aluminium.at(2), wgt_Aluminium.at(3)  );

}
void Convolution_Tool::ApplyFitResults_tononFitVarFull(){

ApplyFitResults_toMaterialNonVertexVars(Full, wgt_Aluminium.at(0),
wgt_Aluminium.at(1),wgt_Aluminium.at(2), wgt_Aluminium.at(3)  );

}

void Convolution_Tool::ApplyFitResults_tononFitVarFull_Fiducial(){

ApplyFitResults_toMaterialNonVertexVars(Full_Fid, wgt_Aluminium.at(0),
wgt_Aluminium.at(1),wgt_Aluminium.at(2), wgt_Aluminium.at(3)  );

}



void Convolution_Tool::ApplyFitResults_toFull(){

ApplyFitResults_toMaterialVertex(Full, wgt_Aluminium.at(0),wgt_Aluminium.at(1),
wgt_Aluminium.at(2), wgt_Aluminium.at(3) );

}

void Convolution_Tool::ApplyFitResults_toFull_Fiducial(){

ApplyFitResults_toMaterialVertex(Full_Fid, wgt_Aluminium.at(0),
wgt_Aluminium.at(1),wgt_Aluminium.at(2), wgt_Aluminium.at(3) );

}



void Convolution_Tool::ApplyFitResults_toFullEmptyJointFit(){

  ApplyFitResults_toMaterialVertex(Full, wgt_Aluminium_Full.at(0),
  wgt_Aluminium_Full.at(1),wgt_Aluminium_Full.at(2), wgt_Aluminium_Full.at(3) );
  ApplyFitResults_toMaterialVertex(Empty, wgt_Aluminium_Empty.at(0),
  wgt_Aluminium_Empty.at(1),wgt_Aluminium_Empty.at(2), wgt_Aluminium_Empty.at(3) );



}




    void Convolution_Tool::Fill_Alwgt(std::vector<double> inputWgt, std::vector<double> inputwgt_errors ){

      for(auto cat: inputWgt){
        wgt_Aluminium.push_back(cat);
      }

      for(auto cat: inputwgt_errors){
        err_Aluminium.push_back(cat);
      }

    }



    void Convolution_Tool::Fill_Alwgt_full_empty(std::vector<double> inputWgt,
       std::vector<double> inputwgt_errors ){

      wgt_Aluminium_Empty.push_back(inputWgt.at(0));
      wgt_Aluminium_Empty.push_back(inputWgt.at(1));
      wgt_Aluminium_Empty.push_back(inputWgt.at(2));
      wgt_Aluminium_Empty.push_back(inputWgt.at(3));


      wgt_Aluminium_Full.push_back(inputWgt.at(4));
      wgt_Aluminium_Full.push_back(inputWgt.at(5));
      wgt_Aluminium_Full.push_back(inputWgt.at(6));
      wgt_Aluminium_Full.push_back(inputWgt.at(7));

      err_Aluminium_Empty.push_back(inputwgt_errors.at(0));
      err_Aluminium_Empty.push_back(inputwgt_errors.at(1));
      err_Aluminium_Empty.push_back(inputwgt_errors.at(2));
      err_Aluminium_Empty.push_back(inputwgt_errors.at(3));


      err_Aluminium_Full.push_back(inputwgt_errors.at(4));
      err_Aluminium_Full.push_back(inputwgt_errors.at(5));
      err_Aluminium_Full.push_back(inputwgt_errors.at(6));
      err_Aluminium_Full.push_back(inputwgt_errors.at(7));


    }

    void Convolution_Tool::FillEmpty_Normal_Fit_ParametersXY(double meanX,
       double sigmaX, double meanY , double sigmaY){

      global_MapParametersXY_Empty[kX].mean = meanX;
      global_MapParametersXY_Empty[kX].stddev = sigmaX;
      global_MapParametersXY_Empty[kY].mean = meanY;
      global_MapParametersXY_Empty[kY].stddev = sigmaY;

    }

    void Convolution_Tool::FillFull_Normal_Fit_ParametersXY(double meanX,
       double sigmaX, double meanY , double sigmaY){

      global_MapParametersXY_Full[kX].mean = meanX;
      global_MapParametersXY_Full[kX].stddev = sigmaX;
      global_MapParametersXY_Full[kY].mean = meanY;
      global_MapParametersXY_Full[kY].stddev = sigmaY;

    }

    void Convolution_Tool::Clear_Al_wgt(){
    wgt_Aluminium.clear();
    err_Aluminium.clear();
    }


    void Convolution_Tool::WriteHist_toFile(TFile& f, MnvH1D*inputhist, char * name ){
      f.cd();
      inputhist->Clone()->Write(name);

    }



    void Convolution_Tool::Write_dataHist_toFile(TFile& f,
       Convolution_hist inputMap, char * nameinput){
      char name[1024];
      sprintf(name, "%s_Data", nameinput);
      WriteHist_toFile(f, inputMap.MnvH1D_data,  name );
    }

    void Convolution_Tool::Write_RecoTrueHists_toFile(TFile& f,
      Convolution_hist inputMap, char *nameinput){
      char name[1024];
      sprintf(name, "%s_Total_RECO",nameinput);
      WriteHist_toFile(f, inputMap.MnvH1D_mc_Reco,  name );

      sprintf(name, "%s_Total_TRUTH",nameinput);
      WriteHist_toFile(f, inputMap.MnvH1D_mc_TRUTH,  name );
    }


    void Convolution_Tool::Write_Convolution_hist_toFile_index(TFile& f,
       Convolution_hist inputMap, char *nameinput, int index){
      char name[1024];
      //sprintf(name, "%s_Total_Convoluted", nameinput);
      //WriteHist_toFile(f, inputMap.MnvH1D_mc_Convoluted[index],  nameinput );

      sprintf(name, "%s_Helium", nameinput);
      WriteHist_toFile(f, inputMap.MnvH1D_mc_Convoluted_Helium[index],  name );

      sprintf(name, "%s_Aluminium", nameinput);
      WriteHist_toFile(f, inputMap.MnvH1D_mc_Convoluted_Aluminium[index],  name );

      sprintf(name, "%s_Carbon", nameinput);
      WriteHist_toFile(f, inputMap.MnvH1D_mc_Convoluted_Carbon[index],  name );

      sprintf(name, "%s_Iron", nameinput);
      WriteHist_toFile(f, inputMap.MnvH1D_mc_Convoluted_Iron[index],  name );

      sprintf(name, "%s_Lead", nameinput);
      WriteHist_toFile(f, inputMap.MnvH1D_mc_Convoluted_Lead[index],  name );

      sprintf(name, "%s_Other", nameinput);
      WriteHist_toFile(f, inputMap.MnvH1D_mc_Convoluted_Other[index],  name );

    }

    void Convolution_Tool::Write_Convolution_Region_Data_toFile(TFile& f,
       Convolution_CryoRegions inputMap, char *nameinput){

      char name[1024];
      sprintf(name, "%s_Upstream",nameinput);
      Write_dataHist_toFile(f, inputMap.Upstream, name);

      sprintf(name, "%s_Barrel", nameinput);
      Write_dataHist_toFile(f, inputMap.Barrel, name);

      sprintf(name, "%s_Downstream",nameinput);
      Write_dataHist_toFile(f, inputMap.Downstream, name);

      sprintf(name, "%s_Concave",nameinput);
      Write_dataHist_toFile(f, inputMap.Concave, name);


    }


    void Convolution_Tool::Write_Convolution_Region_Total_toFile(TFile& f,
       Convolution_CryoRegions inputMap, char *nameinput){

      char name[1024];
      sprintf(name, "%s_Upstream",nameinput);
      Write_RecoTrueHists_toFile(f, inputMap.Upstream, name);

      sprintf(name, "%s_Barrel",nameinput);
      Write_RecoTrueHists_toFile(f, inputMap.Barrel, name);

      sprintf(name, "%s_Downstream",nameinput);
      Write_RecoTrueHists_toFile(f, inputMap.Downstream, name);

      sprintf(name, "%s_Concave",nameinput);
      Write_RecoTrueHists_toFile(f, inputMap.Concave, name);

    }

    void Convolution_Tool::Write_Convolution_Region_Convolution_hist_toFile_index(TFile& f, Convolution_CryoRegions inputMap, char *nameinput, int index){

      char name[1024];
      sprintf(name, "%s_Upstream",nameinput);
      Write_Convolution_hist_toFile_index(f, inputMap.Upstream, name, index);

      sprintf(name, "%s_Barrel",nameinput);
      Write_Convolution_hist_toFile_index(f, inputMap.Barrel, name, index);

      sprintf(name, "%s_Downstream",nameinput);
      Write_Convolution_hist_toFile_index(f, inputMap.Downstream, name, index);

      sprintf(name, "%s_Concave",nameinput);
      Write_Convolution_hist_toFile_index(f, inputMap.Concave, name, index);

    }

    void Convolution_Tool::Write_init_VertexRegions(TFile& f, ConvolutionShiftMap ConvolutionShiftMap,  char *nameinput){

      char name[1024];

      sprintf(name, "Vertex_X_init_%s",  nameinput);
      std::cout<<"Writing name:"<<name <<std::endl;
      std::cout<<"writing data"<<std::endl;
      Write_Convolution_Region_Data_toFile( f, ConvolutionShiftMap.Vertex_X_Regions, name);
      std::cout<<"writing total"<<std::endl;
      //Write_Convolution_Region_Total_toFile( f,ConvolutionShiftMap.Vertex_X_Regions, name);
      std::cout<<"writing regions X " <<std::endl;
      Write_Convolution_Region_Convolution_hist_toFile_index( f, ConvolutionShiftMap.Vertex_X_Regions, name, 0);

      sprintf(name, "Vertex_Y_init_%s",  nameinput);
      std::cout<<"Writing name:"<<name <<std::endl;
      std::cout<<"writing data"<<std::endl;
      Write_Convolution_Region_Data_toFile( f, ConvolutionShiftMap.Vertex_Y_Regions, name);
      std::cout<<"writing total"<<std::endl;
    //  Write_Convolution_Region_Total_toFile( f,ConvolutionShiftMap.Vertex_Y_Regions, name);
      std::cout<<"writing regions Y " <<std::endl;
      Write_Convolution_Region_Convolution_hist_toFile_index( f, ConvolutionShiftMap.Vertex_Y_Regions, name, 0);


      sprintf(name, "Vertex_Z_init_%s",  nameinput);
      std::cout<<"Writing name:"<<name <<std::endl;
      std::cout<<"writing data"<<std::endl;
      Write_Convolution_Region_Data_toFile( f, ConvolutionShiftMap.Vertex_Z_Regions, name);
      std::cout<<"writing total"<<std::endl;
      //Write_Convolution_Region_Total_toFile( f,ConvolutionShiftMap.Vertex_Z_Regions, name);
      std::cout<<"writing regions Z " <<std::endl;
      Write_Convolution_Region_Convolution_hist_toFile_index( f, ConvolutionShiftMap.Vertex_Z_Regions, name, 0);


      sprintf(name, "Vertex_R_init_%s",  nameinput);
      std::cout<<"Writing name:"<<name <<std::endl;
      std::cout<<"writing data"<<std::endl;
      Write_Convolution_Region_Data_toFile( f, ConvolutionShiftMap.Vertex_R_Regions, name);
      std::cout<<"writing total"<<std::endl;
      //Write_Convolution_Region_Total_toFile( f,ConvolutionShiftMap.Vertex_R_Regions, name);
      std::cout<<"writing regions R " <<std::endl;
      Write_Convolution_Region_Convolution_hist_toFile_index( f, ConvolutionShiftMap.Vertex_R_Regions, name, 0);


    }

    void Convolution_Tool::Write_init_TRUEVertexRegions(TFile& f, ConvolutionShiftMap ConvolutionShiftMap,  char *nameinput){

      char name[1024];

      sprintf(name, "TRUE_Vertex_X_init_%s",  nameinput);
      std::cout<<"Writing name:"<<name <<std::endl;
      std::cout<<"writing data"<<std::endl;
      std::cout<<"writing total"<<std::endl;
      //Write_Convolution_Region_Total_toFile( f,ConvolutionShiftMapTRUE_.Vertex_X_Regions, name);
      std::cout<<"writing regions X " <<std::endl;
      Write_Convolution_Region_Convolution_hist_toFile_index( f, ConvolutionShiftMap.Vertex_TRUE_X_Regions, name, 0);

      sprintf(name, "TRUE_Vertex_Y_init_%s",  nameinput);
      std::cout<<"Writing name:"<<name <<std::endl;
      std::cout<<"writing data"<<std::endl;

      std::cout<<"writing total"<<std::endl;
    //  Write_Convolution_Region_Total_toFile( f,ConvolutionShiftMap.Vertex_Y_Regions, name);
      std::cout<<"writing regions Y " <<std::endl;
      Write_Convolution_Region_Convolution_hist_toFile_index( f, ConvolutionShiftMap.Vertex_TRUE_Y_Regions, name, 0);


      sprintf(name, "TRUE_Vertex_Z_init_%s",  nameinput);
      std::cout<<"Writing name:"<<name <<std::endl;
      std::cout<<"writing data"<<std::endl;

      std::cout<<"writing total"<<std::endl;
      //Write_Convolution_Region_Total_toFile( f,ConvolutionShiftMap.Vertex_Z_Regions, name);
      std::cout<<"writing regions Z " <<std::endl;
      Write_Convolution_Region_Convolution_hist_toFile_index( f, ConvolutionShiftMap.Vertex_TRUE_Z_Regions, name, 0);


      sprintf(name, "TRUE_Vertex_R_init_%s",  nameinput);
      std::cout<<"Writing name:"<<name <<std::endl;
      std::cout<<"writing data"<<std::endl;

      std::cout<<"writing total"<<std::endl;
      //Write_Convolution_Region_Total_toFile( f,ConvolutionShiftMap.Vertex_R_Regions, name);
      std::cout<<"writing regions R " <<std::endl;
      Write_Convolution_Region_Convolution_hist_toFile_index( f, ConvolutionShiftMap.Vertex_TRUE_R_Regions, name, 0);


    }

    void Convolution_Tool::Write_init_NonVertexRegions(TFile& f, ConvolutionShiftMap ConvolutionShiftMap,  char *nameinput){

      char name[1024];


      sprintf(name, "muonPT_init_%s",  nameinput);
      std::cout<<"Writing name:"<<name <<std::endl;
      Write_Convolution_Region_Convolution_hist_toFile_index( f, ConvolutionShiftMap.muonPT_Regions, name, 0);
      Write_Convolution_Region_Data_toFile( f, ConvolutionShiftMap.muonPT_Regions, name);

      sprintf(name, "muonPZ_init_%s",  nameinput);
      std::cout<<"writing PZ " <<std::endl;
      Write_Convolution_Region_Convolution_hist_toFile_index( f, ConvolutionShiftMap.muonPZ_Regions, name, 0);
      Write_Convolution_Region_Data_toFile( f, ConvolutionShiftMap.muonPZ_Regions, name);
      sprintf(name, "muonE_init_%s",  nameinput);
      std::cout<<"Writing name:"<<name <<std::endl;
      Write_Convolution_Region_Convolution_hist_toFile_index( f, ConvolutionShiftMap.muonE_Regions, name, 0);
      Write_Convolution_Region_Data_toFile( f, ConvolutionShiftMap.muonE_Regions, name);
      sprintf(name, "muontheta_init_%s",  nameinput);
      std::cout<<"Writing name:"<<name <<std::endl;
      Write_Convolution_Region_Convolution_hist_toFile_index( f, ConvolutionShiftMap.muontheta_Regions, name, 0);
      Write_Convolution_Region_Data_toFile( f, ConvolutionShiftMap.muontheta_Regions, name);

      sprintf(name, "muondoca_init_%s",  nameinput);
      std::cout<<"Writing name:"<<name <<std::endl;
      Write_Convolution_Region_Convolution_hist_toFile_index( f, ConvolutionShiftMap.muonDOCA_Regions, name, 0);
      Write_Convolution_Region_Data_toFile( f, ConvolutionShiftMap.muonDOCA_Regions, name);
      sprintf(name, "nearestwall_init_%s",  nameinput);
      std::cout<<"Writing name:"<<name <<std::endl;
      Write_Convolution_Region_Convolution_hist_toFile_index( f, ConvolutionShiftMap.NearestWall_Regions, name, 0);
      Write_Convolution_Region_Data_toFile( f, ConvolutionShiftMap.NearestWall_Regions, name);
      sprintf(name, "recoildoca_init_%s",  nameinput);
      std::cout<<"Writing name:"<<name <<std::endl;
      Write_Convolution_Region_Convolution_hist_toFile_index( f, ConvolutionShiftMap.recoilDOCA_Regions, name, 0);
      Write_Convolution_Region_Data_toFile( f, ConvolutionShiftMap.recoilDOCA_Regions, name);
      sprintf(name, "recoilangle_init_%s",  nameinput);
      std::cout<<"Writing name:"<<name <<std::endl;
      Write_Convolution_Region_Convolution_hist_toFile_index( f, ConvolutionShiftMap.recoilAngle_Regions, name, 0);
      Write_Convolution_Region_Data_toFile( f, ConvolutionShiftMap.recoilAngle_Regions, name);

      sprintf(name, "recoiltracklength_init_%s",  nameinput);
      std::cout<<"Writing name:"<<name <<std::endl;
      Write_Convolution_Region_Convolution_hist_toFile_index( f, ConvolutionShiftMap.tracklength_Regions, name, 0);
      Write_Convolution_Region_Data_toFile( f, ConvolutionShiftMap.tracklength_Regions, name);



    }

    void Convolution_Tool::Write_Fitted_VertexRegions(TFile& f, ConvolutionShiftMap ConvolutionShiftMap,   char *nameinput, int index){
      char name[1024];
      sprintf(name, "Vertex_X_wgted_%s",nameinput);
      Write_Convolution_Region_Convolution_hist_toFile_index( f, ConvolutionShiftMap.Vertex_X_Regions, name, 1);

      sprintf(name, "Vertex_Y_wgted_%s",nameinput);
      Write_Convolution_Region_Convolution_hist_toFile_index( f, ConvolutionShiftMap.Vertex_Y_Regions, name, 1);


      sprintf(name, "Vertex_Z_wgted_%s",nameinput);
      Write_Convolution_Region_Convolution_hist_toFile_index( f, ConvolutionShiftMap.Vertex_Z_Regions, name, 1);

      sprintf(name, "Vertex_R_wgted_%s",nameinput);
      Write_Convolution_Region_Convolution_hist_toFile_index( f, ConvolutionShiftMap.Vertex_R_Regions, name, 1);
    }

    void Convolution_Tool::Write_fitted_NonVertexRegions(TFile& f, ConvolutionShiftMap ConvolutionShiftMap,  char *nameinput){

      char name[1024];


      sprintf(name, "muonPT_wgted_%s",  nameinput);
      std::cout<<"Writing name:"<<name <<std::endl;
      Write_Convolution_Region_Convolution_hist_toFile_index( f, ConvolutionShiftMap.muonPT_Regions, name, 1);

      sprintf(name, "muonPZ_wgted_%s",  nameinput);
      std::cout<<"writing PZ " <<std::endl;
      Write_Convolution_Region_Convolution_hist_toFile_index( f, ConvolutionShiftMap.muonPZ_Regions, name, 1);

      sprintf(name, "muonE_wgted_%s",  nameinput);
      std::cout<<"Writing name:"<<name <<std::endl;
      Write_Convolution_Region_Convolution_hist_toFile_index( f, ConvolutionShiftMap.muonE_Regions, name, 1);

      sprintf(name, "muontheta_wgted_%s",  nameinput);
      std::cout<<"Writing name:"<<name <<std::endl;
      Write_Convolution_Region_Convolution_hist_toFile_index( f, ConvolutionShiftMap.muontheta_Regions, name, 1);


      sprintf(name, "muondoca_wgted_%s",  nameinput);
      std::cout<<"Writing name:"<<name <<std::endl;
      Write_Convolution_Region_Convolution_hist_toFile_index( f, ConvolutionShiftMap.muonDOCA_Regions, name, 1);

      sprintf(name, "nearestwall_wgted_%s",  nameinput);
      std::cout<<"Writing name:"<<name <<std::endl;
      Write_Convolution_Region_Convolution_hist_toFile_index( f, ConvolutionShiftMap.NearestWall_Regions, name, 1);

      sprintf(name, "recoildoca_wgted_%s",  nameinput);
      std::cout<<"Writing name:"<<name <<std::endl;
      Write_Convolution_Region_Convolution_hist_toFile_index( f, ConvolutionShiftMap.recoilDOCA_Regions, name, 1);

      sprintf(name, "recoilangle_wgted_%s",  nameinput);
      std::cout<<"Writing name:"<<name <<std::endl;
      Write_Convolution_Region_Convolution_hist_toFile_index( f, ConvolutionShiftMap.recoilAngle_Regions, name, 1);


      sprintf(name, "recoiltracklength_wgted_%s",  nameinput);
      std::cout<<"Writing name:"<<name <<std::endl;
      Write_Convolution_Region_Convolution_hist_toFile_index( f, ConvolutionShiftMap.tracklength_Regions, name, 1);



    }

    void Convolution_Tool::Write_Empty_init_and_wgted(TFile& f,  char *nameinput){
      std::cout<<"writting init hists for Empty"<< std::endl;
      Write_init_VertexRegions(f, Empty,  nameinput);
      Write_init_NonVertexRegions(f, Empty,  nameinput);
      Write_init_TRUEVertexRegions( f, Empty,  nameinput);
      Write_Fitted_VertexRegions( f, Empty,  nameinput, 1);
      Write_fitted_NonVertexRegions(f, Empty,  nameinput);
    }

    void Convolution_Tool::Write_Empty_init_and_wgted_Fiducial(TFile& f,  char *nameinput){
      std::cout<<"writting init hists for Empty"<< std::endl;
      Write_init_VertexRegions(f, Empty_Fid,  nameinput);
      Write_init_NonVertexRegions(f, Empty_Fid,  nameinput);
      Write_init_TRUEVertexRegions( f, Empty_Fid,  nameinput);
      Write_Fitted_VertexRegions( f, Empty_Fid,  nameinput, 1);
      Write_fitted_NonVertexRegions(f, Empty_Fid,  nameinput);
    }



void Convolution_Tool::Write_Full_init_and_wgted(TFile& f,  char *nameinput){
  Write_init_VertexRegions(f, Full,  nameinput);
  Write_init_NonVertexRegions(f, Full,  nameinput);
  Write_init_TRUEVertexRegions( f, Full,  nameinput);
  Write_Fitted_VertexRegions( f, Full,  nameinput, 1);
  Write_fitted_NonVertexRegions(f, Full,  nameinput);

}

void Convolution_Tool::Write_Full_init_and_wgted_Fiducial(TFile& f,  char *nameinput){
  Write_init_VertexRegions(f, Full_Fid,  nameinput);
  Write_init_NonVertexRegions(f, Full_Fid,  nameinput);
  Write_init_TRUEVertexRegions( f, Full_Fid,  nameinput);
  Write_Fitted_VertexRegions( f, Full_Fid,  nameinput, 1);
  Write_fitted_NonVertexRegions(f, Full_Fid,  nameinput);

}

std::string Convolution_Tool::constuctString_forHist(std::string inputname,
   bool isinit ,bool fullorempty, int rank,  int i, int j, int k , bool isFiducial){
std::string var;
std::string Status_string = fullorempty ? "Full" : "Empty";
std::string  type_string = isinit ? "init" : "wgted";
std::string Fid_string = isFiducial ? "_Fiducial" : "";
var = inputname + "_"+ type_string + "_"+ Status_string + "_rank_" + std::to_string(rank) + "_i_j_k_" + std::to_string(i) + "_" + std::to_string(j) + "_" + std::to_string(k) + Fid_string +"_";
return var;

}


void Convolution_Tool::ClearChisqrtvector(){
  ChiSq_before_fit.clear();
  ChiSq_after_fit.clear();
  ChiSq_before_fit_var.clear();
  ChiSq_after_fit_var.clear();

}

void Convolution_Tool::GetVectorChiSq_before_fit(std::vector<double> &inputVector){
inputVector= ChiSq_before_fit;
}
void Convolution_Tool::GetVectorChiSqVars_before_fit(std::vector<double> &inputVector){
inputVector= ChiSq_before_fit_var;
}


void Convolution_Tool::GetVectorChiSq_after_fit(std::vector<double> &inputVector){
inputVector= ChiSq_after_fit;
}

void Convolution_Tool::GetVectorChiSqVars_after_fit(std::vector<double> &inputVector){
inputVector= ChiSq_after_fit_var;
}
