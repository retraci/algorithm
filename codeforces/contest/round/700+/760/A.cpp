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

ll va[11];
unordered_map<int, int> cnt;

void init() {
    cnt = {};
    for (int i = 1; i <= 7; i++) cnt[va[i]]++;
}

bool check() {
    for (auto [k, v] : cnt) {
        if (v < 0) return false;
    }

    return true;
}

void solve() {
    for (int i = 1; i <= 7; i++) {
        for (int j = i + 1; j <= 7; j++) {
            for (int k = j + 1; k <= 7; k++) {
                init();
                ll a = va[i], b = va[j], c = va[k];
                cnt[a]--, cnt[b]--, cnt[c]--;
                cnt[a + b]--, cnt[a + c]--, cnt[b + c]--;
                cnt[a + b + c]--;

                if (check()) {
                    cout << a << " " << b << " " << c << "\n";
                    return;
                }
            }
        }
    }
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
        for (int i = 1; i <= 7; i++) cin >> va[i];
        solve();
    }

    return 0;
}