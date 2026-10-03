#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string normalize(string s);
int inputInt();

class Musician
{
protected:
    int id;
    string name;
    int age;
    string instrument;

public:
    Musician();
    Musician(int id, string name, int age, string instrument);
    virtual ~Musician();

    virtual void input();
    virtual void output(ostream& os) const;

    int getId() const;
    string getName() const;
    int getAge() const;
    string getInstrument() const;

    void setId(int id);
    void setName(string name);
    void setAge(int age);
    void setInstrument(string instrument);
};

class StringMusician : public Musician
{
protected:
    int experience;

public:
    StringMusician();
    StringMusician(int id, string name, int age, string instrument, int experience);

    void input() override;
    void output(ostream& os) const override;

    int getExperience() const;
    void setExperience(int experience);
};

class WindMusician : public Musician
{
protected:
    int experience;

public:
    WindMusician();
    WindMusician(int id, string name, int age, string instrument, int experience);

    void input() override;
    void output(ostream& os) const override;

    int getExperience() const;
    void setExperience(int experience);
};

class Violinist : public StringMusician
{
public:
    Violinist();
    Violinist(int id, string name, int age, int experience);

    void input() override;
    void output(ostream& os) const override;
};

class Orchestra
{
private:
    Musician** musicians;
    int count;
    int capacity;

public:
    Orchestra();
    ~Orchestra();

    void addMusician(Musician* musician);
    void showMusicians() const;
    void deleteMusician(int id);
    void editMusician(int id);
    void searchMusician(string instrument) const;
    void sortMusicians();
    void saveToFile(string filename) const;
};

class Concert
{
private:
    string name;
    string date;
    Orchestra orchestra;

public:
    Concert();
    Concert(string name, string date);

    void show() const;
};

void runLab1();