#include <iostream>
#include <TFile.h>
#include <TH1F.h>
#include <TTree.h>
#include <TCanvas.h>
#include <TObjArray.h>
#include <TLeafI.h>


int histDataAnalysis(){
    

    TH1F h("h", "My Notebook Histo;x;#", 64, -4, 4);

    TRandom3 r(1);
    for (auto i : ROOT::TSeqI(1000)) h.Fill(r.Gaus());



    auto f1 = new TF1("f1","gaus",-10,10);
    f1->SetParameters(100,0,1);

    auto res = h.Fit(f1, "SE");


    h.SetLineColor(kBlue);
    h.SetFillColor(kBlue);
    TCanvas c;

    h.Draw();
    c.Draw();
  
    c.Print("c.png");

    return 0;
}
