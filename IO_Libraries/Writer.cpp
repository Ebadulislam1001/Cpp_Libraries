#include <iostream>
#include <vector>
using namespace std;

void put_vector_int(vector<int> vec)
{
    printf("[ ");
    for (int i = 0; i < vec.size(); i++)
    {
        printf("%d, ", vec[i]);
    }
    printf("]\n");
}
void put_vector_vector_int(vector<vector<int>> vec)
{
    printf("[");
    for (int i = 0; i < vec.size(); i++)
    {
        printf("\n\t");
        put_vector_int(vec[i]);
    }
    printf("\n]");
}