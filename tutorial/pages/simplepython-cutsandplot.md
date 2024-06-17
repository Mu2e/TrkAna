## Extracting a signal using python counting experiment

### Ensembles/Mock Data

In this tutorial you will use mock data samples to extract signal and background yields from a combined data sample and perform some basic physics analysis.

We will use "/pnfs/mu2e/tape/phy-nts/nts/mu2e/ensemble-1BB-CEDIOCRYCosmic-600000s-p95MeVc-Triggered/MDC2020ad_perfect_v1_3/tka/7d/c6/nts.mu2e.ensemble-1BB-CEDIOCRYCosmic-600000s-p95MeVc-Triggered.MDC2020ad_perfect_v1_3.0.tka".

This contatins a week of Mock Data at 1BB mode with CE, DIO and Cosmics. The signal rate is just below the current limit at 1e-13.

in the following example we rename the above file simply "pass0b.root" for ease.

### python basics

you should have the standard python packages installed for this example:  

* matplotlib, pyplot
* uproot
* awkward array
* numpy


### Extracting momentum

First import the relevant branch:

```
import uproot
import matplotlib.pyplot as plt
import awkward as ak
import numpy as np

filename = pass0b.root
trkana = uproot.open(filename:+":TrkAna/trkana")
array_TRK = trkana.arrays(filter_name="/demfit/")

```


### Applying cuts

The first set of basic cuts you should apply are:

1) "demfit.time" : [640., 1650], #inTimeWindow
2) "demfit_mom" : [103, 105] # to be optimized (use whatever you want here as a trial)

you want the magnitude of the momentum:

```
array_TRK['demfit_mom'] = np.sqrt((array_TRK['demfit']['mom']['fCoordinates']['fX'])**2 + (array_TRK['demfit']['mom']['fCoordinates']['fY'])**2 + (array_TRK['demfit']['mom']['fCoordinates']['fZ'])**2)

```

looking only at the tracker entrance fit:
```
trk_ent_mask = (array_TRK['demfit']['sid']==0)
```
build masks for cuts (NOTE THIS CAN BE DONE IN A MORE SOPHISTICATED WAY!!!)

```
time_cut_mask_min = (array_TRK['demfit']['time']>= 640)
time_cut_mask_max = (array_TRK['demfit']['time']< 1650)
```

you can add similar masks for other cuts. Now apply the filters:

```
mom_np = np.array(ak.flatten(array_TRK[  (trk_ent_mask) & (time_cut_mask_max) & (time_cut_mask_min) & ....add in you other masks here too ....  ]['demfit_mom'], axis=None))
```

For a cutflow you can look into the masks, see how many True and False fields there are.

### Extracting a signal

What you have above is a numpy array which you can then play with for analysis (with all cuts applied).

To plot:

```
ax.hist(ak.flatten(array_TRK[  (trk_ent_mask) & (time_cut_mask_max) & (time_cut_mask_min) & ....add in you other masks here too ....  ]['demfit_mom'], axis=None), bins=100, range=(95,110), label='ent fits', histtype='step')

ax.set_xlabel('Reconstructed Momentum at Tracker Entrance [MeV/c]')
ax.set_ylabel('Number of Tracks')
ax.legend()
ax.grid(True)
plt.show()
```

