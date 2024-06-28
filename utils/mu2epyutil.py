import uproot
import awkward as ak
import matplotlib.pyplot as plt
import math
import numpy as np
import vector

class EvtNtuple_util:
  """ class to help users import a trkana tree and branch """
  def __init__(self, filename, treename="TrkAna", branchname="trkana"):
    self.filename= filename
    self.treename = treename
    self.branchname = branchname
    self.Array = ak.Array
  
  def ImportTree(self):
    """ import root tree """
    input_file = uproot.open(self.filename)
    input_tree = input_file[self.treename][self.branchname]
    return input_tree
    
  def MakeAwkArray(self):
    """ import root tree and save it as an Awkward array """
    input_tree = self.ImportTree()
    self.Array = input_tree.arrays(library='ak')
    return self.Array

  def ImportBranches(self, tree, leafnames):
      """ import list of branches from trkana"""
      list_names = []
      for i, leafname  in enumerate(leafnames):
          list_names.append("/"+str(leafname)+"/")
      branches = tree.arrays(filter_name=list_names)
      return branches
      
  def GetVectorXYZ(self, leafname, vectorreq, sid=0):
    """ 
    imports a XYZ vector branch e.g. mom and turns it into something which can use funcitons are found in:
    https://vector.readthedocs.io/en/latest/api/vector._methods.html 
    """
    # import code and extract branch
    tree = self.ImportTree()
    branch = self.ImportBranches(tree, [leafname])

    # register the vector class
    vector.register_awkward()

    # take the chosen position to evaluate (nominally entrance)
    trk_ent_mask = (branch[str(leafname)]['sid']==sid)

    # apply mask
    trkent = branch[(trk_ent_mask)]

    # make the Vector 3D TODO - protect against str(leafname)  doesnt exist error
    trkvect3D = ak.zip({
        "x": trkent[str(leafname)][str(vectorreq)]["fCoordinates"]["fX"],
        "y": trkent[str(leafname)][str(vectorreq)]["fCoordinates"]["fY"],
        "z": trkent[str(leafname)][str(vectorreq)]["fCoordinates"]["fZ"],
    }, with_name="Vector3D")
    
    return trkvect3D
  
  def PlotValueHist(self, leafname, vectorreq, sid, low, hi, xaxis_label, scale='linear'):
    """ make basic plot of magnitude of leafname value at tracker ent, mid or ext (specify sid) """
    
    # import code and extract branch
    tree = self.ImportTree()
    branch = self.ImportBranches(tree, [leafname])

    # take the chosen position to evaluate
    trk_mask = (branch[str(leafname)]['sid']==sid)

    # apply mask
    values = branch[(trk_mask)]
    
    fig, ax = plt.subplots(1,1)
    n, bins, patches = ax.hist(ak.flatten(values, axis=None), bins=100, range=(int(low), int(hi)), histtype='step',color='r')

    bin_centers = 0.5 * (bins[:-1] + bins[1:])
    yerrs = []
    for i, j in enumerate(n):
      yerrs.append(math.sqrt(j))
    plt.errorbar(bin_centers, n, yerr=np.sqrt(n), fmt='r.')

    # add in style features:
    ax.set_yscale(str(scale))
    ax.set_xlabel(str(xaxis_label))
    ax.set_ylabel('# events per bin')
    ax.grid(True)
    #ax.legend()
    plt.show()
    
    
  def PlotMagValueHist(self, leafname, vectorreq, sid, low, hi, xaxis_label, scale='log'):
    """ make basic plot of magnitude of leafname value at tracker ent, mid or ext (specify sid) """
    
    vect = self.GetVectorXYZ(leafname, vectorreq, sid)

    fig, ax = plt.subplots(1,1)
    n, bins, patches = ax.hist(ak.flatten(vect.mag, axis=None), bins=100, range=(int(low), int(hi)), histtype='step',color='r')

    bin_centers = 0.5 * (bins[:-1] + bins[1:])
    yerrs = []
    for i, j in enumerate(n):
      yerrs.append(math.sqrt(j))
    plt.errorbar(bin_centers, n, yerr=np.sqrt(n), fmt='r.')

    # add in style features:
    ax.set_yscale(str(scale))
    ax.set_xlabel(str(xaxis_label))
    ax.set_ylabel('# events per bin')
    ax.grid(True)
    #ax.legend()
    plt.show()

