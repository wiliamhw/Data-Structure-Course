#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;
typedef pair<int, int> pii; // waktu, id

pii getMin (vector<pii> &Av, vector<pii> &Ev) {
    if (!Av.empty() && Av.front().first < Ev.front().first) 
        return make_pair(0, Av.front().second);
    else
        return make_pair(1, Ev.front().second);
}

int main() {
    bool *cekA = new bool[1001];
    bool *cekE = new bool[1001];
    bool tes;
    vector<pii> Av;
    vector<pii> Ev;
    vector<int> parkiran;
    int N, K, A, E;

    while (1) {
        cin >> N >> K;
        if (N == 0 && K == 0) break;
        if (!Av.empty()) Av.clear();
        if (!Ev.empty()) Ev.clear();
        if (!parkiran.empty()) parkiran.clear();
        fill(cekA, cekA + 1001, false);
        fill(cekE, cekE + 1001, false);
        if (!tes) tes = true;

        for (int i = 0; i < N; i++) {
            cin >> A >> E;
            if (A >= E) tes = false;
            if (cekA[A] || cekE[E]) continue;

            Av.push_back(make_pair(A, i));
            Ev.push_back(make_pair(E, i));
            cekA[A] = true;
            cekE[E] = true; 
        }

        if (tes) {
            sort(Av.begin(), Av.end());
            sort(Ev.begin(), Ev.end());

            while (!Ev.empty()) {
                pii front = getMin(Av, Ev); // sektor, id
                if (front.first == 0) { // sektor == A
                    Av.erase(Av.begin());
                    parkiran.insert(parkiran.begin(), front.second);
                    if (parkiran.size() > K) {
                        tes = false;
                        break;
                    }
                }
                else { // sektor = B
                    Ev.erase(Ev.begin());
                    int id = parkiran.front();
                    parkiran.erase(parkiran.begin());
                    if (id != front.second) {
                        tes = false;
                        break;
                    }
                }
            }
        }
        if (!tes) cout << "Gak Bisa Woi" << endl;
        else cout << "Lancar Jaya" << endl;
    }
    delete[] cekA;
    delete[] cekE;
    return 0;
}