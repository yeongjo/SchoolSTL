#include <iostream>
using namespace std;

template<class T1, int T2>
class Array {
	size_t num{ 0 };
	T1 data[T2];
public:
	explicit Array(){ }
	~Array() {
		//delete[] data;
	}
	Array(const Array&) = delete;
	Array& operator=(const Array&) = delete;
	T1 operator[](int idx) const {
		return data[idx];
	}
	T1& operator[](int idx) {
		return data[idx];
	}
};

int main() {
	Array<int, 10> a; // 정수 10개를 담을 메모리 확보
	for (int i = 0; i < 10; ++i)
		a[i] = i; // a에 쓰기
	for (int i = 0; i < 10; ++i)
		cout << a[i] << ' '; // a에서 읽기
	cout << endl;
}

