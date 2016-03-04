{
	TFile *ag = new TFile("AgCal.root");
	TFile *ba = new TFile("BaCal.root");
	TFile *cu = new TFile("CuCal.root");
	TFile *mo = new TFile("MoCal.root");
	TFile *rb = new TFile("RbCal.root");
	TFile *tb = new TFile("TbCal.root");

	ag->cd();
	TH1 *hAg = (TH1*) h->Clone();
	hAg -> SetName("hAg");
	TH1 *hAgCal = (TH1*) hcal->Clone();
	hAgCal->SetName("hAgCal");
	hAg -> SetLineColor(13);
	hAg -> SetFillColor(11);
	hAgCal->SetLineColor(1);
	hAgCal->SetFillColor(1);

	ba->cd();
	TH1 *hBa = (TH1*) h->Clone();
	hBa -> SetName("hBa");
	TH1 *hBaCal = (TH1*) hcal->Clone();
	hBaCal->SetName("hBaCal");
	hBa -> SetLineColor(12);
	hBa -> SetFillColor(12);
	hBaCal->SetLineColor(12);
	hBaCal->SetFillColor(12);

	cu->cd();
	TH1 *hCu = (TH1*) h->Clone();
	hCu -> SetName("hCu");
	TH1 *hCuCal = (TH1*) hcal->Clone();
	hCuCal->SetName("hCuCal");
	hCu -> SetLineColor(14);
	hCu -> SetFillColor(14);
	hCuCal->SetLineColor(14);
	hCuCal->SetFillColor(14);

	mo->cd();
	TH1 *hMo = (TH1*) h->Clone();
	hMo -> SetName("hMo");
	TH1 *hMoCal = (TH1*) hcal->Clone();
	hMoCal->SetName("hMoCal");
	hMo -> SetLineColor(15);
	hMo -> SetFillColor(16);
	hMoCal->SetLineColor(16);
	hMoCal->SetFillColor(16);

	rb->cd();
	TH1 *hRb = (TH1*) h->Clone();
	hRb -> SetName("hRb");
	TH1 *hRbCal = (TH1*) hcal->Clone();
	hRbCal -> SetName("hRbCal");
	hRb -> SetLineColor(1);
	hRb -> SetFillColor(1);
	hRbCal->SetLineColor(1);
	hRbCal->SetFillColor(0);

	tb->cd();
	TH1 *hTb = (TH1*) h->Clone();
	hTb -> SetName("hTb");
	TH1 *hTbCal = (TH1*) hcal->Clone();
	hTbCal->SetName("hTbCal");
	hTb -> SetLineColor(1);
	hTb -> SetFillColor(17);
	hTb -> SetLineStyle(1);
	hTbCal->SetLineColor(12);
	hTbCal->SetFillColor(12);
//Now that that's over with...
	TCanvas *cUncal = new TCanvas("cUncal" , "Uncalibrated", 1200 , 720);
//	TCanvas *cCal = new TCanvas("cCal" , "Calibrated");

	cUncal->cd();
	hAg->Draw();
	hBa->Draw("same");
	hCu->Draw("same");
	hMo->Draw("same");
	hRb->Draw("same");
	hTb->Draw("same");

	hAg->SetTitle("Calibration");
	hAg->SetTitleSize(0.09);
	hAg->GetXaxis()->SetTitle("Channel");
	hAg->GetYaxis()->SetTitle("Counts");
	hAg->GetXaxis()->SetTitleSize(0.06);
	hAg->GetYaxis()->SetTitleSize(0.06);
	hAg->GetXaxis()->SetTitleOffset(0.6);
	hAg->GetYaxis()->SetTitleOffset(0.7);
	hAg->GetXaxis()->CenterTitle();
	hAg->GetYaxis()->CenterTitle();

	leg = new TLegend( 0.7 , 0.6 , 0.9 , 0.9 );
	leg->SetTextSize(0.04);
	leg->SetHeader("Calibration Sources");
	leg->AddEntry(hAg , "Ag" , "f");
	leg->AddEntry(hBa , "Ba" , "f");
	leg->AddEntry(hCu , "Cu" , "f");
	leg->AddEntry(hMo , "Mo" , "f");
	leg->AddEntry(hRb , "Rb" , "f");
	leg->AddEntry(hTb , "Tb" , "f");
	leg->Draw();

//	cCal->cd();
//	hAgCal->Draw();
//	hBaCal->Draw("same");
//	hCuCal->Draw("same");
//	hMoCal->Draw("same");
//	hRbCal->Draw("same");
//	hTbCal->Draw("same");
}
