#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Nodo {
 int id;
 char nombre[50];
 int edad;
 struct Nodo* siguiente;
} Nodo;

void insertarFinal(Nodo** cabeza, int id, char* nombre, int edad);
Nodo* crearNodo(int id, char* nombre, int edad);

int main(){
   
    Nodo* cabeza = NULL;
  
    insertarFinal(&cabeza,1,"prueba",21);
     insertarFinal(&cabeza,3,"prueba",21);
       Nodo* temp = cabeza;
    while(temp!=NULL){
    printf("%d",temp->id);
    temp = temp->siguiente;
    }
    return 0;
}



Nodo* crearNodo(int id, char* nombre, int edad) {
 Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
 nuevo->id = id;
 strcpy(nuevo->nombre, nombre);
 nuevo->edad = edad;
 nuevo->siguiente = NULL;
 return nuevo;
}
void insertarFinal(Nodo** cabeza, int id, char* nombre, int edad) {
 Nodo* nuevo = crearNodo(id, nombre, edad);
 if (*cabeza == NULL) {
 *cabeza = nuevo;
 } else {
 Nodo* temp = *cabeza;
 while (temp->siguiente != NULL) {
 temp = temp->siguiente;
 }
 temp->siguiente = nuevo;
 }
}
