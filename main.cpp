#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
using namespace std;
// const double matrixAdyacencia[7][7] = {
//     {0, 168.5, 0, 318.71, 144.63, 0, 0},
//     {168.5, 0, 213.14, 198.16, 193.84, 245.56, 0},
//     {0, 213.14, 0, 140.04, 0, 0, 289.11},
//     {318.71, 198.16, 140.04, 0, 0, 142.34, 0},
//     {144.63, 193.84, 0, 0, 0, 155.46, 0},
//     {0, 245.56, 0, 142.34, 155.46, 0, 137.18},
//     {0, 0, 289.11, 0, 137.18, 0, 0}};
// bool elementMatrix[7] = {false, false, false, false, false, false, false};
// const double heuristicCost[7] = {
//     420.12,
//     346.44,
//     292.11,
//     166.74,
//     292.62,
//     137.18,
//     0};
 const double matrixAdyacencia[7][7] = {
     {0, 3, 0, 0, 0, 10, 0},
     {3, 0, 9, 0, 8, 7, 0},
     {0, 9, 0, 15, 0, 25, 0},
     {0, 0, 15, 0, 8, 0, 0},
     {0, 8, 0, 8, 0, 6, 9},
     {10, 7, 25, 0, 6, 0, 4},
     {0, 0, 0, 0, 9, 4, 0}};
 bool elementMatrix[7] = {false, false, false, false, false, false, false};
 const double heuristicCost[7] = {
     40,
     35,
     35,
     30,
     20,
     15,
     0};
// const double matrixAdyacencia[12][12] = {
//     {0, 142, 162, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//     {142, 0, 0, 0, 125, 0, 0, 0, 304, 0, 0},
//     {162, 0, 0, 0, 113, 0, 0, 0, 0, 0, 0, 0},
//     {0, 280, 0, 0, 0, 52, 0, 227, 0, 0, 0, 0},
//     {0, 125, 113, 0, 0, 210, 0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 52, 210, 0, 296, 0, 237, 0, 0, 0},
//     {0, 0, 0, 0, 0, 296, 0, 0, 102, 0, 383, 0},
//     {0, 0, 0, 227, 0, 0, 0, 0, 0, 0, 447, 0},
//     {0, 304, 0, 0, 0, 237, 102, 0, 0, 74, 283, 0},
//     {0, 0, 0, 0, 0, 0, 0, 0, 74, 0, 244, 0},
//     {0, 0, 0, 0, 0, 0, 383, 447, 283, 244, 0, 226},
//     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 226, 0},
// };

// bool elementMatrix[12] = {false, false, false, false, false, false, false, false, false, false, false, false};

// const double heuristicCost[12] = {
//     893,
//     774,
//     764,
//     734,
//     658,
//     695,
//     571,
//     557,
//     473,
//     437,
//     226,
//     0};

struct Nodo
{
    int id;
    int value;
    Nodo *next;
};

void insertOpenList(Nodo *&, int, int);
void insertClosedList(Nodo *&, Nodo *&, Nodo *);
bool emptylist(Nodo *);
void deleteList(Nodo *&);

