#include "pipe_networking.h"


/*=========================
  server_handshake
  args: int * to_client

  Performs the server side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake(int *to_client) {
  mkfifo("ur_mum_gay", 0644);//WKP
  mkfifo("no_u", 0644);//Private Pipe
  
  char private_pipe[100];
  int pipe1 = open("ur_mum_gay", O_RDONLY);//Waiting for private pipe
  printf("%s\n", "recieving pipe...");
  read(pipe1, private_pipe, sizeof(private_pipe));
  printf("private_pipe : %s\n\n", private_pipe);
  close(pipe1);
  remove("ur_mum_gay");

  int pipe2 = open(private_pipe, O_WRONLY);//Sends file descriptor to client
  printf("%s\n", "sending...");
  write(pipe2, to_client, sizeof(to_client));
  printf("%s\n\n", "sent...");
  close(pipe2);

  int from_client[100];
  int pipe3 = open(private_pipe, O_RDONLY);//Receives file descriptor from client
  printf("%s\n", "recieving...");
  read(pipe3, from_client, sizeof(from_client));
  printf("%s\n", "received...");
  close(pipe3);

  return *from_client;
}


/*=========================
  client_handshake
  args: int * to_server

  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  mkfifo("ur_mum_gay", 0644);//WKP
  mkfifo("no_u", 0644);//Private Pipe

  int pipe1 = open("ur_mum_gay", O_WRONLY);//Sends private pipe name
  printf("%s\n", "sending pipe...");
  write(pipe1, "no_u", sizeof("no_u"));
  printf("%s\n\n", "done...");
  close(pipe1);

  int from_server[100];
  int pipe2 = open("no_u", O_RDONLY);//Recieves file descriptor to server
  printf("%s\n", "recieving...");
  read(pipe2, from_server, sizeof(from_server));
  printf("%s\n\n", "received...");
  close(pipe2);

  int pipe3 = open("no_u", O_WRONLY);//Sends file descriptor to server
  printf("%s\n", "sending...");
  write(pipe3, to_server, sizeof(to_server));
  printf("%s\n", "sent...");
  close(pipe3);

  remove("no_u");

  return *from_server;
}
