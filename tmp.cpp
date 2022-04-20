#include<iostream>
#include<cstring>
#include<set>

using namespace std;
typedef long long LL;
const int maxn = 1e6 + 5;
const LL INF = 0x3f3f3f3f3f3f3f3f;
struct Node {
    int l, r, sum;
} tr[maxn * 4];
LL f[maxn][2];
int a[maxn], p[maxn], L[maxn], R[maxn];
int n, k;

void pushup(int u) {
    tr[u].sum = tr[u << 1].sum + tr[u << 1 | 1].sum;
}

void build(int u, int l, int r) {
    tr[u] = {l, r, 0};
    if (l == r) return;
    int mid = l + r >> 1;
    build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
}

void modify(int u, int x, int v) {
    if (tr[u].l == tr[u].r) {
        tr[u].sum += v;
        return;
    }
    int mid = tr[u].l + tr[u].r >> 1;
    if (x <= mid) modify(u << 1, x, v);
    else modify(u << 1 | 1, x, v);
    pushup(u);
}

int query(int u, int x) {
    if (!tr[u].sum && x <= tr[u].l) return tr[u].l;
    if (tr[u].l == tr[u].r) return -1;
    int mid = tr[u].l + tr[u].r >> 1;
    if (mid < x) return query(u << 1 | 1, x);
    int res = query(u << 1, x);
    if (res == -1) return query(u << 1 | 1, x);
    return res;
}

int get(int a, int b) {
    return min(abs(a - b), n - abs(a - b));
}

int mov(int i, int j) {
    return ((i - 1 + j) % n + n) % n + 1;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &k);
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
            p[a[i]] = i;
            f[i][0] = f[i][1] = INF;
        }
        build(1, 1, n);
        for (int i = 1; i <= k; i++) modify(1, a[i], 1);
        int t = query(1, 0);
        LL ans = INF;
        L[1] = query(1, a[1]);
        R[k] = query(1, a[k]);
        for (int i = 2; i <= n; i++) {
            modify(1, a[i - 1], -1);
            modify(1, a[(i + k - 2) % n + 1], 1);
            L[i] = query(1, a[i]);
            R[(i + k - 2) % n + 1] = query(1, a[(i + k - 2) % n + 1]);
        }
        if (t == -1) {
            puts("0");
            continue;
        }
        f[t][0] = get(1, p[t]);
        f[t][1] = get(k, p[t]);
        for (int i = t; i <= n; i++) {
            {
                int v = L[p[i]];
                if (v == -1) {
                    ans = min(ans, f[i][0]);
                } else {
                    int id1 = p[i], id2 = p[v];
                    f[v][0] = min(f[v][0], f[i][0] + get(id2, id1));
                    f[v][1] = min(f[v][1], f[i][0] + get(id2, mov(id1, k - 1)));
                }
            }
            {
                int v = R[p[i]];
                if (v == -1) {
                    ans = min(ans, f[i][1]);
                } else {
                    int id1 = p[i], id2 = p[v];
                    f[v][1] = min(f[v][1], f[i][1] + get(id2, id1));
                    f[v][0] = min(f[v][0], f[i][1] + get(id2, mov(id1, -(k - 1))));
                }
            }
        }
        printf("%lld\n", ans);
    }
}