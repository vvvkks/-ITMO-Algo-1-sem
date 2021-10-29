entrance = (open("sortland.in"))
n = int(entrance.readline())
M = list(map(float, entrance.readline().split()))
D = M.copy()
for i in range(n-1):
    for k in range(n-i-1):
        if M[k]>M[k+1]:
            M[k],M[k+1] = M[k+1],M[k]
Min = M[0]
Max = M[n-1]
Mid = M[n//2]
print(Max, Mid, Min)
print(M, D)
print( D.index(Min)+1,D.index(Mid)+1,D.index(Max)+1, file = open("sortland.out", "w"))

