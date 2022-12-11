#include <iostream>
#include <string>
#include <random>
#include <array>
#include <vector>
#include <cmath>
#include <time.h>

#include "Sphere.h"
#include "Light.h"
#include "SpherePair.h"
#include "Texture.h"

using namespace std;

#define WIDTH 320
#define HEIGHT 640
#define boundaryX 120
#define boundaryY 240
#define TILELEN 40

clock_t start_clock = clock();
clock_t end_clock;
int fps = 30;

int Stage = 0;
int Score = 0;
vector<int> scoreBoard{ 0, 0, 0 };
vector<Sphere> startPageSphs(86);
SpherePair nextPair;
SpherePair currPair;
array<vector<Sphere>, 6> pileLane;
vector<array<int, 2>> removeCoord;
Light light(boundaryX, boundaryY, boundaryX / 2, GL_LIGHT0);
bool movingFirst = false;
bool movingSecond = false;
bool pause = true;
bool stageChanging = false;
bool removing = false;
bool removeFalling = false;
int removingTime = 0;
vector<Texture> textures;


int genRandColorNum(int num) {
	int numColor = 0;

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(0, num - 1);

	numColor = dis(gen);

	return numColor;
}

Vector4f genRandAmbient(int numColor) {
	Vector4f ambient;

	switch (numColor) {
	case 0:
		ambient.setPos(0.7f, 0.1f, 0.1f, 1.0f);
		break;
	case 1:
		ambient.setPos(0.1f, 0.7f, 0.1f, 1.0f);
		break;
	case 2:
		ambient.setPos(0.1f, 0.1f, 0.7f, 1.0f);
		break;
	case 3:
		ambient.setPos(0.5f, 0.5f, 0.1f, 1.0f);
		break;
	case 4:
		ambient.setPos(0.1f, 0.5f, 0.5f, 1.0f);
		break;
	case 5:
		ambient.setPos(0.3f, 0.5f, 0.1f, 1.0f);
		break;
	case 6:
		ambient.setPos(0.1f, 0.7f, 0.4f, 1.0f);
		break;
	case 7:
		ambient.setPos(0.9f, 0.2f, 0.3f, 1.0f);
		break;
	case 8:
		ambient.setPos(0.3f, 0.3f, 0.3f, 1.0f);
		break;
	case 9:
		ambient.setPos(0.1f, 0.5f, 0.7f, 1.0f);
		break;
	}
	return ambient;
}

void generateNextPair() {
	int sphRadius = TILELEN / 2;
	int stksl = 50;

	SpherePair sph_pair;
	Sphere sph1, sph2;


	int randNum = genRandColorNum(Stage + 2);
	sph1.setColor(randNum);
	sph1.setEmission(0.1, 0.1, 0.1, 1);
	sph1.setAmbient(genRandAmbient(sph1.getColor()));
	sph1.setDiffuse(0.7, 0.7, 0.7, 1);
	sph1.setSpecular(1.0, 1.0, 1.0, 1);
	sph1.setShininess(10);

	randNum = genRandColorNum(Stage + 2);
	sph2.setColor(randNum);
	sph2.setEmission(0.1, 0.1, 0.1, 1);
	sph2.setAmbient(genRandAmbient(sph2.getColor()));
	sph2.setDiffuse(0.7, 0.7, 0.7, 1);
	sph2.setSpecular(1.0, 1.0, 1.0, 1);
	sph2.setShininess(10);

	sph1.setRadius(sphRadius);
	sph2.setRadius(sphRadius);
	sph1.setSlice(stksl);
	sph2.setSlice(stksl);
	sph1.setStack(stksl);
	sph2.setStack(stksl);
	sph1.setLane(2);
	sph2.setLane(3);
	sph1.setCenter(Vector3f(-TILELEN / 2, boundaryY + TILELEN / 2, 0));
	sph2.setCenter(Vector3f(TILELEN / 2, boundaryY + TILELEN / 2, 0));

	Vector3f vel(0.0f, -5.0f, 0.0f);
	sph1.setVelocity(vel);
	sph2.setVelocity(vel);

	sph_pair.setSpherePair(sph1, sph2);
	nextPair = sph_pair;

	
}

