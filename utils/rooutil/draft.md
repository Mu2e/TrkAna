# RooUtil (draft)

RooUtil is a utility class to help analyze EventNtuple in ROOT-based analysis frameworks.

It is currently under development and the available branches are listed [below](#Supported-Branches)

## Classes
There are various classes that combine together branches at different dimenions

| Class | Single Objects | Vectors | Vector-of-Vectors |
|-----|-----|----|-----|
| Event | ```evtinfo```, ```evtinfomc``` | ```trk``` | ```trkfit``` |
| Track | ```trk``` | ```trksegs``` | none |
| TrackSegment | ```trkseg``` | none | none |

## Supported Branches
The currently supported branches are:
* evtinfo, evtinfomc
* trk
* trksegs

## Cut Functions

### Common Cut Functions

Here are the common cut functions defined in ```TrkAna/utils/rooutil/inc/common_cuts.hh``` with explanations:

| function | cuts on | result |
|----|----|----|
|```is_e_minus``` | tracks | true if e-minus hypothesis |
|```is_e_plus``` | tracks | true if e-plus hypothesis |
|```is_mu_minus``` | tracks | true if mu-minus hypothesis |
|```is_mu_plus``` | tracks | true if mu-plus hypothesis |
|```tracker_entrance``` | track segments | true if track segment is at tracker entrance |
|```tracker_middle``` | track segments | true if track segment is at tracker middle |
|```tracker_exit``` | track segments | true if track segment is at tracker exit |

### Combining Cut Functions

There are two ways to combine cut functions:

1. Write a new one yourself e.g:

```
bool my_cut(onst Track& track) {
   return good_track(track) && is_e_minus(track);
}
...
int n_e_minus_good_tracks = event.CountTracks(my_cut);
```

2. or, be combine them in a [lambda function](https://learn.microsoft.com/en-us/cpp/cpp/lambda-expressions-in-cpp?view=msvc-170) (similar to python):

```
int n_e_minus_good_tracks = event.CountTracks([](const Track& track){ return is_e_minus(track) && good_track(track); });
```
