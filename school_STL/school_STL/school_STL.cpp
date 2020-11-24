#include <iostream>
#include <random>
#include <fstream>
#include <iomanip>
using namespace std;
int main() {
	{
		default_random_engine dre;
		uniform_int_distribution<int> uid;
		ofstream out("정수1000만개.data", ios::binary);
		int n;
		for (int i = 0; i < 1000'0000; ++i) {
			n = uid(dre);
			out.write((char*)&n, sizeof(n));
		}
	}

	// 1 읽어오기

	ifstream in("정수1000만개.data", ios::binary);
	int* data = new int[1000'0000];
	in.read((char*)data, sizeof(int) * 1000'0000);

	// 2 정렬하기
	qsort(data, 1000'0000, sizeof(int), [](const void* a, const void* b) {
		return *(static_cast<int const*>(a)) - *(static_cast<int const*>(b));
		});

	// 확인용
	for (int i = 0; i < 100; ++i)
		cout << setw(20) << left << data[i*100];

	// 3 저장하기
	{
		ofstream out("정수1000만개정렬.data", ios::binary);
		for (int i = 0; i < 1000'0000; ++i) {
			out.write((char*)&data[i], sizeof(data[i]));
		}
	}
	cout << "end" << endl;
	system("pause");
}