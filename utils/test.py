from mu2epyutil import EvtNtuple_util as evn


def main():
  """ simple test function to run some of the utils """
  """
  test_evn = evn("/exp/mu2e/app/users/sophie/ProductionEnsembles_v2/py-ana/trkana/pass0a.root", "TrkAna", "trkana")
  surface_id = 0 # tracker entrance
  vector_test = test_evn.GetVectorXYZ("demfit", "mom", surface_id)
  print("vector magnitudes extracted : ", vector_test.mag)
  test_evn.PlotMagValueHist("demfit", "mom", surface_id, 95, 115, "fit mom at Trk Ent [MeV/c]","log")
  test_evn.PlotValueHist("demfit", "time", surface_id, 450, 1700, "fit time at Trk Ent [ns]", 'linear')
  """
  test_evn = evn("/exp/mu2e/app/users/sophie/ProductionEnsembles_v2/py-ana/trkana/pass0a.root", "TrkAna", "trkana")
  filepath = "/exp/mu2e/app/users/sophie/newOffline/TrkAna/utils/example/*.root"
  test_evn.ImportFileList(filepath)
  
if __name__ == "__main__":
    main()
