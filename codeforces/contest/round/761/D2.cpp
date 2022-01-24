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

const int N = 1e4 + 10;

int n;
int inp[N];
int vis[N];

int ask(int a, int b, int c) {
    a++, b++, c++;
    cout << "?" << " " << a << " " << b << " " << c << "\n";
    cout.flush();
    int ret;
    cin >> ret;
    return ret;
}

void work(int x, int id0, int id1) {
    if (x != id0 && x != id1) {
        int ret = ask(id0, id1, x);
        if (!ret) vis[x] = 1;
    }
}

void solve() {
    for (int i = 0; i < n; i += 3) {
        int a = i, b = i + 1, c = i + 2;
        inp[i] = ask(a, b, c);
    }

    int idx0, idx1;
    for (int i = 0; i < n; i += 3) {
        if (inp[i] == 1) idx1 = i;
        else idx0 = i;
    }
    int a0 = idx0, b0 = idx0 + 1, c0 = idx0 + 2;
    int a1 = idx1, b1 = idx1 + 1, c1 = idx1 + 2;

    int q1 = ask(a1, b1, a0);
    int q2 = ask(a1, b1, b0);
    int q3 = ask(a1, b1, c0);
    int q4 = ask(a0, b0, a1);
    int q5 = ask(a0, b0, b1);
    int q6 = ask(a0, b0, c1);

    int id0, id1;
    if (q1 == 1 && q2 == 1 && q3 == 1) {
        id1 = a1;
    } else {
        id1 = c1;
        if (q1 == 0) id0 = a0;
        else if (q2 == 0) id0 = b0;
        else id0 = c0;
    }
    if (q4 == 0 && q5 == 0 && q6 == 0) {
        id0 = a0;
    } else {
        id0 = c0;
        if (q4 == 1) id1 = a1;
        else if (q5 == 1) id1 = b1;
        else id1 = c1;
    }

    for (int i = 0; i < n; i++) vis[i] = 0;
    vis[id0] = 1;
    work(a0, id0, id1);
    work(b0, id0, id1);
    work(c0, id0, id1);
    work(a1, id0, id1);
    work(b1, id0, id1);
    work(c1, id0, id1);


    for (int i = 0; i < n; i += 3) {
        if (i == idx0 || i == idx1) continue;

        int a = i, b = i + 1, c = i + 2;
        if (inp[i]) {
            int ret1 = ask(id0, a, b), ret2 = ask(id0, b, c);
            if (ret1 == 1 && ret2 == 1) continue;
            else if (ret1 == 0 && ret2 == 0) vis[b] = 1;
            else if (ret1 == 0) vis[a] = 1;
            else vis[c] = 1;
        } else {
            int ret1 = ask(id1, a, b), ret2 = ask(id1, b, c);
            if (ret1 == 0 && ret2 == 0) vis[a] = vis[b] = vis[c] = 1;
            else if (ret1 == 1 && ret2 == 1) vis[a] = vis[c] = 1;
            else if (ret1 == 1) vis[b] = vis[c] = 1;
            else vis[a] = vis[b] = 1;
        }
    }

    int cnt = 0;
    for (int i = 0; i < n; i++) cnt += vis[i];
    cout << "!" << " " << cnt;
    for (int i = 0; i < n; i++) {
        if (vis[i]) cout << " " << i + 1;
    }
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