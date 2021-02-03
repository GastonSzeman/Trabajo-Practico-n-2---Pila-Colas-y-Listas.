#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct{
       long partNumber;
       long serialNumber;
       char descripcion[40];
       char ubicacion[100];
    }repuestos_t;

struct lista{
    repuestos_t data;
    struct lista *siguiente,*anterior;
};

int main(){
    char opc;

    FILE *p_archivo;
    struct lista *local=NULL,*aux=NULL,*lista=NULL;
    repuestos_t repuestos;
    do{
       fflush(stdin);
       aux=(struct lista*)malloc(sizeof(struct lista));
        if(!aux){
          printf("Memoria insuficiente.\n");
            return -1;
        }
        printf("PartNumber: ");
         scanf("%ld",&aux->data.partNumber);
          fflush(stdin);
        printf("\nSerialNumber: ");
         scanf("%ld",&aux->data.serialNumber);
          fflush(stdin);
        printf("\nDescripcion: ");
         scanf("%s",&aux->data.descripcion);
          fflush(stdin);
        printf("\nUbicacion: ");
         scanf("%s",&aux->data.ubicacion);
          fflush(stdin);
        //Formo la lista.
        if(lista==NULL){
            lista=aux;
            lista->siguiente=NULL;
            lista->anterior=NULL;
          }
        else{
            local=lista;
            //Enlisto los datos ordenando por descripcion.
             while((local->data.descripcion <= aux->data.descripcion) && (local->siguiente!=NULL)){
                local = local->siguiente;
             }
             if(local->data.descripcion > aux->data.descripcion){
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
        if((p_archivo=fopen("stock.dat","ab"))==NULL){
            printf("No se ha podido cargar datos a 'stock.dat'.\n");
             return -1;
        }
        fwrite(&repuestos,sizeof(repuestos),1,p_archivo);
        printf("'S' - Cargar otro dato.\n");
         scanf("%s",&opc);
        }while(toupper(opc)=='S');

    //Imprimo la lista, libero memoria y termino el programa.
        fread(&repuestos,sizeof(repuestos),1,p_archivo);
     do{
        printf("\npartNumber: %ld.",lista->data.partNumber);
        printf("\nserialNumber: %ld.",lista->data.serialNumber);
        printf("\nDescripcion: %s.",lista->data.descripcion);
        printf("\nUbicacion: %s.",lista->data.ubicacion);

         aux=lista;
         lista=lista->siguiente;
         free(aux);
    }while(lista->siguiente!=NULL);
    fclose(p_archivo);
    free(lista);
    return 0;
}
