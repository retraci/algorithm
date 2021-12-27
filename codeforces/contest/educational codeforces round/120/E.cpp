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

const int N = 11;

int n, m;
int va[N];
string vs[N];

void solve() {
    int mx = -1;
    vector<int> best;
    int lim = 1 << n;
    for (int mask = 0; mask < lim; mask++) {
        vector<int> vp(m);
        int sum = 0;
        for (int i = 0; i < n; i++) {
            int sign = mask >> i & 1 ? 1 : -1;
            sum += -va[i] * sign;
            for (int j = 0; j < m; j++) {
                vp[j] += (vs[i][j] - '0') * sign;
            }
        }

        vector<int> tmp(m);
        iota(tmp.begin(), tmp.end(), 0);
        sort(tmp.begin(), tmp.end(), [&](auto &a, auto &b) {
            return vp[a] < vp[b];
        });

        for (int i = 0; i < m; i++) {
            int id = tmp[i];
            sum += vp[id] * (i + 1);
        }

        if (mx < sum) {
            mx = sum;
            best = tmp;
        }
    }

    vector<int> ans(m);
    for (int i = 0; i < m; i++) {
        int id = best[i];
        ans[id] = i + 1;
    }
    for (int x : ans) cout << x << " ";
    cout << "\n";
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
        cin >> n >> m;
        for (int i = 0; i < n; i++) cin >> va[i];
        for (int i = 0; i < n; i++) cin >> vs[i];
        solve();
    }

    return 0;
}