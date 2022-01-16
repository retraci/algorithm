#include <bits/stdc++.h>

using namespace std;

struct Point {
    int x, y;
};

const int N = 510;

int n, c;
Point vp[N];
vector<int> lsh;
int vv[1010][1010];

int getIdx(int x) {
    return lower_bound(lsh.begin(), lsh.end(), x) - lsh.begin();
}

bool check(int mid) {
    for (int x1 = 1, x2 = 1; x2 < lsh.size(); x2++) {
        while (lsh[x2] - lsh[x1] + 1 > mid) x1++;
        for (int y1 = 1, y2 = 1; y2 < lsh.size(); y2++) {
            while (lsh[y2] - lsh[y1] + 1 > mid) y1++;
            if (vv[x2][y2] - vv[x2][y1 - 1] - vv[x1 - 1][y2] + vv[x1 - 1][y1 - 1] >= c) return true;
        }
    }

    return false;
}

void solve() {
    for (int i = 0; i < n; i++) {
        lsh.push_back(vp[i].x);
        lsh.push_back(vp[i].y);
    }
    lsh.push_back(0); lsh.push_back(1e5);
    sort(lsh.begin(), lsh.end());
    lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());

//    for (int x: lsh) cout << x << endl;

    memset(vv, 0, sizeof(vv));
    for (int i = 0; i < n; i++) {
        int x = vp[i].x, y = vp[i].y;
        vv[getIdx(x)][getIdx(y)]++;
    }

    for (int i = 1; i <= 1000; i++) {
        for (int j = 1; j <= 1000; j++) {
            vv[i][j] += vv[i - 1][j] + vv[i][j - 1] - vv[i - 1][j - 1];
        }
    }

    int left = 1, right = 1e5;
    while (left < right) {
        int mid = left + right >> 1;
        if (check(mid)) right = mid;
        else left = mid + 1;
    }

    cout << left << endl;
}

int main() {
    freopen("../in.txt", "r", stdin);
    std::ios::sync_with_stdio(false);

    cin >> c >> n;
    for (int i = 0; i < n; i++) {
        cin >> vp[i].x >> vp[i].y;
    }
    solve();

    return 0;
}