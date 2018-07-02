#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/wait.h>

#include "define.h"

int main()
{
 int sockfd,new_fd;
 struct sockaddr_in my_addr;
 struct sockaddr_in new_addr;
 int size;
 
 if((sockfd=socket(AF_INET,SOCK_STREAM,0))<0)
 {
  perror("sock init error!\n");
  exit(1);
 }
 my_addr.sin_family=AF_INET;
 my_addr.sin_port=htons(PORT);
 my_addr.sin_addr.s_addr=INADDR_ANY;
 bzero(&(my_addr.sin_zero),sizeof(struct sockaddr_in));
 
 if(bind(sockfd,(struct sockaddr *)&my_addr,sizeof(struct sockaddr))<0)
 {
  perror("bind error!\n");
  exit(2);
 }
 if(-1==listen(sockfd,MAX))
 {
  perror("listen error!\n");
  exit(3);
 }

 

 while(1)
 {
  size=sizeof(struct sockaddr_in);
  if(-1==(new_fd=accept(sockfd,(struct sockaddr *)&new_addr,&size)))
  {
   perror("accept error!\n");
   continue;
  }
  printf("connect from client\n");
  if(!fork())
  {
   if(-1==send(new_fd,SERVER_GREET,sizeof(SERVER_GREET),0))
   {
    perror("send error!\n");
   }
   close(new_fd);
   exit(0);
  }
 }
 close(sockfd);
 //while(waitpid(-1,NULL,WTERMSIG)>0);
 return 0;
}
