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

#ifndef TEMPLATES_H
#define TEMPLATES_H

#import "ofMain.h"
#import "Sequence.h"

class Templates {
public:
	Templates();
	~Templates();
	
	void drawGallery();
	void addSequence(Sequence sequence, bool save=false);
	void load();
	void save();
	
	void updateMouseInput(int x, int y, bool pressed);
    int getTemplateToLoad();
	
    void setPosition(ofVec2f pos);
    
	void incrementScroll();
	void decrementScroll();
	void scrollToEnd();
	
	vector <Sequence> sequences;
		
private:
	ofVec2f position;
    
	vector <string> templateNames;
	int numPreview;
    
    int idSelected;
    int idToLoad;
	int scrollValue;
    
	int previewOffset;
	float previewScale;
    
    ofTrueTypeFont font;
};

#endif