if __name__ == '__main__':
    n = int(input())
    va = list(map(int, input().split()))
    va.insert(0, 0)

    f = [[float('inf') for _ in range(n + 1)] for _ in range(n + 1)]
    for len in range(1, n + 1):
        for L in range(1, n + 1):
            R = L + len - 1
            if R > n:
                break
            if len == 1 or len == 2:
                f[L][R] = 0
            else:
                for k in range(L + 1, R):
                    f[L][R] = min(f[L][R], f[L][k] + f[k][R] + va[L] * va[k] * va[R])
    print(f[1][n])
