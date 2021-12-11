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
#include <ctime>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int dx[9] = {0, 0, -1, 1, -1, -1, 1, 1, 0};
const int dy[9] = {-1, 1, 0, 0, -1, 1, -1, 1, 0};

const int N = 1e5 + 10;

int n;
int va[N], vb[N];
int idx1[N], idx2[N];

void fake() {
    int mx1 = max_element(va + 1, va + n + 1) - va;
    int mx2 = max_element(vb + 1, vb + n + 1) - vb;

    if (mx1 == mx2) {
        string ans = string(n, '0');
        ans[mx1 - 1] = '1';
        cout << ans << "\n";
    } else {
        cout << string(n, '1') << "\n";
    }
}

void solve() {
    for (int i = 1; i <= n; i++) idx1[i] = idx2[i] = i;
    sort(idx1 + 1, idx1 + n + 1, [&](auto &a, auto &b) {
        return va[a] < va[b];
    });
    sort(idx2 + 1, idx2 + n + 1, [&](auto &a, auto &b) {
        return vb[a] < vb[b];
    });

    string ans = string(n, '0');
    {
        unordered_set<int> st;
        int pos = 1, mx = 0;
        for (int i = 1; i <= n; i++) {
            int id = idx1[i];

            st.insert(id);
            mx = max(mx, vb[id]);
            while (pos <= n && mx >= vb[idx2[pos]]) st.insert(idx2[pos]), pos++;

            if (st.size() >= n) ans[id - 1] = '1';
        }
    }

    {
        unordered_set<int> st;
        int pos = 1, mx = 0;
        for (int i = 1; i <= n; i++) {
            int id = idx2[i];

            st.insert(id);
            mx = max(mx, va[id]);
            while (pos <= n && mx >= va[idx1[pos]]) st.insert(idx1[pos]), pos++;

            if (st.size() >= n) ans[id - 1] = '1';
        }
    }
    cout << ans << "\n";
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    srand(time(0));
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> va[i];
        for (int i = 1; i <= n; i++) cin >> vb[i];
        solve();
    }

    return 0;
}