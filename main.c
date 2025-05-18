#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definiciones
#define MAX 100
#define TAMANO 10

// Estructura de Nodo para pacientes
typedef struct Nodo {
    int id;
    char nombre[50];
    int edad;
    struct Nodo *siguiente;
} Nodo;

// Estructura de Cola para citas
typedef struct Cola {
    int pacientes[MAX]; // IDs de pacientes
    int front;
    int rear;
} Cola;

typedef struct HashNode
{
    int id;
    char nombre[50];
    struct HashNode *siguiente;
} HashNode;

HashNode *tabla[TAMANO];

// Prototipos de funciones
void insertarFinal(Nodo **cabeza, int id, char *nombre, int edad);
Nodo *crearNodo(int id, char *nombre, int edad);
void mostrarPacientes(Nodo **cabeza);
void ingresarPacientes(Nodo **cabeza, int *ultimoID);
void eliminarPaciente(Nodo **cabeza, int id);
void menu(Nodo **cabeza, Cola *cola, int *ultimoID);

void inicializarCola(Cola *c);
int estaVacia(Cola *c);
void encolar(Cola *c, int id);
int desencolar(Cola *c);
Nodo* buscarPaciente(Nodo *cabeza, int id);
void atenderPaciente(Cola *cola, Nodo *cabeza);

void inicializarTablaHash();
void insertarHash(int id, char *nombre);
HashNode *buscarHash(int id);

int funcionHash(int id) {
    return id % TAMANO;
}

void inicializarTablaHash() {
    for (int i = 0; i < TAMANO; i++)
    {
        tabla[i] = NULL;
    }
}

void insertarHash(int id, char *nombre) {
    int indice = funcionHash(id);
    HashNode *nuevo = (HashNode *)malloc(sizeof(HashNode));
    nuevo->id = id;
    strcpy(nuevo->nombre, nombre);
    nuevo->siguiente = tabla[indice];
    tabla[indice] = nuevo;
}

HashNode *buscarHash(int id) {
    int indice = funcionHash(id);
    HashNode *actual = tabla[indice];
    while (actual != NULL)
    {
        if (actual->id == id)
            return actual;
        actual = actual->siguiente;
    }
    return NULL;
}

// Crear nodo
Nodo *crearNodo(int id, char *nombre, int edad) {
    Nodo *nuevo = (Nodo *)malloc(sizeof(Nodo));
    nuevo->id = id;
    strcpy(nuevo->nombre, nombre);
    nuevo->edad = edad;
    nuevo->siguiente = NULL;
    return nuevo;
}

// Insertar nodo al final de la lista
void insertarFinal(Nodo **cabeza, int id, char *nombre, int edad) {
    Nodo *nuevo = crearNodo(id, nombre, edad);
    insertarHash(id, nombre);
    if (*cabeza == NULL) {
        *cabeza = nuevo;
    } else {
        Nodo *temp = *cabeza;
        while (temp->siguiente != NULL) {
            temp = temp->siguiente;
        }
        temp->siguiente = nuevo;
    }
}

// Mostrar pacientes
void mostrarPacientes(Nodo **cabeza) {
    Nodo *temp = *cabeza;
    if (temp == NULL) {
        printf("No hay pacientes registrados.\n");
        return;
    }
    printf("ID\tNombre\tEdad\n");
    while (temp != NULL) {
        printf("%d\t%s\t%d\n", temp->id, temp->nombre, temp->edad);
        temp = temp->siguiente;
    }
}

// Ingresar pacientes
void ingresarPacientes(Nodo **cabeza, int *ultimoID) {
    int edad;
    char nombre[50];
    int users;

    printf("Ingrese la cantidad de usuarios que desea registrar: ");
    scanf("%d", &users);

    for (int i = 0; i < users; i++) {
        printf("Ingresar nombre del paciente %d: ", i + 1);
        scanf("%s", nombre);
        printf("Ingrese edad: ");
        scanf("%d", &edad);
        insertarFinal(cabeza, *ultimoID, nombre, edad);
        printf("Paciente registrado con ID: %d\n", *ultimoID);
        (*ultimoID)++;
    }
}

