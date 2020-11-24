#include <set>
#include <vector>
#include <fstream>
#include <map>
#include <string>
#include <iostream>
#include <random>
#include <iterator>
#include <chrono>
using namespace std;



int id = 0;

class Name {
	string first;
	string last;

public:
	Name() = default;
	Name(string first, string last) :first{ first }, last{ last }{}
	string& getFirst() { return first; }
	string& getLast() { return last; }
	void show() const {
		cout << first << " " << last << endl;
	}
	bool operator<(const Name& rhs) const {
		return last < rhs.last;
	}
	friend istream &operator>>(istream& in, Name& dest) {
		in >> dest.first >> dest.last;
		return in;
	}
	friend istream &operator>>(istream& in, pair<string, Name>& dest) {
		string f, l;
		in >> f >> l;
		Name name(f, l);
		dest.first = l;
		dest.second = name;
		return in;
	}

	friend ostream& operator<<(ostream& out, Name& dest) {
		out.write((char*)&dest, sizeof(Name));
		return out;
	}
};


string file1{ "고객1.txt" };
string file2{ "고객2.txt" };
void makeData() {
	ofstream out1(file1);
	ofstream out2(file2);

	default_random_engine dre;
	uniform_int_distribution<int> uidName('a', 'z');
	uniform_int_distribution<int> uidNameLen(3, 12);

	for (int i = 0; i < 10000; i++)
	{
		string first;
		for (int i = 0; i < uidNameLen(dre); i++)
		{
			first += uidName(dre);
		}
		string second;
		for (int i = 0; i < 3; i++)
		{
			second += uidName(dre);
		}
		Name name(first, second);
		out1 << name.getFirst() << "\t" << name.getLast() << endl;
	}
	for (int i = 0; i < 20000; i++)
	{
		string first;
		for (int i = 0; i < uidNameLen(dre); i++)
		{
			first += uidName(dre);
		}
		string second;
		for (int i = 0; i < 3; i++)
		{
			second += uidName(dre);
		}
		Name name(first, second);
		out2 << name.getFirst() << "\t" << name.getLast() << endl;
	}
}


void makeUpper(multiset<Name>& sets) {
	for (auto i = sets.begin(); i != sets.end(); i++) {
		string& last = const_cast<Name*>(&(*i))->getLast();
		string& first = const_cast<Name*>(&(*i))->getFirst();
		last[0] = toupper(last[0]);
		first[0] = toupper(first[0]);
	}
}


Name customers[10000];
int main() {
	//makeData();
	bool is_found = false;


	auto in = ifstream(file1);



	auto start = std::chrono::system_clock::now();

	// 문제 1 ================================
	multiset<Name> b{ istream_iterator<Name>(in), {} };
	Name findObj("kim", "kim");
	// 문제 2 ================================
	for (auto i = b.lower_bound(findObj); i != b.upper_bound(findObj); i++)
	{
		i->show();
		is_found = true;
	}
	if (!is_found) cout << "찾지못함" << endl;


	chrono::duration<double> sec = std::chrono::system_clock::now() - start;
	cout << sec.count() << endl;

	is_found = false;

	in.clear();
	in.seekg(0, ios::beg);

	start = std::chrono::system_clock::now();



	multimap<string, Name> a{ istream_iterator<pair<string, Name>>(in), {} }; // 파일읽어오는부분 만들어두기
	for (auto i = a.lower_bound("kim"); i != a.upper_bound("kim"); i++)
	{
		i->second.show();
		is_found = true;
	}
	if (!is_found) cout << "찾지못함" << endl;


	sec = std::chrono::system_clock::now() - start;
	cout << sec.count() << endl;

	in.clear();
	in.seekg(0, ios::beg);


	// 문제 3 ================================
	//for (const Name& t : b) {
	//	t.show();
	//}


	// 문제 4 ================================
	//makeUpper(b);
	//for (const Name& t : b) {
	//	t.show();
	//}


	// 문제 5 ================================
	//vector<Name> c{ istream_iterator<Name>(in), {} };
	//sort(c.begin(), c.end());
	//for (const Name& t : c) {
	//	t.show();
	//}


	// 문제 6 ================================
	//고객1.txt 와 고객2.txt를 합치라
	//동일한게 존재해선 안된다.

	auto in2 = ifstream(file2);

	set<Name> all(istream_iterator<Name>(in2), {});
	all.insert(b.begin(), b.end());
	for (const Name& t : all) {
		t.show();
	}
}
