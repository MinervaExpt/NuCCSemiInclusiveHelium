//File: MasterAnaCVUniverse.cxx
//Brief: ME MasterAnaCVUniverse for the Helium Analysis selection of CH
//Author: Christian Nguyen christian2nguyen@ufl.edu

#include "HeliumCVUniverse.h"
#include "PlotUtils/PhysicsVariables.h"



double MeVGeV = 0.001; // lazy conversion from MeV to GeV before filling histos
bool m_useNeutronCVReweight = true;

const double Mev_to_GeV=.001;
const double True_Start_Znode = 4292.96; // mm
const double FirstPlaneZPostion = 4337.25; // mm


 //constants
   const double PI = atan(1.0)*4;
   const double deg_to_rad = PI / 180.0;
   const double rad_to_deg = 1. / deg_to_rad;
   const double mev_to_gev = .001;
   const double avagadro   = 6.0221415E23;
   // MINOS Cuts
    const double MIN_MINOS_CURVE = 5.0;
    const int MIN_MINOS_PLANE   = 100;
  //  const double MAX_MINOS_CURVE = 0.0;
    const double MINOS_COIL_RADIUS = 210; //mm
    const double MAX_MINOS_RADIUS = 2500; //mm

    //same value because we assume negligable theta smearing
    const double MAX_THETA_MU = 20.0; //in deg // cut out events with muon theta wrt beam larger than this
    const double MAX_RECO_THETA_MU = 20.0; //in deg // cut out events with muon theta wrt beam larger than this

    const int FIRST_TRACKER_MOD = 27;
    const int LAST_TRACKER_MOD = 80;

    const int PROTON_PDG = 2212;
    const int NEUTRON_PDG = 2112;

    const double Z_scint = .5344;
    const double N_scint = .4656;
    const double Z_carbon = 6.;
    const double N_carbon = 6.;
    const double Z_iron = 26.;
    const double N_iron = 30.;
    const double Z_lead = 82.;
    const double N_lead = 125.;

    const int TRACKER_Z = 99;
    const int TRACKER_Z_EVEN = 98;
    const int TRACKER_Z_ODD = 97;
    const int TRACKER_Z_C  = 91;
    const int TRACKER_Z_FE = 92;
    const int TRACKER_Z_PB = 93;

    const int DEUTERON_Z = 2;

     int m_analysis_neutrino_pdg = 14;
     double m_min_blob_zvtx = 4750.0;
     double m_photon_energy_cut = 10.0; // in MeV
     double m_proton_ke_cut = NSFDefaults::TrueProtonKECutCentral; // Default value

    //NuConfig MasterAnaCVUniverse::m_proton_score_config = Json::Value::null;
     std::vector<double> m_proton_score_Q2QEs = { 0.2, 0.6 };
     std::vector<double> m_proton_score_mins = { 0.2, 0.1, 0.0 };


     bool _is_analysis_neutrino_pdg_set = false;
     bool _is_min_blob_zvtx_set = false;
     bool _is_photon_energy_cut_set = false;
     bool _is_proton_ke_cut_set = false;
     bool _is_proton_score_config_set = false;



///////////////// Defaults and Declarations /////////////////


//const double Mev_to_GeV=.001;
//const double True_Start_Znode = 4292.96; // mm
//const double FirstPlaneZPostion = 4337.25; // mm
using namespace HelicityType;
//CTOR




bool HeliumCVUniverse::isMINOSMatch_bool() const{ return GetBool("isMinosMatchTrack");}
bool HeliumCVUniverse::IsMinosMatchMuon() const { return GetInt("muon_is_minos_match_track") == -1; }

double HeliumCVUniverse::GetCurvatureSignificance_AnaDev() const{return GetDouble("MasterAnaDev_minos_trk_p_curvature");}
///////////////////////////////////////////////////


CH_Signal_type HeliumCVUniverse::return_CH_Sigal_type(Particle_type Particle_type) const {

  if( 1 != GetInt("mc_current")){ return kBG_NC;}
  else if (GetInt("mc_incoming") == -14){return kBG_CCwrongsign;}
  else if(Particle_type == kParticle_neutral || Particle_type == kPion_0_Electron_kGamma){return kBG_Neutral_secTrk; }
  else {return kSignal;}

}


///////////////////////////////////////////////////

///////////////////////////////////////////////////

// Get Branches and Calculate Quantities for the universe/event
// Get RECO Branches (always MeV, radians)
//double HeliumCVUniverse::GetDummyVar()  const { return -999.; }
double HeliumCVUniverse::GetVxtX() const { return GetVecElem("vtx",0); }
double HeliumCVUniverse::GetVxtY() const { return GetVecElem("vtx",1); }
double HeliumCVUniverse::GetVxtZ() const { return GetVecElem("vtx",2); }

/*
 bool HeliumCVUniverse::IsinTracker()const {

double Xvertex = HeliumCVUniverse::GetVxtX();
double Yvertex = HeliumCVUniverse::GetVxtY();
double Zvertex = HeliumCVUniverse::GetVxtZ();

return InTracker(Xvertex,Yvertex,Zvertex);

 };
*/

//double HeliumCVUniverse::GetMuonPT() const //GeV/c
// {
//   return GetPmu()/1000. * sin(GetThetamu());
// }
//
// double HeliumCVUniverse::GetMuonPz() const //GeV/c
// {
//   return GetPmu()/1000. * cos(GetThetamu());
// }
//
// double HeliumCVUniverse::GetMuonPTTrue() const //GeV/c
// {
//   return GetPlepTrue()/1000. * sin(GetThetalepTrue());
// }
//
// double HeliumCVUniverse::GetMuonPzTrue() const //GeV/c
// {
//   return GetPlepTrue()/1000. * cos(GetThetalepTrue());
// }
//



//int HeliumCVUniverse::GetDeadTime() const {
//return GetInt("phys_n_dead_discr_pair_upstream_prim_track_proj");
//}


bool  HeliumCVUniverse::GetDeadTimeCut() const{
if( 1 < GetDeadTime()) {return false;}
else {return true; }
}

int HeliumCVUniverse::GetNTracks() const{return GetInt("multiplicity");}

bool HeliumCVUniverse::Atleast2tracks()const {
if(GetNTracks()>=2)return true;
else return false;
}


/////////////////////////////////
bool HeliumCVUniverse::PassHelicityCut(HelicityType::t_HelicityType h )const
{

   int helicity = GetInt("MasterAnaDev_nuHelicity");
   if(h==0) return true;
   else
     return HelicityType::t_HelicityType(helicity) == h;
}




bool HeliumCVUniverse::PassMuCurveCut( HelicityType::t_HelicityType h  )const
{
    //! If measured by curvature, make a cut on the significance.
    double input = GetDouble("MasterAnaDev_minos_trk_eqp_qp");
    double Curve = (1.0 / input);
    if (h==HelicityType::kNeutrino){
      if( Curve <= -5 ){return true;}
      else{return false;}
    }

    if (h==HelicityType::kAntiNeutrino){
      if( Curve <= 5 ){return true;}
      else{return false;}
    }
}


bool HeliumCVUniverse::PassMuCurveCut()const{

    //Don't make a significance cut if we reconstructed by range
    if(GetDouble("MasterAnaDev_minos_used_curvature") != 1)
        return true;
    return PassMuCurveCut(HelicityType::kNeutrino);

}

bool HeliumCVUniverse::PassMuCoilCut( )const
{

    const double coilXPos = 1219.0;
    const double coilYPos = 393.0;
    const double minos_x = GetDouble("MasterAnaDev_minos_trk_end_x") + coilXPos;
    const double minos_y = GetDouble("MasterAnaDev_minos_trk_end_y") + coilYPos;
    double minosR = sqrt(pow(minos_x,2) + pow(minos_y,2) );
    /*if( !((pow(minos_x,2) + pow(minos_y,2) )>= pow(coilR, 2)) )
     cout << minos_x << " " << minos_y << " " << coilR << endl;
     */

     if(minosR > MINOS_COIL_RADIUS && minosR < MAX_MINOS_RADIUS ){return true; }
     else {return false;}

}



bool HeliumCVUniverse::PassReco( HelicityType::t_HelicityType h)const
{
    if( ! PassHelicityCut(h) )   return false; //! Is this event the right helicity?
//    if( ! cv->GetInt("MasterAnaDev_in_fiducial_area") ) return false; //! Is the event in the fiducial area?
//    if( ! PassZDistCut( cv) )   return false; //! Is the event vertex close enough in Z to the NuclearTarget?
//    if( ! PassDistToDivisionCut(cv) ) return false; //! Is the event vertex far enough away from the separation of target sections?
//    if( 120. < cv->GetEnu() * mev_to_gev ) return false; //! Anne's neutrino Energy cut
    if( 1 < GetInt("phys_n_dead_discr_pair_upstream_prim_track_proj") ) return false; //! Gabe's tdead cut
    if( ! PassMuCurveCut(h) ) return false; //! Is the curvature significant?
    if( ! PassMuCoilCut() ) return false; //! Does the muon track end outside of the coil, or inside the area of MINOS which gives us good energy reco?
    // if( !IsGoodTarget3Event( ) ) return false; //! Is this a target 3 event which clearly originated in target 1 or 2?
    return true;
}
bool HeliumCVUniverse::TrackerOnly()const
{ // Using Jefferey cut values
    if (GetVecElem("MasterAnaDev_vtx",2) >= 5890 && GetVecElem("MasterAnaDev_vtx",2) <= 8467)
        return true;
    else
        return false;
} // added July 6/21
//5890.0, 8467.0
bool HeliumCVUniverse::TrackerOnlyTrue()const
{
    if (GetVecElem("mc_vtx",2) >= 5890 && GetVecElem("mc_vtx",2) <= 8467) // old 8422
        return true;
    else
        return false;
} // added July 6/21

 FluxSlices HeliumCVUniverse::GetRECORegionSliceMasterAna()const{
 return  returnRegionSliceType(GetVecElem("MasterAnaDev_vtx",0), GetVecElem("MasterAnaDev_vtx",1)); };
 FluxSlices HeliumCVUniverse::GetTRUERegionSliceMasterAna()const{
 return  returnRegionSliceType(GetVecElem("mc_vtx",0), GetVecElem("mc_vtx",1)); };

 FluxSlices HeliumCVUniverse::GetTRUERegion12DAISY_MasterAna()const{
 return  returnHeliumdaisyType_inputYX(GetVecElem("mc_vtx",0),  GetVecElem("mc_vtx",1)); };

 FluxSlices HeliumCVUniverse::GetRECORegion12DAISY_MasterAna()const{
 return  returnHeliumdaisyType_inputYX(GetVecElem("MasterAnaDev_vtx",0),  GetVecElem("MasterAnaDev_vtx",1)); };


