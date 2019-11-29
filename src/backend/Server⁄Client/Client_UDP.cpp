#include "../../Libraries/Solicitud.h"
#include <sys/stat.h>
#include <vector>
#include <string>
#include <thread>
#include <iostream>
#include <vector>
#include <thread>
#include <atomic>
#include <unistd.h>

using namespace std;

atomic<int> cont1(0), cont2(0), cont3(0), Total_Words(0);

int Tokenizer(){
	int64_t contador=0;	// contador de palabras de todo el texto
	// archivos en los que se guardaran las palabras tokenizadas para enviarlas a los servidores
	std::ofstream ofs1("servidor1.txt", std::ofstream::out);
	std::ofstream ofs2("servidor2.txt", std::ofstream::out);
	std::ofstream ofs3("servidor3.txt", std::ofstream::out);
	std::ofstream ofs4("servidor4.txt", std::ofstream::out);
	string str1;
	// caracteres auxiliares para el procesamiento del texto
	char aacm = 'á';
	char eacm = 'é';
	char iacm = 'í';
	char oacm = 'ó';
	char uacm = 'ú';
	char aacM = 'Á';
	char eacM = 'É';
	char iacM = 'Í';
	char oacM = 'Ó';
	char uacM = 'Ú';
	// objeto archivo
	ifstream inFile;
	inFile.open("server/libro_aux.txt");
	// si el archivo no fue encontrado
	if(!inFile){
		cout << "No se ha encontrado el libro\n";
		return -1;
	}
	// tokeniza el archivo, elimina caracteres especiales y cambia a minusculas
	while( inFile >> str1){
		std::string aux = "";
		for(char letra:str1){
			if (isalpha(letra)){
			aux=aux+(char)tolower(letra);
			}
			else if (letra==aacM || letra==aacm){
			aux=aux+"á";
			}
			else if (letra==eacM || letra==eacm){
			aux=aux+"é";
			}
			else if (letra==iacM || letra==iacm){
			aux=aux+"í";
			}
			else if (letra==oacM || letra==oacm){
			aux=aux+"ó";
			}
			else if (letra==uacM || letra==uacm){
			aux=aux+"ú";
			}
			// condicion especial
				// si encuentra un caracter '-' lo reemplaza por espacio para separar las palabras tipo abc-def
			else if (letra=='-'){
			aux=aux+"\n";
			// distribuye las palabras en 4 archivos diferentes que se enviaran a los servidores
			if(contador%4==0){
				ofs1 << aux;	
			}
			else if(contador%4==1){
				ofs2 << aux;
			}
			else if(contador%4==2){
				ofs3 << aux;
			}
			else if(contador%4==3){
				ofs4 << aux;
			}
			contador++;
			aux="";
			}
		}
		// distribuye las palabras en 4 archivos diferentes que se enviaran a los servidores
		str1 = aux+"\n";
		if(contador%4==0){
			ofs1 << str1;	
		}
		else if(contador%4==1){
			ofs2 << str1;
		}
		else if(contador%4==2){
			ofs3 << str1;
		}
		else if(contador%4==3){
			ofs4 << str1;
		}
		contador++;
	}
	// cierra los archivos
	inFile.close();
	ofs1.close();
	ofs2.close();
	ofs3.close();
	ofs4.close();

	return 0;
}


// ********************* Hilo 1 *********************
void Hilo1(string ruta1){

	vector <int> v;
	ifstream in(ruta1 +".txt", ios::binary);
    if (in.is_open()){
        while (!in.eof()){
            v.push_back(in.get());
        }
    }
    in.close();
	int64_t tam= v.size();
	char chararray[TAM_MAX_ARG], *resp;
	int paquetes_a_enviar = ceil((double)tam/TAM_MAX_ARG), j=0;
	for(int i=0; i<paquetes_a_enviar; i++){

		for(int l=0; l<TAM_MAX_ARG && j<tam; j++){
			chararray[l] = v[j];
			cout << chararray[l];
			l++;
		}

		Solicitud a;
		cout << "A" << endl;
		//sleep(5);
		resp = a.doOperation("10.100.69.31", 7200, cont1++, (char*)&chararray);
		cout << "B" << endl;
		int resp_int ;
		memcpy(&resp_int, resp, sizeof( resp_int ) );
		cout << endl << resp_int << endl;
		//Total_Words += resp_int;
	}
	//pthread_exit(0);
}

// ********************* Hilo 2 *********************
void Hilo2(string ruta2){

	vector <int> v;
	ifstream in(ruta2 +".txt", ios::binary);
    if (in.is_open()){
        while (!in.eof()){
            v.push_back(in.get());
        }
    }
    in.close();
	int64_t tam= v.size();
	char chararray[TAM_MAX_ARG], *resp;
	int paquetes_a_enviar = ceil((double)tam/TAM_MAX_ARG), j=0;
	for(int i=0; i<paquetes_a_enviar; i++){

		for(int l=0; l<TAM_MAX_ARG && j<tam; j++){
			chararray[l] = v[j];
			cout << chararray[l];
			l++;
		}

		Solicitud a;
		//sleep(5);
		resp= a.doOperation("192.168.43.75", 7200, cont1++, (char*)&chararray);
		int resp_int ;
		memcpy(&resp_int, resp, 4);
		cout << endl << resp_int << endl;
		//Total_Words += resp_int;
	}
	/*for(int i=0; i<10; i++){
		cout << "Dos " << i << endl;
		sleep(2);
	}*/
	//pthread_exit(0);
}


int main(){

	int i= Tokenizer();
	cout << i << endl;

	thread th1(Hilo1, "servidor1");
	//thread th2(Hilo2, "servidor2");

	//th2.join();
	th1.join();

	cout << "El hilo principal termina " << endl;

	cout << "Palabras totales: " << Total_Words << endl;

	/*Solicitud solicitud=Solicitud();
	char respuesta[TAM_MAX_DATA];
	char valores[TAM_MAX_DATA];
	memcpy(valores,"1",TAM_MAX_DATA);
	memcpy(respuesta,solicitud.doOperation("127.0.0.1",9005,1,valores),TAM_MAX_DATA);
	cout<<respuesta<<endl;
	return 0;*/
}