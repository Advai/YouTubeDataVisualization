#include <Python.h>
#include "ofApp.h"
#include <stdlib.h>
#include "json.hpp"

using json = nlohmann::json;

//--------------------------------------------------------------
void ofApp::setup() {
	myfont = new ofTrueTypeFont();

	myfont->load(OF_TTF_SANS, 32);
	ofxDatGui* gui = new ofxDatGui(3200, 1800);
	// add some components //
	header = new ofxDatGuiLabel("Youtube Data Visualizer");
	header->setBackgroundColor(ofColor::red);
	header->setLabelColor(ofColor::white);
	header->setLabelAlignment(ofxDatGuiAlignment::CENTER);
	header->setWidth(3200, .9);
	header->setPosition(0, 0);
	header->setHeight(200);


	subscriptionsFolder = new ofxDatGuiFolder("Subscriptions Based Graphs", ofColor::white);
	subscriptionsFolder->setWidth(800);
	subscriptionsFolder->setPosition(0, 200);
	subscriptionsFolder->expand();
	subscriptionsFolder->toggle();
	
	subscriptionsFolder->addButton("Views");
	subscriptionsFolder->addButton("Subscriber Count");
	subscriptionsFolder->addButton("Popularity");
	
	subscriptionsFolder->getComponent(ofxDatGuiType::BUTTON, "Views")->setWidth(800, 1);
	subscriptionsFolder->getComponent(ofxDatGuiType::BUTTON, "Views")->onButtonEvent(this, &ofApp::viewsEvent);
	subscriptionsFolder->getComponent(ofxDatGuiType::BUTTON, "Popularity")->onButtonEvent(this, &ofApp::popularityEvent);
	subscriptionsFolder->getComponent(ofxDatGuiType::BUTTON, "Popularity")->setWidth(800, 1);
	subscriptionsFolder->getComponent(ofxDatGuiType::BUTTON, "Subscriber Count")->onButtonEvent(this, &ofApp::subEvent);
	subscriptionsFolder->getComponent(ofxDatGuiType::BUTTON, "Subscriber Count")->setWidth(800, 1);
	
	
	
	button = new ofxDatGuiButton("Log In");
	button->setPosition(2650, 0);
	button->setLabelAlignment(ofxDatGuiAlignment::CENTER);
	button->setHeight(200, 1);
	button->onButtonEvent(this, &ofApp::onButtonEvent);


	std::ifstream i("C:\\Users\\advai\\PycharmProjects\\youtubeapitest\\subscription_data.json");
	json subscriber_json = json::parse(i);
	i.close();
	for (int i = 0; i < subscriber_json["items"].size(); i++) {
		subscriptionSubscriberCount.emplace_back(i, subscriber_json["items"][i]["subscriberCount"], subscriber_json["items"][i]["title"]);
		subscriptionViewCount.emplace_back(i, subscriber_json["items"][i]["viewCount"], subscriber_json["items"][i]["title"]);
	}
	subscriptionSubscriberCount = normalize(subscriptionSubscriberCount);
	subscriptionViewCount = normalize(subscriptionViewCount);

	for (int i = 0; i < subscriptionSubscriberCount.size(); i++) {
		popularity.emplace_back(i, (subscriptionSubscriberCount[i].getY() + subscriptionViewCount[i].getY()) / 2, subscriptionSubscriberCount[i].getLabel());
	}
	plot.setPoints(subscriptionSubscriberCount);

	plot.setPos(1000, 250);
	plot.setDim(1500, 700);
	plot.setYLim(0, 1);
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
	plot.getTitle().setText("Subscriber Graph by total view count");
	plot.getTitle().setTextAlignment(GRAFICA_CENTER_ALIGN);
	plot.getYAxis().setAxisLabelText("Views");
	plot.getYAxis().setFontSize(12);
	plot.getXAxis().setFontSize(12);
	plot.getXAxis().getAxisLabel().setFontSize(18);
	plot.getYAxis().getAxisLabel().setFontSize(18);
	plot.getXAxis().setAxisLabelText("Channel");
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
		/*std::ifstream i("C:\\Users\\advai\\PycharmProjects\\youtubeapitest\\subscription_data.json");
		subscriber_json = json::parse(i);
		for (int i = 0; i < subscriber_json["items"].size(); i++) {
			cout << subscriber_json["items"][i]["viewCount"] + " " + subscriber_json["items"][i]["title"];
			points->emplace_back(i, subscriber_json["items"][i]["viewCount"], subscriber_json["items"][i]["title"]);
		}
		i.close();*/
	}
}

void ofApp::popularityEvent(ofxDatGuiButtonEvent e) 
{
	plot.setPoints(popularity);
}

void ofApp::viewsEvent(ofxDatGuiButtonEvent e)
{
	plot.setPoints(subscriptionViewCount);
}

void ofApp::subEvent(ofxDatGuiButtonEvent e) 
{
	plot.setPoints(subscriptionSubscriberCount);	
}

//--------------------------------------------------------------
void ofApp::update() {
	subscriptionsFolder->update();
	button->update();
	header->update();
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
	button->draw();
	//label->draw();
	subscriptionsFolder->draw();
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
