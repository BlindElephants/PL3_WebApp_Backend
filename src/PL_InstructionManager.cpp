//
//  PL_InstructionManager.cpp
//  PL3_WebApp_Backend
//
//  Created by Jeremy Stewart on 4/9/17.
//
//

#include "PL_InstructionManager.hpp"


PL_InstructionManager::PL_InstructionManager(shared_ptr<PL_GoalManager> _gm, const int &_myId, ofxLibwebsockets::Connection &_connection, vector<ofVec2f> &_objects)
:
gm(_gm),
objects(_objects),
myId(_myId),
connection(_connection)
{
    ib = make_shared<PL_IB_WAIT>(gm, myId, connection, objects);
}

void PL_InstructionManager::update() {
    ib->update();
    
    if(ib->checkIsFinished()) {
        pl_console::addLine("behavior finished");
        PL_InstructionBehaviorType nextType = ib->getFollowType();
        switch(nextType) {
            case PLIB_WAIT:
                ib = make_shared<PL_IB_WAIT>(gm, myId, connection, objects);
                pl_console::addLine("[" + ofToString(myId) + "]: PL_IB_WAIT created");
                break;
                
            case PLIB_A:
                ib = make_shared<PL_IB_A>(gm, myId, connection, objects);
                pl_console::addLine("[" + ofToString(myId) + "]: PL_IB_A created");
                break;
                
            case PLIB_B:
                ib = make_shared<PL_IB_B>(gm, myId, connection, objects);
                pl_console::addLine("[" + ofToString(myId) + "]: PL_IB_B created");
                break;
                
            case PLIB_C:
                ib = make_shared<PL_IB_C>(gm, myId, connection, objects);
                pl_console::addLine("[" + ofToString(myId) + "]: PL_IB_C created");
                break;
                
            case PLIB_D:
                ib = make_shared<PL_IB_D>(gm, myId, connection, objects);
                pl_console::addLine("[" + ofToString(myId) + "]: PL_IB_D created");
                break;
                
            case PLIB_E:
                ib = make_shared<PL_IB_E>(gm, myId, connection, objects);
                pl_console::addLine("[" + ofToString(myId) + "]: PL_IB_E created");
                break;
                
            case NUM_BEHAVIORTYPES:
                pl_console::addLine("[" + ofToString(myId) + "]: error creating new behavior type");
                break;
                
            default:
                pl_console::addLine("[" + ofToString(myId) + "]: error creating new behavior type");
                break;
        }
    }
}
