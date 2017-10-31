# README #

This README would normally document whatever steps are necessary to get your application up and running.

### O que há nesse repositório? ###

Considere o seguinte jogo hipotético, que chamaremos de Bankrupt, muito semelhante a Banco Imobiliário
onde várias de suas mecânicas foram simplificadas. Numa partida desse jogo, os players se alteram em 
rodadas, numa ordem definida aleatoriamente no começo da partida. Os players sempre começam uma partida 
com 300 coins cada um. Nesse jogo, o tabuleiro é composto por 20 propriedades em sequência. Cada casa tem                            
um custo de venda, um valor de aluguel, um dono caso já estejam compradas, e seguem uma determinada ordem 
no tabuleiro. Em Bankrupt, não é possível construir hotéis e nenhuma outra melhoria sobre as propriedades 
do tabuleiro, por simplicidade do problema. O valor de venda e de aluguel de todas as 20 propriedades são 
configurados num arquivo de nome gameConfig.txt, que seu programa deve ler e interpretar.

[Learn Markdown](https://bitbucket.org/ceci_costa/desafiotapps)

### Como fazer o Setup? ###

* Setup: Download ou clone o repositório e abra a solução com Visual Studio 2015 ou superior, com 
o suporte a C++ instalado. Nenhuma bibliotéca especifica do Visual C++ ou .NET foi utilizada. Em 
tese a aplicação pode ser compilada com qualquer com compilador que suporte as chamadas especificas 
de C++11 utilizadas.

Obs: Para compilar em outro ambiente pode ser necessário comentar os #include "stdafx.h", adicionados pelo Visual Studio.
 
* Dependências : Compilador com suporte a chamadas de C++11. Recomendado Visual Studio 2015 com suporte a C++ instalado. 
* Como executar: Execute a partir do Visual Studio ou executavel criado.
