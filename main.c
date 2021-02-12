// Marco António Ferreira Domingues
// Aluno número 21280422

#include <stdio.h>
#include <stdlib.h>
#include "pilotos.h"
#include "utils.h"

int main()
{
int Tc=0, Tp=0, pick=0, total_pares, corridas, parag, i=1;
pPiloto p;
pCarro c;
par *participam; //ponteiro q aponta para um array que contem os pares
pVolta Ivolta;   //ponteiro para o inico da estrutura da corrida
pPonto pnts=NULL;


p=conta_pilotos(&Tp);                   //ve o numero de pilotos no ficheiro
c=conta_carros(&Tc);                       //ve o numero de carros no ficheiro
Tp=lePilotos(p);                           //le e guarda a informacao de cada piloto num array
Tc=leCarros(c);                             //le e guarda a informacao de cada carro num array

if(Tc==0 || Tp==0){                             //caso nao haja carros/pilotos
    printf("\n\tERRO!\n\tFicheiros vazios ou inexistentes\n\tO programa vai ser fechado.\n");
    espera(5);
    exit(0);

}else if(Tc==-1 || Tp==-1){                         //caso haja ficheiros mal escritos
    printf("\n\tERRO!\n\tFicheiros mal escritos\n\tO programa vai ser fechado.\n");
    espera(5);
    exit(0);
}



    do{                                                 //funcao menu
        printf("\n\n\n\t\t\tMENU PRINCIPAL\n\n");
        printf("\n\t 1- mostrar lista e caracteristicas dos carros\n\t 2- mostrar lista e caracteristicas dos pilotos \n\t 3- criar uma corrida/ treino\n\t 4- criar um campeonato\n\t 5- penalizar um piloto por mau comportamento\n\t 0- desligar o programa\n\n\topcao:\t");
        scanf("%d", &pick);

        if(pick!=0 && pick!=1 && pick!= 2 && pick!=3 && pick!=4 &&pick!=5){       //caso o valor colocado no menu nao seja o das opçoes disponiveis
            printf("\n\tERRO!\n\tpor favor coloque um valor valido!\n");

        }else if(pick==0){                                      //escolha de encerramento do programa
            printf("\nO programa vai ser encerrado.");
            //atualiza();


        }else if(pick==1){                                  //escolhe mostrar carros
            mostra_carros(c, Tc);


        }else if(pick==2){                       //escolhe mostrar carros
            mostra_pilotos(p, Tp);


        }else if(pick==3){                               //escolhe fazer um treino/ corrida individual
            total_pares=dados(c,Tc,p,Tp);                                       //recolhe  o numero de pares que a corrida ira ter
            participam=cria_par(total_pares,c, Tc, p, Tp);                        //cria, aleatorimanete, os pares carro-piloto
            Ivolta= faz_voltas(participam, total_pares, p, Tp);                            //faz a corrida e devolve um ponteiro para o inicio da estrutura da mesma
            devolve(Ivolta, c, Tc, p, Tp);                                  //coloca no array principal de carros e piltos as mudancas que foram feitas
            liberta(Ivolta);                                                    //liberta memoria guardada para a simulacao da corrida
            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
            //cria este printf para melhoramento da interface


        }else if(pick==4){                              //escolhe fazer um campeonato
            corri(&corridas);                                   //obtem o numero de "corridas" que o campeonato vai ter
            total_pares=dados(c,Tc,p,Tp);                           //recolhe  o numero de pares que a corrida ira ter
            participam=cria_par(total_pares,c, Tc, p, Tp);;              //cria, aleatorimanete, os pares carro-piloto
            i=1;                                                    //coloca um contador de voltas com o valor 1
            while(i<=corridas){
                printf("\n\n\t\t\t CORRIDA NUMERO %d\n\n", i);
                Ivolta= faz_voltas(participam, total_pares, p, Tp);                             //faz a corrida e devolve um ponteiro para o inicio da estrutura da mesma
                devolve(Ivolta, c, Tc, p, Tp);                      //coloca no array principal de carros e piltos as mudancas que foram feitas
                if(i==1){                                             //caso seja a primeira volta
                    pnts= cria_pontuacao(Ivolta);                       //cria uma estrutra dinamica que contem todos os participantes e da-lhes apontcao devida pela primeira corrida
                }else{                                                      //caso nao seja a primeira volta
                    pnts=pontuacao(pnts, Ivolta);                           //atualiza e organiza a estrutura criada na primeira volta que contem as pontuacoes
                }

                liberta(Ivolta);                        //liberta memoria guardada para a simulacao da corrida
                paragem(&parag);
                mostra_pontuacao_final(pnts);                        //pergunta se devera ser feita uma paragem no programa/ campeonato
            // if(parag==0){
                    //escreve ficheiro;                 //desliga o programa caso o utilizador indicar que é seu desejo (nao feito)

                //}
                i++;                                                     //aumenta o contador da volta
            }
            mostra_pontuacao_final(pnts);                       //mostra a pontuacao final do camponato
            limpa_campeonato(pnts);

        }else if(pick==5){
            penaliza(p, Tp);                        //funcao que irá penalizar o piloto escolhido

        }
    }while(pick!=0);
    reescritura(c,Tc,p,Tp);
}
