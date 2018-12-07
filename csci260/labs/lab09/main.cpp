#include <iostream>
#include <map>
#include <vector>


std::map<char,int> vertexMap;
char* vertexArray;
double** myGraph;
int size;


void insert(char v1, char v2, double weight) {
    myGraph[vertexMap[v1]][vertexMap[v2]] = weight;
    myGraph[vertexMap[v2]][vertexMap[v1]] = weight;
}

double** getDoubleArray() {
    double** myArray = new double*[size];

    for (int i = 0; i < size; ++i) {
        myArray[i] = new double[size];
        for (int j = 0; j < size; ++j) {
            myArray[i][j] = 0;
        }
    }
    return myArray;
}


void initialize() {
    vertexArray = new char[size];
    for (int i = 0; i < size; ++i) {
        vertexMap[(char) i + 'a'] = i;
        vertexArray[i] = (char) i + 'a';
    }

    myGraph = getDoubleArray();

    insert('a', 'b', 7);
    insert('a', 'd', 10);
    insert('a', 'e', 17);
    insert('b', 'c', 8);
    insert('b', 'e', 3);
    insert('b', 'g', 9);
    insert('c', 'd', 6);
    insert('c', 'e', 4);
    insert('c', 'f', 4);
    insert('d', 'f', 5);
    insert('e', 'f', 9);
    insert('e', 'g', 2);
    insert('e', 'i', 15);
    insert('f', 'h', 1);
    insert('g', 'h', 12);
    insert('h', 'i', 5);
}


void printTree(double** tree) {
    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size; ++j) {
            if (tree[i][j] > 0) {
                std::cout << vertexArray[i] << " -> " << std::to_string(tree[i][j])
                          << " -> " << vertexArray[j] << "\n"; 
            }
        }
    }
}


class Edge {
public:
    Edge(int v1, int v2, double weight) 
        : v1(v1)
        , v2(v2)
        , weight(weight)
    {};

    ~Edge()= default;

    bool operator==(const Edge &other) const {
        return weight == other.weight;
    }

    bool operator<=(const Edge &other) const {
        return weight <= other.weight;
    }
    
    int v1;
    int v2;
    double weight;
};


void swap(Edge* a, Edge* b) {
    Edge temp = *a;
    *a = *b;
    *b = temp;
}


// void swap(int a, int b, std::vector<double>* v) {
//     double temp = v[a];
//     v[a] = v[b];
//     v[b] = temp;
// }


int partition(std::vector<Edge> &fArray, int startIndex, int endIndex) {
    Edge pivot = fArray[endIndex];
    int index = startIndex;

    for (int i = startIndex; i < endIndex; ++i) {
        if (fArray[i] <= pivot) {
            swap(&fArray[index], &fArray[i]);
            index++;
        }
    }
    swap(&fArray[index], &fArray[endIndex]);
    return index;
}


void quicksort(std::vector<Edge> &fArray, int startIndex, int endIndex) {
    if (startIndex < endIndex) {
        int index = partition(fArray, startIndex, endIndex);

        quicksort(fArray, startIndex, index - 1);
        quicksort(fArray, index + 1, endIndex);
    }
}


double **MinimumSpanningTree(double **graph, int numOfNodes) {
    std::vector<Edge> edgeList;

    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size; ++j) {
            if (graph[i][j] > 0) {
                edgeList.emplace_back(i, j, graph[i][j]);
            }
        }
    }

    quicksort(edgeList, 0, (int) edgeList.size() - 1);

    auto tree = getDoubleArray();

    for (std::vector<Edge>::iterator i = edgeList.begin(); i != edgeList.end(); ++i) {
        if (/* needs to check for cycles */) {
            tree[i->v1][i->v2] = i->weight;
        }
    }

    return tree;
}


int main() {
    size = 9;
    initialize();

    printTree(myGraph);

    std::cout << "\n\n\n";

    printTree(MinimumSpanningTree(myGraph, size));


    return 0;
}