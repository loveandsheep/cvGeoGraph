#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetFrameRate(30);
	
	trainer.setup();

	canvas.setup();
	canvas.setPosition(30, 30);
	canvas.setName("Trainer");
	canvas.addLabel("Trainer",OFX_UI_FONT_LARGE);
	canvas.addSpacer();
	canvas.addSlider("test", 0.0, 1.0, &trainer.testVal, 200, 15);
	canvas.addSlider("Hue", 0.0, 1.0, &baseCol_hue);
	canvas.addSlider("Sat", 0.0, 1.0, &baseCol_sat);
	canvas.addSlider("Bri", 0.0, 1.0, &baseCol_bri);
	canvas.addRangeSlider("cutRange", 0.0, 1.0, &trainer.cutRange_low, &trainer.cutRange_high);
	canvas.addSlider("videoPos", 0.0, 1.0, &video_pos);
	canvas.addFPS();
	canvas.autoSizeToFitWidgets();

	ofAddListener(canvas.newGUIEvent, this, &ofApp::guiEvent);

	baseCol_hue = 0.28;
	baseCol_sat = 0.8;
	baseCol_bri = 1.0;
	trainer.cutRange_low  = 0.0;
	trainer.cutRange_high = 1.0;

	ofFloatColor c;
	c.setHsb(baseCol_hue, baseCol_sat, baseCol_bri);
	trainer.setBaseColor(c);
}

//--------------------------------------------------------------
void ofApp::update(){

	video_pos = trainer.videos[trainer.currentVideo].getPosition();
	trainer.update();

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(0, 0, 0);
	ofSetColor(255);

	trainer.fboReflesh();
	trainer.draw(0, 0, ofGetWidth(), ofGetHeight());

}

void ofApp::guiEvent(ofxUIEventArgs &e){

	if (e.getName() == "Hue" ||
		e.getName() == "Sat" ||
		e.getName() == "Bri"){
		ofFloatColor c;
		c.setHsb(baseCol_hue, baseCol_sat, baseCol_bri);
		trainer.setBaseColor(c);
	}

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == ' ') trainer.cutUp();
	if (key == 'n') trainer.resetFlow();
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
