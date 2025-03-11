#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//ESTRUCTURA
typedef struct Nodo {
 int id;
 char nombre[50];
 int edad;
 struct Nodo* siguiente;
} Nodo;
//PROTORIPOS DE FUNCIONES 
void insertarFinal(Nodo** cabeza, int id, char* nombre, int edad);
Nodo* crearNodo(int id, char* nombre, int edad);
void mostrarPacientes();
void ingresarPacientes();
void menu();
//FUNCION PRINCIPAL
void main(){

menu();

}


//CREAR NODO
Nodo* crearNodo(int id, char* nombre, int edad) {
 Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
 nuevo->id = id;
 strcpy(nuevo->nombre, nombre);
 nuevo->edad = edad;
 nuevo->siguiente = NULL;
 return nuevo;
}
//INCERTA NODO
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
       if(temp!=NULL){
       printf("----- id  nombre  edad -----\n");
       }
    while(temp!=NULL){
        
    printf("      %d   %s   %i      \n",temp->id,temp->nombre,temp->edad);
    temp = temp->siguiente;
    }

}
//ingresa los datos digitados por el usuario
void ingresarPacientes(Nodo** cabeza){
    int id=0;
    int edad;
    char si='s';
    char nombre[50];
     
    while(si =='s' || si =='S'){
        printf("ingreda nombre y edad ");
        scanf("%s %i",nombre,&edad);
        insertarFinal(cabeza,id,nombre,edad);
         printf("desea ingresar otro paciente S/N  ");
         scanf("%s",&si);
        id++;
    }
    menu();
}
//MENU DE FUNCIONES 
void menu(){
    int opcion;
    Nodo* cabeza = NULL;
    printf("----- MENU -----\n");
    printf("1) AGREGAR PACIENTE\n2) MOSTRAR PACIENTES\n");
    printf("Elige una opción (1-2): ");
    scanf("%d", &opcion);
    switch(opcion){
    case 1:
        ingresarPacientes(&cabeza);
    
    case 2:
        mostrarPacientes(&cabeza);
    
    }
    
}