void InitializeStartPage() {
	int radius = 5;

	for (auto itr = startPageSphs.begin(); itr != startPageSphs.end(); itr++) {
		int randNum = genRandColorNum(10);
		itr->setColor(randNum);
		itr->setEmission(0.1, 0.1, 0.1, 1);
		itr->setAmbient(genRandAmbient(itr->getColor()));
		itr->setDiffuse(0.7, 0.7, 0.7, 1);
		itr->setSpecular(1.0, 1.0, 1.0, 1);
		itr->setShininess(10);

		itr->setRadius(radius);
		itr->setSlice(20);
		itr->setStack(20);
		itr->setCenter(Vector3f(0,  0 , 0));
	}
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 5; j++) startPageSphs[j + 43 * i].setCenter(Vector3f(-125 + 10*j + 140 * i, 45, 0));
		for (int j = 0; j < 3; j++) startPageSphs[5 + j + 43 * i].setCenter(Vector3f(-125 + 20 * j + 140 * i, 55, 0));
		for (int j = 0; j < 5; j++) startPageSphs[8 + j + 43 * i].setCenter(Vector3f(-125 + 10 * j + 140 * i, 65, 0));
		for (int j = 0; j < 3; j++) startPageSphs[13 + j + 43 * i].setCenter(Vector3f(-125 + 20 * j + 140 * i, 75, 0));
		for (int j = 0; j < 3; j++) startPageSphs[16 + j + 43 * i].setCenter(Vector3f(-125 + 20 * j + 140 * i, 85, 0));

		for (int j = 0; j < 5; j++) startPageSphs[19 + j + 43 * i].setCenter(Vector3f(-125 + 10 * j + 140 * i, 15, 0));
		startPageSphs[24 + 43 * i].setCenter(Vector3f(-105 + 140 * i, 5, 0));
		startPageSphs[25 + 43 * i].setCenter(Vector3f(-105 + 140 * i, -5, 0));

		startPageSphs[26 + 43 * i].setCenter(Vector3f(-35 + 140 * i, 45, 0));
		startPageSphs[27 + 43 * i].setCenter(Vector3f(-35 - 20.0f/1.4f + 140 * i, 65 - 20.0f / 1.4f, 0));
		startPageSphs[28 + 43 * i].setCenter(Vector3f(-55 + 140 * i, 65, 0));
		startPageSphs[29 + 43 * i].setCenter(Vector3f(-35 - 20.0f / 1.4f + 140 * i, 65 + 20.0f / 1.4f, 0));
		startPageSphs[30 + 43 * i].setCenter(Vector3f(-35 + 140 * i, 85, 0));
		startPageSphs[31 + 43 * i].setCenter(Vector3f(-35 + 20.0f / 1.4f + 140 * i, 65 + 20.0f / 1.4f, 0));
		startPageSphs[32 + 43 * i].setCenter(Vector3f(-15 + 140 * i, 65, 0));
		startPageSphs[33 + 43 * i].setCenter(Vector3f(-35 + 20.0f / 1.4f + 140 * i, 65 - 20.0f / 1.4f, 0));

		for (int j = 0; j < 2; j++) startPageSphs[34 + j + 43 * i].setCenter(Vector3f(-45 + 20 * j + 140 * i, 15, 0));
		for (int j = 0; j < 2; j++) startPageSphs[36 + j + 43 * i].setCenter(Vector3f(-45 + 20 * j + 140 * i, 5, 0));
		for (int j = 0; j < 5; j++) startPageSphs[38 + j + 43 * i].setCenter(Vector3f(-55 + 10 * j + 140 * i, -5, 0));
	}
}

void initialize() {
	light.setAmbient(0.5, 0.5, 0.5, 1.0);
	light.setDiffuse(0.7, 0.7, 0.7, 1.0);
	light.setSpecular(1.0, 1.0, 1.0, 1.0);

	InitializeStartPage();

	generateNextPair();

	currPair = nextPair;
	currPair.modFirstSphere().setCenter(Vector3f(-TILELEN / 2, boundaryY - TILELEN / 2, 0));
	currPair.modSecondSphere().setCenter(Vector3f(TILELEN / 2, boundaryY - TILELEN / 2, 0));

	generateNextPair();

	Texture text1, text2, text3, text4;
	text1.initializeTexture("white.png");
	text2.initializeTexture("purple.png");
	text3.initializeTexture("orange.png");
	text4.initializeTexture("red.png");

	textures.push_back(text1);
	textures.push_back(text2);
	textures.push_back(text3);
	textures.push_back(text4);
}

