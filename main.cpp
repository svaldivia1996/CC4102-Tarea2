#include <bits/stdc++.h>
using namespace std;

//#define USE_SOLUTION_PRINT

void printSolution(vector<int> &dist)
{
    printf("Vertex \t\t Distance from Source\n");
    for (int i = 0; i < dist.size(); i++)
        printf("%d \t\t %d\n", i, dist[i]);
}

int minDistance(vector<int> dist, vector<bool> visited)
{

    int min = INT_MAX, min_index;

    for (int v = 0; v < dist.size(); v++)
        if (visited[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

vector<int> DijskstraSlow(int n, vector<pair<int, int>> *graph, int source)
{
    vector<int> dist(n, INT_MAX);   // array distancias
    vector<bool> visited(n, false); // array visitedios
    dist[source] = 0;               // siempre la distancia a si mismo es 0

    for (int node = 0; node < n; node++)
    {
        int minIndex = minDistance(dist, visited);

        visited[minIndex] = true;
        // node = minIndex;
        int nodeaux = minIndex;

        int v;
        int w;
        // cout << "Node " << node << " makes an edge with \n";
        // para la recursion del sobre la lista https://www.geeksforgeeks.org/graph-implementation-using-stl-for-competitive-programming-set-2-weighted-graph/
        for (auto it = graph[nodeaux].begin(); it != graph[nodeaux].end(); it++)
        {
            v = it->first;
            w = it->second;
            if (!visited[v] and w > 0 and
                dist[minIndex] + w < dist[v])
            {
                // dist[node] = dist[minIndex] + graph[minIndex][node].second;
                dist[v] = dist[minIndex] + w;
            }
        }
    }

#ifdef USE_SOLUTION_PRINT
    printSolution(dist);
#endif

    return dist;
}

vector<int> DijkstraHeap(int n, vector<pair<int, int>> *graph, int source)
{

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> distTo(n, INT_MAX);
    distTo[source] = 0;
    pq.push(make_pair(0, source));
    while (!pq.empty())
    {
        int dist = pq.top().first;
        int prev = pq.top().second;
        pq.pop();
        vector<pair<int, int>>::iterator it;
        for (it = graph[prev].begin(); it != graph[prev].end(); it++)
        {
            int v = it->first;
            int w = it->second;
            if (distTo[v] > distTo[prev] + w)
            {
                distTo[v] = distTo[prev] + w;
                pq.push(make_pair(distTo[v], v));
            }
        }
    }
#ifdef USE_SOLUTION_PRINT
    printSolution(distTo);
#endif
    return distTo;
}

// promedio
double mean(vector<int> &nums, size_t size)
{
    double sum{};
    for (int i{}; i < size; i++)
    {
        sum += nums[i];
    }
    return sum / size;
}

// desviación estándar
double stdev(vector<int> &nums, size_t size)
{
    double mu{mean(nums, size)};
    double sigma{};
    for (int i{}; i < size; i++)
    {
        double prod{nums[i] - mu};
        sigma += (prod * prod);
    }
    return sqrt(sigma / size);
}

int main()
{

    cout << "Ingrese la cantidad de test seguido de la cantidad de nodos probar " << endl;
    int n, nodos;
    cin >> n >> nodos;

    // Ejemplos individuales
    int ntest1 = 5;                                // cant de nodos
    vector<pair<int, int>> graphTest1[ntest1 + 1]; // inic del lista de adj
    graphTest1[0].push_back({1, 2});               // el nodo 0 tiene se dirige al nodo 1 con un peso 2
    graphTest1[0].push_back({3, 1});
    graphTest1[1].push_back({0, 2});
    graphTest1[1].push_back({4, 5});
    graphTest1[1].push_back({2, 4});
    graphTest1[2].push_back({1, 4});
    graphTest1[2].push_back({3, 3});
    graphTest1[2].push_back({4, 1});
    graphTest1[3].push_back({0, 1});
    graphTest1[3].push_back({2, 3});
    graphTest1[4].push_back({1, 5});
    graphTest1[4].push_back({2, 1});

    auto inicio = chrono::steady_clock::now();
    DijskstraSlow(ntest1, graphTest1, 0);
    auto fin = chrono::steady_clock::now();
    double duracion = chrono::duration_cast<chrono::microseconds>(fin - inicio).count();
    cout << "Me demore con el algoritmo con listas de adyacencia: " << duracion << " microsegundos" << endl;

    auto inicio2 = chrono::steady_clock::now();
    DijkstraHeap(ntest1, graphTest1, 0);
    auto fin2 = chrono::steady_clock::now();
    double duracion2 = chrono::duration_cast<chrono::microseconds>(fin2 - inicio2).count();
    cout << "Me demore con el algoritmo con Heap: " << duracion2 << " microsegundos" << endl;



    // crear vector de resultados
    vector<int> resultadosNaive{ };
    vector<int> resultadosHeap{ };
    int testCompletos{ };

    string header{ "cant_nodos,n_tests,t_naive[μs],t_heap[μs],t_fibonacci[μs]" };

    // guardar resultados en un txt
    string filename{ "time_results.csv" };

    // crear archivo y 
    ifstream f(filename.c_str());
    bool existe{f.good()};

    if(!existe)
    {
        std::ofstream outfile;
        outfile.open (filename);
        // colocar header si no existe
        outfile << header << '\n';
        outfile.close();
    }
    else
    {
        string firstLine;
        getline(f, firstLine);
        // fix outdated headers
        if(firstLine != header)
        {
            std::ofstream outfile;
            outfile.open (filename);
            outfile << header << '\n';
            outfile << f.rdbuf();
            outfile.close();
        }

    }

    f.close();

    std::ofstream outfile;
    // modo append
    outfile.open (filename, std::ios::app);

    //generacion de tests aleatorios
    while (n--)
    {
        vector<pair<int, int>> graph[nodos + 1];
        vector<int> aux(nodos);
        for (int i = 0; i < nodos; i++)
        {
            aux[i] = i;
        }
        shuffle(aux.begin(), aux.end(), default_random_engine());

        // pritn para cachar las conecciones
        /*for(int i=0;i<nodos;i++){
            cout << aux[i] <<endl;
        }*/

        for (int i = 0; i < nodos; i++)
        {
            int inic = aux[i];
            int dest = aux[(i + 1) % nodos]; // nodo destino1
            int w1 = rand() % 100;           // peso ida
            int w2 = rand() % 100;           // peso vuelta
            graph[inic].push_back({dest, w1});
            graph[dest].push_back({inic, w2});
        }
        auto inicio = chrono::steady_clock::now();
        DijskstraSlow(nodos, graph, 0);
        auto fin = chrono::steady_clock::now();
        double duracion = chrono::duration_cast<chrono::microseconds>(fin - inicio).count();
        cout << "Me demore con el algoritmo con listas de adyacencia: " << duracion << " microsegundos" << endl;

        auto inicio2 = chrono::steady_clock::now();
        DijkstraHeap(nodos, graph, 0);
        auto fin2 = chrono::steady_clock::now();
        double duracion2 = chrono::duration_cast<chrono::microseconds>(fin2 - inicio2).count();
        cout << "Me demore con el algoritmo con Heap: " << duracion2 << " microsegundos" << endl;

        resultadosNaive.push_back(duracion);
        resultadosHeap.push_back(duracion2);
        //resultadosBloque.push_back(duracion3);

        testCompletos++;    
        
    }

    if(testCompletos == 0)
    {
        cout << "No lograron hacerse tests :(\n";
        outfile.close();
        exit (EXIT_FAILURE);
    }
    

    // calcular promedios
    double promNaive{ mean(resultadosNaive, testCompletos) };
    double promHeap{ mean(resultadosHeap, testCompletos) };
    //double promBloque{ mean(resultadosBloque, testCompletos) };

    // calcular desviaciones estándar

    double stdevDinamico{ stdev(resultadosNaive, testCompletos) };
    double stdevCache{ stdev(resultadosHeap, testCompletos) }; 
    //double stdevBloque{ stdev(resultadosBloque, testCompletos) };

    
    cout <<"\nRESULTADOS FINALES" << "\n\n" << "Número de tests exitosos: " << testCompletos 
    << "\nTiempo[ms] para Algoritmo Naive -\tprom: " << promNaive << " ;\tdevst: " << stdevDinamico
    << "\nTiempo[ms] para Algoritmo Heap -\tprom: " << promHeap << " ;\tdevst: " << stdevCache << '\n';

    
    
    // fila del csv con los tiempos
    outfile << nodos 
            << ',' << testCompletos 
            << ',' << promNaive 
            << ',' << promHeap << '\n';
    // cerrar archivo de tests
    outfile.close();


    return 0;
}