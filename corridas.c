// Marco António Ferreira Domingues
// Aluno número 21280422

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilotos.h"
#include "utils.h"

int dados(carro *c,int Tc,piloto *p,int Tp){

    int Tc_ni=0,Tp_ni=0, i;
    int capacidade_pista, tp_final;

    for(i=0; i<Tp; i++){                //conta os pilotos sem impedimento
        if(p[i].impedimento==0)
            Tp_ni++;
    }

    for(i=0; i<Tc; i++){                    //conta os carros sem avaria
        if(c[i].avaria==0)
            Tc_ni++;
    }

    do{                                                     //pede a capacidade da pista
        printf("\nnumero maximo de carros que podem participar:\t ");
        scanf(" %d", &capacidade_pista);
        if(capacidade_pista<1){
            printf("por favor coloque um valor inteiro positivo");
        }
    }while(capacidade_pista<1);


    if(Tc_ni>Tp_ni){                            //estes 2 ifs verificam entre o numero de carros disponiveis, pilotos disponiveis e capacidade
        tp_final=Tp_ni;                            //da pista qual o menor valor, para depois poder
    }else{                                              //distribuir aleatoriamente carros e pilotos baseado nesse valor
        tp_final=Tc_ni;
    }
    if(tp_final>capacidade_pista){
        tp_final=capacidade_pista;
    }
    return tp_final;
}

