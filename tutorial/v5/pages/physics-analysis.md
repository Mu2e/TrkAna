## Extracting a signal using RooFit

### Ensembles/Mock Data

In this tutorial you will use mock data samples to extract signal and background yields from a combined data sample and perform some basic physics analysis.

We will use "/pnfs/mu2e/tape/phy-nts/nts/mu2e/ensemble-MixBB-CEDIO-1month-p95MeVc-Triggered/MDC2020ad_perfect_v1_2/tka/18/96/nts.mu2e.ensemble-MixBB-CEDIO-1month-p95MeVc-Triggered.MDC2020ad_perfect_v1_2.0.tka".

The exact details of this sample are: https://mu2ewiki.fnal.gov/wiki/MDC2024:_Mock_Data#Mock-Dataset-0_.28MDS0.29_.2895_MeV.2Fc.29 (pass0a). 

This contatins 2 days of Mock Data at 1BB mode with CE, DIO (no cosmics and pileup). The signal rate is just below the current limit at 1e-13.

### Plotting momentum

We will carry out a binned maximum likelihood fit.

Set up a ROOT C macro called Mu2e-fitter.C. Add the following includes:

```
#include <iostream>
#include "TSystem.h"
#include "TROOT.h"
#include "TFile.h"
#include "TH1.h"
```
Make a function called Mu2e-fitter():

Start by plotting the reconstructed momentum:
```
int Mu2e-fitter(){
  TH1F* hist_mom1 = new TH1F("hist_mom1", "", 100, 95, 115);
  trkana->Draw("demfit.mom.R()", recocuts, "HIST");
  return 0;
}
```

run this with the following:

```
root -l Mu2e-fitter.C
```

what you see will be a distribution of ALL track momenta (meaning three points per track).
  

### Applying cuts

For the best chances of finding a signal which we can extract we should add some cuts:

```
TH1F* hist_mom1 = new TH1F("hist_mom1", "", 100, 95, 115);
TString recocuts = "demfit.sid==0 && demlh.t0 > 700 && demlh.t0err < 0.9 && demtrkqual.result > 0.2 && dem.nactive > 20 && demlh.maxr < 680";
trkana->Draw("demfit.mom.R()>>hist_mom1", recocuts, "HIST");
```

Here's what these mean:

* demfit.sid==0 : fit at tracker entrance i.e. were there will be minimal distortions from interactions in the tracker
* demlh.t0 > 640 : arrival fit time cut
* demlh.t0err < 0.9 : cut on error of the time fit
* demtrkqual.result > 0.2 : a cut on the ML trkqual variable
* dem.nactive > 20 : a cut on number of active hits in the fit
* demlh.maxr < 680 : a cut on the maximum track radius

We should add some more cuts e.g. PID requirements as things get more sophisicated.

We do not apply the CRV cuts in this example, hence chosing to fit to a sample which does not include cosmics. The CRV cuts are more complicated.
