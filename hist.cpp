#include <TFormula.h>
#include <TPad.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>
#include <iostream>

void hist(std::string feature = "B01_PMT1_ADC", std::string fileName = "data/out-feb-45F6379E-000345.root"){

    int size = 8;

    TFile *inFile = TFile::Open(fileName.c_str(), "READ");
    TTree *inTree = (TTree*)inFile->Get("mdfTree;1");

    UShort_t featureAddress[size][size];
    TH1F *hist[size][size];
    int numOfEntries = inTree->GetEntries();
    inTree->SetBranchAddress(feature.c_str(), featureAddress);

    for (int x = 0; x < size; x++){
        for (int y = 0; y < size; y++){

            Double_t xmin = inTree->GetMinimum(feature.c_str());
            Double_t xmax = inTree->GetMaximum(feature.c_str());

            hist[x][y] = new TH1F(Form("hist_%d_%d", x, y), Form("%s_%d_%d", feature.c_str(), x+1, y+1), xmin, xmax, 20);

            for (int entryIndex = 0; entryIndex < numOfEntries; entryIndex++) {
                inTree->GetEntry(entryIndex);
                UShort_t entry  = featureAddress[x][y];
                hist[x][y]->Fill(entry);
            }
        }
    }

    int topX       = 200;
    int topY       = 10;
    int width      = 500;
    int height     = 400;
    float margins  = 0.001;
    auto *canvas = new TCanvas("canvas", "Signal Example", topX, topY, width, height);
    
    canvas->Divide(size, size);

    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            canvas->cd((y*size + x)+1);
            gPad->SetLeftMargin(margins);
            gPad->SetRightMargin(margins);
            gPad->SetTopMargin(margins);
            gPad->SetBottomMargin(margins);
            hist[x][y]->Draw();
        }
    }

    canvas->Update();

}