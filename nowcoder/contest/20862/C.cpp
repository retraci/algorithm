#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

const int N = 20;
const double eps = 1e-8;

int n;
double a, b, d;
double mat[N][N], res[N];

void print() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

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

//    print();

    for (int i = 1; i <= 6; i++) {
        if (fabs(mat[i][i]) < eps) return -1;
        res[i] = mat[i][m] /= mat[i][i];
        if (floor(res[i]) != res[i]) return -1;
    }
    return 1;
}

void init() {
    n = 8;
    memset(mat, 0, sizeof mat);
    mat[1][7] = 1, mat[1][1] = 1, mat[1][8] = -a + -b;
    mat[2][7] = 1, mat[2][2] = 1, mat[2][3] = 1, mat[2][8] = -d;
    mat[3][7] = 1, mat[3][4] = 1, mat[3][5] = 1, mat[3][6] = 1, mat[3][8] = 0;
    mat[4][7] = 1, mat[4][4] = 1, mat[4][8] = -a + -d;
    mat[5][7] = 1, mat[5][2] = 1, mat[5][5] = 1, mat[5][8] = -b;
    mat[6][7] = 1, mat[6][1] = 1, mat[6][3] = 1, mat[6][6] = 1, mat[6][8] = 0;
    mat[7][7] = 1, mat[7][2] = 1, mat[7][6] = 1, mat[7][8] = -a;
    mat[8][7] = 1, mat[8][1] = 1, mat[8][2] = 1, mat[8][4] = 1, mat[8][8] = 0;
//    mat[7][7] = 2, mat[7][1] = 1, mat[7][2] = 2, mat[7][4] = 1, mat[7][6] = 1, mat[7][8] = -a;
}

void solve() {
    init();

    if (gauss(n, n) == -1) {
        cout << -1;
    } else {
        for (int i = 1; i <= 6; i++) {
            printf("%d ", (int) res[i]);
        }
    }
    cout << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    int T;
    cin >> T;
    while (T--) {
        cin >> a >> b >> d;
        solve();
    }

    return 0;
}