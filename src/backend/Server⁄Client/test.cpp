#include <bits/stdc++.h>

using namespace std;

int main() {

  vector<int> V;

  ifstream in("ss.png", ios::binary);
  ofstream out("ssscopy.png", ios::binary);
  if (in.is_open() && out.is_open()) {
    while (!in.eof()) {
      V.push_back(in.get());
    }
  }

  for (auto i : V)
    out.put(i);
  in.close();
  out.close();
}