pPar cria_par(int tp_final, carro *c, int Tc,piloto *p,int Tp){

    pPar participam;
    int i, t, *buff_carros, *buff_pilotos, pa, ja_distribuido=0, verificador_repeticao;

    participam= (par *) malloc(tp_final * sizeof(par));                    //aloca memória para criar um array que contem tudo
        if(participam==NULL){                                                 //verifica se ocorreu algum erro na alocacao de memoria e desliga o programa em caso afirmativo
            printf("\nERRO FATAL!\n\t\Erro na alocação de mémoria");
            exit(0);
        }

    buff_pilotos= (int *) malloc(tp_final * sizeof(int));          //aloca memoria para criar um array que servira para garantir que os pilotos nao sao repetidos durante a sua "escolha de par"
        if(buff_pilotos==NULL){                                                 //verifica se ocorreu algum erro na alocacao de memoria e desliga o programa em caso afirmativo
            printf("\nERRO FATAL!\n\t\Erro na alocação de mémoria");
            exit(0);
        }

    for(i=0; i<tp_final; i++){
        buff_pilotos[i]=0;                  //coloca o array buff_pilotos com o valor 0, para evitar problemas
    }



    buff_carros= (int *) malloc(tp_final * sizeof(int));            //aloca memoria para criar um array que servira para garantir que os carros nao sao repetidos durante a sua "escolha de par"
        if(buff_carros==NULL){                                                 //verifica se ocorreu algum erro na alocacao de memoria e desliga o programa em caso afirmativo
            printf("\nERRO FATAL!\n\t\Erro na alocação de mémoria");
            exit(0);
        }

    for(i=0; i<tp_final; i++){
        buff_carros[i]=0;                      //coloca o array buff_carros com o valor 0, para evitar problemas
    }

                        //ESCOLHA ALEATORIA DO PAR PILOTO-CARRO

    for(i=0; i<tp_final;i++,ja_distribuido++){                               //faz a escolha do par piloto-carro
        do{                                                                 //verifica que o valor de pa nao é um valor ja usado para a posicao do carro a ir buscar
            pa= intUniformRnd( 0, Tc-1);
            verificador_repeticao=0;
            if(ja_distribuido==0 && c[pa].avaria>0){
                verificador_repeticao=1;
            }else{
                for(t=0, verificador_repeticao=0; t<ja_distribuido;t++){
                    if(pa==buff_carros[t] || c[pa].avaria>0){
                        verificador_repeticao=1;
                    }
                }
            }
        }while(verificador_repeticao==1);

        buff_carros[ja_distribuido]=pa;                            //guarda a posicao ja escolhida
        participam[i].car=c[pa];                     //enche a posicao i do array de par carro-piloto com a informaco de determinado carro


        do{                                     //verifica que o valor de pa nao é um valor ja usado para a posicao do piloto a ir buscar
            pa= intUniformRnd( 0, Tp-1);
            verificador_repeticao=0;
            if(ja_distribuido==0 && p[pa].impedimento>0){
                verificador_repeticao=1;
            }else{
                for(t=0,verificador_repeticao=0; t<ja_distribuido;t++){
                    if(p[pa].impedimento>0 ||pa==buff_pilotos[t] ){
                        verificador_repeticao=1;
                    }
                }
            }
        }while(verificador_repeticao==1);
        buff_pilotos[ja_distribuido]=pa;                                 //guarda a posicao ja escolhida
        participam[i].pil=p[pa];                     //enche a posicao i do array de par carro-piloto com a informaco de determinado pioloto
    }

                                //MOSTRAR PARES CRIADOS

    for(i=0; i<tp_final; i++){
        printf("\n\n\t par %d", i+1);
        printf("\n\t nome do piloto:\t%s", participam[i].pil.nome);
        printf("\n\t id do carro:\t%d", participam[i].car.id);

    }

                                //MOSTRAR PILOTOS E CARROS NAO ESCOLHIDOS
    printf("\n\n\t\t carros que nao foram escolhidos\n");
    for(i=0; i<Tc;i++){                                     //indica os carros nao escolhidos
        for(verificador_repeticao=0, t=0; t<tp_final;t++){
            if(i==buff_carros[t])
            verificador_repeticao=1;
        }
        if(verificador_repeticao==0){
            if(c[i].avaria==0){
                printf("\n\t id do carro:\t%d", c[i].id);
                printf("\n\t esta em condicoes de participar porem nao foi escolhido\n");
            }
            else{
                printf("\n\t id do carro:\t%d", c[i].id);
                printf("\n\t encontra-se avariado\n");
            }
        }
    }

    printf("\n\n\t\t pilotos que nao foram escolhidos\n");
    for(i=0; i<Tp;i++){                                                 //indica os pilotos nao escolhidos
        for(verificador_repeticao=0, t=0; t<tp_final;t++){
            if(i==buff_pilotos[t])
            verificador_repeticao=1;
        }
        if(verificador_repeticao==0){
            if(p[i].impedimento==0){
                printf("\n\t nome do piloto:\t%s", p[i].nome);
                printf("\n\t esta em condicoes de participar porem nao foi escolhido\n");
            }
            else{
                printf("\n\t nome do pilto:\t%s", p[i].nome);
                printf("\n\t encontra-se impedido \n");
            }
        }
    }

        free(buff_carros);
        free(buff_pilotos);

    return participam;

}

 int calcula_idade(int i ,pPar participam){
    int ano, mes,dia, hora, minuto,segundo, idade;          //cria as variaveis temporais necessarias

    obtemData( &dia, &mes, &ano, &hora, &minuto, &segundo);         //usa a funcao dada para indicar a data e hora
     mes++;
                        //algoritmo de calculo da idade do piloto

    if(mes>participam[i].pil.born.mes || (mes==participam[i].pil.born.mes && dia<=participam[i].pil.born.dia)){
        idade=ano-participam[i].pil.born.ano;

    }else if(mes==participam[i].pil.born.mes || mes<participam[i].pil.born.mes ){
        idade=ano-participam[i].pil.born.ano -1;

    }

    return idade;
 }

