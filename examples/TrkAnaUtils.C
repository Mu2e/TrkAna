//
//  Utility macros for inspecting TrkAna files for use from the root prompt.  As an example, running from
//  a muse directory with TrkAna included:
//  > root -l
//  root> #include TrkAna/examples/TrkAnaUtils.C
//  root> TrkAnaUtils tau("MyTrkAnaFile.root");
//  root> tau.ListTrees(); // lists available TrkAna trees (TDirectories)
//  root> tau.UseTree("TrkAnaNeg"); // use the tree based on downstream negative electron tracks
//  root> tau.ListBranches(); // list the available branches
//  root> tau.ListSubbranches("deent"); // list sub-branches for the downstream negative electron branch
//  root> tau.ListLeaves("hcnt."); // list leaves in the hitcount branch
//  root> tau.Draw("deent.mom.Theta():deent.pos.Y()","hcnt.nbkg<400","colorz"); // Draw a plot
//
//  Original author: Dave Brown (LBNL)
//
#include <iostream>
#include <string>
class TrkAnaUtils {
  public:
    TrkAnaUtils(const char* filename);
    ~TrkAnaUtils() { delete myfile_; }
    TFile const& File() const { return *myfile_; }
    void ListTrees() const;
    void UseTree(const char* treename="TrkAnaNeg");
    void fileName() { return myfile_->GetName(); }
    void treeName() { if(mytree_)return mytree_->GetName(); else std::cout << "No current tree" << std::endl; }
    TFile* file() { return myfile_;}
    TTree* tree() { return mytree_;}
    void ListBranches() const;
    void ListSubbranches(const char* branch) const;
    void ListLeaves(const char* branch) const;
    void Draw(const char* lname,const char* cut="", const char* gopt="") const;
  private:
    TFile* myfile_;
    TTree* mytree_;
};

TrkAnaUtils::TrkAnaUtils(const char* filename) :  mytree_(0) {
  myfile_ = new TFile(filename);
}

void TrkAnaUtils::ListTrees() const {
  TObjArray* keylist = (TObjArray*)myfile_->GetListOfKeys();
  int nkeys = keylist->GetEntries();
  for(int ikey=0;ikey<nkeys;++ikey){
    auto key = keylist->At(ikey);
    std::string kname(key->GetName());
    if(0 == kname.compare(0,6,std::string("TrkAna")))
      std::cout << kname << std::endl;
  }
}

void TrkAnaUtils::UseTree( const char* treename) {
  TObjArray* keylist = (TObjArray*)myfile_->GetListOfKeys();
  int nkeys = keylist->GetEntries();
  for(int ikey=0;ikey<nkeys;++ikey){
    auto key = keylist->At(ikey);
    std::string kname(key->GetName());
    if(0 == kname.compare(std::string(treename))){
      auto td = (TDirectory*)myfile_->GetDirectory(treename);
      if(td){
        mytree_ = (TTree*)td->Get("trkana");
          if(!mytree_)
            std::cout <<"Error: can't find TrkAna tree in TDirectory " << treename << std::endl;
      } else
        std::cout <<"Error: can't find TDirectory " << treename << std::endl;
    }
  }
}

void TrkAnaUtils::ListBranches() const {
  if(mytree_){
    auto blist = mytree_->GetListOfBranches();
    int nbs = blist->GetEntries();
    for(int ib=0;ib<nbs;++ib){
      auto b = blist->At(ib);
      std::cout << b->GetName() << std::endl;
    }
  } else {
    std::cout << "No current tree; call UseTree to set current tree" << std::endl;
  }
}

void TrkAnaUtils::ListSubbranches(const char* branch) const {
  if(mytree_){
    auto bran = mytree_->GetBranch(branch);
    if(bran){
      auto blist = bran->GetListOfBranches();
      int nbs = blist->GetEntries();
      for(int ib=0;ib<nbs;++ib){
        auto b = blist->At(ib);
        std::cout << b->GetName() << std::endl;
      }
    } else {
      std::cout << "Current tree has no branch" << branch << std::endl;
    }
  } else {
    std::cout << "No current tree; call UseTree to set current tree" << std::endl;
  }
}

void TrkAnaUtils::ListLeaves(const char* branch) const {
  if(mytree_){
    auto bran = mytree_->GetBranch(branch);
    if(bran){
      auto blist = bran->GetListOfLeaves();
      int nbs = blist->GetEntries();
      for(int ib=0;ib<nbs;++ib){
        auto b = blist->At(ib);
        std::cout << b->GetName() << std::endl;
      }
    } else {
      std::cout << "Current tree has no branch" << branch << std::endl;
    }
  } else {
    std::cout << "No current tree; call UseTree to set current tree" << std::endl;
  }
}

void TrkAnaUtils::Draw(const char* lname,const char* cut="", const char* gopt="") const {
  if(mytree_){
    mytree_->Draw(lname,cut,gopt);
  } else {
    std::cout << "No current tree; call UseTree to set current tree" << std::endl;
  }
}
