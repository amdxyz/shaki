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

#include "ofApp.h"

void ofApp::setup()
{
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
    
    /* set the callbacks of the buttons*/
    gui.setup();
    gui.btnTemplatesDown.addListener(this, &ofApp::onBtnTemplatesDown);
	gui.btnAddFrame.addListener(this, &ofApp::onBtnAddFrame);
	gui.btnRemoveFrame.addListener(this, &ofApp::onBtnRemoveFrame);
	gui.btnAddTemplate.addListener(this, &ofApp::onBtnAddTemplate);
	gui.btnUpload.addListener(this, &ofApp::onBtnUpload);
	gui.btnTemplatesUp.addListener(this, &ofApp::onBtnTemplatesUp);														
	gui.btnReset.addListener(this, &ofApp::onBtnReset);
	gui.btnExport.addListener(this, &ofApp::onBtnExport);
    gui.btnSPFUp.addListener(this, &ofApp::onBtnSPFUp);
    gui.btnSPFDown.addListener(this, &ofApp::onBtnSPFDown);
    
    /* load templates */
	templates.load();
	templates.setPosition(gui.positionTemplatesText + ofVec2f(0, 100));

    //load shaky photo
    imgShaki.load("shaki_final_back.png");
	
    //load first template if existing
    if (templates.sequences.size() ) {
    	setActiveSequence(&templates.sequences[0]);
    }
    
    //load matrices for letters/numbers drawn through key input
    loadLetters();
    
    /* set spf (shakes per frame) and pass the reference to the gui */
    spf = 5;
    gui.spf_ptr = &spf;
    
    /*animated preview*/
    p_speed = 0.025;
    p_radius1 = 580;
    p_radius2 = 780;
    p_angleArc = 0.3;
    p_fadeout = 0.90;
    p_currentFrame = 0;
    p_alpha.assign(8,false);
    p_shakeCounter = 0;
    
    /* set the default directory of the firmware */
    pathToFirmware = ofFilePath::getAbsolutePath(ofFilePath::getCurrentExePath());  //get the path of the current executed app
    pathToFirmware = ofSplitString(pathToFirmware, "tools")[0] + "firmware";
}

void ofApp::update()
{
}

void ofApp::draw()
{
	ofBackground(240);
    
	ofSetColor(255, 200);
	sequence.drawCurrentFrame();
	sequence.drawFramesPreview();
	
	templates.drawGallery();
    
    /*shaki photo*/
    ofSetColor(255);
    ofPushMatrix();
    ofTranslate(860, 170);
    ofRotateDeg(20);
    imgShaki.draw(0, 0, imgShaki.getWidth()*0.1, imgShaki.getHeight()*0.1);
	ofPopMatrix();
    
    /* animated preview*/
    ofPushMatrix();
    ofTranslate(610, 900);
    ofRotateDeg(200);
    drawAnimatedPreview();
    ofPopMatrix();
    
    gui.draw();    
}

void ofApp::drawAnimatedPreview()
{
    if ( p_direction ) {
        p_angle += p_speed;
        if ( p_angle > p_angleArc ) {
            p_angle = p_angleArc;
            p_direction = false;
            p_shakeCounter++;
            if ( p_shakeCounter == spf ) {
                p_shakeCounter = 0;
                p_currentFrame = (p_currentFrame+1)%sequence.frames.size();
            }
        }
    } else {
        p_angle -= p_speed;
        if ( p_angle < 0 ) {
            p_angle = 0;
            p_direction = true;
        }
    }
    
    for ( int i=0 ; i<8 ; ++i ) {
        p_alpha[i] *= p_fadeout;
        for ( int j=0 ; j<8 ; ++j ) {
            float a = ofMap(i, 0, 8, 0, p_angleArc);
            float r = ofMap(j, 0, 8, p_radius1, p_radius2);
            bool ison = sequence.frames[p_currentFrame].isPixelOn(7-i, 7-j);
            if ( abs(a-p_angle) < 0.02 ) {
                if ( ison ) {
                    p_alpha[i] = 255;
                }
            }
            float x = sin(a) * r;
            float y = cos(a) * r;
            
            int iter = 6;
            for ( int k=0 ; k<iter ; ++k ) {
                if ( ison ) {
                    ofSetColor(200, 50, 50, p_alpha[i]*ofMap(k, 0, iter, 0.01, 1.0));
                } else {
                    ofSetColor(0, 0);
                }
                ofDrawCircle(x, y, 14*ofMap(k, iter, 0, 0.02, 1.0));
            }
        }
    }
}

void ofApp::setActiveSequence(Sequence *seq)
{
	seq->currentFrame = 0;
	seq->ismouseover = false;
	sequence = *seq;
	sequence.position = gui.positionDrawText + ofVec2f(60, 40);
}

void ofApp::loadLetters()
{
	ofDirectory dir("");
	dir.allowExt("tpl");
	dir.listDir();
	for ( int i=0 ; i<dir.size() ; ++i ) {
		ofBuffer buffer = ofBufferFromFile(dir.getPath(i));
		
		for (auto line : buffer.getLines()){
			letters.push_back(ToggleMatrix());
			for ( int x=0 ; x<8 ; ++x ) {
				string str = ofSplitString(line, ",")[x];
				int col = ofHexToInt(str);
				for ( int y=0 ; y<8 ; ++y ) {
					bool ison = col & ( 1 << y);
					letters[letters.size()-1].bits[y*8 + x] = ison;
				}
			}
		}
	}
}

