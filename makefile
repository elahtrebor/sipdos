sipdos: sipdos.c 
	gcc -o sipdos sipdos.c 
	@echo compiling sipdos.c sipdos...
	gcc -o sendsip sendsip.c
	@echo compiling sendsip...         
	gcc -o inviteFlood inviteFlood.c
	@echo compiling inviteFlood
	gcc -o pingsip pingsip.c
	@echo compiling pingsip
	gcc -o sipdosCustom sipdosCustom.c
	@echo compiling sipdosCustom
	gcc -o pingport pingport.c 
	@echo compiling pingport
	gcc -o spoofsip spoofsip.c 
	@echo compiling spoofsip 

clean:
	rm sipdos sendsip inviteFlood pingsip sipdosCustom pingport spoofsip
	@echo removed all
         