void searchAStar(int, int);
void searchElementMatrix(Nodo *&, Nodo *);
void addClosedList(Nodo *&, Nodo *&, Nodo *&);
void showList(Nodo *);
bool locate = false;
int main()
{

    const int longitudElement = (sizeof(elementMatrix) - sizeof(*elementMatrix)) + 1;

    int nodoInitial=0;
    int nodoFinal=0;
    cout <<"ingrese el nodo inicial";
    cin >> nodoInitial;
    cout <<"ingrese el nodo final";
    cin >> nodoFinal;

    searchAStar(nodoFinal, nodoInitial);
    return 0;
}
void searchAStar(int meta, int initialNode)
{

    Nodo *ListOpen = NULL;
    Nodo *firstClosedList = NULL;
    Nodo *lastClosedList = NULL;
    Nodo *aux = new Nodo;
    aux->id = initialNode;
    aux->value = 0;
    aux->next = NULL;

    insertClosedList(firstClosedList, lastClosedList, aux); ///insertamos el nodo inicial en la lista cerrada

    while (!locate)
    {

        if (lastClosedList->id != meta)
        {
            //   cout << endl
            //      << "ultimo en la lista de cierre" << lastClosedList->id << endl;
            searchElementMatrix(ListOpen, lastClosedList); ///buscamos el nodo con menor valor de la lista

            // cout<<"ingreso a if diferente de meta";
        }

        addClosedList(firstClosedList, lastClosedList, ListOpen);
        //insertamos el nodo de menor valor de la lista cerrada en la lista cerrada

        // cout << endl
        //      << endl
        //      << "antes del if(lastClosedList->id==meta)-->" << lastClosedList->id << endl;
        if (lastClosedList->id == meta)
        {
            cout << endl
                 << "mostrador lista Cerrada" << endl;
            showList(firstClosedList);
            locate = true;
        }
    }
}
///buscara elementos adyacentes y agregara a la lista vacia
void searchElementMatrix(Nodo *&list, Nodo *lastClosedList)
{
    double sumAux = 0.0;
    int legnth = (sizeof(elementMatrix) - sizeof(*elementMatrix)) + 1;
    for (int i = 0; i < legnth; i++)
    {
        if (elementMatrix[i] == false && matrixAdyacencia[lastClosedList->id][i] != 0)
        {

            sumAux = heuristicCost[i] + matrixAdyacencia[lastClosedList->id][i]; //f(x)= h(x)+g(x)
            insertOpenList(list, i, sumAux);
            elementMatrix[i] = true;
            cout << endl
                 << "ingresando " << list->id << " " << list->value << endl;
            cout << "valor de recorrido: " << matrixAdyacencia[lastClosedList->id][i] << endl;
        }
    }
}

void addClosedList(Nodo *&firstClosedList, Nodo *&lastClosedList, Nodo *&listOpen)
{
    //  cout << "ingresando a addClosedList" << endl;

    Nodo *aux = new Nodo;
    aux->id = listOpen->id;
    aux->value = listOpen->value;
    aux->next = NULL;
    //  cout << "aux" << aux->id << endl;
    deleteList(listOpen);
    insertClosedList(firstClosedList, lastClosedList, aux);
}

void insertOpenList(Nodo *&list, int id, int value)
{

    Nodo *new_nodo = new Nodo();
    new_nodo->value = value;
    new_nodo->id = id;

    Nodo *aux1 = list;
    Nodo *aux2;

    while ((aux1 != NULL) && (aux1->value < value))
    {
        aux2 = aux1;
        aux1 = aux1->next;
    }

    if (list == aux1)
    {
        list = new_nodo;
    }
    else
    {
        aux2->next = new_nodo;
    }
    new_nodo->next = aux1;

    cout << "\t Elemento " << id << "insertado correctamente a lista abierta\n";
}
void deleteList(Nodo *&list)
{

    elementMatrix[list->id] = true;
    Nodo *aux1 = list;
    list = list->next;
    delete aux1;
}

void insertClosedList(Nodo *&firstClosedList, Nodo *&LastClosedList, Nodo *nodo)
{
    Nodo *new_nodo = new Nodo();
    new_nodo = nodo;
    new_nodo->next = NULL;
    if (emptylist(firstClosedList))
    {
        firstClosedList = new_nodo;
    }
    else
    {
        LastClosedList->next = new_nodo;
    }
    LastClosedList = new_nodo;
    cout << "\t Elemento " << nodo->id << " insertado correctamente en la lista cerrada\n";
}

bool emptylist(Nodo *firstClosedList)

{
    return (firstClosedList == NULL) ? true : false;
}

void showList(Nodo *list)
{
    while (list != NULL)
    {
        cout << list->id << "   " << list->value << endl;
        list = list->next;
    }
}