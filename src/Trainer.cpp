//
//  Trainer.cpp
//  cvGeoGraphics
//
//  Created by Ovis aries on 2014/07/25.
//
//

#include "Trainer.h"

void Trainer::setup(){

	geoGraph.setup();

	//Video management========================
	currentVideo = 0;

	addVideo("videos/Yuri.mov");
	addVideo("videos/Kei_pj.mov");
	addVideo("videos/Twin.mov");
	addVideo("tofu.mp4");

	for (int i = 0;i < videos.size();i++){
		videos[i].play();
		videos[i].setVolume(0.0);
	}

	//Scene management========================

	currentGraph = 0;
	scenes.push_back(new singleScene_Delaunay());
	scenes.push_back(new singleScene_CrossHatch());
	scenes.push_back(new singleScene_TileSquare());
	scenes.push_back(new singleScene_panel());
	scenes.push_back(new singleScene_particle());
	scenes.push_back(new singleScene_trail());

	for (int i = 0;i < scenes.size();i++){
		scenes[i]->setup(&geoGraph);
	}

	ofFbo::Settings settings;
	settings.width = 1280;
    settings.height = 720;
    settings.internalformat	= GL_RGBA;
    settings.useDepth		= true;
    settings.useStencil		= false;
    settings.textureTarget	= ofGetUsingArbTex() ? GL_TEXTURE_RECTANGLE_ARB : GL_TEXTURE_2D;
    settings.depthStencilInternalFormat = GL_DEPTH_COMPONENT16;
	settings.depthStencilAsTexture = false;
    settings.minFilter = GL_LINEAR;
    settings.maxFilter = GL_LINEAR;
    settings.numSamples = 8;

	buffer.allocate(settings);

	videoGrab = false;

//	grabCam.listDevices();
//	grabCam.setDeviceID(0);
	if (videoGrab) grabCam.initGrabber(1280,720);

	maskRect[0].set(0, 0, 1280, 720);
}

void Trainer::update(){
	if (ofGetKeyPressed('1')) currentVideo = 0;
	if (ofGetKeyPressed('2')) currentVideo = 1;
	if (ofGetKeyPressed('3')) currentVideo = 2;

	if (ofGetKeyPressed('q')) currentGraph = 0;
	if (ofGetKeyPressed('w')) currentGraph = 1;
	if (ofGetKeyPressed('e')) currentGraph = 2;
	if (ofGetKeyPressed('r')) currentGraph = 3;
	if (ofGetKeyPressed('t')) currentGraph = 4;
	if (ofGetKeyPressed('y')) currentGraph = 5;


	if (videoGrab){

		grabCam.update();
		if (grabCam.isFrameNew()){
			geoGraph.update(grabCam.getPixelsRef());
			scenes[currentGraph]->update();
		}

	}else{

		videos[currentVideo].update();
		geoGraph.update(videos[currentVideo].getPixelsRef());
		scenes[currentGraph]->update();
	}


}

void Trainer::fboReflesh(){

//	if (ofGetKeyPressed('v')){
//		maskRect[0].set(ofRandom(640), ofRandom(420), ofRandom(780), ofRandom(420));
//		maskRect[1].set(ofRandom(640), ofRandom(420), ofRandom(780), ofRandom(420));
//	}

	buffer.begin();

	ofClear(0, 0, 0);

	ofSetColor(200);

	for (int i = 0;i < 2;i++){
		if (videoGrab){
			grabCam.getTextureReference().bind();
		}else{
			videos[currentVideo].getTextureReference().bind();
		}

		glBegin(GL_TRIANGLE_STRIP);

		glTexCoord2d(maskRect[i].x, maskRect[i].y);
		glVertex2d(maskRect[i].x, maskRect[i].y);

		glTexCoord2d(maskRect[i].x+maskRect[i].width, maskRect[i].y);
		glVertex2d(maskRect[i].x+maskRect[i].width, maskRect[i].y);

		glTexCoord2d(maskRect[i].x, maskRect[i].y+maskRect[i].height);
		glVertex2d(maskRect[i].x, maskRect[i].y+maskRect[i].height);

		glTexCoord2d(maskRect[i].x+maskRect[i].width, maskRect[i].y+maskRect[i].height);
		glVertex2d(maskRect[i].x+maskRect[i].width, maskRect[i].y+maskRect[i].height);

		glEnd();

		if (videoGrab){
			grabCam.getTextureReference().unbind();
		}else{
			videos[currentVideo].getTextureReference().unbind();
		}

	}

	scenes[currentGraph]->draw();

	ofSetColor(255);
	for (int i = 0;i < buffer.getWidth();i+=200){
		for (int j = 0;j < buffer.getHeight();j+=200){
			ofPushMatrix();
			ofTranslate(i, j);
			ofLine(-5, 0, 5, 0);
			ofLine(0, -5, 0, 5);
			ofPopMatrix();
		}
	}

	buffer.end();
}

void Trainer::draw(int x,int y,int w,int h){
	ofSetColor(255);
	buffer.draw(x, y, w, h);

}

void Trainer::cutUp(){

	geoGraph.flow.resetFlow();
	videos[currentVideo].setPosition(ofRandom(cutRange_low,cutRange_high));
	geoGraph.update(videos[currentVideo].getPixelsRef());
	
}

void Trainer::resetFlow(){

	geoGraph.flow.resetFlow();
	geoGraph.update(videos[currentVideo].getPixelsRef());

}

void Trainer::addVideo(string file){
	videos.push_back(ofVideoPlayer());
	videos.back().loadMovie(file);
}

void Trainer::setBaseColor(ofFloatColor c){
	for (int i = 0;i < scenes.size();i++){
		scenes[i]->baseColor = c;
	}
}