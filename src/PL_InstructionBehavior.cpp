//
//  PL_InstructionBehavior.cpp
//  PL3_WebApp_Backend
//
//  Created by Jeremy Stewart on 4/9/17.
//
//

#include "PL_InstructionBehavior.hpp"

PL_InstructionBehavior::PL_InstructionBehavior(float _timeTillFirstInstruction, PL_InstructionBehaviorType _myType, shared_ptr<PL_GoalManager> _gm, const int &_myId, ofxLibwebsockets::Connection &_connection, vector<ofVec2f> &_objects)
:
myType(_myType),
isFinished(false),
timer(0.0f),
nextInstructionNow(false),
timeTillNextInstruction(_timeTillFirstInstruction),
gm(_gm),
myId(_myId),
connection(_connection),
objects(_objects)
{};

void PL_InstructionBehavior::tick() {
    timer += ofGetLastFrameTime();
    if(timer>=timeTillNextInstruction) {
        nextInstructionNow = true;
    }
}

void PL_InstructionBehavior::update() {
    tick();
    if(nextInstructionNow) {
        timer = 0.0;
        timeTillNextInstruction = getNextInstruction();
        nextInstructionNow=false;
    }
    if(gm->getGoals().size()==0) {isFinished=true;}
}

void PL_InstructionBehavior::sortObjectsGoals(vector<ofVec2f> tempObjects) {
    float d2=gm->getDeviceObjectSize();
    d2*=0.5;
    d2*=d2;
    
    if(gm->getCompletedGoals().size() && tempObjects.size()) {
        for(int i=0 ; i<gm->getCompletedGoals().size() ; i++ ) {
            for(int j=tempObjects.size()-1 ; j>=0 ; j-- ) {
                if(tempObjects[j].squareDistance(gm->getCompletedGoals()[i]->getPosition())<=d2) {
                    tempObjects.erase(tempObjects.begin()+j);
                }
            }
        }
    }
    
    if(gm->getGoals().size() && tempObjects.size()) {
        for(int i=gm->getGoals().size()-1; i>=0 ; i-- ) {
            for(int j=tempObjects.size()-1 ; j>=0 ; j-- ) {
                if(tempObjects[j].squareDistance(gm->getGoals()[i]->getPosition())<=d2) {
                    tempObjects.erase(tempObjects.begin()+j);
                    gm->getCompletedGoals().push_back(gm->getGoals()[i]);
                    gm->getGoals().erase(gm->getGoals().begin()+i);
                    break;
                }
            }
        }
    }
}

void PL_InstructionBehavior::sendAddInstr(ofVec2f _goalPosition, float _duration, float _delay) {
    Json::Value m;
//    ofVec2f _g = _goalPosition;
//    convertToScreenCoords(_goalPosition);
    m["address"] = "/instruction/add";
    m["args"].append(_goalPosition.x);
    m["args"].append(_goalPosition.y);
    m["args"].append(_duration);
    m["args"].append(_delay);
    connection.send(m.toStyledString());
    pl_console::addLine("[" + ofToString(myId) + "]: add instruction sent");
    
//    ofxOscMessage sm;
//    sm.setAddress("/instruction/add");
//    sm.addIntArg(myId);
//    sm.addFloatArg(_g.x);
//    sm.addFloatArg(_g.y);
//    sm.addFloatArg(_duration);
//    sm.addFloatArg(_delay);
//    toSoundRef.sendMessage(sm);
}

void PL_InstructionBehavior::sendRemoveInstr(ofVec2f _goalPosition, float _duration, float _delay) {
    Json::Value m;
//    ofVec2f _g = _goalPosition;
//    convertToScreenCoords(_goalPosition);
    
    m["address"] = "/instruction/remove";
    m["args"].append(_goalPosition.x);
    m["args"].append(_goalPosition.y);
    m["args"].append(_duration);
    m["args"].append(_delay);
    connection.send(m.toStyledString());
    pl_console::addLine("[" + ofToString(myId) + "]: remove instruction sent");
    
//    ofxOscMessage sm;
//    sm.setAddress("/instruction/remove");
//    sm.addIntArg(myId);
//    sm.addFloatArg(_g.x);
//    sm.addFloatArg(_g.y);
//    sm.addFloatArg(_duration);
//    sm.addFloatArg(_delay);
//    toSoundRef.sendMessage(sm);
}

void PL_InstructionBehavior::sendMoveInstr(ofVec2f _startPosition, ofVec2f _endPosition, float _duration, float _delay) {
    Json::Value m;
    ofVec2f _s = _startPosition;
    ofVec2f _e = _endPosition;
//    convertToScreenCoords(_startPosition);
//    convertToScreenCoords(_endPosition);
    
    m["address"] = "/instruction/move";
    m["args"].append(_startPosition.x);
    m["args"].append(_startPosition.y);
    m["args"].append(_endPosition.x);
    m["args"].append(_endPosition.y);
    m["args"].append(_duration);
    m["args"].append(_delay);
    connection.send(m.toStyledString());
    pl_console::addLine("[" + ofToString(myId) + "]: move instruction sent");
    
//    ofxOscMessage sm;
//    sm.setAddress("/instruction/move");
//    sm.addIntArg(myId);
//    sm.addFloatArg(_s.x);
//    sm.addFloatArg(_s.y);
//    sm.addFloatArg(_e.x);
//    sm.addFloatArg(_e.y);
//    sm.addFloatArg(_duration);
//    sm.addFloatArg(_delay);
//    toSoundRef.sendMessage(sm);
}
