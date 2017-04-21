//
//  PL_IB_A.cpp
//  PL3_WebApp_Backend
//
//  Created by Jeremy Stewart on 4/9/17.
//
//

#include "PL_IB_A.hpp"
#include "ClientUtilities.hpp"

PL_IB_A::PL_IB_A(shared_ptr<PL_GoalManager> _gm, string &_userName, const int &_myId, ofxLibwebsockets::Connection &_connection, vector<ofVec2f> &_objects)
:
PL_InstructionBehavior(ofRandom(5, 20), PL_InstructionBehaviorType::PLIB_A, _gm, _userName, _myId, _connection, _objects)
{
    gm->makeNewGoalSet_Random(5);
}

float PL_IB_A::getNextInstruction() {
    timeTillNextInstruction=0.0;
    
    vector<ofVec2f> tempObjects;
    
    if(objects.size()) {
        for(int i = 0 ; i < objects.size() ; i ++ ) {
            tempObjects.push_back(ClientUtilities::normalToScreenCoords(objects[i], gm->getDeviceScreenDimensions()));
        }
    }
    
    sortObjectsGoals(tempObjects);
    if(gm->getGoals().size()) {
        if(tempObjects.size()) {
            float du=ofRandom(3.0, 7.0);
            float de=ofRandom(3.0, 15.0);
            if((du+de)>timeTillNextInstruction) timeTillNextInstruction=du+de;
            sendMoveInstr(tempObjects[ofRandom(tempObjects.size())], gm->getGoals()[ofRandom(gm->getGoals().size())]->getPosition(), du, de);
        } else {
            float du=ofRandom(3.0, 7.0);
            float de=ofRandom(3.0, 15.0);
            if((du+de)>timeTillNextInstruction) timeTillNextInstruction=du+de;
            sendAddInstr(gm->getGoals()[ofRandom(gm->getGoals().size())]->getPosition(), du, de);
        }
    } else if(tempObjects.size()) {
        float du=ofRandom(3.0, 7.0);
        float de=ofRandom(3.0, 15.0);
        if((du+de)>timeTillNextInstruction) timeTillNextInstruction=du+de;

        sendRemoveInstr(tempObjects[tempObjects.size()], du, de);
    }
    return timeTillNextInstruction;
}
