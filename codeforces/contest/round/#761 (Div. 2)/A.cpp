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

string s, t;

void solve() {
    map<char, int> cnt;
    for (char ch : s) cnt[ch]++;
    int ca = cnt['a'], cb = cnt['b'], cc = cnt['c'];

    if (t == "abc" && ca > 0 && cb > 0 && cc > 0) {
        string ans = "";
        for (auto[ch, c]: cnt) {
            if (ch == 'b') {
                while (cc--) ans += 'c';
            } else if (ch == 'c') {
                while (cb--) ans += 'b';
            } else {
                while (c--) ans += ch;
            }
        }
        cout << ans << "\n";
        return;
    }

    sort(s.begin(), s.end());
    cout << s << "\n";
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
        cin >> s >> t;
        solve();
    }

    return 0;
}