#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

#define ll long long
#define mid (left + right >> 1)
#define lson ((node << 1) + 1)
#define rson ((node << 1) + 2)

struct Node {
    int left, right;
    ll sum, lz;
};

const int N = 1e6;

int n;
int va[N];
Node tree[4 * N];
vector<ll> lsh;

int getIdx(ll x) {
    return lower_bound(lsh.begin(), lsh.end(), x) - lsh.begin();
}

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