#include "bf/brainfuck.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Nothing to run...");
        getchar();

        return 0;
    }

    char* buffer;
    FILE* file;
    
    if (fopen_s(&file, argv[1], "r") == 0) {
        int size = 0;

        fseek(file, 0, SEEK_END);
        size = ftell(file);
        fseek(file, 0, SEEK_SET);

        buffer = malloc(sizeof(char) * size);
        fread(buffer, sizeof(char), size, file);
        fclose(file);
    } else {
        buffer = argv[1];
    }

    bf_run(buffer);

    printf("\n");
    printf("Press any key to exit.. ");
    getchar();

    return 1;
}