#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/wait.h>

#include "define.h"

int
main ()
{
  int sockfd, numbytes;
  char buff[MAXDATASIZE];
  struct hostent *server;
  struct sockaddr_in server_addr;
  if (-1 == (sockfd = socket (AF_INET, SOCK_STREAM, 0)))
    {
      perror ("sock init error!\n");
      exit (1);
    }

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons (PORT);
  server_addr.sin_addr.s_addr = inet_addr (SERVER_IP);

  bzero (&(server_addr.sin_zero), sizeof (struct sockaddr_in));

  if (-1 ==
      connect (sockfd, (struct sockaddr *) &server_addr,
	       sizeof (struct sockaddr)))
    {
      perror ("connect error!\n");
      exit (1);
    }

  if (-1 == (numbytes = recv (sockfd, buff, MAXDATASIZE, 0)))
    {
      perror ("recv error!\n");
      exit (2);
    }

  buff[numbytes] = '\0';

  printf ("%s\n", buff);

  return 0;
}
