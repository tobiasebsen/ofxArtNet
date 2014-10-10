/*
 *  ofxArtNetDmxData.h
 *  artnetExample
 *
 *  Created by Tobias Ebsen on 9/29/12.
 *  Copyright 2012 Tobias Ebsen. All rights reserved.
 *
 */

#pragma once

#include "ofMain.h"

class ofxArtNetDmxData {
public:
	
	ofxArtNetDmxData(int len = 512);
	ofxArtNetDmxData(uint8_t* data, int len);
	~ofxArtNetDmxData();
	
	void allocate(int len);
	void destroy();
	void set(uint8_t val);
	
	uint8_t* data;
	int len;
	int port;
};