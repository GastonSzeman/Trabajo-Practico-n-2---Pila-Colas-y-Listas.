#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct {
    char desc[60];
    unsigned char potencia;
    unsigned int estado;
}datos_t;

struct lista{
    datos_t datos;
    struct lista *siguiente,*anterior;
};

int main(){
    datos_t data;
    FILE *p_archivo;
    int op;
    struct lista *aux=NULL,*lista=NULL,*local=NULL;
    char opc;

    do{
         if((p_archivo=fopen("potencia.dat","ab"))==NULL){
            printf("ERROR: 'potencia.dat'.\n");
             return -1;
        }
        aux=(struct lista*)malloc(sizeof(struct lista));
         if(!aux){
            printf("ERROR: Memoria.\n");
             return -2;
         }
        fflush(stdin);
        printf("\nDescripcion: ");
         scanf("%s",&aux->datos.desc);
        fflush(stdin);
        printf("\nPotencia: ");
         scanf("%d",&aux->datos.potencia);
         aux->datos.estado=aux->datos.desc[0]*aux->datos.potencia;
          if(lista==NULL){
            lista=aux;
            lista->siguiente=NULL;
            lista->anterior=NULL;
          }
          else{
            local=lista;
             while((local->datos.potencia <= aux->datos.potencia) && (local->siguiente!=NULL)){
                local = local->siguiente;
             }
             if(local->datos.potencia > aux->datos.potencia){
                if(local->anterior!=NULL){
                    aux->anterior->siguiente=aux;
                }
                else{
                    lista=aux;
                }
                aux->anterior= local->anterior;
                local->anterior=aux;
                aux->siguiente=local;
             }
             else{
                local->siguiente=aux;
                aux->anterior=local;
                aux->siguiente=NULL;
             }
          }
          fwrite(&data,sizeof(struct lista),1,p_archivo);
          fflush(stdin);
        printf("S - Seguir ingresando datos.\n");
         scanf("%s",&opc);
    }while(toupper(opc)=='S');
    fclose(p_archivo);
    printf("***IMPRIMIENDO DATOS.***\n");

    do{
       if((p_archivo=fopen("potencia.dat","rb"))==NULL){
            printf("ERROR: 'potencia.dat'.\n");
             return -3;
       }
       printf("1 - Mayor a menor.\n2 - Menor a mayor.\n3 - Liberar memoria y salir.\n");
        scanf("%d",&op);
         if(op==2){
            local=lista;
            do{
            printf("-----------------------------------------------------\n");
            printf("Descripcion: %s.\n",local->datos.desc);
            printf("Potencia: %d.\n",local->datos.potencia);
            printf("Estado: %d.\n",local->datos.estado);
            printf("-----------------------------------------------------\n");
             local= local->siguiente;
         }while(local->siguiente!=NULL);
            printf("-----------------------------------------------------\n");
            printf("Descripcion: %s.\n",local->datos.desc);
            printf("Potencia: %d.\n",local->datos.potencia);
            printf("Estado: %d.\n",local->datos.estado);
            printf("-----------------------------------------------------\n");
        }
       if(op==1){
            local=lista;
          while((local->siguiente!=NULL)){
            local=local->siguiente;
          }
          do{
            printf("-----------------------------------------------------\n");
            printf("Descripcion: %s.\n",local->datos.desc);
            printf("Potencia: %d.\n",local->datos.potencia);
            printf("Estado: %d.\n",local->datos.estado);
            printf("-----------------------------------------------------\n");
             local=local->anterior;
          }while(local->anterior!=NULL);
          printf("-----------------------------------------------------\n");
            printf("Descripcion: %s.\n",local->datos.desc);
            printf("Potencia: %d.\n",local->datos.potencia);
            printf("Estado: %d.\n",local->datos.estado);
            printf("-----------------------------------------------------\n");
       }
    }while(op!=3);
    fclose(p_archivo);
    printf("Fin del programa.\n");
     do{
        aux=lista;
        lista=lista->siguiente;
        free(aux);
     }while(lista->siguiente!=NULL);
    return 0;
}
