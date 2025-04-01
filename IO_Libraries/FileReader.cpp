#include<iostream>
#include<string>
using namespace std;
// This assumes that the file is already opened for reading

void skip_chars(FILE *&readPointer, int charCount)
{
    for (int i = 0; i < charCount; i += 1)
        fgetc(readPointer);
}
void skip_lines(FILE *&readPointer, int lineCount)
{
    for (int i = 0; i < lineCount; i += 1)
    {
        char line[1000];
        fscanf(readPointer, "%[^\n]", line);
        fgetc(readPointer);
    }
}
int read_int(FILE *&readPointer)
{
    int ans = 0;
    fscanf(readPointer, "%d", &ans);
    return ans;
}
string read_string(FILE *&readPointer, char delim)
{
    string ans = "";
    char ch;
    while (true)
    {
        fscanf(readPointer, "%c", &ch);
        if (ch == delim || ch == EOF)
            break;
        ans.push_back(ch);
    }
    return ans;
}
