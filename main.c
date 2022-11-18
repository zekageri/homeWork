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
    FILE* ptr;
    char ch;
    for (size_t i = 0; i < 3; i++){
        char* path;
        strcpy(path,filePaths[i]);
        ptr = fopen(path, "r");
        if (NULL == ptr) {
            printf("%s can't be opened \n",path);
            continue;
        }
        // Print file content for now
        do {
            ch = fgetc(ptr);
            printf("%c", ch);
        } while (ch != EOF);
        // close the file.
        fclose(ptr);
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
    char inputNames[2][128];
    char* namesBuff_ptr = NULL;
    int bufferIndex = 0;
    size_t len = 0;
    size_t lineSize = 0;

    // Get the whole line from stdin
    lineSize = getline(&namesBuff_ptr, &len, stdin);

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