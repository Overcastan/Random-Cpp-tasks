#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int alphabet_size = 26;

void compare_with_the_beginning(string &s, vector <int> &z, int start_pos, int cur_pos, int &l, int &r)
{
    for(int j = start_pos; j < s.size() && s[j] == s[j - cur_pos]; j++)
        z[cur_pos]++;

    if(z[cur_pos] > start_pos - cur_pos)
    {
        l = cur_pos;
        r = cur_pos + z[cur_pos] - 1;
    }
}

void z_func(string &s, vector <int> &z)
{
    z[0] = s.size();
    int l = 0, r = 0;

    for(int i = 1; i < s.size(); i++)
    {
        if(i > r)
        {
            z[i] = 0;
            compare_with_the_beginning(s, z, i, i, l, r);
        }
        else
        {
            if(i + z[i - l] - 1 < r)
            {
                z[i] = z[i - l];
            }
            else
            {
                z[i] = r - i + 1;
                compare_with_the_beginning(s, z, r + 1, i, l ,r);
            }
        }
    }
}

void prefix_func(string &str, vector <int> &prefix)
{
    prefix[0] = 0;

    for(int i = 1; i < prefix.size(); i++)
    {
        int l = prefix[i - 1];

        while(str[l] != str[i] && l > 0)
            l = prefix[l - 1];

        if(str[l] == str[i])
            prefix[i] = l + 1;
        else prefix[i] = 0;
    }
}

void prefix_to_str(string &str, const vector <int> &prefix)
{
    for(int i = 1; i < str.size(); i++)
    {
        if(prefix[i] == 0)
        {
            vector <bool> alphabet(alphabet_size, false);
            alphabet[0] = true;

            int l = prefix[i - 1];

            while(l > 0)
            {
                alphabet[str[l] - 'a'] = true;
                l = prefix[l - 1];
            }

            for(int j = 1; j < alphabet_size; j++)
                if(!alphabet[j])
                {
                    str[i] = 'a' + j;
                    break;
                }
        }
        else
        {
            str[i] = str[prefix[i] - 1];
        }
    }
}

void z_to_str(string &s, const vector <int> &z)
{
    int r = 0;
    vector <int> l(1, 0);

    for(int i = 1; i < s.size(); i++)
    {
        if(z[i] > 0)
        {
            for(int j = 0; j < z[i]; j++)
                s[i + j] = s[j];

            if(i + z[i] - 1 > r)
            {
                l.clear();
                l.push_back(i);
                r = i + z[i] - 1;
            }

            else if(i + z[i] - 1 == r)
                l.push_back(i);
        }

        else
        {
            if(i == r + 1)
            {
                vector <bool> alphabet(alphabet_size, false);
                alphabet[0] = true;

                for(int k : l)
                {
                    alphabet[s[r - k + 1] - 'a'] = true;
                }

                for(int j = 1; j < alphabet_size; j++)
                {
                    if(!alphabet[j])
                    {
                        s[i] = 'a' + j;
                        break;
                    }
                }
            }
            else if(i > r + 1)
            {
                s[i] = 'b';
            }
        }
    }
}

void z_to_prefix(vector <int> &z)
{
    string s(z.size(), 'a');
    z_to_str(s, z);
    prefix_func(s, z);
}

void prefix_to_z(vector <int> &prefix)
{
    string s(prefix.size(), 'a');
    prefix_to_str(s, prefix);
    z_func(s, prefix);
}

int main()
{
    return 0;
}