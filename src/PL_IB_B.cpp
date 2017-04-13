//
//  PL_IB_B.cpp
//  PL3_WebApp_Backend
//
//  Created by Jeremy Stewart on 4/13/17.
//
//

#include "PL_IB_B.hpp"
#include "ClientUtilities.hpp"

PL_IB_B::PL_IB_B(shared_ptr<PL_GoalManager> _gm, const int &_myId, ofxLibwebsockets::Connection &_connection, vector<ofVec2f> &_objects)
:
PL_InstructionBehavior(ofRandom(5, 20), PL_InstructionBehaviorType::PLIB_B, _gm, _myId, _connection, _objects)
{
    gm->makeNewGoalSet_Random(5);
}

float PL_IB_B::getNextInstruction() {
    timeTillNextInstruction=0.0;
    vector<ofVec2f> tempObjects;
    if(objects.size()) {
        for(int i = 0 ; i < objects.size() ; i ++ ) {
            tempObjects.push_back(ClientUtilities::normalToScreenCoords(objects[i], gm->getDeviceScreenDimensions()));
        }
    }
    sortObjectsGoals(tempObjects);
    int numMessages = ofRandom(1, 5);
    if(gm->getGoals().size()<numMessages) {numMessages=gm->getGoals().size();}
    
    for(int i = 0 ; i < numMessages ; i ++ ) {
        float du = ofRandom(3.0, 7.0);
        float de = ofRandom(3.0, 15.0);
        if((du+de)>timeTillNextInstruction) timeTillNextInstruction=du+de;
        sendAddInstr(gm->getGoals()[i]->getPosition(), du, de);
    }
    return timeTillNextInstruction;
}
