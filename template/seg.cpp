#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

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
int va[N];
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