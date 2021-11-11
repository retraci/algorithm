#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

const int N = 410;

int n;
int va[5][N];
vector<int> g[5][N];

bool check(int id1, int id2, int sa, int sb) {
    int *d = va[0], *a = va[id1], *b = va[id2];

    int ta1[N], ta2[N];
    {
        int t = 0;
        for (int i = 0; i < n; i++) {
            int cur = (sa + i) % n;
            ta1[cur] = t;
            t += a[cur];
            ta2[cur] = t;
            t += d[cur];
        }
    }
    int tb1[N], tb2[N];
    {
        int t = 0;
        for (int i = 0; i < n; i++) {
            int cur = (sb + i) % n;
            tb1[cur] = t;
            t += b[cur];
            tb2[cur] = t;
            t += d[cur];
        }
    }

    for (int i = 0; i < n; i++) {
        if (ta2[i] < tb2[i]) {
            if (tb1[i] < ta2[i]) return false;
        } else {
            if (ta1[i] < tb2[i]) return false;
        }
    }

//    cout << id1 << " " << id2 << " " << sa % n << " " << sb % n << endl;
//    for (int i = 0; i < n; i++) {
//        cout << "#" << ta1[i] << " " << ta2[i] << " " << tb1[i] << " " << tb2[i] << endl;
//    }

    return true;
}

void calc(int id1, int id2) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j <= i + n; j++) {
            int u = i % n, v = j % n;

            if (check(id1, id2, u, v)) {
                g[id1][u].push_back(v);
            }
        }
    }
}

void solve() {
    calc(1, 2), calc(2, 3), calc(3, 1);

    for (int i = 0; i < n; i++) {
        for (int bv : g[1][i]) {
            for (int cv : g[2][bv]) {
                for (int av : g[3][cv]) {
                    if (av == i) {
                        cout << av + 1 << " " << bv + 1 << " " << cv + 1 << endl;
                        return;
                    }
                }
            }
        }
    }

    cout << "impossible" << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 0; i < n; i++) cin >> va[0][i];
    for (int i = 0; i < n; i++) cin >> va[1][i];
    for (int i = 0; i < n; i++) cin >> va[2][i];
    for (int i = 0; i < n; i++) cin >> va[3][i];
    solve();

    return 0;
}