#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define CTOI(c) ((c) - '0')

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("wunzip: file1 [file2 ...]\n");
        return 1;
    }

    for (int32_t i = 1; i < argc; i++) {
        FILE *fd = fopen(argv[i], "r");
        if (fd == NULL) {
            printf("wunzip: cannot open file\n");
            return 1;
        }

        const int32_t multiplier = 10;
        int32_t number = 0;
        bool was_number = false;
        char current;
        while ((current = fgetc(fd)) != EOF) {
            if (isdigit(current) && !was_number) {
                number = CTOI(current);
                was_number = true;
            } else if (isdigit(current) && was_number) {
                number = number * multiplier + CTOI(current);
            } else {
                for (int32_t i = 0; i < number; i++) {
                    printf("%c", current);
                }
                number = 1;
                was_number = false;
            }
        }

        fclose(fd);
    }

    return 0;
}
