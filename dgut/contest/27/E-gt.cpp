#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int N = 5e3 + 10;

int n, m;
ll va[N];
ll f[N][N];

void solve() {
    for (int len = 2; len <= n; len++) {
        for (int L = 1; L + len - 1 <= n; L++) {
            int R = L + len - 1;
            f[L][R] = max({f[L + 1][R], f[L][R - 1], va[L] ^ va[R]});
        }
    }

    while (m--) {
        int L, R;
        cin >> L >> R;
        cout << f[L][R] << endl;
    }
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> va[i];
    solve();

    return 0;
}