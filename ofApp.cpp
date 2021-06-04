#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofNoFill();
	ofEnableDepthTest();

	this->font_size = 22;
	ofTrueTypeFontSettings font_settings("fonts/msgothic.ttc", this->font_size);
	font_settings.antialiased = true;
	font_settings.addRanges(ofAlphabet::Japanese);
	this->font.load(font_settings);

	this->words = {

		u8"��", u8"��", u8"��", u8"��", u8"��",
		u8"��", u8"��", u8"��", u8"��", u8"��",
		u8"��", u8"��", u8"��", u8"��", u8"��",
		u8"��", u8"��", u8"��", u8"��", u8"��",
		u8"��", u8"��", u8"��", u8"��", u8"��",
		u8"��", u8"��", u8"��", u8"��", u8"��",
		u8"��", u8"��", u8"��", u8"��", u8"��",
		u8"��", u8"��", u8"��",
		u8"��", u8"��", u8"��", u8"��", u8"��",
		u8"��", u8"��", u8"��",
	};

	for (int x = 0; x < ofGetWidth() - this->font_size * 1.35; x += this->font_size * 1.35) {

		vector<string> line;
		for (int y = 0; y < ofGetHeight() - this->font_size; y += this->font_size * 1.35) {

			line.push_back(this->words[(int)(ofRandom(this->words.size()))]);
		}

		this->matrix.push_back(line);
	}

	for (int z = 0; z < 5; z++) {

		vector<int> random;
		for (int i = 0; i < this->matrix.size(); i++) {

			random.push_back(ofRandom(ofGetHeight() * 5));
		}

		this->random_values.push_back(random);
	}
}
//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(sin(ofGetFrameNum() * 0.02) * 15);

	for (int z = 0; z < 5; z += 1) {

		for (int row = 0; row < this->matrix.size(); row++) {

			int x = row * this->font_size * 1.35 - ofGetWidth() * 0.5;

			bool top = true;
			int random_value = this->random_values[z][row];
			for (int col = 0; col < this->matrix[row].size(); col++) {

				int y = col * this->font_size * 1.35 + ofGetHeight() * 0.5 + this->font_size * 1.35;

				int alpha = (random_value + ofGetFrameNum() * 5 + y) % (int)(ofGetHeight() * 5);
				if (alpha <= 255) {

					if (top) {

						this->matrix[row][col] = this->words[(int)(ofRandom(this->words.size()))];
						top = false;
					}

					ofSetColor(39, 255 - alpha);

					ofPushMatrix();
					ofTranslate(x, ofGetHeight() - y, z * 144 - 360);

					this->font.drawString(this->matrix[row][col], 0, 0);
					
					ofPopMatrix();
				}
			}
		}
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}