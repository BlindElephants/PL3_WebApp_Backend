//
//  PL_IB_E.cpp
//  PL3_WebApp_Backend
//
//  Created by Jeremy Stewart on 4/13/17.
//
//

#include "PL_IB_E.hpp"
#include "ClientUtilities.hpp"

PL_IB_E::PL_IB_E(shared_ptr<PL_GoalManager> _gm, string &_userName, const int &_myId, ofxLibwebsockets::Connection &_connection, vector<ofVec2f> &_objects)
:
PL_InstructionBehavior(ofRandom(5, 20), PL_InstructionBehaviorType::PLIB_E, _gm, _userName, _myId, _connection, _objects)
{
    gm->makeNewGoalSet_Random(ofRandom(4, 12));
}

float PL_IB_E::getNextInstruction() {
    timeTillNextInstruction=0.0;
    vector<ofVec2f> tempObjects;
    if(objects.size()) {
        for(int i = 0 ; i < objects.size() ; i ++ ) {
            tempObjects.push_back(ClientUtilities::normalToScreenCoords(objects[i], gm->getDeviceScreenDimensions()));
        }
    }
    sortObjectsGoals(tempObjects);
    if(gm->getGoals().size()) {
        for(int i=0 ; i<gm->getGoals().size() ; i++ ) {
            float du=ofRandom(1.5, 10.0);
            float de=ofRandom(0.0, 7.0);
            if((du+de)>timeTillNextInstruction) timeTillNextInstruction=du+de;
            sendAddInstr(gm->getGoals()[i]->getPosition(), du, de);
        }
    }
    timeTillNextInstruction+=ofRandom(4.0f, 10.0f);
    return timeTillNextInstruction;
}
