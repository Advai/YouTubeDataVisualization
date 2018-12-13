#include <Python.h>
#include "ofApp.h"
#include <stdlib.h>
#include "json.hpp"

using json = nlohmann::json;

//--------------------------------------------------------------
/*
	sets the default values for all gui elements
*/
void ofApp::setup() {
	myfont = new ofTrueTypeFont();
	myfont->load(OF_TTF_SANS, 32);
	ofSetBackgroundColor(ofColor::white);
	
	setupHeader();
	setupButton();
	setupSubscriptionFolder();
	setupVideoFolder();
	setupGraphDescription();
	setupPlot();
}

/*
	sets default values for the graph description label
*/
void ofApp::setupGraphDescription() 
{
	graphDescription = new ofxDatGuiLabel("Click on a graph option for a description of the graph");
	graphDescription->setPosition(750, 1425);
	graphDescription->setWidth(2000, 1);
	graphDescription->setHeight(200);
	graphDescription->setLabelAlignment(ofxDatGuiAlignment::CENTER);
	graphDescription->setBackgroundColor(ofColor::red);
	graphDescription->setLabelColor(ofColor::white);
}
/*
	sets up default values for header label
*/
void ofApp::setupHeader() 
{
	header = new ofxDatGuiLabel("Youtube Data Visualizer");
	header->setBackgroundColor(ofColor::red);
	header->setLabelColor(ofColor::white);
	header->setLabelAlignment(ofxDatGuiAlignment::CENTER);
	header->setWidth(3200, .9);
	header->setPosition(0, 0);
	header->setHeight(200);
}

/*
	creates folder for subscription based graphs, adds buttons, and sets default values
*/
void ofApp::setupSubscriptionFolder() 
{
	subscriptionsFolder = new ofxDatGuiFolder("Subscriptions Based Graphs", ofColor::white);
	subscriptionsFolder->setWidth(800);
	subscriptionsFolder->setPosition(0, 250);

	subscriptionsFolder->addButton("Views");
	subscriptionsFolder->addButton("Subscriber Count");
	subscriptionsFolder->addButton("Popularity");
	subscriptionsFolder->addButton("Topics");

	subscriptionsFolder->getComponent(ofxDatGuiType::BUTTON, "Views")->setWidth(800, 1);
	subscriptionsFolder->getComponent(ofxDatGuiType::BUTTON, "Views")->setLabelAlignment(ofxDatGuiAlignment::CENTER);
	subscriptionsFolder->getComponent(ofxDatGuiType::BUTTON, "Views")->onButtonEvent(this, &ofApp::subscriberViewsEvent);

	subscriptionsFolder->getComponent(ofxDatGuiType::BUTTON, "Popularity")->onButtonEvent(this, &ofApp::subscriberPopularityEvent);
	subscriptionsFolder->getComponent(ofxDatGuiType::BUTTON, "Popularity")->setWidth(800, 1);
	subscriptionsFolder->getComponent(ofxDatGuiType::BUTTON, "Popularity")->setLabelAlignment(ofxDatGuiAlignment::CENTER);

	subscriptionsFolder->getComponent(ofxDatGuiType::BUTTON, "Subscriber Count")->onButtonEvent(this, &ofApp::subEvent);
	subscriptionsFolder->getComponent(ofxDatGuiType::BUTTON, "Subscriber Count")->setWidth(800, 1);
	subscriptionsFolder->getComponent(ofxDatGuiType::BUTTON, "Subscriber Count")->setLabelAlignment(ofxDatGuiAlignment::CENTER);

	subscriptionsFolder->getComponent(ofxDatGuiType::BUTTON, "Topics")->onButtonEvent(this, &ofApp::subscriptionTopicEvent);
	subscriptionsFolder->getComponent(ofxDatGuiType::BUTTON, "Topics")->setWidth(800, 1);
	subscriptionsFolder->getComponent(ofxDatGuiType::BUTTON, "Topics")->setLabelAlignment(ofxDatGuiAlignment::CENTER);

	subscriptionsFolder->toggle();
	subscriptionsFolder->expand();
}

