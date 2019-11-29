#include "../../Libraries/Solicitud.h"
#include <sys/stat.h>
#include <vector>
#include <string>
#include <thread>
#include <iostream>
#include <vector>

using namespace std;



int main(){
	Solicitud solicitud=Solicitud();
	char respuesta[TAM_MAX_DATA];
	char valores[TAM_MAX_DATA];
	memcpy(valores,"1",TAM_MAX_DATA);
	memcpy(respuesta,solicitud.doOperation("127.0.0.1",9005,1,valores),TAM_MAX_DATA);
	cout<<respuesta<<endl;
  return 0;
}