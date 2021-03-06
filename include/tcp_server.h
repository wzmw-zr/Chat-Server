/*************************************************************************
	> File Name: include/tcp_server.h
	> Author:赵睿 
	> Mail: 1767153298@qq.com
	> Created Time: 2020年03月30日 星期一 10时50分11秒
 ************************************************************************/

#ifndef _INCLUDE_TCP_SERVER_H
#define _INCLUDE_TCP_SERVER_H

void BindAndListen(int sockfd, int port);

void *work(void *arg);
void ExistHandle(User *user);
void HandleMessage(User *user, UserMsg msg);
void Communicate(User *user);

int SearchUser(char *name);
void AddUser(User *user);
void DeleteUser(char *name);

extern User *start;
#endif
