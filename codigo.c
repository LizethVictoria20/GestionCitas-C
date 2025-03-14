#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ESTRUCTURA
typedef struct Nodo
{
  int id;
  char nombre[50];
  int edad;
  struct Nodo *siguiente;
} Nodo;

// PROTOTIPOS DE FUNCIONES
int insertarFinal(Nodo **cabeza, int id, char *nombre, int edad);
Nodo *crearNodo(int id, char *nombre, int edad);
int mostrarPacientes(Nodo **cabeza);
int ingresarPacientes(Nodo **cabeza);
int menu();

// CREAR NODO
Nodo *crearNodo(int id, char *nombre, int edad)
{
  Nodo *nuevo = (Nodo *)malloc(sizeof(Nodo));
  if (nuevo == NULL)
  {
    printf("Error al asignar memoria\n");
    exit(1);
  }
  nuevo->id = id;
  strcpy(nuevo->nombre, nombre);
  nuevo->edad = edad;
  nuevo->siguiente = NULL;
  return nuevo;
}

// INSERTA NODO AL FINAL
int insertarFinal(Nodo **cabeza, int id, char *nombre, int edad)
{
  Nodo *nuevo = crearNodo(id, nombre, edad);
  if (*cabeza == NULL)
  {
    *cabeza = nuevo;
  }
  else
  {
    Nodo *temp = *cabeza;
    while (temp->siguiente != NULL)
    {
      temp = temp->siguiente;
    }
    temp->siguiente = nuevo;
  }
  return 0; // Retornamos 0 para indicar que se insertó correctamente
}

// IMPRIME TODA LA LISTA EN ORDEN DE INGRESO
int mostrarPacientes(Nodo **cabeza)
{
  Nodo *temp = *cabeza;
  if (temp != NULL)
  {
    printf("----- id  nombre  edad -----\n");
  }
  else
  {
    printf("No hay pacientes registrados.\n");
    return 0;
  }
  while (temp != NULL)
  {
    printf("      %d   %s   %d\n", temp->id, temp->nombre, temp->edad);
    temp = temp->siguiente;
  }
  return 0;
}

// INGRESA LOS DATOS DIGITADOS POR EL USUARIO
int ingresarPacientes(Nodo **cabeza)
{
  int id = 0;
  int edad;
  char si = 's';
  char nombre[50];

  while (si == 's' || si == 'S')
  {
    printf("Ingrese nombre: ");
    scanf("%s", nombre);
    printf("Ingrese edad: ");
    scanf("%d", &edad);
    insertarFinal(cabeza, id, nombre, edad);
    printf("Desea ingresar otro paciente (S/N): ");
    scanf(" %c", &si); // Espacio antes de %c para consumir cualquier salto de línea pendiente
    if (si == 'n' || si == 'N')
    {
      menu();
    }
    id++;
  }
  return 0;
}

// MENÚ DE FUNCIONES
int menu()
{
  int opcion;
  // Se declara la cabeza de la lista fuera de las opciones para que sea accesible a ambas funciones
  Nodo *cabeza = NULL;
  printf("----- MENÚ -----\n");
  printf("1) AGREGAR PACIENTE\n2) MOSTRAR PACIENTES\n");
  printf("Elige una opción (1-2): ");
  scanf("%d", &opcion);
  switch (opcion)
  {
  case 1:
    ingresarPacientes(&cabeza);
    break;
  case 2:
    mostrarPacientes(&cabeza);
    break;
  default:
    printf("Opción no válida.\n");
  }
  return 0;
}

int main()
{
  menu();
  return 0;
}
