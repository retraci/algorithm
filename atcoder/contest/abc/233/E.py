if __name__ == '__main__':
    inp = input()
    s = sum((int(a) for a in inp))
    X = int(inp)
    print((X * 10 - s) // 9)
