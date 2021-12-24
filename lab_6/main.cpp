#include <fstream>

using namespace std;

struct el // Структура ячейки элемента списка
{
    string key; // Ключ
    string value; // Значение
    el* nextInChain; // Адрес следующего элемента в цепочке
    el* next; // Адрес следующего элемента
    el* prev; // Адрес предыдущего элемента
};

class LinkedMap // Класс связанного словаря
{
private:
    el* start; // Начальный адрес элемента
public:
    LinkedMap() // Конструктор (вызывается при объявлении переменной)
    {
        start = new el(); // Объявляем новую переменную
        start->key = ""; // Записываем в ключ пустую строку
        start->value = ""; // Записываем в значение пустую строку
        start->nextInChain = NULL; // Адресу следующего элемента в цепочке ставим NULL
    }

    void Insert(string key, string value, el* Head) // Метод добавления элемента
    {
        el* node_new = Search(key); // Находим адрес элемента по ключу

        if (Search(key) == NULL) // Если такого элемента не существует то создаём новый
        {
            node_new = new el; // Объявляем новую переменную для вызова конструктора
            node_new->key = key; // Заносим ключ
            node_new->value = value; // Заносим значение
            node_new->nextInChain = start->nextInChain; // Переводим адрес следующего в цепочке
            start->nextInChain = node_new; // Обвноляем адрес следующего в цепочке
            el* Tail = Head->prev; // Объявляем переменную конца списка и присвиваем адрес прыдыдущего перед началом
            Tail->next = node_new; // Обновляем адрес следующего элемента
            Head->prev = node_new; // Обновляем адрес предыдущего элемента
            node_new->next = Head; // Ставим адрес следующего элемента
            node_new ->prev = Tail; // Ставим адрес предыдущего элемента


        }
        else // Если элемент не найден
        {
            node_new -> value = value; // То перезаписываем значение
        }
    }

    void Delete(string key, el* Head) // Метод удаления элемента
    {
        el* curNode = start; // Ставим адрес на начало списка

        while (curNode->nextInChain != NULL) // Перебираем все адреса списка
        {
            if (curNode->nextInChain->key == key) // Если нашли нужный элемент
            {
                el* del = curNode->nextInChain; // Запоминаем адрес
                curNode->nextInChain = curNode->nextInChain->nextInChain; // Переводим адрес на следующий
                el* PrevListNode = del->prev, * NextListNode = del->next; // Запоминаем адреса предыдущего/следующего
                del->next->prev = PrevListNode; // Заносим адрес предыдущего
                del->prev->next = NextListNode; // Заносим адрес следующего
                delete del; // Удаляем элемент

                break; // Выходим из цикла
            }
            else // Если не найден
            {
                curNode = curNode->nextInChain; // То переходим к следующему адресу (элементу списка)
            }
        }
    }

    el* Search(string key) // Метод поиска адреса элемента по ключу
    {
        el* curNode = start; // Начинаем с начального адреса списка

        while (curNode->nextInChain != NULL) // До тех пор пока адрес следующего элемента не NULL
        {
            if (curNode->nextInChain->key == key) // Если нашли нужный элемент
            {
                return curNode->nextInChain; // Возвращаем его адрес
            }
            else // Если нет
            {
                curNode = curNode->nextInChain; // Переходим к следующему элементу
            }
        }

        return NULL; // Если прошли цикл и не нашли нужного элемента то возвращаем NULL
    }
};

class UpgradeLinkedMap // Класс для оптимизации работы со ссылочным словарём через массив
{
private:
    LinkedMap hash_table[100001]; // Массив словарей
    el* head; // Адрес начального/конечно элемента ("головы" списка)
public:
    UpgradeLinkedMap() // Конструктор
    {
        head = new el; // Объявляем переменную
        head->next = head->prev = head; // Присваиваем предыдещму и следующему элементу один адрес
        head->value = head->key = "HEAD"; // Присваиваем ключу и значению строку "HEAD"
    }

    int func_hash(string key) // Нахождение индекса
    {
        unsigned int result = 0; // Результат
        unsigned int power = 1; // Степень
        unsigned int p = 31; // Константа

        for (int i = 0; i < key.length(); i++)
        {
            result += (key[i] - 'A') * power;
            power *= p;
        }

        return result % 100001; // Возвращаем остаток от деления результата на макс. кол-во элементов в массиве
    }

    void put(string key, string value) // Метод добавления элемента
    {
        hash_table[func_hash(key)].Insert(key, value, head);
    }

    string get(string key) // Метод получения значения в элементе
    {
        el* result = hash_table[func_hash(key)].Search(key); // Находим элемент по ключу

        if (result == NULL) // Если такого элемента нет
        {
            return "none"; // То возвращаем "none"
        }
        else
        {
            return result->value; // иначе возвращаем значение которое хранится по этому адресу
        }
    }

    void hashDelete(string key) // Метод удаления элемента
    {
        hash_table[func_hash(key)].Delete(key, head);
    }

    string next(string key) // Метод получения значения следующего элемента
    {
        el* result = hash_table[func_hash(key)].Search(key); // Находим адрес элемента

        if (result == NULL || result->next == head)
        { // Если адрес текущего элемента равен NULL или адрес следующего элемента равен адресу Head
            return "none"; // то  возвращаем "none"
        }
        else //иначе
        {
            return result->next->value; // Возвращаем значение следующего элемента
        }
    }

    string prev(string key) // Метод получения значения предыдущего элемента
    {
        el* result = hash_table[func_hash(key)].Search(key); // Находим адрес элемента по ключу

        if (result == NULL || result->prev == head)
        { // Если адрес текущего элемента равен NULL или адрес предыдущего равен адресу Head
            return "none"; // то возвращаем "none"
        }
        else // иначе
        {
            return result->prev->value; // возвращаем значение предыдущего элемента
        }
    }
};

int main()
{
    ifstream entrance("linkedmap.in");
    ofstream output("linkedmap.out");

    UpgradeLinkedMap p; // Объявляем переменную

    string command;
    while (entrance >> command) // Вводим команды
    {
        string key;
        entrance >> key;

        if (command == "put")
        {
            string value;
            entrance >> value;

            p.put(key, value);
        }
        else if (command == "delete")
        {
            p.hashDelete(key);
        }
        else if (command == "get")
        {
            output << p.get(key) << endl;
        }
        else if (command == "next")
        {
            output << p.next(key) << endl;
        }
        else
        {
            output << p.prev(key) << endl;
        }
    }
    return 0;
}