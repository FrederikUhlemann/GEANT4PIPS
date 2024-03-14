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
/// \file Run.cc
/// \brief Implementation of the Run class
//  \based on the extended example rdecay02
//

#include "Run.hh"
#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"
#include "HistoManager.hh"

#include "G4ProcessTable.hh"
#include "G4Radioactivation.hh"
#include "G4TwoVector.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include <fstream>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

Run::Run(DetectorConstruction* det)
: G4Run(),
  fDetector(det), fParticle(0), fEkin(0.), fEdep(0.)
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

Run::~Run()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void Run::SetPrimary(G4ParticleDefinition* particle, G4double energy)
{
  fParticle = particle;
  fEkin = energy;
}





//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......




//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void Run::AddEdep(G4double edep1, G4double edep2)
{
  fEdepTarget  += edep1;
  fEdepTarget2 += edep1*edep1;
  fEdepDetect  += edep2;
  fEdepDetect2 += edep2*edep2;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void Run::EndOfRun()
{


//print out importand geometric information
  G4cout << "\n Case   :"
         << " Material = "
         << fDetector->GetCaseMaterial()->GetName();
  G4cout << "\n Detector : Radius = "
         << G4BestUnit(fDetector->GetDetectorRadius(),"Length")
         << " Thickness = "
         << G4BestUnit(fDetector->GetDetectorThickness(),"Length")
         << " Material = "
         << fDetector->GetDetectorMaterial()->GetName() << G4endl;
  G4cout << "\n EntranceWindow : Radius= "
         << G4BestUnit(fDetector->GetDetectorRadius(),"Length")
         << " Thickness = "
         << G4BestUnit(fDetector->GetEntranceWindowThickness(),"Length")
         << " Material = "
         << fDetector->GetDetectorMaterial()->GetName() << G4endl;
  G4cout << " Sample    : "
         << " x : "
         << G4BestUnit(fDetector->GetSampleX(),"Length")
         << " y : "
         << G4BestUnit(fDetector->GetSampleY(),"Length")
         << " Z : "
         << G4BestUnit(fDetector->GetSampleZ(),"Length")<< G4endl;



}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
