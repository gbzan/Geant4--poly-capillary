#ifndef PHYSISCLIST_h
#define PHYSISCLIST_h 1

#include <CLHEP/Units/SystemOfUnits.h>

#include "globals.hh"
#include "G4VModularPhysicsList.hh"

class G4VPhysicsConstructor;
class PhysicsListMessenger;


class PhysiscList: public G4VModularPhysicsList
{
private:
    /* data */
public:
    PhysiscList( G4int ver = 1);
    virtual ~PhysiscList();

};
#endif