#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>

using namespace std;

#define ll long long

const int N = 2e5 + 10;
const int W = 10;

ll K;
ll ps[N], cs[N], tt;
int fa[N], cost[N], m;

void div(ll n) {
    tt = 0;
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            ps[++tt] = i, cs[tt] = 0;
            while (n % i == 0) cs[tt]++, n /= i;
        }
    }
    if (n > 1) ps[++tt] = n, cs[tt] = 1;
}

void work(ll p, ll rt) {
    int f = rt;
    while (p--) {
        fa[++m] = f;
        f = m;
    }
}

void dfs(int k, int rt) {
    div(k);
    int is_r = 0;
    if (tt == 1 && ps[1] != 2) {
        is_r = 1;
        div(k - 1);
    }

    vector<ll> va;
    ll cnt = 0;
    for (int i = 1; i <= tt; i++) {
        ll p = ps[i], c = cs[i];

//        cout << p << " " << c << endl;

        while (c--) {
            if (p > W) va.push_back(p);
            else work(p, rt), cnt++;
        }
    }

    if (is_r) cost[rt] = cnt;
    else cost[rt] = cnt + 1;

    for (ll x : va) {
        int son = ++m;
        fa[son] = rt;
        dfs(x, son);
        cost[rt] += cost[son];
    }
}

void solve() {
    if (K == 1) {
        cout << "2\n"
                "1\n"
                "2 1\n";
        return;
    }
    m = 1;
    for (int i = 1; i < N; i++) cost[i] = 1;

    dfs(K, 1);
    cout << m << endl;
    for (int i = 2; i <= m; i++) cout << fa[i] << " ";
    cout << endl;

    for (int i = 1; i <= m; i++) cout << cost[i] << " ";
    cout << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> K;
    solve();

    return 0;
}