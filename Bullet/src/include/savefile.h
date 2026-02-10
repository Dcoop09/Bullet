#pragma once

typedef struct
{
    //e.g. Game Title
    char* title;
    //https://www.psdevwiki.com/ps3/TITLE_ID#Other_TITLE_IDs for more info
    char* gameSerial;
    //paragraph or something
    char* info;
    //picture in the menu (Icon0)
    void* iconPicture;
    int iconPictureSize;
    //In background when focused on file (Pic1)
    void* backgroundPicture;
    int backgroundPictureSize;
    //animation? (no support(what's a .pmf file?)) would be icon1
    void* data;
    int dataSize;
}Savefile;

void saveSavefile(Savefile save);

void openSavefile(Savefile save);