void specialKeyDown(int key, int x, int y) {
	if (!pause) {
		if ((!movingFirst) && (!movingSecond)) {
			float xFirst = currPair.getFirstSphere().getCenter()[0];
			float xSecond = currPair.getSecondSphere().getCenter()[0];
			float yFirst = currPair.getFirstSphere().getCenter()[1];
			float ySecond = currPair.getSecondSphere().getCenter()[1];
			int laneFirst = currPair.getFirstSphere().getLane();
			int laneSecond = currPair.getSecondSphere().getLane();

			switch (key) {
			case GLUT_KEY_LEFT:
				if (min(laneFirst, laneSecond) > 0) {
					if (pileLane[min(laneFirst, laneSecond) - 1].empty() || pileLane[min(laneFirst, laneSecond) - 1].back().getCenter()[1] < min(yFirst, ySecond) - TILELEN) {
						currPair.modFirstSphere().setCenter(currPair.getFirstSphere().getCenter() - Vector3f((float)TILELEN, 0, 0));
						currPair.modSecondSphere().setCenter(currPair.getSecondSphere().getCenter() - Vector3f((float)TILELEN, 0, 0));
						currPair.modFirstSphere().setLane(laneFirst - 1);
						currPair.modSecondSphere().setLane(laneSecond - 1);
					}
				}
				break;
			case GLUT_KEY_RIGHT:
				if (max(laneFirst, laneSecond) < pileLane.size() - 1) {
					if (pileLane[max(laneFirst, laneSecond) + 1].empty() || pileLane[max(laneFirst, laneSecond) + 1].back().getCenter()[1] < min(yFirst, ySecond) - TILELEN) {
						currPair.modFirstSphere().setCenter(currPair.getFirstSphere().getCenter() + Vector3f((float)TILELEN, 0, 0));
						currPair.modSecondSphere().setCenter(currPair.getSecondSphere().getCenter() + Vector3f((float)TILELEN, 0, 0));
						currPair.modFirstSphere().setLane(laneFirst + 1);
						currPair.modSecondSphere().setLane(laneSecond + 1);
					}
				}
				break;
			case GLUT_KEY_UP:
				if (laneFirst == laneSecond) {
					if (yFirst > ySecond) {
						if ((laneFirst == 5) || ((!pileLane[laneFirst + 1].empty()) && pileLane[laneFirst + 1].back().getCenter()[1] + TILELEN > yFirst)) {
							if ((laneFirst == 0) || ((!pileLane[laneFirst - 1].empty()) && pileLane[laneFirst - 1].back().getCenter()[1] + TILELEN > yFirst)) return;

							currPair.modFirstSphere().setCenter(currPair.getFirstSphere().getCenter() - Vector3f((float)TILELEN, 0, 0));
							currPair.modFirstSphere().setLane(laneFirst - 1);
						}
						currPair.modSecondSphere().setCenter(currPair.getFirstSphere().getCenter() + Vector3f((float)TILELEN, 0, 0));
						currPair.modSecondSphere().setLane(currPair.getFirstSphere().getLane() + 1);
					}
					else {
						if ((laneFirst == 0) || ((!pileLane[laneFirst - 1].empty()) && pileLane[laneFirst - 1].back().getCenter()[1] + TILELEN > yFirst)) {
							if ((laneFirst == 5) || ((!pileLane[laneFirst + 1].empty()) && pileLane[laneFirst + 1].back().getCenter()[1] + TILELEN > yFirst)) return;

							currPair.modFirstSphere().setCenter(currPair.getFirstSphere().getCenter() + Vector3f((float)TILELEN, 0, 0));
							currPair.modFirstSphere().setLane(laneFirst + 1);
						}
						currPair.modSecondSphere().setCenter(currPair.getFirstSphere().getCenter() - Vector3f((float)TILELEN, 0, 0));
						currPair.modSecondSphere().setLane(currPair.getFirstSphere().getLane() - 1);
					}
				}
				else {
					if (xFirst > xSecond) {
						currPair.modSecondSphere().setCenter(currPair.getFirstSphere().getCenter() - Vector3f(0, (float)TILELEN, 0));
						currPair.modSecondSphere().setLane(laneFirst);
					}
					else {
						currPair.modSecondSphere().setCenter(currPair.getFirstSphere().getCenter() + Vector3f(0, (float)TILELEN, 0));
						currPair.modSecondSphere().setLane(laneFirst);
					}
				}
				break;
			case GLUT_KEY_DOWN:
				if (((pileLane[laneFirst].empty() && -boundaryY + 1.5f * (float)TILELEN < yFirst) || ((!pileLane[laneFirst].empty()) && pileLane[laneFirst].back().getCenter()[1] + 2.0f * (float)TILELEN < yFirst)) && ((pileLane[laneSecond].empty() && -boundaryY + 1.5f * (float)TILELEN < ySecond) || ((!pileLane[laneSecond].empty()) && pileLane[laneSecond].back().getCenter()[1] + 2.0f * (float)TILELEN < ySecond))) {
					currPair.modFirstSphere().setCenter(currPair.getFirstSphere().getCenter() - Vector3f(0, (float)TILELEN, 0));
					currPair.modSecondSphere().setCenter(currPair.getSecondSphere().getCenter() - Vector3f(0, (float)TILELEN, 0));
				}
				else if((!pileLane[laneFirst].empty()) && (!pileLane[laneSecond].empty())) {
					currPair.modFirstSphere().setCenter(pileLane[laneFirst].back().getCenter() + Vector3f(0, (float)TILELEN, 0));
					currPair.modSecondSphere().setCenter(pileLane[laneSecond].back().getCenter() + Vector3f(0, (float)TILELEN, 0));
				}
				break;
			}
		}
	}
}

