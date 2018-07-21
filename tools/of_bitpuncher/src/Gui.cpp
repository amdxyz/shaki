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

#include "Gui.h"

Gui::Gui()
{  
}

Gui::~Gui()
{
}

void Gui::setup()
{
    
    positionDrawText = ofVec2f(40, 40);
    positionTemplatesText = ofVec2f(ofGetWidth()-240, 40);
    positionFramesText = ofVec2f(40, 540);
    positionUploadText = ofVec2f(40, 780);
    
	positionTemplatesButtonAdd = ofVec2f(positionTemplatesText.x, positionTemplatesText.y+800);
	positionTemplatesButtonUp = ofVec2f(positionTemplatesText.x, positionTemplatesText.y+40);
	positionTemplatesButtonDown = ofVec2f(positionTemplatesText.x, positionTemplatesText.y+720);
	positionFramesButton = ofVec2f(positionFramesText.x, positionFramesText.y+20);
	positionSPF = positionFramesText + ofVec2f(860, 130);
    positionResetButton = positionUploadText + ofVec2f(20, 20);
	positionUploadButton = positionResetButton + ofVec2f(120, 0);
	positionExportButton = positionUploadButton + ofVec2f(520, 0);
    
    fontIcons.load("Fonts/icons_2.ttf", 24);
    fontIconsSmall.load("Fonts/icons_2.ttf", 16);
    fontLabel.load("Fonts/adventpro-extralight.ttf", 20);
    fontLabelSmall.load("Fonts/adventpro-extralight.ttf", 16);
    fontText.load("Fonts/adventpro-extralight.ttf", 22);
        
	ofJson styleBtnAdd = {      {"type", "fullsize"},
                                {"width","40"},
                                {"height","40"},
								{"background-color", "rgba(0,0,0,0.0)"},
                                {"border-color","rgba(0,0,0,0.0)"}
                            };
	ofJson styleBtnAddTemp = {  {"type", "fullsize"},
                                {"width","200"},
                                {"height","40"},
								{"background-color", "rgba(0,0,0,0)"},
                                {"border-color","rgba(255,255,255,0.8)"}
                            };       
	ofJson styleBtnRemove = {   {"type", "fullsize"},
                                {"width","40"},
                                {"height","40"},
								{"background-color", "rgba(0,0,0,0.0)"},
                                {"border-color","rgba(0,0,0,0.0)"}
                            };
                                
	ofJson styleBtnUpDown = {   {"type", "fullsize"},
                                {"width","180"},
                                {"height","30"},
								{"background-color", "rgba(220,220,220,0.0)"},
                                {"border-color","rgba(255,255,255,0.0)"}
                            };
                                
	ofJson styleBtnUpload = {   {"type", "fullsize"},
                                {"width","500"},
                                {"height","50"},
                                {"text-align", "center"},
								{"background-color", "rgba(0,0,0,0)"}
                            };
	ofJson styleBtnReset = {    {"type", "fullsize"},
                                {"width","100"},
                                {"height","50"},
                                {"text-align", "center"},
								{"background-color", "rgba(0,0,0,0)"}
                            };
	ofJson styleSPF = {   {"type", "fullsize"},
                                {"width","35"},
                                {"height","25"},
                                {"text-align", "center"},
								{"background-color", "rgba(240,240,240,0)"},
                            }; 

    ofJson stylePanelDefault = {{"background-color", "rgba(0,0,0,0.0)"}};
    ofJson stylePanelSmall = {{"width","40"},{"background-color", "rgba(0,0,0,0.0)"}};
    	
	panelFrameEdit = gui.addPanel("frameedit", stylePanelSmall);
	panelFrameEdit->setShowHeader(false);
	panelFrameEdit->add(btnAddFrame.set(""), styleBtnAdd);
	panelFrameEdit->add(btnRemoveFrame.set(""), styleBtnRemove);
	panelFrameEdit->setPosition(positionFramesButton.x, positionFramesButton.y);
    
	panelAddTemplate = gui.addPanel("templateedit", stylePanelDefault);
	panelAddTemplate->setShowHeader(false);
	panelAddTemplate->add(btnAddTemplate.set(""), styleBtnAddTemp);										
    panelAddTemplate->setPosition(positionTemplatesButtonAdd.x, positionTemplatesButtonAdd.y);
	
	panelUpload = gui.addPanel("uploadpanel",stylePanelDefault);
	panelUpload->add(btnUpload.set(""), styleBtnUpload);
    panelUpload->setShowHeader(false);												
    panelUpload->setPosition(positionUploadButton.x, positionUploadButton.y);
	
	panelTemplatesUp = gui.addPanel("tempUp", stylePanelDefault);
	panelTemplatesUp->setShowHeader(false);
	panelTemplatesUp->add(btnTemplatesUp.set(""), styleBtnUpDown);
	panelTemplatesUp->setPosition(positionTemplatesButtonUp.x, positionTemplatesButtonUp.y);
	
	panelTemplatesDown = gui.addPanel("tempDown",stylePanelDefault);
	panelTemplatesDown->setShowHeader(false);
	panelTemplatesDown->add(btnTemplatesDown.set(""), styleBtnUpDown);
	panelTemplatesDown->setPosition(positionTemplatesButtonDown.x, positionTemplatesButtonDown.y);
	
    panelReset = gui.addPanel("resetpanel", stylePanelSmall);
	panelReset->setShowHeader(false);
	panelReset->add(btnReset.set(""), styleBtnReset);
	panelReset->setPosition(positionResetButton.x, positionResetButton.y);
    
    panelExport = gui.addPanel("exportpanel", stylePanelSmall);
	panelExport->setShowHeader(false);
	panelExport->add(btnExport.set(""), styleBtnReset);
	panelExport->setPosition(positionExportButton.x, positionExportButton.y);
    
    panelSPF = gui.addPanel("spf panel", stylePanelSmall);
	panelSPF->setShowHeader(false);
	panelSPF->add(btnSPFUp.set(""), styleSPF);
	panelSPF->add(btnSPFDown.set(""), styleSPF);
	panelSPF->setPosition(positionSPF.x, positionSPF.y);
    
    colorUpload = ofColor(189, 211, 88);
    colorDelete = ofColor(242, 100, 25);
    colorExport = ofColor(230, 230, 230);
}

