{
	string filename;
	cout << "Please input the filename/path:\t";
	cin >> filename;
	int period_position = filename.find(".");
	
	string rawfile = filename.substr(0, period_position);
	string rootfilename = rawfile.append(".root");
	
	TFile *outFile = TFile::Open(rootfilename.c_str(), "RECREATE");
	TTree *tree = new TTree("tree", "csv to root tree");
	
	ifstream fIn(filename.c_str());
	
	if (!fIn){
		cout << c_string << " could not be opened!" << endl;
		exit(1);
	}
	
	float time;
	int count;
	
	TH1F *h = new TH1F("h", "h", 8192, 0, 8191);
	h->SetStats(kFALSE);
	
	tree->Branch("Time", &time, "chan/F");
	tree->Branch("Counts", &count, "count/I");
	
	while(fIn){
		fIn >> time;
		fIn >> count;
		h->Fill(time, count);
		tree->Fill();
	}
	
	h->Draw();
	
	outFile -> Write();
}