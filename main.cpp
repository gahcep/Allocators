#include <cstdio>
#include <iostream>
#include <vector>
#include <list>
#include "simple_allocator.hpp"

using namespace std;

int main()
{
    /*  Vector on MS:       "aux object" (8) + Nodes (4)
     *  Vector on CentOS:   Nodes (4)
     */

    cout << "Constructing Vector" << endl;

    vector<int, simple_allocator<int> > v;

    cout << endl << "l.push_back(1):" << endl;
    v.push_back(1);

    cout << endl << "l.push_back(12):" << endl;
    v.push_back(12);
    cout << endl;

    for (vector<int, simple_allocator<int> >::const_iterator i = v.begin(); i != v.end(); ++i) {
	cout << "Element: " << *i << endl;
    }

    cout << "Destroying Vector" << endl;


    /*  List on MS:      Sentinel (12) + "aux object" (8) + Nodes (12)
     *  List on CentOS:  Nodes (24)
     */

    cout << "Constructing List" << endl;

    list<int, simple_allocator<int> > l;

    cout << endl << "l.push_back(1729):" << endl;
    l.push_back(1729);

    cout << endl << "l.push_back(2161):" << endl;
    l.push_back(2161);
    cout << endl;

    for (list<int, simple_allocator<int> >::const_iterator i = l.begin(); i != l.end(); ++i) {
        cout << "Element: " << *i << endl;
    }

    cout << "Destroying List" << endl;
}
