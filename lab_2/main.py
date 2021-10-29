def mergeSort(list):
    if len(list) > 1:
        mid = len(list)//2
        left = list[:mid]
        right = list[mid:]
        mergeSort(left)
        mergeSort(right)
        i = j = k = 0
        while i < len(left) and j < len(right):
            if left[i][0] <= right[j][0]:
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

entrance = open('race.in')
n = int(entrance.readline())
racers = []
for i in range(n):
    country, name = entrance.readline().split()
    racers.append(["=== " + country + " ==="])
    racers[-1].append(name)

mergeSort(racers)

sportsmens = list()
sportsmens.append(racers[0])
for i in range(1, n):
    if racers[i][0] == racers[i-1][0]:
        sportsmens[-1].append(racers[i][1])
    else:
        sportsmens.append(racers[i])

output = open('race.out', 'w')
for i in range(len(sportsmens)):
    if i != 0:
        output.write('\n')
    output.write('\n'.join(map(str, sportsmens[i])))
entrance.close()
output.close()
print(sportsmens)



