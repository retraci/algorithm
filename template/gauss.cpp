#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const double eps = 1e-8;

// 普通方程
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

// 异或方程
bitset<1010> matrix[2010];  // matrix[1~n]: 增广矩阵, 0 位置为常数
// n 为方程个数, m 为未知数个数, 返回方程组的解（多解 / 无解返回一个空的 vector）
vector<bool> gauss(int n, int m) {
    for (int i = 1; i <= m; i++) {
        int cur = i;
        while (cur <= n && !mat[cur].test(i)) cur++;
        if (cur > n) return -1;
        if (cur != i) swap(mat[cur], mat[i]);
        for (int j = 1; j <= n; j++) {
            if (i != j && mat[j].test(i)) mat[j] ^= mat[i];
        }
    }
    
    vector<bool> res(n + 1, 0);
    for (int i = 1; i <= n; i++) res[i] = matrix[i].test(0);
    return res;
}