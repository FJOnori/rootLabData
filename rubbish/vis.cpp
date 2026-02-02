#include <iostream>
#include <vector>
#include "TFile.h"
#include "TTree.h"

void vis(){

        // TFile *file = TFile::Open("data/out-feb-45F6379E-000345.root", "READ");
    
    // TTree *tree = (TTree*)file->Get("mdfTree;1");
    // if (!tree) {
    //     std::cerr << "No tree!" << std::endl;
    //     return 0;
    // }
    
    // TObjArray *leaves = tree->GetListOfLeaves();
    // if (!leaves) {
    //     std::cerr << "No leaves found in branch!" << std::endl;
    //     return 0;
    // }
    
    // TObjArray* arr = (TObjArray*)tree->GetListOfBranches();
    // Int_t* leaf = (Int_t*)leaves->GetEntries();

    // std::cout << *leaf << std::endl;

    // int value = leaf->GetValue();
    // std::cout << "Leaf " << leaf->GetName() << " = " << value << std::endl;

    // file->Close();

    // tree->GetBranch("sumTotalHits")->Print();
    // tree->Scan("sumTotalHits", "", "", 10);
    // std::cout << std::endl;
    // tree->GetBranch("sumTotalHits")->GetListOfLeaves()->Print();

    // UInt_t sumTotalHits;
    // tree->SetBranchAddress("sumTotalHits", &sumTotalHits);
    // tree->GetEntry(0);

    // TLeaf *leaf = tree->GetLeaf(0);

    // UInt_t value;
    // leaf->SetAddress(&value);

    // std::cout << value << std::endl;







    // TBranch* branch = tree->GetBranch("B01_MAR2_ADC");



    std::string inf = "data/out-feb-45F6379E-000344.root";
    std::string tn  = "mdfTree;1";
    std::string lf  = "B01_MAR2_ADC";
    std::string ouf = "data/out-feb-45F6379E-000344-hist.root";

    // Opens file
    TFile* InFile = TFile::Open(inf.c_str(), "READ");

    //defines tree in c++
    TTree* tree = (TTree*)InFile->Get(tn.c_str());
    // tree->Print();

    Long64_t nEntries = tree->GetEntries();
    std::vector<UShort_t> value(nEntries);
    tree->SetBranchAddress(lf.c_str(), value.data());
    std::vector<UShort_t> allEntries; 

    // for (Long64_t i = 0; i < nEntries; ++i) {
    //     tree->GetEntry(i);
    //     std::cout << value << std::endl;
    // }

    for (int n = 0; n < 100; n++){
        tree->GetEntry(n);
        std::cout << value[n] << std::endl;
        
        for (int j = 0; j < 64; ++j) {
            allEntries.push_back(value[j]);
        }

    }

    InFile->Close(); 
}

    std::cout << "Number of entries: " << inTree->GetEntries() << std::endl;
    // inTree->Print();

    // auto *inBranch = inTree->GetBranch("lep_pt");

    auto *background = new TF1("background", "(1.0/[0])*exp(-[0]*x)");
    auto *signal     = new TF1("signal", "gaus");

    signal->SetRange(0,10);
    background->SetRange(0,10);

    //amplitude, mean, standard deviation
    signal->SetLineColor(4);
    signal->SetLineWidth(3);
    signal->SetParameters(0.25, 5.0, 0.5);

    background->SetLineColor(3);
    background->SetLineWidth(3);
    background->SetParameters(0.2);

    auto *total = new TF1("total", "(1.0/10.0)*(background)+(9.0/10.0)*(signal)");

    total->SetRange(0,10);
    total->SetLineColor(2);
    total->SetLineWidth(3);
    total->SetParameters(0.2);






    // std::vector<float> dataEntries(tree->GetEntries());
    // tree->SetBranchAddress(featureName.c_str(), dataEntries.data());

    // TH1D hist("data","hist", 150, -2, 2);
    // hist.Sumw2();

    // for (Long64_t entry = 0; entry < tree->GetEntries(); entry++){
    //     tree->GetEntry(entry);
    //     std::cout << vec->at(0) < std::endl;

    // }

    // std::cout << "Hist Done!" << std::endl;

    // hist.SetDirectory(0);
    // InFile->Close(); 
    
    // TFile* OutFile = TFile::Open(OutFileName.c_str(), "RECREATE");
    // OutFile->cd();
    // hist.Write();
    // OutFile->Close();



    ///
void hist(){

    std::string fileName = "data/out-feb-4944044F-000344.root";
    TFile *inFile = TFile::Open(fileName.c_str(), "READ");
    TTree *inTree = (TTree*)inFile->Get("mdfTree;1");

    std::cout << "Opening file " << inFile << std::endl;
    std::cout << "Opening Tree " << inTree << std::endl;

    //ADC counts, amplitude of the pmt signal digitizied 
    std::string feature = "B01_PMT1_ADC";
    
    UShort_t photon_n_mem[8][8];
    TH1F* hist[8][8];
    int numOfEntries = inTree->GetEntries();
    inTree->SetBranchAddress(feature.c_str(), photon_n_mem);


    for (int entryIndex = 0; entryIndex < 20; entryIndex++) {
        inTree->GetEntry(entryIndex);
        UShort_t value1 = photon_n_mem[0][0];
        UShort_t value0 = photon_n_mem[4][4];

        std::cout << value0 << " " << value1 << std::endl;

        
    }