#include <iostream>
#include <string>
using namespace std;

class oBST {
    public:
        oBST() {
            left = nullptr;
            right = nullptr;
            val = 0;
        }
        ~oBST();
        oBST *left;
        oBST *right;
        char val;
        void sort_keys(int n, char* key, float* prob);
        void optimize(int n, char* key, float* prob, char* optimized_order);
        void addNode(char key);
        void addNodes(char* key, float* prob, int n);
        int simulateSearchNode(char key);
        int simulateSearchNodes(char* key, float* prob, int n);
        void printBT(int spacing);
};