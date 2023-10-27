#include <iomanip>   

#include "globals.hh"

#include "G4StoppingPhysics.hh"
#include "../include/EmStandardPhysics_option4.hh"
#include "../include/G4OpticalPhysics.hh"


#include "../include/PhysiscList.hh"


PhysiscList::~PhysiscList()
{}


PhysiscList::PhysiscList(G4int ver)
{
    if(ver > 0) {
        G4cout << "<<< Geant4 Physics List simulation engine: HQF_OPTION1"<<G4endl;
        G4cout <<G4endl;
    }
    defaultCutValue = 0.1*CLHEP::mm;  
    SetVerboseLevel(ver);
    
    RegisterPhysics( new EmStandardPhysics_option4(ver));
    RegisterPhysics( new G4OpticalPhysics(ver));
}


