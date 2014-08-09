//
//  basicSingleScene.h
//  cvGeoGraphics
//
//  Created by Ovis aries on 2014/07/28.
//
//

#ifndef __cvGeoGraphics__basicSingleScene__
#define __cvGeoGraphics__basicSingleScene__

#include "ofMain.h"
#include "cvGeoGraph.h"

class basicSingleScene{
public:
	basicSingleScene(){
		
	}

	virtual void setup_virtual();
	virtual void update_virtual();
	virtual void draw_virtual();

	void setup(cvGeoGraph* ptr);
	void update();
	void draw();

	float sigmoid(float x,bool flip = false){
		x = (x - 0.5) * 12.0;
		float e = 2.71828182846;

		if (!flip) return 1.0 / (1.0 + pow(e,-x));
		else	   return 1.0 - (1.0 / (1.0 + pow(e, -x)));
	}

	cvGeoGraph*		geoGraphPtr;
	ofFloatColor	baseColor;
	float			soundVolume;
};

#endif /* defined(__cvGeoGraphics__basicSingleScene__) */