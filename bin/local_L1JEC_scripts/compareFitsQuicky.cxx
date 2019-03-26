#include "TFile.h"
#include "TF1.h"
#include <iostream>
#include "TLegend.h"
#include "TStyle.h"
#include "TAxis.h"
#include "TColor.h"
#include <TCanvas.h>

// script for plotting all fits for all eta bins together
// good for studying variation with eta
// 
// TO RUN: just set the directory, and the input and output files
// $ root -q -b -l "/users/jt15104/CMSSW_8_0_9/src/L1Trigger/L1JetEnergyCorrections/bin/local_L1JEC_scripts/compareFitsQuicky.cxx+"

void makePlots_allTTetaBinningGroupedColours(std::string,std::string,std::string);
void makePlots_allTTetaBinning(std::string,std::string,std::string);
void makePlots_sel16etaBinning(std::string,std::string,std::string);

void compareFitsQuicky(){

	std::string directory = "progress/";
	
	std::string addOnInfo = "";

	// std::string inputFile1 = "fitsPU0to10.root";
	// std::string outputName1 = "plotFitsPU0to10" + addOnInfo + ".pdf";

	// std::string inputFile2 = "fitsPU15to25.root";
	// std::string outputName2 = "plotFitsPU15to25" + addOnInfo + ".pdf";

	std::string inputFile3 = "FINAL_testPU30to40_FIRSTEDIT.root";
	std::string outputName3 = "FINAL_testPU30to40_v1" + addOnInfo + ".pdf";

	// std::string inputFile4 = "fitsPU45to55.root";
	// std::string outputName4 = "plotFitsPU45to55" + addOnInfo + ".pdf";

	// makePlots_allTTetaBinning(inputFile1, outputName1, directory);
	// makePlots_allTTetaBinning(inputFile2, outputName2, directory);
	makePlots_allTTetaBinningGroupedColours(inputFile3, outputName3, directory);
	// makePlots_allTTetaBinning(inputFile4, outputName4, directory);

	// makePlots_sel16etaBinning(inputFile1, outputName1, directory);
	// makePlots_sel16etaBinning(inputFile2, outputName2, directory);
	// makePlots_sel16etaBinning(inputFile3, outputName3, directory);
	// makePlots_sel16etaBinning(inputFile4, outputName4, directory);	
}


