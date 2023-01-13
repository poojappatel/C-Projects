#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int compare(void * num1, void * num2) {
  int num1_i = *(int *)num1;
  int num2_i = *(int *)num2;
  if (num1_i == num2_i) return 0;
  if (num1_i > num2_i) return 1;
  else return -1;
}

int main(int argc, char *argv[]) {
  int sock;
  struct sockaddr_in server;

  sock = socket(AF_INET, SOCK_STREAM, 0);
  
  if (sock < 0) {
    printf("Socket creation error\n");
    return -1;
  }

  //server.sin_addr.s_addr = inet_addr(*(argv+2));
  server.sin_family = AF_INET;
  server.sin_port = htons(atoi(argv[2]));
  server.sin_addr.s_addr = inet_addr(*(argv+3));
  /*
  if (inet_pton(AF_INET, argv[2], &server.sin_addr) <= 0) {
    printf("Invalid address. Address is not supported\n");
    return -1;
  }
  */

  if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
    printf("Connection failed\n");
    printf("%d", connect(sock, (struct sockaddr *)&server, sizeof(server)));
    return -1;
  }

  char buff[1000];

  printf("netID: %s", argv[1]);
  
  strcpy(buff, "cs230 HELLO ");
  strcat(buff, argv[1]);
  strcat(buff, "\n");

  printf("Connected\n");
  
  printf("sent: %s\n", buff);
  send(sock, buff, strlen(buff), 0);

  int len_msg;
  int i;
  char *split;
  char *data[9];
  while (1) {
    
    recv(sock, buff, 1000, 0);
    len_msg = strlen(buff);
    buff[len_msg] = '\0';
    printf("%s\n", buff);  
  
    i = 0;

    split = strtok(buff, " ");
    while (split != NULL) {
      data[i] = split;
      i++;
      split = strtok(NULL, " ");
    }
    
    int answer = atoi(argv[1]);
    if (strcasecmp(data[1], "STATUS") == 0) {
      int op = atoi(data[2]);
      int num1 = atoi(data[3]);
      int num2 = atoi(data[4]);
      int num3 = atoi(data[5]);
      int num4 = atoi(data[6]);
      int num5 = atoi(data[7]);
      int arr[5] = {num1, num2, num3, num4, num5};
    
      if (strcasecmp(data[2], "max") == 0) {
	int max = arr[0];
	for (int i = 1; i < 5; i++) {
	  if (arr[i] > max) {
	    max = arr[i];
	  }
	}
	answer = max;
      } else if (strcasecmp(data[2], "min") == 0) {
	int min = arr[0];
	for (int i = 1; i < 5; i++) {
	  if (arr[i] < min) {
	    min = arr[i];
	  }
	}
	answer = min;
      } else if (strcasecmp(data[2], "median") == 0) {
	qsort(arr, 5, sizeof(int), compare);
	answer = arr[2];
      } else {
	printf("Invalid operation.\n");
      }
    } else {
      break;
    }

    char buff1[1000];
    char ans[10];
    sprintf(ans, "%d", answer);
    
    strcpy(buff1, "cs230 ");
    strcat(buff1, ans);
    strcat(buff1, "\n");
    printf("sent: %s\n", buff1);
    send(sock, buff1, strlen(buff1), 0);

    buff[0] = '\0';
    buff1[0] = '\0';
    free(split);
    data[0] = '\0';
    //len_msg = 0;
  }
 
  return 0;
  
}    
