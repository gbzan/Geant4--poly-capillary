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
#include "G4EventManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4VHitsCollection.hh"
#include "G4SDManager.hh"
#include "G4RunManager.hh"
#include "Analysis.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "OpNoviceRunAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
OpNoviceEventAction::OpNoviceEventAction(OpNoviceRunAction* runAction)
  : G4UserEventAction(),
  fRunAction(runAction),
  fEdep(0.),
  fDHC1ID(-1)
{
  fRayleigh   = 0;
  fAbsorption = 0;
  fMie        = 0;
  fBoundary   = 0;
  counts = 0;
  particle = 0;

  totalParticle = fRunAction -> GetTotalEvent();
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
  fRunAction -> AddCount();

  //获取hitcollectionID fDH1ID
  if (fDHC1ID==-1)
  {
    G4SDManager* sdManager = G4SDManager::GetSDMpointer();
    fDHC1ID = sdManager->GetCollectionID("TrackerChamberSD/TrackerHitsCollection");//SDName/HitsCollectionName
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void OpNoviceEventAction::EndOfEventAction(const G4Event* event)
{
  OpNoviceRun* run = static_cast<OpNoviceRun*>(
    G4RunManager::GetRunManager()->GetNonConstCurrentRun());
  run->AddRayleigh(fRayleigh);
  run->AddAbsorption(fAbsorption);
  run->AddMie(fMie);
  run->AddBoundary(fBoundary);

  //event结束 从hitcollection中读取数据

  //获取hitcollection集合G4HCofthisEvent的指针
  G4HCofThisEvent* hce = event->GetHCofThisEvent();

  //判断当前是否已经存在了hce指针
  if (!hce)
  {
    G4ExceptionDescription msg;
        msg << "No hits collection of this event found.\n"; 
        G4Exception("OpNoviceEventAction::EndOfEventAction()",
                    "Code001", JustWarning, msg);
        return;
  }

  //通过G4HCofThisEvent的指针hce 和hitcollection的ID号 fDH1ID去获取到该hitcollection的指针dHC1
  //TrackerHitsCollection类型在B1SDHit中通过typedef去定义
  TrackerHitsCollection* dHC1 = static_cast<TrackerHitsCollection*>(hce->GetHC(fDHC1ID));

  //判断是否已经存在了hitcollection的指针
  if(!dHC1)
  {
    G4ExceptionDescription msg;
        msg << "Some of hits collections of this event not found.\n"; 
        G4Exception("OpNoviceEventAction::EndOfEventAction()",
                    "Code001", JustWarning, msg);
        return;
  }

  //从hitcollection中获取数据并且填入定义的histogram中
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  //entries函数记录的命中的数量
  G4int n_hit1 = dHC1->entries();
  //G4int flg_trackID = -1;

  //获取数据并填写
  for (G4int i=0 ; i<n_hit1;i++)
  {
    //通过hit类对象的指针获取hitcollection中的数据
    TrackerHit* hit1 = (*dHC1)[i];
    G4double fEnergy = hit1 -> GetEdep();
    G4ThreeVector position = hit1 -> GetPos();
    

    analysisManager->FillH1(0, fEnergy/keV);
     analysisManager->FillH1(1, position.x()*1000);
    // analysisManager->FillH1(2, outenergy3/keV);
    analysisManager->FillH2(0, position.x()*1000, position.y()*1000);
  }
  
  if((fRunAction->GetCount())%320000 == 0)
  {
    fRunAction->AddFlag();
    G4cout << fRunAction->GetFlag() << "%" << G4endl;
  }
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
