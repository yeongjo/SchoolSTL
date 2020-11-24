#include <iostream>
#include <random>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <iterator>
using namespace std;
int g_count = 0;
default_random_engine dre;
uniform_int_distribution<int> uidAge{0, 15};
uniform_int_distribution<int> uidName{ 'a', 'z' };

class Dog {
	string name;  // 15글자 기본할당됨
	int age;

public:
	Dog() {
		for (int i = 0; i < 10; ++i)
			name += uidName(dre);
		age = g_count++;// uidAge(dre);
	}

	void show() const { cout << name << " - " << age << endl; }

	string getName() const {
		return name;
	}

	friend std::istream& operator>>(std::istream& in, Dog& dest);
	friend ostream& operator<<(ostream&, const Dog&);
};

std::istream& operator>>(std::istream& in, Dog& dest) {
	in.read((char*)&dest, sizeof(Dog));
	//int frag = in.rdstate();

	//int currentPos = in.tellg();

	//in.seekg(0, ios::end);
	//int length = in.tellg();
	//in.seekg(currentPos, ios::beg);


	//cout << (ios::eofbit & frag) <<":"<< length <<":"<< currentPos << ":" << in.eof() << endl;
	//if(length == currentPos) in.setstate(in.eofbit|frag|ios::failbit);
	return in;
}

ostream& operator<<(ostream& os, const Dog& dog) {
	os.write((char*)&dog, sizeof(Dog));
	return os;
}

template <>
struct less<Dog> {
	bool operator()(const Dog& a, const Dog& b) const {
		return a.getName() < b.getName();
	}
};

int main()
{
	Dog dogs[2];
	ofstream out("개천마리", ios::binary);
	for (int i = 0; i < 2; ++i)
		out << dogs[i];
	out.close();

	ifstream in("개천마리", ios::binary);
	set<Dog> v{ istream_iterator<Dog>(in), {} };
	for (const Dog& dog : v)
		dog.show();
	in.close();
}