#define PORT 3490
#define MAX  10
#define MAXDATASIZE 128
#define SERVER_GREET "hi,from server!"
#define SERVER_IP "127.0.0.1"

#include <arpa/inet.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close
