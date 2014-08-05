//
//  singleScene_panel.h
//  cvGeoGraphics
//
//  Created by Ovis aries on 2014/07/28.
//
//

#ifndef __cvGeoGraphics__singleScene_panel__
#define __cvGeoGraphics__singleScene_panel__

#include "basicSingleScene.h"

class singleScene_panel : public basicSingleScene{
public:
	singleScene_panel(){

	}

	virtual void setup_virtual();
	virtual void update_virtual();
	virtual void draw_virtual();

	vector<ofPoint> feat_b;
	ofTrueTypeFont font;
};

#endif /* defined(__cvGeoGraphics__singleScene_panel__) */
