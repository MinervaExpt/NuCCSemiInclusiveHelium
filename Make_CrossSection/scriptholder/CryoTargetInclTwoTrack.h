#ifndef CRYOTARGETINCLTWOTRACK_H 
#define CRYOTARGETINCLTWOTRACK_H 1

//I inherit thee
#include "AnaUtils/MinervaAnalysisTool.h"

//-- from Rec
#include "RecUtils/IConeUtilsTool.h"
#include "RecUtils/Cone.h"
#include "RecUtils/ParticleExtraDataDefs.h"
#include "EnergyRecTools/IEnergyCorrectionTool.h"

#include "RecInterfaces/IAnchoredTrackFormation.h"
#include "RecInterfaces/ITrackFormation.h"
#include "RecInterfaces/ITrackPropagator.h"

#include "ParticleMaker/IParticleMakerTool.h"

#include "RecUtils/IAnchorSelectorTool.h"
#include "GeoUtils/IMinervaCoordSysTool.h"
#include "GeoUtils/INuclearTargetTool.h"
#include "GeoUtils/NuclearTarget.h"
#include "BlobFormation/IIDIsolatedIDBlobCreator.h"
#include "RecInterfaces/IIDBlobCreator.h"
#include "RecInterfaces/IAnchoredTrackFormation.h"
//#include "EventReconstruction/IPrimaryBlobProngTool.h"
#include "EventRecInterfaces/IPrimaryBlobProngTool.h"

#include "VertexCreation/IVertexFitter.h"
#include "ProngMaker/IProngClassificationTool.h"
#include "ProngMaker/IODProngClassificationTool.h"
#include "ParticleMaker/IParticleTool.h"

//-- from Tools
#include "MinervaUtils/IHitTaggerTool.h"

#include "VertexCreation/IVertexUtils.h"
//-- from Det
#include "ODDet/DeOuterDetector.h"
#include "MinervaDet/DeDetector.h"

//-- from Ana
#include "AnaUtils/IFastAcceptanceTool.h"
#include "AnaUtils/IMuonUtils.h"
#include "AnaUtils/IProtonUtils.h"
#include "TruthMatcher/ITruthMatcher.h"


class IMinervaObjectAssociator;
class IVetoProngClassificationTool;

class CryoTargetInclTwoTrack : public MinervaAnalysisTool, virtual public IInteractionHypothesis
{
 public:

  //! Standard constructor
  CryoTargetInclTwoTrack( const std::string& type, const std::string& name, const IInterface* parent );

  //! Destructor (mandatory for inheritance)
  ~CryoTargetInclTwoTrack(){};

  //! Initialize (mandatory for inheritance)
  StatusCode initialize();
  //! Finalize (mandatory for inheritance)
  StatusCode finalize();

  //! Reconstruct the event (mandatory for inheritance)
  StatusCode reconstructEvent( Minerva::PhysicsEvent* event, Minerva::GenMinInteraction* truth = NULL ) const;

  //! Attach an interpretations to the event (mandatory for inheritance)
  StatusCode interpretEvent( const Minerva::PhysicsEvent* event, const Minerva::GenMinInteraction* truth, std::vector<Minerva::NeutrinoInt*>& nuInts ) const;

  //! Tag truth via GenMinInteraction
  StatusCode tagTruth( Minerva::GenMinInteraction* truth ) const;


 protected:
  bool muonProng( Minerva::ProngVect& prongs, SmartRef<Minerva::Prong>& prong, 
		  SmartRef<Minerva::Particle>& particle, std::string& type ) const;


  SmartRef<Minerva::Particle> findMuonParticleCandidate( SmartRef<Minerva::Prong>& prong ) const;


  std::string odMuonProng( SmartRef<Minerva::Prong>& prong, SmartRef<Minerva::Particle>& particle ) const;

  void fillBlobEventData( Minerva::PhysicsEvent* event ) const; 


  bool createdIDBlobProng( Minerva::PhysicsEvent* event ) const;

  void setMuonID( Minerva::NeutrinoInt* neutrino, SmartRef<Minerva::Prong>& prong ) const;

  StatusCode extendVtxBlobProng( Minerva::IDClusterVect& clusters, SmartRef<Minerva::Vertex>& vertex,std::vector<Minerva::Prong*>* vtxBlobProngVect ) const;


  void linkProngToPrimaryProng( Minerva::Prong* prong, Minerva::ProngVect& primaryProngs ) const;

  bool classifyProngs( Minerva::PhysicsEvent* event ) const;

  bool createdAnchoredShortTracks( Minerva::PhysicsEvent* event ) const;
  Minerva::IDClusterVect getClusters( Minerva::PhysicsEvent* event, SmartRef<Minerva::Vertex> vertex ) const;


  void setTrackDirection( Minerva::Track* track, Minerva::Vertex* vertex ) const;

  bool createdAnchoredLongTracks( Minerva::PhysicsEvent* event ) const;

  bool VertexLongTracksToCryoRegion( Minerva::PhysicsEvent* event  ) const;

  Minerva::IDClusterVect getClustersForCryoTargetShortAnchorTracks( Minerva::PhysicsEvent* event, SmartRef<Minerva::Vertex> vertex ) const;


