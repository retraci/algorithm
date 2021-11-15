#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <unordered_set>

using namespace std;

const int N = 1010;

int n, K;
int vis[N];
vector<int> ps;

void primes(int n) {
    memset(vis, 0, sizeof vis);
    for (int i = 2; i <= n; i++) {
        if (vis[i]) continue;
        for (int j = i; j <= n / i; j++) vis[i * j] = 1;
    }
}

void solve() {
    primes(n);

    unordered_set<int> st;
    for (int i = 2; i <= n; i++) {
        if (!vis[i]) {
            ps.push_back(i);
            st.insert(i);
        }
    }

    int m = ps.size();
    int cnt = 0;
    for (int i = 0; i < m - 1; i++) {
        int tar = ps[i] + ps[i + 1] + 1;
        cnt += st.count(tar);
    }

    cout << (cnt >= K ? "YES" : "NO") << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> K;
    solve();

    return 0;
}