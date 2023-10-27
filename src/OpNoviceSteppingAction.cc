//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file OpNoviceSteppingAction.cc
/// \brief Implementation of the OpNoviceSteppingAction class

#include "OpNoviceSteppingAction.hh"
#include "OpNoviceRun.hh"
#include "G4Event.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4OpticalPhoton.hh"
#include "G4RunManager.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "OpNoviceEventAction.hh"
#include "OpNoviceDetectorConstruction.hh"
#include "OpNoviceGDMLDetectorConstruction.hh"

#include "parameterlist.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "Analysis.hh"


extern G4String Detector_name;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

OpNoviceSteppingAction::OpNoviceSteppingAction(OpNoviceEventAction* event)
  : G4UserSteppingAction(),
  fEventAction(event),
  fScoringVolume(0)
{
  // beamRadiius = 0.;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
OpNoviceSteppingAction::~OpNoviceSteppingAction() 
{
  // delete fMeasure;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void OpNoviceSteppingAction::UserSteppingAction(const G4Step* step)
{
  static G4ParticleDefinition* opticalphoton =
    G4OpticalPhoton::OpticalPhotonDefinition();

  G4Track* track = step->GetTrack();

  const G4ParticleDefinition* particleDef = 
    track->GetDynamicParticle()->GetParticleDefinition();

  G4ThreeVector position = track->GetPosition();  

  if(particleDef == opticalphoton)
  {
    G4StepPoint* endPoint = step->GetPostStepPoint();
    const G4VProcess* pds = endPoint->GetProcessDefinedStep();
    G4String procname     = pds->GetProcessName();
    if(procname.compare("OpRayleigh") == 0)
      fEventAction->AddRayleigh();
    else if(procname.compare("OpAbsorption") == 0)
      fEventAction->AddAbsorption();
    else if(procname.compare("OpMieHG") == 0)
      fEventAction->AddMie();

    //get opticalphoton position


    // for boundary scattering, process name in 'transportation'.
    // Need to check differently:
    if(endPoint->GetStepStatus() == fGeomBoundary)
    {
      G4OpBoundaryProcessStatus theStatus = Undefined;
      G4ProcessManager* opManager         = opticalphoton->GetProcessManager();
      G4int n_proc = opManager->GetPostStepProcessVector(typeDoIt)->entries();
      G4ProcessVector* postStepDoItVector =
        opManager->GetPostStepProcessVector(typeDoIt);
      for(G4int i = 0; i < n_proc; ++i)
      {
        G4VProcess* currentProcess = (*postStepDoItVector)[i];

        G4OpBoundaryProcess* opProc =
          dynamic_cast<G4OpBoundaryProcess*>(currentProcess);
        if(opProc)
          theStatus = opProc->GetStatus();
      }
      if(theStatus != Undefined && theStatus != NotAtBoundary &&
         theStatus != StepTooSmall)
      {
        fEventAction->AddBoundary();
      }
    }
    G4cout<<"Next Direction:"<<step->GetTrack()->GetDynamicParticle()->GetMomentumDirection().x()
    <<" "<<step->GetTrack()->GetDynamicParticle()->GetMomentumDirection().y()<< " "
    <<step->GetTrack()->GetDynamicParticle()->GetMomentumDirection().z()<<G4endl;
    
    //check if first shoot in detector
    G4VPhysicalVolume* phyVolume = step -> GetPreStepPoint() -> GetTouchableHandle() -> GetVolume();
    static G4VPhysicalVolume* nextVolume = track ->  GetNextVolume ();
    G4String nextVolumeName = nextVolume -> GetName();
    G4VPhysicalVolume* currentVolume = step -> GetPreStepPoint() -> GetTouchableHandle() -> GetVolume();
    // G4cout << "nextVolume is :" << nextVolume -> GetName() << "==========currentVolume is :" <<
    // currentVolume -> GetName() << G4endl;

    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    // G4cout << "step test2" << G4endl;
    if (currentVolume -> GetName() == "VD1_PV" && step -> IsFirstStepInVolume() && particleDef -> GetParticleName() == "opticalphoton")
    {
    // beamRadiius = std::sqrt(position.y()*position.y() + position.x()*position.x());
    // if (beamRadiius != 0 )
    // {
      // analysisManager->FillH1(1, beamR adiius * 1000.);
      analysisManager->FillH1(1, position.x() * 1000);
      analysisManager->FillH2(0, position.x() * 1000, position.y() * 1000);
    // }
    // G4cout << "=======================calculate Radius=========================" << G4endl;
    }
    // else if (nextVolume -> GetName() == "VD2_PV" && currentVolume -> GetName() == "World" 
    //   && position.z() >= fullLenth/2 + secDistance - 1.*mm && position.z() <= fullLenth/2 + secDistance)
    // {
    //   analysisManager->FillH1(2, position.x() * 1000);
    //   analysisManager->FillH2(1, position.x() * 1000, position.y() * 1000);
    // }
    // else if (nextVolume -> GetName() == "VD3_PV" && currentVolume -> GetName() == "World" 
    //   && position.z() >= fullLenth/2 + thiDistance - 1.*mm && position.z() <= fullLenth/2 + thiDistance)
    // {
    //   analysisManager->FillH1(3, position.x() * 1000);
    //   analysisManager->FillH2(2, position.x() * 1000, position.y() * 1000);
    // }
    // else if (nextVolume -> GetName() == "VD4_PV" && currentVolume -> GetName() == "World" 
    //   && position.z() >= fullLenth/2 + forDistance - 1.*mm && position.z() <= fullLenth/2 + forDistance)
    // {
    //   analysisManager->FillH1(4, position.x() * 1000);
    //   analysisManager->FillH2(3, position.x() * 1000, position.y() * 1000);
    // }
    // else if (nextVolume -> GetName() == "VD5_PV" && currentVolume -> GetName() == "World" 
    //   && position.z() >= fullLenth/2 + fitDistance - 1.*mm && position.z() <= fullLenth/2 + fitDistance)
    // {
    //   analysisManager->FillH1(5, position.x() * 1000);
    //   analysisManager->FillH2(4, position.x() * 1000, position.y() * 1000);
    // }
    // else if (nextVolume -> GetName() == "VD6_PV" && currentVolume -> GetName() == "World" 
    //   && position.z() >= fullLenth/2 + sixDistance - 1.*mm && position.z() <= fullLenth/2 + sixDistance)
    // {
    //   analysisManager->FillH1(6, position.x() * 1000);
    //   analysisManager->FillH2(5, position.x() * 1000, position.y() * 1000);
    // }
    // else if(position.x() >= && position.x() <= )
    // {

    // }
    // G4cout << "fill - done" << G4endl;
  }

  if (!fScoringVolume) { 
    const OpNoviceDetectorConstruction* detectorConstruction
      = static_cast<const OpNoviceDetectorConstruction*>
        (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    fScoringVolume = detectorConstruction->GetScoringVolume(); 

    G4cout<<"Volume is :"<<fScoringVolume->GetName()<<G4endl;
  }

  // get volume of the current step
  G4LogicalVolume* volume 
    = step->GetPreStepPoint()->GetTouchableHandle()
      ->GetVolume()->GetLogicalVolume();  
  // G4LogicalVolume* tsvolume = volume->GetVolume(Detector_name)
  // G4cout<<"Volume is :"<<volume->GetName()<<G4endl;
  
  // check if we are in scoring volume
  if (volume != fScoringVolume) return;
  
  // if (track->GetCurrentStepNumber())
  // {
  //   //record first-get-in particle position

  // }
  // collect energy deposited in this step
  G4double edepStep = step->GetTotalEnergyDeposit();
  G4cout<<"=============================calculate energy================================"<<edepStep/keV<<G4endl;
 // G4cout<<"********the step energy is"<<edepStep<<"*************"<<G4endl;
  fEventAction->AddEdep(edepStep);  
  // G4cout<<"=============================calculate energy================================2"<<fEdep<<G4endl;
  // fMeasure ->MeasureOpticalPhotonBeamRadius();
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
