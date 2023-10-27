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
/// \file optical/OpNovice/src/OpNoviceEventAction.cc
/// \brief Implementation of the OpNoviceEventAction class
//
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "OpNoviceEventAction.hh"
#include "OpNoviceRun.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "Analysis.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "OpNoviceRunAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
OpNoviceEventAction::OpNoviceEventAction(OpNoviceRunAction* runAction)
  : G4UserEventAction(),
  fRunAction(runAction),
  fEdep(0.)
{
  fRayleigh   = 0;
  fAbsorption = 0;
  fMie        = 0;
  fBoundary   = 0;
  counts = 0;
  particle = 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
OpNoviceEventAction::~OpNoviceEventAction() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void OpNoviceEventAction::BeginOfEventAction(const G4Event*)
{
  fRayleigh   = 0;
  fAbsorption = 0;
  fMie        = 0;
  fBoundary   = 0;
  fEdep = 0.;
  // fbeamRadius = 0.;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void OpNoviceEventAction::EndOfEventAction(const G4Event*)
{
  OpNoviceRun* run = static_cast<OpNoviceRun*>(
    G4RunManager::GetRunManager()->GetNonConstCurrentRun());
  run->AddRayleigh(fRayleigh);
  run->AddAbsorption(fAbsorption);
  run->AddMie(fMie);
  run->AddBoundary(fBoundary);
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  // accumulate statistics in run action
  //G4cout<<fEdep<<G4endl;
  particle++;
  G4cout<<"*********************particle:"<<particle<<"**************"<<G4endl;
  if(fEdep!=0){
  //  G4double sigma=(0.0004025546437616+0.00000000014700713*sqrt(0.0004025546437616*fEdep*fEdep+0.0000000014700713*fEdep))/2.35842;
  //  G4double outenergy=G4RandGauss::shoot(fEdep,sigma);
   counts++;

   G4cout<<"+++"<<counts<<"********the event energy is"<<fEdep<<"**************"<<G4endl;
  
    analysisManager->FillH1(0, fEdep/keV);
  }
  // if (fbeamRadius != 0 )
  // {
  //   analysisManager->FillH1(1, fbeamRadius * 1000.);
  // }
  
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
