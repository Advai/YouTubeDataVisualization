#pragma once

#include "ofMain.h"
#include "../addons/ofxDatGui/src/ofxDatGui.h"
#include "../addons/ofxGui/src/ofxGui.h"
#include "../addons/ofxGrafica/src/ofxGrafica.h"
#include "json.hpp"

using json = nlohmann::json;

class ofApp : public ofBaseApp {

public:
	ofxLabel *label;
	ofxDatGuiLabel* header;
	ofxDatGuiButton* button;
	ofxDatGui* gui;
	ofTrueTypeFont *myfont;
	ofxDatGuiScrollView* myScrollView;
	ofxDatGuiFolder* subscriptionsFolder;
	//json subscriber_json;
	ofxGPlot plot;
	// vector<ofxGPoint>* points;

	void setup();
	void update();
	void draw();
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	void onButtonEvent(ofxDatGuiButtonEvent e);
	void viewsEvent(ofxDatGuiButtonEvent e);

};
