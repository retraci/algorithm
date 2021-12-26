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

int n;
string s;

void solve() {
    n = s.size() - 1;
    vector<int> fa(n + 1, 1e9), fb(n + 1, 1e9), sa(n + 1, 0);

    if (s[1] == 'a') {
        fa[1] = 0;
        fb[1] = 1;
    } else {
        fa[1] = 1;
        fb[1] = 0;
    }
    for (int i = 2; i <= n; i++) {
        if (s[i] == 'a') {
            fa[i] = min(fa[i - 1], fb[i - 1]);
            fb[i] = fb[i - 1] + 1;
        } else {
            fa[i] = min(fa[i - 1], fb[i - 1]) + 1;
            fb[i] = fb[i - 1];
        }
    }

    cout << min(fa[n], fb[n]) << "\n";
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> s;
    s = ' ' + s;
    solve();

    return 0;
}
