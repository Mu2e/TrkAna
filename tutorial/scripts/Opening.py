import sys # for simple input arguments
import uproot # for reading in ROOT files

filename=sys.argv[1]
treename="TrkAnaNeg/trkana"

# Open the ROOT file and be read yto read in the trkana tree
trkana = uproot.open(filename+":"+treename)

# Read in just the evtinfo id branches, and the demfit.mom branches
branches = trkana.arrays(filter_name=["/evtinfo.*id/", "/demfit.mom.*/"])

# Print the first 20 tracks
print(branches[:20])
