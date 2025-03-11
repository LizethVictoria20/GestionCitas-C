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
void mostrarPacientes();
void ingresarPacientes();

void main(){

Nodo* cabeza = NULL;
    ingresarPacientes(&cabeza);
    mostrarPacientes(&cabeza);

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
//imprime toda la lista en el orden de ingreso
void mostrarPacientes(Nodo** cabeza){
       Nodo* temp = *cabeza;
    while(temp!=NULL){
    printf("id %d nombre %s edad %i \n",temp->id,temp->nombre,temp->edad);
    temp = temp->siguiente;
    }

}

//ingresa los datos ingresados por el usuario 
void ingresarPacientes(Nodo** cabeza){
    int id=0;
    int edad;
    char si='s';
    char nombre[50]; 
    while(si =='s'){
        printf("ingreda nombre y edad ");
        scanf("%s %i",nombre,&edad);
        insertarFinal(cabeza,id,nombre,edad);
         printf("desea ingresar otro paciente S/N  ");
         scanf("%s",&si);
        id++;
    }
}
//prueba de commits






