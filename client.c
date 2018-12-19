#include "pipe_networking.h"


int main() {

  int to_server;
  int from_server;

  from_server = client_handshake( &to_server );

  char send[100];
  char receive[100];
  while(1){
    //Sending Information
    printf("%s\n", "input what you want to send");
    scanf("%[^\n]s\n",send);
    write(to_server, send, sizeof(send));

    //Receives Changed Information
    from_server = client_handshake( &to_server );
    read(from_server, receive, sizeof(receive));
    close(from_server);

    printf("Message received : %s\n", receive);
  }
}
