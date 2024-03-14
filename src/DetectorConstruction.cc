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
/// \file DetectorConstruction.cc
/// \brief Implementation of the DetectorConstruction class
//  \based on the extended example rdecay02
//

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


#include "DetectorConstruction.hh"
#include "DetectorMessenger.hh"

#include "G4Material.hh"
#include "G4Element.hh"
#include "G4NistManager.hh"

#include "G4Tubs.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4RunManager.hh"
#include "G4SubtractionSolid.hh"
#include "G4UnionSolid.hh"

#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4UnitsTable.hh"

#include "detector.hh"
#include "G4SDManager.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// This is the constructor-function of the DetectorConstruction-class
DetectorConstruction::DetectorConstruction()
:G4VUserDetectorConstruction(),
 fCaseMater(0), fLogicCase(0),fLogicCaseBack(0),fLogicCasePort(0),
 fDetectorMater(0),fEntranceWindow (0), fSample(0),
 fWorldMater(0), fPhysiWorld(0), fSpacer(0),fHolder(0), fPTFE(0), fPEEK(0),
 fDetectorMessenger(0)
{
  //assignment of geomatric values of the PIPs detector

  //variables for the Case
  fCaseRadius  = 11.8*mm;
  fCaseLength    = 13.5*mm;

  //variables for the SI detector-plane
  fDetectorRadius    = 6.9*mm;
  fDetectorThickness = 0.15*mm;
  fEntranceWindowThickness = 1.5*um;


  //variables for the construction that is in front of the detector
  OuterSpacer = 32*mm;
  InnerSpacer = 20*mm;
  SpacerThickness = 2*mm;

  OuterHolder = 32*mm;
  InnerHolder = 8*mm;
  HolderThickness = 2*mm;


  //size ot the Geant4 world
  fWorldLength = 10.*cm;

  //the sample is a aluminium foil, the foil is in front of the detector
  fSampleX  = 5.*mm;
  fSampleY  = 5.*mm;
  fSampleZ  = 37.5*nm;

  //average BeamDiameter
  fBeamDiameter = 2*mm;


  DefineMaterials();

  fDetectorMessenger = new DetectorMessenger(this);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction()
{ delete fDetectorMessenger;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  return ConstructVolumes();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//in this function all needed materials are defined
void DetectorConstruction::DefineMaterials()
{

  G4NistManager* man = G4NistManager::Instance();
  //vacuum is used for the world-medium, in GEANT4 there is the "Galactic"
  //material, this is almost vaccum
  fWorldMater = man->FindOrBuildMaterial("G4_Galactic");


  //some basic elemnts are needed
  G4Element* elH  = new G4Element("Hydrogen",               //its name
                                  "H",                     //its symbol
                                  1.,                      //atomic number
                                  1.01*g/mole);             //mass of mole

  fCaseMater = new G4Material("Aluminium", 13, 26.982*g/mole, 2.6989*g/cm3);

  fDetectorMater = new G4Material("Silicium", 14, 28.085*g/mole, 2.3212*g/cm3);


  G4Element* elO =
  new G4Element("Oxygen","O",8.,15.9994*g/mole);

  G4Element* elC =
  new G4Element("Carbon","C",12.,12.0107*g/mole);

  G4Element* elF =
  new G4Element("Fluor","F",9.,9*g/mole);

  G4Element* elN =
  new G4Element("Nitrogen","N",7.,14.01*g/mole);

  G4Material* Air = new G4Material("Air",0.1*mg/cm3,2);
  Air->AddElement(elN, 0.7);
  Air->AddElement(elO, 0.3);


// PEEK and PTFE are some special materials for the spacer and holder
fPEEK = new G4Material("PEEK",
                                  1.32*g/cm3,   //density
                                  3);           //number of elemnts
fPEEK->AddElement(elC,0.56);                    //percentage of single elements
fPEEK->AddElement(elH,0.35);
fPEEK->AddElement(elO, 0.09);

fPTFE = new G4Material("PTFE",
                                  2.2*g/cm3,
                                  2);
fPTFE->AddElement(elF, 0.67);
fPTFE->AddElement(elC, 0.33);


 ///G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//function to construct all needed volumes
G4VPhysicalVolume* DetectorConstruction::ConstructVolumes()
{
  // Cleanup old geometry
  G4GeometryManager::GetInstance()->OpenGeometry();
  G4PhysicalVolumeStore::GetInstance()->Clean();
  G4LogicalVolumeStore::GetInstance()->Clean();
  G4SolidStore::GetInstance()->Clean();

  // World
  //
  // (re) compute World dimensions if necessary


  G4Box*
  sWorld = new G4Box("World",                                    //name
            0.5*fWorldLength,0.5*fWorldLength,0.5*fWorldLength); //dimensions

  G4LogicalVolume*
  lWorld = new G4LogicalVolume(sWorld,                  //shape
                             fWorldMater,               //material
                             "World");                  //name

  fPhysiWorld = new G4PVPlacement(0,                    //no rotation
                            G4ThreeVector(),            //at (0,0,0)
                            lWorld,                     //logical volume
                            "World",                    //name
                            0,                          //mother volume
                            false,                      //no boolean operation
                            0);                         //copy number
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
  // DetectorCase
  //
  G4Tubs*
  sCase = new G4Tubs("Case",                                   //name
        fDetectorRadius,fCaseRadius, fCaseLength/2, 0.,twopi); //dimensions


  fLogicCase = new G4LogicalVolume(sCase,             //shape
                             fCaseMater,              //material
                             "Case");                 //name

           new G4PVPlacement(0,                       //no rotation
                           G4ThreeVector(0.,0.,(fCaseLength/2)+4*mm+fSampleZ),
                           fLogicCase,                //logical volume
                           "Case",                    //name
                           lWorld,                    //mother  volume
                           false,                     //no boolean operation
                           0);                        //copy number


G4Tubs*
sCaseBack = new G4Tubs("CaseBack",                           //name
                   0., fDetectorRadius, 0.001*mm, 0.,twopi); //dimensions


fLogicCaseBack = new G4LogicalVolume(sCaseBack,           //shape
                                 fCaseMater,              //material
                                 "CaseBack");             //name

new G4PVPlacement(0,                             //no rotation
                  G4ThreeVector(0.,0.,fCaseLength+4*mm+fSampleZ),
                  fLogicCaseBack,               //logical volume
                  "CaseBack",                   //name
                  lWorld,                       //mother  volume
                  false,                        //no boolean operation
                  0);                           //copy number


G4Tubs*
sCasePort = new G4Tubs("CasePort",                //name
                      0., 4*mm, 4*mm, 0.,twopi); //dimensions

fLogicCasePort = new G4LogicalVolume(sCasePort,          //shape
                                fCaseMater,              //material
                                "CasePort");             //name

new G4PVPlacement(0,                             //no rotation
                  G4ThreeVector(0.,0.,fCaseLength+6*mm+fSampleZ),
                  fLogicCasePort,                //logical volume
                  "CasePort",                    //name
                  lWorld,                        //mother  volume
                  false,                         //no boolean operation
                  0);                            //copy number


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// EntranceWindow of to Detector
G4Tubs*
sEntranceWindow = new G4Tubs("EntranceWindow",
                    0., fDetectorRadius, fEntranceWindowThickness, 0.,twopi);


fEntranceWindow = new G4LogicalVolume(sEntranceWindow ,      //shape
                                  fDetectorMater,            //material
                                  "EntranceWindow");         //name

new G4PVPlacement(0,                         //no rotation
                G4ThreeVector(0.,0.,7*mm-fEntranceWindowThickness/2 + fSampleZ),
                fEntranceWindow,             //logical volume
                "EntranceWindow",            //name
                lWorld,                      //mother  volume
                false,                       //no boolean operation
                0);                          //copy number


// Detector plane
//
G4Tubs*
sDetector = new G4Tubs("Detector",
                0., fDetectorRadius, fDetectorThickness, 0.,twopi);


fLogicDetector = new G4LogicalVolume(sDetector,         //shape
                             fDetectorMater,            //material
                             "logicDetector");          //name

new G4PVPlacement(0,                              //no rotation
                           G4ThreeVector(0.,0.,7*mm+fDetectorThickness/2
                           + fSampleZ),
                           fLogicDetector,         //logical volume
                           "physDetector",         //name
                           lWorld,                 //mother  volume
                           false,                  //no boolean operation
                           0);                     //copy number

G4SDManager* sdManager = G4SDManager::GetSDMpointer();
sdManager->AddNewDetector(new MySensitiveDetector("SensitiveDetector"));
MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");
SetSensitiveDetector(fLogicDetector, sensDet);
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// AL Foil
//
G4Box*
sSample = new G4Box("Sample",                              //name
               fSampleX,fSampleY,fSampleZ);                //dimensions;


fSample = new G4LogicalVolume(sSample,                     //shape
                                    fCaseMater,            //material
                                    "Sample");             //name

new G4PVPlacement(0,                                       //no rotation
                  G4ThreeVector(0.,0.,0.),                 //at (0,0,0)
                  fSample,                                 //logical volume
                  "Sample",                                //name
                  lWorld,                                  //mother  volume
                  false,                                   //no boolean operation
                  0);                                      //copy number





//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//PTFE spacer
G4Box*
sOuterSpacer = new G4Box("OuterSpacer",
                    OuterSpacer/2,OuterSpacer/2, SpacerThickness/2);

G4Box*
sInnerSpacer = new G4Box("InnerSpacer",
                   InnerSpacer/2,InnerSpacer/2, SpacerThickness);

//the subtraction of the outer and inner sapacer delivers a cuboid with a hole
G4VSolid *sSpacer = new G4SubtractionSolid("Spacer", sOuterSpacer,sInnerSpacer);

fSpacer = new G4LogicalVolume(sSpacer,                //shape
                                    fPTFE,            //material
                                    "LogicSpacer");   //name

new G4PVPlacement(0,                                 //no rotation
                  G4ThreeVector(0.,0.,3*mm+fSampleZ),
                  fSpacer,                           //logical volume
                  "physSpacer",                      //name
                  lWorld,                            //mother  volume
                  false,                             //no boolean operation
                  0);                                //copy number


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//PEEK Holder
G4Box*
sOuterHolder = new G4Box("OuterHolder",
                   OuterHolder/2,OuterHolder/2, HolderThickness/2);
G4Tubs*
sInnerHolder = new G4Tubs("InnerHolder",
                         0., InnerHolder/2, HolderThickness, 0.,twopi);

G4VSolid* sHolder = new G4SubtractionSolid("Holder", sOuterHolder,sInnerHolder);

fHolder = new G4LogicalVolume(sHolder,                //shape
                                    fPEEK,            //material
                                    "LogicHolder");   //name

new G4PVPlacement(0,                                 //no rotation
                  G4ThreeVector(0.,0.,1*mm+fSampleZ),
                  fHolder,                           //logical volume
                  "physHolder",                      //name
                  lWorld,                            //mother  volume
                  false,                             //no boolean operation
                  0);                                //copy number




  PrintParameters();

  //always return the root volume
  //
  return fPhysiWorld;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//Construct a SensitiveDetector, to collect later the energy-data
void DetectorConstruction::ConstructSDandField()
{


}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::PrintParameters()
{

  G4cout << " Case Material = " << fCaseMater->GetName();
  G4cout << "\n Detector : Radius = " << G4BestUnit(fDetectorRadius,"Length")
         << " Tickness = " << G4BestUnit(fDetectorThickness,"Length")
         << " Material = " << fDetectorMater->GetName() << G4endl;
  G4cout << "\n EntranceWindow : Radius = " << G4BestUnit(fDetectorRadius,"Length")
         << " Tickness = " << G4BestUnit(fEntranceWindowThickness,"Length")
         << " Material = " << fDetectorMater->GetName() << G4endl;
  G4cout << "\n" << fCaseMater << "\n" << fDetectorMater << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


void DetectorConstruction::SetDetectorMaterial(G4String materialChoice)
{
  // search the material by its name
  G4Material* pttoMaterial =
     G4NistManager::Instance()->FindOrBuildMaterial(materialChoice);

  if (pttoMaterial) {
    fDetectorMater = pttoMaterial;
    if(fLogicDetector) { fLogicDetector->SetMaterial(fDetectorMater); }
    G4RunManager::GetRunManager()->PhysicsHasBeenModified();
  } else {
    G4cout << "\n--> warning from DetectorConstruction::SetDetectorMaterial : "
           << materialChoice << " not found" << G4endl;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


//functions to chance some properties of the detector, without a recompile of
//the whole project
void DetectorConstruction::SetDetectorThickness(G4double value)
{
  fDetectorThickness = value;
  G4RunManager::GetRunManager()->ReinitializeGeometry();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetDetectorRadius(G4double value)
{
 fDetectorRadius = value;
  G4RunManager::GetRunManager()->ReinitializeGeometry();
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//functions to get detector properties outside of the DetectorConstruction class

G4Material* DetectorConstruction::GetCaseMaterial()
{
  return fCaseMater;
}

G4double DetectorConstruction::GetSampleX()
{
  return fSampleX;
}

G4double DetectorConstruction::GetSampleY()
{
  return fSampleY;
}

G4double DetectorConstruction::GetSampleZ()
{
  return fSampleZ;
}

G4double DetectorConstruction::GetBeamDiameter()
{
  return fBeamDiameter;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4LogicalVolume* DetectorConstruction::GetLogicCase()
{
  return fLogicCase;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4double DetectorConstruction::GetDetectorRadius()
{
  return fDetectorRadius;
}

G4double DetectorConstruction::GetEntranceWindowThickness()
{
  return fEntranceWindowThickness;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4double DetectorConstruction::GetDetectorThickness()
{
  return fDetectorThickness;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Material* DetectorConstruction::GetDetectorMaterial()
{
  return fDetectorMater;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4LogicalVolume* DetectorConstruction::GetLogicDetector()
{
  return fLogicDetector;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
