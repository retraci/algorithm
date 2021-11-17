#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

#define ll long long

const int N = 1e5 + 10;

template<typename T> inline void rd(T& x){
    T ret = 0, sgn = 1;
    char c = getchar();
    while(!isdigit(c)) sgn = (c == '-' ? -1 : 1), c = getchar();
    while(isdigit(c)) ret = (ret << 3) + (ret << 1) + c - '0', c = getchar();
    x = (sgn == -1 ? -ret : ret);
}

ll n, K, x, p;
ll vs[N];
ll ts[N], ps[N];
ll va[N];

void solve() {
    for (int i = 0; i < K; i++) va[i] = ps[i] - ts[i];
    va[n] = p;
    ll mx = *max_element(va, va + n + 1);

    int ans = 0;
    for (int i = 0; i < n; i++) {
        ll need = ((x + vs[i] - 1) / vs[i]);
        ans += need <= mx;
    }

    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    rd(n); rd(K); rd(x); rd(p);
    for (int i = 0; i < n; i++) rd(vs[i]);
    for (int i = 0; i < K; i++) rd(ts[i]);
    for (int i = 0; i < K; i++) rd(ps[i]);
    solve();

    return 0;
}