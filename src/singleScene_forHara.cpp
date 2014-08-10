//
//  singleScene_forHara.cpp
//  cvGeoGraphics
//
//  Created by Ovis aries on 2014/08/10.
//
//

#include "singleScene_forHara.h"

void singleScene_forHara::setup_virtual(){
	isFeatNew = false;
}

void singleScene_forHara::update_virtual(){

	//特徴点をgeoGraphから引っ張る
	feat = geoGraphPtr->flow.getFeatures();
	if (feat_b.size() == 0)	feat_b = feat;
	isFeatNew = true;

	velocity.clear();
	velocity.assign(feat.size(), ofVec3f(0,0,0));
	for (int i = 0;i < feat.size();i++){
		velocity[i] = feat[i] - feat_b[i];
	}

}

void singleScene_forHara::draw_virtual(){

	/*========  描画処理は基本的にここで行います ==============*/

	//アルファ合成でも良いとは思いますが、加算が綺麗かなー。
	ofEnableBlendMode(OF_BLENDMODE_ADD);

	//baseColorというメンバ変数に、基本の色が代入されるのでこれをコピーして使います。
	ofFloatColor c = baseColor;

	//サンプル：特徴点の速度を線で描画。i++で全部描画すると若干くどい時があるので、
	//i+=3とかで少し間引いてあげると良いかもです。
	for (int i = 0;i < feat.size();i+=3){

		//そのままだと1色になってしまうので、cの色相を少し遊んであげる
		c.setHue(baseColor.getHue() + ofNoise(i/35.5)/2.5);
		ofSetColor(c);

		ofPushMatrix();
		ofTranslate(feat[i]);

		float rect_scale = MIN(100, velocity[i].lengthSquared()) + 5;
		ofRect(0, 0, rect_scale, rect_scale);

		ofPopMatrix();

	}



	//速度を引っ張ってくるための処理
	if (isFeatNew){
		feat_b.clear();
		feat_b = feat;
		isFeatNew = false;
	}
}