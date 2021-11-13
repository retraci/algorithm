#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

#define ll long long

const ll N = 1e15;

ll n, m;
ll a[100], b[100];
string s[100];

int dfs(ll rem, ll n) {
    if (rem == 1) return 1;
    if (n < 1) return 0;

    ll p = rem;
    while (p % a[n] == 0) b[n]++, p /= a[n];
    for (int i = b[n]; i >= 0; i--) {
        if (dfs(p, n - 1)) return 1;
        b[n]--;
        p *= a[n];
    }
    b[n]++;
    
    return 0;
}

void solve() {
    a[1] = 2, a[2] = 3;
    n = 2;
    while (a[n] < N) {
        n++;
        a[n] = a[n - 1] + a[n - 2];
    }

    for (int i = n; i >= 1; i--) {
        while (m % a[i] == 0) {
            m /= a[i];
            b[i]++;
        }
    }
    if (!dfs(m, n)) {
        cout << "IMPOSSIBLE";
        return;
    }

    s[1] = "A";
    for (int i = 2; i <= n; i++) s[i] = s[i - 1] + 'A';

    for (int i = n; i >= 1; i--) {
        for (int j = 1; j <= b[i]; j++) {
            cout << s[i] << "B";
        }
    }
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);

    cin >> m;
    solve();

    return 0;
}