// Eliminar paciente
void eliminarPaciente(Nodo **cabeza, int id) {
    printf("Ingrese el ID del paciente a eliminar: ");
    scanf("%d", &id);
    if (*cabeza == NULL) {
        printf("No hay pacientes registrados.\n");
        return;
    }

    Nodo *temp = *cabeza;
    Nodo *anterior = NULL;

    if (temp != NULL && temp->id == id) {
        *cabeza = temp->siguiente;
        free(temp);
        printf("Paciente con ID %d eliminado correctamente.\n", id);
        return;
    }

    while (temp != NULL && temp->id != id) {
        anterior = temp;
        temp = temp->siguiente;
    }

    if (temp == NULL) {
        printf("Paciente con ID %d no encontrado.\n", id);
        return;
    }

    anterior->siguiente = temp->siguiente;
    free(temp);
    printf("Paciente con ID %d eliminado correctamente.\n", id);
}

// Inicializar cola
void inicializarCola(Cola *c) {
    c->front = -1;
    c->rear = -1;
}

// Verificar si cola está vacía
int estaVacia(Cola *c) {
    return (c->front == -1 || c->front > c->rear);
}

// Encolar paciente
void encolar(Cola *c, int id) {
    if (c->rear == MAX - 1) {
        printf("¡Cola llena!\n");
    } else {
        if (c->front == -1) c->front = 0;
        c->rear++;
        c->pacientes[c->rear] = id;
        printf("Paciente con ID %d agregado a la cola de citas.\n", id);
    }
}

// Desencolar paciente
int desencolar(Cola *c) {
    if (estaVacia(c)) {
        printf("No hay pacientes en espera.\n");
        return -1;
    } else {
        int id = c->pacientes[c->front];
        c->front++;
        return id;
    }
}

// Buscar paciente en lista enlazada
Nodo* buscarPaciente(Nodo *cabeza, int id) {
    Nodo *temp = cabeza;
    while (temp != NULL) {
        if (temp->id == id) {
            return temp;
        }
        temp = temp->siguiente;
    }
    return NULL;
}

// Atender paciente
void atenderPaciente(Cola *cola, Nodo *cabeza) {
    int id = desencolar(cola);
    if (id != -1) {
        Nodo *paciente = buscarPaciente(cabeza, id);
        if (paciente != NULL) {
            printf("Atendiendo al paciente: %s (ID: %d, Edad: %d)\n", paciente->nombre, paciente->id, paciente->edad);
        } else {
            printf("Paciente con ID %d no encontrado en la lista.\n", id);
        }
    }
}

// Menú de opciones
void menu(Nodo **cabeza, Cola *cola, int *ultimoID) {
    int opcion, id;
    printf("\n----- MENU -----\n");
    printf("1) AGREGAR PACIENTES\n");
    printf("2) MOSTRAR PACIENTES\n");
    printf("3) ELIMINAR PACIENTE POR ID\n");
    printf("4) AGENDAR CITA\n");
    printf("5) ATENDER PACIENTE\n");
    printf("6) BUSCAR PACIENTE RÁPIDO (HASH)\n");
    printf("Elige una opción (1-6): ");
    scanf("%d", &opcion);

    switch (opcion) {
    case 1:
        ingresarPacientes(cabeza, ultimoID);
        break;
    case 2:
        mostrarPacientes(cabeza);
        break;
    case 3:
        eliminarPaciente(cabeza, id);
        break;
    case 4:
        printf("Ingrese el ID del paciente para agendar cita: ");
        scanf("%d", &id);
        encolar(cola, id);
        break;
    case 5:
        atenderPaciente(cola, *cabeza);
        break;
    case 6:
        printf("Ingrese el ID del paciente a buscar rápidamente: ");
        scanf("%d", &id);
        HashNode *encontrado = buscarHash(id);
        if (encontrado != NULL)
        {
            printf("Paciente encontrado: %s (ID: %d)\n", encontrado->nombre, encontrado->id);
        }
        else
        {
            printf("Paciente no encontrado en la tabla hash.\n");
        }
        break;
    default:
        printf("Opción no válida.\n");
    }
}

int main()
{
    Nodo *cabeza = NULL;
    Cola cola;
    int ultimoID = 0;
    inicializarCola(&cola);
    inicializarTablaHash();

    while (1)
    {
        menu(&cabeza, &cola, &ultimoID);
    }
    return 0;
}
