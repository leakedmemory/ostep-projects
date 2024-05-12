#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc > 3) {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        return 1;
    }

    FILE *in_fd = stdin;
    FILE *out_fd = stdout;
    if (argc == 2) {
        in_fd = fopen(argv[1], "r");
        if (in_fd == NULL) {
            fprintf(stderr, "reverse: cannot open file '%s'\n", argv[1]);
            return 1;
        }
    } else if (argc == 3) {
        in_fd = fopen(argv[1], "r");
        if (in_fd == NULL) {
            fprintf(stderr, "reverse: cannot open file '%s'\n", argv[1]);
            return 1;
        }

        out_fd = fopen(argv[2], "w");
        if (out_fd == NULL) {
            fprintf(stderr, "reverse: cannot open file '%s'\n", argv[2]);
            return 1;
        }
    }

    if (fseek(in_fd, 0L, SEEK_END) == -1) {
        fprintf(stderr, "reverse: cannot set file position to the end\n");
        return 1;
    }

    if (memcmp(in_fd, out_fd, (size_t)ftell(in_fd)) == 0) {
        fprintf(stderr, "reverse: input and output file must differ\n");
        return 1;
    }

    size_t buf_size = 4096;
    char *buf = malloc(sizeof(char) * buf_size);
    if (buf == NULL) {
        fprintf(stderr, "malloc failed\n");
        return 1;
    }

    while (true) {
        if (ftell(in_fd) == 0L) {
            getline(&buf, &buf_size, in_fd);
            fprintf(out_fd, "%s", buf);
            break;
        } else if (fgetc(in_fd) == '\n') {
            ssize_t bytes_read = getline(&buf, &buf_size, in_fd);
            fprintf(out_fd, "%s", buf);
            fseek(in_fd, -(long)bytes_read - 2L, SEEK_CUR);
        } else {
            fseek(in_fd, -2L, SEEK_CUR);
        }
    }

    if (argc == 2) {
        fclose(in_fd);
    } else if (argc == 3) {
        fclose(in_fd);
        fclose(out_fd);
    }

    return 0;
}
