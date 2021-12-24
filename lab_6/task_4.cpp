#include <bits/stdc++.h>
using namespace std;



struct miniMap{ // структура, которое хранит ключи и значения
    string key;
    vector <vector <string> > element;
    miniMap(){
        element.resize(316); // задаём размер множеству значений
    }
};

struct multiMap{   // создаём мейн_множество, которое будет хранить множество minimap
    vector <vector<miniMap>> minimap;
    multiMap(){
        minimap.resize(100005); // задаём размер множеству
    }
};

multiMap mMap; // инициализируем наше мейн_множество

int hashId(const string& key, int hashSize){ // функция для хеширование элементов
    int hashed = 0;
    int multiplier = 1;
    for (char i : key){
        hashed += multiplier * (int)i;
        hashed %= hashSize;
        multiplier = (multiplier * 41) % hashSize;
    }
    return hashed;
}


void put(const string& key, const string& val){ // процедура добовление элементов в множество
    int keyHash = hashId(key, 100005); // хешируем ключ
    for (auto & i : mMap.minimap[keyHash]){
        if (i.key == key){
            int elHash = hashId(val, 316); // хешируем значение элемента
            for (const auto & j : i.element[elHash]){ // блок
                if (j == val) // если такое ключ-значение уже есть в нашем множестве
                    return;
            }
            i.element[elHash].push_back(val); // блок
            return; // если данный ключ уже есть в множестве, но данного значения в нём нет
        }
    }
    // блок: если данного ключ-значения нет в нашем множестве
    miniMap* newminiMap = new miniMap; // создаём множество ключ-значений
    newminiMap->key = key; // записываем ключ
    newminiMap->element[hashId(val, 316)].push_back(val); // заряжаем значение
    mMap.minimap[keyHash].push_back(*newminiMap); // заряжаем получившиеся мн. в мейн_мн.
    delete newminiMap; // после того как мы зарядили наше мн. удаляем структуру
}

void deleteOne(const string& key, const string& val){ // процедура удаления значения для данного ключа
    int keyHash = hashId(key, 100005); // хешируем ключ
    for (auto & i : mMap.minimap[keyHash]){
        if (i.key == key){
            int elHash = hashId(val, 316); // поиск удаляемого значения
            for (int j = 0; j < i.element[elHash].size(); j++){
                if (i.element[elHash][j] == val) {
                    i.element[elHash].erase(i.element[elHash].begin() + j); // удаление значения
                    return;
                }
            }
        }
    }
}

void deleteAll(const string& key){ // процедура удаления всех значений для данного ключа
    int keyHash = hashId(key, 100005); // хешируем ключ
    for (auto & i : mMap.minimap[keyHash]){
        if (i.key == key){ // ищем данный ключ
            for(auto & j : i.element){ // запускаем цикл для множества значений ключа
                while(!j.empty()) // пока множество не пусто, удаляем последнее значение
                    j.pop_back();
            }
            return;
        }
    }
}

vector<string> Get (const string& key){ // функция поиска всех значений для данного ключа
    vector<string> Result; // создаём пустое мн. значений для данного ключа, в который вернём как ответ
    int keyHash = hashId(key, 100005); // хешируем ключ
    for (auto & i : mMap.minimap[keyHash]){
        if (i.key == key){ // ищем данный ключ
            for(auto & j : i.element){ // запускаем цикл для множества значений ключа
                for(const auto & k : j) { // запускаем цикл для значений
                    Result.push_back(k); // записываем все значения в ответ
                }
            }
            return Result;
        }
    }
    return Result;
}

int main(){
    ifstream entrance;
    ofstream output;
    entrance.open("multimap.in");
    output.open("multimap.out");
    while(!entrance.eof()) {
        string com;
        entrance >> com;
        if (com == "put") {
            string first, second;
            entrance >> first >> second;
            put(first, second);
        }
        if (com == "delete") {
            string first, second;
            entrance >> first >> second;
            deleteOne(first, second);
        }
        if (com == "deleteall") {
            string first;
            entrance >> first;
            deleteAll(first);
        }
        if (com == "get") {
            string first;
            entrance >> first;
            vector<string> getA = Get(first);
            output << getA.size() << ' ';
            for (const string& i : getA)
                output << i << ' ';
            output << "\n";
        }

    }
    entrance.close();
    output.close();
    return 0;
}
