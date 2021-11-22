#include <iostream>
#include <fstream>
using namespace std;

void SiftDown(int mas[], int n, int i)
{
    int largest = i;
    // инициализируем наибольший элемент как корень
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && mas[left] > mas[largest]) // если левый дочерний элемент больше корня
    {
        largest = left;
    }

    if (right < n && mas[right] > mas[largest]) // если правый дочерний элемент больше, чем самый большой элемент на данный момент
    {
        largest = right;
    }
    if (largest != i) // если самый большой элемент не корень
    {
        swap(mas[i], mas[largest]);
        SiftDown(mas, n, largest); // рекурсивно преобразуем в двоичную кучу затронутое поддерево
    }
}
// щсновная функция, выполняющая пирамидальную сортировку
void heap_sort(int mas[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i --) // построение кучи
        SiftDown(mas, n, i);

    for (int i = n - 1; i >= 1; i--) // извлечение элементов из кучи
    {
        swap(mas[0], mas[i]); // перемещение корня в конец
        SiftDown(mas, i, 0);
    }
}
int main()
{
    ifstream entrance;
    ofstream output;
    entrance.open("sort.in");
    output.open("sort.out");
    int n;
    entrance >> n;
    int mas[n];
    for(int i = 0 ; i < n ; i++)
    {
        entrance >> mas[i];
    }
    heap_sort(mas , n);
    for(int i = 0 ; i < n ; i++)
    {
        output << mas[i] << " ";
    }
    delete [] mas;
    entrance.close();
    output.close();
}
