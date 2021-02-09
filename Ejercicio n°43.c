#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct{
       long numeroDeOrden;
       char cliente[40];
       char descripciondeFalla[200];
       char modelo[65];
       char fecha[10];
       char hora[10];
}repuestos_t;

struct lista{
    repuestos_t data;
    struct lista *siguiente,*anterior;
};
int main(){

    FILE *p_archivo,*p_archivoNuevo;

    char opc;
    repuestos_t datos;
    struct lista *lista=NULL,*aux=NULL,*local=NULL;


     do{
        if((p_archivo=fopen("datos.dat","ab"))==NULL){
         printf("ERROR: 'datos.dat'.\n");
          return -1;
        }
        aux=(struct lista*)malloc(sizeof(struct lista));
         if(!aux){
            printf("ERROR: memoria insuficiente.\n");
             return -2;
         }
        fflush(stdin);
        printf("\nNumero de orden: ");
         scanf("%ld",&datos.numeroDeOrden);
         fflush(stdin);
        printf("\nCliente: ");
         scanf("%s",datos.cliente);
         fflush(stdin);
        printf("\nDesc. de falla: ");
         scanf("%s",datos.descripciondeFalla);
         fflush(stdin);
        printf("\nFecha: ");
         scanf("%s",datos.fecha);
         fflush(stdin);
        printf("\nModelo: ");
         scanf("%s",datos.modelo);
         fflush(stdin);
        printf("\nHorario: ");
         scanf("%s",datos.hora);
         fflush(stdin);
         aux->data.numeroDeOrden=datos.numeroDeOrden;
         strcpy(aux->data.cliente,datos.cliente);
         strcpy(aux->data.descripciondeFalla,datos.descripciondeFalla);
         strcpy(aux->data.fecha,datos.fecha);
         strcpy(aux->data.modelo,datos.modelo);
         strcpy(aux->data.hora,datos.hora);
          if(lista==NULL){
            lista=aux;
            lista->siguiente=NULL;
            lista->anterior=NULL;
          }
          else{
            local=lista;
            while((local->data.fecha <= aux->data.fecha) && local->siguiente!=NULL){
                local=local->siguiente;
            }
            if(local->data.fecha > aux->data.fecha){
                if(aux->anterior!=NULL){
                    aux->anterior->siguiente=aux;
                }
                else{
                    lista=aux;
                }
                aux->anterior=local->anterior;
                local->anterior=aux;
                aux->siguiente=local;
            }
            else{
                local->siguiente=aux;
                aux->anterior=local;
                aux->siguiente=NULL;
            }
          }
        printf("\n\n'S' - Ingresar otro elemento.\n");
         scanf("%c",&opc);
         fwrite(&aux,sizeof(struct lista),1,p_archivo);
          fclose(p_archivo);
     }while(opc=='s');
     do{
        if((p_archivoNuevo=fopen("DatosOrdenados.dat","ab"))==NULL){
            printf("No se ha podido crear el archivo de 'DatosOrdenados.dat'.\n");
             return -3;
        }
        printf("\n----------------------------------------------------------------");
        printf("\nNumero de orden: %ld.",lista->data.numeroDeOrden);
        printf("\nCliente: %s.",lista->data.cliente);
        printf("\nDescripcion de falla: %s.",lista->data.descripciondeFalla);
        printf("\nModelo: %s.",lista->data.modelo);
        printf("\nFecha: %s",lista->data.fecha);
        printf("\nHorario: %s.",lista->data.hora);
        printf("\n\n----------------------------------------------------------------");
         aux=lista;
         lista=lista->anterior;
         free(aux);
         fwrite(&datos,sizeof(repuestos_t),1,p_archivoNuevo);
          fclose(p_archivoNuevo);
     }while(lista->anterior!=NULL);
        if((p_archivoNuevo=fopen("DatosOrdenados.dat","ab"))==NULL){
            printf("No se ha podido crear el archivo de 'DatosOrdenados.dat'.\n");
             return -3;
        }
        printf("\n----------------------------------------------------------------");
        printf("\nNumero de orden: %ld.",lista->data.numeroDeOrden);
        printf("\nCliente: %s.",lista->data.cliente);
        printf("\nDescripcion de falla: %s.",lista->data.descripciondeFalla);
        printf("\nModelo: %s.",lista->data.modelo);
        printf("\nFecha: %s",lista->data.fecha);
        printf("\nHorario: %s.",lista->data.hora);
        printf("\n\n----------------------------------------------------------------");
         fwrite(&datos,sizeof(repuestos_t),1,p_archivoNuevo);
          free(lista);
          fclose(p_archivoNuevo);
     return 0;
}
