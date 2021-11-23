//importar los módulos .h que necesitemos.
//si necesitamos funciones.h también, y entre comillas.
#include <stdio.h>
#include <signal.h>

#include <funciones.h>


//declarar la función que gestione las señales, 
//pude ser 1 para las dos señales SIGUSR1 y SIGUSR2
// o una común que discrimine por el código de señal
// que viene en el parámetro.

void gestor_senyal(int senyal);

//implementar el main.
//en este caso, el main recibirá como parámetro
//el pid del consumidor 
//el parámetro estará en argv[1]
int main(int argc, char const *argv[])
{
    printf("El parámetro es %s, pero no es de tipo pid_t, así que lo tengo que convertir. atoi (o mejor atol) puede ser una buena opción.",argv[1]);
    return 0;
}

void gestor_senyal(int senyal){
    if(senyal == SIGUSR2){ //La señal 2 la usaremos para finalizar.
        //final = true;
    }
    //cualquier otra señal que hayamos asociado a la función, no hará nada.
}