#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <time.h>


void printarr(int size, int arr[size]);


//ARISTA ARISTA ARISTA ARISTA ARISTA ARISTA ARISTA ARISTA ARISTA ARISTA ARISTA ARISTA 

typedef struct Arista{
    int peso;       //weigth of the edge from one node to another
    int vindex;     //index to the node this is connected to
} arista;

arista* createArista(int i, int w) {
    arista* ret= (arista*) malloc(sizeof(arista));
    ret-> peso= w;
    ret-> vindex= i;
    return ret;
}

void printarr(int size, int arr[size]);


//NODO NODO NODO NODO NODO NODO NODO NODO NODO NODO NODO NODO NODO NODO NODO NODO

typedef struct Nodo{
    int pos;
    int size;
    arista** arrpointer;    //array of edges
} nodo;

nodo* createNodo(int position, int conexiones, int array[2*conexiones]) {  //para crear en tiempo de ejecucion
    //printarr(2*conexiones, array);
    nodo* ret= malloc(sizeof(nodo));
    arista** a= calloc(conexiones, sizeof(arista*));
    //arista* a[conexiones];
    int i= 0;
    while(i< conexiones) {
        a[i]= createArista(array[2*i], array[2*i + 1]);
        i++;
    }
    ret-> pos= position;
    ret-> size= conexiones;
    ret-> arrpointer= a;
    //printf("creado un nodo.\n");
    return ret;
}

void printedgearr(int size, nodo* n);

//HEAP HEAP HEAP HEAP HEAP HEAP HEAP HEAP HEAP HEAP HEAP HEAP HEAP HEAP HEAP HEAP 

int HEAP_SIZE;
nodo** HEAP;
int HEAP_START;
int HEAP_END;
int HEAP_EMPTY;
int HEAP_FULL;

void PRINTSTATE(void);
void printadylist(int size, nodo** n);

/*
void heap(int size, int arr[size]) {
    HEAP_SIZE= size;
    HEAP= (int*) arr;
    HEAP_START= HEAP_END= 0;
}
*/

void heap(int size, nodo* arr[size]){
    HEAP_SIZE= size;
    HEAP= (nodo**) arr;
    HEAP_START= HEAP_END= HEAP_EMPTY= 0;
    HEAP_FULL= 1;
    PRINTSTATE();
    //printf("printstate listo.\n");
    //printadylist(HEAP_SIZE, HEAP);
}


/*
void heapify(void) {
    int min= HEAP[HEAP_START];
    int ind= HEAP_START;
    int i= (ind + 1) % HEAP_SIZE;
    while(i != HEAP_END) {
        if (HEAP[i]< min) {
            min= HEAP[i];
            ind= i;    
        }
        i= (i + 1) % HEAP_SIZE;
    }
    HEAP[ind]= HEAP[HEAP_START];
    HEAP[HEAP_START]= min;
}
*/

void heapifyBy(int pesos[HEAP_SIZE]){
    nodo* min= HEAP[HEAP_START];
    nodo* current;
    int index= HEAP_START;
    int iterator= (index + 1) % HEAP_SIZE;
    while (iterator!= HEAP_END) {
        current= HEAP[iterator];
        if (pesos[current->pos]< pesos[min->pos]){
            min= current;
            index= iterator;
        }
        iterator= (iterator + 1) % HEAP_SIZE;
    }
    HEAP[index]= HEAP[HEAP_START];
    HEAP[HEAP_START]= min;
}


/*
int pop(void) {
    if (HEAP_EMPTY){
        printf("UNDERFLOW: HEAP EMPTY.\nNo se ha quitado el elemento.\n");
    }
    else {
        int aux= HEAP_START;
        HEAP_START= (HEAP_START + 1) % HEAP_SIZE;
        if (HEAP_END== HEAP_START) HEAP_EMPTY= 1;
        if (HEAP_FULL) HEAP_FULL= 0;
        return HEAP[aux];
    }
    return 0;
}
*/

