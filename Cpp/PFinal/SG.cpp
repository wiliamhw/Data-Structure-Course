#include <iostream>
#include <map>
#include <utility>
#include <vector>
#include <sstream>
using namespace std;

class Data {
    private: 
        map<int, string, greater<int>> master;  // Format: ID, nama
        map<int, string, greater<int>> feature;
        map<int, string, greater<int>> *cBranch; // default
        int mID[2];
        int cBr;
        int cID;

    public:
        Data();
        ~Data();
        void commit(string);
        void reset(int);
        void log();
        void checkout(int);
        void status();
        void branch(string);
        void sync();
};

int main() {
    Data data = Data();
    vector<string> words;
    int num, tmp;
    string in, temp, prev;

    while (1) {
        // Get input
        words.clear();
        num = -1;
        getline(cin, in);
        
        stringstream ss(in);
        
        while (!ss.eof()) {
            ss >> skipws >> temp;
            if (temp == prev) break;
            prev = temp;
            
            if (stringstream(temp) >> tmp)
                num = tmp;
            else
                words.push_back(temp);
        }

        // Do command
        if (words.size() == 1) {
            if (num == -1) {
                if (words[0] == "log") data.log();
                else if (words[0] == "status") data.status();
                else if (words[0] == "sync") data.sync();
                else if (words[0] == "quit") break;
                else return 1;
            }
            else {
                if (words[0] == "reset") data.reset(num);
                else if (words[0] == "checkout") data.checkout(num);
                else return 2;
            }    
        }
        else if (words.size() == 2) {
            if (words[0] == "commit") data.commit(words[1]);
            else if (words[0] == "branch") data.branch(words[1]);
            else return 3;
        }
    }
    return 0;
}

Data::Data() {
    cBranch = &master;
    for (int i = 0; i < 2; i++) {
        mID[i] = -1;
    }
    cBr = 0;
}

Data::~Data() {
    master.clear();
    feature.clear();
    cBranch = NULL;
}

void Data::commit(string nama) {
    mID[cBr]++;
    cID = mID[cBr];
    cBranch->insert(pair<int, string>(cID, nama));
}

void Data::reset(int ID) {
    auto it = cBranch->find(ID);
    cBranch->erase(cBranch->begin(), it);
    cID = ID;
    cout << "Anda berada di commit " << (*cBranch)[cID] << endl;
}

void Data::log() {
    if (!cBranch->empty()) {
        for (auto x : *cBranch) {
            cout << x.first << endl;
            cout << x.second << endl;
        }
    }
    else cout << endl;
}

void Data::checkout(int ID) {
    auto it = cBranch->find(ID);
    if (it != cBranch->end())  { // ID exist in commit
        cID = ID;
        cout << "Anda berada di commit " << (*cBranch)[cID] << endl;
    }
    else
        cout << "ID tidak ditemukan" << endl;
}

void Data::status() {
    cout << "Anda berada di commit " << (*cBranch)[cID] << endl;
}

void Data::branch(string nama) {
    if (nama == "master") {
        cBranch = &master;
        cBr = 0; 
    }
    else {
        cBranch = &feature;
        cBr = 1;
    }
    cID = mID[cBr]; // suspect
}

void Data::sync() {
    map<int, string, greater<int>> *oBranch = NULL;
    if (cBr == 0) oBranch = &feature;
    else oBranch = &master;

    auto cP = cBranch->rbegin();
    auto oP = oBranch->rbegin();

    while (cP != cBranch->rend() && oP != oBranch->rend()) {
        if (cP->second == oP->second) {
            cP++;
            oP++;
        }
        else break;
    }

    while (oP != oBranch->rend()) {
        oP = decltype(oP)(oBranch->erase(next(oP).base() ));
    }
}
