#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

// Структура для хранения даты
struct Date
{
    int d, m, y;
};

// Структура для хранения данных о сотруднике
struct people
{
    string surname;
    string pos;
    Date date_ob;
    int xp;
    int sal;
    
    // Метод для проверки соответствия года рождения
    bool year_equal(int year)
    {
        return date_ob.y == year;
    }
};

// Функция преобразования строки в дату (формат: дд.мм.гггг)
Date str_to_date(string str) {
    Date temp;
    temp.d = atoi(str.substr(0, 2).c_str());
    temp.m = atoi(str.substr(3, 2).c_str());
    temp.y = atoi(str.substr(6, 4).c_str());
    return temp;
}

// Функция вывода информации о сотруднике
void print(people x)
{
    cout << x.surname << " " << x.pos << " " 
         << x.date_ob.d << "." << x.date_ob.m << "." << x.date_ob.y 
         << " " << x.xp << " " << x.sal << endl;
}

// Структура узла двусвязного списка
struct list
{
    people inf;
    list* next;
    list* prev;
};

// Функция добавления элемента в конец двусвязного списка
void push(list*& h, list*& t, people x)
{
    list* r = new list;
    r->inf = x;
    r->next = NULL;
    
    if (!h && !t)
    {
        r->prev = NULL;
        h = r;
    }
    else
    {
        t->next = r;
        r->prev = t;
    }
    t = r;
}

// Функция вывода всего двусвязного списка
void print_list(list* h)
{
    list* p = h;
    while (p)
    {
        print(p->inf);
        p = p->next;
    }
}

// Функция удаления узла из двусвязного списка (за O(1) времени)
void del_node(list*& h, list*& t, list* r)
{
    if (r == h && r == t)
    {
        h = t = NULL;
    }
    else if (r == h)
    {
        h = h->next;
        if (h) h->prev = NULL;
    }
    else if (r == t)
    {
        t = t->prev;
        if (t) t->next = NULL;
    }
    else
    {
        r->next->prev = r->prev;
        r->prev->next = r->next;
    }
    delete r;
}

// Функция удаления всех элементов с заданным годом рождения
void delete_all_by_year(list*& h, list*& t, int year)
{
    list* p = h;
    while (p)
    {
        list* next_node = p->next;
        if (p->inf.year_equal(year))
        {
            del_node(h, t, p);
        }
        p = next_node;
    }
}

// Размер хэш-таблицы 
const int M = 23;  // простое число, не степень двойки

// Хэш-функция: метод деления h(x) = x mod M
int hash_func(int year)
{
    return year % M;  // метод деления 
}

// Функция вывода всей хэш-таблицы
void print_hash_table(vector<pair<list*, list*>>& hash)
{
    cout << "\nХЭШ-ТАБЛИЦА (размер M = " << M << "):\n";
    for (int i = 0; i < M; i++)
    {
        cout << "Ячейка " << i << ": ";
        if (hash[i].first == NULL)
            cout << "пусто";
        else
            print_list(hash[i].first);
        cout << endl;
    }
}

// Функция поиска сотрудников по году рождения
// Время поиска O(1 + α), где α = N/M - коэффициент заполнения
void search_by_year(vector<pair<list*, list*>>& hash, int year)
{
    int k = hash_func(year);        // определяем ячейку за O(1)
    cout << "\nПоиск сотрудников с годом рождения " << year 
         << " (ячейка " << k << "):\n";
    
    list* p = hash[k].first;
    bool found = false;
    
    while (p)                       // поиск в списке за O(1 + α)
    {
        if (p->inf.year_equal(year))
        {
            cout << "Найден: ";
            print(p->inf);
            found = true;
        }
        p = p->next;
    }
    
    if (!found)
        cout << "Сотрудники с годом рождения " << year << " не найдены.\n";
}

// Функция удаления всех сотрудников с заданным годом рождения
// Время удаления O(1 + α)
void delete_by_year(vector<pair<list*, list*>>& hash, int year)
{
    int k = hash_func(year);        // определяем ячейку за O(1)
    cout << "\nУдаление всех сотрудников с годом рождения " << year 
         << " (ячейка " << k << "):\n";
    
    // Подсчет количества удаляемых элементов
    int count = 0;
    list* p = hash[k].first;
    while (p)
    {
        if (p->inf.year_equal(year))
            count++;
        p = p->next;
    }
    
    if (count == 0)
    {
        cout << "Сотрудники с годом рождения " << year << " не найдены.\n";
        return;
    }
    
    // Удаляем все элементы с заданным годом
    delete_all_by_year(hash[k].first, hash[k].second, year);
    cout << "Удалено " << count << " записей.\n";
}

int main() {
    // Инициализация хэш-таблицы: массив списков размерности M
    vector<pair<list*, list*>> hash;
    hash.resize(M);
    for (int i = 0; i < M; i++)
    {
        hash[i].first = NULL;   // головы списков
        hash[i].second = NULL;  // хвосты списков
    }

    people temp;
    string tmp_dt;
    ifstream fin;
    
    // Чтение данных из файла
    fin.open("in_file.txt");
    if (!fin.is_open())
    {
        cout << "Ошибка: файл in_file.txt не найден!\n";
        return 1;
    }
    
    cout << "Чтение данных из файла in_file.txt...\n";
    int N = 0;  // счетчик количества элементов
    
    // Алгоритм 1: Создание хэш-таблицы
    while (fin >> temp.surname >> temp.pos >> tmp_dt >> temp.xp >> temp.sal)
    {
        temp.date_ob = str_to_date(tmp_dt);
        cout << "Загружен: ";
        print(temp);
        
        // Определяем значение хэш-функции k = h(A[i])
        int k = hash_func(temp.date_ob.y);
        
        // Добавляем элемент в k-ый список хэш-таблицы
        push(hash[k].first, hash[k].second, temp);
        N++;
    }
    fin.close();
    
    cout << "\nЗагрузка завершена. Всего загружено N = " << N << " записей.";
    cout << "\nКоэффициент заполнения α = N/M = " << (float)N/M << endl;
    
    // Вывод построенной хэш-таблицы
    print_hash_table(hash);
    
    // Алгоритм 2: Поиск элемента
    int search_year;
    cout << "\nВведите год рождения для поиска: ";
    cin >> search_year;
    search_by_year(hash, search_year);
    
    // Алгоритм 2: Удаление элемента
    int del_year;
    cout << "\nВведите год рождения для удаления всех записей: ";
    cin >> del_year;
    delete_by_year(hash, del_year);
    
    // Вывод таблицы после удаления
    cout << "\nХэш-таблица после удаления:\n";
    print_hash_table(hash);
    
    return 0;
}