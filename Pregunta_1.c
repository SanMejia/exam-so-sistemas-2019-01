#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "mycommon.h"
#include "common_threads.h"

volatile int counter = 0; 
int loops;

puerta mi_puerta;



void *worker(void *arg) {
    int i;
    cerrar_puerta(mi_puerta);
    for (i = 0; i < loops; i++) {
	counter++;
    }
    abrir_puerta(mi_puerta);
    return NULL;
}


int main(int argc, char *argv[]) {
    if (argc != 2) { 
	fprintf(stderr, "usage: threads <loops>\n"); 
	exit(1); 
    }
    loops = atoi(argv[1]);
    pthread_t p1, p2;
    crear_puerta(mi_puerta); 
    printf("Initial value : %d\n", counter);
    pthread_create(&p1, NULL, worker, NULL); 
    pthread_create(&p2, NULL, worker, NULL);
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    printf("Final value   : %d\n", counter);
    destruir_puerta(mi_puerta);
    return 0;
}
