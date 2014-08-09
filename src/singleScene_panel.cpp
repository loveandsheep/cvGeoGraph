//
//  singleScene_panel.cpp
//  cvGeoGraphics
//
//  Created by Ovis aries on 2014/07/28.
//
//

#include "singleScene_panel.h"

void singleScene_panel::setup_virtual(){
	font.loadFont("assets/SIMPLIFICA.ttf", 36);
}

void singleScene_panel::update_virtual(){

}

void singleScene_panel::draw_virtual(){
	vector<ofPoint> feat = geoGraphPtr->flow.getFeatures();
	if (feat_b.size() == 0)	feat_b = feat;

	ofEnableBlendMode(OF_BLENDMODE_ADD);
	ofFloatColor c = baseColor;

	for (int i = 0;i < feat.size();i+=6){

		ofPushMatrix();
		ofTranslate(feat[i]);
		ofVec2f v = ofVec2f(feat[i] - feat_b[i]);

		c = baseColor;

		c.setHue(baseColor.getHue()+ofNoise(i/34.1)/2.5);
		if (i / 3 % 7 == 0) c.setHue(fmod(c.getHue() - 0.2f,1.0f));
		ofSetColor(c);
		ofEnableBlendMode(OF_BLENDMODE_ADD);

		ofMesh m = font.getStringMesh(ofToString(ofRandomuf()), 0, 36);
		float scl = pow(ofNoise(i/34.5),1.2f);

		glScaled(scl, scl, scl);
		font.getFontTexture().bind();
		m.drawFaces();
		font.getFontTexture().unbind();

		c.setBrightness(0.3 * baseColor.getBrightness());
		ofSetColor(c);

		float rectW = sigmoid(sin(i/23.5+ofGetElapsedTimef()/1.5));
		ofRect(0, 0, 140 * rectW, 38);
		for (int j = 0;j < 36;j+=4){
			ofLine(0, j, 140 * rectW, j);
		}

		ofFill();

		ofPopMatrix();

	}

	glLineWidth(2.0);//チャネル
	c = baseColor;
	ofSetColor(baseColor);
	
	if (feat.size() > 0){
		for (int i = 0;i < 2;i++){
			int idx[3];
			idx[0] = ofNoise(i/3.5+ofGetElapsedTimef()/34.3)*feat.size();
			idx[1] = ofNoise(i/6.5+ofGetElapsedTimef()/27.4)*feat.size();
			idx[2] = ofNoise(i/8.5+ofGetElapsedTimef()/49.7)*feat.size();

			glBegin(GL_LINE_STRIP);
			glVertex2d(feat[idx[0]].x, feat[idx[0]].y);
			glVertex2d(feat[idx[1]].x, feat[idx[1]].y);
			glVertex2d(feat[idx[2]].x, feat[idx[2]].y);
			glVertex2d(feat[idx[0]].x, feat[idx[0]].y);
			glEnd();
		}
	}
	glLineWidth(1.0);
	
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);

	feat_b.clear();
	feat_b = feat;
}