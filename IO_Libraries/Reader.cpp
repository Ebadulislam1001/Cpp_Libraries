#include <iostream>
#include <vector>
using namespace std;

int get_int(string prompt = "")
{
    printf("%s", prompt.c_str());
    int input;
    cin >> input;
    return input;
}
double get_double(string prompt = "")
{
    printf("%s", prompt.c_str());
    double input;
    cin >> input;
    return input;
}
char get_char(string prompt = "")
{
    printf("%s", prompt.c_str());
    char input;
    cin >> input;
    return input;
}
string get_string(string prompt = "")
{
    printf("%s", prompt.c_str());
    string input;
    cin >> input;
    return input;
}
vector<int> get_vector_int(int size, string prompt = "")
{
    printf("%s", prompt.c_str());
    vector<int> input;
    for (int i = 0; i < size; i++)
    {
        int temp;
        cin >> temp;
        input.push_back(temp);
    }
    return input;
}
vector<double> get_vector_double(int size, string prompt = "")
{
    printf("%s", prompt.c_str());
    vector<double> input;
    for (int i = 0; i < size; i++)
    {
        double temp;
        cin >> temp;
        input.push_back(temp);
    }
    return input;
}