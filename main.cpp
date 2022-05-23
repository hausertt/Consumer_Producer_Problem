//
// Created by hato0 on 23.05.2022.
//

#include <pthread.h>
#include <cstdio>

/* Programm that shows the consumer producer problem with
 * 2 Consumers
 * 3 Producers
 * and with notify all
 * --------------------
 * To only use notify change 'pthread_cond_broadcast(&dieCondition);' to
 * pthread_cond_signal(&dieCondition);
 * --------------------
 * !!!Main program runs infinite!!!
 * !!!Stop it manually!!!*/


/* A mutex protecting put. */
pthread_mutex_t putMutex;

/* A mutex protecting get. */
pthread_mutex_t getMutex;

/* Main condition */
pthread_cond_t dieCondition;

/* Consumer Threads */
pthread_t consumer1;
pthread_t consumer2;

/* Producer Threads */
pthread_t producer1;
pthread_t producer2;
pthread_t producer3;

/* Variable if data can be consumed */
bool available = false;

/* Data and Zahl || Zahl put in Data */
int data;
int zahl;

void *produce(void *);

void *consume(void *);


/* Put. Puts Zahl into data */
void* put(int zahl) {
    int id = pthread_self();
    while(available) {
        printf("[put]:: Thread %d geraet in WAITING \n",id);
        pthread_cond_wait(&dieCondition,&putMutex);
        printf("[put]:: Thread %d macht weiter \n", id);
    }
    data = zahl;
    available = true;
    pthread_cond_broadcast(&dieCondition);
    //pthread_cond_signal(&dieCondition);
    return nullptr;
}

/* Get. Returns data */
int get() {
    int id = pthread_self();
    while(!available) {
        printf("[get]:: Thread %d geraet in WAITING \n",id);
        pthread_cond_wait(&dieCondition,&getMutex);
        printf("[get]:: Thread %d macht weiter \n", id);
    }
    available = false;
    pthread_cond_broadcast(&dieCondition);
    //pthread_cond_signal(&dieCondition);
    return data;
}


/* The main program. */
int main() {
    pthread_mutex_init(&putMutex, nullptr);
    pthread_mutex_init(&getMutex, nullptr);


    pthread_cond_init(&dieCondition, nullptr);

    /* Creates new threads. The new threads will run consume function. */
    pthread_create(&consumer1,nullptr,&consume,nullptr);
    pthread_create(&consumer2,nullptr,&consume,nullptr);

    /* Creates new threads. The new threads will run produce function. */
    pthread_create(&producer1,nullptr,&produce,nullptr);
    pthread_create(&producer2,nullptr,&produce,nullptr);
    pthread_create(&producer3,nullptr,&produce,nullptr);

    /* main thread is blocked from finishing */
    while(true) {
        /* Endless Loop */
    }
}

/* Consumes data continuously */
void *consume(void * unused) {
    int returnedZahl;
    int id = pthread_self();
    /* Endless Loop */
    while(true) {
        pthread_mutex_lock(&getMutex);
        returnedZahl = get();
        pthread_mutex_unlock(&getMutex);
        printf("[consume]:: Thread %d hat Zahl %d konsumiert\n", id, returnedZahl);
    }
}

/* Produces new zahl continuously and puts it into data */
void *produce(void * unused) {
    int id = pthread_self();
    /* Endless Loop */
    while(true) {
        zahl++;
        pthread_mutex_lock(&putMutex);
        printf("[produce]:: Thread %d hat Zahl %d produziert\n", id, zahl);
        put(zahl);
        pthread_mutex_unlock(&putMutex);
    }
}