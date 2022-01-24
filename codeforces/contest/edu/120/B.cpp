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

const int N = 2e5 + 10;

int n;
int va[N];
string s;

void solve() {
    vector<pii> v0, v1;
    for (int i = 1; i <= n; i++) {
        if (s[i] == '0') v0.push_back({va[i], i});
        else v1.push_back({va[i], i});
    }

    sort(v0.begin(), v0.end());
    sort(v1.begin(), v1.end());
    vector<int> ans(n + 1);
    for (int i = 0; i < v0.size(); i++) {
        auto &[v, id] = v0[i];
        ans[id] = i + 1;
    }
    for (int i = 0; i < v1.size(); i++) {
        auto &[v, id] = v1[i];
        ans[id] = i + 1 + v0.size();
    }
    for (int i = 1; i <= n; i++) cout << ans[i] << " ";
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
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> va[i];
        cin >> s;
        s = ' ' + s;
        solve();
    }

    return 0;
}