void reve_corrida(pVolta primeiro, int voltas){
    int opcao=0,i, j, toda=voltas+1, rfinal=toda+1;
    pClass atual;
    pVolta a=primeiro;

    printf("\n\n\t\t MENU DE REVISAO DE RESULTADOS");

    do{
        printf("\n\n\n\t 1 a %d -Rever tempos numa volta especifica da corrida\n\t %d -Rever toda a corrida \n\t %d-Rever colocacao final\n\t 0 -Sair do menu de revisao de resultados", voltas,voltas+1, voltas+2 );
        printf("\n\t opcao ");
        scanf(" %d", &opcao);

        if(opcao<0 || opcao>voltas+2){                 //CASO O NUMERO COLOCADO SEJA INVALIDO
            printf("\n\t Opcao invalida! Por favor coloque de novo.");

        }else if(opcao>=1 && opcao <=voltas){                       //PEDIR PARA VER UMA VOLTA ESPECIFICA DA CORRIDA
            i=2;
            a=primeiro;
            for(j=0;j<(opcao-1); j++){
                a=a->prox;
            }

            atual=a->proxC;

            printf("\n\t\t\t\t VOLTA NUMERO %d", opcao);

            if(atual->acidente==0){                 //CASO SEJA O PRIMEIRO
                printf("\n\n1 classificado:");
                printf("\nnome: %s", atual->nome);
                printf("\nid do carro: %d", atual->carID);
                printf("\ntempo desta volta: %d", atual->tempo);
                printf("\ntempo total: %d", atual->tempo_total);

            }else{
                printf("\n\n1 classificado:");
                printf("\nnome: %s", atual->nome);
                printf("\ndesistiu na volta: %d", atual->acidente);
            }
            do{                                     //RESTO DOS CLASSIFICADOS
                if(atual->prox->acidente==0){
                    printf("\n\n%d classificado:",i );
                    printf("\nnome: %s", atual->prox->nome);
                    printf("\nid do carro: %d", atual->prox->carID);
                    printf("\ntempo desta volta: %d", atual->prox->tempo);
                    printf("\ntempo total: %d", atual->prox->tempo_total);

                }else{
                    printf("\n\n%d classificado:", i);
                    printf("\nnome: %s", atual->prox->nome);
                    printf("\ndesistiu na volta: %d", atual->acidente);
                }
            i++;
            atual=atual->prox;
            }while(atual->prox!=NULL);

        }else if(opcao==toda){                                  //PEDIR PARA REVER TODA A CORRIDA

            a=primeiro;
            j=1;
            while(a!=NULL){
                atual=a->proxC;
                i=2;
                printf("\n\n\t\t VOLTA NUMERO %d", j);      //indicador do numero de volta
                if(atual->acidente==0){                 //CASO SEJA O PRIMEIRO
                    printf("\n\n1 classificado:");
                    printf("\nnome: %s", atual->nome);
                    printf("\nid do carro: %d", atual->carID);
                    printf("\ntempo desta volta: %d", atual->tempo);
                    printf("\ntempo total: %d", atual->tempo_total);

                }else{
                    printf("\n\n1 classificado:");
                    printf("\nnome: %s", atual->nome);
                    printf("\ndesistiu na volta: %d", atual->acidente);
                }
                do{                                     //RESTO DOS CLASSIFICADOS
                    if(atual->prox->acidente==0){
                        printf("\n\n%d classificado:",i );
                        printf("\nnome: %s", atual->prox->nome);
                        printf("\nid do carro: %d", atual->prox->carID);
                        printf("\ntempo desta volta: %d", atual->prox->tempo);
                        printf("\ntempo total: %d", atual->prox->tempo_total);

                    }else{
                        printf("\n\n%d classificado:", i);
                        printf("\nnome: %s", atual->prox->nome);
                        printf("\ndesistiu na volta: %d", atual->acidente);
                    }

                    i++;
                    atual=atual->prox;

                }while(atual->prox!=NULL);
                a=a->prox;
                j++;
            }

        }else if (opcao==rfinal){

            printf("\n\n\t\t Resultado Final:");
            a=primeiro;
                while(a->prox!=NULL){
                    a=a->prox;
                }
            atual=a->proxC;
            i=1;
            while(atual!=NULL){
                if(atual->acidente==0){                 //visualizacao da tabela classificativa final
                    printf("\n\n %d classificado:", i);
                    printf("\nnome: %s", atual->nome);
                    printf("\nid do carro: %d", atual->carID);
                    printf("\ntempo total: %d", atual->tempo_total);

                }else{
                    printf("\n\n%d classificado:", i);
                    printf("\nnome: %s", atual->nome);
                    printf("\ndesistiu na volta: %d", atual->acidente);
                }


                atual=atual->prox;
                i++;

            }
        }
    }while(opcao!=0);


}

