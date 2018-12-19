#include "pipe_networking.h"


/*=========================
  server_handshake
  args: int * to_client

  Performs the client side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake(int *to_client) {
  //Creating well known pipe
  char private[10];
  mkfifo("WKP",0644);

  int public = open("WKP", O_RDONLY);
  printf("public pipe opened by server\n");

  read(public,private,4);//the message sent by client

  printf("message received from client was: %s\n",private);

  int p = open(private,O_WRONLY);
  printf("Server opened private pipe\n");
  write(p,ACK,sizeof(ACK));
  printf("Writting HOLA to client...\n");

  *to_client = p;
  printf("Handshake complete (server)\n");
  return public;
}


/*=========================
  client_handshake
  args: int * to_server

  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {

  char received[10];

  //Create Private Pipe
  mkfifo("P_P",0644);
  printf("Created private Pipe\n");
  // Open the public pipe
  int public = open("WKP",O_WRONLY);
  printf("client opened public pipe\n");
  //Write to server
  write(public,"P_P",4);

  //Declaring

  int private = open("P_P",O_RDONLY);
  printf("client opened private pipe\n");

  read(private,received,10);

  printf("Messaged Received From Server is: %s\n",received);

  //Setting to_server
  *to_server = public;
  printf("Handshake complete (client)\n");
  return private;
}




