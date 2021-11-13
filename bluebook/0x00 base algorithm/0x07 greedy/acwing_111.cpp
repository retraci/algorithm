#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>

using namespace std;

struct Node {
    int l, r, idx;
    bool operator < (const Node &n1) const {
        return l < n1.l;
    }
};

struct Fance {
    int idx, t;
    bool operator < (const Fance &f1) const {
        return t > f1.t;
    }
};

const int N = 50010;

int n;
Node vczr[N];
int tot;
int ans[N];

void solve() {
    priority_queue<Fance> que;
    sort(vczr, vczr + n);

    for (int i = 0; i < n; i++) {
        if (que.empty() || que.top().t >= vczr[i].l) {
            ans[vczr[i].idx] = ++tot;
            que.push({tot, vczr[i].r});
        } else if (que.top().t < vczr[i].l) {
            Fance cur = que.top(); que.pop();
            ans[vczr[i].idx] = cur.idx;
            cur.t = vczr[i].r;
            que.push(cur);
        }
    }

    cout << tot << endl;
    for (int i = 0; i < n; i++) {
        cout << ans[i] << endl;
    }
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &vczr[i].l, &vczr[i].r);
        vczr[i].idx = i;
    }
    solve();

    return 0;
}

