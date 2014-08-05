//
//  singleScene_particle.cpp
//  cvGeoGraphics
//
//  Created by Ovis aries on 2014/08/01.
//
//

#include "singleScene_particle.h"

void singleScene_particle::setup_virtual(){
	pEmit.setup();
	pEmit.setAttenuation(0.90);


	tex.push_back(new ofTexture());
	ofLoadImage(*tex.back(), "textures/flare.png");

	tex.push_back(new ofTexture());
	ofLoadImage(*tex.back(), "textures/flare_line.png");

	tex.push_back(new ofTexture());
	ofLoadImage(*tex.back(), "textures/flare.png");

	tex.push_back(new ofTexture());
	ofLoadImage(*tex.back(), "textures/flare_line.png");

	tex.push_back(new ofTexture());
	ofLoadImage(*tex.back(), "textures/flare.png");
}

void singleScene_particle::update_virtual(){

	ofFloatColor c = baseColor;
	pEmit.update(c);
	pEmit.update(c);

	vector<ofPoint> feat = geoGraphPtr->flow.getFeatures();
	if (feat_b.size() == 0)	feat_b = feat;

	for (int i = 0;i < feat.size();i+=3){
		for (int j = 0;j < 2;j++){
			ofVec3f v = ofVec3f(ofRandomuf(),
								ofRandomuf(),
								ofRandomuf());
			pEmit.emitParticle(feat[i], (feat[i] - feat_b[i])*v, (i+j)%EMIT_UNIT_NUM);
		}
	}

	feat_b.clear();
	feat_b = feat;
}

void singleScene_particle::draw_virtual(){

	ofEnableBlendMode(OF_BLENDMODE_ADD);
	ofFloatColor c = baseColor;

	pEmit.drawMultiSplite(tex);

	vector<ofPoint> feat = geoGraphPtr->flow.getFeatures();
	if (feat_b.size() == 0)	feat_b = feat;

	if (feat.size() > 0){
		ofSetColor(c);
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


	ofEnableBlendMode(OF_BLENDMODE_ALPHA);


}