# sipdos
SIPDOS - Developed by rhale 
Release: FEB 2006
Purpose: Security Testing for various voip devices.

LICENSE: This program suite is completely free

Installation:

tar -zxvf sipdos.tar.gz

Compilation:

make 

 or individually compiled

gcc sipdos.c -lsock -o sipdos


Definitions:

sipdos.c - A basic Registration DOS. Change char *message to be any message you want. When run from the cli takes TARGET IP Address as an argument and then Enters a while loop creating as many packets as it can towards the destination.  

inviteFlood.c - Send a flood of Invites to the far end.

pinginvite.c - Send 1 invite and check for a sip response.

pingport.c - Check for an open TCP port.

pingsip.c - Send a register and check for an invite.

sendsip.c - Send 1 registration message.

sipdosCustom.c - Send a custom message. Useful for fuzzing messages. For instance, inserting a carriage return in the body of some messages causes the far end Parser to crash allowing packets through a firewall that should have been blocked.

spoofsip.c - Send a SIP Registration message with spoofed source address. 

