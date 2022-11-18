/*
*   A program célja megállapítani két játékosról,
        hogy játszottak-e egymás ellen mérkőzést.
*
*   3 szöveges fájlal dolgozunk.
*   - 1. A csapatok nevét és a játékos keretét tartalmazza.
*   - 2. A mérkőzések időpontjait és végkimenetelét tartalmazza.
*   - 3. Az átigazolásokat tartalmazza. ( Ki mikor honnan hova igazolt )
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 128
struct team {
    char* name;
    char* players;
};

struct matches{
    char* home;
    char* against;
};

const char filePaths[3][50] = {
    "./files/firstFile.txt",
    "./files/secondFile.txt",
    "./files/thirdFile.txt"
};


/*
*   Read all three files and create a linked list for each.
*/
void readFiles(void){
    FILE* file_ptr;
    char    *content;
    long    numbytes;
    for (size_t i = 0; i < 3; i++){
        char* path;
        strcpy(path,filePaths[i]);
        file_ptr = fopen(path, "r");
        if (NULL == file_ptr) {
            printf("%s can't be opened \n",path);
            continue;
        }
        // Print file content for now
        fseek(file_ptr, 0L, SEEK_END);
        numbytes = ftell(file_ptr);
        fseek(file_ptr, 0L, SEEK_SET);
        content = (char*)calloc(numbytes, sizeof(char));   
        
        if(content == NULL){
            printf("Failed to allocate enough space for the file content on path: %s \n",path);
            return;
        }
    
        fread(content, sizeof(char), numbytes, file_ptr);
        fclose(file_ptr);
        printf("\n****\n%s content: \n%s\n****\n",path,content);
    }
}

/*
*   Searching if the two names has played against each other or not.
*/
void searchMatch(char* nameOne,char* nameTwo){
    printf("Searching if %s has played against %s\n",nameOne,nameTwo);
}

/*
*   Waiting for two names from the standard input.
*/
void waitForNames(void){
    printf("Please enter two names separated by a \";\" character.\n");
    char inputNames[2][MAX_LINE_LENGTH];
    char* namesBuff_ptr = NULL;
    int bufferIndex = 0;
    size_t len = 0;
    size_t lineSize = 0;

    // Get the whole line from stdin
    lineSize = getline(&namesBuff_ptr, &len, stdin);
    if( lineSize > MAX_LINE_LENGTH ){
        printf("Line is bigger than the allocated buffer. Aborting.\n");
        return;
    }
    // Remove new line character from the buffer.
    if (namesBuff_ptr[lineSize - 1] == '\n'){
        namesBuff_ptr[lineSize - 1] = '\0';
    }

    // Loop trought the entered string
    // Search for ";" delimeter character.
    int nameCharIndex = 0;
    int found = 0;
    for (size_t i = 0; i < lineSize; i++){
        if (namesBuff_ptr[i] == ';') {
            found = 1;
            bufferIndex = 1;
            nameCharIndex = 0;
            continue;
        }
        inputNames[bufferIndex][nameCharIndex] = namesBuff_ptr[i];
        nameCharIndex++;
    }
    free(namesBuff_ptr);
    if(!found){
        printf("Search aborted. You must enter two names separated by a \";\" character.\n");
        return;
    }
    searchMatch(inputNames[0],inputNames[1]);
}

int main(void){
    readFiles();
    while(1){
        waitForNames();
    }
    return 0;
}