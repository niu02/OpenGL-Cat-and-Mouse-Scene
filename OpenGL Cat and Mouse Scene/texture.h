#pragma once
#include <glad/glad.h> 
#include <iostream>
#include "bitmap.h"

GLuint setup_texture(const char* filename)
{
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	GLuint texObject;
	glGenTextures(1, &texObject);
	glBindTexture(GL_TEXTURE_2D, texObject);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	unsigned char* pxls = NULL;
	BITMAPINFOHEADER info;
	BITMAPFILEHEADER file;
	loadbitmap(filename, pxls, &info, &file);

	if (pxls != NULL)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, info.biWidth, info.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, pxls);

	}

	delete[] pxls;
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	return texObject;
}

GLuint setup_mipmaps(const char* filename[], int n)
{
	return 0;
}
