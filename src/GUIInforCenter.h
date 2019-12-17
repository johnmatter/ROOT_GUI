/*
 * GUIInforCenter.h
 *
 *  Created on: May 25, 2018
 *      Author: newdriver
 */

#ifndef GUIINFORCENTER_H_
#define GUIINFORCENTER_H_
#include <TQObject.h>
#include <RQ_OBJECT.h>

#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <math.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TVector2.h>
#include <TVector3.h>
#include "../GEMDetector/GEMUIDGenerator.h"

struct GUICanvasDataStream{

public:
	GUICanvasDataStream(){
	};

	TVector2 GetCanvasDivied(){
		return size;
	}

	Int_t GetTabNestLevel(){
		return tabNestLevel;
	}

	// Is this used anywhere?
	const unsigned int GetCanvasNumber(){
		return histo_1h_arry.size();
	}

	std::map<int/*tab*/,std::vector<TH1F*>> GetHisto1D(){
		generateHisto();
		return histo_1h;
	}

	const std::map<int/*crate tab*/, std::map<int /*mpd tab*/, std::map<int /*canvas x*/,std::map<int/*canvas y*/,TH1F *>>>> GetHisto1dArray(){
		return histo_1h_arry;
	}

	std::map<int/**/,std::vector<int>> GetRaw(){
		return data;
	}

	void LoadData(const std::map<int/**/,std::vector<int>> &data){
		clear();
		this->data=data;
		//generateHisto(data);
	}

	void LoadData(std::map<int, std::map<int,std::vector<TH1F *>>> const data){
		clear();
		this->canvasedDisplay=data;
	}

	void generateHisto(){
		if(data.size()!=0) {
			RawGenerateHisto();
		}
		if(canvasedDisplay.size()){
			ZeroSubGenerateHisto();
		}
	}

private:
	TVector2 size;
	Int_t tabNestLevel;
	std::map<int/**/,std::vector<int>> data;
	std::map<int/*tab*/,std::vector<TH1F*>> histo_1h;
	std::map<int/*crate tab*/, std::map<int /*mpd tab*/, std::map<int /*canvas x*/,std::map<int/*canvas y*/,TH1F *>>>> histo_1h_arry;
	std::map<int, std::map<int,std::vector<TH1F *>>> canvasedDisplay;

	void RawGenerateHisto(){
		std::map<int,std::vector<int>> rawdata = this->data;
		std::vector<int> strip_data;
		int crateid, mpdid, adcid, uid;
		TH1F *h;
		TString histo_name;

		tabNestLevel = 2;

		// Used to keep track of position in the tab's 4x4 layout of histograms
		int i = 0;

		// Loop over APVs and generate histograms
		// rawdata is a map from an apv's UID to the vector<int> contaning its strips' data
		for(auto apv = rawdata.begin(); apv!=rawdata.end(); apv++){

			crateid = GEM::getCrateID(apv->first);
			mpdid = GEM::getMPDID(apv->first);
			adcid = GEM::getADCID(apv->first);
			uid = GEM::GetUID(crateid, mpdid, 0, 0);
			std::cout << "crate:mpd:adc:uid:apv->first = "
					<< crateid << ":" 
					<< mpdid << ":" 
					<< adcid << ":" 
					<< uid << ":" 
					<< apv->first << std::endl; //JMDEBUG

			// Create a histogram for this APV
			histo_name = Form("crate%d_mpd%d_apv%d", crateid, mpdid, adcid); 
			h = new TH1F(histo_name.Data(), histo_name.Data(), 800, 0, 800);

			// Fill histogram with ADC per strip
			strip_data = apv->second;
			for(int j = 0; j < strip_data.size(); j++){
				h->Fill(j+1, strip_data.at(j));
				h->GetYaxis()->SetRangeUser(0,3000);
				h->SetYTitle("ADC");
				h->SetXTitle("channel");
			}

			// Store histogram for drawing elsewhere
			histo_1h[uid].push_back(h);
			histo_1h_arry[crateid][mpdid][i%4][i/4]=h;

			// Increment 4x4 layout counter
			i++;
		}
		size.Set(4.0,4.0);
	}

	void ZeroSubGenerateHisto(){
		histo_1h_arry.clear();
		for (auto tab = canvasedDisplay.begin(); tab != canvasedDisplay.end(); tab++) {
			for (auto dimension = tab->second.begin();
					dimension != tab->second.end(); dimension++) {
				for (unsigned int i = 0; i < (dimension->second).size(); i++) {
					histo_1h_arry[0][tab->first][dimension->first][i] =
							dimension->second.at(i);
				}
			}
		}
		size.Set(2., 4.);
		tabNestLevel = 1;
	}

	void clear(){
		data.clear();
		histo_1h.clear();
		histo_1h_arry.clear();
		canvasedDisplay.clear();

	}
};

struct GUIStatusBarDataStream{
	int processbar=0;
	std::string tab2;
};

struct GUIMainTabDataStream{

};

class GUIInforCenter {

	RQ_OBJECT("GUIInforCenter");

public:
	GUIInforCenter();
	virtual ~GUIInforCenter();
	void SetTab();            // redraw the tab according to the mapping
	void StatusBarDisplay(GUIStatusBarDataStream *stream){
		Emit("GUIStatusBarDraw(GUIStatusBarDataStream *)",stream);

	}
	void CanvasTabDisplay(GUICanvasDataStream *stream){
		Emit("GUICanvasTabDraw(GUICanvasDataStream *)",stream);

	}
	void MainTabDisplay(GUIMainTabDataStream *stream){
		Emit("GUIMainTabDraw(GUIMainTabDataStream *)",stream);
	}

private:
	void GUICanvasTabDraw(GUICanvasDataStream *);     //*SIGNAL*
	void GUIMainTabDraw(GUIMainTabDataStream *);	  //*SIGNAL*
	void GUIStatusBarDraw(GUIStatusBarDataStream *);  //*SIGNAL*
public:
	ClassDef(GUIInforCenter,0);
};


#endif /* GUIINFORCENTER_H_ */
