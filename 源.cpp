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
//cp�����ģ� ep������ 
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
// flag = 1, ����ת���õ���������
// flag = 2 ����ת���õ��������� 
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


// e�ǹ�Կ
// d��˽Կ

ll e, d, n;

ll gcd(ll a, ll b)  //�����Լ��
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

// 0���� 1�� 
ll isPrime(ll i) //�ж�i�Ƿ�������
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

ll myPow(ll a, ll b, ll n)  //��a^b mod n
{
    ll y;

    /*ʹ�ö�����ƽ���˷����� pow(a,b) % n*/
    y = 1;

    while (b != 0)
    {
        /*����b�е�ÿ��1���ۼ�y*/

        if (b & 1)
            y = (y * a) % n;

        /*����b�е�ÿһλ������a��ƽ��*/
        a = (a * a) % n;

        /*׼��b�е���һλ*/
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

ll ModularInverse(ll a, ll b)  //��ȡ(1/a)mod b�Ľ��
{
    ll d, x, y;
    extgcd(a, b, d, x, y);
    return d == 1 ? (x + b) % b : -1;

}

void KeyGeneration()  //��ȡ��Կ��Կ
{
    ll p, q;
    ll phi_n;

    p = 43; q = 59, e = 13;
    n = p * q;
    phi_n = (p - 1) * (q - 1);



    d = ModularInverse(e, phi_n);
}

// һλһλ��������ܵĽ�� 
ll Encryption(ll value)  //����
{
    ll cipher;
    cipher = myPow(value, e, n);
    cout << "���ܵõ�������=" << cipher << "\t���ܵõ�����ĸ=";
    toChar(cipher, 2);
    return cipher;
}

// һλһλ������� �ܵĽ�� 
void Decryption(ll value)  //����
{
    ll decipher;
    decipher = myPow(value, d, n);
    cout << "���ܵõ�������=" << decipher << "\t���ܵõ�����ĸ=";
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
        cout << "���ܵ�����=" << st[i] << st[i + 1] << endl;
        ll num = getNum(st[i], st[i + 1]);
        cout << "���Ķ�Ӧ������" << num << endl;
        ll de = Encryption(num);
        Decryption(de);
    }
    cp[lcp] = '\0';
    ep[lep] = '\0';
    cout << "���ܵĽ��Ϊ" << cp << endl;
    cout << "���ܵĽ��Ϊ:" << ep << endl;


    return 0;
}

