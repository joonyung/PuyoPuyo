#include "Texture.h"

using namespace std;

Texture::Texture() {
	textureID = 0;
	textureData = 0;
	imageWidth = 0;
	imageHeight = 0;
}

FIBITMAP* Texture::createBitMap(char const* filename) {
	FREE_IMAGE_FORMAT format = FreeImage_GetFileType(filename, 0);

	if (format == -1) {
		exit(-1);
	}
	if (format == FIF_UNKNOWN) {
		format = FreeImage_GetFIFFromFilename(filename);

		if (!FreeImage_FIFSupportsReading(format)) {
			//cout << "Detected image format cannot be read!" << endl;
			exit(-1);
		}
	}

	FIBITMAP* bitmap = FreeImage_Load(format, filename);

	int bitsPerPixel = FreeImage_GetBPP(bitmap);

	FIBITMAP* bitmap32;
	if (bitsPerPixel == 32) {
		//cout << "Source image has " << bitsPerPixel << "bits per pixel. Skipping coversion." << endl;
		bitmap32 = bitmap;
	}
	else {
		//cout << "Source image has " << bitsPerPixel << "bits per pixel. Converting to 32-bit colour." << endl;
		bitmap32 = FreeImage_ConvertTo32Bits(bitmap);
	}

	return bitmap32;
}
void Texture::generateTexture() {
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, textureData);
}
void Texture::initializeTexture(char const* filename) {
	FIBITMAP* bitmap32 = createBitMap(filename);
	imageWidth = FreeImage_GetWidth(bitmap32);
	imageHeight = FreeImage_GetHeight(bitmap32);
	textureData = FreeImage_GetBits(bitmap32);

	generateTexture();

}
GLuint Texture::getTextureID() const {
	return textureID;
}
