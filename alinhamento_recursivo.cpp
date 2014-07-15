#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//-	  A	  G	  C	  T
//A	 10	 -1	 -3	 -4
//G	 -1	  7	 -5	 -3
//C	 -3	 -5	  9	  0
//T	 -4	 -3	  0	  8

int custo[4][4] = {10,-1,-3,-4,-1,7,-5,-3,-3,-5,9,0,-4,-3,0,8};


int gap = -5;

int alfa(char a, char b);
int alinhamento (char *seq1, char *seq2, char *novaseq1, char *novaseq2,int i,int j);



int alinhamento (char *seq1, char *seq2, char *novaseq1, char *novaseq2,int i,int j) {
    
    if(i == -1 && j==-1) {
         return 0;
    }
    if(i==-1) {
             for(int r=0;r<j+1;r++) {
                     novaseq1[r] = seq1[r];
                     novaseq2[r] = '-';
                     novaseq1[r+1] = 0;
                     novaseq2[r+1] = 0;
             }
             
             return (j+1)*gap;
    }
    if(j==-1) {
             for(int r=0;r<i+1;r++) {
                     novaseq1[r] = '-';
                     novaseq2[r] = seq2[r];
                     novaseq2[r+1] = 0;
                     novaseq1[r+1] = 0;
             }
             return (i+1)*gap;
    }
    
    
    
    char seq1op1[100];
    char seq2op1[100];
    strcpy(seq1op1,novaseq1);
    strcpy(seq2op1,novaseq2);
    char seq1op2[100];
    char seq2op2[100];
    strcpy(seq1op2,novaseq1);
    strcpy(seq2op2,novaseq2);
    char seq1op3[100];
    char seq2op3[100];
    strcpy(seq1op3,novaseq1);
    strcpy(seq2op3,novaseq2);
    int n;
    
    int op1 = alfa(seq1[j],seq2[i]) + alinhamento(seq1,seq2,seq1op1,seq2op1,i-1,j-1);
    
    int op2 = gap + alinhamento(seq1,seq2,seq1op2,seq2op2,i,j-1);
    
    int op3 = gap + alinhamento(seq1,seq2,seq1op3,seq2op3,i-1,j);
    
    
    if(op1>=op2 && op1>= op3) {
               n = strlen(seq1op1);
               seq1op1[n] = seq1[j];
               seq2op1[n] = seq2[i];
               seq1op1[n+1] =0;
               seq2op1[n+1] =0;
               strcpy(novaseq1,seq1op1);
               strcpy(novaseq2,seq2op1);
               return op1;
    }
    if(op2 > op3) {
           n = strlen(seq1op2);
           seq1op2[n] = seq1[j];
           seq2op2[n] = '-';
           seq1op2[n+1] =0;
           seq2op2[n+1] =0;
           strcpy(novaseq1,seq1op2);
           strcpy(novaseq2,seq2op2);
           return op2;
    }
     n = strlen(seq1op3);
     seq1op3[n] = '-';
     seq2op3[n] = seq2[i];
     seq1op3[n+1] =0;
     seq2op3[n+1] =0;
     strcpy(novaseq1,seq1op3);
     strcpy(novaseq2,seq2op3);
     return op3;
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





int main () {
    char seq1[100];
    char seq2[100];
    char novaseq1[100]="";
    char novaseq2[100]="";
    int ntestes;
    int n;
    int m;
    
    scanf("%d", &ntestes);
    
    
    int cus;
    
    for(int i=0;i<ntestes;i++) {
            scanf("%s", seq1);
            scanf("%s", seq2);
            n = strlen(seq1);
            m = strlen(seq2);
            
            //funcao recursiva que resolve o problema
            cus = alinhamento(seq1,seq2,novaseq1,novaseq2,m-1,n-1);
            printf("Custo: %d",cus);
            printf("\nAlinhamento:  \n");
            printf("%s \n",novaseq1);
            printf("%s \n",novaseq2);
            strset(novaseq1,0);
            strset(novaseq2,0);
            printf("\n");
    }
    return 0;
}
