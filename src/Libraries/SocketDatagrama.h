#include "PaqueteDatagrama.h"
#include <bits/stdc++.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/time.h>

class SocketDatagrama {
public:
    SocketDatagrama( int );
    SocketDatagrama( int, const char * );
    ~SocketDatagrama();
    int recibe(PaqueteDatagrama &p);
    int envia(PaqueteDatagrama &p);
    int recibeTimeout(PaqueteDatagrama &p, time_t segundos, suseconds_t microsegundos);

private:
    struct sockaddr_in direccionLocal;
    struct sockaddr_in direccionForanea;
    timeval timeout;
    int s;
};