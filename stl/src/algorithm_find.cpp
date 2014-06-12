#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

//! C++STL�ķǱ����㷨��Non-mutating algorithms����һ�鲻�ƻ��������ݵ�ģ�庯�����������������ݽ����������Ԫ�ز��ҡ�������������ͳ�ƺ�ƥ�䡣

template<typename T>
void print_all(T start, T end)
{
	std::copy(start, end, std::ostream_iterator<int>(std::cout, " "));
	cout << "\n";
}

///find�㷨���ڲ��ҵ���ĳֵ��Ԫ�ء����������iter��ָ��Ԫ������*iter == value ���򷵻ص�����iter��δ���򷵻�last��
///find_if�㷨 ��find��һ��ν���жϰ汾�������÷��ز���ֵ��ν���ж�pred��������������[first, last)�ϵ�ÿһ��Ԫ�أ�
///���������iter����pred(*iter) == true����ʾ�ҵ�Ԫ�ز����ص�����ֵiter��δ�ҵ�Ԫ�أ��򷵻�last��
void test_find()
{
	vector<int> vvv = { 16, 2, 30, 3, 45, 75, 69, 70 };
	print_all(vvv.begin(), vvv.end());

	int val = 3;
	auto iter = std::find(vvv.begin(), vvv.end(), val);
	if (iter != vvv.end())
			cout << "find it, " << "elem " << val << " at location " << iter - vvv.begin() << "\n";
	else
		cout << "find fail, no elem " << val << "\n";

	//���ҵ�һ���ܹ�����val��Ԫ��λ��
	auto iter2 = std::find_if(vvv.begin(), vvv.end(), [&val](int x){ return x % val == 0; });
	if (iter2 != vvv.end())
		cout << "find it, at location " << iter2 - vvv.begin() << "\n";
	else
		cout << "find fail\n";
}

///adjacent_find�㷨���ڲ�����Ȼ������������ڽ�Ԫ�ضԡ��������ֺ���ԭ�ͣ�
///һ���ڵ���������[first , last)�ϲ�������������Ԫ�����ʱ������Ԫ�ض��е�һ��Ԫ�صĵ�����λ��;
///��һ����ʹ�ö�Ԫν���ж�binary_pred�����ҵ���������[first , last)������binary_pred�������ڽ�Ԫ�ضԣ�δ�ҵ��򷵻�last��
void test_adjacent_find()
{
	int IntArray[] = { 1, 2, 3, 4, 10, 8, 8, 6, 7, 9 };
	const int ARRAY_SIZE = sizeof(IntArray) / sizeof(IntArray[0]);
	print_all(IntArray, IntArray + ARRAY_SIZE);

	// ���ҵ�һ����������ȵ�Ԫ�� 
	int *pos1 = std::adjacent_find(IntArray, IntArray + ARRAY_SIZE);
	if (pos1 != IntArray + ARRAY_SIZE)  // elements found		
		cout << "Found adjacent pair of matching elements: (" << *pos1 << ", " 
		     << *(pos1 + 1) << "), " <<	"at location " << pos1 - IntArray << endl;
	else       
		cout << "No adjacent pair of matching elements were found" << endl;

	// ��ν����ʽ�Ĳ�����������odd_even���ڽ�Ԫ�ض�λ��
	//x bool odd_even(int x, int y)
	//x {
	//x 	return (x - y) % 2 == 0 ? 1 : 0;
	//x }
	//x int *pos2 = std::adjacent_find(IntArray, IntArray + ARRAY_SIZE, odd_even);
	int *pos2 = std::adjacent_find(IntArray, IntArray + ARRAY_SIZE, [](int x, int y){ return (x - y) % 2 == 0 ? 1 : 0; });
	if (pos2 != IntArray + ARRAY_SIZE)  // elements found		
	{
		cout << "Found adjacent pair of matching elements: (" << *pos2 << ", " 
			 << *(pos2 + 1) << "), " << "at location " << pos2 - IntArray << endl;
	}
	else         
		cout << "No adjacent pair of matching elements were found" << endl;
}

