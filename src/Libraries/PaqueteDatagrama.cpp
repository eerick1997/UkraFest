#include "PaqueteDatagrama.h"
#include <stdio.h>
#include <string.h>

using namespace std;

PaqueteDatagrama::PaqueteDatagrama(char *Datos, unsigned int Longitud, char *dirIP, int Puerto){
    longitud = Longitud;
    datos = new char[longitud];
    memcpy(datos, Datos, longitud);
    memcpy(ip, dirIP, sizeof(this->ip));
    puerto = Puerto;
}

PaqueteDatagrama::PaqueteDatagrama(unsigned int Longitud){
    longitud = Longitud;
    datos = new char[longitud];
}

char *PaqueteDatagrama::obtieneDireccion(){
    return ip;
}

unsigned int PaqueteDatagrama::obtieneLongitud(){
    return longitud;
}

int PaqueteDatagrama::obtienePuerto(){
    return puerto;
}

char *PaqueteDatagrama::obtieneDatos(){
    return datos;
}

void PaqueteDatagrama::inicializaPuerto(int Puerto){
    puerto = Puerto;
}

void PaqueteDatagrama::inicializaIp(char *IP){
    memcpy(ip, IP, sizeof(ip));
}

void PaqueteDatagrama::inicializaDatos(char *Datos){
    memcpy(datos, Datos, longitud);
}

PaqueteDatagrama::~PaqueteDatagrama(){
    delete[] datos;
}