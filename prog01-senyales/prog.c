#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void gestionar_interrupcion(int senyal){
    printf("Recibida la señal número %d\n", senyal);
    exit(0);
}

int main(int argc, char const *argv[])
{
    //signal vincula una función a una señal
    signal(SIGINT, gestionar_interrupcion);
    printf("hola mundo\n");

    //sleep(30);
    //pause para la ejecución hasta que le llegue al proceso una señal (normalmente medianae kill)
    //pause();
    printf("hola mundo 2\n");
    return 0;
}

//gcc prog.c -o prog.exe