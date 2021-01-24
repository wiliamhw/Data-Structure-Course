#include <iostream>
#include <string>
#include <cstring>
#define max 10
using namespace std;

int size;
int xTrav[] = { 0, -1, 1, 0 }; // atas, kiri, kanan, bawah
int yTrav[] = {-1,  0, 0, 1};

bool convert(char);
bool valid(bool map[][max], int, int, bool vis[][max]);
int countIsland(bool map[][max]);
void DFS(bool map[][max], int, int, bool vis[][max]);
void printMap(bool arr[][max]);

int main(void)
{
    // Initialize map
    bool map[max][max];
    memset(map, false, sizeof(map));

    // Get input
    int lim = 12; // Panjangan
    int X = 0, Y = 0;

    while (lim-- > 0) {
        X = 0;
        string input;
        getline(cin, input);

        // Insert each number in string input
        for (char word : input) {
            if (isdigit(word)) {
                map[Y][X] = convert(word);
                X++;
            }
        }
        Y++;

        // Loop limit = lebar map (X)
        if (lim == 11) {
            lim = X - 1;
            size = X;
        }
    }

    int count = countIsland(map);
    cout << count << endl;

    return 0;
}

void DFS(bool map[][max], int y, int x, bool vis[][max])
{ 
    vis[y][x] = true; 
  
    // Traverse each adjacent side
    for (int i = 0; i < 4; i++) {
        if (valid(map, y + yTrav[i], x + xTrav[i], vis)) {
            DFS(map, y + yTrav[i], x + xTrav[i], vis);
        }
    }
} 

int countIsland(bool map[][max]) 
{ 
    bool vis[max][max]; 
    memset(vis, false, sizeof(vis)); 
  
    int count = 0; 
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (map[i][j] && !vis[i][j]) { 
                DFS(map, i, j, vis);
                count++;
                // printMap(vis);
            } 
        }
    }
    return count; 
} 

void printMap(bool arr[][max])
{
    cout << endl;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}

bool valid(bool map[][max], int y, int x, bool vis[][max])
{
    if (0 <= x && x < size && 0 <= y && y < size && !vis[y][x] && map[y][x])
    {
        return true;
    }
    else return false;
}

bool convert(char c)
{
    if (c == '1')
        return true;
    else
        return false;
}