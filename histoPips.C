
void histoPips()
{
  TCanvas *c1 = new TCanvas();
  TFile *input = new TFile("pipsProject.root","read");
  TTree *tree = (TTree*)input->Get("Hits");

  double energy;

  tree->SetBranchAddress("Energy", &energy);

  int entries = tree->GetEntries();

  TH1F *hist = new TH1F("hist", "alpha decay spectrum", entries/10, 6, 7.5);

  for(int i = 0; i < entries; i++)
  {
    tree->GetEntry(i);
    //cout << energy << endl;
    hist->Fill(energy);

  }
//c1->SetLogy();
hist->GetXaxis()->SetTitle("Energy in MeV");
hist->GetYaxis()->SetTitle("Entries");
c1->SetGridx();
c1->SetGridy();


hist->Draw();



 //input->Close();


}
