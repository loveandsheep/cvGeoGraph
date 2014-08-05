//
//  singleScene_tileSquare.cpp
//  cvGeoGraphics
//
//  Created by Ovis aries on 2014/07/28.
//
//

#include "singleScene_tileSquare.h"

void singleScene_TileSquare::setup_virtual(){

}

void singleScene_TileSquare::update_virtual(){

}

void singleScene_TileSquare::draw_virtual(){
	vector<ofPoint> feat = geoGraphPtr->flow.getFeatures();
	if (feat_b.size() == 0)	feat_b = feat;

	ofEnableBlendMode(OF_BLENDMODE_ADD);
	ofFloatColor c = baseColor;

	ofSetRectMode(OF_RECTMODE_CENTER);
	for (int i = 0;i < feat.size();i+=3){

		ofPushMatrix();
		ofTranslate(feat[i]);
		ofRotateZ(-25);

		ofVec2f v = ofVec2f(feat[i] - feat_b[i]);
		float scl = MIN(400,5 + v.lengthSquared()/30.0);

		c.setHue(baseColor.getHue() + ofNoise(i/35.5)/2.5);
		c.setBrightness(baseColor.getBrightness() * MIN(1.0,MAX(0.0,(1.0 - scl/555.0))));
		ofSetColor(c);

		if (i % 6 == 0) ofNoFill();

		ofRect(0, 0, scl, scl);
		ofFill();

		ofPopMatrix();
	}
	ofSetRectMode(OF_RECTMODE_CORNER);
	glLineWidth(1.0);

	if (feat.size() > 0){
		for (int i = 0;i < 5;i++){
			int idx1 = MIN(feat.size(),ofNoise(i/3.2 + ofGetElapsedTimef()/32.3)*feat.size());
			int idx2 = MIN(feat.size(),ofNoise(i/5.4 + ofGetElapsedTimef()/55.3)*feat.size());
			ofLine(feat[idx1], feat[idx2]);
		}
	}

	ofEnableBlendMode(OF_BLENDMODE_ALPHA);

	feat_b.clear();
	feat_b = feat;
}