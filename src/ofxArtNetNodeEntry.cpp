/*
 *  ofxArtNetNodeEntry.cpp
 *  artnetExample
 *
 *  Created by Tobias Ebsen on 9/27/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofxArtNetNodeEntry.h"
#include "artnet.h"

ofxArtNetNodeEntry::ofxArtNetNodeEntry(void* node_entry) {
	
	artnet_node_entry ne = (artnet_node_entry)node_entry;

	this->node_entry = malloc(sizeof(artnet_node_entry_t));
	memcpy(this->node_entry, node_entry, sizeof(artnet_node_entry_t));
	
	/*stringstream ssip;
	ssip << (int)ne->ip[0] << "." << (int)ne->ip[1] << "." << (int)ne->ip[2] << "." << (int)ne->ip[3];
	ip = ssip.str();
	
	subnet = ne->sub;
	
	shortName.assign((char*)ne->shortname);
	longName.assign((char*)ne->longname);
	
	nports = ne->numbports;
	memcpy(portTypes, ne->porttypes, sizeof(portTypes));
	memcpy(universeIn, ne->swin, sizeof(universeIn));
	memcpy(universeOut, ne->swout, sizeof(universeOut));
	
	stringstream ssmac;
	ssmac << setfill('0');
	for (int i=0; i<ARTNET_MAC_SIZE; i++) {
		if(i) ssmac << ":";
		ssmac << hex << setw(2) << (int)ne->mac[i];
	}
	mac = ssmac.str();*/
}
//-------------------------------------------------------------
ofxArtNetNodeEntry::~ofxArtNetNodeEntry() {
	free(node_entry);
}
//-------------------------------------------------------------
string ofxArtNetNodeEntry::getIp() {
	artnet_node_entry ne = (artnet_node_entry)node_entry;
	char ip[16];
	sprintf(ip, "%d.%d.%d.%d", ne->ip[0], ne->ip[1], ne->ip[2], ne->ip[3]);
	return ip;
}
//-------------------------------------------------------------
uint16 ofxArtNetNodeEntry::getSubnet() {
	artnet_node_entry ne = (artnet_node_entry)node_entry;
	return ne->sub;
}
//-------------------------------------------------------------
string ofxArtNetNodeEntry::getShortName() {
	artnet_node_entry ne = (artnet_node_entry)node_entry;
	return (char*)ne->shortname;
}
//-------------------------------------------------------------
string ofxArtNetNodeEntry::getLongName() {
	artnet_node_entry ne = (artnet_node_entry)node_entry;
	return (char*)ne->longname;
}
//-------------------------------------------------------------
uint16 ofxArtNetNodeEntry::getPortCount() {
	artnet_node_entry ne = (artnet_node_entry)node_entry;
	return ne->numbports;
}
//-------------------------------------------------------------
uint8 ofxArtNetNodeEntry::getPortType(int port) {
	artnet_node_entry ne = (artnet_node_entry)node_entry;
	return ne->porttypes[port];
}
//-------------------------------------------------------------
string ofxArtNetNodeEntry::getPortTypeName(int port) {
	artnet_node_entry ne = (artnet_node_entry)node_entry;
	switch (ne->porttypes[port] & 0x1F) {
		case 0: return "DMX";
		case 1: return "MIDI";
		case 2: return "AVAB";
		case 3: return "CMX";
		case 4: return "ADB";
		case 5: return "ARTNET";
	}
}
//-------------------------------------------------------------
bool ofxArtNetNodeEntry::isPortInput(int port) {
	artnet_node_entry ne = (artnet_node_entry)node_entry;
	return ne->porttypes[port] & 0x40;
}
//-------------------------------------------------------------
bool ofxArtNetNodeEntry::isPortOutput(int port) {
	artnet_node_entry ne = (artnet_node_entry)node_entry;
	return ne->porttypes[port] & 0x80;
}
//-------------------------------------------------------------
uint8 ofxArtNetNodeEntry::getUniverseInput(int port) {
	artnet_node_entry ne = (artnet_node_entry)node_entry;
	return ne->swin[port];
}
//-------------------------------------------------------------
uint8 ofxArtNetNodeEntry::getUniverseOutput(int port) {
	artnet_node_entry ne = (artnet_node_entry)node_entry;
	return ne->swout[port];
}
//-------------------------------------------------------------
string ofxArtNetNodeEntry::getMac() {
	artnet_node_entry ne = (artnet_node_entry)node_entry;
	char mac[18];
	sprintf(mac, "%02x:%02x:%02x:%02x:%02x:%02x", ne->mac[0], ne->mac[1], ne->mac[2], ne->mac[3], ne->mac[4], ne->mac[5]);
	return mac;
}
