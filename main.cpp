#include <iostream>
#include "HTimer.h"

void printfHello() {
    printf(" hello timer \n");
}

int main() {
    HTimer timer;
    timer.event = printfHello;
    timer.setInterval(5000);
    timer.start();
    timer.stop();
    while(1);
    return 0;
}