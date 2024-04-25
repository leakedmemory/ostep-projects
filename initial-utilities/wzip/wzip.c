#include <stdint.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("wzip: file1 [file2 ...]\n");
        return 1;
    }

    for (int32_t i = 1; i < argc; i++) {
        FILE *fd = fopen(argv[i], "r");
        if (fd == NULL) {
            printf("wzip: cannot open file");
            return 1;
        }

        int32_t count = 0;
        char last = 0;
        char current;
        while ((current = fgetc(fd))) {
            if (current != '\n' && (current == last || count == 0)) {
                count++;
            } else if (last != '\n') {
                printf("%d%c", count, last);
                count = 1;
            } else if (current == EOF) {
                break;
            } else {
                count = 1;
            }

            if (current == '\n') {
                printf("\n");
                count = 1;
            }

            last = current;
        }

        fclose(fd);
    }

    return 0;
}
