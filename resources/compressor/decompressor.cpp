#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

const int BUFFER_SIZE = 2;
const int MAX_LENGTH = 16777217;


int parseInt(string s) {
    int ret = 0;
    for (char c: s) {
        ret *= 10;
        ret += c - '0';
    }
    return ret;
}

int main(int n, char **args) {

    ifstream ifs;
    ifs.open("../test.txt", ios::binary);
    int codes[1677721] = {0};
    string line;
    ifs >> line;
    int last = parseInt(line);
    while (ifs.peek() != EOF) {
        ifs >> line;
        int first = parseInt(line);
        ifs >> line;
        int second = parseInt(line);
        cout << first << " " << second << endl;
        codes[second] = first;
    }
    ifstream ifs1;
    ifs1.open("../test1.txt");
    ofstream ofs;

    ofs.open("../new.txt");
    char c;
    ifs1 >> c;
    while (ifs1.peek() != EOF) {


        int num = (int) c;
        cout << "num : " << num << endl;
        string res = "";
        int f = 0;
        for (int j = 7; j > -1; j--) {
            f *= 2;
            f += (int) (num / pow(2, j)) % 2;
            cout << f;
            if (codes[f]) {
                cout << " " << codes[f] << endl;
                int g = codes[f];
                string l = "";
                while (g) {
                    char h = static_cast<char>(g % 256);
                    cout << h << " " << endl;
                    l = h + l;
                    g /= 256;
                }
                res = res + l;
                cout << "res :" << res << endl;
                f = 0;
            }

        }

        ofs << res;
        ifs1 >> c;
    }

    int num = (int) c;
    cout << "num : " << num << endl;
    string res = "";
    int f = 0;
    for (int j = last - 1; j > -1; j--) {
        f *= 2;
        f += (int) (num / pow(2, j)) % 2;
        cout << f;
        if (codes[f]) {
            cout << " " << codes[f] << endl;
            int g = codes[f];
            string l = "";
            for (int i = 0; i < BUFFER_SIZE; ++i) {
                char h = g % 256;
                cout << h << " " << endl;
                l = h + l;
                g /= 256;
            }
            res = res + l;
            cout << "res :" << res << endl;
            f = 0;
        }

    }

    ofs << res;


    return 0;
}