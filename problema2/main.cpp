#include <iostream>
#include <fstream>
#include <math.h>
#include <string>
#include <string.h>
using namespace std;

//en esta parte se hace la definición de las funciones que usaremos mas adelante.

//codificacion y decodificacion
void letra_a_binario(char letra, char *binario);
int binario_a_letra(char *binario);
char *codificar(char *cadena, int tam_cadena,int n);
char *decodificar(char *cad_codificada, int tam_cad, int bits_por_bloque);

//manejo de cadenas
void concatenar(char *cadena_1,char *cadena_2,int tam_1,int tam_2);

//cajero
void admin();
void usuario();
int contar_caracteres(char * cadena);
void retirar_dinero(int* saldo);
bool comparar_strings(string original, string ingresado, int tam);

//variables globales
int semilla = 4;
fstream data_in;

bool comparar_strings(string original, string ingresado,int tam)
{

    if(ingresado.size() != tam)
        return false;

    for(int u = 0; u < tam; u++)
    {
        if(original[u] != ingresado[u])
            return false;
    }
    return true; // si se llegó al final sin encontrar diferencias
}

void retirar_dinero(int *saldo)
{
    int retirar = 0;


    cout<<endl<<"Ingrese cuanto dinero desea retirar: ";
    cin>>retirar;

    if(*saldo > retirar)
    {
        *saldo -= retirar;
        cout<<endl<<"Su nuevo saldo es: "<<*saldo<<endl;
    }

    else
        cout<<"Saldo insuficiente."<<endl<<"Tu saldo es: "<<*saldo<<endl;

    cout<<endl;

}


int binario_a_letra(char *binario)
{
    int letra = 0;

    for (int i = 0; i < 8 ;i++)
    {
        if(binario[i] == '1')
            letra += pow(2,7-i);
    }
    return letra;
}

void letra_a_binario(char letra, char *binario)
{
    int ascii = letra;

    for(int i = 7; i >= 0; i-- )
    {
        binario[i] = ascii % 2 + 48;
        ascii /=2;
    }
}

void concatenar(char *cadena_1, char *cadena_2, int tam_1, int tam_2)
{
    for(int i = 0; i < tam_2; i++)
        cadena_1[i + tam_1] = cadena_2[i];
}

int main()
{
    int opcion = 0;
    do
    {
        //aqui se encuentran todas las posibles opciones a elegir y sus respectivas funciones dentro del código.
        cout<<"BIENVENIDO" <<endl<< "Ingresar como:" <<endl<< "1. Administrador" <<endl<< "2. Usuario" <<endl<< "3. Salir" <<endl<< "opcion: ";
        cin>>opcion;

        switch(opcion)
        {
        case 1: //admin(); break;

        case 2: //usuario(); break;

        case 3: cout << "Muchas gracias por usar nuestro servicio" << endl << endl;
                break;

        default: cout<<endl<<"Ingresaste una opcion invalida"<<endl;
        }


    }while(opcion != 3);


    return 0;
}