void keyboardDown(unsigned char key, int x, int y) {
	if (!pause) {
		int laneFirst = currPair.getFirstSphere().getLane();
		int laneSecond = currPair.getSecondSphere().getLane();

		if (key == ' ') {
				if (currPair.getFirstSphere().getLane() == currPair.getSecondSphere().getLane()) {
					if (currPair.getFirstSphere().getCenter()[1] < currPair.getSecondSphere().getCenter()[1]) {
						if (pileLane[laneFirst].empty()) currPair.modFirstSphere().setCenter(Vector3f(-boundaryX + (TILELEN * ((float)laneFirst + 0.5f)), -boundaryY + (TILELEN * 0.5f), 0));
						else currPair.modFirstSphere().setCenter(pileLane[laneFirst].back().getCenter() + Vector3f(0, (float)TILELEN, 0));
						currPair.modSecondSphere().setCenter(currPair.getFirstSphere().getCenter() + Vector3f(0, (float)TILELEN, 0));
					}
					else {
						if (pileLane[laneSecond].empty()) currPair.modSecondSphere().setCenter(Vector3f(-boundaryX + (TILELEN * ((float)laneFirst + 0.5f)), -boundaryY + (TILELEN * 0.5f), 0));
						else currPair.modSecondSphere().setCenter(pileLane[laneSecond].back().getCenter() + Vector3f(0, (float)TILELEN, 0));
						currPair.modFirstSphere().setCenter(currPair.getSecondSphere().getCenter() + Vector3f(0, (float)TILELEN, 0));
					}
				}
				else {
					if (pileLane[laneFirst].empty()) currPair.modFirstSphere().setCenter(Vector3f(-boundaryX + (TILELEN * ((float)laneFirst + 0.5f)), -boundaryY + (TILELEN * 0.5f), 0));
					else currPair.modFirstSphere().setCenter(pileLane[laneFirst].back().getCenter() + Vector3f(0, (float)TILELEN, 0));
					if (pileLane[laneSecond].empty()) currPair.modSecondSphere().setCenter(Vector3f(-boundaryX + (TILELEN * ((float)laneSecond + 0.5f)), -boundaryY + (TILELEN * 0.5f), 0));
					else currPair.modSecondSphere().setCenter(pileLane[laneSecond].back().getCenter() + Vector3f(0, (float)TILELEN, 0));
				}
		}
	}
	if (key == 'f') {
		if (fps == 30) fps = 60;
		else fps = 30;
	}
	if (key == 'p') {
		if (Stage > 0 && Stage < 4) {
			if (pause) pause = false;
			else pause = true;
		}
	}
	if (key == ' ') {
		if (Stage == 0) {
			Stage++;
			pause = false;
		}
		if (Stage == -1) {
			for (int i = 0; i < pileLane.size(); i++) {
				pileLane[i].clear();
			}
			generateNextPair();

			currPair = nextPair;
			currPair.modFirstSphere().setCenter(Vector3f(-TILELEN / 2, boundaryY - TILELEN / 2, 0));
			currPair.modSecondSphere().setCenter(Vector3f(TILELEN / 2, boundaryY - TILELEN / 2, 0));

			generateNextPair();

			movingFirst = false;
			movingSecond = false;
			Stage = 1;
			Score = 0;
			pause = false;
		}
		if (stageChanging) {
			if (Stage == 3) {
				Score = 0;
				Stage = 1;
			}
			else Stage++;

			for (int i = 0; i < pileLane.size(); i++) {
				pileLane[i].clear();
			}
			generateNextPair();

			currPair = nextPair;
			currPair.modFirstSphere().setCenter(Vector3f(-TILELEN / 2, boundaryY - TILELEN / 2, 0));
			currPair.modSecondSphere().setCenter(Vector3f(TILELEN / 2, boundaryY - TILELEN / 2, 0));

			generateNextPair();

			movingFirst = false;
			movingSecond = false;
			pause = false;
			stageChanging = false;
		}
	}

}