bool HeliumCVUniverse::InHexagon( double apothem /*= 850.*/ )const {
  bool useDNN = false;
    //vector<double> newVertex = GetMLVertex();
   double x, y;
   if (useDNN){
    x = GetVecElem("ANN_vtx",0);
    y = GetVecElem("ANN_vtx",1);
   }
   else {
    x = GetVecElem("MasterAnaDev_vtx",0);
    y = GetVecElem("MasterAnaDev_vtx",1);
   }
    if( pow(x,2) + pow(y,2) < pow(apothem,2) )
        return true;

    //Hexagon is symmetric about its x and y
    x = fabs(x);
    y = fabs(y);

    double lenOfSide = apothem * ( 2 / sqrt(3) );

    if( x > apothem )
        return false;

    if( y < lenOfSide/2.0 )
        return true;

    double slope = (lenOfSide / 2.0) / apothem;
    if( y < lenOfSide - x*slope )
        return true;

    return false;
}
bool HeliumCVUniverse::InHexagonTrue(double apothem /*= 850.*/ )const{

    //vector<double> newVertex = GetMLVertex();
    double x = GetVecElem("mc_vtx",0);
    double y = GetVecElem("mc_vtx",1);

    if( pow(x,2) + pow(y,2) < pow(apothem,2) )
        return true;

    //Hexagon is symmetric about its x and y
    x = fabs(x);
    y = fabs(y);

    double lenOfSide = apothem * ( 2 / sqrt(3) );

    if( x > apothem )
        return false;

    if( y < lenOfSide/2.0 )
        return true;

    double slope = (lenOfSide / 2.0) / apothem;
    if( y < lenOfSide - x*slope )
        return true;

    return false;
}




bool HeliumCVUniverse::PassThetaCut_heliumlike(double angle)const
{
   if( 0.0 < angle && angle < 12.0 ){return true;}
   else{return false;}
}
// HeliumCVUniverse_cxx


	// ===========================================================
	// ====================== Configurables ======================
	// ===========================================================

	///////////////// Defaults and Declarations /////////////////
	//int HeliumCVUniverse::m_analysis_neutrino_pdg = -14;
	//double HeliumCVUniverse::m_min_blob_zvtx = 4750.0;
	//double HeliumCVUniverse::m_photon_energy_cut = 10.0; // in MeV
	//double HeliumCVUniverse::m_proton_ke_cut = NSFDefaults::TrueProtonKECutCentral; // Default value

	////NuConfig HeliumCVUniverse::m_proton_score_config = Json::Value::null;
	//std::vector<double> HeliumCVUniverse::m_proton_score_Q2QEs = { 0.2, 0.6 };
	//std::vector<double> HeliumCVUniverse::m_proton_score_mins = { 0.2, 0.1, 0.0 };
	/*
	The vectors
		m_proton_score_Q2QEs
		m_proton_score_mins
	come from m_proton_score_config through SetProtonScoreConfig().

	Substituting
		q2qe   = m_proton_score_Q2QEs
		pscore = m_proton_score_mins
	these vectors are interpreted to mean...
		 ____________________________________________________________
		|                             |                             |
		|  for...                     |  proton if...               |
		|_____________________________|_____________________________|
		|                             |                             |
		|            Q2QE <= q2qe[0]  |  proton score >= pscore[0]  |
		|  q2qe[0] < Q2QE <= q2qe[1]  |  proton score >= pscore[1]  |
		|  q2qe[1] < Q2QE             |  proton score >= pscore[2]  |
		|_____________________________|_____________________________|

	Valid proton score configuration inputs are of the form:

		"ProtonScoreConfig": {
			"band1":{ "Q2QE_max":0.2, "pass_proton_score_min":0.2 },
			"band2":{ "Q2QE_range":[0.2,0.6], "pass_proton_score_min":0.1 },
			"band3":{ "Q2QE_min":0.6, "pass_proton_score_min":0.0 }
		},

		which means
		 ______________________________________________
		|                     |                       |
		|  for...             |  proton if...         |
		|_____________________|_______________________|
		|                     |                       |
		|        Q2QE <= 0.2  |  proton score >= 0.2  |
		|  0.2 < Q2QE <= 0.6  |  proton score >= 0.1  |
		|  0.6 < Q2QE         |  proton score >= 0.0  |
		|_____________________|_______________________|

		In terms of q2qe and pscore this would be:

		"ProtonScoreConfig": {
			"band1":{ "Q2QE_max":q2qe[0], "pass_proton_score_min":pscore[0] },
			"band2":{ "Q2QE_range":[q2qe[0],q2qe[1]], "pass_proton_score_min":pscore[1] },
			"band3":{ "Q2QE_min":q2qe[1], "pass_proton_score_min":pscore[2] }
		},

	-OR-

		"ProtonScoreConfig": { "pass_proton_score_min":0.15 },

		which means for
		 ________________________________________________
		|                      |                        |
		|  for...              |  proton if...          |
		|______________________|________________________|
		|                      |                        |
		|  all values of Q2QE  |  proton score >= 0.15  |
		|______________________|________________________|

		In terms of q2qe and pscore this would be:

		"ProtonScoreConfig": { "pass_proton_score_min":pscore[0] },

	*/

	//bool HeliumCVUniverse::_is_analysis_neutrino_pdg_set = false;
	//bool HeliumCVUniverse::_is_min_blob_zvtx_set = false;
	//bool HeliumCVUniverse::_is_photon_energy_cut_set = false;
	//bool HeliumCVUniverse::_is_proton_ke_cut_set = false;
	//bool HeliumCVUniverse::_is_proton_score_config_set = false;

	///////////////// Incoming Neutrino PDG /////////////////
	int HeliumCVUniverse::GetAnalysisNeutrinoPDG() { return m_analysis_neutrino_pdg; }
	bool HeliumCVUniverse::SetAnalysisNeutrinoPDG( int neutrino_pdg, bool print ) {
		if( _is_analysis_neutrino_pdg_set ) {
			std::cout << "WARNING: YOU ATTEMPTED TO SET PHOTON ENERGY CUT A SECOND TIME. "
			          << "THIS IS NOT ALLOWED FOR CONSISTENCY." << std::endl;
			return 0;
		} else {
			m_analysis_neutrino_pdg = neutrino_pdg;
			_is_analysis_neutrino_pdg_set = true;
			if( print ) std::cout << "Analysis neutrino PDG set to " << m_analysis_neutrino_pdg << std::endl;
			return 1;
		}
	}

	///////////////// Blob minimum Z vertex in order to be counted /////////////////
	double HeliumCVUniverse::GetMinBlobZVtx() { return m_min_blob_zvtx; }
	bool HeliumCVUniverse::SetMinBlobZVtx( double min_zvtx, bool print ) {
		if( _is_min_blob_zvtx_set ) {
			std::cout << "WARNING: YOU ATTEMPTED TO SET MIN BLOB ZVTX A SECOND TIME. "
			          << "THIS IS NOT ALLOWED FOR CONSISTENCY." << std::endl;
			return 0;
		} else {
			m_min_blob_zvtx = min_zvtx;
			_is_min_blob_zvtx_set = true;
			if( print ) std::cout << "Minimum blob Z vertex cutoff set to " << m_min_blob_zvtx << std::endl;
			return 1;
		}
	}

	///////////////// Photon Energy Cut /////////////////
	double HeliumCVUniverse::GetPhotonEnergyCut() { return m_photon_energy_cut; }
	bool HeliumCVUniverse::SetPhotonEnergyCut( double energy, bool print ) {
		if( _is_photon_energy_cut_set ) {
			std::cout << "WARNING: YOU ATTEMPTED TO SET PHOTON ENERGY CUT A SECOND TIME. "
			          << "THIS IS NOT ALLOWED FOR CONSISTENCY." << std::endl;
			return 0;
		} else {
			m_photon_energy_cut = energy;
			_is_photon_energy_cut_set = true;
			if( print ) std::cout << "Photon low energy cutoff set to " << m_photon_energy_cut << " MeV" << std::endl;
			return 1;
		}
	}

	///////////////// Proton KE Cut setting /////////////////
	double HeliumCVUniverse::GetProtonKECut() { return m_proton_ke_cut; }
	bool HeliumCVUniverse::SetProtonKECut( double proton_KECut, bool print ) {
		if( _is_proton_ke_cut_set ) {
			std::cout << "WARNING: YOU ATTEMPTED TO SET PROTON KE CUT A SECOND TIME. "
			          << "THIS IS NOT ALLOWED FOR CONSISTENCY." << std::endl;
			return 0;
		} else {
			m_proton_ke_cut = proton_KECut;
			_is_proton_ke_cut_set = true;
			if( print ) std::cout << "ProtonKECut set to " << m_proton_ke_cut << " MeV" << std::endl;
			return 1;
		}
	}

	///////////////// Proton Score configuration /////////////////
