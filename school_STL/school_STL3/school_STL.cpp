#include <iostream>
#include <string>
#include <random>
#include <fstream>
#include <algorithm>

#define SIZE 10

using namespace std;

int gid{};

default_random_engine dre;
uniform_int_distribution<int> uidAge(1, 12);
uniform_int_distribution<int> uidName('a', 'z');
uniform_int_distribution<int> uidNameLen(3, 15);

class Dog {
	string name; // 이름 - 15글자까지만 허용
	int age; // 나이
	int id; // 생성 시 결정되는 고유의 숫자로 된 id
public:
	Dog() : id{ ++gid } {
		int len = uidNameLen(dre);
		for (int i = 0; i < len; ++i)
			name += uidName(dre);
		name += '\0';
		age = uidAge(dre);
	}
	Dog(string name, int age) : name{ name }, age{ age }, id(++gid) {
	}
	~Dog() {
		cout << "remove: " << id << endl;
	}
	const string& getName() const { return name; }
};


class alignas(64) A {
	int a, b;
	string t;
};

int main()
{
	unique_ptr<Dog[]> dogs(new Dog[3]);
}
