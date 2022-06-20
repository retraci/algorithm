if __name__ == '__main__':
    _ = int(input())
    for __ in range(_):
        n = int(input())
        a = int(input())
        lim = 9 * (10 ** (n - 1))
        if a < lim:
            t = (10 ** n) - 1 - a
            print(t)
        else:
            t = "1" * (n + 1)
            t = int(t)
            t -= a
            print(t)
