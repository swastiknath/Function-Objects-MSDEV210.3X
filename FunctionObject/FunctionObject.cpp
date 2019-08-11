#include<string>
#include <iostream>
#include <vector>
#include<algorithm>

using namespace std;

struct sortedStruct {
	int val;
	sortedStruct(int k) : val(k){}
	bool operator <(const sortedStruct& rhs)const {
		return (val < rhs.val);
	}
};

class sortedClass {
private:
	int val;
public:
	sortedClass(int x) : val(x) {
		cout << " Constructor 1 Called.....";
	}
	~sortedClass() {};
	int getVal() const { return val; }

	bool operator < (const sortedClass& sc) const {
		return (val < sc.getVal());
	}
};

class LessThan {
public:
	LessThan() {};
	~LessThan() {};
	bool operator () (const sortedClass & lhs, const sortedClass& rhs) const {
		return (lhs < rhs);
	}

	bool operator() (const sortedStruct& lhs, const sortedStruct& rhs) const {
		return (lhs < rhs);
	}
};

class greaterThan {
private:
	int X;
public:
	greaterThan(int cmp): X(cmp)
	{
		cout << "Consturctot 11";
	}
	~greaterThan(){}
	bool operator () (const sortedClass& z) const {
		return z.getVal() > X;
	}
	bool operator()(const sortedStruct& z) const {
		return z.val > X;
	}
};

template<class RandomAccessIterator>
void Randomise(RandomAccessIterator iterBegin, RandomAccessIterator iterEnd) {
	while (iterBegin < iterEnd) {
		std::iter_swap(iterBegin, iterBegin + rand() % (iterEnd - iterBegin));
		++iterBegin;
	}
}

int main(int argc, char * argv[])
{
	vector<sortedClass> vecSortClas;
	vector<sortedStruct> vecSortStru;

	for (int i = 0; i < 50; i++) {
		sortedClass sc(i);
		sortedStruct ss(i);
		vecSortClas.push_back(sc);
		vecSortStru.push_back(ss);
	}

	Randomise(vecSortClas.begin(), vecSortClas.end());
	Randomise(vecSortStru.begin(), vecSortStru.end());

	cout << "Vector of sorted class before sorting" << "\n\n";
	for (vector<sortedClass>::iterator it = vecSortClas.begin(); it != vecSortClas.end(); it++) 
	{
		cout << "Sorted Class Index is : " << distance(vecSortClas.begin(), it) << " has value  " << it->getVal() << endl;
	}

	std::sort(vecSortClas.begin(), vecSortClas.end(), LessThan());
	cout << endl << "Vector of sortedClass after sorting is: ";
	for (vector<sortedClass>::iterator it = vecSortClas.begin(); it != vecSortClas.end(); it++) {
		cout << "sortedClass index: " << distance(vecSortClas.begin(), it) << " has value " << it->getVal() << endl;

	}
	cout << endl;

	cout << "Vector of sorted Struct before sorting: " << endl;
	for (vector<sortedStruct>::iterator it = vecSortStru.begin(); it != vecSortStru.end(); it++) {
		cout << " Sorted Structure index is : " << distance(vecSortStru.begin(), it) << " has value: " << it->val << endl;
	}

	cout << "Vector of Sorted Struct after Sorting: " << endl;

	for (vector<sortedStruct>::iterator it = vecSortStru.begin(); it != vecSortStru.end(); it++) {
		vector<sortedStruct>::iterator it2 = it;

		auto ittemp = find_if(it2, it2 + 1, greaterThan(45));
		if (ittemp != it2 + 1) {
			cout << "sorted struct index " << distance(vecSortStru.begin(), it) << " has value greater than 45: " << ittemp->val << endl;
		}
	}
	// Destroying Elements: 

	vecSortClas.empty();
	vecSortStru.empty();
}