/*
	NuConfig HeliumCVUniverse::GetProtonScoreConfig(bool print = false) {
		if(!_is_proton_score_config_set) { // Uses default configuration, which produces default m_proton_score_* values
			std::cout << "\nUSING DEFAULT PROTON SCORE CONFIGURATION.\n\n";
			m_proton_score_config.ReadFromString(R"({"band1":{"Q2QE_max":0.2,"pass_proton_score_min":0.2},"band2":{"Q2QE_range":[0.2,0.6],"pass_proton_score_min":0.1},"band3":{"Q2QE_min":0.6,"pass_proton_score_min":0.0}})");
			if( print ) m_proton_score_config.Print();
		}
		else {
			std::cout << "\nUsing proton score configuration provided by user configuration file.\n\n";
			if( print ) m_proton_score_config.Print();
		}
		return m_proton_score_config;
	}
	bool HeliumCVUniverse::SetProtonScoreConfig(NuConfig protonScoreConfig, bool print ) {
		if( _is_proton_score_config_set ) {
			std::cout << "WARNING: YOU ATTEMPTED TO SET PROTON SCORE CONFIGURATION A SECOND TIME. "
			          << "THIS IS NOT ALLOWED FOR CONSISTENCY." << std::endl;
			return 0;
		} else {
			m_proton_score_config = protonScoreConfig;
			if( print ) m_proton_score_config.Print();
			if( m_proton_score_config.GetKeys().size() == 1) {
				// Passing proton score value same for all values of Q2QE
				m_proton_score_mins = {};
				m_proton_score_Q2QEs = {};
				m_proton_score_mins.push_back(m_proton_score_config.GetDouble("pass_proton_score_min"));
			}
			else { // There are Q2QE values that dictate passing proton score values
				m_proton_score_mins = {};
				m_proton_score_Q2QEs = {};
				for ( auto band:m_proton_score_config.GetKeys() ) {
					NuConfig bandConfig = m_proton_score_config.GetConfig(band);
					m_proton_score_mins.push_back(bandConfig.GetDouble("pass_proton_score_min"));
					if( bandConfig.IsMember("Q2QE_max") ) {
						m_proton_score_Q2QEs.push_back(bandConfig.GetDouble("Q2QE_max"));
					}
					else if( bandConfig.IsMember("Q2QE_range") ) {
						m_proton_score_Q2QEs.push_back(bandConfig.GetDoubleVector("Q2QE_range")[1]);
					}
				}
			}
			_is_proton_score_config_set = true;
			return 1;
		}
	}
*/
	// ========================================================================
	// ============================== Get Weight ==============================
	// ========================================================================



	// ========================================================================
	// Write a "Get" function for all quantities access by your analysis.
	// For composite quantities (e.g. Enu) use a calculator function.
	//
	// Currently PlotUtils::MinervaUniverse may already define some functions
	// that you want. The future of these functions is uncertain. You might want
	// to write all your own functions for now.
	// ========================================================================

	double HeliumCVUniverse::GetEventID() const { return GetDouble("eventID"); }
	int HeliumCVUniverse::GetMultiplicity() const { return GetInt("multiplicity"); }
	int HeliumCVUniverse::GetDeadTime() const { return GetInt("phys_n_dead_discr_pair_upstream_prim_track_proj"); }

	// ----------------------- Analysis-related Variables ------------------------

	int HeliumCVUniverse::GetIsMinosMatchTrack() const { return GetInt("muon_is_minos_match_track"); }
	double HeliumCVUniverse::GetEnuHadGeV() const { return HeliumCVUniverse::GetEmuGeV()+HeliumCVUniverse::GetHadronEGeV(); } // GetEnuGeV()?
	double HeliumCVUniverse::GetTrueEnuGeV() const { return GetDouble("mc_incomingE")*MeVGeV; }

	double HeliumCVUniverse::GetEnuCCQEGeV() const {
		int charge = GetAnalysisNuPDG() > 0? 1:-1;
		//std::cout << " before try" << GetEmu() <<  std::endl;
		double val = PlotUtils::nuEnergyCCQE( GetEmu(), GetPmu(), GetThetamu(), charge ); // un-PlotUtil's this?
		//std::cout << " try to getEnuCCQE" << val << std::endl;
		return val*MeVGeV;
	} // both neutrino and antinu

	double HeliumCVUniverse::GetTrueEnuCCQEGeV() const {
		int charge = GetAnalysisNuPDG() > 0? 1:-1;
		//std::cout << " before try" << GetEmu() <<  std::endl;
		double val = PlotUtils::nuEnergyCCQE( GetElepTrue(), GetPlepTrue(), GetThetalepTrue(), charge ); // un-PlotUtil's this?
		//std::cout << " try to getEnuCCQE" << val << std::endl;
		return val*MeVGeV;
	} // may be a better way to implement this

	double HeliumCVUniverse::GetQ2QEGeV() const {
		const double q2min = 0.001;
		int charge = GetAnalysisNuPDG() > 0? 1:-1;
		if(HeliumCVUniverse::GetEnuCCQEGeV()<=0.0)return 0.0;
		//std::cout<<"HeliumCVUniverse::GetQ2QE Cannot calculate neutrino energy "<<std::endl;
		else{
			// Q2 = 2.0*GetEnuCCQE() * ( GetEmu() - GetPmu() * cos( GetThetamu() ) ) - pow( MinervaUnits::M_mu, 2 );
			double q2 = PlotUtils::qSquaredCCQE( GetEmu(), GetPmu(), GetThetamu(), charge )*MeVGeV*MeVGeV;
			//  if(q2 < q2min)q2 =  q2min;
			return q2;
		}
		// return Q2;
	}

	double HeliumCVUniverse::GetTrueQ2QEGeV() const {
		const double q2min = 0.001;
		int charge = GetAnalysisNuPDG() > 0? 1:-1;
		double q2 = PlotUtils::qSquaredCCQE( GetElepTrue(), GetPlepTrue(), GetThetalepTrue(), charge )*MeVGeV*MeVGeV;
		// if(q2 < q2min)q2 =  q2min;
		return q2;
	}

	double HeliumCVUniverse::GetLog10Q2QEGeV() const { return std::log10( HeliumCVUniverse::GetQ2QEGeV() ); }
	double HeliumCVUniverse::GetTrueLog10Q2QEGeV() const { return std::log10( GetTrueQ2QEGeV() ); }

