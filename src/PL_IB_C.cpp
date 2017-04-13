//
//  PL_IB_C.cpp
//  PL3_WebApp_Backend
//
//  Created by Jeremy Stewart on 4/13/17.
//
//

#include "PL_IB_C.hpp"
#include "ClientUtilities.hpp"

PL_IB_C::PL_IB_C(shared_ptr<PL_GoalManager> _gm, const int &_myId, ofxLibwebsockets::Connection &_connection, vector<ofVec2f> &_objects)
:
PL_InstructionBehavior(ofRandom(5, 20), PL_InstructionBehaviorType::PLIB_C, _gm, _myId, _connection, _objects)
{
    gm->makeNewGoalSet_Random(1);
}

float PL_IB_C::getNextInstruction() {
    timeTillNextInstruction=0.0;
    vector<ofVec2f> tempObjects;
    
    if(objects.size()) {
        for(int i = 0 ; i < objects.size() ; i ++ ) {
            tempObjects.push_back(ClientUtilities::normalToScreenCoords(objects[i], gm->getDeviceScreenDimensions()));
        }
        int numMessages = ofRandom(2,10);
        if(numMessages>tempObjects.size()) numMessages=tempObjects.size();
        
        for(int i=0 ; i<numMessages ; i++ ) {
            float du = ofRandom(2.0, 5.0);
            float de = ofRandom(3.0, 7.0);
            if((du+de)>timeTillNextInstruction) timeTillNextInstruction=du+de;
            sendRemoveInstr(tempObjects[i], du, de);
        }
    } else {
        isFinished=true;
    }
    timeTillNextInstruction+=ofRandom(2.0, 4.0);
    return timeTillNextInstruction;
}
