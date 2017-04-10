//
//  PL_SoundSender.cpp
//  PL3_WebApp_Backend
//
//  Created by Jeremy Stewart on 4/10/17.
//
//

#include "PL_SoundSender.hpp"

PL_SoundSender &PL_SoundSender::instance() {
    static PL_SoundSender s;
    return s;
}

void PL_SoundSender::setup(string serverAddr, int serverPort) {instance().sender.setup(serverAddr, serverPort);}
void PL_SoundSender::sendMessage(ofxOscMessage m) {instance().sender.sendMessage(m);}
