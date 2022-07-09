import random
def createData():
    n = random.randint(1, 20000)
    q = random.randint(1, 20000)
    n, q = 10, 10
    print(n, q)
    for i in range(n):
        print(random.randint(1, 20000), end=" ")
    print()
    for i in range(q):
        l = random.randint(1, n)
        r = random.randint(1, n)
        if l > r:
            l, r = r, l
        print(l, r)

if __name__ == '__main__':
    createData()