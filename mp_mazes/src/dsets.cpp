/* Your code here! */

#include "dsets.h"


void DisjointSets::addelements(int num) {
    for (int i = 0; i < num; ++i) {
        elements.push_back(-1);
    }
}

int DisjointSets::find (int elem) {
    if (elements[elem] < 0) { 
        return elem;
    } else {
        int root = find(elements[elem]);
        elements[elem] = root;
        return root;
    }
}

void DisjointSets::setunion (int a, int b) {
    
    //
    int roota = find(a);
    int rootb = find(b);

    int sizeA = elements[roota];
    int sizeB = elements[rootb];

    int newSize = sizeB + sizeA;

    if (sizeA <= sizeB) {
        elements[rootb] = roota;
        elements[roota] = newSize; 
    } else {
        elements[roota] = rootb;
        elements[rootb] = newSize;
    }

}

int DisjointSets::size (int elem) {
    return (abs(elements[find(elem)]));
}