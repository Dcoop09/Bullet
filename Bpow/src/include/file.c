#include <string.h>
#include <malloc.h>
#include <cmake_config.h>
#include "file.h"
#include "logger.h"

#define FILE_CHAR_LIMIT 20

//FILE CHAR LIMIT + the path size
char textureFolder[FILE_CHAR_LIMIT + sizeof(TEXTURE_FOLDER)] = TEXTURE_FOLDER;
char mp3Folder[FILE_CHAR_LIMIT + sizeof(AUDIO_FOLDER)] = AUDIO_FOLDER;
char assetFolder[FILE_CHAR_LIMIT + sizeof(ASSET_FOLDER)] = ASSET_FOLDER;

long getFileSize(FILE* file) 
{
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);
    return length;
}

void* openFile(const char* targetFile)
{
    FILE* file = fopen(strcat(assetFolder, targetFile), "r");
    if(!file) 
    {
        throwError("failed to locate %s\n", assetFolder);
        return NULL;
    }
    long fileSize = getFileSize(file);
    if(fileSize < 0)
    {
        throwError("failed to get size of %s\n", assetFolder);
        return NULL;
    }

    void* fileContents = malloc(fileSize);
    fread(fileContents, sizeof(char), fileSize, file);
    fclose(file);

    strcpy(assetFolder, ASSET_FOLDER);

    return fileContents;
}

void* openTexFile(const char* targetTex) 
{
    FILE* file = fopen(strcat(textureFolder, targetTex), "r");
    if(!file) 
    {
        throwError("failed to locate %s\n", textureFolder);
        return NULL;
    }
    long fileSize = getFileSize(file);
    if(fileSize < 0)
    {
        throwError("failed to get size of %s\n", textureFolder);
        return NULL;
    }
    print("%s\n", textureFolder);

    void* fileContents = malloc(fileSize);
    fread(fileContents, sizeof(char), fileSize, file);
    fclose(file);

    strcpy(textureFolder, TEXTURE_FOLDER);

    return fileContents;
}