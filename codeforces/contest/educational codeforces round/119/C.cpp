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

ll n, K, x;
string str;

void solve() {
    x--;
    vector<ll> va, vb;
    for (int i = 0; i < str.size(); i++) {
        if (str[i] != '*') continue;

        int j = i;
        while (j < str.size() && str[j] == '*') j++;

        va.push_back(j - i);
        i = j - 1;
    }
    reverse(va.begin(), va.end());

    int pos = 0;
    while (x) {
        ll base = va[pos++] * K + 1;
        vb.push_back(x % base);
        x /= base;
    }

    string ans = "";
    pos = 0;
    for (int i = str.size() - 1; i >= 0; i--) {
        if (str[i] != '*') {
            ans += str[i];
            continue;
        }

        int j = i;
        while (j >= 0 && str[j] == '*') j--;
        if (pos < vb.size()) {
            while (vb[pos]--) ans += 'b';
            pos++;
        }

        i = j + 1;
    }

    reverse(ans.begin(), ans.end());
    cout << ans << "\n";
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
        cin >> n >> K >> x;
        cin >> str;
        solve();
    }

    return 0;
}