entrance = open("priorityqueue.in", 'r')
output = open("priorityqueue.out", 'w')

commands = []
queue = []

line = entrance.readline()

while len(line):

    commands.append(line.split())
    line = entrance.readline()

for a in commands:

    if a[0] == 'push': # если первый эл-т массива == 'push', то добавляем второй элемент в очередь

        queue.append(int(a[1]))

    elif a[0] == 'extract-min': # если первый эл-т массива == 'extract-min',то

        if len(queue):

            min = queue[0]
            index = 0
            # проверяем пуста ли очередь
            for r in range(len(queue) - 1, -1, -1):
                if queue[r] < min:
                    min = queue[r]
                    index = r

            print(min, file=output)
            # если очередь не пуста, то:
            del queue[index] # удаляем из очереди минимальный элемент и выводим его в выходной фаил
        else:

            print('*', file=output) # выводим в выходной фаил *

    elif a[0] == 'decrease-key':  # если первый эл-т массива == 'decrease-key', то:

        element = int(commands[int(a[1]) - 1][1])
        commands[int(a[1]) - 1][1] = int(a[2])

        for i in range(len(queue)):

            if queue[i] == element:
                queue[i] = int(a[2])   # заменяем значение элемента, добавленного в очередь операцией "push"
                break