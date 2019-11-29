#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <iostream> 
#include <string>
#include <cstring>
#include <bits/stdc++.h>
#include <vector>
using namespace std;
int main(){
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
inFile.open("server/libro.txt");
// si el archivo no fue encontrado
if(!inFile){
    cout << "No se ha encontrado el libro\n";
    exit(1);
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