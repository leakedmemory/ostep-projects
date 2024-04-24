#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc == 1) {
        return 0;
    }

    for (int i = 1; i < argc; i++) {
        FILE *fd = fopen(argv[i], "r");
        if (fd == NULL) {
            printf("wcat: cannot open file\n");
            return 1;
        }

        char buf[4096];
        size_t bytes_read = 0;
        while ((bytes_read = fread(buf, sizeof(char), 4095, fd)) > 0) {
            buf[bytes_read] = '\0';
            printf("%s", buf);
        }

        fclose(fd);
    }

    return 0;
}
