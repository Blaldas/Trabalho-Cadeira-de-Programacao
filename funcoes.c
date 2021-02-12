// Marco António Ferreira Domingues
// Aluno número 21280422

#include <stdio.h>
#include <stdlib.h>
#include "pilotos.h"
#include "utils.h"

pPiloto conta_pilotos(int *a){  //funcao que tem como objetivo indcar o numeor de cilotos no ficheiro e alocar a memoria necessaria para os guardar
    FILE *f;
    pPiloto p;

    f= fopen("pilotos.txt", "r");           //abre o ficheiro onde estao os pilotos
    if(f==NULL){
        printf(" \n\tERRO FATAL!\nErro ao ler pilotos.txt\n");
        exit(0);
    }


    while(!feof(f)){                    //conta o numeor de pilotos que la estão
        fscanf(f,"%*99[^\n]");
        fscanf(f,"\n");
        fscanf(f," %*d %*d %*d %*d %*d %*f %*d");
        fscanf(f,"\n\n");
        (*a)++;
    }

    fclose(f);

    p= malloc(*a*sizeof(piloto));           //aloca um array dinamico com o tamanho necessario para guardar a informacao do ficheiro
    if(p==NULL){
        printf("\nERRO FATAL!\n");
        exit(0);

    }
    return p;                   //devolve o endereco para a primeira casa do array alocado
}

pCarro conta_carros(int *a){        //funcao que tem como objetivo indcar o numeor de carros no ficheiro e alocar a memoria necessaria para os guardar
    FILE *f;
    pCarro c;

    f= fopen("carros.txt", "r");                    //abre o ficheiro onde estao os carros
    if(f==NULL){
        printf(" \nERRO FATAL!\nErro ao ler pilotos.txt\n");
        exit(0);
    }

     while(!feof(f)){               //conta o numeor de carros que la estão
        fscanf(f," %*d %*d %*d");
        fscanf(f,"\n\n");
        (*a)++;
    }

    c= malloc(*a*sizeof(carro));         //aloca um array dinamico com o tamanho necessario para guardar a informacao do ficheiro
    if(c==NULL){
        printf("\nERRO FATAL!\n");
        return 0;
    }
    return c;                       //devolve o endereco para a primeira casa do array alocado



}

int lePilotos(piloto a[]) {          //função que trata de guardar os plotos do ficheiro para a memoria

    int t,i;
    FILE *f;

    f= fopen("pilotos.txt", "r");   //abre o ficheiro onde estao os pilotos
        if(f==NULL){
            printf(" \nErro ao ler pilotos.txt\n");
            return 0;
        }




    for(t=0; !feof(f); t++){                //guarda todos os pilotos listados no ficheiro no array previamente alocado

        fscanf(f,"%99[^\n]", a[t].nome);
        fscanf(f,"\n");
        fscanf(f," %d %d %d %d %f %f %d", &a[t].id, &a[t].born.dia, &a[t].born.mes, &a[t].born.ano, &a[t].peso, &a[t].xp, &a[t].impedimento);
        fscanf(f,"\n\n");


        /*VERIFICACOES*/

        if(t!=0){
            for(i=0; i<t; i++){
                if(a[i].id==a[t].id){                                     //testa id
                    printf("\n\tERRO!\nExistem 2 ou mais pilotos com o mesmo id!\n\t id= %d", a[i].id);
                return -1;
                }
            }
        }
        if(a[t].impedimento>3 || a[t].impedimento<0){                 //testa impedimento
            printf("\n\tERRO!\n O condutor com id %d contem um impedimento invalido!", a[t].id);
            return -1;
        }
        else if(a[t].born.ano>2019){                                      //teste ano de nascimento
            printf("\n\tERRO!\nO condutor com id %d contem um ano de nascimento invalido!",a[t].id);
            return -1;

        }else if(a[t].born.mes<1 || a[t].born.mes>12){                    //testa mes de nascimento
            printf("\n\tERRO!\nO condutor com id %d contem um mes de nascimento invalido!",a[t].id);
            return -1;

        }else if((a[t].born.mes==1 || a[t].born.mes==3 || a[t].born.mes==5 || a[t].born.mes==7 || a[t].born.mes==8  || a[t].born.mes==3   || a[t].born.mes==10  || a[t].born.mes==12) && (a[t].born.dia<1 || a[t].born.dia>31)){ //nascido num mes com 31 dias
            printf("\n\tERRO!\nO condutor com id %d contem um dia de nascimento invalido!",a[t].id);
            return -1;

        }else if((a[t].born.mes==4 ||a[t].born.mes==6 ||a[t].born.mes==9 ||a[t].born.mes==11)&& (a[t].born.dia<1 || a[t].born.dia>30)){//nascido num mes com 30 dias
            printf("\n\tERRO!\nO condutor com id %d contem um dia de nascimento invalido!",a[t].id);
            return -1;

        }else if ((a[t].born.mes==2) && (a[t].born.ano%4==0) && (a[t].born.dia<1 || a[t].born.dia>29 )){                  //nascido en fevereiro
            printf("\n\tERRO!\nO condutor com id %d contem um dia de nascimento invalido!",a[t].id);
            return -1;

        }else if ((a[t].born.mes==2) && (a[t].born.ano%4!=0) && (a[t].born.dia<1 ||  a[t].born.dia>28 )){                 //nascido em fevereiro
            printf("\n\tERRO!\nO condutor com id %d contem um dia de nascimento invalido!",a[t].id);
            return -1;

        }else if (a[t].peso<=0 &&a[t].peso>500){                       //verifica peso
            printf("\n\tERRO!\nO condutor com id %d contem um peso invalido!",a[t].id);
            return -1;

        }

    }
    fclose(f);

    return t;
}

