#include "Mensaje.h"
#include "SocketDatagrama.h"
class Solicitud
{
public:
    Solicitud();
    char *doOperation(char *IP, int puerto, int operationId, char *arguments);

private:
    mensaje lastResponse;
    SocketDatagrama *socketlocal;
    struct mensaje response;
    int requestID;
};