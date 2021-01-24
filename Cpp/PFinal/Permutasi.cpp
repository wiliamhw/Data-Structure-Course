#include <iostream>
#include <ext/pb_ds/assoc_container.hpp> //perhatikan header ini harus disertakan
#include <ext/pb_ds/tree_policy.hpp> //perhatikan header ini harus disertakan
#include <stdlib.h>
#include <stdio.h>
 
#define mod 1000000007
 
using namespace std;
using namespace __gnu_pbds; //struktur data ini berada pada class __gnu_pbds
 
unsigned long long factorial[100050];
 
typedef tree<
int, //bisa diganti sesuai tipe data yang dibutuhkan
null_type,
less<int>, //jika ingin elemen tidak unik bisa menggunakan less_equal
rb_tree_tag,
tree_order_statistics_node_update> AVL; //karena namanya yang panjang, sebaiknya menggunakan typedef
                                        //menggunakan nama AVL karena memiliki fungsi-fungsi yang ada pada AVL Tree
 
void getFact (int n) {
    factorial[0] = 1;
    factorial[1] = 1;
    unsigned long long hasil = 1;
    for(unsigned long long i = 2; i <= n; i++) {
        factorial[i] = (i * factorial[i - 1]) % mod;
    }
}
 
int main() {
    AVL Data;
    int banyak, X, Y;
    cin >> banyak;

    int *data = new int[100005];
    unsigned long long hasil = 0;
    Y = banyak - 1;
    getFact(banyak);

    for (int i = 0; i < banyak; i++) {
        scanf("%d",&data[i]);
        Data.insert(data[i]);
    }
    for(int i = 0; i < banyak; i++) {
        X = Data.order_of_key(data[i]);
        Data.erase(data[i]);
        hasil = (hasil + X * factorial[Y]) % mod;
        Y--;
    }
    hasil = (hasil + 1) % mod;
    printf("%llu\n",hasil);

    delete[] data;
    return 0;
}