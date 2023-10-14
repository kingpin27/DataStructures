#include <iostream>
#include <vector>
#include <cassert>
#define SIZE 32

using namespace std;

class Fenwick_tree {
private:
    vector<int> store;
    int size;

    int getAccumulationScope(int i) {
        return ~i & (i+1);
    }
public:
    Fenwick_tree(int _size) {
        size = _size;
        store.resize(size, 0);
    }
    void insert(int i, int v) {
        assert(i<size);

        store[i] += v;
        for(int j=0; j<32; j++) {
            if(1<<j >= size) break;
            if(!(i>>j & 1)) {
                i |= 1<<j;
                store[i] += v;
            }
        }   
    }
    int getSum(int i) {
        assert(i<size);

        int sum = 0;
        while (i>0) {
            sum += store[i];
            i -= getAccumulationScope(i);
        }
        return sum;
    }
    void resetStore(int n) {
        store.resize(n, 0);
    }
};


int main() {
    Fenwick_tree *ft = new Fenwick_tree(SIZE);

    //test 1
    cout<<"running test 1...\n";
    ft->insert(0,10);
    ft->insert(2,10);
    ft->insert(3,10);

    if (ft->getSum(4) == 30) cout<<"passed!!\n\n";
    else cout<<"failed!!\n\n";

    return 0;
}