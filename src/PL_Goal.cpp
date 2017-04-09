//
//  PL_Goal.cpp
//  PL3_WebApp_Backend
//
//  Created by Jeremy Stewart on 4/9/17.
//
//

#include "PL_Goal.hpp"

PL_Goal::PL_Goal(ofVec2f _position) :
position(_position)
{}

const ofVec2f &PL_Goal::getPosition() {return position;}