///find_end: ��һ�����������������һ������һ����ƥ���������.
///�ڵ���������[first1, last1)�������������������[first2, last2)Ԫ��ƥ��������У�������Ԫ�صĵ�������last1
///����Ҫ����������ֻ�ǰ�˳��ʼ��������
void test_find_end()
{
	std::cout << "--------------------    find_end   --------------------\n";
	vector<int> v = { 0, 1, 2, 2, 7, 3, 3, 4, 4, 4, 0, 6, 6 };
	//sort(v.begin(), v.end()); 
	copy(v.begin(), v.end(), ostream_iterator<int>(cout, " ")); 	cout << endl;

	vector<int>::iterator iter;

	vector<int> arr = { 1, 2, 2 };
	iter = std::find_end(v.begin(), v.end(), arr.begin(), arr.end());
	if (iter != v.end())
		cout << "find at position " << (iter - v.begin()) << endl;
	else
		cout << "find fail\n";

	vector<int> arr1 = { 1, 2, 2, 9 };
	iter = std::find_end(v.begin(), v.end(), arr1.begin(), arr1.end());
	if (iter != v.end())
		cout << "find at position " << (iter - v.begin()) << endl;
	else
		cout << "find fail\n";

	vector<int> arr2 = { 3, 8, 4 };
	//����һ��ԭ������ĳһ���������У�ʹ��ֵ��1��ǡ��Ϊ������arr2
	iter = std::find_end(v.begin(), v.end(), arr2.begin(), arr2.end(), [](int x, int y){ return x + 1 == y;	});
	if (iter != v.end())
		cout << "find at position " << std::distance(v.begin(), iter) << endl;
	else
		cout << "find fail\n";
}

///find_first_of�㷨���ڲ���λ��ĳ����Χ֮�ڵ�Ԫ�ء��ڵ���������[first1, last1)�ϲ���Ԫ��*i��ʹ�õ���������[first2, last2)
///��ĳ��Ԫ��*j������*i ==*j�������Ԫν�ʺ���comp(*i, *j)==true��������Ԫ���ҵ��򷵻ص�����i�����򷵻�last1
void test_find_first_of()
{
	const char* strOne = "abcdef1212daxs";
	const char* strTwo = "2ef";
	const char* result = find_first_of(strOne, strOne + strlen(strOne),	strTwo, strTwo + strlen(strTwo));
	cout << "�ַ���strOne�е�һ��������strTwo���ַ�Ϊ��" << *result << endl;
}

///count�㷨���ڼ��������е�ĳ������ֵ�ĳ��ִ�������������ʹ��ԭ�ͣ����������������[first, last)�ϵ���valueֵ
///��Ԫ�ظ���n���������ڼ���n��ֱ�ӷ��ػ������÷��ء�
void test_count()
{
	vector<int> vvv = { 16, 70, 30, 3, 45, 75, 69, 70 };
	print_all(vvv.begin(), vvv.end());

	int val = 70;
	int cou = std::count(vvv.begin(), vvv.end(), 70);
	cout << "total have " << cou << " elems(" << val << ")\n";

	int cou2 = std::count_if(vvv.begin(), vvv.end(), [&val](int x){ return x >= 70; });
	cout << "total have " << cou2 << " elems which is equal or greater than(" << val << ")\n";
}

///binary_search: ���ֲ��ң�Ҫ��������б�������
///�����Ƿ���[first, last)�д���iterator i, ���� !(*i<value) && !(value<*i) or comp(*i, value) == false && comp(value, *i) == false
void test_binary_search()
{
	std::cout << "--------------------    binary_search   --------------------\n";
	vector<int> v = { 0, 1, 2, 2, 7, 3, 3, 4, 4, 4, 5, 6, 6 };
	sort(v.begin(), v.end());   //ע�⣬����Ҫ��֤�������		
	copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
	cout << endl;

	// binary_search
	int val = 3;
	if (std::binary_search(v.begin(), v.end(), val))
		cout << "find elem " << val << " success\n";
	else
		cout << "find elem " << val << " fail\n";

	//val = 9;
	//���� ������������ܹ���2������Ԫ��
	if (std::binary_search(v.begin(), v.end(), val, [](int elem, int val)->bool{ return abs(val - elem) % 2 == 0; }))
		cout << "find success\n";
	else
		cout << "find fail\n";
	std::cout << "\n";
}

