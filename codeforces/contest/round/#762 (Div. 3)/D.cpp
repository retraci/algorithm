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

const int N = 1e5 + 10;

int m, n;
vector<pii> va[N];
int cnt[N];

void init() {
    for (int i = 1; i <= n; i++) {
        sort(va[i].begin(), va[i].end());
    }
}

bool check(int mid) {
    for (int j = 1; j <= m; j++) cnt[j] = 0;

    for (int i = 1; i <= n; i++) {
        auto it = lower_bound(va[i].begin(), va[i].end(), (pii) {mid, 0});
        if (it == va[i].end()) return false;

        while (it != va[i].end()) {
            cnt[it->second]++;
            it = next(it);
        }
    }

    for (int j = 1; j <= m; j++) {
        if (cnt[j] >= 2) return true;
    }
    return false;
}

void solve() {
    init();

    int left = 0, right = 1e9;
    while (left < right) {
        int mid = left + right + 1 >> 1;
        if (check(mid)) left = mid;
        else right = mid - 1;
    }

    cout << left << "\n";
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
        cin >> m >> n;

        for (int i = 1; i <= n; i++) va[i] = {};

        for (int j = 1; j <= m; j++) {
            for (int i = 1; i <= n; i++) {
                int a;
                cin >> a;
                va[i].push_back({a, j});
            }
        }
        solve();
    }


    return 0;
}