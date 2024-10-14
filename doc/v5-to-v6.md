# Major Changes from v5 to v6

There was a major update when we moved from v5 to v6. Here are tables of changes for you to consult. Note that the same change may appear in multiple tables since it may be important in one area but defined in another. For example, the folder name is defined in fcl but is also important to know in the Tree / Branch / Leaf Changes

## Tree / Branch / Leaf Changes
|   | v5 | v6 | Notes |
|---|---|---|---|
| tree name | ```trkana``` | ```ntuple``` | defined in code |
| folder name | ```TrkAna``` | ```EventNtuple``` | defined in fcl |
| folder name | ```TrkAnaExt``` | ```EventNtuple``` | defined in fcl |
| branch | ```dem```, ```uem```, etc. | ```trk``` | all track types are now in a single branch |
| branch | ```demfit```, ```uemfit```, etc. | ```trksegs``` | track segments |
| branch | ```demtrkqual``` | ```trkqual``` | otherwise it would have been ```trktrkqual```|
| branch | ```demtch``` | ```trkcalohit``` | |
| branch | ```demtchmc``` | ```trkcalohitmc``` | |
| branch | ```hcnt``` | ```hitcount``` | also now filled |
| branch | ```demtsh``` | ```trkhits``` | |
| branch | ```demtshmc``` | ```trkhitsmc``` | |
| branch | ```demtsm``` | ```trkmats``` | mats = materials |
| branch | ```helixinfo``` | ```helices``` | also now a vector branch |
| branch | ```demlh``` | ```trksegpars_lh``` | pars = parameters, lh = LoopHelix |
| branch | ```demch``` | ```trksegpars_ch``` | pars = parameters, ch = CentralHelix |
| branch | ```demkl``` | ```trksegpars_kl``` | pars = parameters, kl = KinematicLine |
| branch | ```demmcssi``` | ```trksegsmc``` | information of the surface steps at same places as trksegs|

## Fcl File Changes
Many fcl files were renamed, updated, or deleted. New fcl files introduced in v6 and all fcl files are documented on the new [fcl README page](../fcl/README.md)

| fcl file | v5 --> v6 | notes |
|----|---|----|
| TrkAnaReco.fcl | from_mcs-mockdata.fcl | for running on mock datasets, ```genCountLogger``` also removed  |
| TrkAnaExtracted.fcl | from_mcs-extracted.fcl | for running on mcs "extracted position" datasets, now #includes from_mcs-mockdata.fcl as a base |
| TrkAnaReco_ceSimReco.fcl | from_mcs-ceSimReco.fcl | for running on the output of ceSimReco.fcl |
| TrkAnaRecoEnsemble-Data.fcl | from_mcs-mockdata_noMC.fcl | for running on mock data with no MC information |
| TrkAnaDeM.fcl | only #includes updated |  |
| TrkAnaDeMFromDigis.fcl | only #includes updated |  |
| TrkAnaLineFromDigis.fcl | only #includes updated |  |
| TrkAnaReflections.fcl | only #includes updated |  |
| TrkAnaTrigger.fcl | only #includes updated |  |
| TrkAnaTriggerFromDigis.fcl | only #includes updated |  |
| TrkAnaRecoEnsemble-MC.fcl | deleted | use from_mcs-mockdata.fcl instead|
| TrkAnaReco_mergedKalSeeds.fcl | deleted | all track types in one branch is now the default |
| CrvExpert.fcl | deleted | |
| TrkAnaReco_wTrkQualFilter.fcl | deleted | |
| TrkAnaReco_addMCUpstream.fcl | deleted | |
| TrkAnaReco_addStopTgtVDs.fcl | deleted | |
| TrkAnaReco_multipleBestCrv.fcl | deleted | |
| TrkAnaReco_multipleBestCrv_differentThresholds.fcl | deleted | |
| TrkAnaReco_MultipleTrkQual.fcl | deleted | |

## Fcl Parameter Changes 
|  | v5 | v6 | Notes |
|---|--|--|---|
| folder name | ```TrkAna``` | ```EventNtuple``` | |
| default output file name | ```nts.owner.trkana-reco.version.sequencer.root``` | ```nts.owner.description.version.sequencer.root``` | |
| prolog.fcl table name | ```TrkAnaTreeMaker``` | ```EventNtupleMaker``` | the table that contains the default module configuration |
| prolog.fcl physics block | ```TrkAnaReco``` | ```EventNtuple``` | the block that contains ```producers```, ```analyzers```, etc. |
| prolog.fcl path names | ```Sequence``` | ```Path``` | for consistency with previous stages of processing|
| EventNtupleMaker module parameter | ```ProcessEmptyEvents``` | removed | not used anywhere |
| EventNtupleMaker module parameter | ```required``` | removed | not used anywhere |
| ```FillHits``` default value | ```false``` | ```true``` | changed in prolog.fcl |


## Other Code Changes

|  | v5 | v6 | Notes |
|---|--|--|---|
| src file name | ```TrkAnaTreeMaker_module.cc``` | ```EventNtupleMaker_module.cc``` | |
| art module name | ```TrkAnaTreeMaker``` | ```EventNtupleMaker``` |  |
| tree name | ```trkana``` | ```ntuple``` | defined in code |
| art module function | ```fillAllInfos``` | ```fillTrackBranches``` | more descriptive |
| art module code | ```ntuple->Branch("evtinfo.")``` | ```ntuple->Branch("evtinfo")``` | period removed for better access in RooUtil |
| art module code | ```ntuple->Branch("evtinfomc.")``` | ```ntuple->Branch("evtinfomc")``` | period removed for better access in RooUtil |
| info struct | ```TrkFitInfo``` | ```TrkSegInfo``` | to match new branch name, also other changes in module (e.g. ```_allTFIs``` to ```_allTSIs```)|
