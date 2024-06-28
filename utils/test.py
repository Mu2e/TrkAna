from mu2epyutil import EvtNtuple_util as evn

def main():
  test_evn = evn("/exp/mu2e/app/users/sophie/ProductionEnsembles_v2/py-ana/trkana/pass0a.root", "TrkAna", "trkana")
  vector_test = test_evn.GetVectorXYZ("demfit", "mom", 0)
  print(vector_test.mag)
  test_evn.PlotMagValueHist("demfit", "mom", 0, 95, 115, "reco mom at Trk Ent [MeV/c]","log")
  test_evn.PlotValueHist("demfit", "time", 0, 450, 1700, "fit time at Trk Ent [ns]", 'linear')
  
if __name__ == "__main__":
    main()  