/*
	creates folder for video based graphs, adds buttons, and sets default values
*/
void ofApp::setupVideoFolder() 
{
	videosFolder = new ofxDatGuiFolder("Liked Videos Based Graphs", ofColor::white);
	videosFolder->setWidth(800);
	videosFolder->setPosition(0, 550);

	videosFolder->addButton("Views");
	videosFolder->addButton("Likes");
	videosFolder->addButton("Categories");

	videosFolder->getComponent(ofxDatGuiType::BUTTON, "Views")->setWidth(800, 1);
	videosFolder->getComponent(ofxDatGuiType::BUTTON, "Views")->onButtonEvent(this, &ofApp::videoViewsEvent);
	videosFolder->getComponent(ofxDatGuiType::BUTTON, "Views")->setLabelAlignment(ofxDatGuiAlignment::CENTER);

	videosFolder->getComponent(ofxDatGuiType::BUTTON, "Likes")->setWidth(800, 1);
	videosFolder->getComponent(ofxDatGuiType::BUTTON, "Likes")->onButtonEvent(this, &ofApp::videoLikesEvent);
	videosFolder->getComponent(ofxDatGuiType::BUTTON, "Likes")->setLabelAlignment(ofxDatGuiAlignment::CENTER);

	videosFolder->getComponent(ofxDatGuiType::BUTTON, "Categories")->setWidth(800, 1);
	videosFolder->getComponent(ofxDatGuiType::BUTTON, "Categories")->onButtonEvent(this, &ofApp::videoTopicsEvent);
	videosFolder->getComponent(ofxDatGuiType::BUTTON, "Categories")->setLabelAlignment(ofxDatGuiAlignment::CENTER);

	videosFolder->toggle();
	videosFolder->expand();
}

/*
	sets default values for log in button
*/
void ofApp::setupButton() 
{
	button = new ofxDatGuiButton("Log In");
	button->setPosition(2850, 65);
	button->setLabelAlignment(ofxDatGuiAlignment::CENTER);
	button->setHeight(75, 1);
	button->setWidth(400, 1);
	button->onButtonEvent(this, &ofApp::onButtonEvent);
}

/*
	creates plot and sets default values for axes, title, and colors
*/
void ofApp::setupPlot() 
{
	plot.setPos(900, 200);
	plot.setDim(1500, 650);
	plot.startHistograms(GRAFICA_VERTICAL_HISTOGRAM);
	plot.setLineColor(ofColor::red);
	plot.setBgColor(ofColor::gray);
	plot.getTitle().setFontColor(ofColor::white);
	plot.getXAxis().getAxisLabel().setFontColor(ofColor::white);
	plot.getYAxis().getAxisLabel().setFontColor(ofColor::white);
	plot.setMar(300, 90, 60, 50);
	plot.setFontSize(30);
	plot.getHistogram().setFontSize(15);
	plot.getTitle().setFontSize(25);
	plot.getTitle().setText("Graph");
	plot.getTitle().setTextAlignment(GRAFICA_CENTER_ALIGN);
	plot.getYAxis().setAxisLabelText("Y-Axis");
	plot.getXAxis().setAxisLabelText("X-Axis");
	plot.getYAxis().setFontSize(12);
	plot.getXAxis().setFontSize(12);
	plot.getXAxis().getAxisLabel().setFontSize(18);
	plot.getYAxis().getAxisLabel().setFontSize(18);
	plot.getXAxis().getAxisLabel().setOffset(280);
	plot.getXAxis().setDrawTickLabels(false);

	plot.getHistogram().setDrawLabels(true);
	plot.getHistogram().setBgColors({ ofColor(255, 0, 0) });
	plot.getHistogram().setRotateLabels(true);
	plot.getHistogram().setBgColors({ ofColor(255, 0, 0, 50), ofColor(255, 0, 0, 100), ofColor(255, 0, 0, 150),
			ofColor(255, 0, 0, 200) });
}

