#include "Lab1.h"
#include <iomanip>
#include <windows.h>
#include <typeinfo>

int inputInt();

string normalize(string s)
{
    size_t start = s.find_first_not_of(" \t\r\n");
    size_t end = s.find_last_not_of(" \t\r\n");

    if (start == string::npos) return "";

    s = s.substr(start, end - start + 1);

    for (size_t i = 0; i < s.length(); i++)
    {
        unsigned char c = (unsigned char)s[i];

        if (c >= 'A' && c <= 'Z') s[i] = c + 32;
        else if (c >= 192 && c <= 223) s[i] = c + 32;
        else if (c == 168) s[i] = 184;
    }

    return s;
}

Musician::Musician()
{
    id = 0;
    name = "";
    age = 0;
    instrument = "";
}

Musician::Musician(int id, string name, int age, string instrument)
{
    this->id = id;
    this->name = name;
    this->age = age;
    this->instrument = instrument;
}

Musician::~Musician()
{
}

void Musician::input()
{
    cout << "ID: ";
    cin >> id;
    cin.ignore(1000, '\n');

    cout << "ФИО: ";
    getline(cin, name);

    cout << "Возраст: ";
    cin >> age;
    cin.ignore(1000, '\n');

    cout << "Инструмент: ";
    getline(cin, instrument);
}

void Musician::output(ostream& os) const
{
    os << left
        << setw(6) << id
        << setw(30) << name
        << setw(18) << age
        << setw(25) << instrument;
}

int Musician::getId() const
{
    return id;
}

string Musician::getName() const
{
    return name;
}

int Musician::getAge() const
{
    return age;
}

string Musician::getInstrument() const
{
    return instrument;
}

void Musician::setId(int id)
{
    this->id = id;
}

void Musician::setName(string name)
{
    this->name = name;
}

void Musician::setAge(int age)
{
    this->age = age;
}

void Musician::setInstrument(string instrument)
{
    this->instrument = instrument;
}

StringMusician::StringMusician() : Musician()
{
    experience = 0;
}

StringMusician::StringMusician(int id, string name, int age, string instrument, int experience)
    : Musician(id, name, age, instrument)
{
    this->experience = experience;
}

void StringMusician::input()
{
    cout << "ID: ";
    cin >> id;
    cin.ignore(1000, '\n');

    cout << "ФИО: ";
    getline(cin, name);

    cout << "Возраст: ";
    cin >> age;
    cin.ignore(1000, '\n');

    cout << "Инструмент: ";
    getline(cin, instrument);

    cout << "Стаж (лет): ";
    cin >> experience;
    cin.ignore(1000, '\n');
}

void StringMusician::output(ostream& os) const
{
    Musician::output(os);

    os << setw(12) << experience;
}

int StringMusician::getExperience() const
{
    return experience;
}

void StringMusician::setExperience(int experience)
{
    this->experience = experience;
}

WindMusician::WindMusician() : Musician()
{
    experience = 0;
}

WindMusician::WindMusician(int id, string name, int age, string instrument, int experience)
    : Musician(id, name, age, instrument)
{
    this->experience = experience;
}

void WindMusician::input()
{
    Musician::input();

    cout << "Стаж (лет): ";
    cin >> experience;
    cin.ignore(1000, '\n');
}

void WindMusician::output(ostream& os) const
{
    Musician::output(os);

    os << setw(12) << experience;
}

int WindMusician::getExperience() const
{
    return experience;
}

void WindMusician::setExperience(int experience)
{
    this->experience = experience;
}

Violinist::Violinist() : StringMusician()
{
    instrument = "Скрипка";
    experience = 0;
}

Violinist::Violinist(int id, string name, int age, int experience)
    : StringMusician(id, name, age, "Скрипка", experience)
{
}

void Violinist::input()
{
    cout << "ID: ";
    cin >> id;
    cin.ignore(1000, '\n');

    cout << "ФИО: ";
    getline(cin, name);

    cout << "Возраст: ";
    cin >> age;
    cin.ignore(1000, '\n');

    cout << "Стаж (лет): ";
    cin >> experience;
    cin.ignore(1000, '\n');

    instrument = "Скрипка";
}

void Violinist::output(ostream& os) const
{
    Musician::output(os);

    os << setw(12) << experience;
}

Orchestra::Orchestra()
{
    capacity = 10;
    count = 0;
    musicians = new Musician * [capacity];
}

Orchestra::~Orchestra()
{
    for (int i = 0; i < count; i++)
    {
        delete musicians[i];
    }

    delete[] musicians;
}

void Orchestra::addMusician(Musician* musician)
{
    if (count >= capacity)
    {
        int newCapacity = capacity + 10;

        Musician** newMusicians = new Musician * [newCapacity];

        for (int i = 0; i < count; i++)
        {
            newMusicians[i] = musicians[i];
        }

        delete[] musicians;

        musicians = newMusicians;
        capacity = newCapacity;
    }

    musicians[count] = musician;
    count++;
}

