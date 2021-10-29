a = open("turtle.in").read().split('\n')
height, width = map(int, a[0].split())
a = [[int(j) for j in i.split()] for i in a[1:]] #а-двуерный массив, проходимя по всем эл-м,начиная с первого, пропуская 0,
# преобразовываем строки в списо,второму влож циклу поступает одномерный массив i сплитим и
#все строковые j преобразовываем в интовые
#суть этой строки в том,что она преобразовывает все строковые в интовые числа,кроме 0
for i in range(height - 2, -1, -1):
    a[i][0] += a[i + 1][0]
for i in range(1, width):
    a[height - 1][i] += a[height - 1][i - 1]
for i in range(height - 2, -1, -1):
    for g in range(1, width):
        a[i][g] += max(a[i + 1][g], a[i][g - 1])
print(a[0][width - 1],file = open("turtle.out", "w"))