/*
	opens json file with youtube data and reads specific data feature into ofxGPoint vector and then normalizes it
*/
vector<ofxGPoint> ofApp::getData(string path, int flag)
{
	vector<ofxGPoint> toReturn;
	ifstream stream(path);
	json data = json::parse(stream);
	stream.close();
	


	string data_type;
	
	if (flag == 1) {
		data_type = "subscriberCount";
	}
	else if (flag == 0) {
		data_type = "viewCount";
	}
	else {
		data_type = "likeCount";
	}

	for (int i = 0; i < data["items"].size(); i++) {
		toReturn.emplace_back(i, data["items"][i][data_type], data["items"][i]["title"]);
	}

	return normalize(toReturn);
}
/*
	reads topic ids / category ids from json file and counts occurrence of each topic/category in the retrieved youtube json data
*/
vector<ofxGPoint> ofApp::getTopicIds(string topicIdsPath, string dataPath, int flag) 
{
	vector<ofxGPoint> toReturn;
	
	std::ifstream topicIdStream(topicIdsPath);
	json topicIds = json::parse(topicIdStream);
	topicIdStream.close();

	map<string, int> topicCount;

	for (int i = 0; i < topicIds["items"].size(); i++) {
		topicCount.emplace(topicIds["items"][i], 0);
	}

	std::ifstream dataStream(dataPath);
	json data = json::parse(dataStream);
	dataStream.close();


	string data_field;
	
	if (flag == 1) {
		data_field = "topicIds";
		for (int i = 0; i < data["items"].size(); i++) {

			for (int j = 0; j < data["items"][i][data_field].size(); j++) {
				topicCount[data["items"][i][data_field][j]]++;
			}
		}
	}
	else {
		data_field = "category";
		for (int i = 0; i < data["items"].size(); i++) {
			topicCount[data["items"][i][data_field]]++;
		}
	}

	int count2 = 0;
	
	for (const auto &pair : topicCount) {
		toReturn.emplace_back(count2, pair.second, pair.first);
		count2++;
	}

	return toReturn;
}

/*
	evaluates python script to retrieve data, then sets vectors of ofxGPoints to be able to populate its respective graph on button click
*/
void ofApp::onButtonEvent(ofxDatGuiButtonEvent e)
{
	if (e.target == button) {
		// calls python script using C++ python library
		PyObject *obj = Py_BuildValue("s", python_script_path);
		FILE *file = _Py_fopen_obj(obj, "r+");
		FILE *file2 = _Py_fopen(python_script_path.c_str(), "r+");
		PyRun_SimpleFile(file2, python_script_path.c_str());
		button->setLabel("Logged In");
		button->setBackgroundColor(ofColor(100, 100, 100, 100));
		
		subscriptionSubscriberCount = getData(subscription_data_path, 1);
		subscriptionViewCount = getData(subscription_data_path, 0);
		subscriptionTopicsCount = getTopicIds(subscription_topics_path, subscription_data_path, 1);
		
		for (int i = 0; i < subscriptionSubscriberCount.size(); i++) {
			popularity.emplace_back(i, (subscriptionSubscriberCount[i].getY() + subscriptionViewCount[i].getY()) / 2, subscriptionSubscriberCount[i].getLabel());
		}
		popularity = normalize(popularity);
		
		likedVideoLikeCount = getData(video_data_path, 2);
		likedVideoViewCount = getData(video_data_path, 0);
		likedVideoTopics = getTopicIds(video_categories_path, video_data_path, 0);
	}
}
/*
	shows video total views graph and scales graph to accommodate for video title size as well as changes graph description
*/
void ofApp::videoViewsEvent(ofxDatGuiButtonEvent e)
{
	plot.getTitle().setText("View Comparison of your Liked Videos");
	plot.getYAxis().setAxisLabelText("Views");
	plot.getXAxis().setAxisLabelText("Video");
	plot.setMar(500, 90, 60, 50);
	plot.getXAxis().getAxisLabel().setOffset(480);
	plot.setPoints(likedVideoViewCount);
	graphDescription->setLabel("The graph shows which of your liked videos has the most views\n as well as the relative amount of views of your other liked videos");
}

/*
	shows video topic occurrence graph and scales graph to accommodate for video title size as well as changes graph description
*/
void ofApp::videoTopicsEvent(ofxDatGuiButtonEvent e)
{
	plot.getTitle().setText("Category Spread of your Liked Videos");
	plot.getYAxis().setAxisLabelText("Number of videos");
	plot.setMar(500, 90, 60, 50);
	plot.getXAxis().getAxisLabel().setOffset(480);
	plot.getXAxis().setAxisLabelText("Category");
	graphDescription->setLabel("This is the distribution of the video categories that your liked videos fall under\nIt will allow you to understand what kind of videos you like the most");
	plot.setPoints(likedVideoTopics);
}

/*
	shows video total likes graph and scales graph to accommodate for video title size as well as changes graph description
*/
void ofApp::videoLikesEvent(ofxDatGuiButtonEvent e)
{
	plot.getTitle().setText("Likes Comparison of your Liked Videos");
	plot.getYAxis().setAxisLabelText("Likes");
	graphDescription->setLabel("This graph visualizes how many likes a video you have liked has\nUtilize this graph to gauge how popular the videos you liked are");
	plot.getXAxis().setAxisLabelText("Video");
	plot.setMar(500, 90, 60, 50);
	plot.getXAxis().getAxisLabel().setOffset(480);
	plot.setPoints(likedVideoLikeCount);
}