nodo* pop() {
    if (HEAP_EMPTY){
        printf("UNDERFLOW: HEAP EMPTY.\nNo se ha quitado el elemento.\n");
    }
    else {
        int aux= HEAP_START;
        //printf("aux= %d\n", aux);
        HEAP_START= (HEAP_START + 1) % HEAP_SIZE;
        printf("HEAP_START= %d\n", HEAP_START);
        if (HEAP_END== HEAP_START) HEAP_EMPTY= 1;
        printf("EMPTY= %d\n", HEAP_EMPTY);
        if (HEAP_FULL) HEAP_FULL= 0;
        printf("FULL= %d\n", HEAP_FULL);
        printf("popped node: %d- ", HEAP[aux]->pos);
        printedgearr(HEAP[aux]->size, HEAP[aux]);
        return HEAP[aux];
    }
    return 0;
}

/*
void push(int new) {
    if (HEAP_FULL){
        printf("OVERFLOW: HEAP FULL.\nNo se ha anadido el elemento.\n");
    }
    else {
        HEAP[HEAP_END]= new;
        HEAP_END= (HEAP_END + 1) % HEAP_SIZE;
        if (HEAP_END== HEAP_START) HEAP_FULL= 1;
        if (HEAP_EMPTY) HEAP_EMPTY= 0;
    }
}
*/

void push(nodo* new) {
    if (HEAP_FULL){
        printf("OVERFLOW: HEAP FULL.\nNo se ha anadido el elemento.\n");
    }
    else {
        HEAP[HEAP_END]= new;
        HEAP_END= (HEAP_END + 1) % HEAP_SIZE;
        if (HEAP_END== HEAP_START) HEAP_FULL= 1;
        if (HEAP_EMPTY) HEAP_EMPTY= 0;
    }
}

//CONVENIENCE FUNCTIONS CONVENIENCE FUNCTIONS CONVENIENCE FUNCTIONS CONVENIENCE FUNCTIONS 

arista* getArista (nodo* n, int i) {
    //convenience function
    return (n->arrpointer)[i];
}

int sum(arista* a) {
    //control function, used for verifying a node was succesfully created
    return a-> peso + a-> vindex;
}

void printarr(int size, int arr[size]){
    //prints a whole array in order
    int j= 0;
    while(j< size) {
        printf("%d ", arr[j]);
        j++;
    }
    printf("\n");
}

void printedgearr(int size, nodo* n){
    //prints a whole array of edges in order
    int j= 0;
    while(j< size) {
        printf("{%d, %d} ", getArista(n, j)-> vindex, getArista(n, j)-> peso);
        j++;
    }
    printf("\n");
}

void printadylist(int size, nodo** n) {

    printedgearr(n[0]->size, n[0]);    
    
    /*
    int j= 0;
    nodo* node;
    while(j< size) {
        node= n[j];
        printedgearr(node->size, node);
        j++;
    }
    printf("\n");
    */
}

#define PRINT_HEAP printadylist(HEAP_SIZE, HEAP)

void PRINTSTATE(void) {
    //prints the state of the heap
    printf("HEAP STATE:\n   HEAP_SIZE: %d\n   HEAP_START: %d\n   HEAP_END: %d\n   HEAP_FULL: %d\n   HEAP_EMPTY: %d\n", HEAP_SIZE, HEAP_START, HEAP_END, HEAP_FULL, HEAP_EMPTY);
    //PRINT_HEAP;
}

#define PRINTSTATE PRINTSTATE()

void zeroarray(int size, int arr[size]) {
    //turns all array elements to 0
    int i= 0;
    while (i< size) {
        arr[i]= 0;
        i++;
    }
}

void nullarray(int size, nodo* arr[size]) {
    //turns all array elements to NULL
    int i= 0;
    while (i< size) {
        arr[i]= NULL;
        i++;
    }
}

void milarray (int size, int arr[size]) {
    //turns all array elements to NULL
    int i= 0;
    while (i< size) {
        arr[i]= 1000;
        i++;
    }
}
//NODE RANDOMIZER NODE RANDOMIZER NODE RANDOMIZER NODE RANDOMIZER NODE RANDOMIZER 

