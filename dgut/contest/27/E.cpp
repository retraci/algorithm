#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int N = 5e3 + 10;

int n, m;
int va[11 * N];
int tree[11 * N][2], vis[11 * N], tt;

void insert(int x) {
    int rt = 0;
    for (int i = 11; i >= 0; i--) {
        int cur = (x >> i) & 1;
        if (!tree[rt][cur]) tree[rt][cur] = ++tt;
        rt = tree[rt][cur];
    }
    vis[rt] = 1;
}

int search(int x) {
    int ans = 0;
    int rt = 0;
    for (int i = 11; i >= 0; i--) {
        int cur = (x >> i) & 1;
        int tar = cur ^ 1;

        if (tree[rt][tar]) {
            ans |= tar << i;
            rt = tree[rt][tar];
        } else {
            ans |= cur << i;
            rt = tree[rt][cur];
        }
    }
    return ans;
}

int findMaximumXOR(vector<int> &nums) {
    int ans = 0;
    for (int x: nums) {
        insert(x);
        int y = search(x);
        ans = max(ans, x ^ y);
    }

    return ans;
}

void init() {
    tt = 0;
    memset(vis, 0, sizeof vis);
    memset(tree, 0, sizeof tree);
}

void solve() {
    while (m--) {
        init();

        int L, R;
        cin >> L >> R;
        vector<int> nums;
        for (int i = L; i <= R; i++) nums.push_back(va[i]);
        cout << findMaximumXOR(nums) << endl;
    }
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> va[i];
    solve();

    return 0;
}