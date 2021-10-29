entrance = open("aplusbb.in")
output = open("aplusbb.out", "w") #открытие и запись файла
a, b = map(int, entrance.readline().split()) #вводится несколько чисел через пробел map преобразует список в соответствие с функцией
print(a + b**2, file=output)
output.close() #закрывает файл