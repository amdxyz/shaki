/* ***********************************************************************
    of_bitpuncher
    Copyright (C) 2018 Enrico Steinfeld <est@amdx.de>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
* ***********************************************************************/

#ifndef GUI_H
#define GUI_H

#include "ofMain.h"
#include "ofxGuiExtended.h"

class Gui{
public:
    Gui();
    ~Gui();
    
    void setup();
    void draw();
    
	ofxGui gui;
	
	ofParameter <void> btnTemplatesUp;
	ofParameter <void> btnTemplatesDown;
	ofParameter <void> btnAddFrame;
	ofParameter <void> btnRemoveFrame;
	ofParameter <void> btnAddTemplate;
	ofParameter <void> btnUpload;
    ofParameter <void> btnReset;
    ofParameter <void> btnExport;
    ofParameter <void> btnSPFUp;    //shakes per frame
    ofParameter <void> btnSPFDown;
	
	ofVec2f positionDrawText;
	ofVec2f positionTemplatesText;
	ofVec2f positionFramesText;
	ofVec2f positionUploadText;
	ofVec2f positionTemplatesButtonAdd;
	ofVec2f positionTemplatesButtonUp;
	ofVec2f positionTemplatesButtonDown;
	ofVec2f positionFramesButton;
	ofVec2f positionUploadButton;
	ofVec2f positionResetButton;
    ofVec2f positionExportButton;
    ofVec2f positionSPF;
    
    int *spf_ptr;
    
private:
	ofxGuiPanel *panelFrameEdit;
	ofxGuiPanel *panelAddTemplate;
	ofxGuiPanel *panelUpload;
    ofxGuiPanel *panelReset;
    ofxGuiPanel *panelExport;
    ofxGuiPanel *panelSPF;
	
	ofxGuiPanel *panelTemplatesUp;
	ofxGuiPanel *panelTemplatesDown;
    
	ofTrueTypeFont fontIcons;
	ofTrueTypeFont fontIconsSmall;
	ofTrueTypeFont fontText;
	ofTrueTypeFont fontLabel;
	ofTrueTypeFont fontLabelSmall;
    
    ofColor colorDelete;
    ofColor colorUpload;
    ofColor colorExport;

};

#endif