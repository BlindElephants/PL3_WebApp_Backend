#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main(){
    ofGLFWWindowSettings s;
    s.setGLVersion(4, 1);
    s.windowMode = OF_FULLSCREEN;
    ofCreateWindow(s);
	ofRunApp(new ofApp());
}
