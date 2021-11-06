#include <fstream>
using namespace std;

int bin_search_0(int* arr, int key, int n1) // запускаем бинарный поиск
{
    int min = -1; //левая граница
    int max = n1; //правая граница

    // поиск самого левого элемента
    while (min < max - 1) // запускаем цикл
    {
        int mid = (min + max) / 2; // считываем средний индекс
        if (arr[mid] < key) //если средний элемент < ключа, то присваиваем знач сред к мин
            min = mid; //передвигаем левую границу
        else
            max = mid; // иначе сред знач присваивается макс, сужение границ
    }
    return max;
}

int bin_search_n(int* arr, int key, int n1)
{
    int min = -1;// левая граница
    int max = n1; //правая граница

    // поиск самого правого элемента
    while (min < max - 1)
    {
        int mid = (min + max) / 2; //считываем средний индекс
        if (arr[mid] <= key) // если средний элемент <= ключа, то знач сред присваеватся мин
            min = mid; // передвигаем левую границу
        else
            max = mid; // иначе передвигаем правую границу, сужение границ
    }
    return max - 1; //возвращаем это значение, если нет эл-та в массиве
}

int main()
{
    ifstream entrance("binsearch.in");
    ofstream output("binsearch.out");
    int n;
    entrance >> n;
    int* arr = new int[n];
    for (int i = 0; i < n; i++) //заполняем и показываем
        entrance >> arr[i];
    int m;
    entrance >> m;
    for (int i = 0; i < m; i++)
    {
        int key;
        entrance >> key;
        if (bin_search_0(arr, key, n) > bin_search_n(arr, key, n))
            output << "-1 -1\n";
        else
            output << bin_search_0(arr, key, n) + 1 << " " << bin_search_n(arr, key, n) + 1 << endl;
    }
    return 0;
}
