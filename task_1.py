def mergeSort(list):
    if len(list) > 1:
        mid = len(list)//2
        left = list[:mid]
        right = list[mid:]
        mergeSort(left)
        mergeSort(right)
        i = j = k = 0
        while i < len(left) and j < len(right):
            if left[i] < right[j]:
                list[k] = left[i]
                i += 1
            else:
                list[k] = right[j]
                j += 1
            k += 1
        while i < len(left):
            list[k] = left[i]
            i += 1
            k += 1
        while j < len(right):
            list[k] = right[j]
            j += 1
            k += 1
def sort(list):
    for i in range(len(list)):
        print(list[i], end=" ")
    print()
file = open("sort.in")
n = int(file.readline())
list = list(map(int, file.readline().split()))
mergeSort(list)
print(*list,file=open("sort.out", "w"))


