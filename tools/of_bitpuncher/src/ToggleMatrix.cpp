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

#include "ToggleMatrix.h"

ToggleMatrix::ToggleMatrix()
{
	dimension = 8;
	pixelsize = 42;
	gapsize = 3;
	bordersize = 10;
	int size = (pixelsize+gapsize) * dimension + bordersize*2;
	
	canvas.allocate(size,size);
	
	bits.assign(64, false);
	lastBit = -1;
}

void ToggleMatrix::draw(float scale, bool selected)
{
	canvas.begin();
	if ( !selected ) {
		ofBackground(240);
	} else {
		ofBackground(200,200,255);
	}
	for (int y=0 ; y<dimension ; ++y ) {
		for ( int x=0 ; x<dimension ; ++x ) {
			if ( bits[y*dimension+x] ) {
				ofSetColor(30);
			} else {
				ofSetColor(225);
			}
			ofDrawRectRounded( bordersize + x*(pixelsize+gapsize),
								bordersize + y*(pixelsize+gapsize), pixelsize,pixelsize, 2);
		}
	}
	canvas.end();
	
	
	canvas.draw(0,0,canvas.getWidth()*scale,canvas.getWidth()*scale);
}

void ToggleMatrix::updateMouseInput(int x, int y, bool dragging)
{
	if ( !dragging ) {
		lastBit = -1;
	}
	for ( int y_=0 ; y_<dimension ; ++y_ ) {
		for ( int x_=0 ; x_<dimension ; ++x_ ) {
			if ( x > x_*(pixelsize+gapsize)+bordersize && x < (x_+1)*(pixelsize+gapsize)+bordersize ) {
				if ( y > y_*(pixelsize+gapsize)+bordersize && y < (y_+1)*(pixelsize+gapsize)+bordersize ) {
					int newBit = dimension*y_+x_;
					if ( lastBit != newBit ) {
						if ( lastBit == -1 ) {
							isCreating = !bits[newBit];
						}
						bits[newBit] = isCreating;
						lastBit = newBit;
					}
				}
			}
		}
	}
}

bool ToggleMatrix::isPixelOn(int x, int y)
{
    if ( x>=0 && x<8 && y>=0 && y<8 ) {
        return bits[y*dimension+x];
    }
    return false;
}
