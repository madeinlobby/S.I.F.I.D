#include <iostream>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;

struct node {
    int value;
    int frequency;

    node *c0;
    node *c1;

    node(int value, int frequency) : value(value), frequency(frequency), c0(nullptr), c1(nullptr) {}
    node(int frequency, node *c0, node *c1) : value(0), frequency(frequency), c0(c0), c1(c1) {}
};
struct comparator {
    bool operator()(const node *a, const node *b) {
        return a->frequency > b->frequency;
    }
};

const int BUFFER_SIZE = 2;
const int MAX_LENGTH = 16777217;
priority_queue<node *, vector<node *>, comparator> pq;
int frequency[MAX_LENGTH];
string codes[MAX_LENGTH];

int lastBufferSize=0;

int pow(int a, int b) {
    int t = 1;
    for (int i = 0; i < b; i++) {
        t *= a;
    }
    return t;
}
string getBytes(ifstream *ifs) {
    string retVal = "";
    for (int i = 0; i < BUFFER_SIZE; i++) {
        char byte = 0;
        if ((*ifs).peek() == EOF)break;
        (*ifs) >> byte;
        retVal += byte;
    }
    return retVal;
}
int parseInt(string s) {
    int retVal = 0;
    for (int i = 0; i < s.size(); i++) {
        retVal += s[i] * pow(2, 8 * (s.size() - i - 1));
    }
    return retVal;
}

void setFrequency(string path) {
    ifstream ifs;
    ifs.open(path, ios::binary | ios::in);

    string bytes;
    do {
        bytes = getBytes(&ifs);
        if (bytes.size() == 0)break;
        frequency[parseInt(bytes)]++;

    } while (bytes.size() >= BUFFER_SIZE);
    ifs.close();
}
void buildMinHeap() {
    for (int i = 0; i < MAX_LENGTH; i++) {
        if (frequency[i]) {
            node *newNode = new node(i, frequency[i]);
            pq.push(newNode);
        }
    }

}
node *huffman() {
    cerr<<"DDD";
    while (pq.size() > 1) {
        node *n0 = pq.top();
        pq.pop();
        node *n1 = pq.top();
        pq.pop();
        pq.push(new node(n0->frequency + n1->frequency, n0, n1));
    }
    return pq.top();
}
void setCodes(node *root, string code) {
    codes[root->value] = code;
    if (root->c0 == nullptr && root->c1 == nullptr) {
        return;
    }
    if (root->c0)
        setCodes(root->c0, code + '0');
    if (root->c1)
        setCodes(root->c1, code + '1');
    return;
}
void compress(string input_path, string output_path) {
    ofstream fout;
    fout.open(output_path, ios::binary | ios::out);
    ifstream fin;
    fin.open(input_path, ios::binary | ios::in);

    string bytes;
    char byte = 0;
    int length = 0;
    do {
        bytes = getBytes(&fin);
        int index = parseInt(bytes);
        string code = codes[index];

        for (int i = 0; i < code.size(); i++) {
            byte *= 2;
            byte += (code[i] == '1');
            length++;
            if (length == 8) {
                fout << byte;
                byte = length = 0;
            }
        }

    } while (bytes.size() >= BUFFER_SIZE);

    lastBufferSize=length;
    if(length){
        cout<<"wtf!";
//        while(length++ < 8){
//            byte*=2;
//        }
        fout << byte;
    }
    fin.close();
    fout.close();

}
int decimal(string binary){
    int retVal=0;
    for(char i : binary){
        retVal=retVal*2+(i=='1');
    }
    return retVal;
}
void buildTable(string path) {
    ofstream fout;
    fout.open(path, ios::binary | ios::out);
    fout<<lastBufferSize<<'\n';
    for (int i = 0; i < MAX_LENGTH; i++) {
        if (frequency[i]) {
            fout << i << " " <<codes[i] << '\n';
        }
    }
}

int main(int ignored, char **path) {
    string input_path = "in.txt";
    string output_path = "out.txt";
    string table_path = "table.txt";

    cout<<"starting the huffman compression algorithm process\n";

    cout<<"setting the frequencies\n.\n.\n.\n";
    setFrequency(input_path);
    cout<<"done!\n\n";

    cout<<"building the meanHeap\n.\n.\n.\n";
    buildMinHeap();
    cout<<"done!\n\n";

    cout<<"setting the codes\n.\n.\n.\n";
    setCodes(huffman(), "");
    cout<<"done!\n\n";

    cout<<"starting the compression\n.\n.\n.\n";
    compress(input_path, output_path);
    cout<<"done!\n\n";

    cout<<"building the table\n.\n.\n.\n";
    buildTable(table_path);
    cout<<"done!\n\n";

    return 0;
}