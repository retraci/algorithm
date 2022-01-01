#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <bitset>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int dx[9] = {-1, 0, 1, 0, -1, -1, 1, 1, 0};
const int dy[9] = {0, 1, 0, -1, -1, 1, -1, 1, 0};

const int N = 1010;

int n;
int mat[N][N];

void solve() {
    for (int i = 1; i <= n - 1; i++) {
        int k = i;
        for (int j = 1; j <= n - 1; j++) {
            mat[i][j] = k;
            if (++k > n - 1) k = 1;
        }
    }
    for (int i = 1; i <= n - 1; i++) {
        mat[i][n] = mat[n][i] = mat[i][i];
        mat[i][i] = 0;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << mat[i][j] << " ";
        }
        cout << "\n";
    }
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    solve();

    return 0;
}