void Orchestra::showMusicians() const
{
    if (count == 0)
    {
        cout << endl;
        cout << "Оркестр пуст" << endl;
        return;
    }

    cout << endl;
    cout << "СПИСОК МУЗЫКАНТОВ ОРКЕСТРА" << endl;
    cout << "---------------------------------------------------------------------------------------" << endl;

    cout.setf(ios::left);
    cout.setf(ios::dec);

    cout << setw(6) << "ID"
        << setw(30) << "ФИО"
        << setw(18) << "Возраст"
        << setw(25) << "Инструмент"
        << setw(12) << "Стаж (лет)" << endl;

    cout << "---------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < count; i++)
    {
        musicians[i]->output(cout);
        cout << endl;
    }

    cout << "---------------------------------------------------------------------------------------" << endl;

    cout.unsetf(ios::left);
}

void Orchestra::deleteMusician(int id)
{
    for (int i = 0; i < count; i++)
    {
        if (musicians[i]->getId() == id)
        {
            delete musicians[i];

            for (int j = i; j < count - 1; j++)
            {
                musicians[j] = musicians[j + 1];
            }

            count--;

            cout << endl;
            cout << "Музыкант удалён" << endl;
            return;
        }
    }

    cout << endl;
    cout << "Музыкант с таким ID не найден" << endl;
}

void Orchestra::editMusician(int id)
{
    for (int i = 0; i < count; i++)
    {
        if (musicians[i]->getId() == id)
        {
            int fieldChoice;

            cout << endl;
            cout << "Что поменять?" << endl;
            cout << "1. ID" << endl;
            cout << "2. ФИО" << endl;
            cout << "3. Возраст" << endl;
            cout << "4. Инструмент" << endl;
            cout << "5. Изменить все поля" << endl;
            cout << "Выберите поле: ";

            fieldChoice = inputInt();

            switch (fieldChoice)
            {
            case 1:
            {
                int newId;
                cout << "Введите новый ID: ";
                newId = inputInt();
                musicians[i]->setId(newId);
                break;
            }
            case 2:
            {
                string newName;
                cout << "Введите новое ФИО: ";
                getline(cin, newName);
                musicians[i]->setName(newName);
                break;
            }
            case 3:
            {
                int newAge;
                cout << "Введите новый возраст: ";
                newAge = inputInt();
                musicians[i]->setAge(newAge);
                break;
            }
            case 4:
            {
                Violinist* v = dynamic_cast<Violinist*>(musicians[i]);

                if (v != nullptr)
                {
                    cout << "У скрипача инструмент фиксирован — Скрипка." << endl;
                    return;
                }

                string newInstrument;
                cout << "Введите новый инструмент: ";
                getline(cin, newInstrument);
                musicians[i]->setInstrument(newInstrument);
                break;
            }
            case 5:
            {
                int newId;
                string newName;
                int newAge;
                string newInstrument;

                cout << endl;
                cout << "ИЗМЕНЕНИЕ ВСЕХ ДАННЫХ" << endl;

                cout << "Введите новый ID: ";
                newId = inputInt();
                musicians[i]->setId(newId);

                cout << "Введите новое ФИО: ";
                getline(cin, newName);
                musicians[i]->setName(newName);

                cout << "Введите новый возраст: ";
                newAge = inputInt();
                musicians[i]->setAge(newAge);

                Violinist* v = dynamic_cast<Violinist*>(musicians[i]);
                StringMusician* sm = dynamic_cast<StringMusician*>(musicians[i]);
                WindMusician* wm = dynamic_cast<WindMusician*>(musicians[i]);

                if (v != nullptr)
                {
                    cout << "У скрипача инструмент фиксирован — Скрипка." << endl;
                    musicians[i]->setInstrument("Скрипка");

                    int newExp;
                    cout << "Введите новый стаж (лет): ";
                    newExp = inputInt();
                    v->setExperience(newExp);
                }
                else
                {
                    cout << "Введите новый инструмент: ";
                    getline(cin, newInstrument);
                    musicians[i]->setInstrument(newInstrument);

                    int newExp;
                    cout << "Введите новый стаж (лет): ";
                    newExp = inputInt();

                    if (sm != nullptr) sm->setExperience(newExp);
                    else if (wm != nullptr) wm->setExperience(newExp);
                }

                break;
            }
            default:
                cout << "Неверный выбор." << endl;
                return;
            }

            cout << "Данные изменены." << endl;
            return;
        }
    }

    cout << "Музыкант с таким ID не найден." << endl;
}

void Orchestra::searchMusician(string instrument) const
{
    bool found = false;

    string searchTarget = normalize(instrument);

    cout << endl;
    cout << "РЕЗУЛЬТАТ ПОИСКА" << endl;
    cout << "Инструмент: " << instrument << endl;
    cout << "---------------------------------------------------------------------------------------" << endl;

    cout.setf(ios::left);
    cout.setf(ios::dec);

    cout << setw(6) << "ID"
        << setw(30) << "ФИО"
        << setw(18) << "Возраст"
        << setw(25) << "Инструмент"
        << setw(12) << "Стаж (лет)" << endl;

    cout << "---------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < count; i++)
    {
        string dbInstrument = normalize(musicians[i]->getInstrument());

        if (dbInstrument == searchTarget)
        {
            musicians[i]->output(cout);
            cout << endl;
            found = true;
        }
    }

    if (!found)
    {
        cout << "По данному инструменту музыканты не найдены" << endl;
    }

    cout << "---------------------------------------------------------------------------------------" << endl;

    cout.unsetf(ios::left);
}

