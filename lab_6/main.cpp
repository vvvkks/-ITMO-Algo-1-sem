#include <fstream>
#include <vector>

using namespace std;

const int Size = 100001; // размер хеш-таблицы
vector<pair<string, string>> hash_table[Size]; // создам хеш-таблицу через пару элементов

int Search(vector<pair<string, string>> a, const string& key) // функция поиска в хеш-таблице по ключу
{
    for (int i = 0; i < a.size(); i++) // цикл по всем элементам таблицы
        if (a[i].first == key) // если встретели нужный ключ, то возвращаем его индекс
            return i;
    return 0; // возвращаем ноль
}

int GetHash(string key) // Функция для хеширования элементов
{
    int CodeHash = 0; // хеш
    const int k = 8; // константа
    for (char i : key) // это цикл foreach. Он совершает одну итерацию на каждый символ в нашем слове
    {
        CodeHash = k * CodeHash + (int)i; // хешируем
    }
    return abs(CodeHash % Size); // возвращием хеш
}

int main()
{
    ifstream entrance("map.in");
    ofstream output("map.out");
    string com;
    while (entrance >> com)
    {
        if (com == "put") // ввести элемент в хеш-таблицу
        {
            string key, value;
            entrance >> key >> value; // вводи ключ и его значение
            long i = GetHash(key); // хешируем
            int b = Search(hash_table[i], key); // ищем индекс элемент в векторе
            if (!hash_table[i].empty() && hash_table[i][b].first == key) // если вектор не пустой и наш элмент совпадает с ключом
                hash_table[i][b].second = value; // записываем знеачение
            if (hash_table[i].empty() || hash_table[i][b].first != key) // если наш вектор пуст или нашего ключа в нём нет
                hash_table[i].emplace_back(key, value); // записывем ключ-значение в конец вектора(emplace_back - запись в конец вектора)
        }
        else if (com == "delete")
        {
            string key;
            entrance >> key; // вводи ключ
            long i = GetHash(key); // хешируем
            int b = Search(hash_table[i], key); // ищем индекс элемент в векторе
            if (!hash_table[i].empty() && hash_table[i][b].first == key) // если вектор не пустой и наш элмент совпадает с ключом
            {
                swap(hash_table[i][b], hash_table[i][hash_table[i].size() - 1]); // меняем местами наш элемент с последним, потому что pop_back удаляет последний эл. в векторе
                hash_table[i].pop_back(); // удаляем его
            }
        }
        else if (com == "get")
        {
            string key;
            entrance >> key; // вводи ключ
            long i = GetHash(key); // хешируем
            int b = Search(hash_table[i], key); // ищем индекс элемент в векторе
            if (!hash_table[i].empty() && hash_table[i][b].first == key) // если вектор не пустой и наш элемент совпадает с ключом
            {
                output << hash_table[i][b].second << '\n'; // выводим значение, принадлежащие этому ключу
            }
            else
            {
                output << "none\n";
            }
        }
    }
    return 0;
}