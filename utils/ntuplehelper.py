#!/bin/python3

import argparse

class ntuplehelper:

    # A dictionary of branch name to header file containing the struct
    branch_struct_dict = { 'dem' : "TrkAna/inc/TrkInfo.hh",
                           'uem' : "TrkAna/inc/TrkInfo.hh"}

    def whatis(self, array):
        if type(array) is not list: # if a single string is passed, put it into an array
            array = [array]

        # Expecting "item" to be of form "branch.leaf"
        for item in array:
            tokens = item.split('.')
            branch = tokens[0]
            leaf = ""
            if len(tokens)>1:
                leaf = tokens[1]
            print(branch+"."+leaf)
            try:
                struct_file = self.branch_struct_dict[branch]
                found = False;
                with open(struct_file, 'r') as f:
                    lines = f.readlines()
                    for row in lines:
                        if (row.find(" "+leaf+" ") != -1) or (row.find(" "+leaf+";") != -1): # add spaces around leaf so that we don't find substrings
                            print(row)
                            found = True
                            break
                if not found:
                    print(leaf+" could not be found...")
            except KeyError:
                print(branch+" is not in branch_struct_dict...")

# A main function so that this can be run on the command line
def main():
    parser = argparse.ArgumentParser(
        prog='ntuplehelper.py',
        description='A python utility class to get information about branches and leaves',
        epilog='For help contact Andy Edmonds via e-mail/Slack')

    parser.add_argument('--branches', required=True, nargs='*', help="Use format \"branch.leaf\". Multiple items are allowed")

    args = parser.parse_args()

    nthelp = ntuplehelper()
    nthelp.whatis(args.branches)

if __name__ == "__main__":
    main()