pVolta faz_voltas(pPar par,int tp, pPiloto p, int Tp){
                    //par  <------- array de pares
                    //tp <--- numero total de pares
    int i , idade, voltas, tamanho_pista, Nvolta, peso, experiencia, potencia, acidente, j;
    pVolta a, primeiro, b=NULL;
    pClass classi=NULL, atual;

     do{                                             //pede o numero de voltas da pista
        printf("\nnúmero de voltas da pista, valor entre 5 e 10:\t ");
        scanf(" %d", &voltas);
        if(voltas<5 || voltas>10)
            printf("\nO numero de voltas deve ser inteiro e estar emtre 5 e 10");
    }while(voltas<5 || voltas>10);

    do{                                                         //pede o comprimento da pista
        printf("\ncomprimento da pista (metros), valor entre 500 e 1000:\t ");
        scanf(" %d", &tamanho_pista);
        if(tamanho_pista<500 || tamanho_pista>1000)
            printf("\nO comprimento da pista deve ser inteiro e estar emtre 500 e 1000");
    }while(tamanho_pista<500 || tamanho_pista>1000);

                        //SIMULACAO DAS VOLTAS
    for(Nvolta=1; Nvolta<=voltas;Nvolta++){
        printf("\n\n\t\t\t VOLTA NUMERO %d", Nvolta);

        a=malloc(sizeof(volta));
        if(a==NULL){
            printf("\n\tErro a alocar memoria!\n\to programa deverá encerrar!");
            exit(0);
        }
        a->volta_n=Nvolta;
        a->prox=NULL;
        a->proxC=NULL;

        if(Nvolta==1){
            primeiro=a;
            b=a;
        }

        for(i=0;i<tp;i++){
            j=0;
            while(j<Tp && par[i].pil.id!=p[j].id){
                j++;
            }
            if(p[j].impedimento==0){                    //garantir que no caso dos campeonatos nao corre se teve acidente
                classi=malloc(sizeof(tempo));
                if(classi==NULL){
                    printf("\n\tErro a alocar memoria!\n\to programa devera encerrar!");
                    exit(0);
                }

                if(Nvolta==1){                                    //caso seja a primeira volta
                    acidente= probEvento(0.05);           //testa se o par tem acidente na primeira volta
                    if(acidente==1){                                //caso tenha acidente



                        classi->acidente=Nvolta;
                        classi->carID=par[i].car.id;
                        strcpy(classi->nome,par[i].pil.nome);
                        classi->pilotoID=par[i].pil.id;
                        classi->prox=NULL;
                        classi->tempo=0;
                        classi->tempo_total=0;
                        idade= calcula_idade( i, par);
                        classi->idade=idade;

                    }else{                                          //caso nao tenh acidente
                        idade= calcula_idade( i, par);
                        classi->idade=idade;
                        peso= par[i].pil.peso;                          //preparacaopara o calculo do tempo da volta
                        experiencia=par[i].pil.xp;
                        potencia=par[i].car.power;


                        classi->acidente=0;
                        classi->carID=par[i].car.id;
                        strcpy(classi->nome,par[i].pil.nome);
                        classi->pilotoID=par[i].pil.id;
                        classi->prox=NULL;
                        classi->tempo=calculaSegundos(idade, peso, experiencia, potencia, tamanho_pista);
                        classi->tempo_total=classi->tempo;

                    }
                }
                else{                                       //caso nao seja a primeira volta
                    atual=b->proxC;                                 //vai a volta anterior procurar pelo local onde o mesmo par esta
                    if(atual->pilotoID==par[i].pil.id){             //caso seja logo o primeiro
                    ;

                    }else{                                              //caso nao seja o primeiro
                        do{
                            atual=atual->prox;
                        }while(atual->pilotoID!=par[i].pil.id);
                    }
                    if(atual->acidente!=0){
                        classi->carID=par[i].car.id;
                        strcpy(classi->nome,par[i].pil.nome);
                        classi->pilotoID=par[i].pil.id;
                        classi->prox=NULL;
                        classi->tempo=0;
                        classi->acidente=atual->acidente;
                        classi->tempo_total=0;
                        idade= calcula_idade( i, par);
                        classi->idade=idade;

                    }else{
                        acidente= probEvento(0.05);           //testa se o par tem acidente nesta volta
                        if(acidente==1){                                //caso tenha acidente nesta volta

                            classi->acidente=Nvolta;

                            classi->carID=par[i].car.id;
                            strcpy(classi->nome,par[i].pil.nome);
                            classi->pilotoID=par[i].pil.id;
                            classi->prox=NULL;
                            classi->tempo=0;
                            classi->tempo_total=0;
                            idade= calcula_idade( i, par);
                            classi->idade=idade;
                        }else{                          //caso nao tenha tido acidente nesta volta

                            idade= calcula_idade( i, par);
                            peso= par[i].pil.peso;                          //preparacaopara o calculo do tempo da volta
                            experiencia=par[i].pil.xp;
                            potencia=par[i].car.power;

                            classi->acidente=0;                                 //preenchimento dos dados da volta
                            classi->carID=par[i].car.id;
                            strcpy(classi->nome,par[i].pil.nome);
                            classi->pilotoID=par[i].pil.id;
                            classi->prox=NULL;
                            classi->tempo=calculaSegundos(idade, peso, experiencia, potencia, tamanho_pista);
                            idade= calcula_idade( i, par);
                            classi->idade=idade;
                            classi->tempo_total=( classi->tempo + atual->tempo_total);

                        }
                    }
                }
                                    //ordenacao dos resutadosna lista ligada
                if(i==0){                               //colocacao do par caso este seja o primeiro a ser simulado na volta
                    a->proxC=classi;

                }else{                              //colocacao do par caso este nao seja o primeiro a ser simulado na volta
                    atual=a->proxC;

                    if(classi->acidente!=0){                        //caso tenha tido acidente
                        while(atual->prox!=NULL){
                            atual=atual->prox;                          //procura o ultimo posicionado nessa volta ate ao momento
                        }
                        atual->prox=classi;                     //coloca este par acidentado em ultimo

                    }else{
                        atual=a->proxC;
                                                                        //caso nao tenha tido acidente
                        if(atual->acidente!=0){                                 //caso o primeiro tenha tido acidente
                            classi->prox=atual;
                            a->proxC=classi;
                        }else{
                            if(atual->tempo_total>classi->tempo_total){         // caso o tempo do primeiro seja pior que o tempo do que foi agora feito
                                classi->prox=atual;
                                a->proxC=classi;

                            }else{                                      //para os outros da lista

                                while( atual->prox != NULL && atual->prox->acidente==0 && atual->prox->tempo_total < classi->tempo_total){          //procura pela posicao anterior aquela em que a classificacao agora feita sera colocada
                                            atual=atual->prox;
                                }

                                if(atual->prox==NULL){                                              //caso a posicao onde for colocada seja a ultima
                                atual->prox= classi;

                                }else{                                                               //caso a posicao onde for colocada nao seja a ultima
                                    classi->prox=atual->prox;
                                    atual->prox=classi;
                                }
                            }
                        }
                    }
                }
            }
        }

                                //mostrar volta no ecra
        i=2;
        atual=a->proxC;
        if(atual->acidente==0){                 //CASO SEJA O PRIMEIRO
            printf("\n\n1 classificado:");
            printf("\nnome: %s", atual->nome);
            printf("\nid do carro: %d", atual->carID);
            printf("\ntempo desta volta: %d", atual->tempo);
            printf("\ntempo total: %d", atual->tempo_total);

        }else{
            printf("\n\n1 classificado:");
            printf("\nnome: %s", atual->nome);
            printf("\ndesistiu na volta: %d", atual->acidente);
        }
        do{                                     //RESTO DOS CLASSIFICADOS
            if(atual->prox->acidente==0){
                printf("\n\n%d classificado:",i );
                printf("\nnome: %s", atual->prox->nome);
                printf("\nid do carro: %d", atual->prox->carID);
                printf("\ntempo desta volta: %d", atual->prox->tempo);
                printf("\ntempo total: %d", atual->prox->tempo_total);

            }else{
                printf("\n\n%d classificado:", i);
                printf("\nnome: %s", atual->prox->nome);
                printf("\ndesistiu na volta: %d", atual->acidente);
            }

            i++;
            atual=atual->prox;

        }while(atual->prox!=NULL);

        if(Nvolta!=1){
            b->prox=a;
            b=a;
        }
        espera(5);       //_______________________________________colocar em  comentario para melhor teste ____________________________________________________________________________________________________________
    }

    reve_corrida(primeiro, voltas);             //funcao que ira permitir rever a corrida.

    return primeiro;
}
// a funcao guarda o valor de acidente corretamente. o erro encontra-se aquando mostrar.
//aquando da dimulacao de um campeonato, a funcao fica presa na 3 volta da 2 corrida.

