/*
 *  ofxArtNet.h
 *  artnetExample
 *
 *  Created by Tobias Ebsen on 9/25/12.
 *  Copyright 2012 Tobias Ebsen. All rights reserved.
 *
 */

#pragma once

#include "ofMain.h"
#include "ofxArtNetNodeEntry.h"
#include "ofxArtNetInterface.h"
#include "ofxArtNetDmxData.h"

typedef void* artnet_node;

enum artnetNodeType {
	ARTNET_TYPE_SERVER,      /**< An ArtNet server (transmitts DMX data) */
	ARTNET_TYPE_NODE,    /**< An ArtNet node   (dmx reciever) */
	ARTNET_TYPE_MEDIA,    /**< A Media Server */
	ARTNET_TYPE_ROUTE,    /**< No Effect currently */
	ARTNET_TYPE_BACKUP,    /**< No Effect currently */
	ARTNET_TYPE_RAW      /**< Raw Node - used for diagnostics */
};

enum artnetPortIO {
	ARTNET_PORT_ENABLE_INPUT = 0x40,  /**< Enables the input for this port */
	ARTNET_PORT_ENABLE_OUTPUT = 0x80  /**< Enables the output for this port */
};

enum artnetPortData {
	ARTNET_DATA_DMX = 0x00,    /**< Data is DMX-512 */
	ARTNET_DATA_MIDI = 0x01,  /**< Data is MIDI */
	ARTNET_DATA_AVAB = 0x02,  /**< Data is Avab */
	ARTNET_DATA_CMX = 0x03,    /**< Data is Colortran CMX */
	ARTNET_DATA_ADB = 0x04,    /**< Data is ABD 62.5 */
	ARTNET_DATA_ARTNET = 0x05  /**< Data is ArtNet */
};

enum artnetPortType {
	ARTNET_PORT_INPUT = 1,    /**< The input port */
	ARTNET_PORT_OUTPUT,      /**< The output port */
};

class ofxArtNet : private ofThread {
public:
	
	vector<ofxArtNetInterface>& getInterfaces();
	
	void init(string ip = "", bool verbose = false);

	void setOEM(uint8 high, uint8 low);

	void setNodeType(artnetNodeType nodeType);
	void setShortName(string shortName);
	void setLongName(string longName);
	
	void setPortType(int port, artnetPortIO io, artnetPortData data);
	void setPortAddress(int port, artnetPortType portType, uint8_t address);
	void setPortSubnet(int port);
	
	void start();
	void stop();
	void close();
	
	void sendPoll(string ip = "");
	void sendDmx(int port, void* data, int size);
	void sendDmx(ofxArtNetDmxData& dmx);
	void sendDmxRaw(int universe, void* data, int size);
	
	ofEvent<ofxArtNetNodeEntry> pollReply;
	ofEvent<ofxArtNetDmxData> dmxData;

private:

	void threadedFunction();

	int static reply_handler(artnet_node n, void *pp, void *d);
	int static dmx_handler(artnet_node n, int port, void *d);

	artnet_node node;
	vector<ofxArtNetNodeEntry> nodes;
	vector<ofxArtNetInterface> interfaces;
};