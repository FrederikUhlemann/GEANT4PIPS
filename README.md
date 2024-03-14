# GEANT4PIPS simulation project

GEANT4PIPS was created to provide a simple entry-level example for GEANT4.
The simulation is about a semiconductor detector.
The detector is a Passivated Implanted Planar Silicon (short PIPS) detector.
The detector measures especially the energy of alpha particles originating
from radioactive decay.

This project is based on the Geant4 Extended Example rdecay02 from Gabriele Cosmo.
https://gitlab.cern.ch/geant4/geant4/tree/edb408b5618b3b1cd3f40c5759aa5da4aa56bb7b/examples/extended/radioactivedecay/rdecay02


## How to start?


## 1. Install GEANT4 and ROOT
If you have not yet installed GEANT4 and ROOT you must do so first, instructions are provided in the wiki.



## 2. Start of first example runs
In the example, Radeon 219 is generated in the foil.
Execute pipsProject in 'interactive mode' with visualization :
```
./pipsProject
```
This will automatically execute the example.mac file. In which 10 radon 219 decays are simulated.
This is just to take a look on the geometry.

More scientific relevant data is simulated in 'batch' mode with the histoexample.mac file.
Execute pipsProject in 'batch' mode from macro files :
```
./pipsProject histoexample.mac
```
This now simulates 10000 radon 219 decays, this take maybe 10 seconds,
after that is make sense to run the histoPips file, see in wiki "More detailed information about GEANT4PIPS" to HISTOGRAMS
for detailed information.




	


