#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Persona{
	
	int dni[20];
	char nombre[50];
	char apellido[50];
	
};

void ingresarDatos(FILE *archivo);

void buscarPorDni(FILE *archivo);

void buscarPorNombreApellido(FILE *archivo);



int main() {
    FILE *archivo;
    int opcion;


    archivo = fopen("EJ 2.txt", "w+");
    if(archivo == NULL){
        printf("Error al abrir el archivo.\n");
        return 1;
    }

    do{
        printf("\nMenu:\n");
        printf("1. Ingresar datos\n");
        printf("2. Buscar por DNI\n");
        printf("3. Busqueda por Nombre y Apellido\n");
        printf("4. Salir\n");
        printf("\nIngrese su opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                ingresarDatos(archivo);
                break;
            case 2:
                buscarPorDNI(archivo);
                break;
            case 3:
                buscarPorNombreApellido(archivo);
                break;
            case 4:
                printf("\nSaliendo del programa...\n");
                break;
            default:
                printf("\nOpcion no valida. Intente de nuevo.\n");
        }
    }while(opcion != 4);


    fclose(archivo);

    return 0;
}




void ingresarDatos(FILE *archivo) {
    struct Persona persona;
    char dniBuscar[20];

    printf("\nIngrese el DNI: ");
    scanf("%s", dniBuscar);

    rewind(archivo);

  
    while(fscanf(archivo, "%s %s %s", persona.nombre, persona.apellido, persona.dni) != EOF){
        if(strcmp(persona.dni, dniBuscar) == 0){
            printf("\nEl DNI ingresado ya existe en el archivo. No se pueden ingresar datos duplicados.\n");
            return;
        }
    }

    strcpy(persona.dni, dniBuscar);

    printf("\nIngrese el nombre: ");
    scanf("%s", persona.nombre);
    printf("\nIngrese el apellido: ");
    scanf("%s", persona.apellido);

    fprintf(archivo, "%s %s %s\n", persona.nombre, persona.apellido, persona.dni);
    printf("\nDatos guardados correctamente.\n");
}



void buscarPorDNI(FILE *archivo){
    char dniBuscar[20];
    char nombre[50], apellido[50], dni[20];
    int encontrado = 0;

    printf("\nIngrese el DNI a buscar: ");
    scanf("%s", dniBuscar);

    rewind(archivo);

   
    while(fscanf(archivo, "%s %s %s", nombre, apellido, dni) != EOF){
        if(strcmp(dni, dniBuscar) == 0){
            printf("\nNombre: %s\t", nombre);
            printf("Apellido: %s\n", apellido);
            encontrado = 1;
            break;
        }
    }

    if(!encontrado){
        printf("No se encontraron datos para el DNI ingresado.\n");
    }
}


void buscarPorNombreApellido(FILE *archivo){
    char nombreBuscar[50];
    char apellidoBuscar[50];
    char nombre[50], apellido[50], dni[20];
    int encontrado = 0;

    printf("\nIngrese el nombre a buscar: ");
    scanf("%s", nombreBuscar);
    printf("\nIngrese el apellido a buscar: ");
    scanf("%s", apellidoBuscar);


    rewind(archivo);

   
    while(fscanf(archivo, "%s %s %s", nombre, apellido, dni) != EOF){
        if(strcmp(nombre, nombreBuscar) == 0 && strcmp(apellido, apellidoBuscar) == 0){
            printf("\nDNI: %s\n", dni);
            encontrado = 1;
            break;
        }
    }

    if(!encontrado){
        printf("\nNo se encontraron datos para el nombre y apellido ingresados.\n");
    }
}
	
