//
//  singleScene_delaunay.h
//  cvGeoGraphics
//
//  Created by Ovis aries on 2014/07/28.
//
//

#ifndef __cvGeoGraphics__singleScene_delaunay__
#define __cvGeoGraphics__singleScene_delaunay__

#include "basicSingleScene.h"
#include "ofxDelaunay.h"

class singleScene_Delaunay : public basicSingleScene{
public:
	singleScene_Delaunay(){

	}
	
	virtual void setup_virtual();
	virtual void update_virtual();
	virtual void draw_virtual();

	ofxDelaunay delaunay;
};

#endif /* defined(__cvGeoGraphics__singleScene_delaunay__) */
