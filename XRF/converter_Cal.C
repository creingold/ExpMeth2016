{
// Edit the following to adjust the calibration parameters
	float parIntercept = 0.00040;
	float parSlope = 0.02978;

	string filename, header, line;
	
	//Promt user for input
	cout << "Please input the filename/path of your csv:\t";
	cin >> filename;
	
	//Check to make sure the file is a .csv
	int period_position = filename.find(".");
	string extension = filename.substr(period_position +1);
	if (extension != "csv"){
		cout << "I only wrote this for csv files, sorry" << endl;
		exit(1);
	}
	
	//Make sure the csv and root files have the same name with different extension
	string rawfile = filename.substr(0, period_position);
	string rootfilename = rawfile.append(".root");
	
	string rawfile2 = filename.substr( 0 , period_position );

	//Declare root file and tree structure
	TFile *outFile = TFile::Open(rootfilename.c_str(), "RECREATE");
	TTree *tree = new TTree("tree", "csv to root tree");
	
	//Read in file
	ifstream fIn(filename.c_str());
	
	//Make sure filename is valid
	if (!fIn){
		cout << c_string << " could not be opened!" << endl;
		exit(1);
	}
	
	//Define variables and make corresponding branches. Use vectors to deal with varying file lengths
	int comma_position, chan, count;
	vector<int> chanvec;
	vector<int> countvec;
	string chanstr, countstr;
	
	tree->Branch("Channels", &chan, "chan/I");
	tree->Branch("Counts", &count, "count/I");
	
	//Get rid of the header line before looping
	getline(fIn, header);
	
	//Loop over whole file
	while(fIn){
		//Parse text for data
		getline(fIn, line);
		comma_position = line.find(",");
		
		chanstr = line.substr(0, comma_position);
		countstr = line.substr(comma_position + 1);
		
		chan = atoi(chanstr.c_str());
		count = atoi(countstr.c_str());
		
		tree->Fill();
		
		chanvec.push_back(chan);
		countvec.push_back(count);
	}
	
	//Convert vector to array with same length
	chanvec.pop_back();
	countvec.pop_back();
	
	const int len = chanvec.size();
	
	int channel[len];
	int counts[len];
	
	for (int i=0; i<chanvec.size(); i++){
		channel[i] = chanvec.at(i);
		counts[i] = countvec.at(i);
	}
	/*Write whole array as one entry in root file (unnecessary)
	stringstream ss;
	ss << len;
	string lenstr = ss.str();
	
	string s1 = "channel[";
	string s2 = "counts[";
	s1 += lenstr;
	s2 += lenstr;
	s1 += "]/I";
	s2 += "]/I";
	
	tree->Branch("Channel Array", channel, s1.c_str());
	tree->Branch("Count Array", counts, s2.c_str());
	*/
	
	//Declare, fill, and draw histogram
	TH1F *h = new TH1F("h", "h", len, 0, len-1);
	h->SetStats(kFALSE);
	
	TH1F *hcal = new TH1F("hcal" , "h with calibration" , len , 0 , len-1);
	hcal->SetStats(kFALSE);

	//Writing a new .csv file for Patricia
	string newfilename = rawfile2.append( "_calibrated.csv" );

	ofstream newcsv( newfilename.c_str() );
	newcsv << "Energy \tCounts" << endl;

	int x, y;
	float energy;
	for (int j=0; j<len; j++){
		x = channel[j];
		energy = parIntercept + parSlope*channel[j];
		y = counts[j];
		h -> Fill(x,y);
		hcal -> Fill( energy , y );
		newcsv << energy << "," << y << endl;
	}
	
	h->Draw();

	
	//Fill tree and write file
	tree->Fill();
	newcsv.close();	
	outFile->Write();
}
