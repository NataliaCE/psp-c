#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdbool.h>

void tratarSenyal(int cod_senyal);
void ignorarSenyal(int cod_senyal);

//Variables globales
pid_t pidHijo; 
bool final = false;

int main(int argc, char const *argv[])
{
    pidHijo = fork();
    switch (pidHijo)
    {
    case -1: //error
        exit(-1);
        break;
    
    case 0: //hijo
        signal(SIGUSR2, tratarSenyal);
        signal(SIGINT, SIG_IGN); //Ignora la señal CTRL-C
        printf("[HIJO %d]: Esperado señal\n", getpid());
        while (!final) {
            printf("[HIJO]: Esperando 5 segundos...\n");
            sleep(5);
        }
        
        break;

    default: //padre
        signal(SIGINT, tratarSenyal);
        printf("[PADRE %d]: Esperando señal\n", getpid());
        pause();
        wait(NULL);
        break;
    }

    return 0;
}

void tratarSenyal(int cod_senyal) {
    if(cod_senyal == SIGINT) {
        printf("[PROCESO %d]: Recibida señal %d\n", getpid(), cod_senyal);
        printf("Enviando señal al hijo con pid %d en 3 segundos\n", pidHijo);
        sleep(3);
        kill(pidHijo, SIGUSR2);

    } else if(cod_senyal == SIGUSR2) {
        printf("[PROCESO %d]: Recibida señal %d\n", getpid(), cod_senyal);
        final = true;
    }
}

void ignorarSenyal(int cod_senyal) {
    //Lo dejo vacío
    //Con esto el hijo tambien sale del sleep con control c
}

//Para cerrar padre y que envie la señal, se hace en la consola de linux
// kill -s SIGINT 20159