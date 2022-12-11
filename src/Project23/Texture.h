#pragma once
#include <iostream>
#include <GL/glut.h>
#include <FreeImage.h>

class Texture
{
public:
	Texture();

	FIBITMAP* createBitMap(char const* filename);
	void generateTexture();
	void initializeTexture(char const* filename);

	GLuint getTextureID() const;

private:
	GLuint textureID;
	GLubyte* textureData;
	int imageWidth, imageHeight;
};