void drawSquareWithTexture() {
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, textures[0].getTextureID());
	glBegin(GL_QUADS);
	for (int j = 0; j < 6; j++) {
		for (int i = 0; i < 3; i++) {
			glTexCoord2f(0, 0); glVertex2f(-boundaryX + (2 * i) * TILELEN, -boundaryY + (2 * j) * TILELEN);
			glTexCoord2f(0, 1); glVertex2f(-boundaryX + (2 * i) * TILELEN, -boundaryY + (2 * j + 1) * TILELEN);
			glTexCoord2f(1, 1); glVertex2f(-boundaryX + (2 * i + 1) * TILELEN, -boundaryY + (2 * j + 1) * TILELEN);
			glTexCoord2f(1, 0); glVertex2f(-boundaryX + (2 * i + 1) * TILELEN, -boundaryY + (2 * + j) * TILELEN);
			glTexCoord2f(0, 0); glVertex2f(-boundaryX + (2 * i + 1) * TILELEN, -boundaryY + (2 * j + 1) * TILELEN);
			glTexCoord2f(0, 1); glVertex2f(-boundaryX + (2 * i + 1) * TILELEN, -boundaryY + (2 * j + 2) * TILELEN);
			glTexCoord2f(1, 1); glVertex2f(-boundaryX + (2 * i + 2) * TILELEN, -boundaryY + (2 * j + 2) * TILELEN);
			glTexCoord2f(1, 0); glVertex2f(-boundaryX + (2 * i + 2) * TILELEN, -boundaryY + (2 * +j + 1) * TILELEN);
		}
	}
	glEnd();
	switch (Stage) {
	case 1:
		glBindTexture(GL_TEXTURE_2D, textures[1].getTextureID());
		break;
	case 2:
		glBindTexture(GL_TEXTURE_2D, textures[2].getTextureID());
		break;
	case 3:
		glBindTexture(GL_TEXTURE_2D, textures[3].getTextureID());
		break;
	}
	glBegin(GL_QUADS);
	for (int j = 0; j < 6; j++) {
		for (int i = 0; i < 3; i++) {
			glTexCoord2f(0, 0); glVertex2f(-boundaryX + (2 * i + 1) * TILELEN, -boundaryY + (2 * j) * TILELEN);
			glTexCoord2f(0, 1); glVertex2f(-boundaryX + (2 * i + 1) * TILELEN, -boundaryY + (2 * j + 1) * TILELEN);
			glTexCoord2f(1, 1); glVertex2f(-boundaryX + (2 * i + 2) * TILELEN, -boundaryY + (2 * j + 1) * TILELEN);
			glTexCoord2f(1, 0); glVertex2f(-boundaryX + (2 * i + 2) * TILELEN, -boundaryY + (2 * j) * TILELEN);
			glTexCoord2f(0, 0); glVertex2f(-boundaryX + (2 * i) * TILELEN, -boundaryY + (2 * j + 1) * TILELEN);
			glTexCoord2f(0, 1); glVertex2f(-boundaryX + (2 * i) * TILELEN, -boundaryY + (2 * j + 2) * TILELEN);
			glTexCoord2f(1, 1); glVertex2f(-boundaryX + (2 * i + 1) * TILELEN, -boundaryY + (2 * j + 2) * TILELEN);
			glTexCoord2f(1, 0); glVertex2f(-boundaryX + (2 * i + 1) * TILELEN, -boundaryY + (2 * +j + 1) * TILELEN);
		}
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);

}

void displayCharacters(void* font, string str, float x, float y) {
	glColor3f(1.0f, 1.0f, 1.0f);
	glRasterPos2f(x, y);
	for (int i = 0; i < str.size(); i++) {
		glutBitmapCharacter(font, str[i]);
	}
}

void stageCheck() {
	if (Stage == 1 && Score >= 200) {
		pause = true;
		stageChanging = true;
	}
	else if (Stage == 2 && Score >= 400) {
		pause = true;
		stageChanging = true;
	}
	else if (Stage == 3 && Score >= 600) {
		pause = true;
		stageChanging = true;
		for (auto itr = scoreBoard.begin(); itr != scoreBoard.end(); itr++) {
			if (*itr < Score) {
				scoreBoard.insert(itr, Score);
				break;
			}
		}
	}
}

