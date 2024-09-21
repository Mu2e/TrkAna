
This example follows from the earlier example entitled "physics-analysis".

### Fitting to momentum using RooFit

Firstly add the following includes:

```
#include "TF1.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TMath.h"
#include <Riostream.h>

#include "TPaveStats.h"
#include "TPaveText.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TPaveLabel.h"
#include "TAttFill.h"

#include "RooHist.h"
#include "RooRealVar.h"
#include "RooPlot.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooKeysPdf.h"
#include "RooHistPdf.h"
#include "RooAddPdf.h"
#include "RooArgList.h"
#include "RooCBShape.h"
#include "RooGenericPdf.h"
#include "RooFFTConvPdf.h"
#include "RooFitResult.h"
#include "RooMinimizer.h"
#include "RooAbsReal.h"
//My stuff
#include "RefAna/Shape/inc/RooPol58.hh"

```

you should copy the file: "RefAna/Shape/inc/RooPol58.hh" from the RefAna repo.

Set up the RooFit variables

```
    // make RooFit objects
    RooRealVar recomom("recomom", "reco mom [MeV/c]", 95, 115);
    RooDataHist chMom("chMom", "chMom", recomom, hist_mom1); //TODO unbinned use RooDataSet
```

recomom is the variable we  are fitting to i.e. reconstructed momentum. chMom is the name of the RooDataHist, which comes directly from the hist_mom1 TH1F we made in the previous task.

Now set up the variables for the fit:

```
    // CE signal shape:
    RooRealVar fMean("mean", "mean", 104, 103, 105);
    RooRealVar fWidth("sigma", "sigma", 0.5, 0.1, 1.0);
    RooRealVar fcbalpha("fcbalpha", "fcbalpha", 2.5, 0.05, 20.0);
    RooRealVar fcbndeg("fcbndeg", "fcbndeg", 10., 0.25, 80.);
    RooCBShape Sig("Sig", "signal peak", recomom, fMean, fWidth, fcbalpha, fcbndeg);
    RooRealVar nsig("nsig", "number of signal events", 0.0, 0.0, 100);
   
    // DIO shape:
    RooRealVar a5("a5", "a5", 8.6434e-17, 8.5e-17, 8.7e-17);
    RooRealVar a6("a6", "a6", 1.16874e-17, 1.1e-17, 1.2e-17);
    RooRealVar a7("a7", "a7", -1.87828e-19, -1.9e-19, -1.8e-19);
    RooRealVar a8("a8", "a8", 9.16327e-20, 9.1e-20, 9.2e-20);
    RooRealVar ndio("ndio", "number in dio region", 0.0, 0.0, 100000);
    RooPol58 DIO("DIO", "dio tail", recomom, a5, a6, a7, a8);
    
    
    //combined binned ML (extended)
    RooAddPdf fitFun("fitFun", "Sig + DIO  ", RooArgList(Sig, DIO), RooArgList(nsig, ndio)); 
```

we are parameterizing the conversion electron as a crystal ball and the DIO spectrum using the czernecki et al theoetical distribution (CITE). The overall fit function is a sum of the two.

We are using an extended fit which allows us to extract the yields of signal (nsig) and DIO (ndio).

Now set up the Likelihood fit

```  
    TCanvas *can2 = new TCanvas("can2","");
    RooPlot *chFrame2 = nsig.frame(RooFit::Bins(60), RooFit::Range(-1,100));
    RooAbsReal* nll = fitFun.createNLL(chMom);

    RooMinimizer m(*nll);
    m.migrad();
    m.hesse();
    RooFitResult *fitRes = m.save();
    
    nll->plotOn(chFrame2, RooFit::ShiftToZero(), LineColor(kRed), LineStyle(1), Name("nll"));
    chFrame2->SetMinimum(-1);
    chFrame2->SetMaximum(5);
    chFrame2->Draw();
    can2 -> Update();
    can2 -> SaveAs("nll.root");
    std::cout<<fitRes<<std::endl;

```

Here you are using the migrad and hesse algorithms to minimze the negative log likelihood (nll). The likelihood is the combined Sig+DIO extended distribution.

Plot the resulting fit:
 
``` 
    TCanvas *can = new TCanvas("can", "", 100, 100, 600, 600);
    
    RooPlot *chFrame = recomom.frame(Title(""));
    chMom.plotOn(chFrame, MarkerColor(kBlack), LineColor(kBlack), MarkerSize(0.5), Name("chMom"));
    fitFun.plotOn(chFrame, LineColor(kGreen), LineStyle(1), Name("combFit"));
 ```
 you are plotting the fit function onto your histogrammed data.
 
 Find the chisquare goodness of fit:
 
 ```   
    float chiSq = chFrame->chiSquare(11);
    std::cout << "chi2: " << chiSq << "; Probability: " << Prob(chiSq, 151) << std::endl;
```

set the axis labels, use a log so we can see relatively small signal:

```
    chFrame -> SetYTitle("Events per 25 keV");
    chFrame -> SetXTitle("Reconstructed Mom at TrkEnt [MeV/c]");
    can -> Draw();
    can -> SetLogy();
    can -> Update();
    can -> SaveAs("CombinedFitResult.root");  
```

Save this and run.

### Inspecting results

You should have two .root files: CombinedFitResult.root and nll.root. View these in a TBrowser:

```
root *.root
root [0] TBrowser p
```
CombinedFitResult shows the data fitted with the green combined fit PDF. The nll.root shows how the negative log likelihood minimize on the yeild of signal events.
