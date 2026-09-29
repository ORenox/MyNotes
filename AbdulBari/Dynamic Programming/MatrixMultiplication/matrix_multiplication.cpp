#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> rectangular_matrix_multiply(
    const vector<vector<int>>& a,
    const vector<vector<int>>& b,
    vector<vector<int>>& c
) {
    int p = a.size();
    int q = a[0].size();
    int r = b[0].size();

    for (int i = 0; i < p; i++) {
        for (int j = 0; j < r; j++) {
            for (int k = 0; k < q; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    return c;
}

int main() {

    // A = 2x3
    vector<vector<int>> a = {
        {1, 2, 3},
        {4, 5, 6}
    };

    // B = 3x2
    vector<vector<int>> b = {
        {7, 8},
        {9, 10},
        {11, 12}
    };

    // C = 2x2
    vector<vector<int>> c(2, vector<int>(2, 0));

    c = rectangular_matrix_multiply(a, b, c);

    cout << "Matriz C:" << endl;

    for (const auto& fila : c) {
        for (int elemento : fila) {
            cout << elemento << " | ";
        }
        cout << endl;
    }

    return 0;
}