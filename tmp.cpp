#include <map>
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
const int M = (2e5) + 10;
#define ls tree[now].l
#define rs tree[now].r

int n, m;
int k, N;
int root[M];
vector<int> lsh;

struct Node {
    int num;
    int id;
} q[M];

struct node {
    int l, r;
    int size;
} tree[M << 5];

int get_id(int x) { return lower_bound(lsh.begin(), lsh.end(), x) - lsh.begin() + 1; }

inline int read() {
    int f = 1, x = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-')f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

int build(int l, int r) {
    int now = ++k;

    if (l < r) {
        int mid = (l + r) >> 1;
        ls = build(l, mid);
        rs = build(mid + 1, r);
    }
    return now;
}

int update(int pre, int l, int r, int x) {
    int now = ++k;
    tree[now].size = tree[pre].size + 1;
    ls = tree[pre].l;
    rs = tree[pre].r;

    if (l < r) {
        int mid = (l + r) >> 1;
        if (x > mid) rs = update(rs, mid + 1, r, x);
        else ls = update(ls, l, mid, x);
    }

    return now;
}

int query(int u, int v, int l, int r, int x) {//查询操作
    if (l == r) return l;

    int t = tree[tree[v].l].size - tree[tree[u].l].size;
    int mid = (l + r) >> 1;
    if (x <= t) return query(tree[u].l, tree[v].l, l, mid, x);
    else return query(tree[u].r, tree[v].r, mid + 1, r, x - t);
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    n = read();
    m = read();
    for (int i = 1; i <= n; i++) {
        q[i].num = read();
        q[i].id = i;
    }
    for (int i = 1;i <= n; i++) lsh.push_back(q[i].num);
    sort(lsh.begin(), lsh.end());
    lsh.erase(unique(lsh.begin(), lsh.end()), lsh.end());
    N = lsh.size();

    root[0] = build(1, N);
    for (int i = 1; i <= n; i++) {
        root[i] = update(root[i - 1], 1, N, q[i].num);
    }
    for (int i = 1, l, r, x; i <= m; i++) {
        l = read(); r = read();  = read();
        printf("%d\n", lsh[query(root[l - 1], root[r], 1, N, x) - 1]);
    }
    return 0;
}