  void setTrackProngTruth( Minerva::NeutrinoInt* neutrino, SmartRef<Minerva::Prong>& prong, bool isFirstProng ) const;


  bool createdODBlobProng( Minerva::PhysicsEvent* event ) const;

  bool createdTrackedParticles( Minerva::ProngVect& prongs ) const;

  bool VetoWallMatchingTrack( Minerva::ProngVect& prongs ) const;

  //----------
  //for test
  
  Gaudi::XYZVector GuessErrorNewVtxPos( Minerva::Vertex * vtx, Gaudi::XYZPoint newPos ) const;
  
  //----------

 private:

  Minerva::DeDetector* m_ID;


  ITrackFormation*             m_longTrackFormation;
  std::string                  m_longTrackFormationAlias;

  ITrackPropagator*            m_trackPropagator;   
  std::string                  m_trackPropagatorAlias;
  
  typedef std::vector<Minerva::NeutrinoInt*> NeutrinoVect;
  StatusCode interpretFailEvent( Minerva::PhysicsEvent* event ) const;

  IConeUtilsTool*             m_coneUtilsTool;
  IEnergyCorrectionTool*      m_energyCorrectionTool;
  IMinervaCoordSysTool*       m_coordSysTool;
  IFastAcceptanceTool*        m_acceptanceTool;
  ITruthMatcher*              m_truthMatcher;
  IHitTaggerTool*             m_hitTagger;
  Minerva::DeOuterDetector*   m_odDet;

  IProtonUtils*               m_protonUtils;
  std::string                 m_protonUtilsAlias;

  IMuonUtils*                 m_muonUtils;
  std::string                 m_muonUtilsAlias;

  IPrimaryBlobProngTool*      m_primaryBlobProngTool;
  std::string                 m_primaryBlobProngAlias;

  IIDIsolatedIDBlobCreator*   m_idIsolatedBlobCreator;
  std::string                 m_idIsolatedBlobAlias;

  IIDBlobCreator*             m_idDispersedBlobCreator;
  std::string                 m_idDispersedBlobAlias;

  IAnchoredTrackFormation*    m_anchoredTracker;
  std::string                 m_anchorShortTrackerAlias;

  IAnchorSelectorTool*        m_anchorSelector;
  std::string                 m_anchorSelectorAlias;

  //--- for LongTrackFormation (???) 
  IAnchoredTrackFormation*    m_anchoredLongTracker;
  std::string                 m_anchorLongTrackerAlias;

  //---

  IVertexFitter*              m_vertexFitter;
  std::string                 m_vertexFitterAlias;


  IProngClassificationTool*   m_prongIntersection;
  std::string                 m_prongIntersectionAlias;

  IODProngClassificationTool* m_odMatchTool;
  std::string                 m_odMatchAlias;

  //IParticleTool*              m_particleMaker;
  IParticleMakerTool*        m_particleMaker;
  std::string                 m_particleMakerAlias;

  IMinervaObjectAssociator*  m_objectAssociator;


  // For matching Prongs with VetoDigits in the Gate.
  std::string                m_vetoProngMatchToolName;      ///< Name of the tool class.
  std::string                m_vetoProngMatchToolNameAlias; ///< Name in the opts file.
  IVetoProngClassificationTool*  m_vetoProngMatchTool;          ///< Prong vetoing tool.




  IVertexUtils*   m_vertexUtils;

  double                     m_clusVertex2DSeparation;
  double                     m_clusVertexZSeparation;
  double                     m_clusTrackTimeWindow;
  double                     m_strictClusTimeWindow;
  double                     m_distanceFromVertex;
  double                     m_fuzzRadius;

  double                     m_maxSearchDistance;
  double                     m_maxStartingDistance;
  double                     m_maxAllowedSearchGap;
  double                     m_maxSeparationBlobVertex;



  //===== BEGIN Tool Properties =====//
  /** @name Properties
    Properties that you can set from an options file.
    @{*/
  /*! @brief An example of something you can set from the options file
    @property{SomeProperty,"theDefaultValue"}

    The only reason I put this in is to encourage doxygen comments.
   */
  std::string m_someProperty;

  /*!
    @brief Maximum z-value for vertex of tracks for extrapolation to the Cryo-Target (tracks coming from front of the detector) 
    @property{MaxVtxZCryoTargetTrks, 4446.33}
  */    
  double m_maxVtxZCryoTargetTrks;
  
  /*!
    @brief Maximum z-value for crossing-point of the anchor track and any of the other tracks coming from the front of the detector 
    @property{MaxZposCryoVtx, 4293.04}
  */  
  double m_maxZposCryoVtx;


  //temp vtx study (same as in VertexFitterKalman) : begin
  bool m_useMS;
  double m_dMinWeightPOCA;
  double m_nPowerWeightPOCA;

  //temp vtx study (same as in VertexFitterKalman) : end


  double                     m_min_mva_score;
  double                     m_CCQEBindingEnergyMeV;


  int     m_muonProngColor; 
  int     m_protonProngColor; 
  int     m_primaryVertexColor; 
  int     m_secondaryVertexColor; 
  int     m_endPointVertexColor; 
  int     m_unattachedProngColor; 


  double m_temperature;//!< Store the current annealing temperature

  //!@}
  //===== END Tool Properties =====//
};

#endif

