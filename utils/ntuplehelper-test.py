from ntuplehelper import ntuplehelper

nthelp = ntuplehelper()
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
