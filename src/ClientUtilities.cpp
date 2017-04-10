//
//  ClientUtilities.cpp
//  PL3_WebApp_Backend
//
//  Created by Jeremy Stewart on 4/9/17.
//
//

#include "ClientUtilities.hpp"

ofVec2f ClientUtilities::normalizeCoords(ofVec2f position, ofVec2f &screenSize) {
    position += (screenSize*0.5);
    position /= screenSize;
    return position;
}

ofVec2f ClientUtilities::normalToScreenCoords(ofVec2f position, ofVec2f &screenSize) {
    position *= screenSize;
    position -= (screenSize*0.5);
    return position;
}

ofVec2f ClientUtilities::offsetForScreen(ofVec2f position, ofVec2f &screenSize) {
    position -= (screenSize*0.5);
    return position;
}
