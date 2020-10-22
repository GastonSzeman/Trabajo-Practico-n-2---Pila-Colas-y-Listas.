#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int edad;
	char nombre[20],apellido[20],correo[20];
	long telefono;
}contactos_t;

struct pila{
		contactos_t persona;
		struct pila *siguiente;
};

int menu(void);
int cantidad(void);

int main(){
	FILE *p_contactos;
	struct pila *p,*aux;
	int i,cant=cantidad();
	p=aux=NULL;
	do{
		switch(menu()){
			case 1://APILAR.
				for(i=0;i<cant;i++){
					aux=(struct pila *)malloc(sizeof(struct pila));
					fflush(stdin);
					printf("Nombre:\n");
					 scanf("%s",&aux->persona.nombre); 
					fflush(stdin);
					printf("Apellido:\n");
					 scanf("%s",&aux->persona.apellido);
					fflush(stdin); 
					printf("Edad:\n");
					 scanf("%d",&aux->persona.edad);
					fflush(stdin);
					printf("Correo de contacto:\n");
					 scanf("%s",&aux->persona.correo);
					fflush(stdin);
					 printf("Telefono:\n");
					  scanf("%ld",&aux->persona.telefono);  
					  aux->siguiente=p;
					  p=aux;  
					if(aux->persona.edad > 21){
						if((p_contactos=fopen("contactos.dat","wb"))==NULL){
							printf("No se ha podido crear el archivo 'contactos.dat'.\n");
							 return -1;
						}
						fwrite(&(aux->persona),sizeof((aux->persona)),1,p_contactos);
					}  
				}
				system("pause");
				fclose(p_contactos);
			 	break;
			case 2://DESAPILAR.
				 if((p_contactos=fopen("contactos.dat","rb"))==NULL){
				 	printf("No se ha podido encontrar el archivo 'contactos.dat'.\n");
				 	 return -1;
				 }
				 fread(&(p->persona),sizeof((p->persona)),1,p_contactos);
				  while(!feof(p_contactos)){
				  	printf("Dato desapilado:\n Nombre completo: %s %s.\n",p->persona.nombre,p->persona.apellido);
					printf("Edad: %d.\n",p->persona.edad);
					printf("Telefono: %ld.\n",p->persona.telefono);
				  	 aux=p;
					 p=p->siguiente;
				 	 free(aux);
				 	fread(&(p->persona),sizeof((p->persona)),1,p_contactos);
				 	 system("pause");
				 		break;
				  }
				  if((p->siguiente)==NULL){
				  	printf("Pila vacia.\n");
				  	  break;
				  }
				 fclose(p_contactos); 
				system("pause");
				break; 	
		}	
	}while(menu()!=3);
	
	return 0;
}

int cantidad(void){
	int cant;
	printf("***BIENVENIDO.***\n");
	printf("Ingrese la cantidad de contactos que desea cargar:\n");
	printf("----->> ");
	 scanf("%d",&cant);
	  return cant;
}
int menu(void){
	 system("cls");
	 int opc;
	printf("1 - Apilar.\n");
	printf("2 - Desapilar.\n");
	printf("3 - Salir.\n");
	printf("--->> ");
	 scanf("%d",&opc);
	  return opc;
}
