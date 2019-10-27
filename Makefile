

pam_pdrive.o: pam_pdrive.c
	gcc -fPIC -lcurl -fno-stack-protector -c pam_pdrive.c

install: 
	sed -i "5s/^/	auth	  required  pam_pdrive.so\n/" /etc/pam.d/system-auth
	gcc criar_arquivos.c -o criar_arquivos
	./criar_arquivos


