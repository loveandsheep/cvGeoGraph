//
//  singleScene_Trail.h
//  cvGeoGraphics
//
//  Created by Ovis aries on 2014/08/01.
//
//

#ifndef __cvGeoGraphics__singleScene_Trail__
#define __cvGeoGraphics__singleScene_Trail__

#include "basicSingleScene.h"
#include "trailGenerator.h"

class singleScene_trail : public basicSingleScene{
public:
	singleScene_trail(){

	}

	virtual void setup_virtual();
	virtual void update_virtual();
	virtual void draw_virtual();

	vector<ofPoint> feat_b;
	trailGenerator trailGen;
};


#endif /* defined(__cvGeoGraphics__singleScene_Trail__) */
