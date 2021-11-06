#include <fstream>
using namespace std;

struct stack // структура элемента, которая хранит информацию(data) и адрес на след элемент
{
    int data;
    stack* next;
};

class Stack // реализация стека через класс
{
public:
    stack* higher; // адрес на верхний элемент
    Stack() // конструктор (нужен для автоматической инициализации переменных)
    {
        higher = NULL;
    }
    void push(int element) // push - заряжает элемент
    {
        stack* unit = new stack(); // создаём новый элемент
        unit->next = higher; // адресом следующего элемента является нынешняя вершина
        unit->data = element; // записываем информацию в элемент
        higher = unit; // обновляем верхний элемент
    }
    void pop() // удаляем элемент
    {
        if (!vacant()) // если функция vacant - True, то можно удалять элемент
        {
            stack* del = higher; // обновляем переменную и привязываем адрес, чтобы потом её удалить и очистить память
            higher = higher->next; // перевести указатель на следующий элемент после верхнего
            delete del; // удалить адрес
        }
    }
    char gethigher() // получить верхний элемент
    {
        return higher->data;
    }
    bool vacant() // проверка на пустоту стека
    {
        if (higher == NULL) // если верхнего элемента нет(== пустоте)
        {
            return true; // возвращаем истинну
        }
        return false;
    }

};

string answer(string str1) // основная функция работы со скобочками
{
    Stack stack;
    for (int i = 0; str1[i] != '\0'; i++) // проверка символов до той степени, пока строка не закончится
    {
        if (str1[i] == '(' || str1[i] == '[') // если скобочка открывается, то заряжаем стек
        {
            stack.push(str1[i]);
        }
        else
        {
            if (stack.vacant() == false && ((stack.gethigher() == '[' && str1[i] == ']') || (stack.gethigher() == '(' && str1[i] == ')')))
            {
                stack.pop(); // если стек не пуст и если скобка закрывается и подходит под условие, то удаляем верхний элемент из стека
            }
            else
            {
                return "NO"; // если if не выполн, то скобочная последовательность - неправильная
            }

        }
    }
    if (stack.vacant()) // проверка на пустоту стека
    {
        return "YES"; // если пуст, то все скобки соответствуют условию
    }
    else
    {
        return "NO";
    }
}

int main()
{
    ifstream entrance("brackets.in");
    ofstream output("brackets.out");
    string str;
    while (entrance >> str) //использование основной функции для всех строк
    {
        output << answer(str) << endl;
    }
    entrance.close();
    output.close();
    return 0;
}
