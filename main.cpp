//
// Created by hato0 on 23.05.2022.
//

#include <pthread.h>
#include <cstdio>

pthread_mutex_t derMutex;
pthread_cond_t dieCondition;

pthread_t consumer;
pthread_t producer;

bool available = false;
int data;

void *produce(void *);

void *consume(void *);

void* put(int zahl) {
    int id = pthread_self();
    while(available) {
        printf("[put]:: Thread %d geraet in WAITING \n",id);
        pthread_cond_wait(&dieCondition,&derMutex);
        printf("[put]:: Thread %d macht weiter \n", id);
    }
    data = zahl;
    available = true;
    pthread_cond_broadcast(&dieCondition);
    return nullptr;
}

int get() {
    int id = pthread_self();
    while(!available) {
        printf("[put]:: Thread %d geraet in WAITING \n",id);
        pthread_cond_wait(&dieCondition,&derMutex);
        printf("[put]:: Thread %d macht weiter \n", id);
    }
    available = false;
    pthread_cond_broadcast(&dieCondition);
    return data;
}


int main() {
    pthread_mutex_init(&derMutex, nullptr);
    pthread_cond_init(&dieCondition, nullptr);


    pthread_create(&consumer,nullptr,&consume,nullptr);
    pthread_create(&consumer,nullptr,&consume,nullptr);
    pthread_create(&producer,nullptr,&produce,nullptr);
    pthread_create(&producer,nullptr,&produce,nullptr);
    pthread_create(&producer,nullptr,&produce,nullptr);

    while(true) {

    }
}

void *consume(void * unused) {
    int zahl;
    int id = pthread_self();
    while(true) {
        pthread_mutex_lock(&derMutex);
        zahl = get();
        pthread_mutex_unlock(&derMutex);
        printf("[consume]:: Thread %d hat Zahl %d konsumiert\n", id, zahl);
    }
}

void *produce(void * unused) {
    int zahl = 0;
    int id = pthread_self();
    while(true) {
        zahl++;
        pthread_mutex_lock(&derMutex);
        printf("[produce]:: Thread %d hat Zahl %d produziert\n", id, zahl);
        put(zahl);
        pthread_mutex_unlock(&derMutex);
    }
}