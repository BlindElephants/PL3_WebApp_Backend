//
//  PL_SoundSender.hpp
//  PL3_WebApp_Backend
//
//  Created by Jeremy Stewart on 4/10/17.
//
//

#ifndef PL_SoundSender_hpp
#define PL_SoundSender_hpp

#include "ofMain.h"
#include "ofxOsc.h"

class PL_SoundSender {
public:
    static PL_SoundSender &instance();
    static void setup(string serverAddr, int serverPort);
    static void sendMessage(ofxOscMessage m);
    
private:
    PL_SoundSender() {};
    PL_SoundSender(PL_SoundSender const&) {};
    PL_SoundSender& operator=(PL_SoundSender const&) {return *this;}
    ~PL_SoundSender() {};
    
    ofxOscSender sender;
};

#endif /* PL_SoundSender_hpp */
