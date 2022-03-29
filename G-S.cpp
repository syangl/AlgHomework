#include <iostream>
using namespace std;

class Person
{
public:
    int id;
    int list[31];
    int comp;
    Person()
    {
        for (int i = 0; i < 31; i++)
        {
            list[i] = 0;
        }
    }
};

bool select(int n, Person men[], int& mid)
{
    for (int i = 1; i <= n; i++)
    {
        if (men[i].comp == 0 && men[i].list[n] != 0)
        {
            mid = men[i].id;
            return 1;
        }
    }
    return 0;
}

int main()
{
    int n;
    cin >> n;
    Person* men = new Person[n+1], * women = new Person[n+1];

    for (int i = 1; i <= n; i++)
    {
        men[i].id = i;
        men[i].comp = 0;
        for (int j = 1; j <= n; j++)
        {
            cin >> men[i].list[j];
        }
    }

    for (int i = 1; i <= n; i++)
    {
        women[i].id = i;
        women[i].comp = 0;
        for (int j = 1; j <= n; j++)
        {
            cin >> women[i].list[j];
        }
    }

    int mid = 0, wid = 0;
    while (select(n, men, mid))
    {
        for (int i = 1; i <= n; i++)
        {
            if (men[mid].list[i] != 0)
            {
                wid = men[mid].list[i];
                men[mid].list[i] = 0;
                break;
            }
        }
		if (women[wid].comp == 0)
		{
			women[wid].comp = men[mid].id;
			men[mid].comp = women[wid].id;
		}
		else
		{
			for (int j = 1; j <= n; j++)
			{
				if (women[wid].comp == women[wid].list[j])
				{
					break;
				}
				if (men[mid].id == women[wid].list[j])
				{
					men[women[wid].comp].comp = 0;
					women[wid].comp = mid;
					men[mid].comp = wid;
				}
			}
		}

    }

    for (int i = 1; i <= n; i++)
    {
        cout << men[i].comp << " ";
    }

    return 0;
}