//
//  particleEmitter.h
//  carTracking_first
//
//  Created by Ovis aries on 2014/07/31.
//
//

#ifndef __carTracking_first__particleEmitter__
#define __carTracking_first__particleEmitter__

#include "ofMain.h"

#define MAX_PARTICLE_NUM 2500
#define EMIT_UNIT_NUM 4

class particleEmitter{
public:
	void setup();
	void update(ofFloatColor c = ofFloatColor(0.3,0.9,0.5,1.0));
	void draw();
	void drawMultiSplite(vector<ofTexture*> textures);

	void setAttenuation(float val);
	void setLife(float val);
	void emitParticle(ofVec3f pos,ofVec3f vec,int unit);

	ofVbo pVbo[EMIT_UNIT_NUM];
	vector<ofVec3f>			pts[EMIT_UNIT_NUM];
	vector<ofVec3f>			vecs[EMIT_UNIT_NUM];
	vector<ofFloatColor>	colors[EMIT_UNIT_NUM];

	float attenuation;
	float life;
	ofImage texture;
};

#endif /* defined(__carTracking_first__particleEmitter__) */
