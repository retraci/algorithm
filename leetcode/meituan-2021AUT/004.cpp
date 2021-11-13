#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

#define ll long long
#define mid (left + right >> 1)
#define lson ((node << 1) + 1)
#define rson ((node << 1) + 2)

struct Node {
    int left, right;
    ll sum, lz;
};

const int N = 2e5 + 10;
const int INF = 1e9 + 7;

int n;
int va[N];
Node tree[4 * N];

void build(int node, int left, int right) {
    tree[node].left = left;
    tree[node].right = right;
    tree[node].sum = tree[node].lz = INF;

    if (left == right) return;
    build(lson, left, mid);
    build(rson, mid + 1, right);
}

void update(int node, int L, int R, int x) {
    int left = tree[node].left;
    int right = tree[node].right;

    if (right < L || left > R) return;
    if (left == right) {
        tree[node].sum = va[left - L + x];
        return;
    }

    update(lson, L, R, x);
    update(rson, L, R, x);
}

ll query(int node, int L, int R) {
    int left = tree[node].left;
    int right = tree[node].right;

    if (right < L || left > R) return INF;
    if (left == right) {
        return tree[node].sum;
    }

    return min(query(lson, L, R), query(rson, L, R));
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    cin >> n;
    for (int i = 0; i < n; i++) {
        scanf("%d", &va[i]);
    }
    build(0, 0, n - 1);

    int m;
    cin >> m;
    while (m--) {
        int op, k, x, y;
        scanf("%d", &op);
        if (op == 1) {
            scanf("%d%d%d", &k, &x, &y);
            x--, y--;
            int L = y, R = y + k - 1;
            update(0, L, R, x);
        } else {
            scanf("%d", &x);
            x--;
            ll ans = query(0, x, x);
            printf("%lld\n", ans == INF ? -1 : ans);
        }
    }

    return 0;
}