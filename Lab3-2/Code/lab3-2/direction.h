#include<iostream>
#include<string>
#include<fstream>
#include <unistd.h>
#include <fcntl.h>
#include <sstream>

int gpio_direction(unsigned int gpio,std::string dirStatus)
{
    int fd;
    char buf[64];

    snprintf(buf,sizeof(buf),"/sys/class/gpio/gpio%d/direction",gpio);
    fd = open(buf, O_WRONLY);
    if(fd<0){
        perror("gpio/direction");
        return fd;
    }
    if(dirStatus == "out")
        write(fd,"out",4);
    else
        write(fd,"in",3);
    close(fd);
    return 0;
}
