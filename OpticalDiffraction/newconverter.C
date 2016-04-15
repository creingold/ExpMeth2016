{
	string filename;
	cout << "Please input the filename/path:\t";
	cin >> filename;
	
	TCanvas *c1 = new TCanvas("c", "Fast Fourier Transform", 1600, 600);
	c1->Divide(2,1);
	c1->cd(1);
	
	int period_position = filename.find(".");
	
	string rawfile = filename.substr(0, period_position);
	string rootfilename = rawfile.append(".root");
	
	TFile *outFile = TFile::Open(rootfilename.c_str(), "RECREATE");
	TTree *tree = new TTree("tree", "csv to root tree");
	
	ifstream fIn(filename.c_str());
	
	if (!fIn){
		cout << filename.c_str() << " could not be opened!" << endl;
		exit(1);
	}
	
	float time, pos;
	int count;
	
	TH1F *h = new TH1F("h", "h", 601, 0, 150);
	h->SetStats(kFALSE);
	h->SetTitle(rawfile.c_str());
	
	h->GetXaxis()->SetTitle("Position (mm)");
	h->GetXaxis()->CenterTitle();
	
	h->GetYaxis()->SetTitle("Intensity");
	h->GetYaxis()->CenterTitle();
	
	tree->Branch("Position (mm)", &pos, "pos/F");
	tree->Branch("Counts", &count, "count/I");
	
	while(fIn){
		fIn >> time;
		fIn >> count;
		pos = 0.25*time;
		h->Fill(pos, count);
		tree->Fill();
	}
	
	h->Draw();
	c1->cd(2);
	
	/*TH1 *hfft =0;
	TVirtualFFT::SetTransform(0);
	hfft = h->FFT(hfft, "MAG");
	hfft->SetTitle("Fourier Transform");
	hfft->Draw();
	*/
	outFile -> Write();
}