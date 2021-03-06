#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

// 线性基
#define ll long long

const int N = 55;

int n;
ll va[N];
vector<ll> bas;

void insert(ll x) {
    for (auto b: bas) x = min(x, b ^ x);
    for (auto &b: bas) b = min(b, b ^ x);
    if (x) bas.push_back(x);
}

ll query(ll k) {
    ll res = 0;
    if (bas.size() < n) k--;
    for (auto b: bas) {
        if (k & 1) res ^= b;
        k >>= 1;
    }

    if (k == 0) return res;
    else return -1;
}

void init() {
    bas = {};
    for (int i = 1; i <= n; i++) insert(va[i]);
    // 排序
    sort(bas.begin(), bas.end());
}


void solve() {
    init();

    ll ans = 0;
    for (auto b: bas) ans = ans ^ b;
    cout << ans << endl;
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