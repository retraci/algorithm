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

string sa, sb;

ll get(string &s) {
    ll res = 0;
    for (char ch : s) {
        res = res * 2 + ch - '0';
    }
    return res;
}

void solve() {
    for (int i = 0; i < sa.size(); i++) {
        sa[i] ^= 1;

        ll s = get(sa);
        string tmp = "";
        while (s) {
            int md = s % 3;
            tmp += '0' + md;
            s /= 3;
        }
        reverse(tmp.begin(), tmp.end());
        while (tmp.size() < sb.size()) tmp = '0' + tmp;
        int cnt = 0;
        for (int j = 0; j < sb.size(); j++) {
            cnt += sb[j] != tmp[j];
        }
        if (cnt == 1) {
            cout << get(sa) << "\n";
            return;
        }

        sa[i] ^= 1;
    }
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> sa >> sb;
    solve();

    return 0;
}