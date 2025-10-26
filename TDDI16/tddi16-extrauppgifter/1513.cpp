#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

void updateBIT(vector<int> &BIT, int pos, int val) {
  while (pos < BIT.size()) {
    BIT[pos] += val;
    pos += pos & -pos;
  }
}

int checkM(vector<int> &BIT, int pos) {
  int numberOfMovies = 0;
  while (pos > 0) {
    numberOfMovies += BIT[pos];
    pos -= pos & -pos;
  }
  return numberOfMovies - 1;
}

int main() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    unordered_map<int, int> um;
    int s;
    int m;
    cin >> s >> m;
    vector<int> BIT(s + m + 1, 0);
    int top = m;

    for (int i = 1; i <= s; i++) {
      um[i] = i + m;
      updateBIT(BIT, um[i], 1);
    }

    string sum = "";
    for (int i = 1; i <= m; i++) {
      int tmp;
      cin >> tmp;
      sum += to_string(checkM(BIT, um[tmp]));
      if (i != m)
        sum += " ";
      updateBIT(BIT, um[tmp], -1);
      updateBIT(BIT, top, 1);
      um[tmp] = top;
      top--;
    }
    cout << sum << endl;
  }

  return 0;
}