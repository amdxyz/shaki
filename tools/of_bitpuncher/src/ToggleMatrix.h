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

#ifndef TOGGLEMATRIX_H
#define TOGGLEMATRIX_H

#include "ofMain.h"

class ToggleMatrix {
public:

	ToggleMatrix();

	void drawGrid();
	void updateMouseInput(int x, int y, bool dragging);
	
	void play();
	void draw(float scale=1.0f, bool selected = false);
	
    bool isPixelOn(int x, int y);
    
	vector <bool> bits;
	
private:
	ofFbo canvas;
	int lastBit;
	bool isCreating;
	int dimension;
	int pixelsize;
	int gapsize;
	int bordersize;
    		
};

#endif