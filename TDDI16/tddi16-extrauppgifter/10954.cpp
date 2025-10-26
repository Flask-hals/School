#include <iostream>
#include <queue>

using namespace std;

int main() {
  int n;
  while (true) {
    priority_queue<int, vector<int>, greater<int>> pq;
    int tmp;
    int returnSum = 0;

    cin >> n;
    if (n == 0)
      break;

    while (pq.size() < n) {
      cin >> tmp;
      pq.push(tmp);
    }

    while (pq.size() != 1) {
      int first = pq.top();
      pq.pop();
      int second = pq.top();
      pq.pop();
      pq.push(first + second);
      returnSum += first + second;
    }

    cout << returnSum << endl;
  }
  return 0;
}