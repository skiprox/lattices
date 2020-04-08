#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	ofSetLogLevel(OF_LOG_VERBOSE);

	ofGLWindowSettings settings;
	// This needs to be greater than 3,2
    settings.setGLVersion(3,2); /// < select your GL Version here
    ofCreateWindow(settings);

	ofRunApp( new ofApp());

}
