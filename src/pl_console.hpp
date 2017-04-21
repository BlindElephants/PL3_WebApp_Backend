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
    static void setSender(string addr, int port);
    static void setFbo(float x, float y, float w, float h);
private:
    pl_console();
    pl_console(pl_console const&) {};
    pl_console& operator=(pl_console const&) {return *this;}
    ~pl_console() {};
    ofTrueTypeFont font;
    vector <string> lines;
    ofVec2f fboDrawPosition;
    ofFbo fbo;
    
    ofxOscSender sender;
};

#endif /* pl_console_hpp */
