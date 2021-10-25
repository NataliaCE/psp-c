#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char const *argv[]) {

    int a = 3;
    pid_t pid = fork();
    if(pid == 0) { //Proceso hijo
        printf("[HIJO]: Mi PID es: %d\n\tVariable a : %d\n", getpid(), a);
        printf("[HIJO]: El PID de mi padre es %d\n", getppid());
        sleep(1);
    } else {//Proceso padre
        int estado_hijo = -4;
        printf("[PADRE]: Mi PID es: %d\n\tVariable a : %d\n", getpid(), a);
        printf("[PADRE]: El PID de mi padre es %d\n", getppid());
        printf("[PADRE]: El hijo %d ha terminado \n", wait(&estado_hijo));
        printf("[PADRE]: El estado de finalización ha sido: %d\n", estado_hijo);
    }
    //Parte común de ambos procesos
    return 7;
}