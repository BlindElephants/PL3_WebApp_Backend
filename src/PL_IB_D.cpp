//
//  PL_IB_D.cpp
//  PL3_WebApp_Backend
//
//  Created by Jeremy Stewart on 4/13/17.
//
//

#include "PL_IB_D.hpp"
#include "ClientUtilities.hpp"

PL_IB_D::PL_IB_D(shared_ptr<PL_GoalManager> _gm, string &_userName, const int &_myId, ofxLibwebsockets::Connection &_connection, vector<ofVec2f> &_objects)
:
PL_InstructionBehavior(ofRandom(5, 20), PL_InstructionBehaviorType::PLIB_D, _gm, _userName, _myId, _connection, _objects)
{
    gm->makeNewGoalSet_Random(1);
}

float PL_IB_D::getNextInstruction() {
    timeTillNextInstruction=0.0;
    vector<ofVec2f> tempObjects;
    if(objects.size()>3) {
        for(int i = 0 ; i < objects.size() ; i ++ ) {
            tempObjects.push_back(ClientUtilities::normalToScreenCoords(objects[i], gm->getDeviceScreenDimensions()));
        }
        for(int i=0; i<tempObjects.size() ; i ++ ) {
            float du=ofRandom(5.0, 12.5);
            float de=ofRandom(0.0, 6.0);
            if((du+de)>timeTillNextInstruction) timeTillNextInstruction=du+de;
            sendRemoveInstr(tempObjects[i], du, de);
        }
    } else {
        isFinished=true;
    }
    timeTillNextInstruction+=ofRandom(2.0, 5.5);
    return timeTillNextInstruction;
}
