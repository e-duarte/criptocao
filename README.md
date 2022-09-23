# criptocao
Algoritmo de criptografia simétrica simpĺes

# Construção do binário e execução
Os arquivos objetos e binários estão sendo
construídos pelo ferramenta make do GNU.

As seguintes regras são permitidas

$make all [constrói os objetos e binários]

$make clean [limpa os objetos e binários]

[observação] para executar o make é necessário
             está dentro da pasta onde esta o makefile.


Na pasta bin execute o seguinte comando para rodar o algoritmo:

Criptografar
  
  ~bin/$ ./criptocao -c [caminho do documento]

Descriptografar
  
  ~bin/$ ./criptocao -d [caminho do documento criptografado] [caminho da chave] 
  
opção: 
      -c : criptografar o documento
      -d : descriptografar o documento

Qualquer bug no programa entre em contato.
