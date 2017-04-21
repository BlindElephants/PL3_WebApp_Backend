//
//  PL_IB_WAIT.cpp
//  PL3_WebApp_Backend
//
//  Created by Jeremy Stewart on 4/10/17.
//
//

#include "PL_IB_WAIT.hpp"


PL_IB_WAIT::PL_IB_WAIT(shared_ptr<PL_GoalManager> _gm, string &_userName, const int &_myId, ofxLibwebsockets::Connection &_connection, vector<ofVec2f> &_objects)
:
PL_InstructionBehavior(2.5f, PL_InstructionBehaviorType::PLIB_WAIT, _gm, _userName, _myId, _connection, _objects)
{
}

void PL_IB_WAIT::update() {
    tick();
    if(nextInstructionNow) {
        timer = 0.0f;
        timeTillNextInstruction = getNextInstruction();
        nextInstructionNow=false;
        Json::Value md;
        md["address"] = "/get/user";
        connection.send(md.toStyledString());
        cout << "request for user info sent" << endl;
    }
}

float PL_IB_WAIT::getNextInstruction() {
    float mLength = gm->getDeviceScreenDimensions().length();
    cout << mLength << endl;
    if(mLength>0.0f) {
        isFinished=true;
    } else {
        isFinished=false;
    }
    return 2.5f;
}
