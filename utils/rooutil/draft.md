# RooUtil (draft)

RooUtil is a utility class to help analyze EventNtuple in ROOT-based analysis frameworks.

It is currently under development and the available branches are listed [below](#Supported-Branches)

## Classes
There are various classes that combine together branches at different dimenions

| Class | Single Objects | Vectors | Vector-of-Vectors |
|-----|-----|----|-----|
| Event | ```evtinfo``` | ```trk``` | ```trkfit``` |
| Track | ```trk``` | ```trkfit``` | none |
| TrackSegment | ```trkfit``` | none | none |

## Supported Branches
The currently supported branches are:
* evtinfo
* trk
* trkfit
