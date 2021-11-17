#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

#define ll long long

const int INF = 0x3f3f3f;
const int N = 1e6 + 10;

int n;
int va[N];
int f[N];
int ans[N];

template<typename T> inline void rd(T& x){
    T ret = 0, sgn = 1;
    char c = getchar();
    while(!isdigit(c)) sgn = (c == '-' ? -1 : 1), c = getchar();
    while(isdigit(c)) ret = (ret << 3) + (ret << 1) + c - '0', c = getchar();
    x = (sgn == -1 ? -ret : ret);
}

void solve() {
    // reverse(va, va + n);

    // memset(f, 0x3f, sizeof f);
    for(int i = 0; i <= n; i ++) f[i] = INF;
    for (int i  = 0; i < n; i++) {
        auto ptr = lower_bound(f, f + n, va[i]);
        ans[i] = ptr - f;
        *ptr = va[i];
    }

    printf("%d\n", lower_bound(f, f + n, INF) - f);
    for (int i = 0; i < n; i++) {
        printf("%d ", ans[i] + 1);
    }
    printf("\n");
    return ;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    int T;
    rd(T);
    while (T--) {
        rd(n);
        for (int i = 0; i < n; i++) {
            rd(va[i]);
            va[i] = n - va[i];
        }
        solve();
    }

    return 0;
}