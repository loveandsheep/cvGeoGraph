//
//  cvGeoGraph.cpp
//  cvGeoGraphics
//
//  Created by Ovis aries on 2014/07/11.
//
//

#include "cvGeoGraph.h"

void cvGeoGraph::setup(){
	mode = 0;

}

void cvGeoGraph::update(ofPixelsRef& pix){

	flow.calcOpticalFlow(pix);

}

void cvGeoGraph::draw(){

	del.reset();

	if (ofGetKeyPressed('0')) mode = 0;
	if (ofGetKeyPressed('1')) mode = 1;
	if (ofGetKeyPressed('2')) mode = 2;
	if (ofGetKeyPressed('3')) mode = 3;
	if (ofGetKeyPressed('4')) mode = 4;
	if (ofGetKeyPressed('5')) mode = 5;
	if (ofGetKeyPressed('6')) mode = 6;
	if (ofGetKeyPressed('7')) mode = 7;

	if (mode == 0){
		flow.draw();
		for (int i = 0;i < flow.getFeatures().size();i+=5){
			ofVec2f p = flow.getFeatures()[i];
			ofPushMatrix();
			ofTranslate(p);
			ofLine(-5, 0, 5, 0);
			ofLine(0, -5, 0, 5);
			ofPopMatrix();
		}
	}

	if (mode == 1){
		for (int i = 0;i < flow.getFeatures().size();i+=2){

			ofVec2f p = flow.getFeatures()[i];
			ofPushMatrix();
			ofTranslate(p);
			ofNoFill();
			ofSetRectMode(OF_RECTMODE_CENTER);
			ofRect(0, 0, ofNoise(i/23.1)*30, ofNoise(i/23.1)*30);
			ofRect(0, 0, ofNoise(i/23.1)*20, ofNoise(i/23.1)*20);
			ofSetRectMode(OF_RECTMODE_CORNER);
			ofFill();
			ofPopMatrix();

		}
	}

	if (mode == 2){
		for (int i = 0;i < flow.getFeatures().size();i+=10){

			ofVec2f p = flow.getFeatures()[i];
			ofPushMatrix();
			ofTranslate(p);
			ofDrawBitmapString(ofToString(ofRandomf()), 0,0);
			ofPopMatrix();

		}
	}

	for (int i = 0;i < flow.getFeatures().size();i+=3){
		ofVec2f p = flow.getFeatures()[i];

		if (ofRectangle(50,50,1200,690).inside(p)){
			del.addPoint(flow.getFeatures()[i]);
		}
	}

	if (flow.getFeatures().size() > 3){
		del.triangulate();
	}

	ofNoFill();
	if (mode == 0) del.draw();
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	ofFill();

	ofSetColor(255);

}