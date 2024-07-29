import ntuplehelper

nthelp = ntuplehelper.nthelp()

print("Testing a leaf from each branch")
print("=========")
nthelp.whatis(['evtinfomc.pbtime', 'evtinfo.event', 'hcnt.nbkg', 'tcnt.ndem', 'demmcsim.pdg', 'demtch.trkdepth', 'demtsh.ptoca', 'demtshmc.edep', 'demtsm.tlen'])

print("Testing a few leaves from a single branch (should only print the branch description once)")
print("=========")
nthelp.whatis(['evtinfo.run', 'evtinfo.subrun', 'evtinfo.event']) # should only print the "evtinfo" description once

print("Testing a few errors")
print("=========")
nthelp.whatis(['dem.lha', 'fff.gap', 'fff.ddd'])
