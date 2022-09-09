#include <iostream>
#include <fstream>
using namespace std;
const int dprod = {5};

//Funciones a utilizar
void mostrarcliente(string vec[], int dim){
    for(int i = 0; i < dim; ++i)
        cout << i << ":" << vec[i] << endl;
}
void mostrarproducto(string vec[], int dim){
    for(int i = 0; i < dim; ++i)
        cout << i <<":" << vec[i] << endl;
}
void listado(float mat[][dprod], int dclie, string cliente[], string producto[]){//Punto 1
    cout <<"\nListado por clientes, de los tipos de productos que superen los 13000 Kg acumulados:";
    cout <<endl;
    for(int i = 0; i < dclie; ++i){
        for(int j = 0; j < dprod; ++j){
            if (mat[i][j] > 13000){
            cout << cliente[i] << ": " << producto[j] << ", "<< endl;
            }
        }
    }
}
void mostrarprodmax(float v[], int dim, string producto[], int vpos[]){//Punto 2
    for(int i = 0; i < dim; ++i){
        cout << producto[vpos[i]] << " : " << v[i] << endl;
    }
}
int mayorcant(float m[][dprod], int dclie){//Punto 2
    int aux = {0};
    int max = {0};
    int pos = {0};
    for(int i = 0; i < dclie; ++i){
        for(int j = 0; j < dprod; ++j){
            if(m[i][j] > 13000){
                aux++;
            }
        }
        if (max < aux){
            max = aux;
            pos = i;
        } aux = 0;
    }
return pos;
}
void listasce(float vec[], int dim, int vaux[]){//Punto 2
    int i, imin, ipos;
    for(ipos = 0; ipos < dim -1; ++ipos){
        imin = ipos;
        for(i = ipos+1; i < dim; ++i){
            if (vec[i] < vec[imin]){
                imin = i;
            }
        }
            swap(vec[ipos], vec[imin]);
            swap(vaux[ipos], vaux[imin]);
    }
}

int main(){
    const int ntprod = {5};
    const int nclie = {8};
    //Punto 1
    float pesos[nclie][ntprod] = {};
    //Punto 2
    float km[nclie][ntprod] = {};
    int maxprod;
    int v[ntprod];
    float pmax[ntprod];
    //Punto 3
    float entregas[ntprod] = {};
    //lectura archivo de datos
    ifstream adatos;
    adatos.open("Datos.txt");
    if(!adatos){
        cout << "Error al abrir el archivo"<<endl;
        return 1;
    }
    int iclie, itprod = {0};
    double peso, dist = {0};
    while(adatos >> iclie >> itprod >> peso >> dist){
        pesos[iclie][itprod] += peso;
        km[iclie][itprod] += dist;
        entregas[itprod]++;
    } adatos.close();

    string cliente[nclie];//nombre de cliente
    string producto[ntprod];//nombre del producto
    //lectura archivo nombres

    adatos.open("Nombres.txt");
    if(!adatos){
        cout << "Error al abrir el archivo" <<endl;
        return 1;
    }
    for(int i = 0; i < nclie && adatos >> cliente[i]; ++i);
    for(int i = 0; i < ntprod && adatos >> producto[i]; ++i);
    adatos.close();
    //Mostrar datos
    cout<<"Datos de Archivos"<<endl;
    cout <<endl;

    cout <<"Clientes"<<endl;
    mostrarcliente(cliente, nclie);
    cout <<endl;

    cout <<"Productos"<<endl;
    mostrarproducto(producto, ntprod);

    //Punto 1
    listado(pesos, nclie, cliente, producto);

    //Punto 2
    maxprod = mayorcant(pesos, nclie);
    for(int i = 0; i < nclie; ++i){
        for(int j = 0; j < ntprod; ++j){
            v[j] = j;
            pmax[j] = km[maxprod][j];
        }
    }
    listasce(pmax, ntprod, v);
    cout <<"Listado de Km recorridos por tipo de producto (ascendente):" << endl;
    mostrarprodmax(pmax, ntprod, producto, v);
    //Punto 3
    cout << "Cantidad de entregas para el tipo de producto Textiles: " << entregas[3] <<endl;
return 0;
}