#pragma once
#define GPIO_H
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

namespace GPIO{

    int Export(unsigned int gpio) {
        fstream file;
        char buf[64];
           
        file.open("/sys/class/gpio/export", ios::out);
        if(!file) {
            perror("gpio/export");
            return 0;
        }

        int len = snprintf(buf, sizeof(buf), "%d", gpio);
        file.write(buf, len);
        file.close();

        return 0;
    }

    int Unexport(unsigned int gpio) {
        fstream file;
        char buf[64];

        file.open("/sys/class/gpio/unexport", ios::out);
        if(!file) {
            perror("gpio/unexport");
            return 0;
        }

        int len = snprintf(buf, sizeof(buf), "%d", gpio);
        file.write(buf, len);
        file.close();

        return 0;
    }

    int Set_dir(unsigned int gpio, string status) {
        fstream file;
        char buf[64];
        snprintf(buf, sizeof(buf), "/sys/class/gpio/gpio%d/direction", gpio);

        file.open(buf, ios::out);
        if(!file) {
            perror("gpio/direction");
            return 0;
        }

        if(status == "out") {
            file.write("out", 4);
        }
        else {
            file.write("in", 3);
        }

        file.close();
        return 0;
    }

    int Set_val(unsigned int gpio, int value) {
        fstream file;
        char buf[64];
        snprintf(buf, sizeof(buf), "/sys/class/gpio/gpio%d/value", gpio);

        file.open(buf, ios::out);
        if(!file) {
            perror("gpio/value");
            return 0;
        }

        if(value == 1) {
            file.write("1", 2);
        }
        else {
            file.write("0", 2);
        }

        file.close();
        return 0;
    }
}
