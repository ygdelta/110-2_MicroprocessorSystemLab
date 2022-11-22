#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "gpio.h"

#define LED1 396
#define LED2 397
#define LED3 429
#define LED4 393

pthread_mutex_t mutex;
int gpioPin[4] = {LED1, LED2, LED3, LED4};

//子執行緒
void* child(void * data) {
    pthread_mutex_lock(&mutex);
    int* input = (int*) data;
    GPIO::Set_dir(input[0], "out");
    GPIO::Set_val(input[0], input[1]);
    printf("GPIO: %d status: %d\n", input[0], input[1]);
    pthread_mutex_unlock(&mutex);
    sleep(1);
    GPIO::Set_val(input[0], 0);
    pthread_exit(NULL);
}

int main(int argc, char** argv) {
    pthread_t t1, t2, t3, t4;
    pthread_mutex_init(&mutex, 0);
    for(int i = 0; i < 4; i++) {
        GPIO::Export(gpioPin[i]);
    }
    

    int s0[2] = {LED1, argv[1][0] - '0'};
    int s1[2] = {LED2, argv[1][1] - '0'};
    int s2[2] = {LED3, argv[1][2] - '0'};
    int s3[2] = {LED4, argv[1][3] - '0'};

    printf("status: %s\n", argv[1]);

    

    for(int i = 0; i < argv[2][0] - '0'; i++) {
        pthread_create(&t1, NULL, child, s0);
        sleep(1);
        pthread_create(&t2, NULL, child, s1);
        sleep(1);
        pthread_create(&t3, NULL, child, s2);
        sleep(1);
        pthread_create(&t4, NULL, child, s3);
        sleep(1);
        pthread_join(t1, NULL);
        pthread_join(t2, NULL);
        pthread_join(t3, NULL);
        pthread_join(t4, NULL);
    }

    

    return 0;
}