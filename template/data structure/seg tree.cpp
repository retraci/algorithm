#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

/*----------------------------------------*/

// 普通线段树
#define ll long long
#define mid (left + right >> 1)
#define lson (node << 1)
#define rson ((node << 1) + 1)

struct Node {
    int left, right;
    ll sum, lz;
};

const int N = 3e6;

int n;
ll va[N];
Node tree[N * 4];
vector<ll> lsh;

int get_id(ll x) {
    return lower_bound(lsh.begin(), lsh.end(), x) - lsh.begin() + 1;
}

void push_up(int node) {
    tree[node].sum = tree[lson].sum + tree[rson].sum;
}

void push_down(int node) {
    if (tree[node].lz) {
        tree[lson].sum += tree[node].lz;
        tree[rson].sum += tree[node].lz;
        tree[lson].lz += tree[node].lz;
        tree[rson].lz += tree[node].lz;
        tree[node].lz = 0;
    }
}

void build(int node, int left, int right) {
    tree[node].left = left, tree[node].right = right;
    tree[node].sum = tree[node].lz = 0;

    if (left == right) return;
    build(lson, left, mid);
    build(rson, mid + 1, right);
}

void update(int node, int L, int R, ll val) {
    int left = tree[node].left, right = tree[node].right;

    if (right < L || left > R) return;
    if (L <= left && right <= R) {
        tree[node].sum += val;
        tree[node].lz += val;
        return;
    }

    push_down(node);
    update(lson, L, R, val);
    update(rson, L, R, val);
    push_up(node);
}

ll query(int node, int L, int R) {
    int left = tree[node].left, right = tree[node].right;

    if (right < L || left > R) return 0;
    if (L <= left && right <= R) return tree[node].sum;

    push_down(node);
    return (query(lson, L, R) + query(rson, L, R)) % MOD;
}

// 线段树维护矩阵
#define ll long long
#define mid (left + right >> 1)
#define lson (node << 1)
#define rson ((node << 1) + 1)

const int N = 3e5 + 10;
const ll MOD = 998244353;

struct matrix {
    int r, c;
    ll s[5][5];

    matrix(int r = 0, int c = 0) : r(r), c(c) {
        memset(s, 0, sizeof s);
    }

    matrix operator*(const matrix &that) const {
        matrix res = matrix(r, that.c);
        for (int i = 1; i <= res.r; i++) {
            for (int j = 1; j <= res.c; j++) {
                for (int k = 1; k <= c; k++) {
                    res.s[i][j] = (res.s[i][j] + s[i][k] * that.s[k][j] % MOD) % MOD;
                }
            }
        }
        return res;
    }

    bool operator!=(const matrix &that) const {
        for (int i = 1; i <= r; i++) {
            for (int j = 1; j <= c; j++) {
                if (s[i][j] != that.s[i][j]) return true;
            }
        }
        return false;
    }
};

struct Node {
    int left, right;
    matrix sum = matrix(1, 4);
    matrix lz = matrix(4, 4);
};

int n, q;
int va[N];
Node tree[N * 4];
matrix E;

void pt(matrix &mat) {
    for (int i = 1; i <= mat.r; i++) {
        for (int j = 1; j <= mat.c; j++) {
            cout << mat.s[i][j] << " ";
        }
        cout << endl;
    }
}

void print(int node) {
    int left = tree[node].left, right = tree[node].right;
    if (left == right) {
        cout << left << " " << right << endl;
        cout << "sum:" << endl;
        pt(tree[node].sum);
        cout << "lz:" << endl;
        pt(tree[node].lz);
        return;
    }

    cout << left << " " << right << endl;
    cout << "sum:" << endl;
    pt(tree[node].sum);
    cout << "lz:" << endl;
    pt(tree[node].lz);

    print(lson);
    print(rson);
}

void push_up(int node) {
    for (int j = 1; j <= 4; j++) {
        tree[node].sum.s[1][j] = (tree[lson].sum.s[1][j] + tree[rson].sum.s[1][j]) % MOD;
    }
}

void push_down(int node) {
    if (tree[node].lz != E) {
        tree[lson].sum = tree[lson].sum * tree[node].lz;
        tree[lson].lz = tree[lson].lz * tree[node].lz;
        tree[rson].sum = tree[rson].sum * tree[node].lz;
        tree[rson].lz = tree[rson].lz * tree[node].lz;
        tree[node].lz = E;
    }
}

void build(int node, int left, int right) {
    tree[node].left = left, tree[node].right = right;
    tree[node].lz = E;

    if (left == right) {
        tree[node].sum.s[1][4] = 1;
        return;
    }
    build(lson, left, mid);
    build(rson, mid + 1, right);
    tree[node].sum.s[1][4] = tree[lson].sum.s[1][4] + tree[rson].sum.s[1][4];
}

void update(int node, int L, int R, matrix &val) {
    int left = tree[node].left, right = tree[node].right;

    if (right < L || left > R) return;
    if (L <= left && right <= R) {
        tree[node].sum = tree[node].sum * val;
        tree[node].lz = tree[node].lz * val;
        return;
    }

    push_down(node);
    update(lson, L, R, val);
    update(rson, L, R, val);
    push_up(node);
}

ll query(int node, int L, int R, int x) {
    int left = tree[node].left, right = tree[node].right;

    if (right < L || left > R) return 0;
    if (L <= left && right <= R) return tree[node].sum.s[1][x];

    push_down(node);
    return (query(lson, L, R, x) + query(rson, L, R, x)) % MOD;
}