#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

struct Label_node // Создаём структуру для наших меток
{
    string name; // сама сторка
    int val; // значение
};

int main()
{
    ifstream entrance("quack.in");
    ofstream output("quack.out");
    vector <string> a;
    vector <Label_node> label; // создаём метку
    queue <unsigned short int> Queue; //  очередь
    unsigned short int registers[26]; //  регистр
    for (int i = 0; i < 26; i++)
        registers[i] = 0; // присваеваем всем буквам регистр ноль
    while (!entrance.eof()) // запускаем цикл пока не кончится файл
    {
        string com;
        entrance >> com;
        a.push_back(com); // заряжаем наши команды в строку
        if (com[0] == ':')
        {
            string name = com;
            name.erase(0, 1); // удаляем первый символ строки (за это отвечает команда erase)
            label.push_back({ name, (int)a.size() - 1 }); // заряжаем в очередь
        }
    }
    int i = 0; // вводим счётчик для while
    while (i < a.size()) // запускаем цикл пока не пройдёмся по всем командам
    {
        // Достаём два верхних эл. очереди => удаляем их => провидим требующиюся операцию => результат заряжаем в очередь
        if (a[i][0] == '-')
        {   // unsigned - беззнаковое число
            unsigned short int x = Queue.front(); // запомянаем первый элемент в очереди
            Queue.pop(); // удаляем
            unsigned short int y = Queue.front(); // front - возвращает ссылку на первый элемент вектора
            Queue.pop(); // ту же опирацию провидим с следующим числом
            Queue.push((x - y) % 65536); // результат опирации заряжаем в стек
        }
            // Достаём два верхних эл. очереди => удаляем их => провидим требующиюся операцию => результат заряжаем в очередь
        else if (a[i][0] == '+')
        {
            unsigned short int x = Queue.front();
            Queue.pop();
            unsigned short int y = Queue.front();
            Queue.pop();
            Queue.push((x + y) % 65536);
        }
            // Достаём два верхних эл. очереди => удаляем их => провидим требующиюся операцию => результат заряжаем в очередь
        else if (a[i][0] == '*')
        {
            unsigned short int x = Queue.front();
            Queue.pop();
            unsigned short int y = Queue.front();
            Queue.pop();
            Queue.push((x * y) % 65536);
        }
            // Достаём два верхних эл. очереди => удаляем их => провидим требующиюся операцию => результат заряжаем в очередь
        else if (a[i][0] == '%')
        {
            unsigned short int x = Queue.front();
            Queue.pop();
            unsigned short int y = Queue.front();
            Queue.pop();
            if (y == 0) // посколку остаток от деления на ноль -  это ноль, то
                Queue.push(0); // заряжаем ноль
            else
                Queue.push(x % y); // иначе заряжаем результат операции
        }
            // Достаём два верхних эл. очереди => удаляем их => провидим требующиюся операцию => результат заряжаем в очередь
        else if (a[i][0] == '/')
        {
            unsigned short int x = Queue.front();
            Queue.pop();
            unsigned short int y = Queue.front();
            Queue.pop();
            if (y == 0) // рассматриваем случай, когда часное - это ноль
                Queue.push(0);
            else
                Queue.push(x / y);
        }

        else if (a[i][0] == '>')
        {
            unsigned short int x = Queue.front();
            Queue.pop(); // удаляем эл. из очереди
            registers[(int)a[i][1] - (int)'a'] = x; // заряжаем удалённый эл. в регистор
        }
        else if (a[i][0] == '<') // берём значение из регистра
            Queue.push(registers[(int)a[i][1] - (int)'a']);
        else if (a[i][0] == 'P')
        {
            if (a[i].size() == 1) // если после Р единственный символ в строке
            {
                output << Queue.front() << "\n"; // печатем эл. который мы в последствии удалим
                Queue.pop();
            }
            else
            {
                output << registers[(int)a[i][1] - (int)'a'] << "\n"; // выводим значение из регистра
            }
        }
        else if (a[i][0] == 'C') // делает почти то же самое, что и 'Р', только выводит число как символ
        {
            if (a[i].size() == 1)
            {
                output << (char)(Queue.front() % 256);
                Queue.pop();
            }
            else
            {
                output << (char)(registers[(int)a[i][1] - (int)'a'] % 256);
            }
        }
        else if (a[i][0] == 'J') // эта команда осуществляет переход на строку с меткой
        {
            string str = a[i]; // записываем команду в строку
            str.erase(0, 1); // обнуляем букву J
            for (int j = 0; j < label.size(); j++) // ищем в метках нужную
                if (label[j].name == str)
                {
                    i = label[j].val; // как только находим счетчик цикла становиться равен индексу метки
                    break; // прекращаем поиск
                }
        }
        else if (a[i][0] == 'Z') // если значение регистра = 0, то выполнение программы продолжается с метки
        {
            if (registers[(int)a[i][1] - (int)'a'] == 0) // проверяем равен ли регистр нулю
            {
                string str = a[i]; // читаем команду
                str.erase(0, 2); // обнуляем первые два симола
                for (int j = 0; j < label.size(); j++)
                    if (label[j].name == str) // ищем в метках нужную
                    {
                        i = label[j].val; // как только находим счетчик цикла становиться равен индексу метки
                        break; // прекращием поиск
                    }
            }
        }
        else if (a[i][0] == 'E') // если значение двух регистров равны, то выполнение программы продолжается с метки
        {
            if (registers[(int)a[i][1] - (int)'a'] == registers[(int)a[i][2] - (int)'a']) // проверка на равность регистров
            {
                string str = a[i];
                str.erase(0, 3); // обнуляем три лишних первых символа
                for (int j = 0; j < label.size(); j++)
                    if (label[j].name == str) // ищем в метках нужную
                    {
                        i = label[j].val; // как только находим счетчик цикла становиться равен индексу метки
                        break; // прекращием поиск
                    }
            }
        }
        else if (a[i][0] == 'G') // если значение первого регистра больше значения второго, то выполнение программы продолжается с метки
        {
            if (registers[(int)a[i][1] - (int)'a'] > registers[(int)a[i][2] - (int)'a']) // проверка условиия, написанного выше
            {
                string str = a[i];
                str.erase(0, 3); // обнуляем три лишних первых символа
                for (int j = 0; j < label.size(); j++)
                    if (label[j].name == str) // ищем в метках нужную
                    {
                        i = label[j].val; // как только находим, счетчик цикла становиться равен индексу метки
                        break; // прекращаем поиск
                    }
            }
        }
        else if (a[i][0] == 'Q') // прекращает работу программы
            break;
        else if (a[i][0] >= '0' && a[i][0] <= '9') // если встречаем обычное число
        {
            unsigned short int element = 0;
            for (int j = 0; j < a[i].size(); j++)
                element = element * 10 + (int)a[i][j] - (int)'0';
            Queue.push(element);
        }
        i++; // добавляем к счётчику + 1 для продолжения чтения команд
    }
    entrance.close();
    output.close();
    return 0;
}
