# How to get help -- ```ntuplehelper```

On this page, you will learn how to use the [```ntuplehelper```](../../utiles/ntuplehelper.py) utility to get more information about what the different branches and leaves are. You will need to be in a TrkAna environment e.g.

```
mu2einit
muse setup TrkAna
```

You can use this utility:

* on the command line:

```
python3 ${TRKANA_INC}/TrkAna/utils/ntuplehelper.py --branches dem.nhits demmcsim.startCode
```

* and from within python:

```
>>> import ntuplehelper
>>> nthelp = ntuplehelper.nthelp()
>>> nthelp.whatis('dem.hits')
```

see [the test script for more examples](../../utils/ntuplehelper-test.py)


If you notice something missing or a bug, then post it to the #trkana Slack channel and we will fix it
