#ifndef MeasureBeamRadius_h
#define MeasureBeamRadius_h 1

#include "G4Track.hh"
#include "G4EventManager.hh"
#include "G4VVisManager.hh"
#include "G4OpticalPhoton.hh"

class MeasureBeamRadius
{
private:
    double beamRadius;
public:
    MeasureBeamRadius(/* args */);
    ~MeasureBeamRadius();
    void MeasureOpticalPhotonBeamRadius();
};

#endif