void Gui::draw()
{
    
    /* descriptions */
    ofSetColor(50);
    fontText.drawString("Edit: Draw your symbols, icons, letters ...", positionDrawText.x, positionDrawText.y);
    fontText.drawString("Templates", positionTemplatesText.x+20, positionTemplatesText.y);
    fontText.drawString("Add more frames for longer words or moving images", positionFramesText.x, positionFramesText.y);
    fontText.drawString("Click on upload to personalize your Shaki", positionUploadText.x, positionUploadText.y);
    
	ofSetColor(0,50);
	/*template separation line*/
	ofDrawLine(positionTemplatesText.x-30, 0, positionTemplatesText.x-30, ofGetHeight());
	
    /*draw gui icons and button labels manually, since positioning and spacing through ofxGuiExtended addon is not working properly*/
    ofSetColor(220);
    fontIcons.drawString("n", positionTemplatesButtonUp.x+79, positionTemplatesButtonUp.y+28);
    fontIcons.drawString("o", positionTemplatesButtonDown.x+79, positionTemplatesButtonDown.y+28);
    
    ofSetColor(180);
    fontIconsSmall.drawString("n", positionSPF.x+13, positionSPF.y+23);
    fontIconsSmall.drawString("o", positionSPF.x+13, positionSPF.y+58);
    
    ofSetColor(40);
    fontIcons.drawString("m", positionFramesButton.x+16, positionFramesButton.y+34);
    ofSetColor(colorDelete);
    fontIcons.drawString("a", positionFramesButton.x+13, positionFramesButton.y+81);
    
    
    ofSetColor(colorDelete);
    ofDrawRectangle(positionResetButton+ofVec2f(4,4), 100, 50);
    ofSetColor(colorUpload);
    ofDrawRectangle(positionUploadButton+ofVec2f(4,4), 500, 50);
    ofSetColor(colorExport);
    ofDrawRectangle(positionExportButton+ofVec2f(4,4), 100, 50);
    ofSetColor(40,10);
    ofDrawRectangle(positionTemplatesButtonAdd+ofVec2f(4,4), 200, 40);
    ofSetColor(40);
    fontLabel.drawString("Upload", positionUploadButton.x+202, positionUploadButton.y+38);
    fontLabel.drawString("Reset", positionResetButton.x+22, positionResetButton.y+38);
    fontLabel.drawString("Export", positionExportButton.x+22, positionExportButton.y+38);
    fontLabel.drawString("Add Template", positionTemplatesButtonAdd.x+26, positionTemplatesButtonAdd.y+33);
    
    fontLabelSmall.drawString("Shakes per frame:   " + ofToString(*spf_ptr), positionSPF.x-200, positionSPF.y+38);    
}