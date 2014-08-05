//
//  singleScene_delaunay.cpp
//  cvGeoGraphics
//
//  Created by Ovis aries on 2014/07/28.
//
//

#include "singleScene_delaunay.h"

void singleScene_Delaunay::setup_virtual(){

}

void singleScene_Delaunay::update_virtual(){
	
	vector<ofPoint> feat = geoGraphPtr->flow.getFeatures();

	delaunay.reset();

	for (int i = 0;i < feat.size();i+=5){
		delaunay.addPoint(feat[i]);
	}

	if (feat.size() > 0) delaunay.triangulate();

}

void singleScene_Delaunay::draw_virtual(){
	ofEnableBlendMode(OF_BLENDMODE_ADD);


	ofMesh tri = delaunay.triangleMesh;
	ofFloatColor c = baseColor;

	for (int i = 0;i < tri.getNumIndices();i+=3){
		c.setHue(baseColor.getHue() + ofNoise(i/12.5)/3.0);
		ofSetColor(c);

		if (i % 13 == 0)	glBegin(GL_TRIANGLES);
		else				glBegin(GL_LINE_STRIP);

		glVertex2f(tri.getVertices()[tri.getIndex(i  )].x,
				   tri.getVertices()[tri.getIndex(i  )].y);
		glVertex2f(tri.getVertices()[tri.getIndex(i+1)].x,
				   tri.getVertices()[tri.getIndex(i+1)].y);
		glVertex2f(tri.getVertices()[tri.getIndex(i+2)].x,
				   tri.getVertices()[tri.getIndex(i+2)].y);

		glEnd();
	}

	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	ofSetColor(255);
}