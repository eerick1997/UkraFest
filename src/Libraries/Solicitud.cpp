#include "Solicitud.h"
#include <sys/time.h>

//int Solicitud::requestID = 0;

Solicitud::Solicitud() {
    socketlocal = new SocketDatagrama(0);
    requestID = 0;
}

char *Solicitud::doOperation(char *IP, int puerto, int operationId, char *arguments) {
    short n = 7;
    time_t segundos = 2;
    suseconds_t microsegundos = 500000;

    struct mensaje datos;
    datos.messageType = 1123456;
    datos.requestId = requestID;
    datos.operationId = suma;
    memcpy(datos.arguments, arguments, 32);
    PaqueteDatagrama paq((char *)&datos, sizeof(datos), IP, puerto);

    int result = -1;
    while ((n--) > 0 && result < 0) {
        fflush(stdout);
        socketlocal->envia(paq);
        result = socketlocal->recibeTimeout(paq, segundos, microsegundos);
        if (result > 0) {
            memcpy(&response, paq.obtieneDatos(), paq.obtieneLongitud());
            if (response.messageType == REPETIDO) {
                //printf("REPETIDO\n");
                printf("R  %d , O %d \n", response.requestId, requestID);
                if (response.requestId != requestID)
                {
                    result = socketlocal->recibeTimeout(paq, segundos, microsegundos);
                    memcpy(&response, paq.obtieneDatos(), paq.obtieneLongitud());
                    lastResponse = response;
                    requestID++;
                }
                else
                {
                    requestID++;
                    break;
                }
            }
            else
            {
                lastResponse = response;
                requestID++;
                break;
            }
        }
        else
        {
            printf("NO llego nada, %d \n", requestID);
        }
    }
    if (result == -1)
    {
        printf("Servidor no disponible\n");
        exit(0);
    }

    return response.arguments;
}