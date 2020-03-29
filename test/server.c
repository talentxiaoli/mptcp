#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

const int DEST_PORT = 6666;

int main(int argc, char* argv[]) {
    struct sockaddr_in saddr;
    struct sockaddr_in caddr;
    char recvBuf[1024];

    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1) {
        printf("create server socket failed");
        return ;
    }
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);
    saddr.sin_port = htons(DEST_PORT);
    int bindRes = bind(fd, (struct sockaddr*)&saddr, sizeof(saddr));
    if (bindRes == -1) {
        printf("bind ip and port failed");
        close(fd);
        return ;
    }

    int lisRes = listen(fd, 5);
    if (lisRes == -1) {
        printf("lisRes failed");
        close(fd);
        return ;
    }

    printf("start to recv client connect");
    int caddrlen = sizeof(struct sockaddr_in);
    while(1) {
        int cfd = accept(fd, (struct sockaddr*)&caddr, (socklen_t *)&caddrlen);

        printf("client ip = %s", inet_ntoa(caddr.sin_addr));
        printf("client port = %d", ntohs(caddr.sin_port));

        memset(recvBuf,0,sizeof(recvBuf));
        // 处理业务
        int len = -1;
        while((len = recv(cfd, recvBuf, sizeof(recvBuf),0)) > 0) {
            printf("client msg = %s", recvBuf);
        }

        close(cfd);
    }
    return 0;
}