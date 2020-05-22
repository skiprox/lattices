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
		void keyReleased(int key);

		ofEasyCam cam;
		vector<ofMesh> lattices;
		vector<ofMesh> latticesVer;
		int gapSize = 4;
		int latticesNum = 10;
		float zDistance = 400;

		bool showGui = true;

		ofxPanel gui;
	    ofParameter<bool> drawFaces, drawWireframes;
	    ofParameter<float> noiseAmp;
	    ofParameter<float> noiseFreq;
	    ofParameter<glm::vec3> noiseScale;
	    ofParameter<ofColor> colorNear;
	    ofParameter<ofColor> colorFar;

	    ofShader lightingShader;
	    ofShader gradientShader;
		
};
