#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include "monty.h"

int get_file(char *str) {
    char *line_buf = NULL, buff[10024], *b = buff;
    size_t line_bufsize = 0;
    int line_count = 0, i, j;
    ssize_t line_size = 0;
    FILE *fp = fopen(str, "r");

    if (!fp) {
        fprintf(stderr, "Error: Can't open file %s\n", str);
        exit(EXIT_FAILURE);
    }

    line_size = getline(&line_buf, &line_bufsize, fp);

    for (i = 0; i < 10024; i++)
        buff[i] = 0;

    while (line_size >= 0) {
        for (i = 0, j = 0; line_buf[i] && line_buf[i] != '\n'; i++) {
            if (line_buf[i] != ' ') {
                j++;
                break;
            }
        }

        if (line_buf[i] == '#') {
            line_size = getline(&line_buf, &line_bufsize, fp);
            line_count++;
            continue;
        }

        line_count++;

        if (j > 0) {
            clean_string(b, line_buf);
            create_instruction(&list_opcode, b, line_count, fp);
        }

        line_size = getline(&line_buf, &line_bufsize, fp);
    }

    free(line_buf);
    line_buf = NULL;
    fclose(fp);
    return line_count;
}
