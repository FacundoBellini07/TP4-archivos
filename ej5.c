#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int i;

struct Persona {
    char nombre[50];
    char apellido[50];
    char dni[20];
};

int compararPorNombre(const void *a, const void *b);
int compararPorDNI(const void *a, const void *b);
void mostrarDatosOrdenados(struct Persona personas[], int numPersonas);
void guardarCambios(struct Persona personas[], int numPersonas, const char *nombreArchivo);

int main() {
    FILE *archivoOriginal;
    int opcion;
    struct Persona *personas = NULL;
    int numPersonas = 0;
    int capacidad = 0;

    archivoOriginal = fopen("datos.txt", "r");
    if (archivoOriginal == NULL) {
        printf("\nError al abrir el archivo original.\n");
        return 1;
    }


    while (fscanf(archivoOriginal, "%s %s %s", personas[numPersonas].nombre, personas[numPersonas].apellido, personas[numPersonas].dni) != EOF) {

        if (numPersonas >= capacidad) {
            capacidad += 10;
            personas = realloc(personas, capacidad * sizeof(struct Persona));
            if (personas == NULL) {
                printf("\nError al asignar memoria.\n");
                return 1;
            }
        }
        numPersonas++;
    }
    fclose(archivoOriginal);

    do {
        printf("\nMenu:\n");
        printf("1. Mostrar datos ordenados por nombre y apellido\n");
        printf("2. Mostrar datos ordenados por DNI\n");
        printf("3. Guardar cambios en un nuevo archivo\n");
        printf("4. Salir\n");
        printf("\nIngrese su opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                qsort(personas, numPersonas, sizeof(struct Persona), compararPorNombre);
                mostrarDatosOrdenados(personas, numPersonas);
                break;
            case 2:
                qsort(personas, numPersonas, sizeof(struct Persona), compararPorDNI);
                mostrarDatosOrdenados(personas, numPersonas);
                break;
            case 3:
                guardarCambios(personas, numPersonas, "datos_nuevos.txt");
                printf("\nCambios guardados en un nuevo archivo 'datos_nuevos.txt'.\n");
                break;
            case 4:
                printf("\nSaliendo del programa...\n");
                break;
            default:
                printf("\nOpción no válida. Intente de nuevo.\n");
        }
    } while (opcion != 4);

    free(personas);

    return 0;
}

int compararPorNombre(const void *a, const void *b) {
    const struct Persona *personaA = (const struct Persona *)a;
    const struct Persona *personaB = (const struct Persona *)b;
    int cmp = strcmp(personaA->nombre, personaB->nombre);
    if (cmp == 0) {
        return strcmp(personaA->apellido, personaB->apellido);
    }
    return cmp;
}

int compararPorDNI(const void *a, const void *b) {
    const struct Persona *personaA = (const struct Persona *)a;
    const struct Persona *personaB = (const struct Persona *)b;
    return strcmp(personaA->dni, personaB->dni);
}

void mostrarDatosOrdenados(struct Persona personas[], int numPersonas) {
    printf("Nombre\tApellido\tDNI\n");
    for (i = 0; i < numPersonas; i++) {
        printf("%s\t%s\t%s\n", personas[i].nombre, personas[i].apellido, personas[i].dni);
    }
}

void guardarCambios(struct Persona personas[], int numPersonas, const char *nombreArchivo) {
    FILE *archivoNuevo = fopen(nombreArchivo, "w");
    if (archivoNuevo == NULL) {
        printf("\nError al crear el archivo nuevo.\n");
        return;
    }

    for (i = 0; i < numPersonas; i++) {
        fprintf(archivoNuevo, "%s %s %s\n", personas[i].nombre, personas[i].apellido, personas[i].dni);
    }

    fclose(archivoNuevo);
}

