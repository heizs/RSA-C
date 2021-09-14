#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include<string.h>
#include <math.h>
#include<algorithm>
using namespace std;
typedef long long ll;

char map[30] = {
    'a', 'b', 'c', 'd', 'e','f','g',
    'h', 'i', 'j', 'k', 'l', 'm', 'n',
    'o', 'p', 'q', 'r', 's', 't',
    'u', 'v', 'w', 'x', 'y', 'z'
};
//cp存密文， ep存明文 
char cp[1000], ep[1000];
int lcp, lep;

ll getNum(char a, char b) {
    int aa, bb;
    for (int i = 0; i < 30; i++) {
        if (map[i] == a) {
            aa = i;
        }
        if (map[i] == b) {
            bb = i;
        }
    }
    return aa * 100 + bb;
}
// flag = 1, 解密转换得到的是明文
// flag = 2 加密转换得到的是密文 
void toChar(ll num, int flag = 1) {
    int a = num / 100;
    int b = num % 100;
    a %= 26;
    b %= 26;
    cout << map[a] << map[b] << " " << endl;
    if (flag == 1) {
        ep[lep++] = map[a];
        ep[lep++] = map[b];
    }
    else if (flag == 2) {
        cp[lcp++] = map[a];
        cp[lcp++] = map[b];
    }
}


// e是公钥
// d是私钥

ll e, d, n;

ll gcd(ll a, ll b)  //求最大公约数
{
    ll c = 0;
    if (a < b) swap(a, b);
    c = b;
    do
    {
        b = c;
        c = a % b;
        a = b;
    } while (c != 0);
    return b;
}

// 0不是 1是 
ll isPrime(ll i) //判断i是否是素数
{
    ll flag = 0;
    for (ll a = 2; a < i; a++)
    {
        if (i % a == 0)
        {
            flag = 1;
            break;
        }
    }
    if (flag == 1) return 0;
    else return 1;

}

ll myPow(ll a, ll b, ll n)  //求a^b mod n
{
    ll y;

    /*使用二进制平方乘法计算 pow(a,b) % n*/
    y = 1;

    while (b != 0)
    {
        /*对于b中的每个1，累加y*/

        if (b & 1)
            y = (y * a) % n;

        /*对于b中的每一位，计算a的平方*/
        a = (a * a) % n;

        /*准备b中的下一位*/
        b = b >> 1;
    }

    return y;

}

void extgcd(ll a, ll b, ll& d, ll& x, ll& y)
{
    if (!b)
    {
        d = a;
        x = 1;
        y = 0;
    }
    else
    {
        extgcd(b, a % b, d, y, x);
        y -= x * (a / b);
    }
}

ll ModularInverse(ll a, ll b)  //获取(1/a)mod b的结果
{
    ll d, x, y;
    extgcd(a, b, d, x, y);
    return d == 1 ? (x + b) % b : -1;

}

void KeyGeneration()  //获取公钥密钥
{
    ll p, q;
    ll phi_n;

    p = 43; q = 59, e = 13;
    n = p * q;
    phi_n = (p - 1) * (q - 1);



    d = ModularInverse(e, phi_n);
}

// 一位一位地输出加密的结果 
ll Encryption(ll value)  //加密
{
    ll cipher;
    cipher = myPow(value, e, n);
    cout << "加密得到的数字=" << cipher << "\t加密得到的字母=";
    toChar(cipher, 2);
    return cipher;
}

// 一位一位地输出解 密的结果 
void Decryption(ll value)  //解密
{
    ll decipher;
    decipher = myPow(value, d, n);
    cout << "解密得到的数字=" << decipher << "\t解密得到的字母=";
    toChar(decipher, 1);
}
int main()
{
    lcp = 0, lep = 0;
    char st[] = "cybergreatwall";
    KeyGeneration();
    cout << "e=" << e << " d=" << d << " n=" << n << endl;
    int len = strlen(st);
    //	cout<<st<<" "<<len<<endl;
    for (int i = 0; i < len; i += 2) {
        cout << "加密的明文=" << st[i] << st[i + 1] << endl;
        ll num = getNum(st[i], st[i + 1]);
        cout << "明文对应的数字" << num << endl;
        ll de = Encryption(num);
        Decryption(de);
    }
    cp[lcp] = '\0';
    ep[lep] = '\0';
    cout << "加密的结果为" << cp << endl;
    cout << "解密的结果为:" << ep << endl;


    return 0;
}

