#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxXmlSettings.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void updateNoise();
		void draw();

		ofEasyCam cam;
		vector<ofMesh> lattices;
		int latticesNum = 10;
		float zDistance = 400;

		ofxPanel gui;
	    ofParameter<bool> drawFaces, drawWireframes;
	    ofParameter<float> noiseAmp;
	    ofParameter<float> noiseFreq;
	    ofParameter<glm::vec2> noiseScale;
	    ofParameter<ofColor> colorNear;
	    ofParameter<ofColor> colorFar;

	    ofShader shader;
		
};