void nodeRandomizer(int E, int V, nodo* nodelist[V]) {
    //deja en nodelist V nodos conectados por E aristas
    
    int Vleft= V;   //nodos restantes por unir
    int Eleft= E;      //aristas restantes por crear
    
    int Emax= fmin(Eleft - (Vleft - 1), V - 1);
    //El maximo de aristas que puede tener el primer nodo con V = 32 y E = 40 es 9;
    int Emin= fmax(Vleft - (Eleft - 1), 1);
    
    int arr[V];     //almacena aristas a crear
    zeroarray(V, arr);
    
    //printf("arr: \n");
    //printarr(V, arr);
    
    int iterator1= 0;   //cuenta nodos
    int iterator2= 0;   //cuenta aristas
    while (iterator1 < V) {
        printf("iterator1: %d\n", iterator1);
        int conexiones= Emin + rand() % Emax;   //escoge un numero de aristas entre Emin y Emax
        printf("conexiones para el nodo %d: %d\n", iterator1, conexiones);
        while(iterator2< conexiones) {
            //printf("iterator2: %d\n", iterator2);
            int i= rand() % V;    //selecciona un nodo entre 0 y V para una conexion
            
            if (i!= iterator1 && arr[i]== 0) {  //si es valida, propone una arista
                arr[i]= 1 + rand() % 101;
                //printf("peso para la arista %d: %d\n", i, arr[i]);
                iterator2++; 
            }
            
        }
        //printarr(V, arr);
        int creationarray[conexiones*2];
        int i2= 0;
        int creationarrayindex= 0;    //crea variables para inicializar un nodo
        while (i2< V) {  
            if (arr[i2]!= 0) {
                creationarray[creationarrayindex]= i2;
                creationarrayindex++;
                creationarray[creationarrayindex]= arr[i2];
                creationarrayindex++;
                //revisa las aristas por crear y mete los datos a un arreglo
            }
            i2++;
        }
        nodelist[iterator1]= createNodo(iterator1, conexiones, creationarray); //crea un nodo a partir del arreglo de datos de aristas
        printedgearr(conexiones, nodelist[iterator1]);
        zeroarray(V, arr);   //inicializa las variables para ser reutilizadas
        iterator2= 0;
        iterator1++;
        
        Eleft-= conexiones;
        //printf("Eleft %d\n", Eleft);
        Vleft--;
        //printf("Vleft %d\n", Vleft);
        Emax= fmin(Eleft - (Vleft - 1), V-1);
        //printf("Emax %d\n", Emax);
        Emin= fmax(Vleft - (Eleft - 1), 1);
        //printf("Emin %d\n", Emin);
    }
}

//------------------------------------------------------------------------------

int main() {

    srand(time(NULL));    
    
    int V= 32;
    int E= 40;
    
    nodo* nodelist[V];  //almacena los nodos
    
    nodeRandomizer(E, V, nodelist);
    
    nodo* ex= nodelist[10];
    
    printf("\nnodelist ROOT: ");
    printedgearr(ex->size, ex);
    printf("\n");
    
    heap(V, nodelist);
    
    int root= 10;
    int distancias[V];
    nodo* previos[V];
    
//ALG2 ALG2 ALG2 ALG2 ALG2 ALG2 ALG2 ALG2 ALG2 ALG2 ALG2 ALG2 ALG2 ALG2 ALG2 ALG2 
    
    milarray(V, distancias);
    nullarray(V, previos);
    
    distancias[root]= 0;
    
    while(!HEAP_EMPTY) {
        heapifyBy(distancias);
        nodo* min= pop();
        int it= 0;
        arista* conn;
        while (it< (min->size)) {
            conn= getArista(min, it);
            if (distancias[conn->vindex]> distancias[min->pos] + conn-> peso) {
                distancias[conn->vindex]= distancias[min->pos] + conn-> peso;
                previos[conn->vindex]= min;
            }
            it++;
        }
    }
}


//gcc -Wall -g -std=c99 codes2.c -lm -o ejecu 
