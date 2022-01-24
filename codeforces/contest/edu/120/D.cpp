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

const ll MOD = 998244353;
const int N = 5010;

ll n, K;
string str;

// region comb
ll fac[N], ifac[N];

inline ll ksm(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

inline ll inv(ll x) {
    return ksm(x, MOD - 2);
}

inline ll C(ll a, ll b) {
    if (a < 0 || b < 0 || a - b < 0) return 0;
    return fac[a] * ifac[b] % MOD * ifac[a - b] % MOD;
}

inline void init_comb(int lim) {
    fac[0] = ifac[0] = 1;
    for (int i = 1; i <= lim; i++) fac[i] = fac[i - 1] * i % MOD, ifac[i] = inv(fac[i]);
}
// endregion

void solve() {
    if (K == 0) {
        cout << 1 << "\n";
        return;
    }

    init_comb(n);

    vector<int> va;
    va.push_back(-1);
    for (int i = 0; i < n; i++) {
        if (str[i] == '1') va.push_back(i);
    }
    va.push_back(n);

    ll ans = 1;
    for (int i = K; i < va.size() - 1; i++) {
        ll left = i - K + 1, right = i;
        ll lb = va[left - 1] + 1, rb = va[right + 1] - 1;
        ll len = rb - lb + 1;

        ans += C(len, K) - 1;
        if (i != K) ans -= C(va[right] - 1 - lb + 1, K - 1) - 1;
        ans %= MOD;
    }

    ans = (ans + MOD) % MOD;
    cout << ans << "\n";
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> K;
    cin >> str;
    solve();

    return 0;
}