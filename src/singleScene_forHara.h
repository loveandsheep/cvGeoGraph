//
//  singleScene_forHara.h
//  cvGeoGraphics
//
//  Created by Ovis aries on 2014/08/10.
//
//

#ifndef __cvGeoGraphics__singleScene_forHara__
#define __cvGeoGraphics__singleScene_forHara__

#include "basicSingleScene.h"

class singleScene_forHara : public basicSingleScene{
public:
	singleScene_forHara(){

	}

	virtual void setup_virtual();
	virtual void update_virtual();
	virtual void draw_virtual();

	bool isFeatNew;

	vector<ofPoint> feat;//特徴点の配列
	vector<ofPoint> feat_b;//1フレーム前の特徴点
	vector<ofVec3f> velocity;//特徴点の速度
};


#endif /* defined(__cvGeoGraphics__singleScene_forHara__) */
