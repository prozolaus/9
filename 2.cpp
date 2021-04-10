#include "std_lib_facilities.h"

class Name_pairs
{
public:
    void read_names();
    void read_ages();
    void print();
    void sort();

private:
    vector<string> name;
    vector<double> age;
};

void Name_pairs::read_names()
{
    string s = "";
    cout << "Input a list of names (x - for stop):\n";
    while (true)
    {
        cin >> s;
        if (s == "x")
            break;
        name.push_back(s);
    }
}

void Name_pairs::read_ages()
{
    double d = 0;
    for (int i = 0; i < name.size(); i++)
    {
        cout << "Age of " << name[i] << " is ";
        cin >> d;
        age.push_back(d);
    }
}

void Name_pairs::print()
{
    for (int i = 0; i < name.size(); i++)
        cout << name[i] << " " << age[i] << endl;
}

void Name_pairs::sort()
{
    string s = "";
    int index = 0;
    bool flag = false;
    for (int i = 0; i < name.size(); i++)
    {
        s = name[i];
        for (int j = i + 1; j < name.size(); j++)
        {
            if (name[j] < s)
            {
                s = name[j];
                index = j;
                flag = true;
            }
        }
        if (flag)
        {
            string s_temp = name[i];
            name[i] = name[index];
            name[index] = s_temp;

            double age_temp = age[i];
            age[i] = age[index];
            age[index] = age_temp;

            flag = false;
        }
    }
}

int main()
{
    Name_pairs list;
    list.read_names();
    list.read_ages();
    list.sort();
    list.print();
}