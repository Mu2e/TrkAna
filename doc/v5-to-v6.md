# Major Changes from v5 to v6

There was a major update when we moved from v5 to v6. Here are tables of changes for you to consult. Note that the same change may appear in multiple tables since it may be important in one area but defined in another. For example, the folder name is defined in fcl but is also important to know in the Tree / Branch / Leaf Changes

## Tree / Branch / Leaf Changes
|  | v5 | v6 | Notes |
|---|--|--|---|
| tree name | ```trkana``` | ```ntuple``` | defined in code |
| folder name | ```TrkAna``` | ```EventNtuple``` | defined in fcl |
| folder name | ```TrkAnaExt``` | ```EventNtuple``` | defined in fcl |

## Fcl File Changes
Many fcl files were renamed, updated, or deleted

| fcl file | v5 --> v6 | notes |
|----|---|----|
| TrkAnaReco.fcl | from_mcs_mockdata.fcl | for running on mock datasets, ```genCountLogger``` also removed  |
| TrkAnaExtracted.fcl | from_mcs_extracted.fcl | for running on mcs "extracted position" datasets, now #includes from_mcs_mockdata.fcl as a base |
| TrkAnaReco_ceSimReco.fcl | from_mcs_ceSimReco.fcl | for running on the output of ceSimReco.fcl |
| from_mcs_primary.fcl | new file | for running on mcs "primary" datasets |
| from_mcs_mixed.fcl | new file | for running on mcs "mixed" datasets |
| prolog_mc_reweighters.fcl | new file | contains prolog blocks for reweighter modules which were previously in prolog.fcl itself |
| CrvExpert.fcl | deleted | |
| TrkAnaReco_wTrkQualFilter.fcl | deleted | |

## Fcl Parameter Changes 
|  | v5 | v6 | Notes |
|---|--|--|---|
| folder name | ```TrkAna``` | ```EventNtuple``` | |
| default output file name | ```nts.owner.trkana-reco.version.sequencer.root``` | ```nts.owner.description.version.sequencer.root``` | |
| prolog.fcl table name | ```TrkAnaTreeMaker``` | ```EventNtupleMaker``` | the table that contains the default module configuration |
| prolog.fcl physics block | ```TrkAnaReco``` | ```EventNtuple``` | the block that contains ```producers```, ```analyzers```, etc. |
| prolog.fcl path names | ```Sequence``` | ```Path``` | for consistency with previous stages of processing|


## Important Code Changes

|  | v5 | v6 | Notes |
|---|--|--|---|
| src file name | ```TrkAnaTreeMaker_module.cc``` | ```EventNtupleMaker_module.cc``` | |
| art module name | ```TrkAnaTreeMaker``` | ```EventNtupleMaker``` |  |
| tree name | ```trkana``` | ```ntuple``` | defined in code |
