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

int getFileBuffer(char type, const char* targetFile) 
{
    FILE* file;
    switch (type)
    {
        case 0:
            file = fopen(targetFile, "r");
            break;
        case 1:
            file = fopen(strcat(mp3Folder, targetFile), "r");
            strcpy(mp3Folder, AUDIO_FOLDER);
            break;
        case 2:
            file = fopen(strcat(assetFolder, targetFile), "r");
            strcpy(assetFolder, ASSET_FOLDER);
            break;
        case 3:
            file = fopen(strcat(textureFolder, targetFile), "r");
            strcpy(textureFolder, TEXTURE_FOLDER);
            break;
        default:
            break;
    }
    if(!file) 
    {
        throwError("failed to locate %s\n", targetFile);
        return 0;
    }
    
    int buf = getFileSize(file);
    if(buf < 0)
    {
        throwError("failed to get size of %s\n", assetFolder);
        return 0;
    }
    fclose(file);
    return buf;
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