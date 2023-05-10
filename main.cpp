#include <fstream>
#include <algorithm>
#include <cstring>
#include <string.h>
#include "BST.h"
#include "oBST.h"
using namespace std;

int main(int argc, char const *argv[])
{
    for (int i = 0; i < 4; i++) {
        // Count num lines in testcase file
        int numElements = 0;
        string line = "";
        ifstream in("testcase"+to_string(i+1)+".txt");
        while(getline(in, line))
            ++numElements;
        in.close();
        //open file and store in array
        char* keys = new char[numElements];
        char* optim_keys = new char[numElements];
        float* probs = new float[numElements];
        float* optim_probs = new float[numElements];
        int idx = 0;
        ifstream in2("testcase"+to_string(i+1)+".txt");
        while(!in2.eof() || in2.peek() != EOF)
        {
            in2 >> ws;
            if(in2.eof() || in2.peek() == EOF)
                break;
            in2 >> keys[idx] >> probs[idx];
            optim_keys[idx] = keys[idx];
            optim_probs[idx] = probs[idx];
            ++idx;
        }
        in2.close();

        cout << "Testcase " << i+1 << ":" << endl;
        // Build Normal Binary Search Tree, Print Tree, and Simulate 1000 nodes following probabilities
        BST *normal_bst = new BST();
        normal_bst->addNodes(keys, numElements);
        normal_bst->printBT(0);
        int numNormalNodes = normal_bst->simulateSearchNodes(keys, probs, numElements);
        cout << "Normal BST number of nodes searched to find 1000 nodes: " << numNormalNodes << endl;
        free(keys);
        free(probs);
        oBST *optimal_bst = new oBST();
        optimal_bst->addNodes(optim_keys, optim_probs, numElements);
        optimal_bst->printBT(0);
        int numOptimalNodes = optimal_bst->simulateSearchNodes(optim_keys, optim_probs, numElements);
        cout << "Optimal BST Number of nodes searched to find 1000 nodes: " << numOptimalNodes << endl;
        cout << endl;
        cout << "********************" << endl;
    }
    return 0;
}