void makePlots_allTTetaBinningGroupedColours(std::string inputFile, std::string outputFile, std::string directory){

	std::string inputPath = directory + inputFile;
	std::string outputPath = directory + outputFile;

	TFile * f = TFile::Open(inputPath.c_str());

	TF1 * g01 = (TF1*)f->Get("EDITFIT_fitfcneta_0_0.087");
	TF1 * g02 = (TF1*)f->Get("EDITFIT_fitfcneta_0.087_0.174");
	TF1 * g03 = (TF1*)f->Get("EDITFIT_fitfcneta_0.174_0.261");
	TF1 * g04 = (TF1*)f->Get("EDITFIT_fitfcneta_0.261_0.348");
	TF1 * g05 = (TF1*)f->Get("EDITFIT_fitfcneta_0.348_0.435");
	TF1 * g06 = (TF1*)f->Get("EDITFIT_fitfcneta_0.435_0.522");
	TF1 * g07 = (TF1*)f->Get("EDITFIT_fitfcneta_0.522_0.609");
	TF1 * g08 = (TF1*)f->Get("EDITFIT_fitfcneta_0.609_0.696");
	TF1 * g09 = (TF1*)f->Get("EDITFIT_fitfcneta_0.696_0.783");
	TF1 * g10 = (TF1*)f->Get("EDITFIT_fitfcneta_0.783_0.87");
	TF1 * g11 = (TF1*)f->Get("EDITFIT_fitfcneta_0.87_0.957");
	TF1 * g12 = (TF1*)f->Get("EDITFIT_fitfcneta_0.957_1.044");
	TF1 * g13 = (TF1*)f->Get("EDITFIT_fitfcneta_1.044_1.131");
	TF1 * g14 = (TF1*)f->Get("EDITFIT_fitfcneta_1.131_1.218");
	TF1 * g15 = (TF1*)f->Get("EDITFIT_fitfcneta_1.218_1.305");
	TF1 * g16 = (TF1*)f->Get("EDITFIT_fitfcneta_1.305_1.392");
	TF1 * g17 = (TF1*)f->Get("EDITFIT_fitfcneta_1.392_1.479");
	TF1 * g18 = (TF1*)f->Get("EDITFIT_fitfcneta_1.479_1.566");
	TF1 * g19 = (TF1*)f->Get("EDITFIT_fitfcneta_1.566_1.653");
	TF1 * g20 = (TF1*)f->Get("EDITFIT_fitfcneta_1.653_1.74");
	TF1 * g21 = (TF1*)f->Get("EDITFIT_fitfcneta_1.74_1.83");
	TF1 * g22 = (TF1*)f->Get("EDITFIT_fitfcneta_1.83_1.93");
	TF1 * g23 = (TF1*)f->Get("EDITFIT_fitfcneta_1.93_2.043");
	TF1 * g24 = (TF1*)f->Get("EDITFIT_fitfcneta_2.043_2.172");
	TF1 * g25 = (TF1*)f->Get("EDITFIT_fitfcneta_2.172_2.322");
	TF1 * g26 = (TF1*)f->Get("EDITFIT_fitfcneta_2.322_2.5");
	TF1 * g27 = (TF1*)f->Get("EDITFIT_fitfcneta_2.5_2.65");
	TF1 * g28 = (TF1*)f->Get("EDITFIT_fitfcneta_2.65_2.964");
	// TF1 * g29 = (TF1*)f->Get("EDITFIT_fitfcneta_2.65_2.964");
	TF1 * g30 = (TF1*)f->Get("EDITFIT_fitfcneta_2.964_3.139");
	TF1 * g31 = (TF1*)f->Get("EDITFIT_fitfcneta_3.139_3.314");
	TF1 * g32 = (TF1*)f->Get("EDITFIT_fitfcneta_3.314_3.489");
	TF1 * g33 = (TF1*)f->Get("EDITFIT_fitfcneta_3.489_3.664");
	TF1 * g34 = (TF1*)f->Get("EDITFIT_fitfcneta_3.664_3.839");
	TF1 * g35 = (TF1*)f->Get("EDITFIT_fitfcneta_3.839_4.013");
	TF1 * g36 = (TF1*)f->Get("EDITFIT_fitfcneta_4.013_4.191");
	TF1 * g37 = (TF1*)f->Get("EDITFIT_fitfcneta_4.191_4.363");
	// TF1 * g38 = (TF1*)f->Get("EDITFIT_fitfcneta_4.363_4.538");
	// TF1 * g39 = (TF1*)f->Get("fitfcneta_4.538_4.716");
	// TF1 * g40 = (TF1*)f->Get("fitfcneta_4.716_4.889");
	// TF1 * g41 = (TF1*)f->Get("fitfcneta_4.889_5.191");

gStyle->SetPadTickX(1);
gStyle->SetPadTickY(1);

// double colorIndex = (1.0/37.0 + 0.0) * gStyle->GetNumberOfColors()
	// gStyle->SetPalette(kGreenPink);
	// gStyle->SetPalette(kVisibleSpectrum);
	// gStyle->SetPalette(kAvocado);
	gStyle->SetPalette(kBlueGreenYellow);
	// gStyle->SetPalette(kBird);
	g01->SetLineColor( gStyle->GetColorPalette( (1.0/17.0 + 0.0) * gStyle->GetNumberOfColors() ) );
	g02->SetLineColor( gStyle->GetColorPalette( (2.0/17.0 + 0.0) * gStyle->GetNumberOfColors() ) );
	g03->SetLineColor( gStyle->GetColorPalette( (3.0/17.0 + 0.0) * gStyle->GetNumberOfColors() ) );
	g04->SetLineColor( gStyle->GetColorPalette( (4.0/17.0 + 0.0) * gStyle->GetNumberOfColors() ) );
	g05->SetLineColor( gStyle->GetColorPalette( (5.0/17.0 + 0.0) * gStyle->GetNumberOfColors() ) );
	g06->SetLineColor( gStyle->GetColorPalette( (6.0/17.0 + 0.0) * gStyle->GetNumberOfColors() ) );
	g07->SetLineColor( gStyle->GetColorPalette( (7.0/17.0 + 0.0) * gStyle->GetNumberOfColors() ) );
	g08->SetLineColor( gStyle->GetColorPalette( (8.0/17.0 + 0.0) * gStyle->GetNumberOfColors() ) );
	g09->SetLineColor( gStyle->GetColorPalette( (9.0/17.0 + 0.0) * gStyle->GetNumberOfColors() ) );
	g10->SetLineColor( gStyle->GetColorPalette( (10.0/17.0 + 0.0) * gStyle->GetNumberOfColors() ) );
	g11->SetLineColor( gStyle->GetColorPalette( (11.0/17.0 + 0.0) * gStyle->GetNumberOfColors() ) );
	g12->SetLineColor( gStyle->GetColorPalette( (12.0/17.0 + 0.0) * gStyle->GetNumberOfColors() ) );
	g13->SetLineColor( gStyle->GetColorPalette( (13.0/17.0 + 0.0) * gStyle->GetNumberOfColors() ) );
	g14->SetLineColor( gStyle->GetColorPalette( (14.0/17.0 + 0.0) * gStyle->GetNumberOfColors() ) );
	g15->SetLineColor( gStyle->GetColorPalette( (15.0/17.0 + 0.0) * gStyle->GetNumberOfColors() ) );
	g16->SetLineColor( gStyle->GetColorPalette( (16.0/17.0 + 0.0) * gStyle->GetNumberOfColors() ) );
	
	// gStyle->SetPalette(kCherry);
	// gStyle->SetPalette(kSolar);
	gStyle->SetPalette(kFruitPunch);
	// gStyle->SetPalette(kBird);
	// g17->SetLineColor( gStyle->GetColorPalette( (1.0/13.0 + 0.0) * gStyle->GetNumberOfColors() ) );
	// g18->SetLineColor( gStyle->GetColorPalette( (2.0/13.0 + 0.0) * gStyle->GetNumberOfColors() ) );
	// g19->SetLineColor( gStyle->GetColorPalette( (3.0/13.0 + 0.0) * gStyle->GetNumberOfColors() ) );
	// g20->SetLineColor( gStyle->GetColorPalette( (4.0/13.0 + 0.0) * gStyle->GetNumberOfColors() ) );
	// g21->SetLineColor( gStyle->GetColorPalette( (5.0/13.0 + 0.0) * gStyle->GetNumberOfColors() ) );
	// g22->SetLineColor( gStyle->GetColorPalette( (6.0/13.0 + 0.0) * gStyle->GetNumberOfColors() ) );
	// g23->SetLineColor( gStyle->GetColorPalette( (7.0/13.0 + 0.0) * gStyle->GetNumberOfColors() ) );	
	// g24->SetLineColor( gStyle->GetColorPalette( (8.0/13.0 + 0.0) * gStyle->GetNumberOfColors() ) );
	// g25->SetLineColor( gStyle->GetColorPalette( (9.0/13.0 + 0.0) * gStyle->GetNumberOfColors() ) );
	// g26->SetLineColor( gStyle->GetColorPalette( (10.0/13.0 + 0.0) * gStyle->GetNumberOfColors() ) );
	// g27->SetLineColor( gStyle->GetColorPalette( (11.0/13.0 + 0.0) * gStyle->GetNumberOfColors() ) );
	// g28->SetLineColor( gStyle->GetColorPalette( (12.0/13.0 + 0.0) * gStyle->GetNumberOfColors() ) );
	g17->SetLineColor( gStyle->GetColorPalette( (12.0/13.0 + 0.0) * gStyle->GetNumberOfColors() ) );
	g18->SetLineColor( gStyle->GetColorPalette( (11.0/13.0 + 0.0) * gStyle->GetNumberOfColors() ) );
	g19->SetLineColor( gStyle->GetColorPalette( (10.0/13.0 + 0.0) * gStyle->GetNumberOfColors() ) );
	g20->SetLineColor( gStyle->GetColorPalette( (9.0/13.0 + 0.0) * gStyle->GetNumberOfColors() ) );
	g21->SetLineColor( gStyle->GetColorPalette( (8.0/13.0 + 0.0) * gStyle->GetNumberOfColors() ) );
	g22->SetLineColor( gStyle->GetColorPalette( (7.0/13.0 + 0.0) * gStyle->GetNumberOfColors() ) );
	g23->SetLineColor( gStyle->GetColorPalette( (6.0/13.0 + 0.0) * gStyle->GetNumberOfColors() ) );	
	g24->SetLineColor( gStyle->GetColorPalette( (5.0/13.0 + 0.0) * gStyle->GetNumberOfColors() ) );
	g25->SetLineColor( gStyle->GetColorPalette( (4.0/13.0 + 0.0) * gStyle->GetNumberOfColors() ) );
	g26->SetLineColor( gStyle->GetColorPalette( (3.0/13.0 + 0.0) * gStyle->GetNumberOfColors() ) );
	g27->SetLineColor( gStyle->GetColorPalette( (2.0/13.0 + 0.0) * gStyle->GetNumberOfColors() ) );
	g28->SetLineColor( gStyle->GetColorPalette( (1.0/13.0 + 0.0) * gStyle->GetNumberOfColors() ) );	

	// gStyle->SetPalette(kAvocado);
	gStyle->SetPalette(kLake);
	// gStyle->SetPalette(kValentine);
	g30->SetLineColor( gStyle->GetColorPalette( (1.0/9.0 + 0.0) * gStyle->GetNumberOfColors() ) );
	g31->SetLineColor( gStyle->GetColorPalette( (2.0/9.0 + 0.0) * gStyle->GetNumberOfColors() ) );
	g32->SetLineColor( gStyle->GetColorPalette( (3.0/9.0 + 0.0) * gStyle->GetNumberOfColors() ) );
	g33->SetLineColor( gStyle->GetColorPalette( (4.0/9.0 + 0.0) * gStyle->GetNumberOfColors() ) );
	g34->SetLineColor( gStyle->GetColorPalette( (5.0/9.0 + 0.0) * gStyle->GetNumberOfColors() ) );
	g35->SetLineColor( gStyle->GetColorPalette( (6.0/9.0 + 0.0) * gStyle->GetNumberOfColors() ) );
	g36->SetLineColor( gStyle->GetColorPalette( (7.0/9.0 + 0.0) * gStyle->GetNumberOfColors() ) );	
	g37->SetLineColor( gStyle->GetColorPalette( (8.0/9.0 + 0.0) * gStyle->GetNumberOfColors() ) );





	// g01->SetLineColor(kBlue+2);
	// g02->SetLineColor(kBlue+2);
	// g03->SetLineColor(kBlue+2);
	// g04->SetLineColor(kBlue+2);
	// g05->SetLineColor(kBlue+2);

	// g06->SetLineColor(kBlue);
	// g07->SetLineColor(kBlue);
	// g08->SetLineColor(kBlue);
	// g09->SetLineColor(kBlue);
	
	// g10->SetLineColor(kCyan+1);
	// g11->SetLineColor(kCyan+1);
	// g12->SetLineColor(kCyan+1);
	// g13->SetLineColor(kCyan+1);
	
	// g14->SetLineColor(kGreen+2);
	// g15->SetLineColor(kGreen+2);
	
	// g16->SetLineColor(kGreen);
	// g17->SetLineColor(kGreen);
	
	// g18->SetLineColor(kYellow+2);
	// g19->SetLineColor(kYellow+2);
	
	// g20->SetLineColor(kOrange);
	// g21->SetLineColor(kOrange);
	
	// g22->SetLineColor(kOrange+7);
	
	// g23->SetLineColor(kRed+2);	
	
	// g24->SetLineColor(kRed);
	
	// g25->SetLineColor(kMagenta+3);
	
	// g26->SetLineColor(kMagenta);
	
	// g27->SetLineColor(kBlue+2);
	// g28->SetLineColor(kBlue+2);
	
	// g30->SetLineColor(kCyan+1);
	// g31->SetLineColor(kCyan+1);
	// g32->SetLineColor(kCyan+1);
	
	// g33->SetLineColor(kGreen+2);
	// g34->SetLineColor(kGreen+2);
	// g35->SetLineColor(kGreen+2);
	// g36->SetLineColor(kGreen+2);
	
	// g37->SetLineColor(kGreen);
	// g38->SetLineColor(kGreen);
	// // g39->SetLineColor(kGreen);
	// // g40->SetLineColor(kGreen);
	// // g41->SetLineColor(kGreen);


	TCanvas * c3 = new TCanvas("c3", "", 800, 600);
	gStyle->SetOptStat(0);

	TH1D * h = new TH1D("h", "", 1, 10, 250);
	h->GetYaxis()->SetRangeUser(0.77,2.07);
	// h->GetXaxis()->SetRangeUser(0,250);
	h->GetXaxis()->SetTitle("Level-1 Jet E_{T} (GeV)");
	h->GetXaxis()->SetTitleOffset(1.05);
	h->GetXaxis()->SetTitleSize(0.046);
	h->GetYaxis()->SetTitleOffset(1.01);
	h->GetYaxis()->SetTitleSize(0.046);	
	h->GetYaxis()->SetTitle("correction factor");
	// cout << g01->GetXaxis()->GetTitleOffset() << endl;
	// cout << g01->GetXaxis()->GetTitleSize() << endl;
	h->SetTitle("");
	h->Draw();
	g01->Draw("same");
	g02->Draw("same");
	g03->Draw("same");
	g04->Draw("same");
	g05->Draw("same");
	g06->Draw("same");
	g07->Draw("same");
	g08->Draw("same");
	g09->Draw("same");
	g10->Draw("same");
	g11->Draw("same");
	g12->Draw("same");
	g13->Draw("same");
	g14->Draw("same");
	g15->Draw("same");
	g16->Draw("same");

	g30->Draw("same");
	g31->Draw("same");
	g32->Draw("same");
	g33->Draw("same");
	g34->Draw("same");
	g35->Draw("same");
	g36->Draw("same");
	g37->Draw("same");

	g17->Draw("same");
	g18->Draw("same");
	g19->Draw("same");
	g20->Draw("same");
	g21->Draw("same");
	g22->Draw("same");
	g23->Draw("same");
	g24->Draw("same");
	g25->Draw("same");
	g26->Draw("same");
	g27->Draw("same");
	g28->Draw("same");
	// g30->Draw("same");
	// g31->Draw("same");
	// g32->Draw("same");
	// g33->Draw("same");
	// g34->Draw("same");
	// g35->Draw("same");
	// g36->Draw("same");
	// g37->Draw("same");
	// g38->Draw("same");
	// g39->Draw("same");
	// g40->Draw("same");
	// g41->Draw("same");
gPad->RedrawAxis();

	TLegend * leg3 = new TLegend(0.42,0.47,0.87,0.87);
	leg3->SetNColumns(4);
	leg3->AddEntry((TObject*)0, "Barrel", "");
	leg3->AddEntry((TObject*)0, "", "");
	leg3->AddEntry((TObject*)0, "", "");
	leg3->AddEntry((TObject*)0, "", "");
	leg3->AddEntry(g01, "TT1", "l");
	leg3->AddEntry(g02, "TT2", "l");
	leg3->AddEntry(g03, "TT3", "l");
	leg3->AddEntry(g04, "TT4", "l");
	leg3->AddEntry(g05, "TT5", "l");
	leg3->AddEntry(g06, "TT6", "l");
	leg3->AddEntry(g07, "TT7", "l");
	leg3->AddEntry(g08, "TT8", "l");
	leg3->AddEntry(g09, "TT9", "l");
	leg3->AddEntry(g10, "TT10", "l");
	leg3->AddEntry(g11, "TT11", "l");
	leg3->AddEntry(g12, "TT12", "l");
	leg3->AddEntry(g13, "TT13", "l");
	leg3->AddEntry(g14, "TT14", "l");
	leg3->AddEntry(g15, "TT15", "l");
	leg3->AddEntry(g16, "TT16", "l");

	leg3->AddEntry((TObject*)0, "Endcap", "");
	leg3->AddEntry((TObject*)0, "", "");
	leg3->AddEntry((TObject*)0, "", "");
	leg3->AddEntry((TObject*)0, "", "");
	leg3->AddEntry(g17, "TT17");
	leg3->AddEntry(g18, "TT18");
	leg3->AddEntry(g19, "TT19");
	leg3->AddEntry(g20, "TT20");
	leg3->AddEntry(g21, "TT21");
	leg3->AddEntry(g22, "TT22");
	leg3->AddEntry(g23, "TT23");
	leg3->AddEntry(g24, "TT24");							
	leg3->AddEntry(g25, "TT25");
	leg3->AddEntry(g26, "TT26");
	leg3->AddEntry(g27, "TT27");
	leg3->AddEntry(g28, "TT28");

	leg3->AddEntry((TObject*)0, "HF", "");
	leg3->AddEntry((TObject*)0, "", "");
	leg3->AddEntry((TObject*)0, "", "");
	leg3->AddEntry((TObject*)0, "", "");
	leg3->AddEntry(g30, "TT30");
	leg3->AddEntry(g31, "TT31");
	leg3->AddEntry(g32, "TT32");
	leg3->AddEntry(g33, "TT33");
	leg3->AddEntry(g34, "TT34");	
	leg3->AddEntry(g35, "TT35");
	leg3->AddEntry(g36, "TT36");
	leg3->AddEntry(g37, "TT37");
	// leg3->AddEntry(g38, "TT38");
	// leg3->AddEntry(g39, "TT39");
	// leg3->AddEntry(g40, "TT40");
	// leg3->AddEntry(g41, "TT41");
	leg3->Draw();
	c3->SaveAs(outputPath.c_str());
	c3->Close();	
}