/*
  double HeliumCVUniverse::GetExpWTrue_AnaDev() const {
     double mnucleon = GetTrgNucleonMass();  //GetTrgNucleonMass();assuming interaction is neutrino so mass would be neutrino
     double W = pow(mnucleon, 2) - GetQ2Exp_AnaDev() + 2*(mnucleon)*GetEhadTrue();
     W = W > 0 ? sqrt(W) : -1.0;

     return W/1000; // GeV
  }
*/


	// ------------------------------ Muon Variables -----------------------------

	double HeliumCVUniverse::GetEmuGeV() const { return std::sqrt(GetPmu()*GetPmu() + pow( MinervaUnits::M_mu, 2 ))*MeVGeV; }
  bool HeliumCVUniverse::IsEmUGoodEnergy_AnaDev() const {
    double Emu =  GetEmuGeV();
    if(Emu > 2.0 && Emu < 50.0 )return true;
    else {return false;}
  }
	double HeliumCVUniverse::GetTrueEmuGeV() const { return GetElepTrue()*MeVGeV; } // not sure if this is right
	double HeliumCVUniverse::GetPmuGeV() const { return GetPmu()*MeVGeV;	}
	double HeliumCVUniverse::GetTruePmuGeV() const { return GetPlepTrue()*MeVGeV; }
  double HeliumCVUniverse::GetTRUE_EmuGeVNew() const { return std::sqrt(GetPlepTrue()*GetPlepTrue() + pow( MinervaUnits::M_mu, 2 ))*MeVGeV; }
  bool HeliumCVUniverse::isEmuGood_TRUE()const {
    double Energy = GetTRUE_EmuGeVNew();
    if ( 2.0 < Energy && Energy < 50.0){return true;}
    else{return false; }
  }

  double HeliumCVUniverse::GetPparMuGeV() const { return GetPmuGeV()*std::cos( GetThetamu() ); }
	double HeliumCVUniverse::GetTruePparMuGeV() const { return GetTruePmuGeV()*std::cos( GetTrueThetamu() ); }
	double HeliumCVUniverse::GetPperpMuGeV() const { return GetPmuGeV()*std::sin( GetThetamu() ); }
	double HeliumCVUniverse::GetTruePperpMuGeV() const { return GetTruePmuGeV()*std::sin( GetTrueThetamu() ); }

	double HeliumCVUniverse::GetTrueThetaXmu() const {
		TVector3 p3lep( GetVecElem("mc_primFSLepton",0), GetVecElem("mc_primFSLepton",1), GetVecElem("mc_primFSLepton",2) );
		p3lep.RotateX(MinervaUnits::numi_beam_angle_rad);
		double px =  p3lep[0];
		double pz =  p3lep[2];
		//std::cout << "tx " << px << " " << pz << std::endl;
		return std::atan2(px,pz);
	}
	double HeliumCVUniverse::GetTrueThetaYmu() const {
		TVector3 p3lep( GetVecElem("mc_primFSLepton",0), GetVecElem("mc_primFSLepton",1), GetVecElem("mc_primFSLepton",2) );
		p3lep.RotateX(MinervaUnits::numi_beam_angle_rad);
		double py =  p3lep[1];
		double pz =  p3lep[2];
		//std::cout << "tx " << px << " " << pz << std::endl;
		return std::atan2(py,pz);
	}

	double HeliumCVUniverse::GetTrueThetamu() const { return GetThetalepTrue(); }
	double HeliumCVUniverse::GetThetamuDegrees() const { return GetThetamu()*180/M_PI; }
	double HeliumCVUniverse::GetTrueThetamuDegrees() const { return GetThetalepTrue()*180/M_PI; }
  bool HeliumCVUniverse::IsTRUEMuonAngle_HeliumGood(double angle) const {
    double MuonAngle = GetTrueThetamuDegrees();
    if(0.0 < MuonAngle && MuonAngle < angle ){return true;}
    else{return false;}
  }

	// ----------------------------- Proton Variables ----------------------------

	double HeliumCVUniverse::GetHadronEGeV() const { return (GetCalRecoilEnergyGeV() + GetNonCalRecoilEnergyGeV()); }

	// ----------------------------- Recoil Variables ----------------------------


	double HeliumCVUniverse::GetCalRecoilEnergy_AnaDev() const {
		bool neutrinoMode = GetAnalysisNuPDG() > 0;
		if(neutrinoMode) return (GetDouble("nonvtx_iso_blobs_energy")+GetDouble("dis_id_energy")); // several definitions of this, be careful
		else {
			//if(GetVecDouble("recoil_summed_energy").size()==0) return -999.; // protect against bad input,
			//return (GetVecDouble("recoil_summed_energy")[0] - GetDouble("recoil_energy_nonmuon_vtx100mm"));
			return GetDouble("recoil_energy_nonmuon_nonvtx100mm");
		}
	}

	double HeliumCVUniverse::GetCalRecoilEnergyGeV() const { return HeliumCVUniverse::GetCalRecoilEnergy_AnaDev()*MeVGeV; }
	double HeliumCVUniverse::GetNonCalRecoilEnergy() const { return 0; } // not certain why I want to implement this but there ya go.
	double HeliumCVUniverse::GetNonCalRecoilEnergyGeV() const { return GetNonCalRecoilEnergy()*MeVGeV; }
	double HeliumCVUniverse::GetRecoilEnergyGeV() const { return GetRecoilEnergy()*MeVGeV; } // GetCalRecoilEnergy()?
	double HeliumCVUniverse::GetTrueRecoilEnergyGeV() const { return HeliumCVUniverse::GetTrueQ0GeV(); } // need this?
	double HeliumCVUniverse::GetTrueLog10RecoilEnergyGeV() const { return std::log10(HeliumCVUniverse::GetTrueQ0GeV()); } // need this?
	double HeliumCVUniverse::GetLog10RecoilEnergyGeV() const { return std::log10(GetRecoilEnergy())-3.; }
		// return HeliumCVUniverse::GetCalRecoilEnergy();
		// std::cout << GetRecoilEnergy()*MeVGeV <<  " " << std::log10(GetRecoilEnergy()) << std::log10(GetRecoilEnergy())  - 3. << std::endl;

	double HeliumCVUniverse::GetTrueQ0GeV() const {
		static std::vector<double> mc_incomingPartVec;
		static std::vector<double> mc_primFSLepton;
		mc_incomingPartVec = GetVecDouble("mc_incomingPartVec");
		mc_primFSLepton = GetVecDouble("mc_primFSLepton");
		double q0 = mc_incomingPartVec[3] - mc_primFSLepton[3];
	return q0*MeVGeV;
	}
	double HeliumCVUniverse::GetTrueQ3GeV() const {
		static std::vector<double> mc_incomingPartVec;
		static std::vector<double> mc_primFSLepton;
		mc_incomingPartVec = GetVecDouble("mc_incomingPartVec");
		mc_primFSLepton = GetVecDouble("mc_primFSLepton");
		double px = mc_primFSLepton[0] - mc_incomingPartVec[0];
		double py = mc_primFSLepton[1] - mc_incomingPartVec[1];
		double pz = mc_primFSLepton[2] - mc_incomingPartVec[2];
		double q3 = std::sqrt( px*px + py*py + pz*pz );
		return q3*MeVGeV;
	}
	double HeliumCVUniverse::GetTrueQ2GeV() const {
		double q3 = HeliumCVUniverse::GetTrueQ3GeV();
		double q0 = HeliumCVUniverse::GetTrueQ0GeV();
		return q3*q3 - q0*q0;
	}


	// ----------------------------- Other Variables -----------------------------

	//  virtual double GetWgenie() const { return GetDouble("mc_w"); }
	int HeliumCVUniverse::GetMCIntType() const { return GetInt("mc_intType"); }
	int HeliumCVUniverse::GetTruthNuPDG() const { return GetInt("mc_incoming"); }
	int HeliumCVUniverse::GetCurrent() const { return GetInt("mc_current"); }

	double HeliumCVUniverse::GetTpiGeV( const int hadron ) const {
		double TLA = GetVecElem("hadron_track_length_area", hadron);
		return (2.3112 * TLA + 37.03)*MeVGeV; // what are these numbers
	}


	// --------------------- Quantities only needed for cuts ---------------------
	// Although unlikely, in principle these quanties could be shifted by a
	// systematic. And when they are, they'll only be shifted correctly if we
	// write these accessor functions.
	//bool HeliumCVUniverse::IsMinosMatchMuon() const { return GetInt("muon_is_minos_match_track") == -1; }
		// does this flip for neutrino?
		// This isn't even used anymore, there's something else. This is left over from Amit's analysis

	int HeliumCVUniverse::GetNuHelicity() const {
		return GetInt(std::string(MinervaUniverse::GetTreeName()+"_nuHelicity").c_str());
	}
	double HeliumCVUniverse::GetCurvature() const {
		return GetDouble(std::string(MinervaUniverse::GetTreeName()+"_minos_trk_qp").c_str());
	}

	double HeliumCVUniverse::GetTrueCurvature() const { return 0.0; }
	int HeliumCVUniverse::GetTDead() const { return GetInt("tdead"); }
		// Dead electronics, a rock muon removal technique. Amit's analysis doesn't have
		// that cut most likely. Not even in that tuple, only reason it survives is bc it's
		// not called anymore. Can't find it? Just a hard coded constant in CCQENuCutsNSF.h

	// These cuts are already made in the CCQENu AnaTuple, may be unnecessary
	ROOT::Math::XYZTVector HeliumCVUniverse::GetVertex() const {
		ROOT::Math::XYZTVector result;
		result.SetCoordinates(GetVec<double>("vtx").data());
		return result;
	}

	// 1-d apothems for cuts

	double HeliumCVUniverse::GetApothemY() const {  // this should be less than apothem cut
		const double fSlope = 1./sqrt(3.);
		std::vector<double> vertex = GetVec<double>("vtx");
		return (fabs(vertex[1]) + fSlope*fabs(vertex[0]))*sqrt(3.)/2.;
	}

	double HeliumCVUniverse::GetApothemX() const {  // this should be less than apothem cut
		std::vector<double> vertex = GetVec<double>("vtx");
		return fabs(vertex[0]);
	}

	double HeliumCVUniverse::GetTrueApothemY() const {  // this should be less than apothem cut
		const double fSlope = 1./sqrt(3.);
		std::vector<double> vertex = GetVec<double>("mc_vtx");
		return (fabs(vertex[1]) + fSlope*fabs(vertex[0]))*sqrt(3.)/2.;
	}

	double HeliumCVUniverse::GetTrueApothemX() const {  // this should be less than apothem cut
		std::vector<double> vertex = GetVec<double>("mc_vtx");
		return fabs(vertex[0]);
	}

	double HeliumCVUniverse::GetZVertex() const {
		std::vector<double> tmp = GetVec<double>("vtx");
		return tmp[2];
	}

	ROOT::Math::XYZTVector HeliumCVUniverse::GetTrueVertex() const {
		ROOT::Math::XYZTVector result;
		result.SetCoordinates(GetVec<double>("mc_vtx").data());
		return result;
	}

	double HeliumCVUniverse::GetTrueZVertex() const {
		std::vector<double> tmp = GetVec<double>("mc_vtx");
		return tmp[2];
	}


	// Some stuff Heidi added to test out some issues with the NTuples

	int HeliumCVUniverse::GetRun() const { return GetInt("ev_run"); }
	int HeliumCVUniverse::GetSubRun() const { return GetInt("ev_subrun"); }
	int HeliumCVUniverse::GetGate() const { return GetInt("ev_gate"); }
	int HeliumCVUniverse::GetTrueRun() const { return GetInt("mc_run"); }
	int HeliumCVUniverse::GetTrueSubRun() const { return GetInt("mc_subrun"); }
	int HeliumCVUniverse::GetTrueGate() const { return GetInt("mc_nthEvtInFile")+1; } // not certain if this is stored

	// --------------------- put cut functions here ---------------------------------

	int HeliumCVUniverse::GetGoodRecoil() const { // implement Cheryl's cut
		double Q2 = HeliumCVUniverse::GetQ2QEGeV();
		double recoil = HeliumCVUniverse::GetRecoilEnergyGeV();
		double offset=0.05;
		if( Q2 < 0.175 ) return ( recoil <= 0.08+offset);
		else if( Q2 < 1.4 )return (recoil <= 0.03 + 0.3*Q2+offset);
		else return (recoil <= 0.45+offset); //antinu
	}

	int HeliumCVUniverse::GetTruthIsCC() const {
    if(HeliumCVUniverse::GetCurrent() == 1){return true; }
    else {return false;}

  }

	// helper function
	bool HeliumCVUniverse::passTrueCCQELike(bool neutrinoMode, std::vector<int> mc_FSPartPDG, std::vector<double> mc_FSPartE, int mc_nFSPart, double proton_KECut) const {
		int genie_n_muons = 0;
		int genie_n_antimuons = 0;
		double protonKECut = proton_KECut;
		for(int i = 0; i < mc_nFSPart; i++){
			int pdg =  mc_FSPartPDG[i];
			int abs_pdg = abs(pdg);
			double energy = mc_FSPartE[i];
			double KEp = energy - MinervaUnits::M_p;

			// implement 120 MeV KE cut, if needed
			// The photon energy cut is hard-coded at 10 MeV at present. We're happy to make it general, if the need arises !

			if(      abs_pdg ==  211 ||            // Charged Pions            Pions
			         pdg     ==  111   ) return 0; // Neutral Pions            Pions
			else if( abs_pdg == 3112 ||            // Sigma- and Sigma~+      Strange Baryons
				     	 abs_pdg == 3122 ||            // Lambda0 and Lambda~0    Strange Baryons
				     	 abs_pdg == 3212 ||            // Sigma0 and Sigma~0      Strange Baryons
				     	 abs_pdg == 3222   ) return 0; // Sigma+ and Sigma~-      Strange Baryons
			else if( energy > m_photon_energy_cut &&
			         pdg     ==   22   ) return 0; // Photons > Energy Cut
			else if( pdg     ==  130 ||            // KL0                     Strange Mesons
				     	 pdg     ==  310 ||            // KS0                     Strange Mesons
				     	 abs_pdg ==  311 ||            // K0 and K~0              Strange Mesons
				       abs_pdg ==  313 ||            // K*(892)0 and K*(892)~0  Strange Mesons
				    	 abs_pdg ==  321 ||            // K+ and K-               Strange Mesons
				       abs_pdg ==  323   ) return 0; // K*(892)+ and K*(892)-   Strange Mesons
			else if( abs_pdg == 4112 ||            // Sigma_c0 and Sigma_c~0   Charmed Baryons
				       abs_pdg == 4122 ||            // Lambda_c+ and Lambda_c~- Charmed Baryons
				       abs_pdg == 4212 ||            // Sigma_c+ and Sigma_c~-   Charmed Baryons
				       abs_pdg == 4222   ) return 0; // Sigma_c++ and Sigma_c~-- Charmed Baryons
			else if( abs_pdg ==  411 ||            // D+ and D-                Charned Mesons
				       abs_pdg ==  421   ) return 0; // D0 and D~0               Charmed Mesons
			else if( !neutrinoMode   &&
				       pdg     == 2212 &&
				       KEp  > protonKECut) return 0; // For antinus, no protons > cut-off KE
			else if( pdg     ==   13   ) genie_n_muons++;
			else if( pdg     ==  -13   ) genie_n_antimuons++;
			// Intermediate muon counts check
			if( genie_n_muons + genie_n_antimuons > 1 ) return 0;
		}
		/*
		bool passes = 1;
		if( neutrinoMode ) {
			for(int i = 0; i < mc_nFSPart; i++) {
				int pdg =  mc_FSPartPDG[i];
				double energy = mc_FSPartE[i];

				if( pdg == 13 ) { // muon
					genie_n_muons++;
					if( genie_n_muons > 1 ) return 0;
					else continue;
				}
				else if( pdg == 2112 ) continue; // neutrons allowed
				else if( pdg == 2212 ) continue; // protons allowed
				else if( pdg == 22 && energy <= m_photon_energy_cut ) continue; // low energy photons allowed
				else return 0; // not other pdgs allowed

			}
		}
		else {
			for(int i = 0; i < mc_nFSPart; i++) {
				int pdg =  mc_FSPartPDG[i];
				double energy = mc_FSPartE[i];
				double KEp = energy - MinervaUnits::M_p;

				if( pdg == -13 ) { // antimuon
					genie_n_muons++;
					if( genie_n_muons > 1 ) return 0; // Check muon count
					continue;
				}
				else if( pdg == 2112 ) continue; // neutron
				else if( pdg == 2212 && KEp <= protonKECut ) continue; // proton <= proton KE cut
				else if( pdg == 22 && energy <= m_photon_energy_cut ) continue; // low energy photons
				else return 0; // not other pdgs allowed
			}
		}
		*/
		if( ( neutrinoMode && genie_n_muons     == 0) ||
		    (!neutrinoMode && genie_n_antimuons == 0)   ) return 0;
		else return 1;
	}

	int HeliumCVUniverse::GetTruthIsCCQELike() const {  // cut hardwired for now
		std::vector<int>mc_FSPartPDG = GetVecInt("mc_FSPartPDG");
		std::vector<double>mc_FSPartE = GetVecDouble("mc_FSPartE");
		bool neutrinoMode = HeliumCVUniverse::GetTruthNuPDG() > 0;
		int mc_nFSPart = GetInt("mc_nFSPart");
		//int mc_incoming = GetInt("mc_incoming");
		bool passes = 0; // Assume not CCQELike, if CC check
		if(GetInt("mc_current") == 1 && GetInt("mc_incoming") == m_analysis_neutrino_pdg) {
			passes = ( HeliumCVUniverse::passTrueCCQELike(neutrinoMode, mc_FSPartPDG, mc_FSPartE, mc_nFSPart, m_proton_ke_cut));
		}


		return passes;
	}

	// all CCQElike without proton cut enabled

	int HeliumCVUniverse::GetTruthIsCCQELikeAll() const {  // cut hardwired for now
		std::vector<int>mc_FSPartPDG = GetVecInt("mc_FSPartPDG");
		std::vector<double>mc_FSPartE = GetVecDouble("mc_FSPartE");
		bool neutrinoMode = HeliumCVUniverse::GetTruthNuPDG() > 0;
		int mc_nFSPart = GetInt("mc_nFSPart");
		//int mc_incoming = GetInt("mc_incoming");
		//int mc_current = GetInt("mc_current");
		bool passes = ( HeliumCVUniverse::passTrueCCQELike(neutrinoMode, mc_FSPartPDG, mc_FSPartE, mc_nFSPart, 10000.));

		return passes;
	}

	int HeliumCVUniverse::GetTruthIsQELike() const {
		if(HeliumCVUniverse::GetTruthIsCCQELikeAll() == 1 &&
		   HeliumCVUniverse::GetTruthNuPDG() == m_analysis_neutrino_pdg &&
		   HeliumCVUniverse::GetCurrent() == 1 ) return 1;
		else return 0;
	}

	// ------------------------------------------------------------------------------
	// ----------------- Added by Sean for Neutrino ---------------------------------
	// ------------------------------------------------------------------------------

	// Interaction Vertex

	int HeliumCVUniverse::GetHasInteractionVertex() const { return GetInt("has_interaction_vertex"); }

	// Isolated Blobs and Charged Pions

	int HeliumCVUniverse::GetNBlobs() const {
		int n_blobs = 0;
		int kmax = GetInt("nonvtx_iso_blobs_start_position_z_in_prong_sz");
		std::vector<double> blob_z_starts = GetVecDouble("nonvtx_iso_blobs_start_position_z_in_prong");
		// counts blobs with zvertex greater than set value
		for(int k=0; k<kmax; ++k){
			if(blob_z_starts[k] > m_min_blob_zvtx) n_blobs++;
		}
		return n_blobs;
	}

	// One charged pion and charged pion count and CCQE except 1+ charged pions

	int HeliumCVUniverse::GetTruthHasSingleChargedPion() const {
		int genie_n_charged_pion = 0;
		std::vector<int> mc_FSPartPDG = GetVecInt("mc_FSPartPDG");
		std::vector<double> mc_FSPartE = GetVecDouble("mc_FSPartE");
		int mc_nFSPart = GetInt("mc_nFSPart");

		for(int i = 0; i < mc_nFSPart; i++){
			int pdg =  mc_FSPartPDG[i];

			if(      pdg             ==  111   ) return 0; // Neutral pions
			else if( abs(pdg)        ==  211   ) genie_n_charged_pion++;
			// Intermediate check of charged pion count
			if( genie_n_charged_pion >    1   ) return 0;
		}

		if( genie_n_charged_pion == 1 ) return 1;
		return 0; // i.e. if genie_n_charged_pion == 0
	}

	int HeliumCVUniverse::GetTrueChargedPionCount() const {
		int genie_n_charged_pion = 0;
		std::vector<int> mc_FSPartPDG = GetVecInt("mc_FSPartPDG");
		int mc_nFSPart = GetInt("mc_nFSPart");

		for(int i = 0; i < mc_nFSPart; i++){
			if( abs(mc_FSPartPDG[i]) == 211 ) genie_n_charged_pion++;
		}

		return genie_n_charged_pion;
	}

	int HeliumCVUniverse::GetTruthCCQELikeExceptForChargedPions() const {
		if( HeliumCVUniverse::GetTruthNuPDG() != m_analysis_neutrino_pdg ) return 0;
		if ( HeliumCVUniverse::GetCurrent() != 1 ) return 0;
		int genie_n_muons = 0;
		int genie_n_antimuons = 0;
		int genie_n_chargedpions = 0;
		double protonKECut = m_proton_ke_cut;
		bool neutrinoMode = 0;
		std::vector<int> mc_FSPartPDG = GetVecInt("mc_FSPartPDG");
		std::vector<double> mc_FSPartE = GetVecDouble("mc_FSPartE");
		int mc_nFSPart = GetInt("mc_nFSPart");

		if( m_analysis_neutrino_pdg > 0 ) neutrinoMode = 1;

		for(int i = 0; i < mc_nFSPart; i++){
			int pdg =  mc_FSPartPDG[i];
			int abs_pdg = abs(pdg);
			double energy = mc_FSPartE[i];
			double KEp = energy - MinervaUnits::M_p;

			// implement 120 MeV KE cut, if needed
			// The photon energy cut is hard-coded at 10 MeV at present. We're happy to make it general, if the need arises !

			if(      abs_pdg ==  211   ) genie_n_chargedpions++;
			else if( pdg     ==  111   ) return 0; // Neutral Pions            Neutral Pions
			else if( abs_pdg == 3112 ||            // Sigma- and Sigma~+      Strange Baryons
				       abs_pdg == 3122 ||            // Lambda0 and Lambda~0    Strange Baryons
				       abs_pdg == 3212 ||            // Sigma0 and Sigma~0      Strange Baryons
				       abs_pdg == 3222   ) return 0; // Sigma+ and Sigma~-      Strange Baryons
			else if( energy > m_photon_energy_cut &&
			         pdg     ==   22   ) return 0; // Photons > Energy Cut
			else if( pdg     ==  130 ||            // KL0                     Strange Mesons
				       pdg     ==  310 ||            // KS0                     Strange Mesons
				       abs_pdg ==  311 ||            // K0 and K~0              Strange Mesons
				       abs_pdg ==  313 ||            // K*(892)0 and K*(892)~0  Strange Mesons
				       abs_pdg ==  321 ||            // K+ and K-               Strange Mesons
				       abs_pdg ==  323   ) return 0; // K*(892)+ and K*(892)-   Strange Mesons
			else if( abs_pdg == 4112 ||            // Sigma_c0 and Sigma_c~0   Charmed Baryons
				       abs_pdg == 4122 ||            // Lambda_c+ and Lambda_c~- Charmed Baryons
				       abs_pdg == 4212 ||            // Sigma_c+ and Sigma_c~-   Charmed Baryons
				       abs_pdg == 4222   ) return 0; // Sigma_c++ and Sigma_c~-- Charmed Baryons
			else if( abs_pdg ==  411 ||            // D+ and D-                Charned Mesons
				       abs_pdg ==  421   ) return 0; // D0 and D~0               Charmed Mesons
			else if( !neutrinoMode   &&
				       pdg     == 2212 &&
				       KEp  > protonKECut) return 0; // For antinus, no protons > cut-off KE
			else if( pdg     ==   13   ) genie_n_muons++;
			else if( pdg     ==  -13   ) genie_n_antimuons++;
			// Intermediate muon counts check
			if( genie_n_muons + genie_n_antimuons > 1 ) return 0;
		}
		if( ( neutrinoMode && genie_n_muons     == 0) ||
		    (!neutrinoMode && genie_n_antimuons == 0) ||
		    ( genie_n_chargedpions              == 0)   ) return 0;
		else return 1;
	}

	// Michel Electrons and Neutral Pions

	int HeliumCVUniverse::GetNMichel() const { return GetInt("has_michel_vertex_type_sz"); }
	std::vector<int> HeliumCVUniverse::GetMichelVertexType() const { return GetVecInt("has_michel_vertex_type"); }

	int HeliumCVUniverse::GetImprovedNMichel() const { return GetInt("improved_michel_match_vec_sz"); }
	std::vector<int> HeliumCVUniverse::GetImprovedMichelMatch() const { return GetVecInt("improved_michel_match_vec"); }

	int HeliumCVUniverse::GetFittedNMichel() const { return GetInt("FittedMichel_michel_fitPass_sz"); }
	std::vector<int> HeliumCVUniverse::GetFittedMichelFitPass() const { return GetVecInt("FittedMichel_michel_fitPass"); }

	int HeliumCVUniverse::GetTrueFittedNMichel() const {
		int ntruefittedmichels = 0;
		int nfittedmichels = GetFittedNMichel();
		for (int i =0; i< nfittedmichels; i++) {
			double datafrac = GetVecElem("FittedMichel_michel_datafraction", i);
			int fitted = GetVecElem("FittedMichel_michel_fitPass", i);
			if(fitted == 0) continue;
			if(datafrac > 0.5) continue;
			ntruefittedmichels++;
		}
		return ntruefittedmichels;
	}

	int HeliumCVUniverse::GetHasMichelElectron() const {
		if(GetNMichel() > 0) return 1;
		return 0;
	}

	int HeliumCVUniverse::GetHasImprovedMichelElectron() const {
		if(GetImprovedNMichel() > 0) return 1;
		return 0;
	}

	int HeliumCVUniverse::GetTruthHasMichel() const { return GetInt("truth_reco_has_michel_electron"); }
	int HeliumCVUniverse::GetTruthHasImprovedMichel() const { return GetInt("truth_improved_michel_electron"); }

	int HeliumCVUniverse::GetTruthHasSingleNeutralPion() const {
		int genie_n_neutral_pion = 0;
		std::vector<int> mc_FSPartPDG = GetVecInt("mc_FSPartPDG");
		int mc_nFSPart = GetInt("mc_nFSPart");

		for(int i = 0; i < mc_nFSPart; i++){
			int pdg =  mc_FSPartPDG[i];

			if(      abs(pdg)        ==  211   ) return 0; // Charged pions
			else if( pdg             ==  111   ) genie_n_neutral_pion++;
			// Intermediate check of neutral pion count
			if( genie_n_neutral_pion >     1   ) return 0;
		}
		// Check final neutral pion count
		if( genie_n_neutral_pion == 1 ) return 1;
		return 0; // By process of elimination, if neutral pion count == 0
	}

	int HeliumCVUniverse::GetTrueNeutralPionCount() const {
		int genie_n_neutral_pion = 0;
		std::vector<int> mc_FSPartPDG = GetVecInt("mc_FSPartPDG");
		int mc_nFSPart = GetInt("mc_nFSPart");

		for(int i = 0; i < mc_nFSPart; i++){
			if( mc_FSPartPDG[i] == 111 ) genie_n_neutral_pion++;
		}

		return genie_n_neutral_pion;
	}

	// Michel+Blobs and MultiPion

	int HeliumCVUniverse::GetTruthHasMultiPion() const {
		int genie_n_pion = 0;
		int genie_er_n_eta = 0;
		std::vector<int> mc_FSPartPDG = GetVecInt("mc_FSPartPDG");
		int mc_nFSPart = GetInt("mc_nFSPart");

		for(int i = 0; i < mc_nFSPart; i++){
			int pdg =  mc_FSPartPDG[i];
			if( abs(pdg)      ==  211 ||
			    pdg           ==  111   ) genie_n_pion++;
			if( genie_n_pion > 1 ) return 1; // End early if conditions met
		}

		// Look for presence of Eta in mc_er_*... They typically decay into 2+ pions
		int nerpart = GetInt("mc_er_nPart");
		std::vector<int> erpartID = GetVecInt("mc_er_ID");
		std::vector<int> erpartstatus = GetVecInt("mc_er_status");
		for(int i = 0; i < nerpart; i++){
			int status = erpartstatus[i];
			int id = erpartID[i];

			if(abs(status) == 14 && id == 221) return 1; // If there is an Eta passes
		}

		// If no eta and genie_n_pion < 2 then fails
		return 0;
	}

	int HeliumCVUniverse::GetTruePionCount() const {
		int genie_n_charged_pion = 0;
		int genie_n_neutral_pion = 0;
		std::vector<int> mc_FSPartPDG = GetVecInt("mc_FSPartPDG");
		int mc_nFSPart = GetInt("mc_nFSPart");

		for(int i = 0; i < mc_nFSPart; i++){
			int pdg =  mc_FSPartPDG[i];
			if(      abs(pdg) == 211 ) genie_n_charged_pion++;
			else if( pdg      == 111 ) genie_n_neutral_pion++;
		}

		return genie_n_neutral_pion + genie_n_charged_pion;
	}

	int HeliumCVUniverse::GetEventRecordTrueEtaCount() const {
		int genie_er_n_eta = 0;
		int nerpart = GetInt("mc_er_nPart");
		std::vector<int> erpartID = GetVecInt("mc_er_ID");
		std::vector<int> erpartstatus = GetVecInt("mc_er_status");

		for(int i = 0; i < nerpart; i++){
			bool neutrinoMode = GetAnalysisNuPDG() > 0;
			int status = erpartstatus[i];
			int id = erpartID[i];

			if(abs(status) == 14 && id == 221) genie_er_n_eta++;
		}

		return genie_er_n_eta;
	}

	int HeliumCVUniverse::GetHasMichelOrNBlobs() const {
		if( GetInt("improved_michel_match_vec_sz") > 0 ||
		    HeliumCVUniverse::GetNBlobs() > 1 ) return 1;
		else return 0;
	}

	// Protons

	double HeliumCVUniverse::GetProtonScore(int i) const {
		if( GetMultiplicity() < i+2 ) return -9999.;
		else if( i == 0 ) return GetDouble(std::string(MinervaUniverse::GetTreeName()+"_proton_score").c_str());
		else if( GetInt(std::string(MinervaUniverse::GetTreeName()+"_sec_protons_proton_scores_sz").c_str()) < i ) return -9999.;
		else return GetVecElem(std::string(MinervaUniverse::GetTreeName()+"_sec_protons_proton_scores").c_str(), i-1);
	}
	double HeliumCVUniverse::GetProtonScore1(int i) const {
		if( GetMultiplicity() < i+2 ) return -9999.;
		else if( i == 0 ) return GetDouble(std::string(MinervaUniverse::GetTreeName()+"_proton_score1").c_str());
		else if( GetInt(std::string(MinervaUniverse::GetTreeName()+"_sec_protons_proton_scores1_sz").c_str()) < i ) return -9999.;
		else return GetVecElem(std::string(MinervaUniverse::GetTreeName()+"_sec_protons_proton_scores1").c_str(), i-1);
	}
	double HeliumCVUniverse::GetProtonScore_0() const { return GetProtonScore(0); }
	double HeliumCVUniverse::GetProtonScore_1() const { return GetProtonScore(1); }
	double HeliumCVUniverse::GetProtonScore_2() const { return GetProtonScore(2); }
	double HeliumCVUniverse::GetProtonScore_3() const { return GetProtonScore(3); }
	double HeliumCVUniverse::GetProtonScore_4() const { return GetProtonScore(4); }
	double HeliumCVUniverse::GetProtonScore_5() const { return GetProtonScore(5); }
	double HeliumCVUniverse::GetProtonScore_6() const { return GetProtonScore(6); }
	double HeliumCVUniverse::GetProtonScore_7() const { return GetProtonScore(7); }
	double HeliumCVUniverse::GetProtonScore_8() const { return GetProtonScore(8); }
	double HeliumCVUniverse::GetProtonScore_9() const { return GetProtonScore(9); }

	int HeliumCVUniverse::GetPassProtonScoreCut(double score, double tree_Q2) const {
		if( score < 0 ) return -9999;
		int index = 0;
		for ( int i = 0 ; i < m_proton_score_Q2QEs.size() ; i++ ) {
			if( tree_Q2 >= m_proton_score_Q2QEs[i] ) index++;
		}
		if( score < m_proton_score_mins[index] ) return 0;
		else return 1;
	}
	int HeliumCVUniverse::GetPassScoreCutProton_0() const { return GetPassProtonScoreCut(GetProtonScore_0(),GetQ2QEGeV()); }
	int HeliumCVUniverse::GetPassScoreCutProton_1() const { return GetPassProtonScoreCut(GetProtonScore_1(),GetQ2QEGeV()); }
	int HeliumCVUniverse::GetPassScoreCutProton_2() const { return GetPassProtonScoreCut(GetProtonScore_2(),GetQ2QEGeV()); }
	int HeliumCVUniverse::GetPassScoreCutProton_3() const { return GetPassProtonScoreCut(GetProtonScore_3(),GetQ2QEGeV()); }
	int HeliumCVUniverse::GetPassScoreCutProton_4() const { return GetPassProtonScoreCut(GetProtonScore_4(),GetQ2QEGeV()); }
	int HeliumCVUniverse::GetPassScoreCutProton_5() const { return GetPassProtonScoreCut(GetProtonScore_5(),GetQ2QEGeV()); }
	int HeliumCVUniverse::GetPassScoreCutProton_6() const { return GetPassProtonScoreCut(GetProtonScore_6(),GetQ2QEGeV()); }
	int HeliumCVUniverse::GetPassScoreCutProton_7() const { return GetPassProtonScoreCut(GetProtonScore_7(),GetQ2QEGeV()); }
	int HeliumCVUniverse::GetPassScoreCutProton_8() const { return GetPassProtonScoreCut(GetProtonScore_8(),GetQ2QEGeV()); }
	int HeliumCVUniverse::GetPassScoreCutProton_9() const { return GetPassProtonScoreCut(GetProtonScore_9(),GetQ2QEGeV()); }

	int HeliumCVUniverse::GetSecondaryProtonCandidateCount1() const {
		return GetInt(std::string(MinervaUniverse::GetTreeName()+"_sec_protons_proton_scores1_sz").c_str());
	}

	int HeliumCVUniverse::GetSecondaryProtonCandidateCount() const {
		return GetInt(std::string(MinervaUniverse::GetTreeName()+"_sec_protons_proton_scores_sz").c_str());
	}

	int HeliumCVUniverse::GetPassAllProtonScoreCuts(std::vector<double> scores, double tree_Q2) const {
		int index = 0;
		for ( int i = 0 ; i < m_proton_score_Q2QEs.size() ; i++ ) {
			if( tree_Q2 >= m_proton_score_Q2QEs[i] ) index++;
		}
		for ( auto score:scores ) {
			if( score < m_proton_score_mins[index] ) return 0;
		}
		return 1;
	}

	double HeliumCVUniverse::GetPrimaryProtonScore() const {
		return GetDouble(std::string(MinervaUniverse::GetTreeName()+"_proton_score").c_str());
	}
	double HeliumCVUniverse::GetPrimaryProtonScore1() const {
		return GetDouble(std::string(MinervaUniverse::GetTreeName()+"_proton_score1").c_str());
	}
	double HeliumCVUniverse::GetPrimaryProtonScore2() const {
		return GetDouble(std::string(MinervaUniverse::GetTreeName()+"_proton_score2").c_str());
	}


  double HeliumCVUniverse::GetPrimaryPionScore() const {
		return GetDouble(std::string(MinervaUniverse::GetTreeName()+"_pion_score").c_str());
	}
	double HeliumCVUniverse::GetPrimaryPionScore1() const {
		return GetDouble(std::string(MinervaUniverse::GetTreeName()+"_pion_score1").c_str());
	}
	double HeliumCVUniverse::GetPrimaryPionScore2() const {
		return GetDouble(std::string(MinervaUniverse::GetTreeName()+"_pion_score2").c_str());
	}


	int HeliumCVUniverse::GetIsPrimaryProton1() const {
		if(GetMultiplicity() < 2) return 1; // NA when multiplicity is < 2
		// define and get applicable variables
		double tree_Q2 = GetQ2QEGeV();
		double proton_score1 = GetPrimaryProtonScore1();
		int passes = GetPassProtonScoreCut(proton_score1,tree_Q2);
		return passes;
	}

	int HeliumCVUniverse::GetIsPrimaryProton() const {
		if(GetMultiplicity() < 2) return 1; // NA when multiplicity is < 2
		// define and get applicable variables
		double tree_Q2 = GetQ2QEGeV();
		double proton_score1 = GetPrimaryProtonScore();
		int passes = GetPassProtonScoreCut(proton_score1,tree_Q2);
		return passes;
	}

	int HeliumCVUniverse::GetAreClustsFoundAtPrimaryProtonEnd() const {
		if( GetInt("clusters_found_at_end_proton_prong_sz") > 0) {
			return GetVecElem("clusters_found_at_end_proton_prong",0);
		}
		else return -9999;
	}

	int HeliumCVUniverse::GetNumClustsPrimaryProtonEnd() const {
		if( GetInt("number_clusters_at_end_proton_prong_sz") > 0) {
			return GetVecElem("number_clusters_at_end_proton_prong",0);
		}
		else return -9999;
	}

	double HeliumCVUniverse::GetPrimaryProtonTrackLength() const { return GetDouble("proton_track_length"); }
  double HeliumCVUniverse::GetPrimaryProtonTrackLength_cm() const {
    return GetPrimaryProtonTrackLength() *.1;
}

	double HeliumCVUniverse::GetPrimaryProtonTrackEndX() const { return GetDouble("proton_track_endx"); }
	double HeliumCVUniverse::GetPrimaryProtonTrackEndY() const { return GetDouble("proton_track_endy"); }
	double HeliumCVUniverse::GetPrimaryProtonTrackEndZ() const { return GetDouble("proton_track_endz"); }
	double HeliumCVUniverse::GetPrimaryProtonAngle() const {
		return GetDouble(std::string(MinervaUniverse::GetTreeName()+"_proton_theta").c_str());
	}

  //double HeliumCVUniverse::GetPrimaryPionTrackEndX() const { return GetDouble("pion_track_endx"); }
	//double HeliumCVUniverse::GetPrimaryPionTrackEndY() const { return GetDouble("pion_track_endy"); }
	//double HeliumCVUniverse::GetPrimaryPionTrackEndZ() const { return GetDouble("pion_track_endz"); }
	//double HeliumCVUniverse::GetPrimaryPionAngle() const {
