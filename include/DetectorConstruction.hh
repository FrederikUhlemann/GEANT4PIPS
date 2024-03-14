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
/// \file DetectorConstruction.hh
/// \brief Definition of the DetectorConstruction class
//
//

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"

class G4LogicalVolume;
class G4Material;
class DetectorMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:

    DetectorConstruction();
   ~DetectorConstruction();

  public:

    virtual G4VPhysicalVolume* Construct();

    void SetTargetLength (G4double value);
    void SetTargetRadius (G4double value);
    void SetCaseMaterial (G4String);

    void SetDetectorRadius(G4double value);
    void SetDetectorThickness(G4double value);
    void SetDetectorMaterial(G4String);

    void PrintParameters();

  public:

    G4double GetTargetLength();
    G4double GetTargetRadius();
    G4Material* GetCaseMaterial();
    G4LogicalVolume* GetLogicCase();

    G4double GetDetectorRadius();
    G4double GetDetectorThickness();
    G4double GetEntranceWindowThickness();
    G4Material* GetDetectorMaterial();
    G4LogicalVolume* GetLogicDetector();

    G4double GetSampleX();   //Return the sample geometry, because it is needed in thei
    G4double GetSampleY();   //PrimaryGeneratorAction to generate particles inside Sample randomly
    G4double GetSampleZ();
    G4double GetBeamDiameter();


  private:

    //Case attributes
    G4double           fCaseRadius;
    G4double           fCaseLength;
    G4Material*        fCaseMater;
    G4LogicalVolume*   fLogicCase;
    G4LogicalVolume*   fLogicCaseBack;
    G4LogicalVolume*   fLogicCasePort;
    G4LogicalVolume*   fSpacer;
    G4LogicalVolume*   fHolder;



    // detectorplane and EntranceWindow attributes
    G4double           fDetectorRadius;
    G4double           fDetectorThickness;
    G4double           fEntranceWindowThickness;
    G4Material*        fDetectorMater;
    G4LogicalVolume*   fEntranceWindow;
    G4LogicalVolume*   fLogicDetector;
    virtual void ConstructSDandField();          //For Senstive Detector



    //Sample attributes
    G4double fSampleX;
    G4double fSampleY;
    G4double fSampleZ;
    G4LogicalVolume* fSample;

    G4double fBeamDiameter;

    G4Material* fPTFE;
    G4Material* fPEEK;

    G4double OuterSpacer;
    G4double InnerSpacer;
    G4double SpacerThickness;
    G4double OuterHolder;
    G4double InnerHolder;
    G4double HolderThickness;





    //world attributes
    G4double           fWorldLength;
    G4Material*        fWorldMater;
    G4VPhysicalVolume* fPhysiWorld;

    DetectorMessenger* fDetectorMessenger;

  private:

    void               DefineMaterials();
    G4VPhysicalVolume* ConstructVolumes();
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


#endif
