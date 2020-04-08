#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0);
	ofSetFrameRate(60);
	ofSetSphereResolution(128);
	ofEnableAlphaBlending();
	float width = ofGetWidth();
	float height = ofGetHeight();
	int rowsColsVal = 60;
	// Create the mesh
	/*
	add indices:

	make triangles to form a grid -

	1 grid square   =>     2 triangles

	A-------B          A-------B        B
	|     / |          |     /        / |
	|   /   |    =>    |   /   +    /   |
	| /     |          | /        /     |
	C-------D          C        C-------D

	A - current point
	B - next grid column
	C - next grid row
	D - next grid row + col

	triangles, ordered clockwise:
	A,B,C... B,D,C

	*/
	for (int d = 0; d < latticesNum; d++) {
		ofMesh lattice;
		lattices.push_back(lattice);
		for (int c = 0; c < rowsColsVal; c++){
		    for (int r = 0; r < rowsColsVal; r++){
		        glm::vec3 pos;
		        // grid centered at 0,0,0
		        pos.x = ofMap(r, 0, rowsColsVal-1, -width * 0.5, width * 0.5);
		        pos.y = ofMap(c, 0, rowsColsVal-1, height * 0.5, -height * 0.5);
		        pos.z = ofMap(d, 0, latticesNum, -zDistance, zDistance);
		        // add the point to the mesh
		        lattices[d].addVertex(pos);
		        // add a color for the point
		        lattice.addColor(ofColor());
		        if (r > 0 && c > 0) {
		        	if ((r * rowsColsVal + c) % 4 == 0 ||
		        		r % 4 == 0) {
		        		int index = r * rowsColsVal + c;
			            // triangle 1
			            lattices[d].addIndex(index);
			            lattices[d].addIndex(index - 1);
			            lattices[d].addIndex(index - rowsColsVal);
			            // triangle 2
			            lattices[d].addIndex(index - 1);
			            lattices[d].addIndex((index - 1) - rowsColsVal);
			            lattices[d].addIndex(index - rowsColsVal);
		        	}
		        }
		    }
		}
	}
	// Setting up all the gui stuff
	gui.setup();
	gui.add( drawFaces.set("draw faces", true) );
    gui.add( drawWireframes.set("draw wires", false) );
    gui.add( noiseScale.set("noise scale", glm::vec2(.001), glm::vec2(0.), glm::vec2(.005)));
    gui.add( noiseFreq.set("frequency", 0.5, 0., 2.));
    gui.add( noiseAmp.set("amplitude", 40., 0., 100.));
    gui.add( colorNear.set("color near", ofColor::fuchsia, ofColor(0,0), ofColor(255,255,255,255)));
    gui.add( colorFar.set("color far", ofColor::navy, ofColor(0,0,0,0), ofColor(255,255,255,255)));

    // load the shader
    shader.load("shaders/shader");
}

//--------------------------------------------------------------
void ofApp::update(){
	updateNoise();
}

// --------------------------------
void ofApp::updateNoise(){
    float time = ofGetElapsedTimef();
    for (int j = 0; j < lattices.size(); j++) {
    	for (int i=0; i<lattices[j].getVertices().size(); i++){
	        // animate noise waves on vertex.z position
	        glm::vec3& vertex = lattices[j].getVertices()[i];
	        //  '&' - vertex is a 'reference' to the actual point in the mesh (not a copy)
	        //  calc a noise value from -1 to 1
	        float noise = ofSignedNoise (vertex.x * noiseScale.get().x,    // x pos
											vertex.y * noiseScale.get().y,    // y pos
											time * noiseFreq    // time (z) to animate
											);
	        //  change vertex z depth based on noise and amplitude setting
	        vertex.z = ofMap(j, 0, lattices.size(), -zDistance/2.0, zDistance/2.0) + (noise * noiseAmp);
	    }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
	cam.begin();
    ofEnableDepthTest();
    for (int i = 0; i < lattices.size(); i++) {
    	float depthPercent = ofMap(i, 0, lattices.size(), 0, 1, true);
    	ofColor lerpedColor = colorFar.get().getLerped(colorNear.get(), depthPercent);
    	// ofSetColor(lerpedColor);
    	// ofFill();
    	if (drawFaces){
    		glm::vec3 lerpedColorVec;
	    	lerpedColorVec.x = lerpedColor.r/255.0;
	    	lerpedColorVec.y = lerpedColor.g/255.0;
	    	lerpedColorVec.z = lerpedColor.b/255.0;
	    	shader.begin();
	    	shader.setUniform1f("u_offset", ofMap(i, 0, lattices.size(), -zDistance/2.0, zDistance/2.0));
	    	shader.setUniform1f("u_amplitude", noiseAmp);
	    	shader.setUniform2f("u_resolution", ofGetWidth(), ofGetHeight());
	    	shader.setUniform3f("u_materialColor", lerpedColorVec);
    		lattices[i].draw();
    		shader.end();
	    } else if (drawWireframes) {
	    	ofSetColor(lerpedColor);
	    	ofFill();
			lattices[i].drawWireframe();
	    }
    }
    ofSetColor(80, 190, 255);
    ofFill();
    ofSpherePrimitive sphere;
    sphere.setRadius(100);
	sphere.setPosition(100, 100, -50);
	sphere.draw();
    ofDisableDepthTest();
    cam.end();
    gui.draw();
}