///search: ����������Χ����һ������������һ�����еĵ�һ�γ��ֵ�λ�á�
///search_n: �����������Ƿ���һϵ��Ԫ��ֵ��Ϊĳ������ֵ(��������ν���ж��������������С�
///��������������Ҫ����������ֻ�ǰ�˳��ʼ��������
void test_search()
{
	std::cout << "--------------------    search   --------------------\n";

	vector<int> v = { 0, 1, 2, 2, 7, 3, 3, 4, 4, 4, 0, 6, 6, 4 };
	//x sort(v.begin(), v.end());   //ע�⣬����Ҫ��֤�������
	copy(v.begin(), v.end(), ostream_iterator<int>(cout, " ")); 	cout << endl;

	{   //search
		auto func = [](std::vector<int> &vec){ copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, ",")); return ""; };

		vector<int> v1 = { 2, 7, 3 };
		vector<int>::iterator iter1 = std::search(v.begin(), v.end(), v1.begin(), v1.end());
		if (iter1 != v.end())
			cout << "v have sub sequences is v1(", func(v1), cout << ")\n";
		else
			cout << "v have not sub sequences is v1(", func(v1), cout << ")\n";

		vector<int> v2 = { 2, 7, 3, 5 };
		vector<int>::iterator iter2 = std::search(v.begin(), v.end(), v2.begin(), v2.end());
		if (iter2 != v.end())
			cout << "v have sub sequences is v2\n";
		else
			cout << "v have not sub sequences is v2\n";
	}
	{   //search_n
		int count = 3, val = 4;
		if (std::search_n(v.begin(), v.end(), count, val) != v.end())
			cout << "find " << count << " continuous sequencs is " << val << "\n";
		else
			cout << "find not " << count << " continuous sequencs is " << val << "\n";

		count = 2, val = 7;
		if (std::search_n(v.begin(), v.end(), count, val) != v.end())
			cout << "find " << count << " continuous sequencs is" << val << "\n";
		else
			cout << "find not " << count << " continuous sequencs is" << val << "\n";

		count = 3, val = 8;
		if (std::search_n(v.begin(), v.end(), count, val, [](int elem, int val){ return elem * 2 == val; }) != v.end())
			cout << "find " << count << " continuous sequencs which its double is " << val << "\n";
		else
			cout << "find " << count << " continuous sequencs which its double is " << val << "\n";

		count = 4, val = 8;
		if (std::search_n(v.begin(), v.end(), count, val, [](int elem, int val){ return elem * 2 == val; }) != v.end())
			cout << "find " << count << " continuous sequencs which its plus one is " << val << "\n";
		else
			cout << "find not " << count << " continuous sequencs which its plus one is " << val << "\n";
	}
}

