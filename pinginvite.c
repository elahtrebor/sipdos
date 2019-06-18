#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <signal.h>

#define BUFFSIZE 1024

void Die(char *mess) { perror(mess); exit(1); }
  
char *message = "INVITE sip:600@192.168.0.100 SIP/2.0\n"
"Via: SIP/2.0/UDP 192.168.0.187:5060;rport;branch=z9hG4bKPjc4A9snWPIdWhpWDT2NumokGGPZ9tejcn\n"
"Max-Forwards: 70\nFrom: sip:2000@192.168.0.100;tag=yxF6j6K5ubtVwGYLE3naOBc6Cj5awUJl\n"
"To: sip:600@192.168.0.100\nContact: <sip:2000@192.168.0.187:5060>\n"
"Call-ID: yaU3GwzDQ-qnDNT78iuhtnnXDWKSbLNg\nCSeq: 29473 INVITE\n"
"Allow: PRACK, INVITE, ACK, BYE, CANCEL, UPDATE, SUBSCRIBE, NOTIFY, REFER, MESSAGE, OPTIONS\n"
"Supported: replaces, 100rel, timer, norefersub\nSession-Expires: 1800\nMin-SE: 90\n"
"User-Agent: pingsip v1.0\nProxy-Authorization: Digest username=\"pingsip\", "
"realm=\"asterisk\", nonce=\"5f04808di\", uri=i\"sip:600@192.168.0.100i\", response=i\"8451225d5ca7b880199050c7024b68e9\", algorithm=MD5\n"
"Content-Type: application/sdp\nContent-Length:   267\n\nv=0\no=- 3505659725 3505659725 IN IP4 192.168.0.187\ns=pingsip\nc=IN IP4 192.168.0.187\n"
"t=0 0\na=X-nat:0\nm=audio 4000 RTP/AVP 3 0 8 101\na=rtpmap:3 GSM/8000\na=rtpmap:0 PCMU/8000\na=rtpmap:8 PCMA/8000\na=sendrecv\n"
"a=rtpmap:101 telephone-event/8000\n";

char *port = "5060";   /* SIP PORT */

  int main(int argc, char *argv[]) {
            int sock;
            struct sockaddr_in sipserver;
            struct sockaddr_in sipclient;
            char buffer[BUFFSIZE];
            unsigned int siplen, clientlen;
            int received = 0;
            char sipmsg;

struct timeval tv;
  tv.tv_sec = 1;
  tv.tv_usec = 0;

            if (argc != 2) {
              fprintf(stderr, "Incorrect Arguments. Please use: %s <server_ip>\n", argv[0]);
              exit(1);
            }

           /* Create the UDP socket */
            if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
              Die("Failed to create socket");
            }
if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO,&tv,sizeof(tv)) < 0) {
      perror("Error");
  }

            /* Construct the server sockaddr_in structure */
            memset(&sipserver, 0, sizeof(sipserver));       /* zero out the structure */
            sipserver.sin_family = AF_INET;                  /* Internet/IP */
            sipserver.sin_addr.s_addr = inet_addr(argv[1]);  /* CLI passed IP address */
            sipserver.sin_port = htons(atoi(port));       /* server port hard coded for SIP */

          siplen = strlen(message);
          if (sendto(sock, message, siplen, 0,
                     (struct sockaddr *) &sipserver,
                     sizeof(sipserver)) != siplen) {
            Die("Mismatch in number of sent bytes");
          }
      /* Listen for a return message */

              clientlen = sizeof(sipclient);

              if ((received = recvfrom(sock, buffer, BUFFSIZE, 0,
                                       (struct sockaddr *) &sipclient,
                                       &clientlen)) < 0) {


                    printf("No response from %s.\n", argv[1]); 
              }else{ 
              printf("%s is alive.\n",argv[1]);
              exit(0);
             }
 return 0;
}
