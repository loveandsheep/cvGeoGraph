//
//  Trainer.h
//  cvGeoGraphics
//
//  Created by Ovis aries on 2014/07/25.
//
//

#ifndef __cvGeoGraphics__Trainer__
#define __cvGeoGraphics__Trainer__

#include "cvGeoGraph.h"
#include "ofMain.h"
#include "singleScene_delaunay.h"
#include "singleScene_crossHatch.h"
#include "singleScene_tileSquare.h"
#include "singleScene_panel.h"
#include "singleScene_particle.h"
#include "singleScene_Trail.h"

class Trainer{
public:

	void setup();
	void update();
	void fboReflesh();
	void draw(int x,int y,int w,int h);

	void cutUp();
	void resetFlow();
	void addVideo(string file);
	void changeVideo(int index);

	void setBaseColor(ofFloatColor c);

	cvGeoGraph geoGraph;

	vector<ofVideoPlayer> videos;
	vector<basicSingleScene*> scenes;
	ofFbo buffer;

	int currentVideo;
	int currentGraph;

	float cutRange_low,cutRange_high;

	float testVal;

	ofRectangle maskRect[2];

	bool videoGrab;
	ofVideoGrabber grabCam;
};

#endif /* defined(__cvGeoGraphics__Trainer__) */
