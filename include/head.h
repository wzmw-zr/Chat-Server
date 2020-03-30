/*************************************************************************
	> File Name: include/head.h
	> Author:赵睿 
	> Mail: 1767153298@qq.com
	> Created Time: 2020年03月30日 星期一 10时37分57秒
 ************************************************************************/

#ifndef _INCLUDE/HEAD_H
#define _INCLUDE/HEAD_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <arpa/inet.h>
int check(char *line, char *key);
char *split_value(char *line);
char *get_value(char *path, char *key);
int GetSocket();

typedef struct User {
    char name[100];
    int sockfd;
    pthread_t tid;
    struct User *next;
} User;

typedef struct UserMsg {
    char name[100];
    int type, size;
    char filename[256];
    char data[1024];
} UserMsg;

#endif