//		return GetDouble(std::string(MinervaUniverse::GetTreeName()+"_pion_theta").c_str());
//	}





	double HeliumCVUniverse::GetCalibEClustsPrimaryProtonEnd() const {
		if( GetInt("calibE_clusters_at_end_proton_prong_sz") > 0) {
			return GetVecElem("calibE_clusters_at_end_proton_prong",0);
		}
		else return -9999.;
	}

	double HeliumCVUniverse::GetVisEClustsPrimaryProtonEnd() const {
		if( GetInt("visE_clusters_at_end_proton_prong_sz") > 0) {
			return GetVecElem("visE_clusters_at_end_proton_prong",0);
		}
		else return -9999.;
	}

	double HeliumCVUniverse::GetPrimaryProtonTfromdEdx() const {
		return GetDouble(std::string(MinervaUniverse::GetTreeName()+"_proton_T_fromdEdx").c_str());
	}

  double HeliumCVUniverse::GetPrimaryProtonThetafromdEdx() const {
		return GetDouble(std::string(MinervaUniverse::GetTreeName()+"_proton_theta_fromdEdx").c_str());
	}



  double HeliumCVUniverse::GetSecondaryProtonTfromdEdx() const {
		return GetDouble(std::string(MinervaUniverse::GetTreeName()+"_sec_protons_T_fromdEdx").c_str());
	}

  double HeliumCVUniverse::GetSecondaryProtonThetafromdEdx() const {
		return GetDouble(std::string(MinervaUniverse::GetTreeName()+"_sec_proton_theta_fromdEdx").c_str());
	}



	double HeliumCVUniverse::GetTotalPrimaryProtonEnergydEdxAndClusters() const {
		return GetPrimaryProtonTfromdEdx() + GetCalibEClustsPrimaryProtonEnd();
	}

	double HeliumCVUniverse::GetPrimaryProtonFractionEnergyInCone() const {
		return GetCalibEClustsPrimaryProtonEnd()/GetTotalPrimaryProtonEnergydEdxAndClusters();
	}

	double HeliumCVUniverse::GetPrimaryProtonTrueKE() const {
		if (GetInt("proton_prong_PDG") == 2212) {
			return GetVecElem("proton_prong_4p",0) - MinervaUnits::M_p;
		}
		else return -9999.;
	}

	int HeliumCVUniverse::GetPrimaryProtonCandidatePDG() const {
		return GetInt("proton_prong_PDG");
	}

	double HeliumCVUniverse::GetEnergyDiffTruedEdx() const {
		return GetPrimaryProtonTrueKE() - GetTotalPrimaryProtonEnergydEdxAndClusters();
	}

	int HeliumCVUniverse::GetRecoTruthIsPrimaryProton() const {
		if (GetInt("proton_prong_PDG") == 2212) return 1;
		else return 0;
	}
	int HeliumCVUniverse::GetRecoTruthIsPrimaryPion() const {
		int pdg = GetInt("proton_prong_PDG");
		if (pdg == 211 || pdg == -211) return 1;
		else return 0;
	}
	int HeliumCVUniverse::GetRecoTruthIsPrimaryOther() const {
		int pdg = GetInt("proton_prong_PDG");
		if (pdg == 2212 || pdg == 211 || pdg == -211) return 0;
		else return 1;
	}

	int HeliumCVUniverse::GetTruthHasSingleProton() const { return GetInt("truth_reco_has_single_proton"); }

	int HeliumCVUniverse::GetAllExtraTracksProtons() const {
		if(GetMultiplicity() < 2) return 1; // NA when multiplicity is < 2
		int n_sec_proton_scores = GetInt(std::string(MinervaUniverse::GetTreeName()+"_sec_protons_proton_scores_sz").c_str());
		if(n_sec_proton_scores == 0) return 1; // NA if not secondary proton candidates

		// define and get applicable variables
		double tree_Q2 = GetQ2QEGeV();
		std::vector<double> sec_proton_scores = GetVecDouble(std::string(MinervaUniverse::GetTreeName()+"_sec_protons_proton_scores").c_str());

		int passes = GetPassAllProtonScoreCuts(sec_proton_scores,tree_Q2);
		return passes;
	}
	int HeliumCVUniverse::GetAllExtraTracksProtons1() const {
		if(GetMultiplicity() < 2) return 1; // NA when multiplicity is < 2
		int n_sec_proton_scores1 = GetInt(std::string(MinervaUniverse::GetTreeName()+"_sec_protons_proton_scores1_sz").c_str());
		if(n_sec_proton_scores1 == 0) return 1; // NA if not secondary proton candidates

		// define and get applicable variables
		double tree_Q2 = GetQ2QEGeV();
		std::vector<double> sec_proton_scores1 = GetVecDouble(std::string(MinervaUniverse::GetTreeName()+"_sec_protons_proton_scores1").c_str());

		int passes = GetPassAllProtonScoreCuts(sec_proton_scores1,tree_Q2);
		return passes;
	}

	int HeliumCVUniverse::GetProtonCount() const {
		if(GetMultiplicity() < 2) return 0;
		int count = 0;
		double tree_Q2 = GetQ2QEGeV();
		double proton_score = GetPrimaryProtonScore();
		if( GetPassProtonScoreCut(proton_score,tree_Q2) ) count++;
		int n_sec_proton_scores = GetInt(std::string(MinervaUniverse::GetTreeName()+"_sec_protons_proton_scores_sz").c_str());
		std::vector<double> sec_proton_scores = GetVecDouble(std::string(MinervaUniverse::GetTreeName()+"_sec_protons_proton_scores").c_str());
		for ( int i=0; i<n_sec_proton_scores; i++ ) {
			if(GetPassProtonScoreCut(sec_proton_scores[i],tree_Q2)) count++;
		}
		return count;
	}
	int HeliumCVUniverse::GetProtonCount1() const {
		if(GetMultiplicity() < 2) return 0;
		int count = 0;
		double tree_Q2 = GetQ2QEGeV();
		double proton_score1 = GetPrimaryProtonScore1();
		if( GetPassProtonScoreCut(proton_score1,tree_Q2) ) count++;
		int n_sec_proton_scores1 = GetInt(std::string(MinervaUniverse::GetTreeName()+"_sec_protons_proton_scores1_sz").c_str());
		std::vector<double> sec_proton_scores1 = GetVecDouble(std::string(MinervaUniverse::GetTreeName()+"_sec_protons_proton_scores1").c_str());
		for ( int i=0; i<n_sec_proton_scores1; i++ ) {
			if(GetPassProtonScoreCut(sec_proton_scores1[i],tree_Q2)) count++;
		}
		return count;
	}

	int HeliumCVUniverse::GetTrueProtonCount() const {
		int genie_n_protons = 0;

		std::vector<int> mc_FSPartPDG = GetVecInt("mc_FSPartPDG");
		std::vector<double> mc_FSPartE = GetVecDouble("mc_FSPartPDG");
		int mc_nFSPart = GetInt("mc_nFSPart");

		for(int i = 0; i < mc_nFSPart; i++){
			int pdg =  mc_FSPartPDG[i];
			double energy = mc_FSPartE[i];
			double KEp = energy - MinervaUnits::M_p;
			if( pdg == 2212         &&
				KEp  > m_proton_ke_cut ) genie_n_protons++;
		}

		return genie_n_protons;
	}

	// Other particles

	int HeliumCVUniverse::GetTrueNumberOfFSParticles() const {
		return GetInt("mc_nFSPart");
	}

	int HeliumCVUniverse::GetTrueLightMesonCount() const { // Just base etas right now
		int genie_n_light_meson = 0;
		std::vector<int> mc_FSPartPDG = GetVecInt("mc_FSPartPDG");
		int mc_nFSPart = GetInt("mc_nFSPart");
		for(int i = 0; i < mc_nFSPart; i++){
			if( mc_FSPartPDG[i] == 221) genie_n_light_meson++;
		}
		return genie_n_light_meson;
	}

	int HeliumCVUniverse::GetTrueCharmedMesonCount() const { // D_+ and D_0
		int genie_n_charmed_meson = 0;
		std::vector<int> mc_FSPartPDG = GetVecInt("mc_FSPartPDG");
		int mc_nFSPart = GetInt("mc_nFSPart");
		for(int i = 0; i < mc_nFSPart; i++){
			if( mc_FSPartPDG[i] == 411 ||
			    mc_FSPartPDG[i] == 421   ) genie_n_charmed_meson++;
		}
		return genie_n_charmed_meson;
	}

	int HeliumCVUniverse::GetTrueStrangeMesonCount() const { // K__L0, K_S0, K_0, K_*(892)0, K_+, K_*(892)+
		int genie_n_strange_meson = 0;
		std::vector<int> mc_FSPartPDG = GetVecInt("mc_FSPartPDG");
		int mc_nFSPart = GetInt("mc_nFSPart");
		for(int i = 0; i < mc_nFSPart; i++){
			if( mc_FSPartPDG[i]      == 130 ||
				mc_FSPartPDG[i]      == 310 ||
				mc_FSPartPDG[i]      == 311 ||
				mc_FSPartPDG[i]      == 313 ||
				abs(mc_FSPartPDG[i]) == 321 ||
				abs(mc_FSPartPDG[i]) == 323   ) genie_n_strange_meson++;
		}
		return genie_n_strange_meson;
	}

	int HeliumCVUniverse::GetTrueCharmedBaryonCount() const { // Sigma_c0, Lambda_c+, Sigma_c+, Sigma_c++
		int genie_n_charmed_baryon = 0;
		std::vector<int> mc_FSPartPDG = GetVecInt("mc_FSPartPDG");
		int mc_nFSPart = GetInt("mc_nFSPart");
		for(int i = 0; i < mc_nFSPart; i++){
			if( mc_FSPartPDG[i] == 4112 ||
			    mc_FSPartPDG[i] == 4122 ||
			    mc_FSPartPDG[i] == 4212 ||
			    mc_FSPartPDG[i] == 4222   ) genie_n_charmed_baryon++;
		}
		return genie_n_charmed_baryon;
	}

	int HeliumCVUniverse::GetTrueStrangeBaryonCount() const { // Sigma_-, Lambda, Sigma_0, Sigma_+
		int genie_n_strange_baryon = 0;
		std::vector<int> mc_FSPartPDG = GetVecInt("mc_FSPartPDG");
		int mc_nFSPart = GetInt("mc_nFSPart");
		for(int i = 0; i < mc_nFSPart; i++){
			if( mc_FSPartPDG[i] == 3112 ||
			    mc_FSPartPDG[i] == 3122 ||
			    mc_FSPartPDG[i] == 3212 ||
			    mc_FSPartPDG[i] == 3222   ) genie_n_strange_baryon++;
		}
		return genie_n_strange_baryon;
	}

	int HeliumCVUniverse::GetMCTargetA() const { return GetInt("mc_targetA"); }
	int HeliumCVUniverse::GetMCTargetZ() const { return GetInt("mc_targetZ"); }
	int HeliumCVUniverse::GetMCTargetNucleon() const { return GetInt("mc_targetNucleon"); }

	int HeliumCVUniverse::Dummy() const { return 0; }

	// Arachne

	void HeliumCVUniverse::PrintTrueArachneLink() const {
		int link_size = 200;
		char link[link_size];
		int run = GetInt("mc_run");
		int subrun = GetInt("mc_subrun");
		int gate = GetInt("mc_nthEvtInFile") + 1;
		int slice = GetVecElem("slice_numbers", 0);
		sprintf(link,
			    "https://minerva05.fnal.gov/Arachne/"
			    "arachne.html\?det=SIM_minerva&recoVer=v21r1p1&run=%d&subrun=%d&gate="
			    "%d&slice=%d",run, subrun, gate, slice);
		/*std::cout << link << std::endl;
		std::cout << "Lepton E: " <<  GetElepTrueGeV() << " Run " << run << "/"<<subrun << "/" << gate << "/" << slice << std::endl;
		std::cout << "Printing Available Energy " << NewEavail() << std::endl;
		std::cout << "Muon P: " << GetMuonP() << std::endl;
		std::cout << "Get Muon Pt: " << GetMuonPT() << std::endl;
		std::cout << "Get Muon Pz: " << GetMuonPz() << std::endl;
		std::cout << "Get Muon PT True " << GetMuonPTTrue() << std::endl;*/

	}

	void HeliumCVUniverse::PrintDataArachneLink() const {
		int link_size = 200;
		char link[link_size];
		int run = GetInt("ev_run");
		int subrun = GetInt("ev_subrun");
		int gate = GetInt("ev_gate");
		int slice = GetVecElem("slice_numbers", 0);
		sprintf(link,
			    "https://minerva05.fnal.gov/Arachne/"
			    "arachne.html\?det=MV&recoVer=v21r1p1&run=%d&subrun=%d&gate="
			    "%d&slice=%d",run, subrun, gate, slice);
		std::cout << link << std::endl;
		// std::cout << "Lepton E: " <<  GetMuonPT() << " Run " << run << "/"<<subrun << "/" << gate << "/" << slice << std::endl;
	}


