#include <fstream>
#include <vector>
using namespace std;

const int Size = 100001; // Размер хеш-таблицы
vector<long> hash_table[Size]; // Создаём хеш-таблицу

int Search(vector<long> a, long el) // Функция, поиска элемента в хеш-таблице
{
    for (int i = 0; i < a.size(); i++) // цикл по всем элементам таблицы
        if (a[i] == el) // если встретели нужный элемент, то возвращаем его индекс
            return i;
    return 0;
}

int main()
{
    ifstream entrance("set.in");
    ofstream output("set.out");
    string com; //инициализируем команду
    while (entrance >> com) // запускаем цикл, пока будут вводиться команды из файла
    {
        if (com == "insert") // ввести элемент в хеш-таблицу
        {
            long el; // инициализируем новый элемент
            entrance >> el; // вводим
            long hash = abs(el % Size); // хешируем элемент
            int b = Search(hash_table[hash], el); // ищем индекс элемент в векторе
            if (hash_table[hash].empty() || hash_table[hash][b] != el) // если вектор не пустой и если этого элемента ещё нет в хеш-таблице
                hash_table[hash].push_back(el); // заряжаем элемент в вектор
        }
        else if (com == "delete") // удалить элемент из хеш-таблицы
        {
            long el; // инициализируем новый элемент
            entrance >> el; // вводим
            long hash = abs(el % Size); // хешируем элемент
            int b = Search(hash_table[hash], el); // ищем индекс элемент в вектор
            if (!hash_table[hash].empty() && hash_table[hash][b] == el) // если вектор не пустой и если этот элемент есть в хеш-таблице
            {
                swap(hash_table[hash][b], hash_table[hash][hash_table[hash].size() - 1]); // меняем местами наш элемент с последним, потому что pop_back удаляет последний эл. в векторе
                hash_table[hash].pop_back();
            }
        }
        else if (com == "exists") // поиск в хеш-таблице
        {
            long el; // инициализируем новый элемент
            entrance >> el; // вводим
            long hash = abs(el % Size); // хешируем элемент
            int b = Search(hash_table[hash], el); // ищем индекс элемент в вектор
            if (!hash_table[hash].empty() && hash_table[hash][b] == el) // если вектор не пустой и если этот элемент есть в хеш-таблице
                output << "true\n";
            else
                output << "false\n";
        }
    }
    return 0;
}
