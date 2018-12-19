#include "pipe_networking.h"


int main() {

  int to_client;
  int from_client;

  from_client = server_handshake( &to_client );

  char send[100];
  char receive[100];
  while(1){
    //Receiving Information
    from_client = server_handshake( &to_client );
    read(from_client, receive, sizeof(receive));
    close(from_client);

    //Modifies Information
    for(int i = 0;receive[i];i++){
      char c = receive[i] + 26;
      if((c > 90 && c < 97) || (c > 123)){
	c = c - 26;
      }
      send[i] = c;
    }
    
    //Sends Changed Information
    write(to_client, send, sizeof(send));
  }
}
