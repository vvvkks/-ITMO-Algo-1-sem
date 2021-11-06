queue = []
input = open("queue.in")
output = open("queue.out", "w")
n = int(input.readline())
first = 0

for i in range(n):
    a = list((input.readline().split()))

    if a[0] == "+":
        a[1] = int(a[1])
        queue.append(a[1])


    else:
        print(queue[first], file=output)
        first += 1
output.close()