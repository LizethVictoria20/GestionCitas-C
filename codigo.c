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
// PROTORIPOS DE FUNCIONES
void insertarFinal(Nodo **cabeza, int id, char *nombre, int edad);
Nodo *crearNodo(int id, char *nombre, int edad);
void mostrarPacientes();
void ingresarPacientes();
void menu();
// FUNCION PRINCIPAL
int main()
{
  //Se declara cabeza para que los datos puedan persistir en la memoria
  Nodo *cabeza = NULL; 
  while (1)
  {
    menu(&cabeza);
  }
  return 0;
}

// CREAR NODO
Nodo *crearNodo(int id, char *nombre, int edad)
{
  Nodo *nuevo = (Nodo *)malloc(sizeof(Nodo));
  nuevo->id = id;
  strcpy(nuevo->nombre, nombre);
  nuevo->edad = edad;
  nuevo->siguiente = NULL;
  return nuevo;
}
// Ingresa nodo
void insertarFinal(Nodo **cabeza, int id, char *nombre, int edad)
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
}
// Imprime toda la lista en el orden de ingreso
void mostrarPacientes(Nodo **cabeza)
{
  Nodo *temp = *cabeza;
  if (temp == NULL)
  {
    printf("No hay pacientes registrados.\n");
    return;
  }
  if (temp != NULL)
  {
    printf("ID\tNombre\tEdad\n");
  }
  while (temp != NULL)
  {

    printf("%d\t %s\t %i\n", temp->id, temp->nombre, temp->edad);
    temp = temp->siguiente;
  }
}
// Ingresa los datos digitados por el usuario
void ingresarPacientes(Nodo **cabeza)
{
  int id = 0;
  int edad;
  char nombre[50];
  int users;
 
  printf("Ingrese la cantidad de usuarios que desea registrar: ");
  scanf("%i", &users);

  for (int i = 1; i <= users; i++)
  {
    printf("Ingresar nombre del paciente %i: ", i);
    scanf("%s", nombre);
    printf("Ingrese edad: ");
    scanf("%i", &edad);
    insertarFinal(cabeza, id, nombre, edad);
    id++;
  }
}

void eliminarPaciente(Nodo **cabeza, int id)
{
  printf("Ingrese el ID del paciente a eliminar: ");
  scanf("%d", &id);
  if (*cabeza == NULL)
  {
    printf("No hay pacientes registrados.\n");
    return;
  }

  Nodo *temp = *cabeza;
  Nodo *anterior = NULL;

  if (temp != NULL && temp->id == id)
  {
    *cabeza = temp->siguiente;
    free(temp);
    printf("Paciente con ID %d eliminado correctamente.\n", id);
    return;
  }

  while (temp != NULL && temp->id != id)
  {
    anterior = temp;
    temp = temp->siguiente;
  }

  if (temp == NULL)
  {
    printf("Paciente con ID %d no encontrado.\n", id);
    return;
  }

  anterior->siguiente = temp->siguiente;
  free(temp);
  printf("Paciente con ID %d eliminado correctamente.\n", id);
}

// MENU DE FUNCIONES
void menu(Nodo **cabeza)
{
  int opcion, id;
  printf("----- MENU -----\n");
  printf("1) AGREGAR PACIENTES\n2) MOSTRAR PACIENTES\n3) ELIMINAR PACIENTE POR ID\n");
  printf("Elige una opción (1-3): ");
  scanf("%d", &opcion);
  switch (opcion)
  {
  case 1:
    ingresarPacientes(cabeza);
    break;
  case 2:
    mostrarPacientes(cabeza);
    break;
  case 3:
    eliminarPaciente(cabeza, id);
    break;
  default:
    printf("Opción no válida.\n");
  }
}
