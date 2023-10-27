#ifndef Parameterlist_h
#define Parameterlist_h 1

#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "globals.hh"
#include "tls.hh"


extern G4String Detector_name;
extern G4String fileName;

  //Parametrs constructing X-Ray polycapillary lens
  // G4String CXRPName;
extern G4double fullLenth;
extern G4double oiPhi;
extern G4double ooPhi;
extern G4double focalLenth;
extern G4double diameterRadio;
extern G4double VDDiameter;
extern G4double distanceVD1andVD2;
extern G4double halfVDheight;
extern G4double inpinholeCollimatorDiamater;
extern G4double outpinholeCollimatorDiamater;
extern G4double halfPinholeCollimatorHeight;
extern G4double secDistance;
extern G4double thiDistance; 
extern G4double forDistance; 
extern G4double fitDistance; 
extern G4double sixDistance;
extern G4double gapSize;

extern G4double worldhZ,worldhX,worldhY;

extern int n;
extern int numberOfmonocapillaries;
extern G4int numberOfLayer;
extern G4int numOfEdges;
#endif