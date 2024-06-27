from mu2epyutil import EvtNtuple_util as evn

def main():
  test_evn = evn("/exp/mu2e/app/users/sophie/ProductionEnsembles_v2/py-ana/trkana/pass0a.root", "TrkAna", "trkana")
  vector_test = test_evn.GetVectorXYZ("demfit", "mom", 0)
  print(vector_test.mag)
  
if __name__ == "__main__":
    main()  
