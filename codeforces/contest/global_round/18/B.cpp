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

const int N = 2e5 + 10;

int L, R;
int s[N][33];
int cnt[33];

void work(int x) {
    for (int i = 0; i <= 31; i++) {
        if (x >> i & 1) s[x][i]++;
    }
}

void init() {
    for (int i = 1; i < N; i++) {
        work(i);
    }

    for (int i = 1; i < N; i++) {
        for (int j = 0; j <= 31; j++) {
            s[i][j] += s[i - 1][j];
        }
    }
}

void solve() {
    memset(cnt, 0, sizeof cnt);
    for (int j = 0; j <= 31; j++) cnt[j] = s[R][j] - s[L - 1][j];

    int mx = *max_element(cnt, cnt + 32);
    int c0 = R - L + 1 - mx;
    cout << c0 << "\n";
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    init();
    int T;
    cin >> T;
    while (T--) {
        cin >> L >> R;
        solve();
    }

    return 0;
}