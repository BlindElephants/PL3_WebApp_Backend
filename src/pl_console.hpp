//
//  pl_console.hpp
//  PL2_FLOOR
//
//  Created by EMPAC Video on 2/7/17.
//
//

#ifndef pl_console_hpp
#define pl_console_hpp

#include "ofMain.h"
#include "ofxOsc.h"

class pl_console {
public:
    static pl_console& instance();
    static void addLine(string l);
    static void draw();
    static void setSender(string addrPiA, string addrPiB, string addrPiC, int port);
    static void setFbo(float x, float y, float w, float h);
    
    static void addPerformerLine(int performerIndex, string l) ;
    static void addConnectedUser(string userName);
    static void addDisconnectedUser(string userName);
    static void updateAudioCue(int performerIndex, string l);
private:
    pl_console();
    pl_console(pl_console const&) {};
    pl_console& operator=(pl_console const&) {return *this;}
    ~pl_console() {};
    ofTrueTypeFont font;
    vector <string> lines;
    ofVec2f fboDrawPosition;
    ofFbo fbo;
    
    ofxOscSender senderPiA, senderPiB, senderPiC;
};

#endif /* pl_console_hpp */
