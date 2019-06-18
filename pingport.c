/* pingport.c  developed by: Robert Hale   Feb 2002 */
/* Version Build: Linux  V2 */
/* Added Forked counter  for timeout */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <signal.h>

int main(int argc, char *argv[]) {
pid_t childPID = fork();


  if ( childPID == -1 )
  {
    printf( "failed to fork child\n" );
    _exit( 1 );
  }
  else if ( childPID == 0 )
  {
char *IPADDR;
unsigned short PORT;     /* Destination Port */


    if ((argc < 2) || (argc > 3))    /* check the args */
    {
        printf("\n\nUsage: pingport <Destination IP Address> <Destination Port>\n\n");
        exit(0);
    }

if(argc != 2){ 


if (strstr(argv[1],"-h"))    /* check the args */
    {
        printf("\n\nNot enough arguments\n\n");
        printf("\n\nUsage: pingport <Destination IP Address> <Destination Port>\n\n");
        exit(0);
    }

     
        PORT = atoi(argv[2]); /* Use given port, if any */
        IPADDR = argv[1];
 
}


else {
        printf("\n\nNot enough arguments\n\n");
        printf("\n\nUsage: pingport <Destination IP Address> <Destination Port>\n\n");
        exit(0);

}
 

    int sockfd;

    struct sockaddr_in dest_addr;   // struct to hold dest addr

    sockfd = socket(PF_INET, SOCK_STREAM, 0); // init socket

    dest_addr.sin_family = AF_INET;          // host byte order
    dest_addr.sin_port = htons(PORT);   // short, network byte order
    dest_addr.sin_addr.s_addr = inet_addr(IPADDR);
    memset(dest_addr.sin_zero, '\0', sizeof dest_addr.sin_zero);

   if(connect(sockfd, (struct sockaddr *)&dest_addr, sizeof dest_addr) < 0){

    printf("No reply from %s\n", IPADDR);}
   else{
        printf("%s is alive.\n", IPADDR);
    }

 }

 while ( 1 )
  {
    sleep(2);

      kill( childPID, SIGKILL );
    break;
  }

  return 0;


} 
// END PROG
