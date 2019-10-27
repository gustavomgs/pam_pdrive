# pam_pdrive
Esse projeto é uma das soluções para quem precisa de um modulo de autenticação via pendrive, qualquer pendrive pode ser usado para a instalação do módulo.

Versão 1.0.

################################################################################################
0 - Instalação
################################################################################################

  Para instalar:
    make
    make install
    
################################################################################################
1 - Programa de Instalação
################################################################################################

  O instalador cria duas pastas e dois arquivos necessários para o funcionamento do móulo:
    /etc/pam.d/pam.pdrive
      ->login : Aqui fica localizado o serial do pendrive  instalada, apenas com o usuario root se tem acesso.
    /etc/pam.d/pam.pdrive/log
      ->log : Aqui fica localizado o arquivo de log, onde registra data e hora de todos os logins efetuados, e a serial que foi utilizada.
   
################################################################################################
2 - Limitações
################################################################################################
    Versão 1.0 : Grava apenas 1 serial.
