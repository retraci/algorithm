#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <unordered_map>
#include <vector>

using namespace std;

#define ll long long

typedef pair<ll, ll> pll;

const int N = 5010;
const ll MOD = 998244353;

int n;
int va[N];
ll f[N][N];
unordered_map<ll, ll> mp;
vector<pll> vb;
ll fac[N];

ll dfs(ll c1, ll c2, int cur) {
    if (c1 == n / 2 && c2 == n / 2) return 1;
    if (c1 > n / 2 || c2 > n / 2) return 0;
    if (f[c1][c2]) return f[c1][c2];

    int cnt = mp[cur];
    for (int i = 0; i <= cnt; i++) {
        int j = cnt - i;
        if (c1 + i >= c2 + j) f[c1][c2] = (f[c1][c2] + dfs(c1 + i, c2 + j, cur + 1)) % MOD;
    }

    return f[c1][c2] = f[c1][c2] * fac[cnt] % MOD;
}

void solve() {
    for (int i = 1; i <= n; i++) mp[va[i]]++;
    for (auto &vk : mp) vb.push_back(vk);
    fac[0] = 1;
    for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % MOD;

    memset(f, 0, sizeof f);
    cout << dfs(0, 0, 0) << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> va[i];
    }
    solve();

    return 0;
}