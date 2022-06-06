if __name__ == '__main__':
    n = 10000
    f = [(2 ** n) for i in range(0, n + 1)]
    f[0] = 0
    f[1] = 1

    ids = [(2 ** n) for i in range(0, n + 1)]

    ans = '"0", "1", '
    ans2 = '0, 0, '
    for i in range(2, n + 1):
        for j in range(0, i):
            t =  2 * f[j] + 2 ** (i - j) - 1
            if f[i] > t:
                f[i] = t
                ids[i] = j

        # ans += '"' + str(f[i]) + '"' + ', '
        ans2 += str(ids[i]) + ', '
    f = open(r'E:\workspace\cpp\clion\algorithm\F.txt', 'w')
    f.write(ans2)
