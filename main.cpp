#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <iostream>
#include "Handler.cpp"
#include <pthread.h>
#include "Init.cpp"
#include "ConstString.h"



int main()
{
  Init::init();
  int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
  if(sock_fd < 0)
  {
    perror("socket");
    exit(1);
  }

  struct sockaddr_in addr_serv;
  int len;
  memset(&addr_serv, 0, sizeof(struct sockaddr_in));
  addr_serv.sin_family = AF_INET;
  addr_serv.sin_port = htons(SERV_PORT);
  addr_serv.sin_addr.s_addr = inet_addr(SERVICE_IP);
  len = sizeof(addr_serv);

  if(bind(sock_fd, (struct sockaddr *)&addr_serv, sizeof(addr_serv)) < 0)
  {
    perror("bind error:");
    exit(1);
  }


  int recv_num;
  char recv_buf[10240];
  struct sockaddr_in addr_client;

  while(1)
  {
    printf("server wait:\n");

    recv_num = recvfrom(sock_fd, recv_buf, sizeof(recv_buf), 0, (struct sockaddr *)&addr_client, (socklen_t *)&len);

    if(recv_num < 0)
    {
      perror("recvfrom error:");
      exit(1);
    }

    recv_buf[recv_num] = '\0';
    printf("server receive %d bytes: %s\n", recv_num, recv_buf);

    Uri uri(recv_buf);
    pthread_t tid;
    int ret = pthread_create(&tid,NULL,Handler::handle,(void*) (&uri));
    cout<<"thread " << ret << " was create to handle to task" << endl;
  }

  

  close(sock_fd);

  return 0;
}