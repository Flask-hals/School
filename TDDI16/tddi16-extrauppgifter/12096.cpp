#include <iostream>
#include <stack>
#include <set>
#include <map>

using namespace std;

int main()
{
    int T = 0;
    cin >> T;
    for (int i = 0; i < T; i++)
    {
        stack<string> s;
        map<set<int>, int> m;

        int N = 0;
        cin >> N;
        for (int i = 0; i < N; i++)
        {
            string operation;
            cin >> operation;

            if (operation == "PUSH")
            {
                set<int> emptySet;

                int id;
                if (m.count(emptySet))
                    cout << "ingen" << endl;
                else
                {
                    cout << "lägg till" << endl;
                    id = 1;
                    
                }


            }
            else if (operation == "DUP")
            {
                
            }
            else if (operation == "ADD")
            {
                
            }
            else if (operation == "UNION")
            {
                
            }
            else if (operation == "INTERSECT")
            {
                
            }

        }
    }
    return 0;
}

/*
    2
9
PUSH
DUP
ADD
PUSH
ADD
DUP
ADD
DUP
UNION
5
PUSH
PUSH
ADD
PUSH
INTERSECT
*/