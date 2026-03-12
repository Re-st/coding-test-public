#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int p, s, acc = 0;
    int acgt[4] = {0, 0, 0, 0}, acgtreq[4];
    string dna;
    cin >> s >> p >> dna;
    vector<int> dnaint;
    for (int i = 0; i < s; i++)
        switch (dna[i]) {
            case 'A': dnaint.push_back(0); break;
            case 'C': dnaint.push_back(1); break;
            case 'G': dnaint.push_back(2); break;
            case 'T': dnaint.push_back(3); break;
            default: break;
        }
    for (int i = 0; i < 4; i++) cin >> acgtreq[i];
    for (int i = 0; i < p - 1; i++) acgt[dnaint[i]]++;
    for (int a = 0, b = p - 1; b < s; a++, b++) {
        acgt[dnaint[b]]++;
        if (acgt[0] >= acgtreq[0] and acgt[1] >= acgtreq[1] and acgt[2] >= acgtreq[2] and acgt[3] >= acgtreq[3]) acc++;
        acgt[dnaint[a]]--;
    }
    cout << acc;
    return 0;
}