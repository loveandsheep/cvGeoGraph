//
//  singleScene_tileSquare.h
//  cvGeoGraphics
//
//  Created by Ovis aries on 2014/07/28.
//
//

#ifndef __cvGeoGraphics__singleScene_tileSquare__
#define __cvGeoGraphics__singleScene_tileSquare__

#include "basicSingleScene.h"

class singleScene_TileSquare : public basicSingleScene{
public:
	singleScene_TileSquare(){

	}

	virtual void setup_virtual();
	virtual void update_virtual();
	virtual void draw_virtual();

	bool isFeatNew;
	vector<ofPoint> feat;
	vector<ofPoint> feat_b;
	vector<ofVec3f> velocity;
};

#endif /* defined(__cvGeoGraphics__singleScene_tileSquare__) */
