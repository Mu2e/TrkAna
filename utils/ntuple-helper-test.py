from ntuplehelper import ntuplehelper

nthelp = ntuplehelper()
nthelp.whatis('dem.gap')
nthelp.whatis(['dem.nhits', 'uem.nhits'])
nthelp.whatis('dem.lha') # will show an error message that leaf cannot be found
nthelp.whatis('fff.t') # will show an error message that branch cannot be found
nthelp.whatis('fff') # will show an error message that branch cannot be found