void makePlots_allTTetaBinning(std::string inputFile, std::string outputFile, std::string directory){

	std::string inputPath = directory + inputFile;
	std::string outputPath = directory + outputFile;

	TFile * f = TFile::Open(inputPath.c_str());

	TF1 * g01 = (TF1*)f->Get("fitfcneta_0_0.087");
	TF1 * g02 = (TF1*)f->Get("fitfcneta_0.087_0.174");
	TF1 * g03 = (TF1*)f->Get("fitfcneta_0.174_0.261");
	TF1 * g04 = (TF1*)f->Get("fitfcneta_0.261_0.348");
	TF1 * g05 = (TF1*)f->Get("fitfcneta_0.348_0.435");
	TF1 * g06 = (TF1*)f->Get("fitfcneta_0.435_0.522");
	TF1 * g07 = (TF1*)f->Get("fitfcneta_0.522_0.609");
	TF1 * g08 = (TF1*)f->Get("fitfcneta_0.609_0.696");
	TF1 * g09 = (TF1*)f->Get("fitfcneta_0.696_0.783");
	TF1 * g10 = (TF1*)f->Get("fitfcneta_0.783_0.87");
	TF1 * g11 = (TF1*)f->Get("fitfcneta_0.87_0.957");
	TF1 * g12 = (TF1*)f->Get("fitfcneta_0.957_1.044");
	TF1 * g13 = (TF1*)f->Get("fitfcneta_1.044_1.131");
	TF1 * g14 = (TF1*)f->Get("fitfcneta_1.131_1.218");
	TF1 * g15 = (TF1*)f->Get("fitfcneta_1.218_1.305");
	TF1 * g16 = (TF1*)f->Get("fitfcneta_1.305_1.392");
	TF1 * g17 = (TF1*)f->Get("fitfcneta_1.392_1.479");
	TF1 * g18 = (TF1*)f->Get("fitfcneta_1.479_1.566");
	TF1 * g19 = (TF1*)f->Get("fitfcneta_1.566_1.653");
	TF1 * g20 = (TF1*)f->Get("fitfcneta_1.653_1.74");
	TF1 * g21 = (TF1*)f->Get("fitfcneta_1.74_1.83");
	TF1 * g22 = (TF1*)f->Get("fitfcneta_1.83_1.93");
	TF1 * g23 = (TF1*)f->Get("fitfcneta_1.93_2.043");
	TF1 * g24 = (TF1*)f->Get("fitfcneta_2.043_2.172");
	TF1 * g25 = (TF1*)f->Get("fitfcneta_2.172_2.322");
	TF1 * g26 = (TF1*)f->Get("fitfcneta_2.322_2.5");
	TF1 * g27 = (TF1*)f->Get("fitfcneta_2.5_2.65");
	TF1 * g28 = (TF1*)f->Get("fitfcneta_2.65_2.964");
	TF1 * g30 = (TF1*)f->Get("fitfcneta_2.964_3.139");
	TF1 * g31 = (TF1*)f->Get("fitfcneta_3.139_3.314");
	TF1 * g32 = (TF1*)f->Get("fitfcneta_3.314_3.489");
	TF1 * g33 = (TF1*)f->Get("fitfcneta_3.489_3.664");
	TF1 * g34 = (TF1*)f->Get("fitfcneta_3.664_3.839");
	TF1 * g35 = (TF1*)f->Get("fitfcneta_3.839_4.013");
	TF1 * g36 = (TF1*)f->Get("fitfcneta_4.013_4.191");
	TF1 * g37 = (TF1*)f->Get("fitfcneta_4.191_4.363");
	TF1 * g38 = (TF1*)f->Get("fitfcneta_4.363_4.538");
	TF1 * g39 = (TF1*)f->Get("fitfcneta_4.538_4.716");
	// TF1 * g40 = (TF1*)f->Get("fitfcneta_4.716_4.889");
	// TF1 * g41 = (TF1*)f->Get("fitfcneta_4.889_5.191");

	g01->SetLineColor(kBlack);
	g02->SetLineColor(kBlue+3);
	g03->SetLineColor(kBlue);
	g04->SetLineColor(kBlue-7);
	g05->SetLineColor(kCyan+2);
	g06->SetLineColor(kCyan);
	g07->SetLineColor(kGreen+4);
	g08->SetLineColor(kGreen+2);
	g09->SetLineColor(kGreen);
	g10->SetLineColor(kYellow+4);
	g11->SetLineColor(kYellow+2);
	g12->SetLineColor(kYellow);
	g13->SetLineColor(kOrange);
	g14->SetLineColor(kOrange+7);
	g15->SetLineColor(kRed+4);
	g16->SetLineColor(kRed+2);
	g17->SetLineColor(kRed);
	g18->SetLineColor(kMagenta+4);
	g19->SetLineColor(kMagenta+2);
	g20->SetLineColor(kMagenta);
	g21->SetLineColor(kBlack);
	g22->SetLineColor(kBlue+3);
	g23->SetLineColor(kBlue);
	g24->SetLineColor(kBlue-7);
	g25->SetLineColor(kCyan+2);
	g26->SetLineColor(kCyan);
	g27->SetLineColor(kGreen+4);
	g28->SetLineColor(kGreen+2);
	g30->SetLineColor(kGreen);
	g31->SetLineColor(kYellow+4);
	g32->SetLineColor(kYellow+2);
	g33->SetLineColor(kYellow);
	g34->SetLineColor(kOrange);
	g35->SetLineColor(kOrange+7);
	g36->SetLineColor(kRed+4);
	g37->SetLineColor(kRed+2);
	g38->SetLineColor(kRed);
	g39->SetLineColor(kMagenta+4);
	// g40->SetLineColor(kMagenta+2);
	// g41->SetLineColor(kMagenta);

	g17->SetLineStyle(9);
	g18->SetLineStyle(9);
	g19->SetLineStyle(9);
	g20->SetLineStyle(9);
	g21->SetLineStyle(9);
	g22->SetLineStyle(9);
	g23->SetLineStyle(9);					
	g24->SetLineStyle(9);
	g25->SetLineStyle(9);
	g26->SetLineStyle(9);
	g27->SetLineStyle(9);
	g28->SetLineStyle(9);

	TCanvas * c3 = new TCanvas("c3", "", 600, 600);
	gStyle->SetOptStat(0);
	g01->GetYaxis()->SetRangeUser(0.9,2.0);
	g01->GetXaxis()->SetRangeUser(0,300);
	g01->Draw();
	g02->Draw("same");
	g03->Draw("same");
	g04->Draw("same");
	g05->Draw("same");
	g06->Draw("same");
	g07->Draw("same");
	g08->Draw("same");
	g09->Draw("same");
	g10->Draw("same");
	g11->Draw("same");
	g12->Draw("same");
	g13->Draw("same");
	g14->Draw("same");
	g15->Draw("same");
	g16->Draw("same");
	g17->Draw("same");
	g18->Draw("same");
	g19->Draw("same");
	g20->Draw("same");
	g21->Draw("same");
	g22->Draw("same");
	g23->Draw("same");
	g24->Draw("same");
	g25->Draw("same");
	g26->Draw("same");
	g27->Draw("same");
	g28->Draw("same");
	g30->Draw("same");
	g31->Draw("same");
	g32->Draw("same");
	g33->Draw("same");
	g34->Draw("same");
	g35->Draw("same");
	g36->Draw("same");
	g37->Draw("same");
	// g38->Draw("same");
	// g39->Draw("same");
	// g40->Draw("same");
	// g41->Draw("same");

	TLegend * leg3 = new TLegend(0.43,0.53,0.88,0.88);
	leg3->AddEntry(g01, "(HB) 1");		
	leg3->AddEntry(g02, "2");
	leg3->AddEntry(g03, "3");
	leg3->AddEntry(g04, "4");
	leg3->AddEntry(g05, "5");
	leg3->AddEntry(g06, "6");
	leg3->AddEntry(g07, "7");
	leg3->AddEntry(g08, "8");
	leg3->AddEntry(g09, "9");
	leg3->AddEntry(g10, "10");
	leg3->AddEntry(g11, "11");
	leg3->AddEntry(g12, "12");
	leg3->AddEntry(g13, "13");
	leg3->AddEntry(g14, "14");
	leg3->AddEntry(g15, "15");
	leg3->AddEntry(g16, "16");
	leg3->AddEntry(g17, "(HE) 17");
	leg3->AddEntry(g18, "18");
	leg3->AddEntry(g19, "19");
	leg3->AddEntry(g20, "20");
	leg3->AddEntry(g21, "21");
	leg3->AddEntry(g22, "22");
	leg3->AddEntry(g23, "23");
	leg3->AddEntry(g24, "24");							
	leg3->AddEntry(g25, "25");
	leg3->AddEntry(g26, "26");
	leg3->AddEntry(g27, "27");
	leg3->AddEntry(g28, "28");
	leg3->AddEntry(g30, "(HF) 30");
	leg3->AddEntry(g31, "31");
	leg3->AddEntry(g32, "32");
	leg3->AddEntry(g33, "33");
	leg3->AddEntry(g34, "34");	
	leg3->AddEntry(g35, "35");
	leg3->AddEntry(g36, "36");
	leg3->AddEntry(g37, "37");
	// leg3->AddEntry(g38, "38");
	// leg3->AddEntry(g39, "39");
	// leg3->AddEntry(g40, "40");
	// leg3->AddEntry(g41, "41");
	leg3->Draw();
	c3->SaveAs(outputPath.c_str());
	c3->Close();	
}



