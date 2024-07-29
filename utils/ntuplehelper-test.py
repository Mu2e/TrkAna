import ntuplehelper

nthelp = ntuplehelper.nthelp()

print("Calling nthelp.whatis(['evtinfomc.pbtime', 'evtinfo.event', 'hcnt.nbkg']) (testing a leaf from each branch)")
print("=========")
nthelp.whatis(['evtinfomc.pbtime', 'evtinfo.event', 'hcnt.nbkg'])

print("Calling nthelp.whatis(['evtinfo.run', 'evtinfo.subrun', 'evtinfo.event']) (this should only print the \"evtinfo\" description once)")
print("=========")
nthelp.whatis(['evtinfo.run', 'evtinfo.subrun', 'evtinfo.event']) # should only print the "evtinfo" description once


nthelp.whatis('dem.gap')
nthelp.whatis(['dem.nhits', 'uem.nhits'])
nthelp.whatis('dem.lha') # will show an error message that leaf cannot be found
nthelp.whatis('fff.t') # will show an error message that branch cannot be found
nthelp.whatis('fff') # will show an error message that branch cannot be found
nthelp.whatis('klmcsim.startCode')
nthelp.whatis('crvsummary.totalPEs')
nthelp.whatis('crvcoincs.timeStart')
nthelp.whatis('crvsummarymc.minPathLayer')
nthelp.whatis('crvcoincsmc.gparent')
nthelp.whatis('crvcoincsmcplane.dir')
