#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 310;
int n;
int va[N][N];
int vis[N];

void solve() {
    memset(vis, 0, sizeof vis);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!vis[va[i][j]]) {
                cout << va[i][j] << " ";
                vis[va[i][j]] = 1;
                break;
            }
        }
    }
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &va[i][j]);
        }
    }
    solve();

    return 0;
}