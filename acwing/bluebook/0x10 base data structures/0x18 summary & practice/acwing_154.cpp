#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <map>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int N = 1e6 + 10;

int n, K;
int va[N];
map<int, int> cnt;
int ans1[N], ans2[N], tt;

void solve() {
    for (int i = 1; i < K; i++) cnt[va[i]]++;

    for (int i = K; i <= n; i++) {
        cnt[va[i]]++;
        int mi = (*cnt.begin()).first;
        int mx = (*--cnt.end()).first;
        ans1[++tt] = mi, ans2[tt] = mx;

        int lb = i - K + 1;
        if (--cnt[va[lb]] == 0) cnt.erase(va[lb]);
    }

    for (int i = 1; i <= tt; i++) cout << ans1[i] << " ";
    cout << '\n';
    for (int i = 1; i <= tt; i++) cout << ans2[i] << " ";
    cout << '\n';
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> K;
    for (int i = 1; i <= n; i++) cin >> va[i];
    solve();

    return 0;
}