void makePlots_sel16etaBinning(std::string inputFile, std::string outputFile, std::string directory){

	std::string inputPath = directory + inputFile;
	std::string outputPath = directory + outputFile;

	TFile * f = TFile::Open(inputPath.c_str());

	TF1 * g00 = (TF1*)f->Get("fitfcneta_0_0.435");
	TF1 * g01 = (TF1*)f->Get("fitfcneta_0.435_0.783");
	TF1 * g02 = (TF1*)f->Get("fitfcneta_0.783_1.131");
	TF1 * g03 = (TF1*)f->Get("fitfcneta_1.131_1.305");
	TF1 * g04 = (TF1*)f->Get("fitfcneta_1.305_1.479");
	TF1 * g05 = (TF1*)f->Get("fitfcneta_1.479_1.653");
	TF1 * g06 = (TF1*)f->Get("fitfcneta_1.653_1.83");
	TF1 * g07 = (TF1*)f->Get("fitfcneta_1.83_1.93");
	TF1 * g08 = (TF1*)f->Get("fitfcneta_1.93_2.043");
	TF1 * g09 = (TF1*)f->Get("fitfcneta_2.043_2.172");
	TF1 * g10 = (TF1*)f->Get("fitfcneta_2.172_2.322");
	TF1 * g11 = (TF1*)f->Get("fitfcneta_2.322_2.5");
	TF1 * g12 = (TF1*)f->Get("fitfcneta_2.5_2.964");
	TF1 * g13 = (TF1*)f->Get("fitfcneta_2.964_3.489");
	TF1 * g14 = (TF1*)f->Get("fitfcneta_3.489_4.191");
	TF1 * g15 = (TF1*)f->Get("fitfcneta_4.191_5.191");	

	g00->SetLineColor(kBlue+2);
	g01->SetLineColor(kBlue);
	g02->SetLineColor(kCyan+1);
	g03->SetLineColor(kGreen+2);
	g04->SetLineColor(kGreen);	
	g05->SetLineColor(kYellow+2);
	g06->SetLineColor(kOrange);
	g07->SetLineColor(kOrange+7);
	g08->SetLineColor(kRed+2);	
	g09->SetLineColor(kRed);
	g10->SetLineColor(kMagenta+3);
	g11->SetLineColor(kMagenta);
	g12->SetLineColor(kBlue+2);
	g13->SetLineColor(kCyan+1);
	g14->SetLineColor(kGreen+2);
	g15->SetLineColor(kGreen);

	TCanvas * c3 = new TCanvas("c3", "", 600, 600);
	gStyle->SetOptStat(0);
	g00->GetYaxis()->SetRangeUser(0.9,2.0);
	g00->GetXaxis()->SetRangeUser(0,300);
	g00->Draw();
	g01->Draw("same");
	g02->Draw("same");
	g03->Draw("same");
	g04->Draw("same");
	g05->Draw("same");
	g06->Draw("same");
	g07->Draw("same");
	g08->Draw("same");
	g09->Draw("same");
	g10->Draw("same");
	g11->Draw("same");
	g12->Draw("same");
	g13->Draw("same");
	g14->Draw("same");
	g15->Draw("same");
	
	TLegend * leg3 = new TLegend(0.43,0.53,0.88,0.88);	
	leg3->AddEntry(g00, "bin00");
	leg3->AddEntry(g01, "bin01");
	leg3->AddEntry(g02, "bin02");
	leg3->AddEntry(g03, "bin03");
	leg3->AddEntry(g04, "bin04");
	leg3->AddEntry(g05, "bin05");
	leg3->AddEntry(g06, "bin06");
	leg3->AddEntry(g07, "bin07");
	leg3->AddEntry(g08, "bin08");
	leg3->AddEntry(g09, "bin09");
	leg3->AddEntry(g10, "bin10");
	leg3->AddEntry(g11, "bin11");
	leg3->AddEntry(g12, "bin12");
	leg3->AddEntry(g13, "bin13");
	leg3->AddEntry(g14, "bin14");
	leg3->AddEntry(g15, "bin15");	
	leg3->Draw();		
	c3->SaveAs(outputPath.c_str());
	c3->Close();	
}