void Orchestra::sortMusicians()
{
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            if (musicians[j]->getName() > musicians[j + 1]->getName())
            {
                Musician* temp = musicians[j];

                musicians[j] = musicians[j + 1];
                musicians[j + 1] = temp;
            }
        }
    }

    cout << endl;
    cout << "Сортировка по ФИО выполнена" << endl;
}

void Orchestra::saveToFile(string filename) const
{
    ofstream file;

    file.open(filename);

    if (!file.is_open())
    {
        cout << "Не удалось открыть файл" << endl;
        return;
    }

    if (file.good())
    {
        file << "СПИСОК МУЗЫКАНТОВ ОРКЕСТРА" << endl;
        file << "---------------------------------------------------------------------------------------" << endl;

        file.setf(ios::left);

        file << setw(6) << "ID"
            << setw(30) << "ФИО"
            << setw(18) << "Возраст"
            << setw(20) << "Инструмент"
            << setw(12) << "Стаж (лет)" << endl;

        file << "---------------------------------------------------------------------------------------" << endl;

        for (int i = 0; i < count; i++)
        {
            musicians[i]->output(file);
            file << endl;
        }

        file << "----------------------------------------------------------------------------------------" << endl;

        file.unsetf(ios::left);
    }

    if (file.bad())
    {
        cout << "Ошибка потока" << endl;
    }

    if (file.fail())
    {
        cout << "Ошибка записи" << endl;
    }

    if (file.eof())
    {
        file.clear();
    }

    file.close();

    cout << "Данные сохранены в файл orchestra.txt" << endl;
}

Concert::Concert()
{
    name = "";
    date = "";
}

Concert::Concert(string name, string date)
{
    this->name = name;
    this->date = date;
}

void Concert::show() const
{
    cout << "Концерт: " << name << endl;
    cout << "Дата: " << date << endl;

    orchestra.showMusicians();
}

int inputInt()
{
    int value;
    while (true)
    {
        cin >> value;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Ошибка ввода. Попробуйте снова." << endl;
            continue;
        }

        cin.ignore(1000, '\n');
        return value;
    }
}

void runLab1()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Orchestra orchestra;

    int choice;

    do
    {
        cout << endl;
        cout << "       ЛАБОРАТОРНАЯ РАБОТА 1" << endl;
        cout << "       ВАРИАНТ 13 - ОРКЕСТР" << endl;
        cout << "---------------------------------------------" << endl;
        cout << "1. Добавить музыканта" << endl;
        cout << "2. Показать музыкантов" << endl;
        cout << "3. Удалить музыканта" << endl;
        cout << "4. Изменить музыканта" << endl;
        cout << "5. Поиск по инструменту" << endl;
        cout << "6. Сортировка по ФИО" << endl;
        cout << "7. Сохранить в файл" << endl;
        cout << "0. Выход" << endl;
        cout << "----------------------------------------------" << endl;
        cout << "Выберите пункт: ";

        choice = inputInt();

        switch (choice)
        {
        case 1:
        {
            int type;

            cout << endl;
            cout << "ВЫБОР ТИПА МУЗЫКАНТА" << endl;
            cout << "1. Струнный музыкант" << endl;
            cout << "2. Духовой музыкант" << endl;
            cout << "3. Скрипач" << endl;
            cout << "Выберите тип: ";

            type = inputInt();

            Musician* musician = nullptr;

            if (type == 1)
            {
                musician = new StringMusician();
            }
            else if (type == 2)
            {
                musician = new WindMusician();
            }
            else if (type == 3)
            {
                musician = new Violinist();
            }
            else
            {
                cout << "Неверный тип музыканта" << endl;
                break;
            }

            cout << endl;
            cout << "ВВОД ДАННЫХ МУЗЫКАНТА" << endl;

            musician->input();

            orchestra.addMusician(musician);

            cout << endl;
            cout << "Музыкант успешно добавлен" << endl;

            break;
        }

        case 2:
            orchestra.showMusicians();
            break;

        case 3:
        {
            int id;

            cout << endl;
            cout << "Введите ID музыканта: ";
            id = inputInt();

            orchestra.deleteMusician(id);

            break;
        }

        case 4:
        {
            int id;

            cout << endl;
            cout << "Введите ID музыканта: ";
            id = inputInt();

            orchestra.editMusician(id);

            break;
        }

        case 5:
        {
            string instrument;

            cout << endl;
            cout << "Введите название инструмента: ";

            getline(cin, instrument);

            orchestra.searchMusician(instrument);

            break;
        }

        case 6:
            orchestra.sortMusicians();
            break;

        case 7:
            orchestra.saveToFile("orchestra.txt");
            break;

        case 0:
            cout << endl;
            cout << "Работа программы завершена." << endl;
            break;

        default:
            cout << endl;
            cout << "Такого пункта меню нет" << endl;
        }

    } while (choice != 0);
}