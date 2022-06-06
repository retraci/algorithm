#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

// region 快读
static struct FastInput {
    template<typename T>
    inline FastInput& operator>> (T &x) {
        T ret = 0, sgn = 1;
        char c = getchar();
        while (!isdigit(c)) sgn = (c == '-' ? -1 : 1), c = getchar();
        while (isdigit(c)) ret = (ret << 3) + (ret << 1) + c - '0', c = getchar();
        x = (sgn == -1 ? -ret : ret);
        return *this;
    }
} fin;
// endregion

#define ll long long

const int N = 1e5 + 10;

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

    fin >> n >> K >> x >> p;
    for (int i = 0; i < n; i++) fin >> vs[i];
    for (int i = 0; i < K; i++) fin >> ts[i];
    for (int i = 0; i < K; i++) fin >> ps[i];
    solve();

    return 0;
}