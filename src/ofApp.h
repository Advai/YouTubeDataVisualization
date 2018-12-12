#pragma once

#include "ofMain.h"
#include "../addons/ofxDatGui/src/ofxDatGui.h"
#include "../addons/ofxGui/src/ofxGui.h"
#include "../addons/ofxGrafica/src/ofxGrafica.h"
#include "json.hpp"

using json = nlohmann::json;

class ofApp : public ofBaseApp {

private:
	bool loggedIn = false;
public:
	ofxLabel *label;
	ofxDatGuiLabel* header;
	ofxDatGuiButton* button;
	ofxDatGui* gui;
	ofTrueTypeFont *myfont;
	ofxDatGuiScrollView* myScrollView;
	ofxDatGuiFolder* subscriptionsFolder;
	ofxDatGuiFolder* videosFolder;
	//json subscriber_json;
	ofxGPlot plot;
	vector<ofxGPoint> subscriptionViewCount;
	vector<ofxGPoint> subscriptionSubscriberCount;
	vector<ofxGPoint> popularity;
	vector<ofxGPoint> likedVideoViewCount;
	vector<ofxGPoint> likedVideoLikeCount;
	vector<ofxGPoint> likedVideoTopics;
	vector<ofxGPoint> subscriptionTopicsCount;
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
	void subscriberViewsEvent(ofxDatGuiButtonEvent e);
	void subEvent(ofxDatGuiButtonEvent e);
	void subscriberPopularityEvent(ofxDatGuiButtonEvent e);
	void videoViewsEvent(ofxDatGuiButtonEvent e);
	void videoLikesEvent(ofxDatGuiButtonEvent e);
	void videoTopicsEvent(ofxDatGuiButtonEvent e);
	void subscriptionTopicEvent(ofxDatGuiButtonEvent e);
	vector<ofxGPoint> normalize(vector<ofxGPoint> vec);
};
