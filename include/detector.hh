#ifndef DETECTOR_HH
#define DETECTOR_HH

#include "G4VSensitiveDetector.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4Run.hh"
#include "G4VProcess.hh"
#include "globals.hh"
#include "G4AnalysisManager.hh"




class MySensitiveDetector : public G4VSensitiveDetector
{
public:
    MySensitiveDetector(G4String);
    ~MySensitiveDetector();

private:
    virtual G4bool ProcessHits(G4Step *, G4TouchableHistory *);
    virtual void 	Initialize(G4HCofThisEvent *);
    virtual void 	EndOfEvent(G4HCofThisEvent *);

    //G4PhysicsOrderedFreeVector *quEff;
};

#endif