void devolve( volta *Ivolta, carro *c, int Tc, piloto *p, int Tp){

    pClass atual;
    pVolta a;
    int i;

    for(i=0;i<Tc;i++){                          //retira 1 a avaria de cada carro avariado
        if(c[i].avaria!=0) c[i].avaria--;
    }

    for(i=0;i<Tp;i++){                              //retira 1 ao impedimento de cada piloto lesionado
        if(p[i].impedimento!=0) p[i].impedimento--;
    }




    a=Ivolta;
    while(a->prox!=NULL){                   //vai ate a ultima volta
        a=a->prox;
    }
    atual=a->proxC;

    printf("\n\n\n\t\t\t atual::::: %d", atual);


    while(atual!=NULL && atual->acidente==0){          //procura os pares que tiveram acidentes
        atual=atual->prox;
    }


    while(atual!=NULL){                     //quando os encontra comeca a distribuir os devidos impedimentos
        for(i=0;i<Tp; i++){                     //impedimento aos pilotos
            if(p[i].id==atual->pilotoID){
                p[i].xp--;                          //retirar a experiencia
                if(p[i].xp<0) p[i].xp=0;
                p[i].impedimento=2;                   //colocar o impedimento
                break;
            }
        }
        for(i=0;i<Tc;i++){                          //avarias de carros
            if(c[i].id==atual->carID);{
                c[i].avaria=1;
                break;
            }
        }
        atual=atual->prox;

    }
    a=Ivolta;                       // coloca o ponteiro a na primeira volta

    while(a!=NULL){
        atual=a->proxC;                         //coloca o ponteiro atual a apontar para o primeiro classificado da volta
        for(i=0;i<Tp;i++){
            if(p[i].id==atual->pilotoID){
                p[i].xp+=0.5;                                   //adiciona a experiencia ao vencedor da volta
                break;
            }
        }a=a->prox;
    }
}

