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

    if(fork() == 0){
      //Receiving Information
      while(read(from_client, receive, sizeof(receive)) > 0){
	receive[strlen(receive)] = '\0';
	printf("recieved info : %s\n", receive);
    
	//Modifies Information
	for(int i = 0;receive[i];i++){
	  int c = receive[i];
	  if((c >= 65 && c <= 77) || (c >= 97 && c <= 109)){
	    c+= 13;
	  }else if((c >= 78 && c <= 90) || (c >= 110 && c <= 122)){
	    c -= 13;
	  }
	  send[i] = c;
	}
	//printf("modified info : %s\n", receive);
    
	//Sends Changed Information
	write(to_client, send, sizeof(send));
      }
      printf("error %d\n", errno);
    }else{

    }
  }
  return 0;
}