void detectPop() {
	vector<vector<vector<array<int, 2>>>> popPop(Stage + 2);
	vector<array<int, 2>> deleteCoord;

	for (int i = 0; i < pileLane.size(); i++) {
		int j = 0;
		for (auto itr = pileLane[i].begin(); itr != pileLane[i].end(); itr++) {
			array<int, 2> tempCoord = { i, j };
			int numCol = itr->getColor();

			auto itrCoord = popPop[numCol].begin();
			auto tempItr1 = popPop[numCol].begin();
			auto tempItr2 = popPop[numCol].begin();
			bool found = false;
			bool crossUpFound = false;
			while (itrCoord != popPop[numCol].end()) {
				for (auto itrArray = itrCoord->begin(); itrArray != itrCoord->end(); itrArray++) {
					int x1 = (*itrArray)[0];
					int y1 = (*itrArray)[1];
					int x2 = i;
					int y2 = j;

					if (((x1 == x2) && (abs(y1 - y2) == 1)) || ((abs(x1 - x2) == 1) && (y1 == y2))) {
						auto itrFind = find(itrCoord->begin(), itrCoord->end(), tempCoord);
						if (itrFind == itrCoord->end()) itrCoord->push_back(tempCoord);
						found = true;
						break;
					}

					if (itr != pileLane[i].end() - 1) {
						auto tempItr = itr + 1;
						int Yj = 1;
						while (tempItr != pileLane[i].end()) {
							if (tempItr->getColor() == numCol) {
								if ((x1 == x2 - 1) && (y1 == y2 + Yj)) {
									auto itrFind = find(itrCoord->begin(), itrCoord->end(), tempCoord);
									if (itrFind == itrCoord->end()) itrCoord->push_back(tempCoord);
									found = true;
									crossUpFound = true;
									break;
								}
								Yj++;
								tempItr++;
							}
							else break;
						}
						if (crossUpFound) break;
					}

				}
				if (found) break;
				itrCoord++;
			}
			if (itrCoord == popPop[numCol].end()) {
				vector<array<int, 2>> tempVec;
				tempVec.push_back(tempCoord);
				popPop[numCol].push_back(tempVec);
			}
			j++;
		}
	}

	for (auto itrColor = popPop.begin(); itrColor != popPop.end(); itrColor++) {
		for (auto itrCoord = itrColor->begin(); itrCoord != itrColor->end(); itrCoord++) {
			if (itrCoord->size() >= 4) {
				for (auto itrDel = itrCoord->begin(); itrDel != itrCoord->end(); itrDel++) {
					auto itr = deleteCoord.begin();
					while (itr != deleteCoord.end()) {
						if ((*itrDel)[0] > (*itr)[0]) {
							itr++;
							continue;
						}
						else if ((*itrDel)[0] == (*itr)[0]) {
							if ((*itrDel)[1] > (*itr)[1]) {
								itr++;
								continue;
							}
							else break;
						}
						else break;
					}
					deleteCoord.insert(itr, *itrDel);
				}
			}
		}
	}

	removeCoord = deleteCoord;
		
	if (!deleteCoord.empty()) {
		removeCoord = deleteCoord;
		removing = true;
	}
	else {
		removeCoord.clear();
	}
		

}

int pileCollision() {
	int collision = 0;

	int sphRadius = TILELEN / 2;
	float firstLower = currPair.getFirstSphere().getCenter()[1] - (float)sphRadius;
	float secondLower = currPair.getSecondSphere().getCenter()[1] - (float)sphRadius;
	int firstLane = currPair.getFirstSphere().getLane();
	int secondLane = currPair.getSecondSphere().getLane();

	for (int i = 0; i < pileLane.size(); i++) {
		float upper;
		if (pileLane[i].empty()) upper = -boundaryY;
		else upper = pileLane[i].back().getCenter()[1] + (float)sphRadius;
		
		if ((upper >= firstLower || upper >= secondLower) && ((i == firstLane) && (i == secondLane))) {
			collision = 3;
			break;
		}
		else {
			if (upper >= firstLower && i == firstLane) {
				if (collision == 0) collision = 1;
				else if (collision == 2) {
					collision = 3;
					break;
				}
			}
			if (upper >= secondLower && i == secondLane) {
				if (collision == 0) collision = 2;
				else if (collision == 1) {
					collision = 3;
					break;
				}
			}
		}
	}

	return collision;
}

bool failCondition() {
	for (int i = 0; i < pileLane.size(); i++) {
		if (pileLane[i].size() >= 12) return true;
	}
	return false;
}

void alignPile() {
	for (int i = 0; i < pileLane.size(); i++) {
		int j = 0;
		for (auto itr = pileLane[i].begin(); itr != pileLane[i].end(); itr++) {
			itr->setCenter(Vector3f(-boundaryX + (TILELEN * ((float)i + 0.5f)), -boundaryY + (TILELEN * ((float)j + 0.5f)), 0));
			j++;
		}
	}
}

void pushPileLane(const Sphere& sph) {
	Sphere insertSph(sph);
	int laneNum = sph.getLane();
	int elementInLane = pileLane[laneNum].size();

	insertSph.setCenter(Vector3f(-boundaryX + (TILELEN * ((float)laneNum + 0.5f)), -boundaryY + (TILELEN * ((float)elementInLane + 0.5f)), 0));
	pileLane[laneNum].push_back(insertSph);
}

