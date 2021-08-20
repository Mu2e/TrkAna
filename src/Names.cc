#include "TrkAna/inc/Names.hh"
namespace Names {
  std::string XYZnames(const char* vname) {
    std::string svname(vname);
    static std::string leaves; leaves = svname + std::string("x/F:") +
      svname + std::string("y/F:") + svname + std::string("z/F");
    return leaves;
  }
}

