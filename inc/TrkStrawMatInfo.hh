//
// TrkStrawMatInfo: branch to describe straw materials on the Kalman fit
//
#ifndef TrkStrawMatInfoHH
#define TrkStrawMatInfoHH
namespace mu2e
{
  struct TrkStrawMatInfo {
    bool active = false;    // was this material was used in the Kalman fit or not
    int plane = -1, panel = -1, layer = -1, straw = -1; // StrawId fields of the straw
    float doca = -1000.0;    // DOCA between the track fit and the wire
    float tlen = -1000.0;   // length along the helix of the POCA
    float dp  = -1000.0;      // momentum (energy) loss induced by this straw's material, including both entry and exit wall and the gas
    float radlen = -1000.0;  // radiation length of this straw's material seen by the track (including angular effects)
  };
}
#endif
