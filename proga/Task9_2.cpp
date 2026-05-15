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
    bool deleted;  // флаг для пометки удаленных элементов
    
    // Конструктор по умолчанию
    people() : surname(""), pos(""), xp(0), sal(0), deleted(false) 
    {
        date_ob.d = 0;
        date_ob.m = 0;
        date_ob.y = 0;
    }
    
    // Метод для проверки соответствия года рождения
    bool year_equal(int year)
    {
        return date_ob.y == year;
    }
    
    // Проверка, пустая ли ячейка (NULL)
    bool is_null()
    {
        return surname.empty() && !deleted;
    }
    
    // Проверка, удалена ли ячейка
    bool is_deleted()
    {
        return deleted;
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
         << " " << x.xp << " " << x.sal;
    if (x.deleted)
        cout << " [УДАЛЕН]";
    cout << endl;
}

// Размер хэш-таблицы (выбираем простое число, не степень двойки)
// Согласно теории: M должно быть простым числом, достаточно далеким от степени двойки
const int M = 23;  // 23 - простое число, не степень двойки (2^4=16, 2^5=32)

// Вспомогательная хэш-функция: метод деления h'(x) = x mod M
int hash_auxiliary(int year)
{
    return year % M;
}

// Основная хэш-функция для линейного хэширования: h(x,i) = (h'(x) + i) mod M
// где i принимает значения в диапазоне [0, M-1]
int hash_main(int year, int i)
{
    return (hash_auxiliary(year) + i) % M;
}

// Функция поиска элемента (согласно теории: идем по ячейкам до NULL или искомого элемента)
int search(vector<people>& hash_table, int year, bool print_results = true)
{
    int h_aux = hash_auxiliary(year);
    
    if (print_results)
        cout << "\nПоиск сотрудников с годом рождения " << year << ":\n";
    
    bool found = false;
    int first_found_index = -1;
    
    // Последовательно исследуем ячейки пока не встретим NULL
    for (int i = 0; i < M; i++)
    {
        int index = hash_main(year, i);
        
        // Если встретили NULL (пустую ячейку), прекращаем поиск
        if (hash_table[index].is_null())
            break;
        
        // Если ячейка не пустая и не удаленная
        if (!hash_table[index].is_deleted() && hash_table[index].year_equal(year))
        {
            if (print_results)
            {
                cout << "Найден (ячейка " << index << "): ";
                print(hash_table[index]);
            }
            found = true;
            if (first_found_index == -1)
                first_found_index = index;
        }
    }
    
    if (!found && print_results)
        cout << "Сотрудники с годом рождения " << year << " не найдены.\n";
    
    return found ? first_found_index : -1;
}

// Функция вставки элемента (согласно Алгоритму 3)
// Используем линейное хэширование: последовательно исследуем ячейки до пустой
bool insert(vector<people>& hash_table, people new_emp)
{
    int h_aux = hash_auxiliary(new_emp.date_ob.y);
    
    // Последовательно исследуем ячейки с помощью h(x,i) = (h'(x) + i) mod M
    for (int i = 0; i < M; i++)
    {
        int index = hash_main(new_emp.date_ob.y, i);
        
        // Если ячейка пустая (NULL) или помечена как удаленная, вставляем
        if (hash_table[index].is_null() || hash_table[index].is_deleted())
        {
            hash_table[index] = new_emp;
            hash_table[index].deleted = false;
            cout << "Вставлен в ячейку " << index << endl;
            return true;
        }
    }
    
    // Если дошли до конца таблицы и не нашли свободной ячейки
    cout << "Ошибка: таблица переполнена, невозможно вставить элемент!\n";
    return false;
}

// Функция удаления элемента (логическое удаление)
// В закрытом хэшировании используем пометку deleted
bool delete_by_year(vector<people>& hash_table, int year)
{
    int h_aux = hash_auxiliary(year);
    bool deleted = false;
    
    cout << "\nУдаление всех сотрудников с годом рождения " << year << ":\n";
    
    // Последовательно исследуем ячейки
    for (int i = 0; i < M; i++)
    {
        int index = hash_main(year, i);
        
        // Если встретили NULL, прекращаем поиск
        if (hash_table[index].is_null())
            break;
        
        // Если ячейка не пустая и не удаленная
        if (!hash_table[index].is_deleted() && hash_table[index].year_equal(year))
        {
            cout << "Удален (ячейка " << index << "): ";
            print(hash_table[index]);
            hash_table[index].deleted = true;
            hash_table[index].surname = "";  // очищаем для is_null()
            deleted = true;
        }
    }
    
    if (!deleted)
        cout << "Сотрудники с годом рождения " << year << " не найдены.\n";
    else
        cout << "Удаление завершено\n";
    
    return deleted;
}

