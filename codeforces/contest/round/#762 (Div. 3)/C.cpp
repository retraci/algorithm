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

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int dx[9] = {-1, 0, 1, 0, -1, -1, 1, 1, 0};
const int dy[9] = {0, 1, 0, -1, -1, 1, -1, 1, 0};

string a, b, s;

void solve() {
    reverse(a.begin(), a.end());
    reverse(s.begin(), s.end());

    b = "";
    int n = a.size(), m = s.size();
    int p1 = 0, p2 = 0;
    while (p1 < n && p2 < m) {
        if (s[p2] < a[p1]) {
            if (p2 + 1 >= m) {
                cout << -1 << "\n";
                return;
            }

            int ts = (s[p2 + 1] - '0') * 10 + s[p2] - '0';
            int tb = ts - (a[p1] - '0');

            if (tb < 0 || tb >= 10) {
                cout << -1 << "\n";
                return;
            }
            b += to_string(tb);
            p1++, p2 += 2;
        } else {
            int ts = s[p2] - '0';
            int tb = ts - (a[p1] - '0');

            if (tb < 0 || tb >= 10) {
                cout << -1 << "\n";
                return;
            }
            b += to_string(tb);
            p1++, p2++;
        }
    }

    if (p1 != n) {
        cout << "-1" << "\n";
        return;
    }

    while (p2 < m) b += s[p2++];
    while (b.size() > 1 && b.back() == '0') b.pop_back();
    reverse(b.begin(), b.end());
    cout << b << "\n";
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
        cin >> a >> s;
        solve();
    }

    return 0;
}