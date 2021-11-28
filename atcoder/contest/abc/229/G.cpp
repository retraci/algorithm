#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int N = 2e5 + 10;

int n;
string str;
ll K;
ll va[N], s[N];

ll get_sum(ll x) {
    return (1 + x) * x / 2;
}

ll work(ll need1, ll need2) {
    ll res = 1e18;
    for (int i = need1 + 1; i + need2 <= n; i++) {
        int lb = i - need1, rb = i + need2;
        ll cur1 = 0, cur2 = 0;

        // 左边
        cur1 += need1 * va[i] - (s[i - 1] - s[lb - 1]);
        cur1 -= get_sum(need1);

        // 右边
        cur2 += -need2 * va[i] + (s[rb] - s[i]);
        cur2 -= get_sum(need2);

        res = min(res, cur1 + cur2);
    }

    return res;
}

bool check(int mid) {
    ll cnt1 = work(mid / 2 - 1, (mid + 1) / 2);
    ll cnt2 = work(mid / 2, (mid + 1) / 2 - 1);
    return min(cnt1, cnt2) <= K;
}

void solve() {
    for (int i = 0; i < str.size(); i++) {
        if (str[i] == 'Y') va[++n] = i + 1;
    }

    for (int i = 1; i <= n; i++) s[i] += s[i - 1] + va[i];

    int left = 0, right = n;
    while (left < right) {
        int mid = left + right + 1 >> 1;
        if (check(mid)) left = mid;
        else right = mid - 1;
    }

    cout << left << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> str >> K;
    solve();

    return 0;
}