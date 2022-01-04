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

int n;

int ask(int x) {
    cout << "? " << x << "\n";
    cout.flush();
    int res;
    cin >> res;
    return res;
}

void solve() {
    int ans[n + 1], vis[n + 1];
    memset(vis, 0, sizeof vis);

    for (int i = 1; i <= n; i++) {
        if (vis[i]) continue;

        vector<int> tmp;
        int ret = ask(i); tmp.push_back(ret);
        int end = ret;
        ret = ask(i); tmp.push_back(ret);
        while (ret != end) {
            ret = ask(i); tmp.push_back(ret);
        }
//        cout << "#\n";
//        for (int x : tmp) cout << x << " ";
//        cout << "\n";

        for (int j = 1; j < tmp.size(); j++) {
            ans[tmp[j - 1]] = tmp[j];
            vis[tmp[j]] = 1;
        }
    }

    cout << "! ";
    for (int i = 1; i <= n; i++) cout << ans[i] << " ";
    cout << "\n";
    cout.flush();
}

int main() {
//#ifdef LOCAL
//    freopen("../in.txt", "r", stdin);
//    freopen("../out.txt", "w", stdout);
//#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        solve();
    }

    return 0;
}