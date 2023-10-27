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
/// \file OpNovice/src/OpNoviceRunAction.cc
/// \brief Implementation of the OpNoviceRunAction class
//
//
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#include "OpNoviceRunAction.hh"
#include "OpNovicePrimaryGeneratorAction.hh"
#include "OpNoviceRun.hh"
#include "G4ParticleDefinition.hh"
#include "G4Run.hh"

#include "Analysis.hh"
#include "parameterlist.hh"


extern G4String fileName;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
OpNoviceRunAction::OpNoviceRunAction(OpNovicePrimaryGeneratorAction* prim)
  : G4UserRunAction()
  , fRun(nullptr)
  , fPrimary(prim)
  , count(0)
  , flag(0)
{
  //实例化analysis
  //nstance()保证每一个类仅有一个实例，并为它提供一个全局访问点。
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  G4cout<<"Using"<<analysisManager->GetType()<<G4endl;

  //打开ntuple 设置打印详情
  analysisManager -> SetVerboseLevel(1);
  analysisManager-> SetFileName(fileName);
  // analysisManager->SetFileType("root");
  analysisManager -> SetNtupleMerging(true);

  //定制 histograms 
  //自动排序 1DhistogramID=0
  analysisManager -> CreateH1 ("Guass_Pin","total energy/keV",400,0.,10.);
  // analysisManager -> CreateH1 ("BeamRadius_Pin","beamradius/um",1000,0.,(6.+0.5)*numberOfmonocapillaries*ooPhi);
  //1DhistogramID=1
  analysisManager -> CreateH1 ("BeamRadius_axis1","beamradius/um",1000,-VDDiameter*2000,VDDiameter*2000);
  //2DhistogramID=0
  analysisManager -> CreateH2 ("BeamPosition_Pin1","beamposition/um",
                                1000,-VDDiameter*2000,VDDiameter*2000,
                                1000,-VDDiameter*2000,VDDiameter*2000);

  // //1DhistogramID=2
  // analysisManager -> CreateH1 ("BeamRadius_axis2","beamradius/um",500,-VDDiameter/2*1000,VDDiameter/2*1000);
  // //2DhistogramID=1
  // analysisManager -> CreateH2 ("BeamPosition_Pin2","beamposition/um",
  //                               500,-VDDiameter/2*1000,VDDiameter/2*1000,
  //                               500,-VDDiameter/2*1000,VDDiameter/2*1000);

  // //1DhistogramID=3
  // analysisManager -> CreateH1 ("BeamRadius_axis3","beamradius/um",500,-VDDiameter/2*1000,VDDiameter/2*1000);
  // //2DhistogramID=2
  // analysisManager -> CreateH2 ("BeamPosition_Pin3","beamposition/um",
  //                               500,-VDDiameter/2*1000,VDDiameter/2*1000,
  //                               500,-VDDiameter/2*1000,VDDiameter/2*1000);

  // //1DhistogramID=4
  // analysisManager -> CreateH1 ("BeamRadius_axis4","beamradius/um",500,-VDDiameter/2*1000,VDDiameter/2*1000);
  // //2DhistogramID=3
  // analysisManager -> CreateH2 ("BeamPosition_Pin4","beamposition/um",
  //                               500,-VDDiameter/2*1000,VDDiameter/2*1000,
  //                               500,-VDDiameter/2*1000,VDDiameter/2*1000);

  // //1DhistogramID=5
  // analysisManager -> CreateH1 ("BeamRadius_axis5","beamradius/um",500,-VDDiameter/2*1000,VDDiameter/2*1000);
  // //2DhistogramID=4
  // analysisManager -> CreateH2 ("BeamPosition_Pin5","beamposition/um",
  //                               500,-VDDiameter/2*1000,VDDiameter/2*1000,
  //                               500,-VDDiameter/2*1000,VDDiameter/2*1000);

  // //1DhistogramID=6
  // analysisManager -> CreateH1 ("BeamRadius_axis6","beamradius/um",500,-VDDiameter/2*1000,VDDiameter/2*1000);
  // //2DhistogramID=5
  // analysisManager -> CreateH2 ("BeamPosition_Pin6","beamposition/um",
  //                               500,-VDDiameter/2*1000,VDDiameter/2*1000,
  //                               500,-VDDiameter/2*1000,VDDiameter/2*1000);
  G4cout << "root created - done" << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
OpNoviceRunAction::~OpNoviceRunAction() 
{
  delete G4AnalysisManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4Run* OpNoviceRunAction::GenerateRun()
{
  fRun = new OpNoviceRun();
  return fRun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void OpNoviceRunAction::BeginOfRunAction(const G4Run* run)
{
  if(fPrimary)
  {
    G4ParticleDefinition* particle =
      fPrimary->GetParticleGun()->GetParticleDefinition();
    G4double energy = fPrimary->GetParticleGun()->GetParticleEnergy();
    fRun->SetPrimary(particle, energy);
  }

  totalEvent = run -> GetNumberOfEvent();

  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager -> OpenFile(fileName);
  G4cout << "run test1" << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void OpNoviceRunAction::EndOfRunAction(const G4Run*)
{
  if(isMaster)
    fRun->EndOfRun();
  
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager -> Write();
  analysisManager -> CloseFile();
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
