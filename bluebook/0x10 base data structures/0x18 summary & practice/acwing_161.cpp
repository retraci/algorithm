#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int dx[9] = {0, 0, -1, 1, -1, -1, 1, 1, 0};
const int dy[9] = {-1, 1, 0, 0, -1, 1, -1, 1, 0};

const int N = 10010;

int n;
string va[N];

int tree[10 * N][10], exist[10 * N], tt;

bool insert(string &s) {
    int is_match = false, is_creat = false;
    int root = 0;
    for (char ch : s) {
        int u = ch - '0';
        if (!tree[root][u]) {
            is_creat = true;
            tree[root][u] = ++tt;
        }
        if (exist[root]) is_match = true;

        root = tree[root][u];
    }
    exist[root] = 1;

    return !is_match && is_creat;
}

void solve() {
    tt = 0;
    memset(tree, 0, sizeof tree);
    memset(exist, 0, sizeof exist);

    for (int i = 1; i <= n; i++) {
        if (!insert(va[i])) {
            cout << "NO" << "\n";
            return;
        }
    }
    cout << "YES" << "\n";
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> va[i];
        solve();
    }

    return 0;
}