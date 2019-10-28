<h2>Fatec - Faculdade de Técnologia de Americana</h2>

Sistemas Operacionais II<br>
Professor: Rossano Pablo Pinto<br>
Aluno: Gustavo Messias Guimarães da Silva<br>
RA: 0040481821039<br>
<hr>

Esse projeto é uma das soluções para quem precisa de um modulo de autenticação via pendrive, qualquer pendrive pode ser usado para a instalação do módulo.
<br>
Versão 1.0 - 26/10/19<br>
Versão 1.1 - 28/10/19<br>
<hr>

<h4> >> Instalação</h4>

  Para instalar inicie o terminal no diretório dos arquivos do módulo:<br>
  Como usuário root digite:<br>
    <li>make</li>
    <li>make install</li>
  Pronto, o seu módulo está instalado.<br>
  Abaixo segue a descrição do funcionamento do programa de instalação.
<hr>
<h4> >> Programa de Instalação</h4>

  O instalador cria duas pastas e dois arquivos necessários<br>
  para o funcionamento do móulo:<br>
    <li>/etc/pam.d/pam.pdrive</li>
      ->login : Aqui fica localizado o serial do pendrive  instalada, apenas com o usuario root se tem acesso.<br>
    <li>/etc/pam.d/pam.pdrive/log</li>
      ->log : Aqui fica localizado o arquivo de log, onde registra data e hora de todos os logins efetuados, e a serial que foi utilizada.<br>
   
################################################################################################<br>
2 - Limitações
################################################################################################<br>
    Versão 1.0 : Grava apenas 1 serial.<br>


