/*
 * Author: Gustavo Messias
 * E-Mail: gustavomgs13@gmail.com
 * ----
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
    

    /*FILE *fp = fopen("/etc/pam.d/pam.pdrive/pdrive.serial", "r");
    char conteudo;
    char conteud;
    int linha = 1;
    int count;
    int c,v;

    char carac[10][100];
    char serial[10][100];
    
    while((conteudo = fgetc(fp)) != EOF){              
            
        carac[linha][count] = conteudo;
        printf("%c", carac[linha][count]);


        if(conteudo=='\n'){   
            linha++;
        }
        count++;
    }
    */

PAM_EXTERN int pam_sm_setcred( pam_handle_t *pamh, int flags, int argc, const char **argv ) 
{
	return PAM_SUCCESS;
}

PAM_EXTERN int pam_sm_authenticate( pam_handle_t *pamh, int flags,int argc, const char **argv ) 
{
    system("clear");

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
 
    buf[len - 1] = 0;


    FILE *user_info;
    char serial[24];

    
    user_info = fopen("/etc/pam.d/pam.pdrive/pdrive.serial", "r");
    
    while(fgets(serial, 100, user_info) != NULL){
    
        if(strcmp(buf, serial) == 0){
            printf("Logado com sucesso");
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

            return PAM_SUCCESS;

        }else{
            printf("Pendrive não cadastrado");
        }
        
        fclose(user_info);
    }

}
    