void liberta(pVolta Ivolta){
    pVolta p, a;
    pClass i, j;

    a=Ivolta;
    p=Ivolta;

    while(Ivolta->prox!=NULL){                  //liberta tudo menos a 1 volta
        while(p->prox->prox!=NULL){         // p fica a pontar para a penultima volta disponivel
            p=p->prox;
        }
        a=p->prox;                                  // a fica a apontar para a ultima volta disponivel
        while(a->proxC!=NULL){
            i=a->proxC;
            while(i->prox->prox!=NULL){           //procura pelo penultimo lugar disponivel de cada volta
                i=i->prox;
            }
            j=i->prox;                      //j aponta para o ultimo
            free(j);
            i->prox=NULL;                   //o que era penultimo fica agora em ultimo e é colocado com valor NULL
            if(i->prox==NULL){            //caso seja o primeiro da volta;
                free(i);
                a->proxC=NULL;
            }
        }
        free(a);
        p->prox=NULL;
        p=Ivolta;
    }
                            //libertacao da primeira volta
    i=Ivolta->proxC;

    while(Ivolta->proxC!=NULL){
        while(i->prox->prox!=NULL)
            i=i->prox;                      //i aponta para o penultimo classificado disponivel
        j=i->prox;                      //j aponta para o ultimo classificado disponivel nessa volta
        free(j);                            //libertacao do ultimo classificado disponivel nessa volta
        i->prox=NULL;                   //o que era penultimo fica agora em ultimo e o ponteiro para o seguinte é colocado com valor NULL
        if(i->prox==NULL){            //caso seja o primeiro colocado da volta;
            free(i);                        //libertacao do primeiro colocado da primeira volta
            Ivolta->proxC=NULL;                //coloca o ponteiro para o primeiro classificado dessa volta a NULL, fazendo o cliclo parar
        }
    }
    free(Ivolta);                           //liberta o ponteiro para a primeira volta
}

