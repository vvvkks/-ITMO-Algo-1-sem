#include <iostream>
#include <algorithm>
#include <fstream>
using namespace std;
struct element // структура для описания элемента
{
    int numb; // само число
    int left_child;
    int right_child;
};
int height(element* tree, int h) // поиск высоты бинарного дерева
{
    if (h == -1)
        return 0; // если нету детей, то не спускаемся
    else // если есть дети, то спускаемся и рассматриваем их как элемент
        return max(height(tree, tree[h].left_child), height(tree, tree[h].right_child)) + 1;
}
int main() {
    ifstream fin("height.in");
    ofstream output("height.out");
    int n;
    fin >> n;
    element* tree = new element[n];
    for (int i = 0; i < n; i++)
    {
        fin >> tree[i].numb >> tree[i].left_child >> tree[i].right_child;
        tree[i].left_child--;
        tree[i].right_child--;
    }
    if (n == 0) // если элементов в дереве нет, то высота равна 0
        output << 0;
    else
        output << height(tree,0) << endl; // иначе ищем высоту
    fin.close();
    output.close();
    return 0;
}