//
//  ClientUtilities.hpp
//  PL3_WebApp_Backend
//
//  Created by Jeremy Stewart on 4/9/17.
//
//

#ifndef ClientUtilities_hpp
#define ClientUtilities_hpp

#include "ofMain.h"

namespace ClientUtilities {
    ofVec2f normalizeCoords(ofVec2f position, ofVec2f &screenSize);
    ofVec2f normalToScreenCoords(ofVec2f position, ofVec2f &screenSize);
    ofVec2f offsetForScreen(ofVec2f position, ofVec2f &screenSize);
}



#endif /* ClientUtilities_hpp */
