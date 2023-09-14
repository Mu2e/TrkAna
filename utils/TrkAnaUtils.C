//
//  Utility macros for inspecting TrkAna files for use from the root prompt.  As an example, running from
//  a muse directory with TrkAna included:
//  > root -l
//  root> #include TrkAna/examples/TrkAnaUtils.C
//  root> TrkAnaUtils tau("MyTrkAnaFile.root");
//  root> tau.ListTrees(); // lists available TrkAna trees (TDirectories)
//  root> tau.UseTree("TrkAnaNeg"); // use the tree based on downstream negative electron tracks
//  root> tau.ListBmeranches(); // list the available branches
//  root> tau.ListSubbranches("deent"); // list sub-branches for the downstream negative electron branch
//  root> tau.ListLeaves("hcnt."); // list leaves in the hitcount branch
//  root> tau.Draw("deent.mom.Theta():deent.pos.Y()","hcnt.nbkg<400","colorz"); // Draw a plot
//
//  Original author: Dave Brown (LBNL)
//
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include <iostream>
#include <fstream>
#include <string>
#include "TChain.h"
using namespace std;
class TrkAnaUtils {
  public:
    TrkAnaUtils(TTree* tatree);
    TrkAnaUtils(TFile* myfile,const char* treename="TrkAnaNeg");
    TrkAnaUtils(const char* filename,const char* treename);
    TrkAnaUtils(const char* treename="TrkAnaNeg");
    TFile const& File() const { return *myfile_; }
    void ListTrees() const;
    void UseTree(const char* treename="TrkAnaNeg");
    auto fileName() { return myfile_->GetName(); }
    auto treeName() { if(mytree_)return mytree_->GetName(); else return "none"; }
    TFile* file() { return myfile_;}
    TTree* tree() { return mytree_;}
    TCanvas* can() const { return mycan_; }
    void ListBranches(int maxdepth=0) const;
    void ListBranch(const char* bname, int maxdepth=1) const;
    void ListLeaves(const char* branch) const;
    void Draw(const char* lname,const char* cut="", const char* gopt="") const;
    void Project(const char* pname, const char* lname, const char* cut="") const;
    void Scan(const char* lname,const char* cut="") const;
  private:
    void ListBranch(TBranch* branch, int idepth, int maxdepth) const;
    mutable TFile* myfile_;
    mutable TTree* mytree_;
    mutable TCanvas* mycan_;
    TChain* mychain_;
};

TrkAnaUtils::TrkAnaUtils(TTree* tatree) : myfile_(0), mytree_(tatree), mychain_(0) {}
TrkAnaUtils::TrkAnaUtils(TFile* myfile,const char* treename) : myfile_(myfile), mytree_(0), mychain_(0) {
  UseTree(treename);
}

TrkAnaUtils::TrkAnaUtils(const char* filename,const char* treename) :  mytree_(0) ,mychain_(0) {
  // get the suffix
  std::string sfn(filename);
  auto idx = sfn.rfind('.')+1;
  if(sfn.compare(idx,4,"root") == 0){
    myfile_ = new TFile(filename);
    UseTree(treename);
  } else if(sfn.compare(idx,3,"txt") == 0){
    // interpret as a list of files
    ifstream ifs(filename);
    if(ifs.is_open()){
      string stn = string(treename) + string("/trkana");
      mychain_ = new TChain(stn.c_str());
      string file;
      while(getline(ifs,file)){
        cout << "adding file " << file << " to chain " << endl;
        mychain_->Add(file.c_str());
      }
      ifs.close();
      mytree_  = mychain_;
    } else
      cout << "File " << filename << " can't be opened, aborting" << endl;
  } else {
    cout << "Unknown file type" << sfn.substr(idx) << endl;
  }
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

void TrkAnaUtils::ListBranches(int maxdepth) const {
  int idepth(0);
  if(mytree_){
    auto tlist = mytree_->GetListOfBranches();
    int nbs = tlist->GetEntries();
    for(int ib=0;ib<nbs;++ib){
      auto branch = (TBranch*)tlist->At(ib);
      ListBranch(branch,idepth,maxdepth);
    }
  } else {
    std::cout << "No current tree; call UseTree to set current tree" << std::endl;
  }
}

void TrkAnaUtils::ListBranch(const char* bname, int maxdepth) const {
  if(mytree_){
    auto branch = mytree_->GetBranch(bname);
    if(branch){
      ListBranch(branch,0,maxdepth);
    } else {
      // try with a dot
      std::string bstr = std::string(bname) + ".";
      branch = mytree_->GetBranch(bstr.c_str());
      if(branch){
        ListBranch(branch,0,maxdepth);
      } else {
        std::cout << "No branch " << bname << " in current tree" << std::endl;
      }
    }
  } else {
    std::cout << "No current tree; call UseTree to set current tree" << std::endl;
  }
}

void TrkAnaUtils::ListBranch(TBranch* branch, int idepth, int maxdepth) const {
  std::cout << branch->GetName() << std::endl;
  if(idepth < maxdepth){
    auto blist = branch->GetListOfBranches();
    int nbs = blist->GetEntries();
    for(int ib=0;ib<nbs;++ib){
      auto subbranch = (TBranch*)blist->At(ib);
      ListBranch(subbranch,idepth++,maxdepth);
    }
  }
}



void TrkAnaUtils::ListLeaves(const char* bname) const {
  if(mytree_){
    auto bran = mytree_->GetBranch(bname);
    if(bran){
      auto blist = bran->GetListOfLeaves();
      int nbs = blist->GetEntries();
      for(int ib=0;ib<nbs;++ib){
        auto b = blist->At(ib);
        std::cout << b->GetName() << std::endl;
      }
    } else {
       // try with a dot
      std::string bstr = std::string(bname) + ".";
      bran = mytree_->GetBranch(bstr.c_str());
      if(bran){
        auto blist = bran->GetListOfLeaves();
        int nbs = blist->GetEntries();
        for(int ib=0;ib<nbs;++ib){
          auto b = blist->At(ib);
          std::cout << b->GetName() << std::endl;
        }
      } else {
        std::cout << "No branch " << bname << " in current tree" << std::endl;
      }
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

void TrkAnaUtils::Project(const char* pname,const char* lname,const char* cut="") const {
  if(mytree_){
    mytree_->Project(pname,lname,cut);
  } else {
    std::cout << "No current tree; call UseTree to set current tree" << std::endl;
  }
}

void TrkAnaUtils::Scan(const char* lname,const char* cut="") const {
  if(mytree_){
    mytree_->Scan(lname,cut);
  } else {
    std::cout << "No current tree; call UseTree to set current tree" << std::endl;
  }
}
