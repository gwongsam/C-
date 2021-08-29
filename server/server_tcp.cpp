#include <cstdio>
#include <netinet/in.h>
#include <sys/errno.h>
#include <cstring>
#include <signal.h>
#include <unistd.h>
#include <cstdlib>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/unistd.h>

#define BUFFSIZE 2048
#define DEFAULT_PORT 16552
#define MAXLINK 2048

//  void stopServerRunning(int p)
//     {
//         close(sockfd);
//         printf("Close Server\n");
//         exit(0);
//     }

class Server
{
public:
    int TurnOn()
    {
        CreateSocket();
        SetIpPort();
        SetListen();
        return 0;
    }

protected:
    int CreateSocket()
    {
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd == -1)
        {
            return -1;
        }
        return 0;
    }
    int SetIpPort()
    {
        bzero(&servaddr, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
        servaddr.sin_port = htons(DEFAULT_PORT);
        if (bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)))
        {
            printf("Bind error(%d): %s\n", errno, strerror(errno));
            return -1;
        }
        return 0;
    }
    int SetListen()
    {
        if (listen(sockfd, MAXLINK))
        {
            printf("Listen error(%d): %s\n", errno, strerror(errno));
            return -1;
        }
        printf("Listening...\n");
        while (true)
        {
            //signal(SIGINT, stopServerRunning);
            connfd = accept(sockfd, NULL, NULL);
            if (connfd == -1)
            {
                printf("Accept error(%d): %s\n", errno, strerror(errno));
                return -1;
            }
            bzero(buff, BUFFSIZE);
            recv(connfd, buff, BUFFSIZE - 1, 0);
            printf("Recv: %s\n", buff);
            send(connfd, buff, strlen(buff), 0);
            close(connfd);
        }
        
        return 0;
    }
   
    void StopServerRunning(int p)
    {
        close(sockfd);
        printf("Close Server\n");
        exit(0);
    }

private:
    int sockfd = 0;
    int connfd = 0;
    char buff[BUFFSIZE];
    struct sockaddr_in servaddr;
};

int main()
{
    Server services;
    services.TurnOn();
    return 0;
}