void HeliumCVUniverse::Print() const { std::cout
<< ShortName() << ", "
<< GetRun() << ", "
<< GetSubRun() << ", "
<< GetGate() << ", "
<< GetTruthNuPDG() << ","
<< GetTruthIsCC() << ","
<< GetTruthIsCCQELike() << ", "
<< GetIsMinosMatchTrack() << ", "
<< std::endl;
}




std::vector <double> HeliumCVUniverse::GETvector_Pion_T() const{ return GetVecDouble(std::string(MinervaUniverse::GetTreeName() + "_pion_T").c_str());}
std::vector <double> HeliumCVUniverse::GETvector_Pion_Theta() const{ return GetVecDouble(std::string(MinervaUniverse::GetTreeName() + "_pion_theta").c_str());}

std::vector <int> HeliumCVUniverse::GETvector_Pion_InRecoBranch_getTrueTrackID() const{ return GetVecInt(std::string(MinervaUniverse::GetTreeName() + "_hadron_tm_trackID").c_str());}

int HeliumCVUniverse::GET_index_Pion_InRecoBranch_getTrueTrackID(int index) const{
   return GetVecElem(std::string(MinervaUniverse::GetTreeName() + "_hadron_tm_trackID").c_str(), index);

 }



std::vector <int> HeliumCVUniverse::GETvector_Pion_InRecoBranch_getTrueTrackID_corrected()const{

  std::vector <int> index_vector =GETvector_Pion_InRecoBranch_getTrueTrackID();
  //for(auto singleindex: index_vector ){if(singleindex != -1){return_vector.push_back(singleindex - 1);}}

index_vector.erase(std::remove(index_vector.begin(), index_vector.end(), -1), index_vector.end());
  return index_vector;
}



