#include<iostream>
#include<string>
#include<fstream>

using namespace std;

#define MIN(x,y) (y>=x)?(x):(y) 

long long file_data_count(string str) {
    long long cnt = 0, data_check;
    ifstream fin;
    fin.open(str);

    while (!fin.eof()) {
        fin >> data_check;
        cnt++;
    }

    fin.close();

    return cnt;

}

void read_file(string str, long long* read_input) {
    int cnt = 0;
    ifstream fin(str);

    while (!fin.eof()) {
        fin >> read_input[cnt++];
    }
    fin.close();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    long long** read_input = new long long* [8];
    long long Binary_Tree[15] = { 0 }, cnt[8] = { 0 }, sp = 0, fp = 0, winner_path[4] = { 0 }, winner = 0, left = 0, right = 0;

    for (long long i = 0; i < 8; ++i) {
        read_input[i] = new long long[file_data_count("input_" + to_string(i) + ".txt")];
        read_file("input_" + to_string(i) + ".txt", read_input[i]);
    }

    ofstream fout("merged_out.txt"); //merge_out.txt 파일 열기

    for (long long i = 0; i < 10; ++i) {
        sp = 7, fp = 15;

        for (int j = sp; j < fp; ++j) {
            Binary_Tree[j] = read_input[j - 7][cnt[j - 7]];
        }


        for (long long j = 0; j < 3; ++j) {
            for (long long pos = sp; pos < fp; pos += 2) {
                Binary_Tree[(pos - 1) / 2] = MIN(Binary_Tree[pos], Binary_Tree[pos + 1]);
            }
            fp = sp - 1;
            sp /= 2;
        }

        winner = Binary_Tree[0];
        left = 1, right = 2;

        for (long long j = 0; j < 3; j++) {
            if (Binary_Tree[left] == winner) {
                winner_path[2 - j] = left;
                right = (left + 1) * 2;
                left = left * 2 + 1;
            }
            else if (Binary_Tree[right] == winner) {
                winner_path[2 - j] = right;
                left = right * 2 + 1;
                right = (right + 1) * 2;
            }
        }

        cnt[winner_path[0] - 7]++;
        fout << winner << '\n';

        for (long long j = 0; j < 4; ++j) {
            fout << winner_path[j] << ' ';
        }
        fout << '\n';

    }

    fout.close();

    for (int i = 0;i < 8;++i) {
        delete[] read_input[i];
    }

    delete[] read_input;

    return 0;
}
