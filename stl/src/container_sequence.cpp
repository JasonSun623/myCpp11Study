#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <array>
#include <forward_list>
#include <algorithm>
#include <numeric>   // for std::accumulate
using namespace std;

template<typename T>
void print_all(T start, T end)
{
	std::copy(start, end, std::ostream_iterator<int>(std::cout, " "));
	cout << "\n";
}

void test_forward_list()
{
	std::forward_list<int> flist;

	flist.push_front(4);
	flist.push_front(20);
	flist.emplace_front(9);
	flist.insert_after(++flist.begin(), 20);
	flist.emplace_after(++flist.begin(), 88);

	cout << "flist�е�Ԫ��: " << endl;  print_all(flist.begin(), flist.end());

	//size_t size = flist.size(); //error û��size����������
	//auto it = flist.begin() + 1;  // error

	cout << "flist�е�Ԫ��: " << endl;  print_all(flist.begin(), flist.end());

	int top = flist.front();
	flist.pop_front();

	flist.sort();	//����С��������
	cout << "flist�е�Ԫ��: " << endl;  print_all(flist.begin(), flist.end());

	flist.reverse();	//��ת
	cout << "flist�е�Ԫ��: " << endl;  print_all(flist.begin(), flist.end());

	int result = std::accumulate(flist.begin(), flist.end(), 0);  //���
	cout << "��Ϊ��" << result << endl;

	flist.remove(20);
	flist.remove_if([](int e){return e > 50; });
	cout << "flist�е�Ԫ��: " << endl;  print_all(flist.begin(), flist.end());

	std::forward_list<int>().swap(flist);
	if (flist.empty())
		cout << "now the list is empty\n";
}


int main()
{
	test_forward_list();
	getchar();
	return 0;
}