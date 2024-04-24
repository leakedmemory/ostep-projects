// needed for getline
#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("wgrep: searchterm [file ...]\n");
        return 1;
    }

    const char *term = argv[1];

    // match term with stdin
    if (argc == 2) {
        char buf[4096];
        while (fgets(buf, 4096, stdin) != NULL) {
            if (strstr(buf, term) != NULL) {
                printf("%s", buf);
            }
        }

        return 0;
    }

    size_t buf_size = 4096;
    char *buf = malloc(buf_size * sizeof(char));
    for (int i = 2; i < argc; i++) {
        FILE *fd = fopen(argv[i], "r");
        if (fd == NULL) {
            printf("wgrep: cannot open file\n");
            return 1;
        }

        while (getline(&buf, &buf_size, fd) != -1) {
            if (strstr(buf, term) != NULL) {
                printf("%s", buf);
            }
        }

        fclose(fd);
    }
    free(buf);

    return 0;
}