///lower_bound: ������Զ��һ��iterator i�� ʹ��[first,i)���������һ��iterator j���� *j < value or comp(*j,value)==true. 
///����һ��Iterator��ָ�����������з�Χ�ڵĿ��Բ���ָ��ֵ�����ƻ�����˳��ĵ�һ��λ��.���غ���ʹ���Զ���Ƚϲ���
///upper_bound: ������Զ��һ��iterator i�� ʹ��[first,i)���������һ��iterator j���� !(*j < value) or comp(*j,value)==false. 
///����һ��ForwardIterator,ָ�����������з�Χ�ڲ���value�����ƻ�����˳������һ��λ�ã���λ�ñ�־һ������value��ֵ��
///�ٶ���ֵͬ��Ԫ�ؿ����ж��,lower_bound ���ص�һ������������Ԫ��λ��;upper_bound �������һ������������Ԫ��λ��
void test_lower_upper_bound()
{
	{	//lower_bound
		std::cout << "--------------------    lower_bound   --------------------\n";
		vector<int> v = { 0, 1, 2, 2, 7, 3, 3, 4, 4, 4, 0, 6, 6 };
		sort(v.begin(), v.end());   //ע�⣬����Ҫ��֤�������
		copy(v.begin(), v.end(), ostream_iterator<int>(cout, " ")); 	cout << endl;

		/*  lower_bound */
		int val = 3;
		cout << "lower_bound function, split value = " << val << endl;
		vector<int>::iterator iter = std::lower_bound(v.begin(), v.end(), val);
		cout << "less than " << val << " : ";
		copy(v.begin(), iter, ostream_iterator<int>(cout, " "));		cout << endl;
		cout << "equal or greater than " << val << " : ";
		copy(iter, v.end(), ostream_iterator<int>(cout, " "));			cout << endl;
		std::cout << "\n";
	}
	{	//upper_bound
		std::cout << "--------------------    upper_bound   --------------------\n";
		vector<int> v = { 0, 1, 2, 2, 7, 3, 3, 4, 4, 4, 5, 6, 6 };

		sort(v.begin(), v.end());   //ע�⣬����Ҫ��֤�������

		copy(v.begin(), v.end(), ostream_iterator<int>(cout, " ")); 	cout << endl;

		int val = 3;
		cout << "upper_bound function, split value = " << val << endl;
		vector<int>::iterator iter = std::upper_bound(v.begin(), v.end(), val);
		cout << "equal or less than " << val << " : ";
		copy(v.begin(), iter, ostream_iterator<int>(cout, " "));		cout << endl;
		cout << "greater than " << val << " : ";
		copy(iter, v.end(), ostream_iterator<int>(cout, " "));			cout << endl;
		std::cout << "\n";
	}
}

///equal_range: ˳����ң�Ҫ��������б�������
///��������subrange[i,j)��ʹ������һ��iterator in [i,j)����!(*k<value) && !(value<*k) or comp(*k,value)==false && comp(value,*k)==false.
///�ٶ���ֵͬ��Ԫ�ؿ����ж��,equal_range �������е���ָ��ֵ��ͷ/βԪ�ص�λ�ã���ʵ����lower_bound��upper_bound
void test_equal_range()
{
	std::cout << "--------------------    equal_range   --------------------\n";

	vector<int> v = { 0, 1, 2, 2, 7, 3, 3, 4, 4, 4, 0, 6, 6 };
	sort(v.begin(), v.end());   //ע�⣬����Ҫ��֤�������
	copy(v.begin(), v.end(), ostream_iterator<int>(cout, " ")); 	cout << endl;

	int val = 3;
	cout << "euqual_range function, split value = " << val << endl;
	pair<vector<int>::iterator, vector<int>::iterator> vecpair = std::equal_range(v.begin(), v.end(), val);
	cout << "get euqal value " << val << "= ";
	copy(vecpair.first, vecpair.second, ostream_iterator<int>(cout, " "));	cout << endl;

	val = 9;
	cout << "euqual_range function, split value = " << val << endl;
	vecpair = std::equal_range(v.begin(), v.end(), val);
	cout << "get euqal value " << val << "= ";
	copy(vecpair.first, vecpair.second, ostream_iterator<int>(cout, " "));	cout << endl;
	std::cout << "\n";
}

int main()
{
	test_find();
	std::cout << "===================\n";

	test_adjacent_find();
	std::cout << "===================\n";

	test_find_end();
	std::cout << "===================\n";

	test_find_first_of();
	std::cout << "===================\n";

	test_count();
	std::cout << "===================\n";

	test_binary_search();
	std::cout << "===================\n";

	test_search();
	std::cout << "===================\n";

	test_lower_upper_bound();
	std::cout << "===================\n";

	test_equal_range();
	std::cout << "===================\n";

	getchar();
	return 0;
}