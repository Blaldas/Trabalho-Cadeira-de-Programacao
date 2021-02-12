// Marco António Ferreira Domingues
// Aluno número 21280422

#ifndef PILOTOS_H_INCLUDED
#define PILOTOS_H_INCLUDED
#define N 100
typedef struct pilotos piloto, *pPiloto;
typedef struct carros carro, *pCarro;

typedef struct{                 //estrutura usada para guardar uma data
    int ano, mes, dia;
}data;
struct pilotos{         //estrutura que le e  guarda toda a informcao existente dos piltos
    char nome[N];
    int id;
    data born;
    float peso;
    float xp;
    int impedimento;
};
struct carros{                  //estrutura que le e guarda toda a informacao existente dos carros
    int id;
    int power;
    int avaria;
};
typedef struct par_carros_pilotos par,*pPar;                    //estrutura que é usada na cricao dos pares piloto-carro
struct par_carros_pilotos{                                          //contem toda a informacao sobre os carros e os pilotos
    carro car;
    piloto pil;
    par *prox;
};

typedef struct classificado tempo, *pClass;
struct classificado{                                        //estrutura que é usada para guardar informacao relativa a cada volta de um determminado par piloto-carro
    char nome[N];
    int carID, tempo, acidente, pilotoID, tempo_total, idade;
    pClass prox;
};
typedef struct voltas volta, *pVolta;                           //estrutura usada para "guardar" as voltas
struct voltas{
    int volta_n;
    pVolta prox;
    pClass proxC;
};

typedef struct pontuacao pontos, *pPonto;                   //estrutura usada na criacao do array dinamico que permite guardar as pontuacoes dos pilotos em campeonatos
struct pontuacao{
    int pontos, carID, pilotoID, idade, acidente, corridas;
    char nome[N];
    pPonto prox;
};




pPiloto conta_pilotos(int  *a);
pCarro conta_carros(int *a);
int lePilotos(piloto a[]);
int leCarros(carro a[]);
void  penaliza(pPiloto p, int Tp);

void mostra_pilotos(piloto *a, int tp);
void mostra_carros(carro *c, int tp);



int dados(carro *c,int Tc,piloto *p,int Tp);
pPar cria_par(int tp_final, carro *c, int Tc,piloto *p,int Tp);
pVolta faz_voltas(pPar par,int tp, pPiloto p, int Tp);
void devolve( pVolta Ivolta, carro *c, int Tc, piloto *p, int Tp);
void liberta(pVolta Ivolta);

pPonto cria_pontuacao( pVolta Ivolta);
pPonto pontuacao(pPonto pnts, pVolta Ivolta);
void corri( int *j);
void paragem( int *p);
void mostra_pontuacao_final(pPonto pnts);
void limpa_campeonato(pPonto pnts);

void reescritura(pCarro c,int Tc,pPiloto p,int Tp);

#endif // PILOTOS_H_INCLUDED