void corri( int *j){

    printf("\n\n\t Numero de corridas:\t");                 //pede o numero de corridas
    scanf(" %d", j);                                //guarda diretamente o numero de corridas a ser feita
    if(*j>8 || *j<3){
        while(*j>8 || *j<3){                            //caso nao esteja em [3;8]
            printf("\n\tPor favor coloque um valor entre 3 e 8\n\tNumero de corridas:\t");
            scanf(" %d", j);
        }
    }
}

void paragem( int *p){

    printf("\n\n\n\t\tContinuacao");               // mostra as opcoes de continuacao
    printf("\n\t0-parar campeonato e encerrar programa");
    printf("\n\t1-continuar campeonato\n");
    scanf(" %d", p);
    if(*p!=0 && *p!=1){                 //pede para colocar 0 ou 1 repetidamente ate este valor ser colocado
        do{
            printf("\n\tPor favor coloque um valor valido:\n");
            scanf(" %d", p);
        }while(*p!=0 && *p!=1);
    }
}

pPonto cria_pontuacao( pVolta Ivolta){

    pVolta a=NULL;
    pClass atual=NULL;
    pPonto m=NULL, p=NULL, b=NULL;
    int i=1;


    a=Ivolta;
    while(a->prox!=NULL)            //faz o a apontar para a ultima volta
        a=a->prox;

    atual=a->proxC;
    while(atual!=NULL){
        m=malloc(sizeof(pontos));       //aloca memoria para fazer a struct pontos
        if(m==NULL){
            printf("\n\tErro ao alocar memoria");
            exit(0);
        }

        if(i==1) p=m; //guarda a posicao do primeiro no ponteiro p

                        //enche posicao
        m->idade=atual->idade;
        m->carID=atual->carID;
        m->pilotoID=atual->pilotoID;
        strcpy(m->nome, atual->nome);
        m->prox=NULL;
        if(b!=NULL){                //caso nao seja o primeiro, a ser feito, o anterior vai apontar para este, criando uma lista ligada
            b->prox=m;
        }
        m->acidente=atual->acidente;
                        //distribuicao de pontos
        if(i==1) m->pontos=5;
        else if(i==2 && atual->acidente==0) m->pontos=4;
        else if(i==3 && atual->acidente==0) m->pontos=3;
        else if(i==4 && atual->acidente==0) m->pontos=2;
        else if(i==5 && atual->acidente==0) m->pontos=1;
        else if(i>5 || atual->acidente!=0) m->pontos=0;
        if(atual->acidente==0)m->corridas=1;
        if(atual->acidente!=0)m->acidente=atual->acidente;

        b=m;            //coloca o b a apontar para o a, fazendo com que o b acabe por estar atras do a
        i++;
        atual=atual->prox;
    }

    return p;

}

