#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "transport.h"

int main()
{
    char* message;
    client_init("localhost", "5050");
    client_emission("HEL test_$");
    message = client_reception();
    printf("%s\n", message);
    client_terminaison();

    return 0;
}