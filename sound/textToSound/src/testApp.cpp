#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetFrameRate(30);
    sdr.open("soundData.text");
}

//--------------------------------------------------------------
void testApp::update(){
    //float ms = ofGetElapsedTimeMillis();
    sdr.nextMS(1000.f / 30 * ofGetFrameNum());
}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofPushStyle();
    for (int i = 0; i < 30; i ++) {
        ofSetColor((i % 10 == 0) ? ofColor(128, 0, 0) : ofColor(255,255,255));
        ofLine(0, ofGetHeight() - 100 - 10 * i, ofGetWidth(), ofGetHeight() - 100 - 10 * i);
    }
    ofPopStyle();
    
    float width = (float)(5 * 128) / (sdr.data.size() - 2);
    for (int i = 2; i < sdr.data.size(); i ++) {
		ofRect(5 + (i - 2) * width, ofGetHeight()-100, width, -(sdr.data[i] * 200));
    }
    v.save();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
