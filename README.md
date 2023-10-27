# Geant4--poly-capillary
Simulation of poly-capillary
This is a code that bases on GEANT4 Plane to simulate X-Ray Transportation in poly-capillary

 if use StepAction to statistics data in the process of simulation, just SetUserAction(your StepAction*) and Comment out the fuction ConstructSDandField() in OpNoviceDetectorConstruction.

AirAbsLengtht.txt: includes data of X-Ray Absorption Length in air material.

Pyrex_refraction_beta.txt: includes data of IMAGINARYRINDEX of Complex index of refraction in Pyrex glass.

Pyrex_refraction_dalta.txt: includes data of delta of Complex index of refraction, REALRINDEX=1-delta in Pyrex glass.

PyrexAbsLength.txt: includes data of X-Ray Absorption Length in Pyrex glass.