// Функция вывода всей хэш-таблицы
void print_hash_table(vector<people>& hash_table)
{
    cout << "\nХЭШ-ТАБЛИЦА (закрытое хэширование, линейное пробирование)\n";
    cout << "Размер таблицы M = " << M << " (простое число)\n";
    
    for (int i = 0; i < M; i++)
    {
        cout << "Ячейка " << i << ": ";
        if (hash_table[i].is_null())
            cout << "NULL";
        else if (hash_table[i].is_deleted())
            cout << "УДАЛЕН";
        else
            print(hash_table[i]);
    }
    
}

// Функция для демонстрации процесса вставки 
void demonstrate_insertion_process(vector<people>& hash_table, people emp)
{
    int h_aux = hash_auxiliary(emp.date_ob.y);
    cout << "h'(" << emp.date_ob.y << ") = " << h_aux << ". ";
    
    for (int i = 0; i < M; i++)
    {
        int index = hash_main(emp.date_ob.y, i);
        if (hash_table[index].is_null() || hash_table[index].is_deleted())
        {
            cout << "Ячейка " << index << " пустая, вставляем.\n";
            break;
        }
        else
        {
            cout << "Ячейка " << index << " занята, увеличиваем индекс. ";
        }
    }
}

int main() {
    // Создаем хэш-таблицу и заполняем ее значением NULL
    vector<people> hash_table;
    hash_table.resize(M);
    
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
    int N = 0;
    
    // Алгоритм 3: Создание хэш-таблицы
    while (fin >> temp.surname >> temp.pos >> tmp_dt >> temp.xp >> temp.sal)
    {
        temp.date_ob = str_to_date(tmp_dt);
        temp.deleted = false;
        cout << "Загружен: ";
        print(temp);
        
        // Демонстрация процесса вставки
        demonstrate_insertion_process(hash_table, temp);
        
        // Вставка в хэш-таблицу с линейным пробированием
        if (insert(hash_table, temp))
            N++;
        else
            break;
    }
    fin.close();
    
    cout << "\nЗагрузка завершена. Всего загружено N = " << N << " записей.";
    cout << "\nКоэффициент заполнения α = N/M = " << (float)N/M << endl;
    
    // Вывод построенной хэш-таблицы
    print_hash_table(hash_table);
    
    // Добавление нового сотрудника (демонстрация ввода элемента)
    cout << "\nДОБАВЛЕНИЕ НОВОГО СОТРУДНИКА\n";
    people new_emp;
    cout << "Введите фамилию: ";
    cin >> new_emp.surname;
    cout << "Введите должность: ";
    cin >> new_emp.pos;
    cout << "Введите дату рождения (дд.мм.гггг): ";
    cin >> tmp_dt;
    new_emp.date_ob = str_to_date(tmp_dt);
    cout << "Введите стаж работы: ";
    cin >> new_emp.xp;
    cout << "Введите зарплату: ";
    cin >> new_emp.sal;
    new_emp.deleted = false;
    
    demonstrate_insertion_process(hash_table, new_emp);
    insert(hash_table, new_emp);
    N++;
    
    // Вывод таблицы после добавления
    print_hash_table(hash_table);
    
    // Поиск элемента (демонстрация)
    int search_year;
    cout << "\nВведите год рождения для поиска: ";
    cin >> search_year;
    search(hash_table, search_year, true);
    
    // Удаление элемента (демонстрация)
    int del_year;
    cout << "\nВведите год рождения для удаления: ";
    cin >> del_year;
    delete_by_year(hash_table, del_year);
    
    // Вывод таблицы после удаления
    cout << "\nХэш-таблица после удаления:\n";
    print_hash_table(hash_table);
    
    // Повторный поиск после удаления (демонстрация)
    cout << "\nПовторный поиск после удаления:";
    search(hash_table, del_year, true);
    
    return 0;
}