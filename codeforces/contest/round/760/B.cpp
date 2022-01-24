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

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int dx[9] = {0, 0, -1, 1, -1, -1, 1, 1, 0};
const int dy[9] = {-1, 1, 0, 0, -1, 1, -1, 1, 0};

const int N = 110;

int n, m;
string inp;
string va[N];

void init() {
    m = 0;
    for (int i = 0; i < inp.size(); i += 3) {
        string tmp = "";
        tmp += inp[i], tmp += inp[i + 1];
        va[++m] = tmp;
    }
}

void solve() {
    init();

    string ans = va[1];
    for (int i = 2; i <= m; i++) {
//        cout << va[i] << "\n";
        if (ans.back() == va[i][0]) ans += va[i][1];
        else ans += va[i];
    }

    while (ans.size() < n) ans += 'a';
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
        cin >> n;
        getline(cin, inp);
        getline(cin, inp);
        solve();
    }

    return 0;
}