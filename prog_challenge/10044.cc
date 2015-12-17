#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <map>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <cstring>
using namespace std;

/// BFS to search

map<string, map<string, bool> > co_author;
map<string, int> erdos_num;

void parsePaper(string &str)
{
    string names = str.substr(0, str.find(":"));
    vector<string> writes;

    size_t start, cur, end;
    bool fullname = false;

    cur = 0, start = 0;
    while (cur != string::npos) {
        cur = names.find(",", cur+1);
        if (fullname) {
            end = cur-1;
            while (names[end] == ' ') end--;
            writes.push_back(names.substr(start, end-start+1));
            start = cur+2;
        }
        fullname = !fullname;
    }

    for (size_t i = 0; i < writes.size(); i++)
        for (size_t j = 0; j < writes.size(); j++)
            if (writes[i] != writes[j])
                co_author[writes[i]][writes[j]] = true;

    return ;
}

void countErdosNum(const char* name)
{
    queue<const char*> visit;
    const char* cur_name;
    int level = 1;
    visit.push(name);

    while (!visit.empty()) {
        visit.push(" ");
        while (1) {
            cur_name = visit.front();
            visit.pop();

            if (strcmp(cur_name, " ") == 0) {
                level++;
                break;
            }

            for (map<string,bool>::const_iterator it = co_author[cur_name].begin();
                 it != co_author[cur_name].end(); it++) {
                if (erdos_num[it->first] == 0 || erdos_num[it->first] > level) {
                    erdos_num[it->first] = level;
                    visit.push(it->first.c_str());
                }
            }
        }
    }
}

int main(int argc, char *argv[])
{
    int cases, i;
    int p, n, j;
    string str;

    cin >> cases;
    for (i = 0; i < cases; i++) {
        erdos_num.erase(erdos_num.begin(), erdos_num.end());
        co_author.erase(co_author.begin(), co_author.end());

        cin >> p >> n;
        cin.ignore(10, '\n');

        for (j = 0; j < p; j++) {
            getline(cin, str);
            parsePaper(str);
        }

        countErdosNum("Erdos, P.");

        cout << "Scenario " << dec << i+1 << endl;
        for (j = 0; j < n; j++) {
            getline(cin, str);
            size_t pos = str.find('\r');
            if (pos != string::npos)
                str[pos] = '\0';

            if (erdos_num[str.c_str()] == 0)
                cout << str.c_str() << " infinity" << endl;
            else
                cout << str.c_str() << " " << erdos_num[str.c_str()] << endl;
        }
    }

    return 0;
}
