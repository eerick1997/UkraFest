#include "Mensaje.h"
#include "SocketDatagrama.h"
#include <vector>
class Solicitud
{
public:
    Solicitud();
    char * doOperation(char *IP, int puerto, int operationId, char *arguments);

private:
    SocketDatagrama *socketlocal;
    struct mensaje response;
    static int requestID;
};