if __name__ == '__main__':
    n = int(input())
    n %= 10007
    ans = int((n + 2) * (n + 1) * n / 6)
    ans %= 10007
    print(ans)
    