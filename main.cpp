#include <vector>
#include <iostream>
using namespace std;

class MyUF {
private:
    vector<int> ufVec;
    vector<bool> openStateVec;
    int n;

public:
    MyUF(int n) : n(n) {
        ufVec.resize(n * n);
        openStateVec.resize(n * n, false);
        for (int i = 0; i < n * n; i++) {
            ufVec[i] = i;
        }
    }

    int transformToOneD(int row, int col) {
        return (row - 1) * n + (col - 1);
    }

    bool percolates() {
        for (int i = 0; i < n; i++) {
            int top = find(transformToOneD(1, i + 1));
            for (int j = 0; j < n; j++) {
                int bottom = find(transformToOneD(n, j + 1));
                if (top == bottom) {
                    return true;
                }
            }
        }
        return false;
    }

    void merge(int p, int q) {
        int pRoot = find(p);
        int qRoot = find(q);
        if (pRoot != qRoot) {
            ufVec[pRoot] = qRoot;
        }
    }

    int find(int p) {
        while (p != ufVec[p]) {
            ufVec[p] = ufVec[ufVec[p]];  // Path compression
            p = ufVec[p];
        }
        return p;
    }

    void setOpen(int row, int col) {
        int idx = transformToOneD(row, col);
        openStateVec[idx] = true;
        // Check top
        if (row > 1 && openStateVec[idx - n]) {
            merge(idx, idx - n);
        }
        // Check bottom
        if (row < n && openStateVec[idx + n]) {
            merge(idx, idx + n);
        }
        // Check left
        if (col > 1 && openStateVec[idx - 1]) {
            merge(idx, idx - 1);
        }
        // Check right
        if (col < n && openStateVec[idx + 1]) {
            merge(idx, idx + 1);
        }
    }
};

int main() {
    int n = 5;
    MyUF uf(n);


    uf.setOpen(1, 1);
    uf.setOpen(2, 1);
    uf.setOpen(3, 1);
    uf.setOpen(4, 1);
    uf.setOpen(5, 1);

    if (uf.percolates()) {
        cout << "The system percolates." << endl;
    } else {
        cout << "The system does not percolate." << endl;
    }

    return 0;
}
