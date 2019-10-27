# pam_pdrive
Esse projeto é uma das soluções para quem precisa de um modulo de autenticação via pendrive, qualquer pendrive pode ser usado para a instalação do módulo.

Versão 1.0.

################################################################################################<br>
0 - Instalação
################################################################################################<br>


    
################################################################################################<br>
1 - Programa de Instalação
################################################################################################<br>

  O instalador cria duas pastas e dois arquivos necessários para o funcionamento do móulo:<br>
    /etc/pam.d/pam.pdrive<br>
      ->login : Aqui fica localizado o serial do pendrive  instalada, apenas com o usuario root se tem acesso.<br>
    /etc/pam.d/pam.pdrive/log<br>
      ->log : Aqui fica localizado o arquivo de log, onde registra data e hora de todos os logins efetuados, e a serial que foi utilizada.<br>
   
################################################################################################<br>
2 - Limitações
################################################################################################<br>
    Versão 1.0 : Grava apenas 1 serial.<br>


