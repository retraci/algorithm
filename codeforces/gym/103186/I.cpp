#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

#define ll long long

const int N = 3e5 + 10;
const ll MOD = 998244353;

template<int SZ>
struct Mat {
    int r, c;
    ll a[SZ + 1][SZ + 1];

    inline Mat(int r = 0, int c = 0) : r(r), c(c) {
        memset(a, 0, sizeof a);
    }

    inline Mat operator-(const Mat &T) const {
        Mat res(r, c);
        for (int i = 1; i <= r; i++) {
            for (int j = 1; j <= c; j++) {
                res.a[i][j] = (a[i][j] - T.a[i][j]) % MOD;
            }
        }
        return res;
    }

    inline Mat operator+(const Mat &T) const {
        Mat res(r, c);
        for (int i = 1; i <= r; i++) {
            for (int j = 1; j <= c; j++) {
                res.a[i][j] = (a[i][j] + T.a[i][j]) % MOD;
            }
        }
        return res;
    }

    inline Mat operator*(const Mat &T) const {
        Mat res(r, T.c);
        for (int i = 1; i <= res.r; i++) {
            for (int j = 1; j <= T.c; j++) {
                for (int k = 1; k <= c; k++) {
                    res.a[i][j] = (res.a[i][j] + a[i][k] * T.a[k][j] % MOD) % MOD;
                }
            }
        }
        return res;
    }

    inline Mat operator*(ll x) const {
        Mat res(r, c);
        for (int i = 1; i <= r; i++) {
            for (int j = 1; j <= c; j++) {
                res.a[i][j] = (a[i][j] * x) % MOD;
            }
        }
        return res;
    }

    inline Mat operator^(ll x) const {
        Mat res(r, c), bas(r, c);
        for (int i = 1; i <= r; i++) res.a[i][i] = 1;
        memcpy(bas.a, a, sizeof a);

        while (x) {
            if (x & 1) res = res * bas;
            bas = bas * bas;
            x >>= 1;
        }
        return res;
    }

    inline bool operator==(const Mat &T) const {
        for (int i = 1; i <= r; i++) {
            for (int j = 1; j <= c; j++) {
                if (a[i][j] != T.a[i][j]) return false;
            }
        }
        return true;
    }

    inline void print() const {
        for (int i = 1; i <= r; i++) {
            for (int j = 1; j <= c; j++) {
                cout << a[i][j] << " ";
            }
            cout << "\n";
        }
    }
};
namespace Seg {
const int SZ = 3e5;

#define mid (left + right >> 1)
#define lson (node << 1)
#define rson ((node << 1) + 1)

struct Node {
    int left, right;
    Mat<4> sum = Mat<4>(1, 4);
    Mat<4> lz = Mat<4>(4, 4);
};

Node tree[SZ * 4];
Mat<4> E;

void push_up(int node) {
    for (int j = 1; j <= 4; j++) {
        tree[node].sum.a[1][j] = (tree[lson].sum.a[1][j] + tree[rson].sum.a[1][j]) % MOD;
    }
}

void push_down(int node) {
    if (!(tree[node].lz == E)) {
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
        tree[node].sum.a[1][4] = 1;
        return;
    }
    build(lson, left, mid);
    build(rson, mid + 1, right);
    tree[node].sum.a[1][4] = tree[lson].sum.a[1][4] + tree[rson].sum.a[1][4];
}

void update(int node, int L, int R, Mat<4> &val) {
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
    if (L <= left && right <= R) return tree[node].sum.a[1][x];

    push_down(node);
    return (query(lson, L, R, x) + query(rson, L, R, x)) % MOD;
}
}
using namespace Seg;

int n, q;
int va[N];

void solve() {
    E = Mat<4>(4, 4);
    E.a[1][1] = E.a[2][2] = E.a[3][3] = E.a[4][4] = 1;
    build(1, 1, n);

    while (q--) {
        int op;
        cin >> op;
        if (op == 0) {
            ll x, L, R;
            cin >> x >> L >> R;
            cout << query(1, L, R, x) << endl;
        } else if (op == 1) {
            ll x, L, R, y;
            cin >> x >> L >> R >> y;
            Mat tmp = E;
            tmp.a[4][x] = y;
            update(1, L, R, tmp);
        } else if (op == 2) {
            ll x, y, L, R;
            cin >> x >> y >> L >> R;
            Mat tmp = E;
            tmp.a[x][x] = tmp.a[y][y] = 0, tmp.a[x][y] = tmp.a[y][x] = 1;
            update(1, L, R, tmp);
        } else if (op == 3) {
            ll x, y, L, R;
            cin >> x >> y >> L >> R;
            Mat tmp = E;
            tmp.a[x][y]++;
            update(1, L, R, tmp);
        }
    }
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(false);
    cin >> n >> q;
    solve();

    return 0;
}