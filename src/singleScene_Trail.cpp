//
//  singleScene_Trail.cpp
//  cvGeoGraphics
//
//  Created by Ovis aries on 2014/08/01.
//
//

#include "singleScene_Trail.h"

void singleScene_trail::setup_virtual(){

	trailGen.setup();
}

void singleScene_trail::update_virtual(){

	ofFloatColor c = baseColor;

	vector<ofPoint> feat = geoGraphPtr->flow.getFeatures();
	if (feat_b.size() == 0)	feat_b = feat;

	for (int i = 0;i < feat.size();i+=3){
		trailGen.setPoint(feat[i]);
	}

	trailGen.update();
	feat_b.clear();
	feat_b = feat;
}

void singleScene_trail::draw_virtual(){

	ofEnableBlendMode(OF_BLENDMODE_ADD);
	ofFloatColor c = baseColor;

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	trailGen.draw();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	
	
}