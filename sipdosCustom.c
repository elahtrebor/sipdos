#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#define BUFFSIZE 1024

void Die(char *mess) { perror(mess); exit(1); }

char *port = "5060";   /* SIP PORT */

  int main(int argc, char *argv[]) {
            int sock;
            struct sockaddr_in sipserver;
            struct sockaddr_in sipclient;
            unsigned int siplen, clientlen;
            int received = 0;
            char sipmsg;
            if (argc != 3) {
              fprintf(stderr, "Incorrect Arguments. Please use: %s <server_ip> <file_name>\n", argv[0]);
              exit(1);
            }


char message[BUFFSIZE];
char buffer[500];
FILE * fp;
 fp = fopen(argv[2], "r");
  if(!(fp)) { puts ("Couldn't open FILE\n"); return 0; }
       while(fgets(buffer, 500, fp) != NULL) {
            strcat (message, buffer);
            memset (buffer, 0, 500); 
           }


           /* Create the UDP socket */
            if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
              Die("Failed to create socket");
            }
            /* Construct the server sockaddr_in structure */
            memset(&sipserver, 0, sizeof(sipserver));       /* zero out the structure */
            sipserver.sin_family = AF_INET;                  /* Internet/IP */
            sipserver.sin_addr.s_addr = inet_addr(argv[1]);  /* CLI passed IP address */
            sipserver.sin_port = htons(atoi(port));       /* server port hard coded for SIP */

  /* Build a continuous loop to send the message to the far end */
 while(1){
          siplen = strlen(message);
          if (sendto(sock, message, siplen, 0,
                     (struct sockaddr *) &sipserver,
                     sizeof(sipserver)) != siplen) {
            Die("Mismatch in number of sent bytes");
          }
      }
}

