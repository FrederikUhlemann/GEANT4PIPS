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
/// \file PrimaryGeneratorAction.cc
/// \brief Implementation of the PrimaryGeneratorAction class
//  \based on the extended example rdecay02
//  \here is the starting information (position energy) of the particles defined
//
//

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "PrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4ParticleTable.hh"
#include "G4IonTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4Geantino.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

#include <cstdlib>
#include <time.h>
#include <random>
#include <cmath>

#include "DetectorConstruction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::PrimaryGeneratorAction(DetectorConstruction* det)
: G4VUserPrimaryGeneratorAction(),fParticleGun(0), fDetector(det)
{
  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);



  fParticleGun->SetParticleEnergy(0*eV);

  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//the goal is, that the particles starts randomly in like a circle or beam shape
//inside the AL foil
//because in the real experiment a low energy beam implants the radiocative
//nuclides in the foil

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//some c++ code to get random numbers, here is defined a individual seed,
//thats based on the current time, up to microseconds

  std::random_device rd;
    // seed value is designed specifically to make initialization
    // parameters of std::mt19937 (instance of std::mersenne_twister_engine<>)
    // different across executions of application
    std::mt19937::result_type seed = rd() ^ (
            (std::mt19937::result_type)
            std::chrono::duration_cast<std::chrono::seconds>(
                std::chrono::system_clock::now().time_since_epoch()
                ).count() +
            (std::mt19937::result_type)
            std::chrono::duration_cast<std::chrono::microseconds>(
                std::chrono::high_resolution_clock::now().time_since_epoch()
                ).count() );


    std::mt19937 gen(seed);

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//get the needed parameters from the DetectorConstruction class
   G4double d = (fDetector->GetBeamDiameter());
   G4double zSam = (fDetector->GetSampleZ());

// polar coordinates are used for the circle shape
// random angle phi from 0 to 2 pi
  std::uniform_real_distribution<double> distribphi(0,3.14159*2);
  //the radius is defined with a normal distribution, in order to make the
  //beam density higher in the center of it
  std::normal_distribution<double> distribr(0,d/2);
  //in z direction it is completely random where the beam implants
  //the nuclide in the foil
  std::uniform_real_distribution<double> distribZ(-zSam,zSam);

  G4double phi = (distribphi(gen));
  G4double r = abs((distribr(gen)));
  G4double z = (distribZ(gen));

// polar coordinates:
  G4double ux = r*std::cos(phi);
  G4double uy = r*std::sin(phi);
  fParticleGun->SetParticlePosition(G4ThreeVector(ux*mm,uy*mm,z*nm));

  //uncomment to set the z postion in the middle of the foil
  //fParticleGun->SetParticlePosition(G4ThreeVector(ux*mm,uy*mm,0*nm));

  //create vertex
  //
  fParticleGun->GeneratePrimaryVertex(anEvent);
  fParticleGun->GeneratePrimaryVertex(anEvent);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
