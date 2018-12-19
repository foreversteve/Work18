#include "pipe_networking.h"


char *strrev(char *str){
    char *p1, *p2;

    if (! str || ! *str)
        return str;
    for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2){
        *p1 ^= *p2;
        *p2 ^= *p1;
        *p1 ^= *p2;
    }
    return str;
}

static void sighandler(int signo){
	if (signo == SIGINT){
		remove("WKP");
		exit(0);
	}
}

int main() {

  int to_client;
  int from_client;

  signal(SIGINT,sighandler);

  from_client = server_handshake( &to_client );

  char received[100];
  	while (1){
	  int f;
	  f = fork();
	  if (!f){
	    while(1){
	      
	      read(from_client,received,sizeof(received));
	      printf("Reversing client's message...\n");
	      //Scramble
	   //    char temp = received[0];
		  // char *a = received;
		  // strcat(a,"\0");
		  // printf("%s\n",a);
		  // while(*(a+1)){
		  // 	*a = *(a+1);
		  // 	a+=1;
		  // }
		  // received[0] = *a;
		  char *temp = strrev(received);
		  temp+=1;
		  strcat(temp,"\n");
		  // strcpy(received,temp);
	      printf("Message after edit was: %s\n",received);
	      write(to_client,temp,100);
	    }
	  }
	  else{
	      int status;
	      int pid = wait(&status);
	      printf("Resetting server from another connection...\n\n");
	      from_client = server_handshake( &to_client );
	  }
	}
}
