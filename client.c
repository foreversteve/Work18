#include "pipe_networking.h"


int main() {

  int to_server;
  int from_server;

  from_server = client_handshake( &to_server );
  //Getting data
  char input[100];
  char received[100];
  while(1){
    printf("Enter data for server: ");
    fgets(input,sizeof(input),stdin);
    //Writing data:
    write(to_server,input,sizeof(input));
    read(from_server,received,sizeof(received));
    printf("Server says: %s",received);
  }
}
