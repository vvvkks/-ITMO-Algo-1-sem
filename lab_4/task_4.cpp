#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct stack // структура элемента, которая хранит информацию(data) и адрес на след элемент
{
	int data;
	stack* next;
};

class Stack // реализация стека через класс
{
private:
    stack* higher; // адрес на верхний элемент
public:
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

	int pop() // удаляем элемент
	{
		int result = higher->data;
		stack* del = higher; // обновляем переменную и привязываем адрес, чтобы потом её удалить и очистить память
        higher = higher->next; // перевести указатель на следующий элемент после верхнего
		delete del; // удалить адрес
		return result; // возвращаем результат
	}
};

int main()
{
	Stack stack;
	ifstream entrance("postfix.in");
	ofstream output("postfix.out");
	string str;
	getline(entrance, str);
	for (int i = 0; str[i] != '\0'; i++) // проверка символов до той степени, пока строка не закончится
	{
		if (str[i] >= '0' && str[i] <= '9') // если элемент >= "0" и <= "9", то заряжаем стек
			stack.push((int)str[i] - '0');
		else if (str[i] == '+') // если элемент == "+", то заряжаем стек суммой послед удаленных элементов
			stack.push(stack.pop() + stack.pop());
		else if (str[i] == '-') // если элемент == "-", то заряжаем стек разностью послед удаленных элементов
		{
			int y = stack.pop();
			int x = stack.pop();
			stack.push(x - y);
		}
		else if (str[i] == '*')    // если элемент == "*", то заряжаем стек произведением послед удаленных элементов
			stack.push(stack.pop() * stack.pop());
	}
    output << stack.pop() << endl;
    entrance.close();
    output.close();
	return 0;
}
