#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    sp.loadSound("sound.mp3");
    sp.play();
    
	fftSmoothed = new float[8192];
	for (int i = 0; i < 8192; i++){
		fftSmoothed[i] = 0;
	}
	nBandsToGet = 128;
    ofSetFrameRate(60);
    file.open(ofToDataPath("soundData.text"), ofFile::WriteOnly);
    ofBuffer buff;
    buff = "";
    file.writeFromBuffer(buff);
    file.close();
}

//--------------------------------------------------------------
void testApp::update(){
    
	ofSoundUpdate();
    
    string str = "";
    str += ofToString(sp.getPositionMS()) + ", " + ofToString(ofGetFrameNum()) + ", ";
    float* val = ofSoundGetSpectrum(nBandsToGet);
	for (int i = 0;i < nBandsToGet; i++){
		fftSmoothed[i] *= 0.96f;
		if (fftSmoothed[i] < val[i]) fftSmoothed[i] = val[i];
        str += ofToString(val[i]) + ((i == nBandsToGet - 1) ? "\n" : ", ");
	}
    
    
    file.open(ofToDataPath("soundData.text"), ofFile::Append);
    ofBuffer buff;
    buff = str;
    file.writeFromBuffer(buff);
    file.close();
}

//--------------------------------------------------------------
void testApp::draw(){
	float width = (float)(5 * 128) / nBandsToGet;
	for (int i = 0;i < nBandsToGet; i++){
		ofRect(5 + i*width,ofGetHeight()-100,width,-(fftSmoothed[i] * 200));
	}
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
