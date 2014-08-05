//
//  trailGenerator.cpp
//  carTracking_first
//
//  Created by Ovis aries on 2014/08/01.
//
//

#include "trailGenerator.h"

void trailGenerator::setup(){
	trails.clear();
}

void trailGenerator::setPoint(ofVec3f pt){

	int catchTrail = -1;

	for (int i = 0;i < trails.size();i++){
		if (trails[i].pts.back().distanceSquared(pt) < 10000){
			catchTrail = i;
		}
	}

	if (catchTrail != -1){
		trails[catchTrail].addPt(pt);
	}else{
//		trails.push_back(audioTrail(pt, &audioFloat));
		trails.push_back(scopeTrail(pt, scope_left));
	}

}

void trailGenerator::update(){
	for (int i = 0;i < trails.size();i++){
		trails[i].update();

		if (trails[i].aliveCount > 30)
			trails.erase(trails.begin()+i);
	}

	if (ofGetKeyPressed('c')) trails.clear();
}

void trailGenerator::draw(){
	if (trails.size() > 0){
		for (int i = 0;i < trails.size();i++){
			trails[i].draw();
		}
	}
}