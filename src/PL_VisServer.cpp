//
//  PL_VisServer.cpp
//  PL3_WebApp_Backend
//
//  Created by Jeremy Stewart on 4/26/17.
//
//

#include "PL_VisServer.hpp"

PL_VisServer &PL_VisServer::instance() {
    static PL_VisServer v;
    return v;
}

void PL_VisServer::setup(string serverAddr, int serverPort) {instance().sender.setup(serverAddr, serverPort);}
void PL_VisServer::sendMessage(ofxOscMessage m) {instance().sender.sendMessage(m);}
