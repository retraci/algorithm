#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <vector>

using namespace std;

#define ll long long

const int N = 10010;

int n, ca;
ll va[N];
vector<ll> B;

void insert(ll x) {
    for (auto b: B) x = min(x, b ^ x);
    for (auto &b: B) b = min(b, b ^ x);
    if (x) B.push_back(x);
}

ll query(ll k) {
    ll res = 0;
    if (B.size() < n) k--;
    for (auto b: B) {
        if (k & 1) res ^= b;
        k >>= 1;
    }

    if (k == 0) return res;
    else return -1;
}


void solve() {
    B = {};
    for (int i = 1; i <= n; i++) insert(va[i]);
    sort(B.begin(), B.end());

    cout << "Case #" + to_string(++ca) + ":" << endl;
    int q;
    cin >> q;
    while (q--) {
        ll k;
        cin >> k;
        cout << query(k) << endl;
    }
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> va[i];
        solve();
    }

    return 0;
}