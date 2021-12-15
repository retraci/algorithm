#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <queue>

using namespace std;


typedef pair<int, int> PII;

const int N = 810;

int n, m;
char g[N][N];
int st[N][N];
PII ghost[2];

bool check(int x, int y, int step) {
    if (x < 0 || x >= n || y < 0 || y >= m || g[x][y] == 'X') return false;

    for (int i = 0; i < 2; i++)
        if (abs(x - ghost[i].first) + abs(y - ghost[i].second) <= step * 2)
            return false;

    return true;
}

int bfs() {
    int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};

    memset(st, 0, sizeof st);

    int cnt = 0;
    PII boy, girl;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (g[i][j] == 'M') boy = {i, j};
            else if (g[i][j] == 'G') girl = {i, j};
            else if (g[i][j] == 'Z') ghost[cnt++] = {i, j};

    queue<PII> qb, qg;
    qb.push(boy);
    qg.push(girl);

    int step = 0;
    while (qb.size() || qg.size()) {
        step++;
        for (int i = 0; i < 3; i++)
            for (int j = 0, len = qb.size(); j < len; j++) {
                auto t = qb.front();
                qb.pop();
                int x = t.first, y = t.second;
                if (!check(x, y, step)) continue;
                for (int k = 0; k < 4; k++) {
                    int a = x + dx[k], b = y + dy[k];
                    if (check(a, b, step)) {
                        if (st[a][b] == 2) {
                            cout << a << " " << b << "\n";
                            return step;
                        }
                        if (!st[a][b]) {
                            st[a][b] = 1;
                            qb.push({a, b});
                        }
                    }
                }
            }

        for (int i = 0; i < 1; i++)
            for (int j = 0, len = qg.size(); j < len; j++) {
                auto t = qg.front();
                qg.pop();

                int x = t.first, y = t.second;
                if (!check(x, y, step)) continue;
                for (int k = 0; k < 4; k++) {
                    int a = x + dx[k], b = y + dy[k];
                    if (check(a, b, step)) {
                        if (st[a][b] == 1) {
                            return step;
                        }
                        if (!st[a][b]) {
                            st[a][b] = 2;
                            qg.push({a, b});
                        }
                    }
                }
            }
    }

    return -1;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; i++) scanf("%s", g[i]);

        printf("%d\n", bfs());
    }

    return 0;

}
