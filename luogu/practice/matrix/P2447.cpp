#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <bitset>

using namespace std;

const int N = 2010;

int n, m;
string vs[N];
int va[N];
bitset<N> mat[N];
int mx;

void print() {
    for (int i = 1; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// 异或方程
// r 为方程个数, c 为未知数个数, 返回方程组的解（多解 / 无解返回一个空的 vector）
// matrix[1~n]: 增广矩阵, 0 位置为常数
vector<bool> gauss(int r, int c) {
    int row = 1;
    for (int col = 1; col <= c; col++) {
        for (int i = row; i <= r; i++) {
            if (mat[i][col] == 0) continue;
            swap(mat[row], mat[i]);
            mx = max(mx, i);
            break;
        }
        if (mat[row][col] == 0) return vector<bool>(0);

        for (int i = 1; i <= r; i++) {
            if (i != row && mat[i][col]) mat[i] ^= mat[row];
        }
        row++;
    }

    vector<bool> res(r + 1, 0);
    for (int i = 1; i <= r; i++) res[i] = mat[i][0];
    return res;
}

void init() {
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            mat[i][j] = vs[i][j - 1] - '0';
        }
        mat[i][0] = va[i];
    }
}

void solve() {
    init();

    mx = 0;
    vector<bool> res = gauss(m, n);
    if (res.empty()) {
        cout << "Cannot Determine" << endl;
    } else {
        cout << mx << endl;
        for (int j = 1; j <= n; j++) cout << (res[j] == 1 ? "?y7M#" : "Earth") << endl;
    }
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> vs[i] >> va[i];
    }
    solve();

    return 0;
}