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


void makeDirPdrive(){

    //variavel que grava o estado, 0 diretorio nao existe, -1 existe.
    struct stat st = {0};
	
    //se existe, retorna msg, se não cria o diretório
	if (stat("/etc/pam.d/pam.pdrive", &st) == -1) {
		if(mkdir("/etc/pam.d/pam.pdrive", 0700) == 0){
            printf("    Diretório criado com Sucesso: /pam.pdrive\n");
		}else{
            printf("    Erro ao criar diretório: /pam.pdrive\n");
        }
	}else{
            printf("    Diretório ja existente: /pam.pdrive\n");
    }
}

void makeDirLog(){

        //variavel que grava o estado, 0 diretorio nao existe, -1 existe.
        struct stat st = {0};
        
        //se existe, retorna msg, se não cria o diretório
        if (stat("/etc/pam.d/pam.pdrive/log", &st) == -1) {
                if(mkdir("/etc/pam.d/pam.pdrive/log", 0700) == 0){
                    printf("    Diretório criado com Sucesso: /log\n");
                }else{
                    printf("    Erro ao criar diretório: /log\n");
                }
            }else{
                    printf("    Diretório ja existente: /log\n");
        }
}

void makeFileSerial(){
    FILE *pdrive_serial;
    
    pdrive_serial = fopen("/etc/pam.d/pam.pdrive/pdrive.serial", "a");

    if (pdrive_serial == NULL){
        printf("    Erro ao criar arquivo de seriais.\n");
    }
    else{
        printf("    Arquivo de seriais criado com sucesso.\n");
    }
}

void makeFileLog(){
    FILE *log;
    
    log = fopen("/etc/pam.d/pam.pdrive/log/login", "a");

    if (log == NULL){
        printf("    Erro ao criar arquivo de histórico de logins.\n");
    }
    else{
        printf("    Arquivo de histórico de logins criado com sucesso.\n");
    }
}


int verPendrive(){
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
        printf("Erro");
    }
 
    buf[len - 1] = 0;

    int qtd = strlen(buf);

    return qtd;
    
}

char verSerial(){
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
    

    return buf;

}


void addUser( char nome[256] ){
    ssize_t len;
     
    char buf[256], *p;
    char buf2[256];
    int i;
   
    len = readlink("/sys/block/sdb", buf, 256);
   
    buf[len] = 0;
   
    sprintf(buf2, "%s/%s", "/sys/block/", buf);
    for (i=0; i<6; i++) {
        p = strrchr(buf2, '/');
        *p = 0;
    }
   
    strcat(buf2, "/serial");

    int f = open(buf2, 0);
    len = read(f, buf, 256);
    if (len <= 0) {
        
    }
 
    buf[len - 1] = 0;

    FILE *pont_arq; // cria variável ponteiro para o arquivo
        
        //abrindo o arquivo com tipo de abertura w
        pont_arq = fopen("/etc/pam.d/pam.pdrive/pdrive.serial", "w");
        
        //testando se o arquivo foi realmente criado
        if(pont_arq == NULL)
        {
        printf("    Erro na abertura do arquivo!");
        }
        
        //usando fprintf para armazenar a string no arquivo
        fprintf(pont_arq, "%s", buf);

        //usando fclose para fechar o arquivo
        fclose(pont_arq);

        puts("    Pendrive cadastados com sucesso.\n");

}

int main(int argc, char *argv[]){
    system("clear");

    puts("\n\n-> Para iniciar, certifique-se que o Pendrive esteja conectado.");
    puts("\n-> Certifique-se que apenas 1 Pendrive esteja conectado.");
    puts("\n-> Caso nenhum pendrive seja detectado, o programa de instalação será encerrado.");
    system("read -p \"\nApós seguir as instruções, pressione enter para continuar...\" foo");

    system("clear"); 

     puts("\n-> Iniciando instalação:");
    puts("---------------------------------------------------");
    sleep(2);

    puts("\n-> Criando diretórios de configuração do módulo:");
    puts("   '/etc/pam.d/pam.pdrive'");
    puts("   '/etc/pam.d/pam.pdrive/log'");
    makeDirPdrive();
    makeDirLog();
    sleep(2);

    puts("\n-> Criando arquivo que armazena os seriais:");
    puts("   '/etc/pam.d/pam.pdrive'");
    puts("   '/etc/pam.d/pam.pdrive/log'");
    makeFileSerial();
    makeFileLog(); 

    char nome[100]; 

    puts("\n-> Criando primeiro pendrive liberado:");

    addUser(nome);

    system("read -p \"Pressione enter para continuar...\" foo");




}