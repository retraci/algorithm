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
    for (int i = 0; i < 26; i++) {
        string v = s;
        for (int j = 0; j < v.size(); j++) {
            int x = v[j] - 'a';
            int nxt = (x + i) % 26;
            v[j] = nxt + 'a';
        }
        if (v == t) {
            cout << "Yes" << "\n";
            return;
        }
    }

    cout << "No" << "\n";
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> s >> t;
    solve();

    return 0;
}