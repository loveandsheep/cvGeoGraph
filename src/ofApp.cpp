#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	int deviceId;
	bool isUsingCamera;

	output_pos			= ofPoint(1920, 0);//外部出力の座標
	output_resolution	= ofVec2f(800, 600);//外部出力の画面解像度

	isUsingCamera		= true;	//カメラ使用フラグ(Falseの時はビデオなのでサマソニはtrue)
	deviceId			= 0;	//デバイスIDの設定(要確認！)
	//デバイスIDについて:
	//Macに接続されているカメラの数だけIDが割り振られます。
	//基本的には内蔵カメラが0で、1以降にBlackmagicのレコーダーが来ますが、映像ソースの種類によって適切なIDが変わります。
	//listDevicesで実行時コンソールに表示されるので、そこから適切なIDをピックアップしてdeviceIDに代入してください…！

	ofSetFrameRate(30);
	trainer.setup(isUsingCamera, deviceId);
	uiSetup();

}

//--------------------------------------------------------------
void ofApp::update(){

	//特徴点の更新処理
	trainer.update();

	//オーディオ入力処理
	scaledVol = ofMap(smoothedVol, 0.0, 0.17, 0.0, 1.0, true) * volume_gain;
	trainer.input_volume = scaledVol;

	//映像のマスター明度更新
	if (bVisible)	video_transp = MIN(1.0, video_transp + 0.02);
	else			video_transp = MAX(0.0, video_transp - 0.02);

	//GUIの時間表記更新
	((ofxUILabel *)(canvas.getWidget("cTime")))->setLabel("Time :"+ofToString(ofGetHours(),2,'0')+":"+
														  ofToString(ofGetMinutes(),2,'0')+":"+
														  ofToString(ofGetSeconds(),2,'0'));

	//ビデオ位置更新
	if (!trainer.videoGrab)
		video_pos = trainer.videos[trainer.currentVideo].getPosition();
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(0, 0, 0);
	ofSetColor(255);

	//映像の更新
	trainer.fboReflesh();

	ofSetColor(video_transp * 255.0);

	//手元側の描画
	trainer.draw( 240, 0, 1280, 720);

	//外部出力の描画
	trainer.draw(output_pos.x, output_pos.y + (output_resolution.y - output_resolution.x / 16.0 * 9.0) / 2.0,
				 output_resolution.x, output_resolution.x / 16.0 * 9.0);

	//オーディオ入力のモニタリング
	ofSetColor(255);
	ofRect(0, ofGetHeight() - scaledVol * 200, 10, scaledVol * 200);
}

void ofApp::guiEvent(ofxUIEventArgs &e){

	if (e.getName() == "Hue" ||
		e.getName() == "Sat" ||
		e.getName() == "Bri"){
		ofFloatColor c;
		c.setHsb(baseCol_hue, baseCol_sat, baseCol_bri);
		trainer.setBaseColor(c);
	}

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
//	if (key == ' ') trainer.cutUp();
	if (key == 'n') trainer.resetFlow();
	if (key == 'f') ofToggleFullscreen();
}

void ofApp::uiSetup(){

	canvas.setup();
	canvas.setPosition(30, 30);
	canvas.setName("Trainer");
	canvas.addLabel("cTime", "00:00:00",OFX_UI_FONT_LARGE);
	canvas.addSpacer();
	canvas.addLabel("Colors",OFX_UI_FONT_LARGE);
	canvas.addSlider("Hue", 0.0, 1.0, &baseCol_hue);
	canvas.addSlider("Sat", 0.0, 1.0, &baseCol_sat);
	canvas.addSlider("Bri", 0.0, 1.0, &baseCol_bri);
//	canvas.addSpacer();
//	canvas.addLabel("VideoManage",OFX_UI_FONT_LARGE);
//	canvas.addRangeSlider("cutRange", 0.0, 1.0, &trainer.cutRange_low, &trainer.cutRange_high);
//	canvas.addSlider("videoPos", 0.0, 1.0, &video_pos);

	canvas.addSpacer();
	canvas.addLabel("System",OFX_UI_FONT_LARGE);
	canvas.addSlider("Sound_Gain", 0.0, 5.0, &volume_gain);
	canvas.addToggle("fxEnable", &trainer.fxEnable);
	canvas.addSpacer();
	canvas.addLabel("Output",OFX_UI_FONT_LARGE);
	canvas.addSlider("brightness", 0.0, 1.0, &video_transp);
	canvas.addToggle("visible", &bVisible);
//	canvas.add2DPad("Offset", ofxUIVec3f(-100.0,100.0,0.0), ofxUIVec3f(-100.0,100.0,0.0), &mainOffset, 200, 200);
	canvas.addFPS();
	canvas.autoSizeToFitWidgets();

	ofAddListener(canvas.newGUIEvent, this, &ofApp::guiEvent);

	baseCol_hue = 0.43;
	baseCol_sat = 0.28;
	baseCol_bri = 1.0;
	trainer.cutRange_low  = 0.0;
	trainer.cutRange_high = 1.0;
	mainOffset.set(0.0,0.0,0.0);

	bVisible = true;
	video_transp = 1.0;

	ofFloatColor c;
	c.setHsb(baseCol_hue, baseCol_sat, baseCol_bri);
	trainer.setBaseColor(c);


	//オーディオ設定========================
	int bufferSize = 256;

	left.assign(bufferSize, 0.0);
	right.assign(bufferSize, 0.0);
	volHistory.assign(400, 0.0);

	bufferCounter	= 0;
	drawCounter		= 0;
	smoothedVol     = 0.0;
	scaledVol		= 0.0;

	soundStream.setup(this, 0, 2, 44100, bufferSize, 4);
	volume_gain = 1.0;
	//オーディオ設定========================
}

void ofApp::audioIn(float *input, int bufferSize, int nChannels){
	float curVol = 0.0;

	// samples are "interleaved"
	int numCounted = 0;

	//lets go through each sample and calculate the root mean square which is a rough way to calculate volume
	for (int i = 0; i < bufferSize; i++){
		left[i]		= input[i*2]*0.5;
		right[i]	= input[i*2+1]*0.5;

		curVol += left[i] * left[i];
		curVol += right[i] * right[i];
		numCounted+=2;
	}

	//this is how we get the mean of rms :)
	curVol /= (float)numCounted;

	// this is how we get the root of rms :)
	curVol = sqrt( curVol );

	smoothedVol *= 0.93;
	smoothedVol += 0.07 * curVol;

	bufferCounter++;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
