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

#ifndef OFAPP_H
#define OFAPP_H

#include "ofMain.h"
#include "ofxGuiExtended.h"
#include "Sequence.h"
#include "Templates.h"
#include "Gui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
				
		void createTemplate();
		void loadLetters();

		void keyPressed(int key);
		void mouseMoved(int x, int y);
		void mousePressed(int x, int y, int button);
		void mouseDragged(int x, int y, int button);
		
        void setActiveSequence(Sequence *seq);
		
		void drawAnimatedPreview();
		
		void exportHeaderFile(bool defaultLocation=true);
		
        /* button callbacks*/
		void onBtnAddFrame();
		void onBtnRemoveFrame();
		void onBtnAddTemplate();
		void onBtnUpload();
		void onBtnTemplatesUp();
		void onBtnTemplatesDown();
		void onBtnReset();
		void onBtnExport();
		void onBtnSPFUp();
		void onBtnSPFDown();
		
		Sequence sequence;
		Templates templates;
		
		vector <ToggleMatrix> letters;
		
		Gui gui;
		ofImage imgShaki;	//shaki photo
		
		string pathToFirmware;
		
		int spf;	//shakes per frame
		
		bool dialogToggle;		
		
		/*animated preview*/
		float p_angleArc;
		float p_speed;
		float p_fadeout;
		float p_radius1, p_radius2;
		float p_angle;
		vector <float> p_alpha;
		bool p_direction;
		int p_currentFrame;
		int p_shakeCounter;
				
};

#endif