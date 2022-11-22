#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <map>

#define LED1 396
#define LED2 397
#define LED3 429
#define LED4 393

using namespace std;

void setGPIO(unsigned int gpio, string status) {
    int io = open("/dev/demo", O_WRONLY);
    if(io < 0){
        printf("can't open device\n");
        return;
    }
    char buf[10];
    if(status == "on"){
        strcpy(buf, (to_string(gpio) + "1").c_str());
    }
    else {
        strcpy(buf, (to_string(gpio) + "0").c_str());
    }
    cout << "input: " << buf << endl;
    write(io, buf, 5);
    close(io);
    return;
}

void readGPIO(unsigned int gpio) {
    int io = open("/dev/demo", O_WRONLY);
    if(io < 0){
        printf("can't open device\n");
        return;
    }
    char buf[64];
    strcpy(buf, (to_string(gpio) + "2").c_str());
    write(io, buf, 5);
    read(io, buf, sizeof(buf));
    cout << buf << endl;
    close(io);
    return;
}

int main(int argc, char** argv){
    if(argc == 2) {
        switch(argv[1][3]) {
        case '1':
            readGPIO(LED1);
            break;
        case '2':
            readGPIO(LED2);
            break;
        case '3':
            readGPIO(LED3);
            break;
        case '4':
            readGPIO(LED4);
            break;
        }
        
    }
    else if(argc == 3) {
        switch(argv[1][3]) {
        case '1':
            setGPIO(LED1, argv[2]);
            break;
        case '2':
            setGPIO(LED2, argv[2]);
            break;
        case '3':
            setGPIO(LED3, argv[2]);
            break;
        case '4':
            setGPIO(LED4, argv[2]);
            break;
        }
    }
    return 0;
}

