#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

#define ll long long
#define mid (left + right >> 1)
#define lson ((node << 1) + 1)
#define rson ((node << 1) + 2)

struct Node {
    int left, right;
    ll sum, lz;
};

const int N = 5e3 + 10;

int n, K;
int va[N];
int ans[N];
Node tree[4 * N];

void pushUp(int node) {
    tree[node].sum = tree[lson].sum + tree[rson].sum;
}

void pushDown(int node) {
    if (tree[node].lz) {
        tree[lson].sum += tree[node].lz;
        tree[rson].sum += tree[node].lz;
        tree[lson].lz += tree[node].lz;
        tree[rson].lz += tree[node].lz;
        tree[node].lz = 0;
    }
}

void build(int node, int left, int right) {
    tree[node].left = left;
    tree[node].right = right;
    tree[node].sum = tree[node].lz = 0;

    if (left == right) return;
    build(lson, left, mid);
    build(rson, mid + 1, right);
}

void update(int node, int L, int R, ll val) {
    int left = tree[node].left;
    int right = tree[node].right;

    if (right < L || left > R) return;
    if (L <= left && right <= R) {
        tree[node].sum += val;
        tree[node].lz += val;
        return;
    }

    pushDown(node);
    update(lson, L, R, val);
    update(rson, L, R, val);
    pushUp(node);
}

ll query(int node, int L, int R) {
    int left = tree[node].left;
    int right = tree[node].right;

    if (right < L || left > R) return 0;
    if (L <= left && right <= R) return tree[node].sum;

    pushDown(node);
    return query(lson, L, R) + query(rson, L, R);
}

void solve() {
    if (n == 1) {
        cout << va[0] << endl;
        return;
    }

    int flag = 0;
    queue<int> qs[10];
    for (int i = 0; i < n; i++) {
        qs[va[i]].push(i);
        flag |= qs[va[i]].size() >= 2;
    }

    build(0, 0, n - 1);
    for (int i = 0; i < n; i++) {
        for (int j = 9; j >= 0; j--) {
            if (qs[j].empty()) continue;

            int idx = qs[j].front();
            int delta = query(0, idx + 1, n - 1);
            int d = idx + delta - i;
            if (d <= K) {
                qs[j].pop();
                update(0, idx, idx, 1);
                ans[i] = j;
                K -= d;
                break;
            }
        }
    }

    if (K && !flag && K & 1) swap(ans[n - 1], ans[n - 2]);

    for (int i = 0; i < n; i++) {
        printf("%d ", ans[i]);
    }
    cout << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    int T;
    cin >> T;
    while (T--) {
        scanf("%d%d", &K, &n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &va[i]);
        }
        solve();
    }

    return 0;
}