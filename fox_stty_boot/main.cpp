#include <unistd.h>
#include "Boot.h"

int main()
{
    Boot boot;
    boot.start();
    while (true)
    {
        ::usleep(1*1000*1000);
    }
        
}