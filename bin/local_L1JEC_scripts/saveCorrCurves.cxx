#include "TFile.h"
#include "TGraphErrors.h"
#include "TH1F.h"
#include <iostream>
#include <TCanvas.h>

// $ root -q -b -l "$CMSSW_BASE/src/L1Trigger/L1JetEnergyCorrections/bin/local_L1JEC_scripts/saveCorrCurves.cxx+"

void loadAndSave(std::string inputFile, std::string graphName, std::string etaRange)
{
	TFile * f = TFile::Open(inputFile.c_str());

	TGraphErrors * graph = (TGraphErrors*)f->Get(graphName.c_str());
	TF1 * func = (TF1*)f->Get("EDITFIT_fitfcneta_0_0.435");
	// TH1D * h = new TH1D("h", "", 1, 0, 600);
	// h->GetYaxis()->SetRangeUser(0.97,2.03);
	// // h->GetXaxis()->SetTitle("Level-1 Jet E_{T} (GeV)");
	// h->GetXaxis()->SetTitleOffset(1.05);
	// h->GetXaxis()->SetTitleSize(0.046);
	// h->GetYaxis()->SetTitleOffset(1.01);
	// h->GetYaxis()->SetTitleSize(0.046);	
	// h->GetYaxis()->SetTitle("correction factor");

	gStyle->SetPadTickX(1);
	gStyle->SetPadTickY(1);
	gStyle->SetOptStat(1);
	gStyle->SetTitleY(0.965);
	gStyle->SetLegendTextSize(0.05);
	TCanvas * c = new TCanvas("c","",800,600);
		
	gStyle->SetEndErrorSize(2);
	graph->SetLineWidth(2);
	// graph->SetLineColorAlpha(kBlue, 0.30);
	graph->SetLineColor(kBlue+1);
	graph->SetMarkerSize(3);

	graph->SetTitle("0 < |#eta^{L1}| < 0.435");
	// graph->SetTitleOffset(1.05);
	graph->GetHistogram()->SetMaximum(2.03);
	graph->GetHistogram()->SetMinimum(0.97);
	graph->GetXaxis()->SetRangeUser(0, 600);
	graph->GetXaxis()->SetTitle("#LTE_{T}^{L1}#GT (GeV)");
	graph->GetXaxis()->SetTitleSize(0.046);
	graph->GetXaxis()->SetTitleOffset(0.97);
	graph->GetYaxis()->SetTitle("#LTE_{T}^{L1} / E_{T}^{ref}#GT^{-1}");
	graph->GetYaxis()->SetTitleSize(0.046);
	graph->GetYaxis()->SetTitleOffset(0.95);

	graph->Draw("AP");
	
	func->SetLineWidth(5);
	func->SetLineColorAlpha(kRed, 0.70);
	func->Draw("same");
	
	graph->Draw("P, same");

	TLegend * leg3 = new TLegend(0.45,0.67,0.83,0.83);
	leg3->SetBorderSize(0);

	TGraphErrors * grFake = new TGraphErrors(0);
	grFake->SetMarkerStyle(21);
	grFake->SetMarkerColor(kBlue+1);
	grFake->SetMarkerSize(2);

	leg3->AddEntry(grFake, "points from E_{T}^{ref} bins", "p");
	leg3->AddEntry(func, "fit to graph", "L");
	leg3->Draw();

	gPad->RedrawAxis();
	std::string saveName = graphName+".pdf";	
	c->SaveAs(saveName.c_str());

}

void saveCorrCurves()
{
	std::string inputFile = "EDIT.root";

	loadAndSave(inputFile.c_str(), "l1corr_eta_0_0.435", "eta_0_0.435");
	// loadAndSave(inputFile.c_str(), "EDITFIT_l1corr_eta_0.435_0.783_fit", "eta_0.435_0.783");
	// loadAndSave(inputFile.c_str(), "EDITFIT_l1corr_eta_0.783_1.131_fit", "eta_0.783_1.131");
	// loadAndSave(inputFile.c_str(), "EDITFIT_l1corr_eta_1.131_1.305_fit", "eta_1.131_1.305");
	// loadAndSave(inputFile.c_str(), "EDITFIT_l1corr_eta_1.305_1.479_fit", "eta_1.305_1.479");
	// loadAndSave(inputFile.c_str(), "EDITFIT_l1corr_eta_1.479_1.653_fit", "eta_1.479_1.653");
	// loadAndSave(inputFile.c_str(), "EDITFIT_l1corr_eta_1.653_1.83_fit", "eta_1.653_1.83");
	// loadAndSave(inputFile.c_str(), "EDITFIT_l1corr_eta_1.83_1.93_fit", "eta_1.83_1.93");	
	// loadAndSave(inputFile.c_str(), "EDITFIT_l1corr_eta_1.93_2.043_fit", "eta_1.93_2.043");
	// loadAndSave(inputFile.c_str(), "EDITFIT_l1corr_eta_2.043_2.172_fit", "eta_2.043_2.172");
	// loadAndSave(inputFile.c_str(), "EDITFIT_l1corr_eta_2.172_2.322_fit", "eta_2.172_2.322");
	// loadAndSave(inputFile.c_str(), "EDITFIT_l1corr_eta_2.322_2.5_fit", "eta_2.322_2.5");
	// loadAndSave(inputFile.c_str(), "EDITFIT_l1corr_eta_2.5_2.964_fit", "eta_2.5_2.964");
	// loadAndSave(inputFile.c_str(), "EDITFIT_l1corr_eta_2.964_3.489_fit", "eta_2.964_3.489");
	// loadAndSave(inputFile.c_str(), "EDITFIT_l1corr_eta_3.489_4.191_fit", "eta_3.489_4.191");
	// loadAndSave(inputFile.c_str(), "EDITFIT_l1corr_eta_4.191_5.191_fit", "eta_4.191_5.191");	

}