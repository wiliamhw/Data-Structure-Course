#include <bits/stdc++.h>
using namespace std;

bool comparator(string a, string b) {
    return a < b;
}

vector<string> sort_bjir(vector<string> w) {
    int n = w.size();
    sort(w.begin(), w.end(), comparator);
    return w;
}

int main(void) {
    int s;
    cin >> s;
    getchar();

    for (int i = 0; i < s; i++) {
        vector<string> words;
        string in;
        getline(cin, in);
        
        // Pecah kalimat
        string tmp = "";
        for (auto x : in) {
            if (x == ' ') {
                words.push_back(tmp);
                tmp = "";
            }
            else {
                tmp = tmp + x;
            }
        }
        words.push_back(tmp);
        words = sort_bjir(words);

        // Print kata unik
        string prev = "";
        for (auto kata : words) {
            if (kata != prev) {
                cout << kata << " ";
                prev = kata;
            }
        }
        cout << endl;
    }
    return 0;
}