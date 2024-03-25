#include <stdio.h> 
#include <unistd.h> 
#include <math.h> 
int main()
{
    double res; 
    void *p;
    p = sbrk(40000); // aumenta el espacio de datos del programa en X bytes 
    res = sin(30.0);
    printf("res = %f \n", res); 
    printf("PID = %d \n", getpid()
    ); 
    return(0);
}