int leCarros(carro a[]){        //função que trata de guardar os carros do ficheiro para a memoria
    int t, i;
    FILE *f;


    f= fopen("carros.txt","r");          //abre o ficheiro onde estao os carros
    if(f==NULL){
        printf(" \nErro ao ler carros.txt\n");
        return 0;
    }

    for(t=0; !feof(f); t++){                //guarda todos os carros listados no ficheiro no array previamente alocado
        fscanf(f," %d %d %d", &a[t].id, &a[t].power, &a[t].avaria);
        fscanf(f,"\n");


    //verificações

        for(i=0;i<t;i++){
            if(a[i].id==a[t].id){           //verifica o id unico
                printf("\n\tERRO!\nExistem 2 ou mais carros com o mesmo id!\n\t id= %d", a[i].id);
                return -1;
            }
        }
        if(a[t].power<0){               //verifica se a potencia é valida
            printf("\nERRO!\nO carro com id %d tem uma potencia invalida!", a[t].id);
            return -1;

        }else if( a[t].avaria!=0 && a[t].avaria!=1){            //verifica se o valor da avaria é valido
            printf("\nERRO!\nO carro com id %d tem um valor de avaria invalido!", a[t].id);
            return -1;

        }
    }
    fclose(f);
    return t;                   //devolve o numero de carros

}

void mostra_pilotos(piloto *a, int tp){         //função que mostra a lista de pilotos e as suas caracteristicas
    int i;

    printf("\n\n\t\tLista de pilotos");

    for(i=0; i<tp; i++){
        printf("\n nome: %s \n",a[i].nome);
        printf(" id: %d \n",a[i].id);
        printf(" data de nascimento: %d - %d - %d", a[i].born.dia, a[i].born.mes, a[i].born.ano);
        printf("\n peso: %f", a[i].peso);
        printf("\n experiencia: %f", a[i].xp);
        printf("\n impedimento: %d\n\n", a[i].impedimento);
    }
}

void mostra_carros(carro *c, int tp){       //função que mostra a lista de carros e o seu estado
    int i;

    printf("\n\n\t\tLista de carros");

    for(i=0;i<tp; i++){
        printf("\n id: %d", c[i].id);
        printf("\n potencia: %d", c[i].power);
        printf("\n avaria: %d\n\n", c[i].avaria);

    }
}

void reescritura(pCarro c,int Tc,pPiloto p,int Tp){

    int i;
    FILE *f;
    pPiloto a;
    pCarro b;

                //ESCREVER PILOTOS

    f=fopen("pilotos.txt","w");
    if(f==NULL){
        printf("\n\tErro na devolucao de dados");
    }

    a=p;

    for(i=0;i<Tp; i++){
        fprintf(f, "%s", a[i].nome);
        fprintf(f,"\n");
        fprintf(f,"%d %d %d %d %.1f %.1f %d", a[i].id, a[i].born.dia, a[i].born.mes, a[i].born.ano, a[i].peso, a[i].xp, a[i].impedimento);
        fprintf(f,"\n\n");
    }

    fclose(f);

                //ESCREVER CARROS

    f=fopen("carros.txt","w");
    if(f==NULL){
        printf("\n\tErro na devolucao de dados");
    }

    b=c;
    for(i=0;i<Tc;i++){
        fprintf(f,"%d %d %d", b[i].id, b[i].power, b[i].avaria);
        fprintf(f,"\n\n");



    }














}

void  penaliza(pPiloto p, int Tp){

    int i, j,pena, f=2;

    printf("\n\n\t id do piloto que sera punido:\t");                       //id do piloto a ser penalizado
    scanf(" %d", &i);
    do{
        printf("\n\n\tNumero de corridas que ficara suspenso:\t");                //valor da penalizacao
        scanf(" %d", &pena);

        if(pena<1 || pena>3){
            printf("\n\n\tPor favor coloque um valor entre 1 e 3\n");               //caso o valor nao seja adequado
        }
    }while(pena<1 || pena>3);                                       //ciclio que será feito até dar um valor adequando


    for(j=0;j<=Tp;j++){                         //procura do piloto com o id correspondente
        if(p[j].id==i){                             //caso seja o piloto com o id correspondente
            p[j].impedimento+=pena;                             //aumento do impedimento do piloto correspondente
            f=0;                                    //colocacao da variavel f a zero
            break;                                  //paragem imediata do ciclo
        }
    }

    if(f==2){                                   //caso nao tenha sido encontrado nenhum piloto com o id correspondente
        printf("\n\n\n\n\t  nenhum piloto tem o id %d", i);

    }else{
        printf("\n\n\n\n\t Piloto penalizado:\n");
        printf("\n\t nome: %s", p[j].nome);
        printf("\n\t penalizacao total: %d", p[j].impedimento);
    }


    espera(2);

}

