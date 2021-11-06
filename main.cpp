#include <iostream>
#include <fstream>

using namespace std; // "using-директива" сообщает компилятору, что мы используем все объекты из пространства имен std

struct stack_element // структура элемента, которая хранит информацию(value) и адрес на след элемент, все поля и методы public по умолч
{
    int value;
    stack_element* next; // указатель на следующий элемент
};

class StackClass // реализация стека через класс
{
private:
    stack_element* top = nullptr; // верхушка стека, доступ к полям открыт только самому классу
public:
    void push(int value)
    {
        stack_element* element = new stack_element(); // создание указателя, указывающего на тип struct stack_element
        element->next = top; // адресом следующего элемента является вершина
        element->value = value; // элемент указывает на значение
        top = element; // обновляем вершину
    }

    int pop() // удаление последнего добавленного элемента, возврат его значения
    {
        int temp = top->value;
        top = top->next; // перевести указатель на следующий элемент после верхнего
        return temp; // возврат его значения
    }
};

int main()
{
    StackClass stack;
    int temp, M;
    char a;

    ifstream entrance("stack.in");
    ofstream output("stack.out");

    entrance >> M;

    for (int i = 0; i < M; i++)
    {
        entrance >> a;
        if (a == '+')
        {
            entrance >> temp;
            stack.push(temp);
        }
        else
            output << stack.pop() << '\n';
    }

    entrance.close();
    output.close();

    return 0;
}