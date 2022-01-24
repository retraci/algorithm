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
#include <numeric>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int dx[9] = {-1, 0, 1, 0, -1, -1, 1, 1, 0};
const int dy[9] = {0, 1, 0, -1, -1, 1, -1, 1, 0};

const int N = 5e5 + 10;

int n;
int vop[N], va[N], vb[N];
int fa[N];

void solve() {
    for (int i = 0; i < N; i++) fa[i] = i;

    vector<int> ans;
    for (int i = n; i >= 1; i--) {
        int op = vop[i], a = va[i], b = vb[i];

        if (op == 1) {
            ans.push_back(fa[a]);
        } else {
            fa[a] = fa[b];
        }
    }

    reverse(ans.begin(), ans.end());
    for (int x : ans) cout << x << " ";
    cout << "\n";
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> vop[i];
        if (vop[i] == 1) cin >> va[i];
        else cin >> va[i] >> vb[i];
    }
    solve();

    return 0;
}