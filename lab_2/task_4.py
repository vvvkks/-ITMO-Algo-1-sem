entrance = open("antiqs.in","r")
n = int(entrance.readline())
mass = list(range(1, n + 1))
for i in range(n):
    mass[i], mass[int(i / 2)] = mass[int(i / 2)], mass[i]
print(*mass,file= open("antiqs.out", "w"))
