/*************************************************************************
	> File Name: src/head.c
	> Author:赵睿 
	> Mail: 1767153298@qq.com
	> Created Time: 2020年03月30日 星期一 10时45分20秒
 ************************************************************************/

#include "../include/head.h"
int check(char *line, char *key) {
    if (strncmp(line, key, strlen(key)) || line[strlen(key)] != '=') return 0;
    return 1;
}

char *split_value(char *line) { 
    char *tmp = line;
    if (line[strlen(line) - 1] == '\n') line[strlen(line) - 1] = '\0';
    while (*line != '=') line++;
    char *ret = strdup(++line);
    free(tmp);
    return ret;
}

char *get_value(char *path, char *key) {
    char *value = (char *) calloc(sizeof(char), 100);
    FILE *fp;
    if ((fp = fopen(path, "r")) == NULL) {
        perror("fopen");
        exit(1);
    }
    char *line = NULL;
    size_t number = 0;
    while (getline(&line, &number, fp) != -1) {
        if (check(line, key)) break;
        free(line);
        line = NULL;
        number = 0;
    }
    if (!line) return NULL;
    return split_value(line);
}

int GetSocket() {
    int socketfd;
    if ((socketfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }
    return socketfd;
}

