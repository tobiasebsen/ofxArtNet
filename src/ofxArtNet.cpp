/*
 *  ofxArtNet.cpp
 *  artnetExample
 *
 *  Created by Tobias Ebsen on 9/25/12.
 *  Copyright 2012 Tobias Ebsen. All rights reserved.
 *
 */

#include "ofxArtNet.h"
#include "artnet.h"

////////////////////////////////////////////////////////////
vector<ofxArtNetInterface>& ofxArtNet::getInterfaces() {
	
	interfaces.clear();
	
	ofxArtNetInterface::getInterfaces(interfaces);
	
	return interfaces;
}
////////////////////////////////////////////////////////////
void ofxArtNet::init(string ip, bool verbose) {
	
	node = artnet_new((ip.empty() ? NULL : ip.c_str()), verbose);
	if (node == NULL) {
		ofLog(OF_LOG_ERROR, artnet_strerror());
		return;
	}
	artnet_set_handler(node, ARTNET_REPLY_HANDLER, ofxArtNet::reply_handler, this);
	artnet_set_dmx_handler(node, ofxArtNet::dmx_handler, this);
}
////////////////////////////////////////////////////////////
void ofxArtNet::setOEM(uint8 high, uint8 low) {
	artnet_setoem(node, high, low);
}
////////////////////////////////////////////////////////////
void ofxArtNet::setNodeType(artnetNodeType nodeType) {
	artnet_set_node_type(node, (artnet_node_type)nodeType);
}
////////////////////////////////////////////////////////////
void ofxArtNet::setShortName(string shortname) {
	artnet_set_short_name(node, shortname.c_str());
}
////////////////////////////////////////////////////////////
void ofxArtNet::setLongName(string longname) {
	artnet_set_long_name(node, longname.c_str());
}
////////////////////////////////////////////////////////////
void ofxArtNet::setSubNet(int subnet) {
	artnet_set_subnet_addr(node, subnet);
}
////////////////////////////////////////////////////////////
void ofxArtNet::setBroadcastLimit(int bcastlimit) {
	artnet_set_bcast_limit(node, bcastlimit);
}
////////////////////////////////////////////////////////////
void ofxArtNet::setPortType(int port, artnetPortIO io, artnetPortData data) {
	artnet_set_port_type(node, port, (artnet_port_settings_t)io, (artnet_port_data_code)data);
}
////////////////////////////////////////////////////////////
void ofxArtNet::setPortAddress(int port, artnetPortType type, uint8_t address) {
	artnet_set_port_addr(node, port, (artnet_port_dir_t)type, address);
}
////////////////////////////////////////////////////////////
void ofxArtNet::start() {
	if (artnet_start(node) != ARTNET_EOK) {
		ofLog(OF_LOG_ERROR, artnet_strerror());
		return;
	}
	startThread(true, false);
}
////////////////////////////////////////////////////////////
void ofxArtNet::stop() {
	stopThread();
	artnet_stop(node);
}
////////////////////////////////////////////////////////////
void ofxArtNet::close() {
	artnet_destroy(node);
	node = NULL;
}
////////////////////////////////////////////////////////////
void ofxArtNet::sendPoll(string ip) {
	for (int i=0; i<nodes.size(); i++)
		delete nodes[i];
	nodes.clear();
	artnet_send_poll(node, ip.empty() ? NULL : ip.c_str(), ARTNET_TTM_DEFAULT);
}
////////////////////////////////////////////////////////////
void ofxArtNet::sendDmx(int port, void* data, int size) {
	artnet_send_dmx(node, port, size, (uint8_t*)data);
}
////////////////////////////////////////////////////////////
void ofxArtNet::sendDmx(ofxArtNetDmxData& dmx) {
	sendDmx(dmx.port, dmx.data, dmx.len);
}
////////////////////////////////////////////////////////////
void ofxArtNet::sendDmxRaw(int universe, void* data, int size) {
	artnet_raw_send_dmx(node, universe, size, (uint8_t*)data);
}
////////////////////////////////////////////////////////////
void ofxArtNet::threadedFunction() {
	
	fd_set rd_fds;
	struct timeval tv;
	int max;
	
	int artnet_sd = artnet_get_sd(node);
	
	while (isThreadRunning()) {

		FD_ZERO(&rd_fds);
		FD_SET(0, &rd_fds);
		FD_SET(artnet_sd, &rd_fds);
		
		max = artnet_sd;

		tv.tv_sec = 1;
		tv.tv_usec = 0;
		
		int n = select(max+1, &rd_fds, NULL, NULL, &tv);
		if (n > 0) {
			if (FD_ISSET(artnet_sd , &rd_fds))
	    		artnet_read(node, 0);
		}
	}
}
////////////////////////////////////////////////////////////
int ofxArtNet::reply_handler(artnet_node node, void *pp, void *d) {

	ofxArtNet* t = (ofxArtNet*)d;
	artnet_node_list nl = artnet_get_nl(node);
	int nodes_found = t->nodes.size();

	int n = artnet_nl_get_length(nl);
	if(n == nodes_found)
		return 0;
	
	artnet_node_entry ne = NULL;
	if(nodes_found == 0)
		ne = artnet_nl_first(nl);
	else
		ne = artnet_nl_next(nl);

	ofxArtNetNodeEntry* entry = new ofxArtNetNodeEntry(ne);
	t->nodes.push_back(entry);
	ofNotifyEvent(t->pollReply, entry, t);
	
	return 0;
}
////////////////////////////////////////////////////////////
int ofxArtNet::dmx_handler(artnet_node n, int port, void *d) {
	
	ofxArtNet* t = (ofxArtNet*)d;
	
	int len;
	uint8_t* data = artnet_read_dmx(n, port, &len);
	ofxArtNetDmxData dmx(data, len);
	dmx.port = port;
	ofNotifyEvent(t->dmxData, dmx, t);
}
