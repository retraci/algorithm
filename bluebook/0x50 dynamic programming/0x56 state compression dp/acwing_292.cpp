#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

const int N = 110;

int n, m;
int g[N];

bool check(int mask) {
    for (int i = 0; i < m; i++) {
        if (mask >> i & 1 && (mask >> (i + 1) & 1 || mask >> (i + 2) & 1)) return false;
    }

    return true;
}

void solve() {
    int lim = 1 << m;
    vector<int> state;
    for (int mask = 0; mask < lim; mask++) {
        if (check(mask)) state.push_back(mask);
    }

    int f[2][lim][lim];
    memset(f, 0, sizeof f);
    for (int i = 0; i < n + 2; i++) {
        for (int a = 0; a < state.size(); a++) {
            for (int b = 0; b < state.size(); b++) {
                for (int c = 0; c < state.size(); c++) {
                    int s1 = state[a], s2 = state[b], s3 = state[c];
                    if (g[i] & s1 || s1 & s2 || s1 & s3 || s2 & s3) continue;
                    f[i & 1][s1][s2] = max(f[i & 1][s1][s2], f[i - 1 & 1][s2][s3] + __builtin_popcount(s1));
                }
            }
        }
    }

    cout << f[n + 1 & 1][0][0] << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    cin >> n >> m;
    memset(g, 0, sizeof g);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char ch;
            cin >> ch;
            if (ch == 'H') g[i] |= 1 << j;
        }
    }
    solve();

    return 0;
}