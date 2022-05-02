#include<iostream>
#include<cstring>
#include<algorithm>
#include<bitset>

using namespace std;
typedef long long LL;
typedef pair<int, int> PII;
const int mod = 998244353;
int f[1 << 10];
#define x first
#define y second
int xs[25], ys[25];
int cntx, cnty;
bitset<500> mask[10], state;
int n, w, h, k;
int inv[30];

int qpow(int a, int b, int mod) {
    int res = 1;
    while (b) {
        if (b & 1) res = 1LL * res * a % mod;
        b >>= 1;
        a = 1LL * a * a % mod;
    }
    return res;
}

struct Rect {
    PII a, b;
} r[15];

void dfs(int u, int s) {
    if (u == n) {
        f[s] = (state.count() == k) ? 0 : -1;
        return;
    }
    bitset<500> bk = state;
    dfs(u + 1, s);
    state = bk;
    state |= mask[u];
    dfs(u + 1, s | (1 << u));
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    for (int i = 1; i < 20; i++) inv[i] = qpow(i, mod - 2, mod);
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &n, &w, &h);
        cntx = cnty = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d%d%d%d", &r[i].a.x, &r[i].a.y, &r[i].b.x, &r[i].b.y);
            if (r[i].a.x > w) r[i].a.x = w;
            if (r[i].b.x > w) r[i].b.x = w;
            if (r[i].a.y > h) r[i].a.y = h;
            if (r[i].b.y > h) r[i].b.y = h;
            xs[++cntx] = r[i].a.x;
            xs[++cntx] = r[i].b.x;
            ys[++cnty] = r[i].a.y;
            ys[++cnty] = r[i].b.y;
        }
        sort(xs + 1, xs + cntx + 1);
        sort(ys + 1, ys + cnty + 1);
        cntx = unique(xs + 1, xs + cntx + 1) - (xs + 1);
        cnty = unique(ys + 1, ys + cnty + 1) - (ys + 1);
        k = (cntx - 1) * (cnty - 1);
        bitset<500> t;
        for (int i = 0; i < n; i++) {
            r[i].a.x = lower_bound(xs + 1, xs + cntx + 1, r[i].a.x) - xs;
            r[i].a.y = lower_bound(ys + 1, ys + cnty + 1, r[i].a.y) - ys;
            r[i].b.x = lower_bound(xs + 1, xs + cntx + 1, r[i].b.x) - xs;
            r[i].b.y = lower_bound(ys + 1, ys + cnty + 1, r[i].b.y) - ys;
            mask[i].reset();
            t.reset();
            t = (1 << (r[i].b.y - r[i].a.y)) - 1;
            t <<= r[i].a.y - 1;
            for (int j = r[i].a.x - 1; j < r[i].b.x - 1; j++)
                mask[i] |= (t << (j * (cnty - 1)));
        }
        state.reset();
        dfs(0, 0);
        if (f[(1 << n) - 1] == -1) {
            puts("-1");
            continue;
        }
        int p = inv[n];
        for (int i = (1 << n) - 1; i >= 0; i--) {
            if (f[i] != -1) continue;
            int cnt = 0;
            int res = 0;
            for (int j = 0; j < n; j++) {
                if (i >> j & 1) cnt++;
                else res = (res + 1LL * p * f[i | (1 << j)]) % mod;
            }
            f[i] = (1LL + res) * n % mod * inv[n - cnt] % mod;
        }
        for (int mask = 0; mask < 1 << n; mask++) {
            if (f[mask] == 0) cout << bitset<8>(mask) << "\n";
        }

        printf("%d\n", f[0]);
    }
}