void ofApp::exportHeaderFile(bool defaultLocation)
{
    
	string str = "/* ***********************************************************************\n";
    str += "    Shaki firmware\n    Copyright (C) 2016-2018 Marco Fagiolini <mfx@amdx.de>\n\n";
    str += "    This program is free software: you can redistribute it and/or modify\n";
    str += "    it under the terms of the GNU General Public License as published by\n";
    str += "    the Free Software Foundation, either version 3 of the License, or\n";
    str += "    (at your option) any later version.\n\n";
    str += "    This program is distributed in the hope that it will be useful,\n";
    str += "    but WITHOUT ANY WARRANTY; without even the implied warranty of\n";
    str += "    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n";
    str += "    GNU General Public License for more details.\n\n";
    str += "    You should have received a copy of the GNU General Public License\n";
    str += "    along with this program.  If not, see <https://www.gnu.org/licenses/>.\n";
    str += "* ***********************************************************************/\n\n";
    str += "#ifndef FRAMEDATA_H_\n";
    str += "#define FRAMEDATA_H_\n\n";
    str += "\n\n#include <stdint.h>\n";
    str += "#include <avr/pgmspace.h>\n\n";
    str += "// Persist each frame for " + ofToString(spf) + " shakes\n";
    str += "#define SPF    " + ofToString(spf) + "\n\n";
    str += "// Framebuffer boundaries\n";
    str += "#define FRAMES_COUNT  " + ofToString(sequence.frames.size()) + "\n";
    str += "#define COLS          8\n\n";
    str += "// Framebuffer\n";
    str += "// Each byte represents a column, each array a frame\n";
	str += "const uint8_t frames[FRAMES_COUNT][COLS] PROGMEM = {\n";

	for ( int f=0 ; f<sequence.frames.size() ; ++f ) {
		str += "\n{";
		for ( int x=0 ; x<8 ; ++x ) {
			int row = 0;
			for ( int y=0 ; y<8 ; ++y ) {
				row |= sequence.frames[f].bits[8*y + x] << y;
			}
			str += "0x" + ofToHex(row).substr(6, 8);
			if ( x < 7 ) {
				str += ", ";
			} else {
				str += "}";
			}
		}
		if ( f < sequence.frames.size()-1 ) {
			str += ",";
		} else {
			str += "\n};";
		}
	}
    str += "\n\n";
    str += "#endif /* FRAMEDATA_H_ */";
    
	ofFile file;
    if ( defaultLocation ) {
    	file.open(pathToFirmware + "/src/frame_data.h", ofFile::WriteOnly);
    	file << str;
    	file.close();
    } else {
        if ( !dialogToggle ) {
            dialogToggle = true;
            ofFileDialogResult result = ofSystemSaveDialog("frame_data.h", "Export the frame_data.h");
            if ( result.bSuccess ) {
                string pathToFrameData = result.getPath();
            	file.open(pathToFrameData, ofFile::WriteOnly);
    	        pathToFirmware = ofSplitString(pathToFrameData, "frame_data.h")[0];    
            	file << str;
            	file.close();
            }
            dialogToggle = false;
        }
    }
}

void ofApp::onBtnAddFrame()
{
	sequence.addFrame();
}

void ofApp::onBtnRemoveFrame()
{
	sequence.removeFrame();
    p_currentFrame = 0;
}

void ofApp::onBtnAddTemplate()
{
	templates.addSequence(sequence, true);
	templates.scrollToEnd();
}

void ofApp::onBtnUpload()
{
	exportHeaderFile();
    string str = "osascript -e 'tell application \"Terminal\" to do script \"cd " + pathToFirmware + " && pio run -t upload\"'";
    char* valChar = (char*) str.c_str();
    system(valChar);
}

void ofApp::onBtnTemplatesUp()
{
	templates.decrementScroll();
}

void ofApp::onBtnTemplatesDown()
{
	templates.incrementScroll();
}

void ofApp::onBtnReset()
{
    sequence.reset();
    spf = 5;
}

void ofApp::onBtnExport()
{
    exportHeaderFile(false);
}

void ofApp::onBtnSPFUp()
{
    spf++;
    if ( spf > 10 ) {
        spf = 10;
    }
}

void ofApp::onBtnSPFDown()
{
    spf--;
    if ( spf < 1 ) {
        spf = 1;
    }
}

void ofApp::keyPressed(int key)
{
    if ( key >= 'a' && key <= 'z' ) {
        sequence.setCurrentFrame(&letters[key-'a']);
    } else if ( key >= '0' && key <= '9' ) {
        sequence.setCurrentFrame(&letters[key-'0'+'z'-'a'+1]);
    }
}

/*pass mouse input to current sequence and the templates*/
void ofApp::mouseMoved(int x, int y)
{
	templates.updateMouseInput(x, y, false);
}

void ofApp::mousePressed(int x, int y, int button)
{
	sequence.updateMouseInput(x, y, false);
    
    templates.updateMouseInput(x, y, true);
	int temp_id = templates.getTemplateToLoad();
	if ( temp_id > -1 ) {
		setActiveSequence(&templates.sequences[temp_id]);
	}
}

void ofApp::mouseDragged(int x, int y, int button)
{
	sequence.updateMouseInput(x, y, true);
}
