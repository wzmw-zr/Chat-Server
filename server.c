#include "./include/head.h"
#include "./include/tcp_server.h"

char *path = "./server.conf";

void *test(void *arg) {
    int fd = *(int *)arg;
    while (1) {
        char word[100];
        int len = sizeof(word);
        if (recv(fd, word, len, 0) <= 0) {
            perror("recv");
            return NULL;
        }
        printf("%s\n", word);
    }
    return NULL;
}

int main() { 
    int port = atoi(get_value(path, "PORT"));
    int sockfd = GetSocket();
    BindAndListen(sockfd, port);
    while (1) {
        int fd;
        pthread_t tid;
        if ((fd = accept(sockfd, NULL, NULL)) == -1) {
            perror("accept");
            continue;
        }
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
        pthread_create(&tid, &attr, test, &fd);
    }
    return 0; 
}
