#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct{
       long partNumber;
       long serialNumber;
       char descripcion[40];
       char ubicacion[100];
}repuestos_t;

struct cola{
    repuestos_t data;
    struct cola *siguiente;
};

int main(){

    FILE *p_archivo,*p_archivoNuevo,*p_archivoSinFalla;
    repuestos_t datos;
    struct cola *cola=NULL,*aux=NULL,*local=NULL;

    if((p_archivo=fopen("stock.dat","rb"))==NULL){
        printf("No se ha podido abrir el archivo con 'stock.dat'.\n");
         return -1;
    }
    fread(&datos,sizeof(repuestos_t),1,p_archivo);
     while(!feof(p_archivo)){
      if(datos.partNumber==1234 && datos.serialNumber&(1<<3) && datos.serialNumber&(1<<5)){
        aux=(struct cola*)malloc(sizeof(struct cola));
         if(!aux){
            printf("Memoria insuficiente.\n");
             return -2;
         }

         aux->data.partNumber=datos.partNumber;
         aux->data.serialNumber=datos.serialNumber;
         strcpy(aux->data.descripcion,datos.descripcion);
         strcpy(aux->data.ubicacion,datos.ubicacion);

         aux->siguiente=NULL;
          if(cola==NULL){
            cola=aux;
            local=aux;
          }
          else{
            local->siguiente=aux;
            local=aux;
          }
         if((p_archivoNuevo=fopen("fallados.dat","ab"))==NULL){
            printf("No se ha podido generar el archivo con los datos fallados('fallados.dat').\n");
             return -3;
            }
             fwrite(&datos,sizeof(repuestos_t),1,p_archivoNuevo);
             fread(&datos,sizeof(repuestos_t),1,p_archivo);
        }
      else{
        //Hago la baja fisica.
        if((p_archivoSinFalla=fopen("stockActual.dat","ab"))==NULL){
            printf("No se ha podido actualizar el archivo con los datos.\n");
             return -4;
        }
        fwrite(&datos,sizeof(repuestos_t),1,p_archivoSinFalla);
      }
     }

    while(aux->siguiente!=NULL){
        printf("\n-------------------------------------------\n");
        printf("PartNumber: %ld.\n",aux->data.partNumber);
        printf("SerialNumber: %ld.\n",aux->data.serialNumber);
        printf("Descripcion: %s.\n",aux->data.descripcion);
        printf("Ubicacion. %s.",aux->data.ubicacion);
        printf("\n-------------------------------------------\n");
        aux=cola;
        cola=cola->siguiente;
        free(aux);
    }

    free(cola);
    fclose(p_archivo);
    fclose(p_archivoNuevo);
    fclose(p_archivoSinFalla);

    return 0;
}
