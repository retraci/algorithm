// region prufer
template<int N>
struct Prufer {
    int deg[N];

    Prufer() {}

    vector<int> tree2prufer(int fa[], int n) {
        fill(deg, deg + n + 1, 0);
        for (int i = 1; i <= n - 1; i++) deg[fa[i]]++;

        vector<int> p(n + 1);
        int i = 0, j = 1;
        while (i + 1 <= n - 2) {
            while (deg[j]) j++;
            p[++i] = fa[j];
            while (i + 1 <= n - 2 && --deg[p[i]] == 0 && p[i] < j) p[i + 1] = fa[p[i]], i++;
            j++;
        }

        return p;
    }

    vector<int> prufer2tree(int p[], int n) {
        fill(deg, deg + n + 1, 0);
        p[n - 1] = n;
        for (int i = 1; i <= n - 1; i++) deg[p[i]]++;

        vector<int> fa(n + 1);
        int i = 1, j = 1;
        while (i <= n - 1) {
            while (deg[j]) j++;
            fa[j] = p[i];
            while (i + 1 <= n - 1 && --deg[p[i]] == 0 && p[i] < j) fa[p[i]] = p[i + 1], i++;
            i++, j++;
        }

        return fa;
    }
};
// endregion
