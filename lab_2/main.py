def mergeSort(left,right):
    result = list()
    i,j,invertions = 0,0,0
    while i < len(left) and j < len(right):
        if left[i] <= right[j]:
            result.append(left[i])
            i += 1
        else:
            result.append(right[j])
            j += 1
            invertions += (len(left)-i)
    result += left[i:]
    result += right[j:]
    return result,invertions
def sc(array):
    if len(array) <= 1:
        return array, 0
    middle = len(array) // 2
    left,inv_left = sc(array[:middle])
    right,inv_right = sc(array[middle:])
    merged, count = mergeSort(left,right)
    count += (inv_left + inv_right)
    return merged, count
file = open("inversions.in")
n = int(file.readline())
array = list(map(int, file.readline().split()))
merge_array,inversions = sc(array)
print(inversions,file=open("inversions.out", "w"))