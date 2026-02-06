#include <TFormula.h>
#include <TPad.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>
#include <iostream>
#include <array>

void hist(){
    // drawing of the set up and pictures of labels to draw
    // take pictures
    // 100 bins 0-500 range
    // 346 NaI, 347 LSO

    std::string feature      = "B01_PMT1_ADC";
    std::string fileNames[2] = {"data/out-feb-45F6379E-000344.root","data/out-feb-4944044F-000344.root"};
    int colors[2] = {632, 400};

    int size  = 8;
    int files = 2;

    TH1F *hist[files][size][size];

    for (int f = 0; f < files; f++){

        std::string fileName = fileNames[f];

        TFile *inFile = TFile::Open(fileName.c_str(), "READ");
        TTree *inTree = (TTree*)inFile->Get("mdfTree;1");

        UShort_t featureAddress[size][size];
        
        int numOfEntries = inTree->GetEntries();
        inTree->SetBranchAddress(feature.c_str(), featureAddress);

        for (int x = 0; x < size; x++){
            for (int y = 0; y < size; y++){

                hist[f][x][y] = new TH1F(Form("hist_%d_%d", x, y), Form("%s_%d_%d", feature.c_str(), x+1, y+1), 5, 20, 5);

                for (int entryIndex = 0; entryIndex < numOfEntries; entryIndex++) {
                    inTree->GetEntry(entryIndex);
                    UShort_t entry  = featureAddress[x][y];
                    hist[f][x][y]->Fill(entry);
                }

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

    for (int f = 0; f < files; f++){
        for (int x = 0; x < size; x++) {
            for (int y = 0; y < size; y++) {
                
                canvas->cd((y*size + x)+1);
                gPad->SetLeftMargin(margins);
                gPad->SetRightMargin(margins);
                gPad->SetTopMargin(margins);
                gPad->SetBottomMargin(margins);
                hist[f][x][y]->SetLineColor(colors[f]);
                hist[f][x][y]->Draw("SAME");
            }
        }
    }

 
    canvas->Update();

}