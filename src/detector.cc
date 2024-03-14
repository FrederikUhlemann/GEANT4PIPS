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
/// \brief Implementation of the detector class
// \this class manages the information collection,
// \of the sensitive silicium detector plane
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#include "detector.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......



MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{

}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
MySensitiveDetector::~MySensitiveDetector()
{}

void MySensitiveDetector::Initialize(G4HCofThisEvent *)
{

}

void MySensitiveDetector::EndOfEvent(G4HCofThisEvent *)
{

}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//the ProcessHits function is called, when a particle reaches
//the detector surface
G4bool MySensitiveDetector::ProcessHits(G4Step *aStep,
                                        G4TouchableHistory *ROhist)
{
  //get the specific track
  G4Track *track = aStep->GetTrack();
  //when particle reached the detector surface,this track is deleted
  //track->SetTrackStatus(fStopAndKill);
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


  //get the beginning and end point of this step
  G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
  G4StepPoint *postStepPoint = aStep->GetPreStepPoint();

  //get the position were the particle hits the detector
  G4ThreeVector posParticle = preStepPoint->GetPosition();
  //get the energy loss, that the particle loses via ionisation in the silicium
  G4double edepStep = aStep->GetTotalEnergyDeposit();

  //in "name" is the particle name of the particle that hits the detector,
  //of course this is not an measurable data in a real experiment
  const G4ParticleDefinition* particle = track->GetParticleDefinition();
  G4String name   = particle->GetParticleName();

  //uncomment to print out the data for debugging
  //G4cout <<"Pos: " <<posParticle <<G4endl;
  //G4cout <<"Energy: " <<energy+edepStep <<G4endl;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

if (name == "alpha") {
  //save all this data via the G4AnalysisManager, espacially in this program
  //the data is stored in a .root file
  G4AnalysisManager* man = G4AnalysisManager::Instance();
  man->FillNtupleSColumn(0,name);
  man->FillNtupleDColumn(1,edepStep);
  man->FillNtupleDColumn(2,posParticle[0]);
  man->FillNtupleDColumn(3,posParticle[1]);
  man->FillNtupleDColumn(4,posParticle[2]);
  man->AddNtupleRow(0);

//G4cout<<name<<"\t"<<edepStep<<G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

return 0;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
