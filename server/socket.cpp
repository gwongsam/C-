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

int g_sockfd = 0;
void StopServerRunning(int p)
{
    close(g_sockfd);
    printf("\nClose Server\n");
    exit(0);
}

class Server
{
public:
    friend void StopServerRunning(int p);
    int Launch()
    {
        if (CreateSocket() != 0)
        {
            return -1;
        }
        if (BindPort() != 0)
        {
            return -1;
        }
        if (Connent() != 0)
        {
            return -1;
        }
        if (Listening() != 0)
        {
            return -1;
        }
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
        g_sockfd = sockfd;
        return 0;
    }
    int BindPort()
    {
        bzero(&servaddr, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
        servaddr.sin_port = htons(9000);
        if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)))
        {
            printf("Bind error(%d):%s\n", errno, strerror(errno));
            return -1;
        }

        return 0;
    }
    int Connent()
    {
        if (listen(sockfd, 2048))
        {
            printf("Listen error(%d): %s\n", errno, strerror(errno));
            return -1;
        }

        return 0;
    }
    int Listening()
    {
        printf("Listening...\n");

        while (true)
        {
            signal(SIGINT, StopServerRunning);
            int connfd = accept(sockfd, NULL, NULL);
            if (connfd == -1)
            {
                printf("Accept error(%d): %s\n", errno, strerror(errno));
                return -1;
            }
            bzero(buff, 1024);
            recv(connfd, buff, 1023, 0);
            printf("Recv: %s\n", buff);
            send(connfd, buff, strlen(buff), 0);
            close(connfd);
        }
        //close(connfd);
        return 0;
    }
    int Terminate()
    {
        close(sockfd);
        printf("Close Server\n");
        return 0;
    }

    int sockfd = 0;
    //int connfd = 0;
    char buff[1024];
    struct sockaddr_in servaddr;
};

int main()
{
    Server myserver;
    myserver.Launch();
    return 0;
}