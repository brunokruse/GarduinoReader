#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofSetVerticalSync(true);
	
	bSendSerialMessage = false;
	ofBackground(255);	
	ofSetLogLevel(OF_LOG_VERBOSE);
	
	font.loadFont("DIN.otf", 20);
	
    // list of all serial devices connected to the machine (HAL 9000)
	serial.listDevices();
	vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
	
	// this should be set to whatever com port your serial device is connected to.
	// (ie, COM4 on a pc, /dev/tty.... on linux, /dev/tty... on a mac)
	// arduino users check in arduino app....		
	
    //serial.setup(0, 9600); //open the first device (not used in this example)
    //serial.setup("COM4"); // windows example
	serial.setup("/dev/tty.usbserial-A9003VLw",9600); // mac osx example
	//serial.setup("/dev/ttyUSB0", 9600); //linux example
	
	nTimesRead = 0;
	nBytesRead = 0;
	readTime = 0;
	memset(bytesReadString, 0, 4);
}

//--------------------------------------------------------------
void testApp::update(){
	
	if (bSendSerialMessage){
		
    // (1) write the letter "a" to serial:
    serial.writeByte('a');
    
    // (2) read
    // now we try to read 3 bytes
    // since we might not get them all the time 3 - but sometimes 0, 6, or something else,
    // we will try to read three bytes, as much as we can
    // otherwise, we may have a "lag" if we don't read fast enough
    // or just read three every time. now, we will be sure to 
    // read as much as we can in groups of three...
    
    nTimesRead = 0;
    nBytesRead = 0;
    int nRead  = 0;  // a temp variable to keep count per read
    
    unsigned char bytesReturned[11];
    
    memset(bytesReadString, 0, 12);
    memset(bytesReturned, 0, 11);
    
    while( (nRead = serial.readBytes( bytesReturned, 11)) > 0){
        nTimesRead++;	
        nBytesRead = nRead;
    };
    
    memcpy(bytesReadString, bytesReturned, 11);
    
    bSendSerialMessage = false;
    readTime = ofGetElapsedTimef();

	}
}

//--------------------------------------------------------------
void testApp::draw(){
    
    
	//if (nBytesRead > 0 && ((ofGetElapsedTimef() - readTime) < 0.5f)){
		ofSetColor(0);
	//} else {
	//	ofSetColor(220);
	//}
    
    
	string msg;

    
    msg += "click to test values \n \n";
	msg += "read: " + ofToString(bytesReadString) + "\n";
    
    font.drawString(msg, 50, 100);
    
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
	
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){ 
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	bSendSerialMessage = true;
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
	
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
	
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 
	
}

/* NOTES
 
 You can use punctuation or you can use a call-and-response or handshaking method. Use whichever makes the most sense to you.
 
 
 resources:
 openFrameworks: openframeworks.cc
 nature of code: http://www.shiffman.net/teaching/nature/
 itp physcomp: http://itp.nyu.edu/physcomp/Tutorials/Tutorials
 
 
*/
