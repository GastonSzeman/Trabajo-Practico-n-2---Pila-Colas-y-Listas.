#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct {
    char desc[60];
    unsigned char potencia;
    unsigned int estado;
    int id;//Se agregó este nuevo campo.
}datos_t;

struct lista{
    datos_t datos;
    struct lista *siguiente,*anterior;
};

void buscar(int x);

int main(){
    datos_t data;
    FILE *p_archivo,*p_archivo1;
    int op;
    struct lista *aux=NULL,*lista=NULL,*local=NULL,*cola=NULL;
    char opc;

    do{
         if((p_archivo=fopen("potencia.dat","ab"))==NULL){
            printf("ERROR: 'potencia.dat'.\n");
             return -1;
        }
        aux=(struct lista*)malloc(sizeof(struct lista));
         if(!aux){
            printf("Memoria insuficiente.\n");
             return -2;
         }
        fflush(stdin);
        printf("\nDescripcion: ");
         scanf("%s",&aux->datos.desc);
        fflush(stdin);
        printf("\nPotencia: ");
         scanf("%d",&aux->datos.potencia);
        printf("\nClave(id):");
         scanf("%d",&aux->datos.id);
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
       printf("1 - Mayor a menor.\n2 - Menor a mayor.\n3 - Liberar memoria y salir.\n4 - Buscar por id.\n\n");
        scanf("%d",&op);
         if(op==2){
            local=lista;
            do{
            printf("-----------------------------------------------------\n");
            printf("Descripcion: %s.\n",local->datos.desc);
            printf("Potencia: %d.\n",local->datos.potencia);
            printf("Estado: %d.\n",local->datos.estado);
            printf("Clave (id):\n",local->datos.id);
            printf("-----------------------------------------------------\n");
             local= local->siguiente;
         }while(local->siguiente!=NULL);
            printf("-----------------------------------------------------\n");
            printf("Descripcion: %s.\n",local->datos.desc);
            printf("Potencia: %d.\n",local->datos.potencia);
            printf("Estado: %d.\n",local->datos.estado);
            printf("Clave (id):\n",local->datos.id);
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
            printf("Clave (id):\n",local->datos.id);
            printf("-----------------------------------------------------\n");
             local=local->anterior;
          }while(local->anterior!=NULL);
          printf("-----------------------------------------------------\n");
            printf("Descripcion: %s.\n",local->datos.desc);
            printf("Potencia: %d.\n",local->datos.potencia);
            printf("Estado: %d.\n",local->datos.estado);
            printf("Clave (id):\n",local->datos.id);
            printf("-----------------------------------------------------\n");
       }
       if(op==4){
        int clave;
        printf("***BUSQUEDA.***\n");
        printf("Ingrese la clave de identificacion(id):\n");
         scanf("%d",&clave);
          buscar(clave);
          system("cls");
       }
    }while(op!=3);
    fclose(p_archivo);

    rewind(p_archivo);
    if((p_archivo=fopen("potencia.dat","rb"))==NULL){
        printf("No se ha podido abrir el archivo 'potencias.dat'.\n");
         exit(-1);
    }
    fread(&data,sizeof(struct lista),1,p_archivo);
    while(feof(p_archivo)){
      fread(&data,sizeof(struct lista),1,p_archivo);
      if(data.estado&(1<<0) && data.estado&(1<<2)){
        aux=(struct lista*)malloc(sizeof(struct lista));
         if(!aux){
            printf("No hay suficiente memoria disponible.\n");
             exit(0);
         }
            aux->siguiente=NULL;
            if(cola==NULL){
                cola=aux;
                local=aux;
              }
              else{
                local->siguiente=aux;
                local=aux;
              }
        if((p_archivo1=fopen("salida.dat","ab"))==NULL){
            printf("Error: Archivo 'salida.dat'.\n");
        }
        fwrite(&data,sizeof(struct lista),1,p_archivo);
      }
    }
    fclose(p_archivo1);
    fclose(p_archivo);

    printf("Fin del programa.\n");
     do{
        aux=lista;
        lista=lista->siguiente;
        free(aux);
     }while(lista->siguiente!=NULL);
     free(lista);
    return 0;
}

void buscar(int x){
    datos_t data;
    FILE *p_archivo;
    char *s,*i,aux[20];

    if((p_archivo=fopen("potencia.dat","rb"))==NULL){
      printf("No se ha podido abrir el archivo 'potencia.dat'\n");
       return -1;
    }
    fread(&data,sizeof(struct lista),1,p_archivo);

      while(!feof(p_archivo)){
     fread(&data,sizeof(struct lista),1,p_archivo);
     if(data.id==x){
      printf("Archivo encontrado.\n");
      printf("----------------------------------\n");
      printf("Descripcion: %s.",data.desc);
      printf("Potencia: %d.\n",data.potencia);
      printf("Estado: %d.",data.estado);
      printf("Clave(id): %d.",data.id);
      printf("----------------------------------\n");

      s=&data.desc[0];
      i=aux;
      while(*s){
        s++;
      }
      s--;
      while(s!=data.desc[0]){
         *i=*s;
         s--;
         i++;
      }
      *i=*s;
      i++;
      i=0;

      printf("Se ha invertido la primer palabra de la descripcion del registro.\n");
      data.estado=data.estado^(1<<3);
      printf("Se ha cambiado el estado del bit n°3 del campo 'estado'.\n");

      fwrite(&data,sizeof(struct lista),1,p_archivo);
      }
      else{
        printf("\nArchivo no encontrado.\n");
         fclose(p_archivo);
          exit(0);
      }
      if(feof(p_archivo)){
        printf("Registro no encontrado.\n");
         return;
      }
    }
    fclose(p_archivo);
}
