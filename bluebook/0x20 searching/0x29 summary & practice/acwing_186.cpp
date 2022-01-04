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
typedef tuple<int, int, int> ti3;
typedef tuple<ll, ll, ll> tl3;

const int dx[9] = {-1, 0, 1, 0, -1, -1, 1, 1, 0};
const int dy[9] = {0, 1, 0, -1, -1, 1, -1, 1, 0};

const int N = 2000;

int n;
int bus[66];
vector<tl3> va;

bool check(int s, int d) {
    if (s - d >= 0 || s + d > 59) return false;

    for (int i = s; i <= 59; i += d) {
        if (bus[i] <= 0) return false;
    }

    return true;
}

bool dfs(int cur, int rem, int dep, int mx_dep) {
    if (dep == mx_dep) return rem == 0;

    for (int i = cur; i < va.size(); i++) {
        auto &[c, s, d] = va[i];
        if (c * (mx_dep - dep) < rem) break;

        if (!check(s, d)) continue;
        for (int j = s; j <= 59; j += d) bus[j]--;
        if (dfs(i, rem - c, dep + 1, mx_dep)) return true;
        for (int j = s; j <= 59; j += d) bus[j]++;
    }

    return false;
}

void solve() {
    for (int s = 0; s <= 59; s++) {
        for (int d = 1; d <= 59; d++) {
            if (check(s, d)) {
                int c = (59 - s) / d + 1;
                va.push_back({c, s, d});
            }
        }
    }


    sort(va.begin(), va.end(), greater<>());
    int dep = 0;
    while (!dfs(0, n, 0, dep)) dep++;
    cout << dep << "\n";
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int t;
        cin >> t;
        bus[t]++;
    }
    solve();

    return 0;
}