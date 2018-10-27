#ifndef LAB6_H
#define LAB6_H

#include <list>
#include <vector>
#include <iostream>
using namespace std;


template <typename T>
void insert_list(vector<list<T>> &VLI, list<T> L)
{
   VLI.push_back(L);
}


template <typename T>
void print(vector<list<T>> VLI)
{
    // use iterators to print the contents
    typename vector<std::list<T>>::iterator V_it;
    typename list<T>::iterator L_it;
    for (V_it = VLI.begin(); V_it != VLI.end(); V_it++) {
        list<T> L = (*V_it);
        for (L_it = L.begin(); L_it != L.end(); L_it++) {
            T i = (*L_it);
            cout << i << " ";
        }
        cout << std::endl;
    }
}


#endif
