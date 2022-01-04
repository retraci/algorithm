#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <bitset>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int dx[9] = {-1, 0, 1, 0, -1, -1, 1, 1, 0};
const int dy[9] = {0, 1, 0, -1, -1, 1, -1, 1, 0};

const int N = 1e5 + 10;

int n;
ll ls[N], rs[N], cs[N];

void solve() {
    ll ans[n + 1];

    ll id1, id2;
    ll lb = 1e18, rb = -1e18;
    for (int i = 1; i <= n; i++) {
        ll L = ls[i], R = rs[i], c = cs[i];

        int flag = 0;
        if (L < lb) {
            lb = L, id1 = i;
            flag = 1;
        } else if (L == lb) {
            if (c < cs[id1]) {
                id1 = i;
            }
        }

        if (R > rb) {
            rb = R, id2 = i;
            flag = 1;
        } else if (R == rb) {
            if (c < cs[id2]) {
                id2 = i;
            }
        }

        if (flag) {
            if (L == lb && R == rb) {
                ans[i] = c;
            } else {
                ll cur = cs[id1] + cs[id2];
                if (id1 == id2) cur -= cs[id1];
                ans[i] = cur;
            }
            continue;
        }

        if (L == lb && R == rb) {
            ans[i] = min(ans[i - 1], c);
        } else {
            ll cur = cs[id1] + cs[id2];
            if (id1 == id2) cur -= cs[id1];
            ans[i] = min(ans[i - 1], cur);
        }
    }

    for (int i = 1; i <= n; i++) cout << ans[i] << "\n";
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
        for (int i = 1; i <= n; i++){
            cin >> ls[i] >> rs[i] >> cs[i];
        }
        solve();
    }

    return 0;
}