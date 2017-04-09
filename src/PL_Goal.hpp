//
//  PL_Goal.hpp
//  PL3_WebApp_Backend
//
//  Created by Jeremy Stewart on 4/9/17.
//
//

#ifndef PL_Goal_hpp
#define PL_Goal_hpp

#include "ofMain.h"

class PL_Goal {
public:
    const ofVec2f &getPosition();
    PL_Goal(ofVec2f _position);
private:
    const ofVec2f position;
};

#endif /* PL_Goal_hpp */
