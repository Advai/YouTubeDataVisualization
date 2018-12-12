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
	//myScrollView = new ofxDatGuiScrollView("Possible Statistics", 10);
	//myScrollView->setPosition(0, 200);
	//myScrollView->setHeight(1600);
	//myScrollView->add("Liked Videos");
	//myScrollView->add("Disliked Videos");
	subscriptionsFolder = new ofxDatGuiFolder("Subscriptions Based Graphs", ofColor::white);
	subscriptionsFolder->setWidth(800);
	subscriptionsFolder->addButton("Views");
	subscriptionsFolder->addButton("Subscriber Count");
	subscriptionsFolder->getComponent(ofxDatGuiType::BUTTON, "Views")->setWidth(800, 1);
	subscriptionsFolder->getComponent(ofxDatGuiType::BUTTON, "Views")->onButtonEvent(this, &ofApp::viewsEvent);
	subscriptionsFolder->getComponent(ofxDatGuiType::BUTTON, "Subscriber Count")->setWidth(800, 1);
	subscriptionsFolder->setPosition(0, 200);
	subscriptionsFolder->expand();
	subscriptionsFolder->toggle();
	button = new ofxDatGuiButton("Log In");
	button->setPosition(2650, 0);
	button->setLabelAlignment(ofxDatGuiAlignment::CENTER);
	button->setHeight(200, 1);
	button->onButtonEvent(this, &ofApp::onButtonEvent);
	string::size_type sz;
	vector<ofxGPoint> points;
	std::ifstream i("C:\\Users\\advai\\PycharmProjects\\youtubeapitest\\subscription_data.json");
	json subscriber_json = json::parse(i);
	i.close();
	auto views = subscriber_json["items"][0]["viewCount"].dump();
	auto title = subscriber_json["items"][0]["title"].dump();
	cout << title + views;
	cout << subscriber_json["items"][0]["viewCount"].is_string();
	//cout << subscriber_json["items"][0]["viewCount"] +" " + subscriber_json["items"][0]["title"];
	for (int i = 0; i < subscriber_json["items"].size(); i++) {
		//cout << subscriber_json["items"][i]["viewCount"] + " " + subscriber_json["items"][i]["title"];
		//float var = stof(subscriber_json["items"][i]["viewCount"].dump());
		points.emplace_back(i, subscriber_json["items"][i]["viewCount"], subscriber_json["items"][i]["title"]);
	}
	plot.setPoints(points);

	plot.setPos(500, 600);
	plot.setDim(800, 800);
	plot.getTitle().setText("Subscriber Graph by total view count");
	plot.getTitle().setTextAlignment(GRAFICA_CENTER_ALIGN);
	plot.getYAxis().setAxisLabelText("Views");
	plot.getXAxis().setAxisLabelText("Channel");
	plot.startHistograms(GRAFICA_VERTICAL_HISTOGRAM);
	plot.getHistogram().setDrawLabels(true);
	plot.getHistogram().setRotateLabels(true);
	plot.getHistogram().setBgColors({ ofColor(0, 0, 255, 50), ofColor(0, 0, 255, 100), ofColor(0, 0, 255, 150),
			ofColor(0, 0, 255, 200) });

}

void ofApp::onButtonEvent(ofxDatGuiButtonEvent e)
{
	if (e.target == button) {
		//system("python oauthtest.py");
		//Py_SetProgramName("get data from youtube api");
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

void ofApp::viewsEvent(ofxDatGuiButtonEvent e)
{
		/*vector<ofxGPoint> points;
		std::ifstream i("C:\\Users\\advai\\PycharmProjects\\youtubeapitest\\subscription_data.json");
		json subscriber_json = json::parse(i);
		i.close();
		for (int i = 0; i < subscriber_json["items"].size(); i++) {
			cout << subscriber_json["items"][i]["viewCount"] + " " + subscriber_json["items"][i]["title"];
			points.emplace_back(i, subscriber_json["items"][i]["viewCount"], subscriber_json["items"][i]["title"]);
		}
		plot.setPoints(points);*/
}

//--------------------------------------------------------------
void ofApp::update() {
	subscriptionsFolder->update();
	button->update();
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
