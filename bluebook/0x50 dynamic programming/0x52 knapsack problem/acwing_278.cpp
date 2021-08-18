#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 110, M = 1e4 + 10;

int n, m;
int va[N];
int f[M];

void solve() {
    memset(f, 0, sizeof f);

    f[0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = m; j >= va[i]; j--) {
            f[j] += f[j - va[i]];
        }
    }

    cout << f[m];
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    cin >> n >> m;
     for (int i = 1; i <= n; i++) {
         cin >> va[i];
     }
     solve();

    return 0;
}