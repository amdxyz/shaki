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

#include "Sequence.h"

Sequence::Sequence()
{
	currentFrame = 0;
	frames.push_back(ToggleMatrix());

	ismouseover = false;	
	
	max_frames = 10;
	frames_offset = 88;
	frames_scale = 0.2;
	fps = 2;
    
    positionSingleFrames = ofVec2f(110, 570);

	
}
Sequence::~Sequence()
{
}

void Sequence::drawCurrentFrame(float scale)
{
	if ( ismouseover ) {
		frametime += ofGetLastFrameTime();
	
		if ( frametime >= 1.0f / fps ) {
			frametime = 0.0f;
			currentFrame++;
			if ( currentFrame > frames.size()-1 ) {
				currentFrame = 0;
			}
		}
	}
	ofSetColor(255, 200);
	
	ofPushMatrix();
	ofTranslate(position);
	frames[currentFrame].draw(scale, ismouseover);
	ofPopMatrix();
	
	
}

void Sequence::playbackFrames()
{
	
	drawCurrentFrame(frames_scale);
}

void Sequence::drawFramesPreview()
{
	ofPushMatrix();
	ofTranslate(positionSingleFrames);
	for ( int i=0 ; i<frames.size() ; ++i ) {
		if ( i != 0 ) ofTranslate(frames_offset, 0);
		frames[i].draw(frames_scale, i==currentFrame);
	}
	ofPopMatrix();
}

void Sequence::addFrame()
{
	if ( frames.size() < max_frames ) {
		frames.push_back(ToggleMatrix());
		currentFrame = frames.size() - 1;
	}
}

void Sequence::removeFrame()
{
	frames.erase(frames.begin()+currentFrame);
	if ( currentFrame > frames.size() - 1 ) {
		currentFrame--;
	}
	if ( frames.size() == 0 ) {
		addFrame();
	}
}

void Sequence::reset()
{
    frames.clear();
    currentFrame = 0;
    addFrame();
}

void Sequence::setCurrentFrame(ToggleMatrix *frame)
{
    frames[currentFrame] = *frame;
}


void Sequence::updateMouseInput(int x, int y, bool dragging)
{
	frames[currentFrame].updateMouseInput(x-position.x, y-position.y, dragging);
	
	for ( int i=0 ; i<frames.size() ; ++i ) {
		if ( x - positionSingleFrames.x > i*frames_offset && x - positionSingleFrames.x < (i+1)*frames_offset ) {
			if ( y - positionSingleFrames.y > 0 && y - positionSingleFrames.y < frames_offset ) {
				currentFrame = i;
			}
		}
	}
	
}