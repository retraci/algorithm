#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

#define mid (left + right >> 1)
#define lson (node << 1)
#define rson ((node << 1) + 1)

struct Node {
    int left, right;
    ll sum, lz;
};

const int N = 1e6 + 10;

int n;
ll va[N];
Node tree[N * 4];
vector<ll> lsh;

int f[N];
int cnt[N], mx[N], vis[N];

int get_id(ll x) {
    return lower_bound(lsh.begin(), lsh.end(), x) - lsh.begin() + 1;
}

void push_up(int node) {
    tree[node].sum = max(tree[lson].sum, tree[rson].sum);
}

void push_down(int node) {
    if (tree[node].lz) {
        tree[lson].sum = max(tree[lson].sum, tree[node].lz);
        tree[rson].sum = max(tree[rson].sum, tree[node].lz);
        tree[lson].lz = max(tree[lson].lz, tree[node].lz);
        tree[rson].lz = max(tree[rson].lz, tree[node].lz);
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
        tree[node].sum = max(tree[node].sum, val);
        tree[node].lz = max(tree[node].lz, val);
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
    return max(query(lson, L, R), query(rson, L, R));
}

void solve() {
    for (int i = 1; i <= n; i++) lsh.push_back(va[i]);
    sort(lsh.begin(), lsh.end());
    lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());
    build(1, 1, lsh.size());

    for (int i = 1; i <= n; i++) {
        int id = get_id(va[i]);
        f[i] = query(1, 1, id) + 1;
        update(1, id, id, f[i]);
    }

//    for (int i = 1; i <= n; i++) cout << f[i] << " ";
//    cout << endl;

    int ans = *max_element(f + 1, f + n + 1);
    for (int i = n; i >= 1; i--) {
        int id = get_id(va[i]);

        if (f[i] == ans || mx[f[i] + 1] >= id) {
            vis[i] = 1;
            cnt[f[i]]++;
            mx[f[i]] = max(mx[f[i]], id);
        }
    }

    for (int i = 1; i <= n; i++) {
        if (vis[i] && cnt[f[i]] == 1) cout << ans - 1 << " ";
        else cout << ans << " ";
    }
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> va[i];
    solve();

    return 0;
}