//
//  PL_IB_A.hpp
//  PL3_WebApp_Backend
//
//  Created by Jeremy Stewart on 4/9/17.
//
//

#ifndef PL_IB_A_hpp
#define PL_IB_A_hpp

#include "PL_InstructionBehavior.hpp"


class PL_IB_A : public PL_InstructionBehavior {
public:
    virtual float getNextInstruction();
    PL_IB_A(shared_ptr<PL_GoalManager> _gm, const int &_myId, ofxLibwebsockets::Connection &_connection, vector<ofVec2f> &_objects);
private:
    
};

#endif /* PL_IB_A_hpp */