//std::vector <double> HeliumCVUniverse::GETvector_Pion_InRecoBranch_getTrueTrackID() const{ return GetVecDouble(std::string(MinervaUniverse::GetTreeName() + "_hadron_tm_trackID").c_str());}





// there is already function that do this from ccqe
//double  HeliumCVUniverse::GET_PrimaryProton_EndPointX() const{ return GetDouble(std::string(MinervaUniverse::GetTreeName() + "_proton_endPointX").c_str());}
//double  HeliumCVUniverse::GET_PrimaryProton_EndPointY() const{ return GetDouble(std::string(MinervaUniverse::GetTreeName() + "_proton_endPointY").c_str());}
//double  HeliumCVUniverse::GET_PrimaryProton_EndPointZ() const{ return GetDouble(std::string(MinervaUniverse::GetTreeName() + "_proton_endPointZ").c_str());}
//
//double  HeliumCVUniverse::GET_PrimaryProton_StartPointX() const{ return GetDouble(std::string(MinervaUniverse::GetTreeName() + "_proton_startPointX").c_str());}
//double  HeliumCVUniverse::GET_PrimaryProton_StartPointY() const{ return GetDouble(std::string(MinervaUniverse::GetTreeName() + "_proton_startPointY").c_str());}
//double  HeliumCVUniverse::GET_PrimaryProton_StartPointZ() const{ return GetDouble(std::string(MinervaUniverse::GetTreeName() + "_proton_startPointZ").c_str());}
//
//double HeliumCVUniverse::GetPrimaryProton_TrackLength const {
//
//double DiffX = GET_PrimaryProton_EndPointX() - GET_PrimaryProton_StartPointX();
//double DiffY = GET_PrimaryProton_EndPointY() - GET_PrimaryProton_StartPointY();
//double DiffZ = GET_PrimaryProton_EndPointZ() - GET_PrimaryProton_StartPointZ();
//
//return  sqrt(pow(DiffX,2) + pow(DiffY,2)+ pow(DiffZ,2));
//}



