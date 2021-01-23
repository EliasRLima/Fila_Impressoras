#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX 3

//alunos: Elias Lima e Italo

struct tipo_impressora{
    int livre;
    int id;
};

struct tipo_documento{
    int numPags;
    char nome[100];
    char link[1000];
};

struct tipo_impressao{
    struct tipo_documento documento;
    struct tipo_impressora imp;
    int numImpressas;
};

typedef struct tipo_documento doc;
typedef struct tipo_impressora impressora;
typedef struct tipo_impressao elemento;

const doc VL_DOC_NULO = {0, NULL, NULL};
const impressora VL_IMP_NULO = {0, -1};
const elemento VL_NULO = {0, NULL, 0, NULL, 0, 0, NULL};

#include "TadFilaDin.c"

int inicializa_impressora(impressora *i,int id){
      i->id = id;
      i->livre = 1;
      return 1;
}

int cont=0;

int cadastrar_documento(doc *documento){
      int i;
      printf("Digite o numero de paginas: ");
      scanf("%d",&i);
      documento->numPags = i;
      
      printf("Digite o nome do arquivo: ");
      fflush(stdin);
      gets(documento->nome);
      fflush(stdin);

      printf("Entre com o link do arquivo! exemplo: 'C:/Desktop' Digite: ");
      fflush(stdin);
      gets(documento->link);
      fflush(stdin);

}
elemento getPRImeiro(tipo_fila fila)
{
  return (fila.inicio)->elem;
}

void removerPrimeiro(tipo_fila fila, elemento *n)
{
  	ptrNodo pnodo;

	
		pnodo = fila.inicio;
		fila.inicio = fila.inicio->prox;
		*n = pnodo->elem;
		free(pnodo);
		if (fila.inicio == NULL)
			fila.fim = NULL;
		fila.tamanho--;
		

}

int imprimir(tipo_fila *fila, time_t tempo_inicio){
       if(!tamanho(*fila)){
          printf("Sem documentos na fila!\n");
          system("pause");
          return;
       }
       
       time_t atual;
       time(&atual);
       impressora impressoras[MAX];
       int i;
       for(i=0; i<MAX; i++){
          inicializa_impressora((impressoras+i),i);
       }
       
       int t = tamanho(*fila);
       elemento na[MAX];
       elemento e;
        for(i =0; i<MAX; i++){
            if(impressoras[i].livre && t > 0){
                primeiroFila(*fila, &e);
                na[i] = e;
                sairElemento(fila, &e);
                if(na[i].imp.id == -1 && impressoras[i].livre){ 
                    na[i].imp = impressoras[i]; 
                    impressoras[i].livre = 0; 
                }
                t--;
            }
        }
        int numlivres = 0;
        
       while(1){

           numlivres = 0;

           for(i=0; i< MAX; i++){
              if(impressoras[i].livre == 1){
                 numlivres++;
              } 
           }

           if(numlivres == MAX){
              printf("\n\nTodos os documentos foram impressos!\n");
              return; //finalizou impressao
           }

           int imp = 0;
           for(i = 0; i < MAX; i++){
             if(impressoras[i].livre = 0){ 
                imp = 1;
                printf("Impressora %d:\nDocumento %s\nImprimindo pag %d\n", i+1, na[i].documento.nome, na[i].numImpressas);
                na[i].numImpressas++;
                if(na[i].numImpressas == na[i].documento.numPags){
                   impressoras[i].livre = 1;
                }
             }else{
                printf("Impressora %d:\nA impressora esta livre arguardando documento\n", i+1);
             }
           }
           
           if(imp){
              while(difftime(atual, tempo_inicio) <= 2.5) // delay
              time(&atual);
           }
           tempo_inicio = atual;

           int t = tamanho(*fila);
           for(i=0; i< MAX; i++){
            if( na[i].numImpressas == na[i].documento.numPags){
             if(tamanho > 0){
                 primeiroFila(*fila, &e);
                 na[i] = e;
                 na[i].imp = impressoras[i];
                 impressoras[i].livre = 0;
                 sairElemento(fila, &e);
             }else{
               impressoras[i].livre = 1;
             }
            }
           }
       }
       
}

int main() {
   int i;
   int menu;
   tipo_fila fila;
   criarFila(&fila);
   doc VL_DOC;
   struct tm *data_hora_atual;
   time_t segundos;

   do{
      system("cls");
   printf("MENU:\n1.Cadastrar Documento\n2.Iniciar impressao\n4.Sair\nEscolha: ");
   scanf("%d",&menu);
   switch(menu)
   {
     case 1:
        cadastrar_documento(&VL_DOC);
        elemento e;
        e.numImpressas = 0;
        e.documento = VL_DOC;
        e.imp = VL_IMP_NULO;
        entrarElemento(&fila, e);
        break;

     case 2:
        printf("Impressao iniciada!\n");
        time(&segundos);
        imprimir(&fila, segundos);
        break;
   }
   }while(menu!=4);
   


}
