#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

const int N = 1010;
const int M = 1000010;

int n;
int fa[M], tt;
queue<int> ques[N];

int T;

void solve() {
    for (int i = 0; i < N; i++) {
        while (!ques[i].empty()) ques[i].pop();
    }

    printf("Scenario #%d\n", ++T);

    string op;
    queue<int> quet;
    while (cin >> op, op != "STOP") {
        if (op == "ENQUEUE") {
            int x;
            scanf("%d", &x);
            int tid = fa[x];
            if (ques[tid].size() == 0) {
                quet.emplace(tid);
            }
            ques[tid].emplace(x);
        } else {
            int tid = quet.front();
            int x = ques[tid].front(); ques[tid].pop();

            printf("%d\n", x);

            if (ques[tid].empty()) quet.pop();
        }
    }
    cout << endl;
}

int main() {
    freopen("../in.txt", "r", stdin);

    while (cin >> n, n) {
        for (int i = 1, cnt; i <= n; i++) {
            scanf("%d", &cnt);
            for (int j = 0, b; j < cnt; j++) {
                scanf("%d", &b);
                fa[b] = tt;
            }
            tt++;
        }
        solve();
    }

    return 0;
}