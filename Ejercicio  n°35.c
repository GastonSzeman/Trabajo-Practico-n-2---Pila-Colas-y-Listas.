#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
    Apilar=1,
    Desapilar,
    Salir,
};

typedef struct{
	int edad;
	char nombre[25];
	char apellido[25];
	char correo[25];
	long telefono;
}persona_t;

struct pila{
	persona_t persona;
	struct pila *siguiente;
};

int menu(void);

int main(){
	struct pila *p,*aux;
	p=aux=NULL;
    FILE *p_contactos;
    int opc;
	do{
        switch(opc=menu()){
            case Apilar:
                system("cls");
                aux=(struct pila*)malloc(sizeof(struct pila));
                 if(aux){
                    fflush(stdin);
                    printf("---CARGA DE DATOS---\n");
                    printf("Nombre:\n");
                     scanf("%s",&aux->persona.nombre);
                    fflush(stdin);
                    printf("Apellido:\n");
                     scanf("%s",&aux->persona.apellido);
                    fflush(stdin);
                    printf("Edad:\n");
                     scanf("%d",&aux->persona.edad);
                    fflush(stdin);
                    printf("Telefono:\n");
                     scanf("%ld",&aux->persona.telefono);
                    fflush(stdin);
                    printf("Correo de contacto:\n");
                     scanf("%s",&aux->persona.correo);
                    printf("Datos ingresados:\n");
                    printf("----------------------------------------------------------------------------------------------\n");
                    printf("Nombre: %s %s,\nEdad: %d.\nTelefono: %ld.\nCorreo electronico: %s.\n",aux->persona.nombre,aux->persona.apellido,aux->persona.edad,aux->persona.telefono,aux->persona.correo);
                    printf("----------------------------------------------------------------------------------------------\n");
                     aux->siguiente=p;
                     p=aux;
                      if(aux->persona.edad > 21){
                        if((p_contactos=fopen("contactos.dat","ab+"))==NULL){
                        printf("No se ha podido crear el archivo 'contactos.dat'.\n");
                         return -1;
                          }
                         else{
                            printf("----------------------------------------------------------------------------------------------\n");
                            printf("\nSe han guardado los datos en el archivo 'contactos.dat'.\n");
                            printf("----------------------------------------------------------------------------------------------\n");
                             fwrite(&aux->persona,sizeof(struct pila),1,p_contactos);
                             fclose(p_contactos);
                         }
                      }
                     system("pause");
                 }
                 else{
                    printf("\nMemoria insuficiente.\n");
                    system("pause");
                     return -1;
                 }
             break;
            case Desapilar:
                if(p){
                    printf("----------------------------------------------------------------------------------------------\n\n");
                    printf("Nombre: %s %s.\nEdad: %d.\nTelefono:%ld.\nCorreo electronico:%s.\n",p->persona.nombre,p->persona.apellido,p->persona.edad,p->persona.telefono,p->persona.correo);
                    printf("----------------------------------------------------------------------------------------------\n\n");
                    aux=p;
                    p=p->siguiente;
                    free(aux);
                    system("pause");
                }
                else{
                    printf("Pila vacia.\n");
                     system("pause");
                     break;
                }
             break;
        }
	}while(opc!=Salir);
     return 0;
}

int menu(void){
    system("cls");
	int opc;
	system("cls");
	printf("1 - Apilar.\n");
	printf("2 - Desapilar.\n");
	printf("3 - Salir.\n");
	 scanf("%d",&opc);
	  return opc;
}
