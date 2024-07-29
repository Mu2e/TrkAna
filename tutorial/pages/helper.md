# How to get help -- ```ntuplehelper```

## Introduction

On this page, you will learn how to get more information about

### From the command line

```
python3 ${TRKANA_INC}/TrkAna/utils/ntuplehelper.py --branches dem.nhits demmcsim.startCode
```

### From within a python

```
>>> import ntuplehelper
>>> nthelp = ntuplehelper.nthelp()
>>> nthelp.whatis('dem.hits')
```

see [the test script for more examples](../../utils/ntuplehelper-test.py)

### Notice something missing?
Post it on the #trkana Slack channel
