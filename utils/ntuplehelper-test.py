import ntuplehelper

nthelp = ntuplehelper.nthelp()

print("Testing a leaf from each branch")
print("=========")
nthelp.whatis(['evtinfomc.pbtime', 'evtinfo.event', 'hcnt.nbkg', 'tcnt.ndem', 'demmcsim.pdg'])

print("Testing a few leaves from a single branch (should only print the branch description once)")
print("=========")
nthelp.whatis(['evtinfo.run', 'evtinfo.subrun', 'evtinfo.event']) # should only print the "evtinfo" description once

print("Testing a few errors")
print("=========")
nthelp.whatis(['dem.lha', 'fff.gap', 'fff.ddd'])

nthelp.whatis('dem.gap')
nthelp.whatis(['dem.nhits', 'uem.nhits'])
nthelp.whatis('klmcsim.startCode')
nthelp.whatis('crvsummary.totalPEs')
nthelp.whatis('crvcoincs.timeStart')
nthelp.whatis('crvsummarymc.minPathLayer')
nthelp.whatis('crvcoincsmc.gparent')
nthelp.whatis('crvcoincsmcplane.dir')
