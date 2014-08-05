//
//  singleScene_particle.h
//  cvGeoGraphics
//
//  Created by Ovis aries on 2014/08/01.
//
//

#ifndef __cvGeoGraphics__singleScene_particle__
#define __cvGeoGraphics__singleScene_particle__

#include "basicSingleScene.h"
#include "particleEmitter.h"

class singleScene_particle : public basicSingleScene{
public:
	singleScene_particle(){

	}

	virtual void setup_virtual();
	virtual void update_virtual();
	virtual void draw_virtual();

	vector<ofPoint> feat_b;
	particleEmitter pEmit;

	vector<ofTexture*> tex;
};


#endif /* defined(__cvGeoGraphics__singleScene_particle__) */