void idle() {
	if (Stage == 0) {
		end_clock = clock();
		if (end_clock - start_clock > 10000.0f/(float)fps) {
		for (auto itr = startPageSphs.begin(); itr != startPageSphs.end(); itr++) {
			int randNum = genRandColorNum(10);
			itr->setColor(randNum);
			itr->setAmbient(genRandAmbient(itr->getColor()));
			start_clock = end_clock;
		}
	}
	}

	if (!pause) {
		end_clock = clock();
		if (end_clock - start_clock > 1000.0f/(float)fps) {
			stageCheck();
			if (failCondition()) {
				for (auto itr = scoreBoard.begin(); itr != scoreBoard.end(); itr++) {
					if (*itr < Score) {
						scoreBoard.insert(itr, Score);
						break;
					}
				}
				Stage = -1;
				pause = true;
				return;
			}
			
			if ((!movingFirst) && (!movingSecond)) {
				if(!removeFalling) detectPop();
				if (removing) {
					if (removingTime < 4) {
						for (auto itr = removeCoord.begin(); itr != removeCoord.end(); itr++) {
							int xCoord = (*itr)[0];
							int yCoord = (*itr)[1];
							pileLane[xCoord][yCoord].setAmbient(0.7f * pileLane[xCoord][yCoord].getAmbient());
						}
						removingTime++;
					}
					else {
						while (!removeCoord.empty()) {
							int xCoord = removeCoord.back()[0];
							int yCoord = removeCoord.back()[1];

							removeCoord.pop_back();
							pileLane[xCoord].erase(pileLane[xCoord].begin() + yCoord);
							Score += 10;
						}
						removingTime = 0;
						removing = false;
						removeFalling = true;
					}
				}
				else if (removeFalling) {
					bool noFall = true;
					for (int i = 0; i < pileLane.size(); i++) {
						int j = 0;
						for (auto itr = pileLane[i].begin(); itr != pileLane[i].end(); itr++) {
							if (itr->getCenter()[1] > -boundaryY + (TILELEN * ((float)j + 0.6f))) {
								itr->move();
								noFall = false;
							}
							j++;
						}
					}
					if (noFall) {
						alignPile();
						removeFalling = false;
					}

				}
				else {
					alignPile();
					if (pileCollision() == 3) {
						if (currPair.getFirstSphere().getLane() == currPair.getSecondSphere().getLane()) {
							if (currPair.getFirstSphere().getCenter()[1] < currPair.getSecondSphere().getCenter()[1]) {
								pushPileLane(currPair.getFirstSphere());
								pushPileLane(currPair.getSecondSphere());
							}
							else {
								pushPileLane(currPair.getSecondSphere());
								pushPileLane(currPair.getFirstSphere());
							}
						}
						else {
							pushPileLane(currPair.getFirstSphere());
							pushPileLane(currPair.getSecondSphere());
						}
						currPair = nextPair;
						currPair.modFirstSphere().setCenter(Vector3f(-TILELEN / 2, boundaryY - TILELEN / 2, 0));
						currPair.modSecondSphere().setCenter(Vector3f(TILELEN / 2, boundaryY - TILELEN / 2, 0));

						alignPile();
						generateNextPair();
					}
					else if (pileCollision() == 1) {
						pushPileLane(currPair.getFirstSphere());
						currPair.modSecondSphere().setVelocity(2 * currPair.getSecondSphere().getVelocity());
						movingSecond = true;
					}
					else if (pileCollision() == 2) {
						pushPileLane(currPair.getSecondSphere());
						currPair.modFirstSphere().setVelocity(2 * currPair.getFirstSphere().getVelocity());
						movingFirst = true;
					}
					else currPair.move();
				}
			}
			if (movingSecond) {
				int sphRadius = TILELEN / 2;
				float lower = currPair.getSecondSphere().getCenter()[1] - (float)sphRadius;
				int laneNum = currPair.getSecondSphere().getLane();

				if (-boundaryY >= lower || ((!pileLane[laneNum].empty()) && pileLane[laneNum].back().getCenter()[1] + (float)sphRadius >= lower)) {
					currPair.modSecondSphere().setVelocity(0.5f * currPair.getSecondSphere().getVelocity());
					pushPileLane(currPair.getSecondSphere());
					currPair = nextPair;
					currPair.modFirstSphere().setCenter(Vector3f(-TILELEN / 2, boundaryY - TILELEN / 2, 0));
					currPair.modSecondSphere().setCenter(Vector3f(TILELEN / 2, boundaryY - TILELEN / 2, 0));

					alignPile();
					generateNextPair();

					movingSecond = false;

				}
				else currPair.modSecondSphere().move();
			}
			if (movingFirst) {
				int sphRadius = TILELEN / 2;
				float lower = currPair.getFirstSphere().getCenter()[1] - (float)sphRadius;
				int laneNum = currPair.getFirstSphere().getLane();

				if (-boundaryY >= lower || ((!pileLane[laneNum].empty()) && pileLane[laneNum].back().getCenter()[1] + (float)sphRadius >= lower)) {
					currPair.modFirstSphere().setVelocity(0.5f * currPair.getFirstSphere().getVelocity());
					pushPileLane(currPair.getFirstSphere());
					currPair = nextPair;
					currPair.modFirstSphere().setCenter(Vector3f(-TILELEN / 2, boundaryY - TILELEN / 2, 0));
					currPair.modSecondSphere().setCenter(Vector3f(TILELEN / 2, boundaryY - TILELEN / 2, 0));

					alignPile();
					generateNextPair();

					movingFirst = false;
				}
				else currPair.modFirstSphere().move();
			}
			start_clock = end_clock;
		}
		
	}
	glutPostRedisplay();
}

