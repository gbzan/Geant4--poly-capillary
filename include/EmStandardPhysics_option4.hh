//---------------------------------------------------------------------------
//
// ClassName:   EmStandardPhysics_option4
//
// Author:      V.Ivanchenko 28.09.2012
//
// Modified:
//
//----------------------------------------------------------------------------
//
// This class provides construction of EM physics using the best models
// of standard and low-energy packages and set of 
// the most adavced options allowing precise simulation at low
// and intermediate energies
//

#ifndef EmStandardPhysics_option4_h
#define EmStandardPhysics_option4_h 1

#include "G4VPhysicsConstructor.hh"
#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class EmStandardPhysics_option4 : public G4VPhysicsConstructor
{
public:

  explicit EmStandardPhysics_option4(G4int ver=1, const G4String& name="");

  ~EmStandardPhysics_option4() override;

  void ConstructParticle() override;
  void ConstructProcess() override;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif






