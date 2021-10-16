#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const double eps = 1e-8;

int gauss(int n, int m) {
    int row = 1;
    for (int col = 1; col <= n; col++) {
        for (int i = row; i <= n; i++) {
            if (fabs(mat[i][col]) > eps) {
                for (int j = col; j <= m; j++) swap(mat[i][j], mat[row][j]);
            }
        }
        if (fabs(mat[row][col]) < eps) break;

        for (int j = m; j >= col; j--) mat[row][j] /= mat[row][col];
        for (int i = 1; i <= n; i++) {
            if (i != row) {
                for (int j = m; j >= col; j--) {
                    mat[i][j] -= mat[i][col] * mat[row][j];
                }
            }
        }
        row++;
    }

    for (int i = 1; i <= n; i++) {
        if (fabs(mat[i][i]) < eps) return -1;
        res[i] = mat[i][m] /= mat[i][i];
        if (floor(res[i]) != res[i]) return -1;
    }
    return 1;
}