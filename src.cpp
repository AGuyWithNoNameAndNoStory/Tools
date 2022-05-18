#include <stdio.h>
#include <io.h>
#include <string>
using namespace std;
#pragma warning(disable:4996)£»

int main()
{
    int count = 0;
    char Filename[100], Performer[50], Title[100];
    printf("filename:");
    gets_s(Filename);
    char* str1 = (char*)malloc(100);
    strcpy(str1, Filename);
    strcat(str1, ".cue");
    FILE *fpWrite = fopen(str1, "w"); //create the file

    if (fpWrite == NULL) return 0;
    // fixed format of .cue file
    printf("performer:");
    gets_s(Performer);
    printf("title:");
    gets_s(Title);
    fprintf(fpWrite, "PERFORMER \"%s\"\n", Performer);
    fprintf(fpWrite, "TITLE \"%s\"\n", Title);
    long handle;  //create the handle
    struct _finddata_t fileinfo; //struct of file information

    for (int i = 0; i < 3; i++) {
        const char* type[3] = { ".flac", ".mp3", ".ape" };  //the different type of audio files
        const char* addr = "*";
        char* str2 = (char*)malloc(1 + strlen(addr) + strlen(type[i]));
        strcpy(str2, addr);
        strcat(str2, type[i]);
        const char* to_search = str2;        

        handle = _findfirst(to_search, &fileinfo); //search the first audio files
        if (-1 == handle) return -1;
        // fixed format of .cue file
        fprintf(fpWrite, "FILE \"%s\" WAVE\n", fileinfo.name);
        string num;
        if (++count < 10) num = '0' + to_string(count);
        else num = to_string(count);
        fprintf(fpWrite, "    TRACK %s AUDIO\n", num.c_str());
        string name = fileinfo.name;
        string title = name.substr(0, strlen(name.c_str()) - strlen(type[i]));
        //printf("%s\n", title.c_str());
        fprintf(fpWrite, "    TITLE \"%s\"\n", title.c_str());
        fprintf(fpWrite, "    INDEX 01 00:00:00\n");
    
        //printf("%s\n", fileinfo.name); //print the file name
        while (!_findnext(handle, &fileinfo)) //search other audio files
        {
            // fixed format of .cue file
            fprintf(fpWrite, "FILE \"%s\" WAVE\n", fileinfo.name);
            string num;
            if (++count < 10) num = '0' + to_string(count);
            else num = to_string(count);
            fprintf(fpWrite, "    TRACK %s AUDIO\n", num.c_str());
            string name = fileinfo.name;
            string title = name.substr(0, strlen(name.c_str()) - strlen(type[i]));
            fprintf(fpWrite, "    TITLE \"%s\"\n", title.c_str());
            fprintf(fpWrite, "    INDEX 01 00:00:00\n");
            //printf("%s\n", fileinfo.name); //print the file name
        }
    }
    fclose(fpWrite); //save the file
    _findclose(handle); //close the handle
    return 0;
}

    
