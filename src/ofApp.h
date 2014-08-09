#pragma once

#include "ofMain.h"
#include "ofxUI.h"
#include "Trainer.h"

class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();

	void uiSetup();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	void guiEvent(ofxUIEventArgs& e);

	ofVideoPlayer vid;
	Trainer trainer;

	ofxUICanvas canvas;

	float baseCol_hue;
	float baseCol_sat;
	float baseCol_bri;

	float video_pos;
	float video_transp;
	bool  bVisible;


	//Audio=====================
	void audioIn(float * input, int bufferSize, int nChannels);

	vector <float> left;
	vector <float> right;
	vector <float> volHistory;

	int 	bufferCounter;
	int 	drawCounter;

	float smoothedVol;
	float scaledVol;
	float volume_gain;

	ofSoundStream soundStream;
	ofRectangle mainOut;

	ofxUIVec3f mainOffset;
	
	ofPoint output_pos;
	ofVec3f output_resolution;
	float	output_width;

};
