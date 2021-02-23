#include<stdio.h>
#include<stdlib.h>
#include <math.h>

struct cola {
    char dato;
    struct cola *prim,*ult;
};

void mostrarDatos(struct cola *p);

int main(){

    struct cola *p=NULL,*u=NULL,*aux=NULL;

    int i;

    aux=(struct cola*)malloc(sizeof(struct cola));
     if(!aux){
        printf("No hay suficiente memoria disponible.\n");
         exit(1);
     }
     printf("Cargando datos.\n");
      for(i=0; i<91;i+5){
       aux->dato =sin(i*0.017453)*127;
        if(!p){
            p=u=aux;
            p->prim=NULL;
            p->ult=NULL;
        }
        else{
            aux->ult=NULL;
            aux->prim=u;
            u->ult=aux;
            u=aux;
        }
      }
     printf("\nSe han cargado los datos.\n");
     printf("\nDatos cargados:\n");
      aux=p;
        while(aux!=NULL){
         printf("%d",aux->dato);
          aux=aux->ult;
         }
      aux=u;
      while(aux!=NULL){
        printf("%d",aux->dato);
        aux=aux->prim;
      }
      aux=p;
      aux->dato|(1<<7);
      while(aux!=NULL){
        printf("%d",aux->dato);
        aux=aux->prim;
      }
      aux->dato|(1<<7);
      aux=u;
      while(aux!=NULL){
        printf("%d",aux->dato);
        aux=aux->prim;
      }
        printf("Fin del programa.\n");
    return 0;
}
