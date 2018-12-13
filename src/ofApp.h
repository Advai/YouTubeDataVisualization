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
	string video_data_path = "C:\\Users\\advai\\PycharmProjects\\youtubeapitest\\liked_video_data.json";
	string subscription_data_path = "C:\\Users\\advai\\PycharmProjects\\youtubeapitest\\subscription_data.json";
	string python_script_path = "C:\\Users\\advai\\PycharmProjects\\youtubeapitest\\data_retriever.py";
	string video_categories_path = "C:\\Users\\advai\\PycharmProjects\\youtubeapitest\\video_categories.json";
	string subscription_topics_path = "C:\\Users\\advai\\PycharmProjects\\youtubeapitest\\topic_ids.json";
public:
	ofxDatGuiLabel* header;
	ofxDatGuiLabel* graphDescription;
	
	ofxDatGuiButton* button;
	
	ofTrueTypeFont *myfont;
	
	ofxDatGuiFolder* subscriptionsFolder;
	ofxDatGuiFolder* videosFolder;
	
	ofxGPlot plot;
	
	vector<ofxGPoint> subscriptionViewCount;
	vector<ofxGPoint> subscriptionSubscriberCount;
	vector<ofxGPoint> popularity;
	vector<ofxGPoint> likedVideoViewCount;
	vector<ofxGPoint> likedVideoLikeCount;
	vector<ofxGPoint> likedVideoTopics;
	vector<ofxGPoint> subscriptionTopicsCount;

	void setup();
	void setupGraphDescription();
	void setupHeader();
	void setupSubscriptionFolder();
	void setupVideoFolder();
	void setupButton();
	void setupPlot();
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
	vector<ofxGPoint> getData(string path, int flag);
	vector<ofxGPoint> getTopicIds(string topicIdsPath, string dataPath, int flag);
};
