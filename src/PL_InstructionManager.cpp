//
//  PL_InstructionManager.cpp
//  PL3_WebApp_Backend
//
//  Created by Jeremy Stewart on 4/9/17.
//
//

#include "PL_InstructionManager.hpp"
#include "PL_SoundSender.hpp"
#include "PL_PerformerServer.hpp"
#include "PL_AuditoryMessageBuilder.hpp"
#include "ofApp.h"
#include "PL_VisServer.hpp"

PL_InstructionManager::PL_InstructionManager(shared_ptr<PL_GoalManager> _gm, string &_userName, const int &_myId, ofxLibwebsockets::Connection &_connection, vector<ofVec2f> &_objects, ofVec2f &_ClientScreenDimensions)
:
gm(_gm),
objects(_objects),
myId(_myId),
userName(_userName),
connection(_connection),
ClientScreenDimensions(_ClientScreenDimensions),
numInstructionBehaviorsCompleted(0)
{
    ib = make_shared<PL_IB_WAIT>(gm, userName, myId, connection, objects, ClientScreenDimensions);
}

void PL_InstructionManager::update() {
    ib->update();
    if(ib->checkIsFinished()) {
        ofxOscMessage m;
        m.setAddress("/instruction/behavior/complete");
        m.addIntArg(myId);
        m.addStringArg(userName);
        m.addIntArg(ib->getType());
        m.addIntArg(ib->getFollowType());
        PL_SoundSender::sendMessage(m);
        PL_VisServer::sendMessage(m);
        if(ofApp::runPiece) {
            PL_PerformerServer::sendVibeMessage(userName, ofRandom(2), ofRandom(5)+1, 0.0f, ofRandom(50, 500), ofRandom(0, 100), 50);
            
            numInstructionBehaviorsCompleted++;
            if(numInstructionBehaviorsCompleted>4) {
                ofxOscMessage m;
                vector<int> msgInts;
                string a=PL_AuditoryMessageBuilder::getAuditoryMessage(msgInts);
                if(PL_PerformerServer::sendAuditoryMessage(userName, ofRandom(2), a, msgInts)) {
                    numInstructionBehaviorsCompleted=0;
                }
            }
        }
        
        pl_console::addLine("behavior finished");
        PL_InstructionBehaviorType nextType = ib->getFollowType();
        switch(nextType) {
            case PLIB_WAIT:
                ib = make_shared<PL_IB_WAIT>(gm, userName, myId, connection, objects, ClientScreenDimensions);
                pl_console::addLine("[" + ofToString(myId) + "]: PL_IB_WAIT created");
                break;
                
            case PLIB_A:
                ib = make_shared<PL_IB_A>(gm, userName, myId, connection, objects, ClientScreenDimensions);
                pl_console::addLine("[" + userName + "]: PL_IB_A created");
                break;
                
            case PLIB_B:
                ib = make_shared<PL_IB_B>(gm, userName, myId, connection, objects, ClientScreenDimensions);
                pl_console::addLine("[" + userName + "]: PL_IB_B created");
                break;
                
            case PLIB_C:
                ib = make_shared<PL_IB_C>(gm, userName, myId, connection, objects, ClientScreenDimensions);
                pl_console::addLine("[" + userName + "]: PL_IB_C created");
                break;
                
            case PLIB_D:
                ib = make_shared<PL_IB_D>(gm, userName, myId, connection, objects, ClientScreenDimensions);
                pl_console::addLine("[" + userName + "]: PL_IB_D created");
                break;
                
            case PLIB_E:
                ib = make_shared<PL_IB_E>(gm, userName, myId, connection, objects, ClientScreenDimensions);
                pl_console::addLine("[" + userName + "]: PL_IB_E created");
                break;
                
            case NUM_BEHAVIORTYPES:
                pl_console::addLine("[" + userName + "]: error creating new behavior type");
                break;
                
            default:
                pl_console::addLine("[" + userName + "]: error creating new behavior type");
                break;
        }
    }
}
