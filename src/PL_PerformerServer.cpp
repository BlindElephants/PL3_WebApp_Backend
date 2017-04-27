//
//  PL_PerformerServer.cpp
//  PL3_WebApp_Backend
//
//  Created by Jeremy Stewart on 4/25/17.
//
//

#include "PL_PerformerServer.hpp"
#include "pl_console.hpp"
#include "PL_VisServer.hpp"

PL_PerformerServer &PL_PerformerServer::instance() {
    static PL_PerformerServer p;
    return p;
}

void PL_PerformerServer::setup(string serverAddr, int serverPort) {
    instance().sender.setup(serverAddr, serverPort);
}

void PL_PerformerServer::sendMessage(ofxOscMessage m) {
    instance().sender.sendMessage(m);
}

void PL_PerformerServer::tick() {
    instance().msgTimerA+=ofGetLastFrameTime();
    (instance().msgTimerA>=instance().msgTimerLock) ? instance().canSendMsgA=true : instance().canSendMsgA=false;

    instance().msgTimerB+=ofGetLastFrameTime();
    (instance().msgTimerB>=instance().msgTimerLock) ? instance().canSendMsgB=true : instance().canSendMsgB=false;
    
    instance().auditoryMsgTimerA+=ofGetLastFrameTime();
    (instance().auditoryMsgTimerA>=instance().auditoryMsgTimerLock) ? instance().canSendAuditoryMsgA=true : instance().canSendAuditoryMsgA=false;
    
    instance().auditoryMsgTimerB+=ofGetLastFrameTime();
    (instance().auditoryMsgTimerB>=instance().auditoryMsgTimerLock) ? instance().canSendAuditoryMsgB=true : instance().canSendAuditoryMsgB=false;
}

void PL_PerformerServer::setMsgTimerLock(float _msgTimerLock) {
    instance().msgTimerLock=_msgTimerLock;
}

bool PL_PerformerServer::sendVibeMessage(string clientName, int performerIndex, int motorNumber, float delay, float atk, float sus, float rel) {
    if(performerIndex==0) {
        if(instance().canSendMsgA) {
            ofxOscMessage m;
            m.setAddress("/vibe/msg");
            m.addStringArg(clientName);
            m.addIntArg(performerIndex);
            m.addIntArg(motorNumber);
            m.addIntArg(delay);
            m.addIntArg(atk);
            m.addIntArg(sus);
            m.addIntArg(rel);
            instance().sender.sendMessage(m);
            PL_VisServer::sendMessage(m);
            instance().msgTimerA=0.0f;
            string s = "["+clientName+"] : tactile message sent to performer [" + ofToString(performerIndex) + "] motor: [" + ofToString(motorNumber) + "] // " + ofToString(delay) + " " + ofToString(atk) + " " + ofToString(sus) + " " + ofToString(rel);
            pl_console::addLine(s);
            pl_console::addPerformerLine(performerIndex, s);
            return true;
        }
    } else if(performerIndex==1) {
        if(instance().canSendMsgB) {
            ofxOscMessage m;
            m.setAddress("/vibe/msg");
            m.addStringArg(clientName);
            m.addIntArg(performerIndex);
            m.addIntArg(motorNumber);
            m.addIntArg(delay);
            m.addIntArg(atk);
            m.addIntArg(sus);
            m.addIntArg(rel);
            instance().sender.sendMessage(m);
            PL_VisServer::sendMessage(m);

            instance().msgTimerB=0.0f;
            
            string s = "["+clientName+"] : tactile message sent to performer [" + ofToString(performerIndex) + "] motor: [" + ofToString(motorNumber) + "] // " + ofToString(delay) + " " + ofToString(atk) + " " + ofToString(sus) + " " + ofToString(rel);
            pl_console::addLine(s);
            pl_console::addPerformerLine(performerIndex, s);
            return true;
        }
    }
    return false;
}

bool PL_PerformerServer::sendAuditoryMessage(string clientName, int performerIndex, string auditoryMessage, vector<int> &msgInts) {
    if(performerIndex==0) {
        if(instance().canSendAuditoryMsgA) {
            ofxOscMessage m;
            m.setAddress("/auditory/msg");
            m.addStringArg(clientName);
            m.addIntArg(performerIndex);
            
            if(msgInts.size()) {
                for(int i=0; i<msgInts.size(); i++ ) {
                    m.addIntArg(msgInts[i]);
                    if(msgInts[i]==25 && msgInts.size()>i+1) {
                        ofxOscMessage vm;
                        vm.setAddress("/auditory/msg");
                        vm.addIntArg(msgInts[i+1]);
                        PL_VisServer::sendMessage(vm);
                    }
                }
            } else {
                cout << "[ERROR] no message ints in PL_PerformerServer::sendAuditoryMessage()";
            }
            instance().sender.sendMessage(m);
            
//            PL_VisServer::sendMessage(m);

            instance().auditoryMsgTimerA=0.0f;
            
            string s="["+clientName+"] : auditory message sent to performer [" + ofToString(performerIndex) + "] " + auditoryMessage;
            string a="["+clientName+"] : [" + ofToString(performerIndex)+"] " + auditoryMessage;
            pl_console::addLine(s);
            pl_console::addPerformerLine(performerIndex, s);
            pl_console::updateAudioCue(performerIndex, a);
            return true;
        }
    } else if(performerIndex==1) {
        if(instance().canSendAuditoryMsgB) {
            ofxOscMessage m;
            m.setAddress("/auditory/msg");
            m.addStringArg(clientName);
            m.addIntArg(performerIndex);
            if(msgInts.size()) {
                for(int i=0; i<msgInts.size(); i++ ) {
                    m.addIntArg(msgInts[i]);
                    if(msgInts[i]==25 && msgInts.size()>i+1) {
                        ofxOscMessage vm;
                        vm.setAddress("/auditory/msg");
                        vm.addIntArg(msgInts[i+1]);
                        PL_VisServer::sendMessage(vm);
                    }
                }
            } else {
                cout << "[ERROR] no message ints in PL_PerformerServer::sendAuditoryMessage()";
            }
            instance().sender.sendMessage(m);
            PL_VisServer::sendMessage(m);

            instance().auditoryMsgTimerB=0.0f;
            
            string s="["+clientName+"] : auditory message sent to performer [" + ofToString(performerIndex) + "] " + auditoryMessage;
            string a="["+clientName+"] : [" + ofToString(performerIndex)+"] " + auditoryMessage;

            pl_console::addLine(s);
            pl_console::addPerformerLine(performerIndex, s);
            pl_console::updateAudioCue(performerIndex, a);
            return true;
        }
    }
    return false;
}
