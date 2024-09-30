#include "TrkAna/utils/rooutil/inc/RooUtil.hh"

void PrintEvents(std::string filename) {

  RooUtil util(filename);
  std::cout << filename << " has " << util.GetNEvents() << " events" << std::endl;
}
