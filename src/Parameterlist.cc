#include "parameterlist.hh"
#include "G4SystemOfUnits.hh"

//
G4String Detector_name = "Detector";

G4String fileName = "Len_focus.root";

//Parametrs constructing X-Ray polycapillary lens
// G4String CXRPName;
G4double fullLenth = 47.0 * mm;       //透镜长度
G4double oiPhi = 13.9 * um;           //透镜入口外直径
G4double ooPhi = 21.6 * um;           //透镜出口外直径
G4double focalLenth = 55.0 * mm;      //光源到透镜处的距离
G4double diameterRadio = 0.8;         //直径比


G4double halfVDheight = 0.5 * mm;
G4double distanceVD1andVD2 = 40. * mm;
G4double inpinholeCollimatorDiamater = 3.9 * mm; 
G4double outpinholeCollimatorDiamater = 2*(numberOfmonocapillaries + 0.5 + (2*numberOfmonocapillaries + 1)*(numberOfLayer + 4))*ooPhi; 
G4double halfPinholeCollimatorHeight = 1. * mm;

//探测器距离
G4double secDistance = 20 * mm;
G4double thiDistance = 40 * mm; 
G4double forDistance = 60 * mm; 
G4double fitDistance = 80 * mm; 
G4double sixDistance = 100 * mm; 
G4double gapSize = 4 * mm;

//SolidSize
G4double worldhZ;
G4double worldhX = (numberOfmonocapillaries + 0.5 + (2*numberOfmonocapillaries + 1)*(numberOfLayer + 4))*ooPhi; 
G4double worldhY = (numberOfmonocapillaries + 0.5 + (2*numberOfmonocapillaries + 1)*(numberOfLayer + 4))*ooPhi; 


G4int numberOfLayer = 6;
G4int numOfEdges = 6;
int numberOfmonocapillaries = 15;
int n = 50;     //管子的长度截点

G4double VDDiameter = 3.7989*mm; 


