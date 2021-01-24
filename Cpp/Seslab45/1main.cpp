#include <iostream>
#include <string>

// eksternal definition
#include "Player.h"

using namespace std;

int main(int argc, char const *argv[])
{
    char nama[10];
    cout << "Nama: ";
    cin >> nama;

    Player* playerObject = new Player(nama);
    playerObject->display();

    cout << "get name: "<< playerObject->getName() << endl;

    cout << "rubah nama" << endl;
    playerObject->setName("Tanjiro");
    playerObject->display();
    return 0;
}