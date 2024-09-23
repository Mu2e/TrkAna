# Fcl Files
The naming convention for fcl files is ```from_tier-type_extra.fcl``` where ```tier``` is the data tier of the input dataset, ```type``` is the type of dataset (e.g. primary-only, extracted position), and ```extra``` gives some extra information (optional)

| fcl file | runs on | additional info |
|----------|-----|-----|
| from_mcs-mockdata.fcl | mock datasets | |
| from_mcs-mockdata_noMC.fcl | mock datasets | doesn't include MC in output|
| from_mcs-extracted.fcl | reconstructed extracted position datasets | |
| from_mcs-primary.fcl | reconstructed primary (i.e. no background hits) datasets | |
| from_mcs-mixed.fcl | reconstructed mixed (i.e. primary+background hits) datasets | |
| from_mcs-ceSimReco.fcl | output of ceSimReco.fcl | |
