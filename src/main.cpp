#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main(){
    ofGLFWWindowSettings s;
    s.setGLVersion(4, 1);
    s.windowMode = OF_WINDOW;
    ofCreateWindow(s);
	ofRunApp(new ofApp());
}
