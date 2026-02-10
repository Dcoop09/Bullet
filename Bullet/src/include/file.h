#pragma once
#include <stdio.h>

#define BASICFILE 0
#define AUDIOFILE 1
#define ASSETFILE 2
#define TEXTUREFILE 3

//looks for file in asset folder and returns it's contents
void* openFile(const char* targetFile);

void* openTexFile(const char* targetTex);

int getFileBuffer(char type, const char* targetFile);
