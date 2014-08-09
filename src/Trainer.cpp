//
//  Trainer.cpp
//  cvGeoGraphics
//
//  Created by Ovis aries on 2014/07/25.
//
//

#include "Trainer.h"

void Trainer::setup(bool useCamera, int deviceId){

	geoGraph.setup();
	videoGrab = useCamera;

	//Video management========================
	currentVideo = 0;

	if (!videoGrab){
		addVideo("videos/Yuri.mov");
		addVideo("videos/Kei_pj.mov");
		addVideo("videos/Twin.mov");
		addVideo("tofu.mp4");

		for (int i = 0;i < videos.size();i++){
			videos[i].play();
			videos[i].setLoopState(OF_LOOP_NORMAL);
			videos[i].setVolume(0.0);
		}
	}

	//Scene management========================

	currentGraph = 0;
	scenes.push_back(new singleScene_Delaunay());
	scenes.push_back(new singleScene_CrossHatch());
	scenes.push_back(new singleScene_TileSquare());
	scenes.push_back(new singleScene_panel());
	scenes.push_back(new singleScene_particle());
//	scenes.push_back(new singleScene_trail());

	for (int i = 0;i < scenes.size();i++){
		scenes[i]->setup(&geoGraph);
	}

	ofEnableArbTex();
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

	bmGrab = false;

	if (videoGrab){
		if (bmGrab){
			blackMagicGrabber.setup(1280, 720, 30);
		}else{

			vector<ofVideoDevice> vd = grabCam.listDevices();
			for (int i = 0;i < vd.size();i++){
				cout << "ID " << i << ":" << vd[i].deviceName << endl;
			}

			grabCam.setDeviceID(deviceId);
			grabCam.initGrabber(1280,720);
		}
	}

	maskRect[0].set(0, 0, 1280, 720);
	maskRect[1].set(0, 0, 1280, 720);

	postGlitch.setup(&buffer);

	autoResetFlow = true;
	fxEnable = true;
	autoReset_step = ofRandom(5,15);
}

void Trainer::update(){

	if (autoResetFlow && (ofGetFrameNum() % autoReset_step == 0)){
		autoReset_step = ofRandom(10,50);
		resetFlow();
	}

	if (ofGetKeyPressed('1')) currentVideo = 0;
	if (ofGetKeyPressed('2')) currentVideo = 1;
	if (ofGetKeyPressed('3')) currentVideo = 2;

	if (ofGetKeyPressed('q')) currentGraph = 0;
	if (ofGetKeyPressed('w')) currentGraph = 1;
	if (ofGetKeyPressed('e')) currentGraph = 2;
	if (ofGetKeyPressed('r')) currentGraph = 3;
	if (ofGetKeyPressed('t')) currentGraph = 4;
//	if (ofGetKeyPressed('y')) currentGraph = 5;


	if (videoGrab){

		if (bmGrab){

			blackMagicGrabber.update();
			if (ofGetFrameNum() > 60)
				geoGraph.update(blackMagicGrabber.getColorPixels());

		}else{

			grabCam.update();
			if (grabCam.isFrameNew()){

				geoGraph.update(grabCam.getPixelsRef());
				scenes[currentGraph]->update();
				
			}

		}

	}else{

		videos[currentVideo].update();
		geoGraph.update(videos[currentVideo].getPixelsRef());
		scenes[currentGraph]->update();

	}

	scenes[currentGraph]->soundVolume = input_volume;

}

void Trainer::fboReflesh(){

//	if (ofGetKeyPressed('v')){
//		maskRect[0].set(0, 0, 1280, 720);
//	}
//
//	if (ofGetKeyPressed('m')){
//		for (int i = 0;i < MASK_NUM;i++){
//			maskRect[i].set(ofRandom(640), ofRandom(420),
//							ofRandom(1280), ofRandom(720));
//		}
//	}

	buffer.begin();

	ofClear(0, 0, 0);

	ofSetColor(200);

	for (int i = 0;i < MASK_NUM;i++){
		if (videoGrab){
			if (bmGrab){
				blackMagicGrabber.getYuvTexture().bind();
			}else{
				grabCam.getTextureReference().bind();
			}
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
			if (bmGrab){
				blackMagicGrabber.getYuvTexture().unbind();
			}else{
				grabCam.getTextureReference().unbind();
			}
		}else{
			videos[currentVideo].getTextureReference().unbind();
		}

	}

	if (fxEnable){
		scenes[currentGraph]->draw();

		int step = 150;

		ofSetColor(255);
		for (int i = 0;i < buffer.getWidth();i+=step){
			for (int j = 0;j < buffer.getHeight();j+=step){
				ofPushMatrix();

				ofTranslate(i + ((int)buffer.getWidth() % step) / 2,
							j + ((int)buffer.getHeight()% step) / 2);

				float scl = 5 + input_volume*15.0;
				ofLine(-scl, 0, scl, 0);
				ofLine(0, -scl, 0, scl);
				ofPopMatrix();
			}
		}

	}

	buffer.end();

	postGlitch.setFx(OFXPOSTGLITCH_CONVERGENCE	, ofGetKeyPressed('a'));
	postGlitch.setFx(OFXPOSTGLITCH_CUTSLIDER	, ofGetKeyPressed('a'));
	postGlitch.setFx(OFXPOSTGLITCH_GLOW			, ofGetKeyPressed('s'));
	postGlitch.setFx(OFXPOSTGLITCH_SHAKER		, ofGetKeyPressed('s'));
	postGlitch.setFx(OFXPOSTGLITCH_NOISE		, ofGetKeyPressed('d'));
	postGlitch.setFx(OFXPOSTGLITCH_SWELL		, ofGetKeyPressed('d'));
	postGlitch.setFx(OFXPOSTGLITCH_SHAKER		, ofGetKeyPressed('s'));
	
	postGlitch.generateFx();
}

void Trainer::draw(int x,int y,int w,int h){
	buffer.draw(x, y, w, h);

}

void Trainer::cutUp(){

	if (!videoGrab){
		videos[currentVideo].setPosition(ofRandom(cutRange_low,cutRange_high));
		geoGraph.flow.resetFlow();
		geoGraph.update(videos[currentVideo].getPixelsRef());
	}

}

void Trainer::resetFlow(){

	geoGraph.flow.resetFlow();
	if (videoGrab){
		geoGraph.update(grabCam.getPixelsRef());
	}else{
		geoGraph.update(videos[currentVideo].getPixelsRef());
	}

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