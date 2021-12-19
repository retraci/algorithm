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

const int N = 22;

int n, m;
pii va[N], vb[N];
int idx[N];

void solve() {
    for (int i = 1; i <= n; i++) idx[i] = i;

    map<pii, int> cnt2;
    for (int i = 1; i <= m; i++) {
        auto [a, b] = vb[i];
        cnt2[{a, b}]++, cnt2[{b, a}]++;
    }

    do {
        map<pii, int> cnt1;
        for (int i = 1; i <= m; i++) {
            auto [a, b] = va[i];
            cnt1[{idx[a], idx[b]}]++, cnt1[{idx[b], idx[a]}]++;
        }
        if (cnt1 == cnt2) {
            cout << "Yes" << "\n";
            return;
        }
    } while (next_permutation(idx + 1, idx + n + 1));

    cout << "No" << "\n";
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        va[i] = {a, b};
    }
    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        vb[i] = {a, b};
    }
    solve();

    return 0;
}