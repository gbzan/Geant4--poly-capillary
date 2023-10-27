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
/// \file OpNovice/include/OpNoviceDetectorConstruction.hh
/// \brief Definition of the OpNoviceDetectorConstruction class
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef OpNoviceDetectorConstruction_h
#define OpNoviceDetectorConstruction_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4SDManager.hh"
#include "TrackerSD.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class OpNoviceDetectorMessenger;
class G4VPhysicalVolume;
class G4LogicalVolume;
class G4Material;
class G4Tubs;
class G4UnionSolid;
class G4PVPlacement;
class G4ExtrudedSolid;
class G4MaterialPropertiesTable;

class OpNoviceDetectorConstruction : public G4VUserDetectorConstruction
{
 public:
  OpNoviceDetectorConstruction();
  ~OpNoviceDetectorConstruction();

  G4VPhysicalVolume* Construct() override;
  void ConstructSDandField() override;

  void SetDumpGdml(G4bool);
  G4bool IsDumpGdml() const;
  void SetVerbose(G4bool verbose);
  G4bool IsVerbose() const;
  void SetDumpGdmlFile(G4String);
  G4String GetDumpGdmlFile() const;

  G4LogicalVolume* GetScoringVolume() const { return fScoringVolume; }

  //cubic function  t is Ck,ij, phi1 is out-diameter at entrance, 
  //phi2 is out-diameter at exit, f is focal lenth, 
  //L is polycapillary lens' lenth
  // void CopyParameters(G4double t, G4double phi1, G4double phi2, G4double f ,G4double L );
  G4double CubicFunction(G4double z);
  G4double SlopeCubicFunction(G4double z);
  void DefineMaterials();
  G4VPhysicalVolume* CXRP();

 private:
  void PrintError(G4String);

  G4LogicalVolume*  fScoringVolume = nullptr; 

  G4Material*       fLensMaterial = nullptr;  // pointer to the target  material
  G4Material*       fWorldMaterial = nullptr; // pointer to the chamber material
  G4Material*       fDetector = nullptr;
  G4Material*       fpinholeCollimatorMaterial = nullptr;


  // G4Tubs* cylinder1 = nullptr;
  // G4Tubs* cylinder2 = nullptr;
  // G4Tubs** microTubs = nullptr;
  // G4UnionSolid* combinedCylinder = nullptr;
  // G4LogicalVolume* CombinedCylinderLV = nullptr;
  // G4LogicalVolume** TubsLV = nullptr;
  // G4PVPlacement* CombinedCylinderPV = nullptr;

  // G4MaterialPropertiesTable* AirMPT1 = nullptr;
  // G4MaterialPropertiesTable* PyrexMPT1 = nullptr;

  OpNoviceDetectorMessenger* fDetectorMessenger = nullptr;
  G4String fDumpGdmlFileName;

  G4double fWorld_x;
  G4double fWorld_y;
  G4double fWorld_z;

  G4double fExpHall_x;
  G4double fExpHall_y;
  G4double fExpHall_z;

  G4double fTank_x;
  G4double fTank_y;
  G4double fTank_z;

  G4double fBubble_x;
  G4double fBubble_y;
  G4double fBubble_z;
  
  G4double semiAxisX1;
  G4double semiAxisY1;
  G4double semiAxisZ1;

  G4double semiAxisX2;
  G4double semiAxisY2;
  G4double semiAxisZ2;
  
  G4bool fVerbose;
  G4bool fDumpGdml;
  G4bool fCheckOverlaps = true;
  // G4double 
  // G4double

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif /*OpNoviceDetectorConstruction_h*/
