//
//  cvGeoGraph.h
//  cvGeoGraphics
//
//  Created by Ovis aries on 2014/07/11.
//
//

#ifndef __cvGeoGraphics__cvGeoGraph__
#define __cvGeoGraphics__cvGeoGraph__

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxDelaunay.h"

class cvGeoGraph {
public:

	void setup();
	void update(ofPixelsRef& pix);
	void draw();

	ofxCv::FlowPyrLK flow;
	ofxDelaunay del;

	int mode;
};

#endif /* defined(__cvGeoGraphics__cvGeoGraph__) */
