//
//  basicSingleScene.cpp
//  cvGeoGraphics
//
//  Created by Ovis aries on 2014/07/28.
//
//

#include "basicSingleScene.h"

void basicSingleScene::setup(cvGeoGraph *ptr){
	geoGraphPtr = ptr;
	setup_virtual();
}

void basicSingleScene::update(){
	update_virtual();
}

void basicSingleScene::draw(){
	draw_virtual();
}

//Override class================================

void basicSingleScene::setup_virtual(){
	
}

void basicSingleScene::draw_virtual(){

}

void basicSingleScene::update_virtual(){

}