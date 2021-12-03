#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int dx[9] = {0, 0, -1, 1, -1, -1, 1, 1, 0};
const int dy[9] = {-1, 1, 0, 0, -1, 1, -1, 1, 0};

const int N = 2e5 + 10;
const ll MOD = 998244353;

int n;
ll va[N];
ll s[N];
ll f[N];
unordered_map<ll, ll> mp;

void solve() {
    for (int i = 1; i <= n; i++) s[i] = s[i - 1] + va[i];

    f[0] = 1;
    ll sum = 1;
    for (int i = 1; i <= n; i++) {
        f[i] = sum;
        sum = (sum * 2) % MOD;
        sum = (sum - mp[s[i]] + MOD) % MOD;
        mp[s[i]] = f[i];
    }

    cout << f[n] << "\n";
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> va[i];
    solve();

    return 0;
}