void display() {
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw 3D
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(light.getID());
	light.draw();
	glPushMatrix();

	if (!stageChanging && (Stage > 0 && Stage < 4)) drawSquareWithTexture();

	glPushMatrix();
	if (Stage == 0) {
		displayCharacters(GLUT_BITMAP_HELVETICA_18, "Press space bar to start", -100, -100);
		displayCharacters(GLUT_BITMAP_HELVETICA_18, "2016-14043", 0, -180);
		displayCharacters(GLUT_BITMAP_HELVETICA_18, "LEE JUNYOUNG", 0, -200);
	}
	else if (Stage == -1) {
		displayCharacters(GLUT_BITMAP_HELVETICA_18, "Game Over", -50, 0);
		displayCharacters(GLUT_BITMAP_HELVETICA_18, "Press space bar to restart", -110, -100);
		displayCharacters(GLUT_BITMAP_TIMES_ROMAN_24, "[ HALL OF FAME ]", -100, 200);
		displayCharacters(GLUT_BITMAP_HELVETICA_18, "1. " + to_string(scoreBoard[0]), -30, 160);
		displayCharacters(GLUT_BITMAP_HELVETICA_18, "2. " + to_string(scoreBoard[1]), -30, 140);
		displayCharacters(GLUT_BITMAP_HELVETICA_18, "3. " + to_string(scoreBoard[2]), -30, 120);
	}
	if (stageChanging && Stage == 1) {
		displayCharacters(GLUT_BITMAP_HELVETICA_18, "Stage 1 Clear!", -60, 0);
		displayCharacters(GLUT_BITMAP_HELVETICA_18, "Press space bar to continue", -110, -100);
	}
	if (stageChanging && Stage == 2) {
		displayCharacters(GLUT_BITMAP_HELVETICA_18, "Stage 2 Clear!", -60, 0);
		displayCharacters(GLUT_BITMAP_HELVETICA_18, "Press space bar to continue", -110, -100);
	}
	if (stageChanging && Stage == 3) {
		displayCharacters(GLUT_BITMAP_HELVETICA_18, "Game Clear!", -60, 0);
		displayCharacters(GLUT_BITMAP_HELVETICA_18, "Press space bar to restart", -105, -100);
		displayCharacters(GLUT_BITMAP_TIMES_ROMAN_24, "[ HALL OF FAME ]", -100, 200);
		displayCharacters(GLUT_BITMAP_HELVETICA_18, "1. " + to_string(scoreBoard[0]), -30, 160);
		displayCharacters(GLUT_BITMAP_HELVETICA_18, "2. " + to_string(scoreBoard[1]), -30, 140);
		displayCharacters(GLUT_BITMAP_HELVETICA_18, "3. " + to_string(scoreBoard[2]), -30, 120);
	}
	glPopMatrix();

	if (Stage == 0) {
		for (auto itr = startPageSphs.begin(); itr != startPageSphs.end(); itr++) {
			itr->draw();
		}
	}

	if (Stage > 0 && !stageChanging) {
		displayCharacters(GLUT_BITMAP_HELVETICA_18, "STAGE: " + to_string(Stage), -boundaryX - 20, boundaryY + 50);
		displayCharacters(GLUT_BITMAP_HELVETICA_18, "SCORE: " + to_string(Score), -boundaryX - 20, boundaryY + 30);
		displayCharacters(GLUT_BITMAP_HELVETICA_18, "SPACE BAR: DROP", -boundaryX - 20, -boundaryY - 20);
		displayCharacters(GLUT_BITMAP_HELVETICA_18, "'P': PAUSE", -boundaryX - 20, -boundaryY - 40);
		displayCharacters(GLUT_BITMAP_HELVETICA_18, "'F': FPS CONTROL (" + to_string(fps) + " fps)", -boundaryX - 20, -boundaryY - 60);
		
		for (auto i = 0; i < pileLane.size(); i++) {
			for (auto itr = pileLane[i].begin(); itr != pileLane[i].end(); itr++) {
				itr->draw();
			}
		}

		currPair.draw();
		nextPair.draw();
	}
	glPopMatrix();
	glDisable(light.getID());
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);

	glutSwapBuffers();
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);

	float wRatio = (float)w / WIDTH;
	float hRatio = (float)h / HEIGHT;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-WIDTH/2 * wRatio, WIDTH/2 * wRatio, -HEIGHT/2 * hRatio, HEIGHT/2 * hRatio, -100.0, 100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char** argv) {
	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(650, 0);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Puyopuyo by Junyoung Lee");
	initialize();

	// register callbacks
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboardDown);
	glutSpecialFunc(specialKeyDown);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 0;
}