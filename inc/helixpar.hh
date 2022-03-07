//
// BaBar convention helix parameters.  This struct is for us in TTrees, the actual helix fit parameters are
// defined by BaBar classes
// Dave Brown (LBNL)
//
#ifndef helixparHH
#define helixparHH
#include "Rtypes.h"
#include "CLHEP/Matrix/SymMatrix.h"
#include "CLHEP/Matrix/Vector.h"
#include "Offline/RecoDataProducts/inc/HelixVal.hh"
namespace mu2e
{
  struct helixpar {
    Float_t d0; // transverse distance of closest approach to the z axis, signed by the track angular momentum
    Float_t p0; // aximuth of the momentum vector at the point of closest approach to the z axis
    Float_t om; // curvature (inverse radius), signed by the charge.  This is position independent
    Float_t z0; // z position of the track at the transverse point of closest approach
    Float_t td; // tangent of the dip angle (= pi/2 - theta).  This is independent of position
    helixpar() : d0(0.0),p0(0.0),om(0.0),z0(0.0),td(0.0) {}
    helixpar(const CLHEP::HepVector& pvec) : d0(pvec[0]),p0(pvec[1]),om(pvec[2]),z0(pvec[3]),td(pvec[4]) {}
    helixpar(const CLHEP::HepSymMatrix& pcov) : d0(sqrt(pcov.fast(1,1))),p0(sqrt(pcov.fast(2,2))),om(sqrt(pcov.fast(3,3))),
    z0(sqrt(pcov.fast(4,4))),td(sqrt(pcov.fast(5,5))) {}
    helixpar(HelixVal const& hval ) : d0(hval.d0()), p0(hval.phi0()), om(hval.omega()), z0(hval.z0()), td(hval.tanDip()) {}
    void reset() { d0 = p0 = om = z0 = td = 0.0; }
    static std::string leafnames() { static std::string leaves; leaves = std::string("d0/F:p0/F:om/F:z0/F:td/F"); return leaves; }
  };
}
#endif
