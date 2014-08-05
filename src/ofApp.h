#pragma once

#include "ofMain.h"
#include "ofxUI.h"
#include "Trainer.h"

class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();

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
};
