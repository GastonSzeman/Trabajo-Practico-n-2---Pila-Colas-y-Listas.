#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct{
	int edad;
	char nombre[25];
	char apellido[25];
	char correo[25];
	long telefono;
}persona_t;

struct lista_t{
    persona_t datos;
    struct lista_t *siguiente,*anterior;
};

int menu(void);

int main(){

    persona_t personas;
    FILE *p_archivo,*p_ordenado;
    struct lista_t *lista=NULL,*aux=NULL,*local=NULL;

    if((p_archivo=fopen("contactos.dat","rb"))==NULL){
        printf("No se ha podido encotrar el archivo de 'contactos.dat'.\n");
         return -1;
    }
    aux=(struct lista_t*)malloc(sizeof(struct lista_t));
    if(!aux){
        printf("No hay memoria suficiente.\n");
         return -2;
    }
    //Ordenando lista.
    if(lista == NULL){
        lista=aux;
        lista->siguiente=NULL;
    }
    else{
        local=lista;
        while((strcmp(local->datos.nombre,aux->datos.nombre) < 0) && (local->siguiente!=NULL)){
            local=local->siguiente;
            }
        if(strcmp(local->datos.nombre,aux->datos.nombre) > 0){
           if(aux->anterior!=NULL)
            {
            aux->anterior->siguiente=NULL;
            }
           else{
            lista=aux;
            aux->anterior=local->anterior;
            local->anterior=aux;
            aux->siguiente=local;
           }
        }
        else{
            local->siguiente=aux;
            aux->anterior=local;
            aux->siguiente=NULL;
        }
    }
    printf("\n***MOSTRANDO DATOS.***\n");
    while(!feof(p_archivo)){
        local=lista;
        printf("\n----------------------------------------------------------------------------------------------\n");
        printf("\nNombre: %s.",local->datos.nombre);
        printf("\nApellido: %s.",local->datos.apellido);
        printf("\nEdad: %d.",local->datos.edad);
        printf("\nNumero de telefono: %ld.",local->datos.telefono);
        printf("\nCorreo de contacto: %s.",local->datos.correo);
        printf("\n----------------------------------------------------------------------------------------------\n");
        fread(&personas,sizeof(personas),1,p_archivo);
        }
        if((p_ordenado=fopen("contactos_ordenados.dat","ab"))==NULL){
            printf("No se ha podido crear o agregar datos en el archivo 'contactos_ordenados.dat'.\n");
             return -1;
        }
        fwrite(&personas,sizeof(personas),1,p_ordenado);
      fclose(p_archivo);
      fclose(p_ordenado);
     return 0;
}
