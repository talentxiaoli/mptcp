#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
const int DEST_PORT = 6666;

int main(int argc, char* argv[]) {
    char buf[1024] = "hehehe";
    struct sockaddr_in caddr;
    int cfd = socket(AF_INET, SOCK_STREAM, 0);
    if (cfd == -1) {
        printf("create client socket failed");
        return -1;
    }
    caddr.sin_family = AF_INET;
    caddr.sin_addr.s_addr = inet_addr(DEST_IP);
    caddr.sin_port = htons(DEST_PORT);
    int conn = connect(cfd, (struct sockaddr*)&caddr, sizeof(caddr));
    while (1) {

    }
    printf("conn = %d", conn);
    send(cfd, buf, strlen(buf), 0);
    close(cfd);
    return 0;
}