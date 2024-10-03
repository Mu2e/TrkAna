import sys # for simple input arguments
import uproot # for reading in ROOT files

filename=sys.argv[1]
treename="TrkAna/trkana"

# Open the ROOT file and be read yto read in the trkana tree
trkana = uproot.open(filename+":"+treename)

# Read in just the evtinfo id branches, and the tcnt branches
branches = trkana.arrays(filter_name=["/evtinfo.*id/", "/tcnt.*/"])

print(branches.fields)
# Print the first 20 tracks
print(branches[:20].to_list())
