#include <fstream>
#include <vector>

using namespace std;

struct element_struck // Создаём структуру для описания элемента
{
    int date; // само число
    int left_child; // индекс левого ребёнка
    int right_child; // индекс правого ребёнка
};

int check(vector <int>& tops) // Рекрусивная функция проверки коррекности
{
    for (int i = 1; i < tops.size(); i++) // проверяем все вершины и если какая то вершина меньше, чем следующая, то дерево уже некорректно
    {
        if (tops[i] <= tops[i - 1])
            return 1; //  дерево не прошло проверку корректности
    }
    return 0; // всё ок
}

void sort(element_struck* tree, vector <int>& tops, int x) // Рекрусивная функция псевдо сортировки вершин
{
    if (x != -1) // если у вершины нет ребёнка, то дальше функция не идёт
    {
        sort(tree, tops, tree[x].left_child);  // запускаем рекурсию для левого ребёнка
        tops.push_back(tree[x].date);		  // заряжаем вершину в вектор
        sort(tree, tops, tree[x].right_child); // запускаем рекурсию для правого ребёнка
    }
}

int check_2(element_struck* tree, int x)
{
    vector <int> tops; // создаём вектор, который будет хранить вершины дерева
    sort(tree, tops, 0); // запускаем псевдо сортировку
    return check(tops);
}

int main()
{
    ifstream entrance;
    ofstream output;

    entrance.open("check.in");
    output.open("check.out");

    int n;
    entrance >> n;
    element_struck* tree = new element_struck[n];
    for (int i = 0; i < n; i++)
    {
        entrance >> tree[i].date >> tree[i].left_child >> tree[i].right_child;
        tree[i].left_child--;
        tree[i].right_child--;
    }

    if (n == 0 || check_2(tree, 0) == 0) // если флаг - ok или дерево не содержит элементов, то выводим "YES"
        output << "YES";
    else
        output << "NO";

    entrance.close();
    output.close();
    return 0;
}
