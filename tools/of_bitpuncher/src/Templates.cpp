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

#include "Templates.h"

Templates::Templates()
{
	previewOffset = 100;
	previewScale = 0.22;
	numPreview = 12;
    idSelected = -1;
    idToLoad = -1;
    
    font.load("Fonts/adventpro-extralight.ttf", 14);
    
}

Templates::~Templates()
{
	
}

void Templates::load()
{
	ofDirectory dir("Templates");
	dir.allowExt("dat");
	dir.listDir();
	for ( int i=0 ; i<dir.size() ; ++i ) {
		ofBuffer buffer = ofBufferFromFile(dir.getPath(i));
		templateNames.push_back(dir.getPath(i));
		int frameCounter = 0;
		
		Sequence seq;
		for (auto line : buffer.getLines()){
			if ( frameCounter > 0 ) {
				seq.addFrame();
			}
			
			for ( int x=0 ; x<8 ; ++x ) {
				string str = ofSplitString(line, ",")[x];
				int col = ofHexToInt(str);
				for ( int y=0 ; y<8 ; ++y ) {
					bool ison = col & ( 1 << y);
					seq.frames[frameCounter].bits[y*8 + x] = ison;
				}
			}
			frameCounter++;
		}
		addSequence(seq);
	}
}

void Templates::drawGallery()
{
	
	
	for ( int i=0 ; i<numPreview ; ++i ) {
		int id = i + scrollValue;
		if ( id < sequences.size() ) {
        	ofPushMatrix();
        	ofTranslate(position);
		    ofTranslate((i%2)*previewOffset, i/2 * previewOffset);
			sequences[id].drawCurrentFrame(previewScale);
            if ( idSelected == id ) {
                ofSetColor(230,230,230,230);
                ofDrawRectangle(0,0,previewOffset-17,previewOffset/2-7);
                ofSetColor(245, 138, 7,230);
                ofDrawRectangle(0,previewOffset/2-10,previewOffset-17,previewOffset/2-7);
                ofSetColor(40);
                font.drawString("Load",22,25);
                font.drawString("Delete",15,previewOffset/2+20);
                
            }
        	ofPopMatrix();
		}
	}
}

void Templates::addSequence(Sequence sequence, bool save)
{
	sequence.position = ofVec2f(0,0);
	sequences.push_back(sequence);
	
	if ( save ) {
		ofFile file;
		string filename = "Templates/template_" + ofGetTimestampString() + ".dat";
		file.open(filename, ofFile::WriteOnly);
	    templateNames.push_back(filename);
		for ( int f=0 ; f<sequence.frames.size() ; ++f ) {
			string frame = "";
			for ( int x=0 ; x<8 ; ++x ) {
				int row = 0;
				for (int y=0 ; y<8 ; ++y ) {
					row |= sequence.frames[f].bits[8*y + x] << y;
				}
				frame += ofToHex(row).substr(6,8);
				if ( x < 7 ) {
					frame += ", ";
				} else {
					frame += "\n";
				}
			}
			file << frame;
		}
		file.close();
	}
}



void Templates::setPosition(ofVec2f pos)
{
    position = pos;
}

int Templates::getTemplateToLoad()
{
    int id = idToLoad;
    idToLoad = -1;
    return id;
}

void Templates::updateMouseInput(int x, int y, bool pressed)
{
    int id = -1;
    bool add = false;
    
	for ( int i=0 ; i<numPreview ; ++i ) {
		int id_ = i + scrollValue;
		if ( id_ < sequences.size() ) {
            ofVec2f pos = position + ofVec2f((id_%2)*previewOffset, i/2*previewOffset);            
			if ( x-pos.x > 0 && x-pos.x < previewOffset && 
					y-pos.y > 0 && y-pos.y < previewOffset ) {
                if ( y-pos.y < previewOffset/2 ) {
                    add = true;
                } else {
                    add = false;
                }
				id = id_;
                break;
			}
		} else {
		    id = -1;
		}
	}    
    
    if ( pressed ) {
        if ( idSelected == -1 ) {
            idSelected = id;
        } else {
            if ( idSelected == id ) {
                if ( add ) {
                    idToLoad = id;
                } else {
                    ofFile file;
                    file.open(templateNames[idSelected], ofFile::WriteOnly);
                    file.remove(false);
                    file.close();
                    templateNames.erase(templateNames.begin()+idSelected);
                    sequences.erase(sequences.begin()+idSelected);
                }
            }
            idSelected = -1;
            
        }
    } else {
        for ( int i=0 ; i<sequences.size() ; ++i ) {
            if ( i == id ) {
        		sequences[id].ismouseover = true;
            } else {
        		sequences[i].ismouseover = false;
        		sequences[i].currentFrame = 0;
            }
        }
    }
}

void Templates::incrementScroll()
{
	if ( scrollValue < (int)sequences.size() - numPreview ) {
		scrollValue+=2;
	}
}

void Templates::decrementScroll()
{
	if ( scrollValue > 0 ) {
		scrollValue-=2;
	}
}

void Templates::scrollToEnd()
{
	scrollValue = (int)sequences.size() - numPreview;
    if (scrollValue%2) scrollValue += 1;
	if ( scrollValue < 0 ) scrollValue = 0;
}
