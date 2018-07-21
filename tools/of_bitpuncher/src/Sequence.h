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

#ifndef SEQUENCE_H
#define SEQUENCE_H

#include "ofMain.h"
#include "ToggleMatrix.h"

class Sequence{
public:
	Sequence();
	~Sequence();
	
	void drawCurrentFrame(float scale = 1.0f);
	void playbackFrames();
	void drawFramesPreview();
	
	void addFrame();
	void removeFrame();
    
    void reset();
	
    void setCurrentFrame(ToggleMatrix *frame);
    
	void updateMouseInput(int x, int y, bool dragging);
	
	ofVec2f position;
    ofVec2f positionSingleFrames;
	
	int currentFrame;
	bool ismouseover;
	
	vector <ToggleMatrix> frames;
	
private:
	float fps;
	float frametime;
	
	int max_frames;
	int frames_distance;
	int frames_offset;
	float frames_scale;
	
};

#endif