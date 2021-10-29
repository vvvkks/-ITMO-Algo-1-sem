entrance = (open("smallsort.in"))
n = int(entrance.readline())
a = list(map(int, entrance.readline().split()))
for i in range(n-1):
    for k in range(n-i-1):
        if a[k]>a[k+1]:
            a[k],a[k+1] = a[k+1],a[k]
print(*a, file = open("smallsort.out", "w"))


#Сортировка пузырьком - это метод сортировки массивов и списков путем последовательного
#сравнения и обмена соседних элементов, если предшествующий оказывается больше последующего.