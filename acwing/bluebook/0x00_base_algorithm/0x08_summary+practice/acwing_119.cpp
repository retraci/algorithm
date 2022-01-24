#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

struct Point {
    int x, y, type;
    bool operator< (const Point &p) const {
        return x < p.x;
    }
};

const int N = 100000 * 2 + 10;
const double INF = 1e10;

int n;
Point vp[N];
Point tmp[N];

double calc(Point &p1, Point &p2) {
    if (p1.type == p2.type) return INF;
    double dx = p1.x - p2.x, dy = p1.y - p2.y;
    return sqrt(dx * dx + dy * dy);
}

double dfs(int left, int right) {
    if (left >= right) return INF;

    int mid = left + right >> 1;
    double res = min(dfs(left, mid), dfs(mid + 1, right));

    // 对 y 进行归并排序， 可以在 A 处进行剪枝
    {
        int i = left, j = right;
        for (int k = left; k <= right; k++) {
            if (j > right || i <= mid && vp[i].y < vp[j].y) tmp[k] = vp[i++];
            else tmp[k] = vp[j++];
        }
    }

    // 把 x 可能符合条件的全都加入到 tmp 中
    int k = 0;
    for (int i = left; i <= right; i++) {
        if (vp[i].x >= vp[mid].x - res && vp[i].x <= vp[mid].x + res) tmp[k++] = vp[i];
    }

    // A
    for (int i = 1; i < k; i++) {
        for (int j = i - 1; j >= 0 && tmp[i].y - tmp[j].y <= res; j--) {
            res = min(res, calc(tmp[i], tmp[j]));
        }
    }

    return res;
}

void solve() {
    sort(vp, vp + 2 * n);

    printf("%.3lf\n", dfs(0, 2 * n - 1));
}

int main() {
    freopen("../in.txt", "r", stdin);
    std::ios::sync_with_stdio(false);

    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> vp[i].x >> vp[i].y;
            vp[i].type = 1;
        }
        for (int i = n; i < 2 * n; i++) {
            cin >> vp[i].x >> vp[i].y;
            vp[i].type = 2;
        }
        solve();
    }

    return 0;
}