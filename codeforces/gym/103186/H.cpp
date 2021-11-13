#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

#define ll long long

struct Car {
    ll p, v, t;
};

typedef pair<ll, ll> pll;

const int N = 1e5 + 10;

int n, K;
Car cs[N];
int L[N], R[N];

bool check(ll x) {
    vector<pll> va;
    for (int i = 0; i < n; i++) {
        auto &[p, v, t] = cs[i];
        ll np = p + v * x;
        va.push_back({np, i});
    }
    sort(va.begin(), va.end());

    // 判位置相同
    for (int i = 1; i < n; i++) {
        auto &[p1, id1] = va[i];
        auto &[p2, id2] = va[i - 1];
        if (p1 == p2 && cs[id1].t != cs[id2].t) return true;
    }
    // 判相对位置
    for (int i = 0; i < n; i++) {
        auto &[p1, id1] = va[i];
        if (i < L[id1] || i > R[id1]) return true;
    }

    return false;
}

void solve() {
    sort(cs, cs + n, [&](auto &a, auto &b) {
        return a.p < b.p;
    });
    L[0] = 0;
    for (int i = 1; i < n; i++) {
        if (cs[i].t == cs[i - 1].t) L[i] = L[i - 1];
        else L[i] = i;
    }
    R[n - 1] = n - 1;
    for (int i = n - 2; i >= 0; i--) {
        if (cs[i].t == cs[i + 1].t) R[i] = R[i + 1];
        else R[i] = i;
    }

    ll left = 0, right = 1e10;
    while (left < right) {
        ll mid = left + right >> 1;
        if (check(mid)) right = mid;
        else left = mid + 1;
    }

    cout << (left == 1e10 ? -1 : left - 1) << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(false);
    cin >> n >> K;
    for (int i = 0; i < n; i++) {
        ll a, b, c;
        cin >> a >> b >> c;
        cs[i] = {a, b, c};
    }
    solve();

    return 0;
}