#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

#define ll long long

const int N = 100010;

int n;
ll vm[N], vp[N];
int idx[N];
ll s1[N], s2[N];

bool check(int mid) {
    priority_queue<ll> que;
    ll sum = 0;
    for (int i = 1; i <= n; i++) {
        int id = idx[i];
        if (que.size() < mid) {
            que.push(-vm[id]);
            sum += vm[id];
        } else {
            ll tp = que.top(); tp = -tp;
            if (vm[id] > tp) {
                que.pop();
                que.push(-vm[id]);
                sum -= tp, sum += vm[id];
            }
        }
        s1[i] = sum;
    }

    que = {};
    sum = 0;
    for (int i = n; i >= 1; i--) {
        int id = idx[i];
        if (que.size() < mid) {
            que.push(vp[id]);
            sum += vp[id];
        } else {
            ll tp = que.top();
            if (vp[id] < tp) {
                que.pop();
                que.push(vp[id]);
                sum -= tp, sum += vp[id];
            }
        }
        s2[i] = sum;
    }

    for (int i = mid; i <= n - mid; i++) {
        if (s1[i] >= s2[i + 1]) return true;
    }

    return false;
}

void solve() {
    for (int i = 1; i <= n; i++) idx[i] = i;
    sort(idx + 1, idx + n + 1, [&](auto &a, auto &b) {
        return vm[a] + vp[a] > vm[b] + vp[b];
    });

//    for (int i = 1; i <= n; i++) {
//        int id = idx[i];
//        cout << vm[id] << " " << vp[id] << endl;
//    }

    int left = 0, right = n / 2;
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
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> vm[i];
    for (int i = 1; i <= n; i++) cin >> vp[i];
    solve();

    return 0;
}