pPonto pontuacao(pPonto pnts, pVolta Ivolta){
    pPonto p, a, s, e;
    pVolta m;
    pClass n;
    int i, verifica=0;

    m=Ivolta;
    while(m->prox!=NULL)    m=m->prox;      //coloca o m a apontar para a ultima volta

    n=m->proxC;             //coloca o n a pontar para o primeiro classificado na ultima volta( melhor classificado no fim da corrida)

                                //ATUALIZACAO DAS PONTUACOES

    for(i=1;i<6;i++){               //aumentar a pontuacao dos 5 primeiros classificados

    a=pnts;                 //coloca o a a apontar para o primeiro classificado em pontos totais

    while(n->carID!=a->carID) a=a->prox;           //procura pelo colocado, na lista de pontuacoes

        if(i==1 && a->acidente==0) a->pontos += 5;               //coloca a pontuacao correspondente á sua classificacao
        else if(i==2 && a->acidente==0) a->pontos += 4;
        else if(i==3 && a->acidente==0) a->pontos += 3;
        else if(i==4 && a->acidente==0) a->pontos += 2;
        else if(i==5 && a->acidente==0) a->pontos += 1;
        else if(i>5 || a->acidente!=0)  a->pontos += 0;
        a->acidente=n->acidente;
    }
            //VOLTAS
    a=pnts;
    while(a!=NULL){                 //aumenta o numero de corridas feitas pelos piltos
        if(a->acidente==0) a->corridas++;
        a=a->prox;
    }


            //ORDENACAO
printf("\n\n\n\n\n\n\\t\t\t\tentrou");
do{
   verifica=0;                         //coloca sempre a variavel verifica a zero
    s=pnts->prox->prox;                 //coloca o ponteiro a a apontar para o segundo classificado em pontos totais, vai funcionar como "seguinte" ao ponteiro "principal"
    p=pnts;                 //coloca o ponteiro p a apontar para o primeiro classificado em pontos totais
    e=pnts->prox;       //vai funcionar como ponteiro "principal"
    a=pnts;      // vai funcionar como ponteiro "anterior" ao "principal"

    //caso do primeiro lugar
    printf("\n\t %d", verifica);
    if(a->pontos<e->pontos){            //caso a segundo tenha mais pontos que o primeiro, trocam a posicao
        p=e;
        a->prox=s;
        e->prox=a;
        verifica=1;

    }else if(e->pontos==a->pontos){             //caso os 2 primeiros tenham os mesmos pontos, trocam a posicao
        if(a->corridas<e->corridas){                //caso o segundo tenha mais corridas que o primeiro, trocam a posicao
            p=e;
            a->prox=s;
            e->prox=a;
            verifica=1;

        }else if(a->corridas==e->corridas){         //caso os 2 primeiros tenham o mesmo numero de corridas
            if(a->idade>e->idade){                      //caso o segundo seja mais novo que o primeiro, trocam a posicao
                p=e;
                a->prox=s;
                e->prox=a;
                verifica=1;
            }
        }
    }
    printf("\n\t , fez o primeiro");
    //todo o resto da lista

    while( a!=NULL){
        verifica=0;
        if(a->pontos<s->pontos){            //se o seguinte tiver melhor pontuacao que a "atual", mudam a posicao
            verifica=1;
            a->prox=s;
            e->prox=s->prox;
            s->prox=e;

        }else if(a->pontos==s->pontos){
           if(e->corridas<a->corridas){                //caso o seguinte tenha mais corridas que o atual, trocam a posicao
            a->prox=s;
            e->prox=s->prox;
            s->prox=e;
            verifica=1;

            }else if(a->corridas==e->corridas){         //caso os seguinte e atual tenham o mesmo numero de corridas
                if(a->idade>e->idade){                      //caso o seguinte seja mais novo que o atual, trocam a posicao
                    a->prox=s;
                    e->prox=s->prox;
                    s->prox=e;
                    verifica=1;
                }
            }
        }
        if(verifica==1){
            a=p;
            e=p->prox;
            s=p->prox->prox;

        }
        s=s->prox;
        a=s->prox;
        e=e->prox;

    }


}while(verifica!=0);            //faz enquanto houver problemas na colocacao na lista
    printf("\n\n\n\n\n\n\\t\t\t\tsaiu");

    return p;                                                   //devolve o endereco do primeiro classificado
}

void mostra_pontuacao_final(pPonto pnts){

    pPonto a;
    int i=1;

    a=pnts;                     // coloca o ponteiro 'a' a apontar para o peimrio classificado

    while(a!=NULL){                         //mostra as informacoes dos classificados
        printf("\n\n\t\t\t %d classificado", i);
        printf("\n\t nome: %s", a->nome);
        printf(" \n\t pontuacao: %d",a->pontos);
        printf("\n\t id carro: %d", a->carID);
        printf("\n\t numero de corridas em que participou: %d", a->corridas);
        printf("\n\t idade: %d", a->idade);
        i++;
        a=a->prox;
    }

}

void limpa_campeonato(pPonto pnts){
    pPonto a,b;



    while(pnts->prox!=NULL){                //faz o while ate libertar todos exceto o primeiro classificado no campeonato
        a=pnts;                                 //coloca o ponteiro 'a' a apontar para o primeiro classificado
        while(a->prox->prox!=NULL){             //avanca com o ponteiro 'a' ate chegar ao penultimo lugar
            a=a->prox;
        }
        b=a->prox;                  //coloca o b a apontar para o ultimo cassificado disponivel
        free(b);                    //liberta o ultimo
        a->prox=NULL;               // coloca o -agora- ultimo ( que era penultimo antes da libertacao do b) com ponteiro prox para NULL
    }
    free(pnts);                     //no final liberta o primeiro classificado

}
