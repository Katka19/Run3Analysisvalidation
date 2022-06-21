void processYield(const char* pinFileFname = "dphi_corr.root", double absDeltaEtaMin = 1.4, double absDeltaEtaMax = 2.0, const char* poutFileName = "yield.root", uint flags = 0)
{
  // Nct represents the multiplicity interval of the analysis, here given in ranges of Ntracks. 
  static Double_t Nct[] = {2.5, 8.0, 13.0, 20.5};
  // Nbins is the number of multiplicity bins
  static const uint Nbins = sizeof(Nct) / sizeof(Nct[0]);
  const double absDeltaPhi = 1.3; // y-projection range

  TFile* pf = new TFile(pinFileFname, "read");
  TFile* pfout = new TFile(poutFileName, "recreate");
  pfout->cd();

  const uint trigCount = 2;
  TH1D* pltf1[trigCount][trigCount][Nbins] = {0};

  for (uint itrig = 0; itrig < trigCount; ++itrig) {
    for (uint iassoc = 0; iassoc <= itrig; ++iassoc) {
      TGraphErrors* pridgeYield = new TGraphErrors(Nbins);
      TGraphErrors* pfarYield = new TGraphErrors(Nbins);
      TGraphErrors* pfragYield = new TGraphErrors(Nbins);
      for (uint ib = 0; ib < Nbins; ++ib) {
        TH2D* ph = (TH2D*)pf->Get(Form("dphi_%u_%u_%u", itrig, iassoc, ib));
        if (!ph) {
          printf("No histograms corresponding mult bin %u. (itrig=%u, iassoc=%u)\n", ib, itrig, iassoc);
          continue;
        } // if histogram not existing
      } // loop over the index of the multiplicity interval
    } // loop over the index of the associated particle
  } // loop over the index of the trigger particle
}// end of processYield
