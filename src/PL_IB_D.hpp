//
//  PL_IB_D.hpp
//  PL3_WebApp_Backend
//
//  Created by Jeremy Stewart on 4/13/17.
//
//

#ifndef PL_IB_D_hpp
#define PL_IB_D_hpp

#include "PL_InstructionBehavior.hpp"

class PL_IB_D : public PL_InstructionBehavior {
public:
    virtual float getNextInstruction();
    PL_IB_D(shared_ptr<PL_GoalManager> _gm, string &_userName, const int &_myId, ofxLibwebsockets::Connection &_connection, vector<ofVec2f> &_objects, ofVec2f &_ClientScreenDimensions);
private:
};

#endif /* PL_IB_D_hpp */
