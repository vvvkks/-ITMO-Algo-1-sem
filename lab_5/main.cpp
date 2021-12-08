#include <iostream>
#include <fstream>

using namespace std;

struct element //создаём структуры для элементов бин поиска

{
    int date; // само число
    element* parent; // указатель на родителя
    element* left_child; // указатель на левого ребёнка
    element* right_child; // указатель на правого ребёнка
};

class Search // создаём класс
{
private:
    element* root = NULL; // верхний элемент(корень)
public:
    element* Searching(int x) // поиск элемента в бин. дереве поиска
{
        element* actual_element = root; //текущий элемент равен корню
        while (actual_element != NULL && x != actual_element -> date) // запускаем while пока не найдём значение эл. или выясним, что такого эл. в дереве нет
        {
            // опциональный поиск искомого числа в левом или в правом поддереве
            if (x < actual_element -> date)
                actual_element = actual_element -> left_child;
            else
                actual_element = actual_element -> right_child;
        }
        return actual_element; // возвращаем найденное значение
}
void Insert(int x) // функция, которая заряжает элементы
{
        if (Cheking(x)) // проверка существует ли заряжаемый элемент
            return;
        element* new_element = new element; // новая ветвь дерева
        // заполняем структуру элемента
        new_element -> date = x;
        new_element -> parent = NULL;
        new_element -> left_child = NULL;
        new_element -> right_child = NULL;

        element* actual_element = root; // создаем структуру для текущего элемента
        // ищем место для нашего нового элемента
        while (actual_element != NULL) //если текущий элемент > нового, то ищем каким будет текущий элемент
        {
            new_element -> parent = actual_element;
            if (new_element -> date < actual_element -> date)
                actual_element = actual_element -> left_child;
            else
                actual_element = actual_element -> right_child;
        }
        if (new_element -> parent == NULL) // если дерево пусто, то новый элемент становится корнем
            root = new_element;
        else
        {
            if (new_element -> date < new_element -> parent -> date) // если текущий эл < нового, то ищем каким будет новый элемент
                new_element -> parent -> left_child = new_element;
            else
                new_element -> parent -> right_child = new_element;
        }
}
void Delete(int x) // Функция, которая обнуляет элементы
{
        element* del = Searching(x); // ищем нужный нам элемент
        if (del == NULL) // если нужного нам элемента нет
        {
            return;
        }
        element* previous; // структура для предыдущего эл.
        element* heplping_el; // структура для вспомогательного эл.
        if (del -> left_child == NULL || del -> right_child == NULL) // если у удаляемого эл. нет детей
            previous = del; // то предыдущий становиться равен удаляемому
        else
            previous = Next(x); // иначе ищем мин. > x
        if (previous -> left_child != NULL) // если левый ребёнок не равен пустоте
            heplping_el = previous -> left_child;
        else
            heplping_el = previous -> right_child;
        if (heplping_el != NULL) // если вспомогательный эл. не равен пустоте
            heplping_el -> parent = previous -> parent;
        if (previous -> parent == NULL) // если родитель равен пустоте
            root = heplping_el;
        else
        {
            if (previous == previous -> parent -> left_child)
                previous -> parent -> left_child = heplping_el;
            else
                previous -> parent -> right_child = heplping_el;
        }
        if (previous != del) // по итогу если предыдущий эл. не равен удаляемому
            del -> date = previous -> date; // удаляемый становиться предыдущим
        delete previous; // и удаляем следующий элемент
    }

    bool Cheking(int x) // проверка равен ли нужный нам элемент пустоте
    {
        return Searching(x) != NULL; // возвращаем true или false
    }

    element* Next(int x) // Функция возвращает минимальный эл. > x или none(если такого нет)
    {
        element* actual_el = root;   // текущий элемент равен корню
        element* heir = NULL; // следующий - пустоте
        // ищем нужный элемент, используя условие
        while (actual_el != NULL)
        {
            if (actual_el -> date > x) // основное условие
            {
                heir = actual_el;
                actual_el = actual_el -> left_child;
            }
            else
                actual_el = actual_el -> right_child;
        }
        return heir; // возвращаем значение
    }

    element* Previous(int x) // Функция возвращает максимальный эл. < x или none(если такого нет)
    {
        element* actual_el = root; // текущий эл. равен корню
        element* previous_el = NULL; // предыдущий - пустоте
        // ищем нужный элемент, используя условие
        while (actual_el != NULL)
        {
            if (actual_el -> date < x) // основное условие
            {
                previous_el = actual_el;
                actual_el = actual_el -> right_child;
            }
            else
                actual_el = actual_el -> left_child;
        }

        return previous_el;
    }
};

int main()
{
    ifstream entrance("bstsimple.in");
    ofstream output("bstsimple.out");
    Search tree;
    string command;
    int key;
    while (entrance >> command >> key)
    // блок чтения команад и выполнение их
    {
        if (command == "insert")
            tree.Insert(key);
        if (command == "delete")
            tree.Delete(key);
        if (command == "exists")
        {
            if (tree.Searching(key))
                output << "true\n";
            else
                output << "false\n";
        }
        if (command == "next")
        {
            element* result = tree.Next(key);
            if (result == NULL)
                output << "none\n";
            else
                output << result -> date << "\n";
        }
        if (command == "prev")
        {
            element* result = tree.Previous(key);
            if (result == NULL)
                output << "none\n";
            else
                output << result -> date << "\n";
        }
    }
    entrance.close();
    output.close();
    return 0;
};