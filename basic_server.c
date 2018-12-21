#include "pipe_networking.h"


int main() {

  int to_client;
  int from_client;

  char send[100];
  char receive[100];
  //char * send = malloc(sizeof(char*));
  //char * receive = malloc(sizeof(char*));
  while(1){
    from_client = server_handshake( &to_client );
    
    //Receiving Information
    while(read(from_client, receive, sizeof(receive))){
      receive[strlen(receive)] = '\0';
      printf("recieved info : %s\n", receive);
    
      //Modifies Information
      /*
	for(int i = 0;receive[i];i++){
	char c = receive[i] + 13;
	if((c > 90 && c < 97) || (c > 123)){
	c = c - 13;
	}
	send[i] = c;
	}
      */
      strcpy(send, receive);
      printf("modified info : %s\n", receive);
    
      //Sends Changed Information
      write(to_client, send, sizeof(send));
    }
  }
  return 0;
}