bool HeliumCVUniverse::AreAllPion_theta_equal_AnaDev()const{
  std::vector <double> angles = GETvector_Pion_Theta();
if ( allEqual(angles) ){
  return true;
}
else {return false;}
}


bool HeliumCVUniverse::AreAllHadron_equal_AnaDev()const{
  std::vector <int> hadron_ID = GETvector_Pion_InRecoBranch_getTrueTrackID();
if ( allEqual(hadron_ID) ){
  return true;
}
else {return false;}
}


bool HeliumCVUniverse::PionRECOtrack_good() const{

bool hadron_allequal = AreAllHadron_equal_AnaDev();
bool pion_allequal = AreAllPion_theta_equal_AnaDev();

if(hadron_allequal || pion_allequal ) {return false;}
else {return true;}


}




std::vector <int> HeliumCVUniverse::GETindexvector_Pions_Thetalessthan(double input_angle ) const{
  std::vector <double> angles = GETvector_Pion_Theta();
  std::vector<int> index;
  int count=0;
  for(auto angle: angles){
    if(angle < input_angle && angle > 0.0){
      index.push_back(count);
    }

    count++;
  }

  return index;
}
bool HeliumCVUniverse::IsthereRecoilwithAngleLess(double inputangle)const{
  std::vector <double> angles = GETvector_Pion_Theta();
for(auto angle: angles){
if(angle < inputangle && angle > 0.0 )
{return true;}
}

return false;

}



int HeliumCVUniverse::GetTPion(std::vector <int> index)const {
  std::vector <double> KE = GETvector_Pion_T();
  double greatest = -99999;
  int bestindex = -1;
  for(auto input: index){
      if(KE.at(input) > greatest){
      greatest = KE.at(input);
      bestindex = input;
    }
  }
  return bestindex;
}

int HeliumCVUniverse::FindPionIndex(double input_angle) const {
 auto list = GETindexvector_Pions_Thetalessthan( input_angle) ;
 return GetTPion(list);

}


int HeliumCVUniverse::getPDG_PionRECOTrack(int index) const{
  return GetVecElem(std::string(MinervaUniverse::GetTreeName() + "_hadron_tm_PDGCode").c_str(), index);
}

double HeliumCVUniverse::Get_NonmuTrkANGLE_WRTB_AnaDev(int index)  const{
  return GetVecElem(std::string(MinervaUniverse::GetTreeName() + "_pion_theta").c_str(),index)* TMath::RadToDeg();}

std::vector <double> HeliumCVUniverse::GETvector_hadron_beginKE() const{ return GetVecDouble(std::string(MinervaUniverse::GetTreeName() + "_hadron_tm_beginKE").c_str());}


int HeliumCVUniverse::GET_RECO_index_hadron_GreatestKE()const {
  std::vector <double> Energy = GETvector_hadron_beginKE();
  return std::distance(Energy.begin(),std::max_element(Energy.begin(), Energy.end()));
}



bool HeliumCVUniverse::PassTrueDistToDivisionCut(double xySep /* = 25. */ )
{
    //only relevant for passive targets 1235
    if( 0 < GetInt("truth_targetID") && GetInt("truth_targetID") < 10 && 4 != GetInt("truth_targetID"))
        return ( xySep < GetDouble("truth_target_dist_to_division") );

    return true;
}


bool HeliumCVUniverse::PassTrueFiducial( )
{
bool TrueHexCut = InHexagonTrue( 850.);
bool True_dist_division = PassTrueDistToDivisionCut( );
if(TrueHexCut == true && True_dist_division == true){return true;}
else {return false;}


}
