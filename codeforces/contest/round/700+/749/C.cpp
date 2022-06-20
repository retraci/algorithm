#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 1e6 + 10;

int n, m;
char mp[N];
int s[N];

int get_idx(int i, int j) {
    return (i - 1) * m + j;
}

void init() {
    for (int j = 1; j <= m; j++) s[j] = 0;

    for (int i = 2; i <= n; i++) {
        for (int j = 2; j <= m; j++) {
            if (mp[get_idx(i - 1, j)] == 'X' && mp[get_idx(i, j - 1)] == 'X') s[j] = 1;
        }
    }

    for (int j = 2; j <= m; j++) s[j] += s[j - 1];
}

void solve() {
    init();

    int Q;
    cin >> Q;
    while (Q--) {
        int a, b;
        cin >> a >> b;
        cout << (s[b] - s[a] == 0 ? "YES" : "NO") << endl;
    }
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> mp[get_idx(i, j)];
        }
    }
    solve();

    return 0;
}