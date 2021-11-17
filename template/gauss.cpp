#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

/*----------------------------------------*/

#define ld long double

const ld eps = 1e-8;

// 普通方程
// r 为方程数, c 为未知数数目
int gauss(int r, int c) {
    int row = 1;
    for (int col = 1; col <= c; col++) {
        for (int i = row; i <= r; i++) {
            if (fabs(mat[i][col]) > eps) {
                for (int j = col; j <= c + 1; j++) swap(mat[i][j], mat[row][j]);
            }
        }
        if (fabs(mat[row][col]) < eps) break;

        for (int i = 1; i <= r; i++) {
            if (i != row && fabs(mat[i][col]) > eps) {
                ld rate = mat[i][col] / mat[row][col];
                for (int j = c + 1; j >= col; j--) {
                    mat[i][j] -= mat[row][j] * rate;
                }
            }
        }
        row++;
    }

    for (int i = 1; i <= c; i++) {
        if (fabs(mat[i][i]) < eps) return -1;
        res[i] = mat[i][c + 1] /= mat[i][i];
        if (floor(res[i]) != res[i]) return -1;
    }
    return 1;
}

// 异或方程
// r 为方程个数, c 为未知数个数, 返回方程组的解（多解 / 无解返回一个空的 vector）
// matrix[1~n]: 增广矩阵, 0 位置为常数
bitset<N> mat[N];

vector<bool> gauss(int r, int c) {
    int row = 1;
    for (int col = 1; col <= c; col++) {
        for (int i = row; i <= r; i++) {
            if (mat[i][col] == 0) continue;
            swap(mat[row], mat[i]);
        }
        if (mat[row][col] == 0) continue;

        for (int i = 1; i <= r; i++) {
            if (i != row && mat[i][col]) mat[i] ^= mat[row];
        }
        row++;
    }

    vector<bool> res(r + 1, 0);
    for (int i = 1; i <= r; i++) res[i] = mat[i][0];
    return res;
}