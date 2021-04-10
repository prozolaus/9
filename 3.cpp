#include "std_lib_facilities.h"

class Name_pairs
{
public:
    void read_names();
    void read_ages();
    void sort();
    vector<string> get_names() { return name; }
    vector<double> get_ages() { return age; }

private:
    vector<string> name;
    vector<double> age;
};
//----------------------------------------------------------------------
bool operator==(Name_pairs &np1, Name_pairs &np2)
{
    return np1.get_names() == np2.get_names() && np1.get_ages() == np2.get_ages();
}

bool operator!=(Name_pairs &np1, Name_pairs &np2)
{
    return !(np1 == np2);
}
//-----------------------------------------------------------------------
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
//-----------------------------------------------------------------
ostream &operator<<(ostream &os, Name_pairs &np)
{
    os << endl;
    for (int i = 0; i < np.get_names().size(); i++)
        os << np.get_names()[i] << " is " << np.get_ages()[i] << " years old" << endl;
    return os;
}
//-------------------------------------------------------------------
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
    Name_pairs list1;
    list1.read_names();
    list1.read_ages();
    list1.sort();
    cout << "\nMetallica members: " << list1;

    Name_pairs list2;
    list2.read_names();
    list2.read_ages();
    list2.sort();
    if (list1 == list2)
        cout << "These lists are the same.\n";
    else
        cout << "These lists are not the same.\n";
}