#!/bin/python3

import os
import argparse

class nthelp:

    track_types_dict = { 'kl' : "kinematic line fit (i.e. straight-line fit)",
                         'dem' : "downstream e-minus fit",
                         'uem' : "upstream e-minus fit",
                         'dmm' : "downstream mu-minus fit",
                         'umm' : "upstream mu-minus fit",
                         'dep' : "downstream e-plus fit",
                         'uep' : "upstream e-plus fit",
                         'dmp' : "downstream mu-plus fit",
                         'ump' : "upstream mu-plus fit",
                         'trk' : "track"
                        }

    # A dictionary of branch name to header file containing the struct
    branch_struct_dict = { 'evtinfo' : "EventInfo",
                           'evtinfomc' : "EventInfoMC",
                           'hcnt' : "HitCount.hh",
                           'tcnt' : "TrkCount.hh",
                           'trk' : "TrkInfo.hh",
                           'trkfit' : "TrkInfo.hh",
                           'trkmc' : "TrkInfo.hh",
                           'trkmcsim' : "SimInfo.hh",
                           'trktch' : "TrkCaloHitInfo.hh",
                           'trktsh' : "TrkStrawHitInfo.hh",
                           'trktshmc' : "TrkStrawHitInfoMC.hh",
                           'trktsm' : "TrkStrawMatInfo.hh",
                           'trkmcsci' : "MCStepInfo.hh",
                           'trkmcssi' : "MCStepInfo.hh",
                           "crvsummary" : "CrvSummaryReco.hh",
                           "crvsummarymc" : "CrvSummaryMC.hh",
                           "crvcoincs" : "CrvHitInfoReco.hh",
                           "crvcoincsmc" : "CrvHitInfoMC.hh",
                           "crvcoincsmcplane" : "CrvPlaneInfoMC.hh"
                          }

    def check_track_type(self, branch):
        retval = ["", ""]
        if "crv" not in branch: # "umm" is matching "crvsummary"
            for key in self.track_types_dict:
                if key in branch: # branch could be "demmc" but key will be "dem"
                    retval = [key, self.track_types_dict[key]]
                    break

        return retval

    def whatis(self, array):
        if type(array) is not list: # if a single string is passed, put it into an array
            array = [array]

        # Expecting "item" to be of form "branch.leaf"
        for item in array:
            tokens = item.split('.')
            branch = tokens[0]

            # Check if this is a track branch
            branch_to_search = branch
            track_type, explanation = self.check_track_type(branch)
            if (explanation != ""):
                print(branch+" = "+explanation)
                branch_to_search = branch.replace(track_type, "trk") # we have keyed all the different track-related branches to "trk" in e.g. branch_struct_dict

            leaf = ""
            if len(tokens)>1:
                leaf = tokens[1]
            branch_output = branch;
            leaf_output = branch + "." + leaf + ": ";
            try:
                struct = self.branch_struct_dict[branch_to_search]
                struct_file = struct;
                if (".hh" not in struct_file):
                    struct_file += ".hh"
                found = False;
                with open(os.environ.get("TRKANA_INC")+"/TrkAna/inc/"+struct_file, 'r') as f:
                    lines = f.readlines()
                    for row in lines:
                        if (row.find("// "+struct) != -1):
                            #print(row)
                            branch_output += row.replace("// "+struct, "").replace('\n', ''); # remove the trailing newline as well

                        if (row.find(" "+leaf+" ") != -1) or (row.find(" "+leaf+";") != -1): # add spaces around leaf so that we don't find substrings
#                            print(row)
                            leaf_output += row.replace("\t", "")
                            found = True
                            break
                if not found:
                    print(leaf+" could not be found...\n")
            except KeyError:
                print(branch_to_search+" is not in branch_struct_dict...\n")

            print(branch_output)
            print(leaf_output)
# A main function so that this can be run on the command line
def main():
    parser = argparse.ArgumentParser(
        prog='ntuplehelper.py',
        description='A python utility class to get information about branches and leaves',
        epilog='For help contact Andy Edmonds via e-mail/Slack')

    parser.add_argument('--branches', required=True, nargs='*', help="Use format \"branch.leaf\". Multiple items are allowed")

    args = parser.parse_args()

    nth = nthelp()
    nth.whatis(args.branches)

if __name__ == "__main__":
    main()