/*
	shows subscription overall popularity graph and scales graph to accommodate for channel title size as well as changes graph description
	popularity is determined by combining the likes and views component of each channel and dividing it by 2
*/
void ofApp::subscriberPopularityEvent(ofxDatGuiButtonEvent e)
{
	plot.getTitle().setText("Popularity Comparison of your Subscriptions");
	plot.setMar(300, 90, 60, 50);
	plot.getXAxis().getAxisLabel().setOffset(280);
	plot.getYAxis().setAxisLabelText("Popularity");
	plot.getXAxis().setAxisLabelText("Channel");
	graphDescription->setLabel("This is the popularity metric of your subscriptions. It combines the \nsubscriber and view count metrics to holistically rank your subscriptions");
	plot.setPoints(popularity);
}

/*
	shows subscription total view count graph and scales graph to accommodate for channel title size as well as changes graph description
*/
void ofApp::subscriberViewsEvent(ofxDatGuiButtonEvent e)
{
	plot.getTitle().setText("View Count Comparison of your Subscriptions");
	plot.getYAxis().setAxisLabelText("Views");
	plot.setMar(300, 90, 60, 50);
	plot.getXAxis().getAxisLabel().setOffset(280);
	plot.getXAxis().setAxisLabelText("Channel");
	graphDescription->setLabel("This is a graph of the cumulative views each channel subscription has\nThis reflects how many people have viewed this channel since its creation");
	plot.setPoints(subscriptionViewCount);
}

/*
	shows subscription subscriber count graph and scales graph to accommodate for channel title size as well as changes graph description
*/
void ofApp::subEvent(ofxDatGuiButtonEvent e)
{
	plot.getTitle().setText("Subscriber Count Comparison of your Subscriptions");
	plot.getYAxis().setAxisLabelText("Subscribers");
	plot.setMar(300, 90, 60, 50);
	plot.getXAxis().getAxisLabel().setOffset(280);
	graphDescription->setLabel("This is a graph of the subscribers each channel subscription has\nThis sheds light on how many people actively keep up with this channel's uploads");
	plot.getXAxis().setAxisLabelText("Channel");
	plot.setPoints(subscriptionSubscriberCount);
}

/*
	shows subscriber category occurrence graph and scales graph to accommodate for channel title size as well as changes graph description
*/
void ofApp::subscriptionTopicEvent(ofxDatGuiButtonEvent e)
{
	plot.getTitle().setText("Topic Spread of your Subscriptions");
	plot.getYAxis().setAxisLabelText("Number of channels");
	plot.setMar(300, 90, 60, 50);
	plot.getXAxis().getAxisLabel().setOffset(280);
	plot.getXAxis().setAxisLabelText("Topic");
	graphDescription->setLabel("This shows the distribution of topics that your subscriptions cover\nUse this graph to better understand the type of content you actively consume");
	plot.setPoints(subscriptionTopicsCount);
}

/*
	updates components with any possible changes
*/
//--------------------------------------------------------------
void ofApp::update() {
	subscriptionsFolder->update();
	videosFolder->update();
	button->update();
	header->update();
	graphDescription->update();
}

/*
	draws all components
*/
//--------------------------------------------------------------
void ofApp::draw() {
	header->draw();
	graphDescription->draw();
	button->draw();
	subscriptionsFolder->draw();
	videosFolder->draw();
	plot.beginDraw();
	plot.drawBackground();
	plot.drawBox();
	plot.drawYAxis();
	plot.drawXAxis();
	plot.drawTitle();
	plot.drawHistograms();
	plot.endDraw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}

/*
	normalizes a vector of ofxGPoints by finding the max and min and dividing the difference of the value and the min by the difference between the max and the min
	 x - min
	---------
	 max - min
*/
vector<ofxGPoint> ofApp::normalize(vector<ofxGPoint> vec)
{
	if (vec.size() == 0) {
		return vec;
	}
	float min, max;
	min = vec[0].getY();
	max = vec[0].getY();
	for (int i = 0; i < vec.size(); i++) {
		if (vec[i].getY() > max) {
			max = vec[i].getY();
		}
		if (vec[i].getY() < min) {
			min = vec[i].getY();
		}
	}
	for (int i = 0; i < vec.size(); i++) {
		vec[i].setY((vec[i].getY() - min) / (max - min));
	}

	return vec;
}
