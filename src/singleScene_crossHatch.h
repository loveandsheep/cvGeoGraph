//
//  singleScene_crossHatch.h
//  cvGeoGraphics
//
//  Created by Ovis aries on 2014/07/28.
//
//

#ifndef __cvGeoGraphics__singleScene_crossHatch__
#define __cvGeoGraphics__singleScene_crossHatch__

#include "basicSingleScene.h"

class singleScene_CrossHatch : public basicSingleScene{
public:
	singleScene_CrossHatch(){

	}

	virtual void setup_virtual();
	virtual void update_virtual();
	virtual void draw_virtual();

	bool isFeatNew;
	
	vector<ofPoint> feat;
	vector<ofPoint> feat_b;
	vector<ofVec3f> velocity;
};

#endif /* defined(__cvGeoGraphics__singleScene_crossHatch__) */
