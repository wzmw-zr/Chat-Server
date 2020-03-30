/*************************************************************************
	> File Name: src/tcp_server.c
	> Author:赵睿 
	> Mail: 1767153298@qq.com
	> Created Time: 2020年03月30日 星期一 10时51分36秒
 ************************************************************************/

#include "../include/head.h"
#include "../include/tcp_server.h"
#define LOCK pthread_mutex_lock(&mutex)
#define UNLOCK pthread_mutex_unlock(&mutex)
////////////////////////User Search, Add, Delete///////////////////////
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

User *start;

int SearchUser(char *name) {
    User *head = start;
    while (head->next && strcmp(name, head->next->name)) head = head->next;
    if (head->next) return 1;
    return 0;
}

void AddUser(User *user) {
    user->next = start->next;
    start->next = user;
}

void DeleteUser(char *name) {
    User *head = start;
    while (head->next && strcmp(name, head->next->name)) head = head->next;
    if (head->next) return ;
    User *tmp = head->next;
    head->next = tmp->next;
    free(tmp);
}

//////////////////////////// Pthread /////////////////////////////////

void ExistHandle(User *user) {
    int sockfd = user->sockfd;
    char message[100];
    sprintf(message, "%s has already logged in!\n", user->name);
    if (send(sockfd, message, strlen(message), 0) <= 0) perror("send");
    free(user);
    close(sockfd);
}

void HandleMessage(User *user, UserMsg msg) {
    if (msg.type == -1) {
        close(user->sockfd);
        DeleteUser(user->name);
    }
}

void Communicate(User *user) {
    int sockfd = user->sockfd, len;
    char message[100];
    sprintf(message, "Welcome! %s.\n", user->name);
    if (send(sockfd, message, strlen(message), 0) <= 0) perror("send");
    while (1) {
        UserMsg msg;
        int len = sizeof(msg);
        if (recv(sockfd, (void *) &msg, len, 0) <= 0) {
            perror("recv");
            break;
        }    
        HandleMessage(user, msg);
    }
    LOCK;
    DeleteUser(user->name);
    UNLOCK;
}

void *work(void *arg) {
    User *head = start;
    while (head->next) printf("%s ", head->next->name), head = head->next;
    printf("\n");
    User *user = (User *) arg; 
    int len = sizeof(user->name);
    if (recv(user->sockfd, user->name, len, 0) == -1) {
        perror("recv");
        close(user->sockfd);
        free(user);
        return NULL;
    }    
    printf("%s\n", user->name);
    LOCK;
    if (SearchUser(user->name)) {
        ExistHandle(user); 
        UNLOCK;
    } else {
        AddUser(user);
        UNLOCK;
        Communicate(user);
    }
    return NULL;
}


//////////////////////////// PreWork ////////////////////////////////

void BindAndListen(int sockfd, int port) { 
    struct linger val;
    val.l_onoff = 1;
    val.l_linger = 0; 
    if (setsockopt(sockfd, SOL_SOCKET, SO_LINGER, (void *) &val, (socklen_t ) sizeof(val)) == -1) {
        perror("setsockopt");
        exit(1);
    }
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = INADDR_ANY;
    if (bind(sockfd, (struct sockaddr *)&address, sizeof(address)) == -1) {
        perror("bind");
        exit(1);
    }
    if (listen(sockfd, 20) == -1) {
        perror("listen");
        exit(1);
    }
}

