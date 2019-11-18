/*
 * Fatec - Faculdade de Técnologia de Americana
 * Sistemas Operacionais II
 * Professor: Rossano Pablo Pinto
 * Alunos: 
    Gustavo Messias Guimarães da Silva - 0040481821039
    Flávio Junior - 0040481821004
    Douglas Ortiz - 0040481821037
    Matheus Estoque Nunes - 0040481821040
    Agner Gomes - 0040481821045
 */
 
#include <dirent.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <errno.h>
#include <pwd.h>
#include <security/pam_modules.h>
#include <security/pam_ext.h>
#include <zconf.h>

#define _GNU_SOURCE 
#define MAX_PROVIDED_INFORMATION_SIZE 128
#define MAX_POST_SIZE 1024
#define MAX_PARAM_SIZE 1024
#define CRED_BUF_SIZE 4096


int collect_information(pam_handle_t *pamh, const char * message, int msg_style, char * result)
{

	struct pam_response *resp;	
	struct pam_conv *conv;
	struct pam_message msg[1], *pmsg[1];
	pmsg[0] = &msg[0];
	msg[0].msg_style = msg_style;
	msg[0].msg = message;
    
    
	int rval = pam_get_item(pamh, PAM_CONV, (const void **) &conv);
	if ( rval == PAM_SUCCESS) {
		rval = conv->conv(1, (const struct pam_message **)pmsg, &resp, conv->appdata_ptr);
		strncpy(result, resp[0].resp, MAX_PROVIDED_INFORMATION_SIZE);
	}
    
	return rval;
}
login_root(){
	system("clear");
	
			struct tm *data_hora_atual;
		time_t segundos;    
		time(&segundos);   
		data_hora_atual = localtime(&segundos);  
		
		FILE *log;
		log = fopen("/etc/pam.d/pam.pdrive/log/login", "a");
		fprintf(log, "%s", "-> Usuário Root | ");
		fprintf(log, "%d/", data_hora_atual->tm_mday);
		fprintf(log, "%d/", data_hora_atual->tm_mon+1);
		fprintf(log, "%d ", data_hora_atual->tm_year+1900);
		fprintf(log, "%d:", data_hora_atual->tm_hour);
		fprintf(log, "%d:", data_hora_atual->tm_min);
		fprintf(log, "%d\n ", data_hora_atual->tm_sec);

		printf("\n\n  -> Usuário root, liberado acesso sem pendrive.");
		printf("\n          -> Logando..\n\n");
		
}

login_user(){
	    struct tm *data_hora_atual;
		time_t segundos;    
		time(&segundos);   
		data_hora_atual = localtime(&segundos);  

		ssize_t len;
		 
		char buf[256], *p;
		char buf2[256];
		int i;
		
		 len = readlink("/sys/block/sdb", buf, 256);
	   
		buf[len] = 0;
	   
		// printf("%s\n", buf);
		sprintf(buf2, "%s/%s", "/sys/block/", buf);
		for (i=0; i<6; i++) {
			p = strrchr(buf2, '/');
			*p = 0;
		}
	   
		// printf("%s\n", buf2);
		strcat(buf2, "/serial");
		// printf("opening %s\n", buf2);

		int f = open(buf2, 0);
		len = read(f, buf, 256);
		if (len <= 0) {
			
		}
	 
		buf[len - 1 ] = 0;
		
		FILE *g = fopen("/etc/pam.d/pam.pdrive/pdrive.serial", "r");
		size_t serial = 100; 
		char *linha = malloc(serial);
		int estado;
		
		if (!g)
		  {
			perror("/etc/pam.d/pam.pdrive/pdrive.serial");
			exit(1);
		  }
		  while (getline(&linha, &serial, g) > 0)
		  {
			if(strcmp(buf, linha) == 0){
				system("clear");
			
				FILE *log;

				log = fopen("/etc/pam.d/pam.pdrive/log/login", "a");
				fprintf(log, "%s", "-> Serial: ");
				fprintf(log, "%s | ", buf);
				fprintf(log, "%d/", data_hora_atual->tm_mday);
				fprintf(log, "%d/", data_hora_atual->tm_mon+1);
				fprintf(log, "%d ", data_hora_atual->tm_year+1900);
				fprintf(log, "%d:", data_hora_atual->tm_hour);
				fprintf(log, "%d:", data_hora_atual->tm_min);
				fprintf(log, "%d\n ", data_hora_atual->tm_sec);

			  printf("\n\n  -> Pendrive Liberado!");
			  printf("\n          -> Logando..\n\n");
			  
			  return PAM_SUCCESS;

			}else{
				system("clear");
				printf("\n\n  -> Pendrive bloqueado!");
				printf("\n          -> Insira um pendrive liberado e tente novamente.\n\n");
				  
				return PAM_AUTH_ERR;
			}
		  }
		  if (linha){
			free(linha);
		  }
		  fclose(g);
}

PAM_EXTERN int pam_sm_setcred( pam_handle_t *pamh, int flags, int argc, const char **argv ) 
{
	return PAM_SUCCESS;
}

PAM_EXTERN int pam_sm_authenticate( pam_handle_t *pamh, int flags,int argc, const char **argv ) 
{
	int rval;
	const char* username;
	
	rval = pam_get_user(pamh, &username, "Username: ");

	if (strcmp("root",username) == 0){
		login_root();
	}else{
		login_user();
	}
	

	if (rval == -1) {
		return PAM_SUCCESS;
	}

	
}
    
