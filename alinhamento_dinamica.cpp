#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Elemento {
     int ele;
     int i,j;
}elemento;
  

//-	  A	  G	  C	  T
//A	 10	 -1	 -3	 -4
//G	 -1	  7	 -5	 -3
//C	 -3	 -5	  9	  0
//T	 -4	 -3	  0	  8

int custo[4][4] = {10,-1,-3,-4,-1,7,-5,-3,-3,-5,9,0,-4,-3,0,8};


int gap = -5;


int max(int opcao1, int opcao2, int opcao3, int *op);
void alinhamento(char* seq1, char* seq2, elemento **c);
int alfa(char a, char b);
int resposta (elemento **c, char *seq1, char *seq2, char *novaseq1, char *novaseq2, int i, int j, int tamanho);



void alinhamento(char* seq1, char* seq2, elemento ***c) {
    
    int n = strlen(seq1); // sequencia um fica nas colunas
    int m = strlen(seq2); // sequencia dois fica nas linhas
    
    //criando a matriz de tamanho n*m dinamicamente
    
    *c = (elemento **) malloc( (m+1) * sizeof(elemento *) );
    
    for (int i = 0; i < m+1; i++)
       (*c)[i] = (elemento *) malloc( (n+1) * sizeof (elemento));
    
    
    //preenchendo a primeira colunha com o custo de gap
    (*c)[0][0].ele = 0;
    (*c)[0][0].i = -1;
    (*c)[0][0].j = -1;
    for (int i = 1; i <m+1; i++) {
        (*c)[i][0].ele = gap*i;
        (*c)[i][0].i = i-1;
        (*c)[i][0].j = 0;
    }
    
    //preenchendo a primeira linha com o custo de gap
    
    for (int i = 1; i <n+1; i++) {
        (*c)[0][i].ele = gap*i;
        (*c)[0][i].i = 0;
        (*c)[0][i].j = i-1;
    }
    
    
    //preenchendo a matriz com os custos
    
    int op;
    
    for (int i=1;i<m+1;i++) {
        for (int j=1;j<n+1;j++) {
            
            //descobrindo o maior custo
            
            (*c)[i][j].ele = max( alfa(seq1[j-1],seq2[i-1]) + (*c)[i-1][j-1].ele , gap + (*c)[i][j-1].ele , gap + (*c)[i-1][j].ele , &op);
            
            
            //preenchendo de onde o valor veio, ou seja, a setinha
            
            if(op==1) {
                  (*c)[i][j].i = i-1;
                  (*c)[i][j].j = j-1;
            } 
            else {
                   if(op==2) {
                         (*c)[i][j].i = i;
                         (*c)[i][j].j = j-1;
                   } 
                   else {
                         (*c)[i][j].i = i-1;
                         (*c)[i][j].j = j;
                   }
            }
            
            
            
            
        }
        
    }
    
}
  


int max(int opcao1, int opcao2, int opcao3, int *op) {
    
    
    if(opcao1 >= opcao2 && opcao1 >= opcao3) {
              *op = 1;
              return opcao1;          
    }
    if(opcao2 > opcao3) {
              *op = 2;
              return opcao2;          
    }
    *op = 3;
    return opcao3; 
}  




int alfa(char a, char b) {
    int i,j;
    
    
    if(a=='A') {
               i = 0;
    }
    else {
         if(a=='G') {
                   i=1;
         }
         else {
              if(a=='C') {
                         i=2;
              }
              else {
                   i=3;
              }
         }
    }
    
    if(b=='A') {
               j = 0;
    }
    else {
         if(b=='G') {
                   j=1;
         }
         else {
              if(b=='C') {
                         j=2;
              }
              else {
                   j=3;
              }
         }
    }
    
    return custo[i][j];
}



int resposta (elemento **c, char *seq1, char *seq2, char *novaseq1, char *novaseq2, int i, int j, int tamanho) {
    
    if(i == 0 && j==0) {
         return tamanho;
    }
    
    elemento per = c[i][j];
    int posicao;
    
    if(per.i == i-1 && per.j == j-1) {
             
             tamanho = resposta(c, seq1, seq2, novaseq1, novaseq2, i-1, j-1, tamanho);
             posicao = strlen(novaseq1);
             novaseq1[posicao] = seq1[j-1];
             novaseq2[posicao] = seq2[i-1];
             if (seq1[j-1] == seq2[i-1]) {
                tamanho++;
             }
             return tamanho;
    }
    if(per.i == i && per.j == j-1) {
             tamanho = resposta(c,seq1,seq2,novaseq1,novaseq2,i,j-1,tamanho);
             posicao = strlen(novaseq1);
             novaseq1[posicao] = seq1[j-1];
             novaseq2[posicao] = '-';
             
                          
             return tamanho;
    }
    tamanho = resposta(c,seq1,seq2,novaseq1,novaseq2,i-1,j,tamanho);
    posicao = strlen(novaseq1);
    novaseq1[posicao] = '-';
    novaseq2[posicao] = seq2[i-1];
             
    return tamanho;
    
    
}


int main() {
    
    elemento **mat;
    int ntestes;
    char sequencia1[100];
    char sequencia2[100];
    char novaseq1[200]= "";
    char novaseq2[200]= "";
    //tamanho = quantidade de elementos iguais
    int tamanho;
    //n = tamanho sequencia 1
    int n;
    //m = tamanho sequencia 2
    int m;
    
    //ntestes é a quantidade de testes que terei no meu programa
    
    scanf("%d", &ntestes);
    
    // esse for pega as 2 proximas sequencias e resolve o problema pra elas, e assim para todo o par de sequencias
    for(int i=0;i<ntestes;i++) {
            scanf("%s", sequencia1);
            scanf("%s", sequencia2);
            n = strlen(sequencia1);
            m = strlen(sequencia2);
            //funcao que cria a matriz
            alinhamento(sequencia1,sequencia2,&mat);
            //funcao recursiva que pega o resultado e coloca
            tamanho = resposta(mat,sequencia1,sequencia2,novaseq1,novaseq2,m,n,0);
            printf("Tamanho: %d",tamanho);
            printf("\nAlinhamento:  \n");
            printf("%s \n",novaseq1);
            printf("%s \n",novaseq2);
            strset(novaseq1,0);
            strset(novaseq2,0);
            free(&mat);
            printf("\n");
    }
    return 0;
}


