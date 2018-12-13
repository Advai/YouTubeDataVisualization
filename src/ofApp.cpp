#include <Python.h>
#include "ofApp.h"
#include <stdlib.h>
#include "json.hpp"

using json = nlohmann::json;

//--------------------------------------------------------------
void ofApp::setup() {
	myfont = new ofTrueTypeFont();
	circle = new ofxDatGuiLabel("TEST");
	myfont->load(OF_TTF_SANS, 32);
	ofxDatGui* gui = new ofxDatGui(3200, 1800);
	ofSetBackgroundColor(ofColor::white);
	header = new ofxDatGuiLabel("Youtube Data Visualizer");
	header->setBackgroundColor(ofColor::red);
	header->setLabelColor(ofColor::white);
	header->setLabelAlignment(ofxDatGuiAlignment::CENTER);
	header->setWidth(3200, .9);
	header->setPosition(0, 0);
	header->setHeight(200);
	graphDescription = new ofxDatGuiLabel("Click on a graph option for a description of the graph");
	graphDescription->setPosition(750, 1425);
	graphDescription->setWidth(2000, 1);
	graphDescription->setHeight(200);
	graphDescription->setLabelAlignment(ofxDatGuiAlignment::CENTER);
	graphDescription->setBackgroundColor(ofColor::red);
	graphDescription->setLabelColor(ofColor::white);


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

	button = new ofxDatGuiButton("Log In");
	button->setPosition(2850, 65);
	button->setLabelAlignment(ofxDatGuiAlignment::CENTER);
	button->setHeight(75, 1);
	button->setWidth(400, 1);
	button->onButtonEvent(this, &ofApp::onButtonEvent);



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

void ofApp::onButtonEvent(ofxDatGuiButtonEvent e)
{
	if (e.target == button) {
		PyObject *obj = Py_BuildValue("s", "C:\\Users\\advai\\PycharmProjects\\youtubeapitest\\oauthtest.py");
		FILE *file = _Py_fopen_obj(obj, "r+");
		FILE *file2 = _Py_fopen("C:\\Users\\advai\\PycharmProjects\\youtubeapitest\\oauthtest.py", "r+");
		PyRun_SimpleFile(file2, "C:\\Users\\advai\\PycharmProjects\\youtubeapitest\\oauthtest.py");
		button->setLabel("LOGGED IN!");
		loggedIn = true;

		std::ifstream topicIdStream("C:\\Users\\advai\\PycharmProjects\\youtubeapitest\\topic_ids.json");
		json topicIds = json::parse(topicIdStream);
		topicIdStream.close();
		map<string, int> topicCount;
		for (int i = 0; i < topicIds["items"].size(); i++) {
			topicCount.emplace(topicIds["items"][i], 0);
		}

		std::ifstream i("C:\\Users\\advai\\PycharmProjects\\youtubeapitest\\subscription_data.json");
		json subscriber_json = json::parse(i);
		i.close();
		for (int i = 0; i < subscriber_json["items"].size(); i++) {
			subscriptionSubscriberCount.emplace_back(i, subscriber_json["items"][i]["subscriberCount"], subscriber_json["items"][i]["title"]);
			subscriptionViewCount.emplace_back(i, subscriber_json["items"][i]["viewCount"], subscriber_json["items"][i]["title"]);
			for (int j = 0; j < subscriber_json["items"][i]["topicIds"].size(); j++) {
				topicCount[subscriber_json["items"][i]["topicIds"][j]]++;
			}
		}
		int count2 = 0;
		for (const auto &pair : topicCount) {
			subscriptionTopicsCount.emplace_back(count2, pair.second, pair.first);
			count2++;
		}
		subscriptionSubscriberCount = normalize(subscriptionSubscriberCount);
		subscriptionViewCount = normalize(subscriptionViewCount);

		for (int i = 0; i < subscriptionSubscriberCount.size(); i++) {
			popularity.emplace_back(i, (subscriptionSubscriberCount[i].getY() + subscriptionViewCount[i].getY()) / 2, subscriptionSubscriberCount[i].getLabel());
		}
		popularity = normalize(popularity);


		std::ifstream categories_stream("C:\\Users\\advai\\PycharmProjects\\youtubeapitest\\video_categories.json");
		json vidCategories = json::parse(categories_stream);
		categories_stream.close();
		map<string, int> categoryCount;
		for (int i = 0; i < vidCategories["items"].size(); i++) {
			categoryCount.emplace(vidCategories["items"][i], 0);
		}

		std::ifstream j("C:\\Users\\advai\\PycharmProjects\\youtubeapitest\\liked_video_data.json");
		json liked_video_json = json::parse(j);
		j.close();
		for (int i = 0; i < liked_video_json["items"].size(); i++) {
			likedVideoLikeCount.emplace_back(i, liked_video_json["items"][i]["likeCount"], liked_video_json["items"][i]["title"]);
			likedVideoViewCount.emplace_back(i, liked_video_json["items"][i]["viewCount"], liked_video_json["items"][i]["title"]);
			categoryCount[liked_video_json["items"][i]["category"]]++;
		}
		int count = 0;
		for (const auto &pair : categoryCount) {
			likedVideoTopics.emplace_back(count, pair.second, pair.first);
			count++;
		}
		likedVideoViewCount = normalize(likedVideoViewCount);
		likedVideoLikeCount = normalize(likedVideoLikeCount);
	}
}

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

//--------------------------------------------------------------
void ofApp::update() {
	subscriptionsFolder->update();
	videosFolder->update();
	button->update();
	header->update();
	graphDescription->update();
}

//--------------------------------------------------------------
void ofApp::draw() {
	//ofSetHexColor(0x000000);
	//ofFill();
	//ofDrawRectangle(100, 100, 500, 500);
	//ofSetHexColor(0xffffff);
	//myfont->drawString("a test of\nmultiline text", 100, 100);
	//myScrollView->draw();
	header->draw();
	graphDescription->draw();
	button->draw();
	//label->draw();
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

vector<ofxGPoint> ofApp::normalize(vector<ofxGPoint> vec)
{
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
