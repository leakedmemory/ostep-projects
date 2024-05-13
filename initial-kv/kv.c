// needed to use `strdup`
#define _POSIX_C_SOURCE 200809L

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define DATABASE "kv.db"

// list of commands
#define PUT "p"
#define GET "g"
#define DELETE "d"
#define CLEAR "c"
#define ALL "a"

typedef struct {
    char *command;
    int key;
    char *value;
} Input;

int main(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        char *input[3];
        size_t input_len = 0;

        const char *delim = ",\n";
        char *tk = strtok(argv[i], delim);
        while (tk) {
            input[input_len++] = tk;
            tk = strtok(NULL, delim);
        }

        // assuming that the key of the inputs will always the different
        if (strcmp(input[0], PUT) == 0) {
            FILE *db = fopen(DATABASE, "a");
            if (db == NULL) {
                fprintf(stderr, "kv: cannot access database\n");
                return 1;
            }

            fprintf(db, "%s,%s\n", input[1], input[2]);
            fclose(db);
        } else if (strcmp(input[0], GET) == 0) {
            FILE *db = fopen(DATABASE, "r");
            if (db == NULL) {
                fprintf(stderr, "kv: cannot access database\n");
                return 1;
            }

            size_t buf_size = 4096;
            char *buf = malloc(sizeof(char) * buf_size);
            if (buf == NULL) {
                fprintf(stderr, "kv: malloc failed\n");
                return 1;
            }

            bool found = false;
            while (getline(&buf, &buf_size, db) != -1) {
                char *key = strtok(buf, ",");
                if (strcmp(input[1], key) == 0) {
                    printf("%s,%s\n", key, buf);
                    found = true;
                    break;
                }
            }
            if (!found) {
                printf("%s not found\n", input[1]);
            }

            free(buf);
            fclose(db);
        } else if (strcmp(input[0], DELETE) == 0) {
            FILE *db = fopen(DATABASE, "r");
            if (db == NULL) {
                fprintf(stderr, "kv: cannot access database\n");
                return 1;
            }

            size_t buf_size = 4096;
            char *buf = malloc(sizeof(char) * buf_size);
            if (buf == NULL) {
                fprintf(stderr, "kv: malloc failed\n");
                return 1;
            }

            char *new_db_path = "temp.db";
            FILE *new_db = fopen(new_db_path, "w");
            if (new_db == NULL) {
                fprintf(stderr, "kv: error while deleting\n");
                return 1;
            }

            bool found = false;
            while (getline(&buf, &buf_size, db)) {
                char *key = strtok(buf, ",");
                if (strcmp(input[1], key) != -1) {
                    found = true;
                } else {
                    fprintf(new_db, "%s", buf);
                }
            }

            if (found) {
                char *const mv = "/bin/mv";
                char *const args[] = {mv, "-f", new_db_path, DATABASE, NULL};
                execv(mv, args);
            } else {
                printf("%s not found\n", input[1]);
                char *const rm = "/bin/rm";
                char *const args[] = {rm, "-f", new_db_path, NULL};
                execv(rm, args);
            }

            free(buf);
            fclose(db);
        } else if (strcmp(input[0], CLEAR) == 0) {
            fclose(fopen(DATABASE, "w"));
        } else {
            FILE *db = fopen(DATABASE, "r");
            if (db == NULL) {
                fprintf(stderr, "kv: cannot access database\n");
                return 1;
            }

            size_t buf_size = 4096;
            char *buf = malloc(sizeof(char) * buf_size);
            if (buf == NULL) {
                fprintf(stderr, "kv: malloc failed\n");
                return 1;
            }

            while (getline(&buf, &buf_size, db) != -1) {
                printf("%s", buf);
            }

            free(buf);
            fclose(db);
        }
    }

    return 0;
}
