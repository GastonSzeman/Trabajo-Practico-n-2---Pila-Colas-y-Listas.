#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct d{
  long clave;
  char d[30];
  unsigned char tipo;
  char b;
  int pos;//Se agrega esta variable a la estructura para luego saber su posición.
}d;

struct pila{
    struct d datos;
    struct pila *anterior;
};

struct pila *apilar(long,struct pila *);
int menu(void);

int main(void){

    struct pila *p=NULL,*aux;
    long cl;
    int opc;

    do{
        system("cls");
        printf("\nClave: ");
         scanf("%ld",&cl);
          p=apilar(cl,p);
           printf("\n0 - Dejar de buscar datos.\n");
            scanf("%d",&opc);
    }while(opc!=0);
    system("cls");
    do{
      printf("\nClave: %ld.",p->datos.clave);
      printf("\nPosicion: %d.",p->datos.pos);
       p=aux;
        aux = aux->anterior;
         free(p);
     }while(p!=NULL);
    return 0;
}

struct pila *apilar(long x,struct pila *pila){

    struct d data;
    struct pila *aux=NULL;
    int pos=0;

    FILE *p_archivo;

    if((p_archivo=fopen("datos.dat","rb"))==NULL){
        printf("No se ha podido abrir el archivo 'datos.dat'.\n");
         exit(1);
    }
    fread(&data,sizeof(data),1,p_archivo);
    while(!feof(p_archivo)){
        if((data.clave==x) && (data.tipo & (1<<4))){
            //Muestro los datos encontrados.
            printf("\nClave: %ld.",data.clave);
            printf("\nDescripcion: %s.",data.d);
            printf("\nTipo: %c.",data.tipo);
            printf("\nEstado: %c.",data.b);
                aux=(struct pila*)malloc(sizeof(struct d));
                 aux -> datos.clave = data.clave;
                  aux -> datos.pos = pos;
                   pos++;
            if(pila==NULL){
                aux ->anterior==NULL;
            }
        }
        else{
            printf("Registro no encontrado.\n");
             exit(1);
        }
    }
    fclose(p_archivo);

    return aux;
}
