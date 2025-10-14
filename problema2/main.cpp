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

//codificacion y decodificacion
char * decodificar(char * cad_codificada,int tam_cad,int bits_por_bloque)
{
    char * original = new char [tam_cad], *texto = new char [tam_cad/8] ;

    int cont_1 = 0,cont_0 = 0,cont_bloques = 0;

    //se decodifica la primera linea


    for(int i = 0; i < bits_por_bloque ; i++)
    {
        if(cad_codificada[i] == '1')
            original[i] = '0';
        else
            original[i] = '1';
    }

    for(int i = 0; i < bits_por_bloque ; i++)
    {
        if(original[i] == '1')
            cont_1++;
        else
            cont_0++;
    }

    cont_bloques++;

    //se decodifican las lineas siguientes
    while(cont_bloques < tam_cad/bits_por_bloque)
    {
        if(cont_0 == cont_1)
        {
            for(int i = bits_por_bloque * cont_bloques; i < (bits_por_bloque * cont_bloques)+ bits_por_bloque ; i++)
            {
                if(cad_codificada[i] == '1')
                    original[i] = '0';
                else
                    original[i] = '1';
            }
        }

        else if(cont_0 > cont_1)
        {
            for(int i = (bits_por_bloque * cont_bloques); i < (bits_por_bloque * cont_bloques)+ bits_por_bloque ; i++)
            {
                if(((i+1 - (bits_por_bloque * cont_bloques))%2) == 0 )
                {
                    if(cad_codificada[i] == '1')
                        original[i] = '0';
                    else
                        original[i] = '1';
                }
                else
                    original[i] = cad_codificada[i];
            }
        }

        else
        {
            for(int i = (bits_por_bloque * cont_bloques); i < (bits_por_bloque * cont_bloques)+ bits_por_bloque ; i++)
            {
                if(((i+1 - (bits_por_bloque * cont_bloques))%3) == 0 )
                {
                    if(cad_codificada[i] == '1')
                        original[i] = '0';
                    else
                        original[i] = '1';
                }
                else
                    original[i] = cad_codificada[i];
            }
        }

        cont_0 = 0;
        cont_1 = 0;


        for(int i = (bits_por_bloque * cont_bloques); i < (bits_por_bloque * cont_bloques)+ bits_por_bloque ; i++)
        {
            if(original[i] == '1')
                cont_1++;
            else
                cont_0++;
        }

        cont_bloques++;

    }

    cont_1 = 0;

    for(int i = 0; i < tam_cad ; i+= 8)
    {
        texto [cont_1] = binario_a_letra(&original[i]);
        cont_1++;
    }

    delete[] original;

    return texto;
}

char *codificar(char * cadena, int tam_cadena, int n)
{
    int cont_0 = 0,cont_1 = 0,cont_bloques = 0;
    char * nueva = new char [tam_cadena * 8],* codificado = new char [tam_cadena * 8], binario[8];


    // se hace transforma a binario el primer caracter
    letra_a_binario(cadena[0],binario);

    concatenar(nueva,binario,0,8);

    // se transforma a binario el resto de caracteres
    for (int i = 0; i < tam_cadena; i++)
    {
        letra_a_binario(cadena[i+1],binario);
        concatenar(nueva,binario,(i*8)+8,8);
    }

    for (int i = 0; i < tam_cadena*8; i++)
        codificado[i] = nueva[i];

    while(cont_bloques < (tam_cadena*8)/n)
    {


        if(cont_bloques == 0)
        {
            //se codifica el primer bloque

            for(int i = 0; i < n; i++) // se cuentan los 1 y 0
            {
                if(nueva[i] == '1')
                    cont_1++;
                else
                    cont_0++;
            }

            for (int i = 0; i < n; i++) // se intercambian los 1 y 0
            {
                if(nueva[i] == '1')
                    codificado[i] = '0';
                else
                    codificado[i] = '1';
            }
        }

        else
        {

            for(int i = n*cont_bloques - n; i < n*cont_bloques; i++) // se cuentan los 1 y 0
            {
                if(nueva[i] == '1')
                    cont_1++;
                else
                    cont_0++;
            }

            if(cont_0 == cont_1)
            {
                for (int i = n*cont_bloques; i < (n*cont_bloques)+n; i++) // se intercambian los 1 y 0
                {
                    if(nueva[i] == '1')
                        codificado[i] = '0';
                    else
                        codificado[i] = '1';
                }
            }

            else if(cont_0 > cont_1)
            {
                for (int i = (n*cont_bloques) + 1; i < (n*cont_bloques) + n; i+=2)
                {
                    if(nueva[i] == '1')
                        codificado[i] = '0';
                    else
                        codificado[i] = '1';
                }
            }

            else
            {
                for (int i = (n*cont_bloques) + 2; i < (n*cont_bloques) +n; i+=3)
                {
                    if(nueva[i] == '1')
                        codificado[i] = '0';
                    else
                        codificado[i] = '1';
                }
            }
        }
        cont_bloques ++;
        cont_0 = 0;
        cont_1 = 0;

    }

    return codificado;
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
