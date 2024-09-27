import ntuplehelper

nthelp = ntuplehelper.nthelper()

print("Testing a leaf from each branch")
print("=========")
nthelp.whatis(['evtinfomc.pbtime', 'evtinfo.event', 'hitcount.nbkg', 'tcnt.ndem', 'demmcsim.pdg', 'demtch.trkdepth', 'demtsh.ptoca', 'demtshmc.edep', 'demtsm.tlen', 'crvsummary.totalPEs', 'crvsummarymc.sectorNumber', 'crvcoincs.time', 'crvcoincsmc.primaryE', 'crvcoincsmcplane.dir', 'demmcsci.dp', 'demmcssi.dp', 'dem.nactive', 'demmc.ndigigood', 'demfit.mom', 'demlh.cx', 'demch.omega', 'klkl.phi0', 'trkqual.result'])

print("Testing a few leaves from a single branch (should only print the branch description once)")
print("=========")
nthelp.whatis(['evtinfo.run', 'evtinfo.subrun', 'evtinfo.event']) # should only print the "evtinfo" description once

print("Testing wildcard")
print("=========")
nthelp.whatis(["dem.*", "demfit.*"])

print("Testing a few errors")
print("=========")
nthelp.whatis(['dem.lha', 'fff.gap', 'fff.ddd'])
