/*http://www.ibm.com/developerworks/cn/aix/library/1307_lisl_c11/*/
#include <iostream>
#include <string>
#include <vector>
using namespace std;

//���ڰ�ȫ�����ɣ������Ĳ�������Զ�����϶�Ϊ��ֵ����ʹ���Ǳ���������ģ�Ϊ�˻����ֵ����ʹ�� std::move<T>()
bool is_r_value(int &&) { return true; }
bool is_r_value(const int &) { return false; }
bool forward_r_value(int && i) { return is_r_value(i); }
void test_rvr(int && i)
{
	cout << is_r_value(i) << "\n"; //false: iΪ������������ʹ����������ֵҲ�����Ƶ�����ֵ(������������ֻ������ֵ����)
	cout << is_r_value(std::move<int&>(i)) << "\n";  //true: ʹ�� std::move<T>() ȡ����ֵ
	cout << is_r_value(2) << "\n"; //true: 2����ֵ 
	cout << forward_r_value(2) << "\n";  //false: ��Ȼ2����ֵ�����Ǿ���ת�������˾������������ձ����ֵ
}

/***             ��ֵ�������ļ�ֵ֮һ�� ֧��ת������(Move Sementics)
ת��������Խ���Դ(�ѣ�ϵͳ�����) ��һ������ת�Ƶ���һ�����������ܹ����ٲ���Ҫ����ʱ����Ĵ����������Լ����٣�
�ܹ��������� C++ Ӧ�ó�������ܡ�

��ʱ�����ά�� ( ���������� ) ������������Ӱ�졣ͨ��ת�����壬��ʱ�����е���Դ�ܹ�ת�������Ķ����

�����е�C++�����У����ǿ��Զ��忽�����캯���͸�ֵ������
Ҫʵ��ת�����壬��Ҫ����ת�ƹ��캯���������Զ���ת�Ƹ�ֵ��������
������ֵ�Ŀ����͸�ֵ�����ת�ƹ��캯����ת�Ƹ�ֵ��������
���ת�ƹ��캯����ת�ƿ���������û�ж��壬��ô����ѭ���еĻ��ƣ��������캯���͸�ֵ�������ᱻ���á�

��ͨ�ĺ����Ͳ�����Ҳ����������ֵ���ò�����ʵ��ת�����塣
***/

//������������ֻ������ֵ���ã������֪һ�����������ٱ�ʹ�ö����������ת�ƹ��캯����ת�Ƹ�ֵ������
//Ҳ���ǰ�һ����ֵ���õ�����ֵ������ʹ�ã�����ʹ�ñ�׼���ṩ��std::move��������������Էǳ��򵥵ķ�ʽ����ֵ����ת��Ϊ��ֵ���á�
std::string test(const std::string& str)
{
	printf("1: 0x%08x\n", str.c_str());
	std::string tmp(str);
	tmp.append("test!");  //ע�����д��룬2��3��ַ��ͬ����Ӵ��к�2��3��ַ��ͬ��
	printf("2: 0x%08x\n", tmp.c_str());
	//return std::move(tmp);  //�������ֱ�ӷ�����һ���ģ���Ϊstring�Ѿ�ʵ����ת������
	return tmp;
}

std::vector<int> test(const std::vector<int>& v)
{
	printf("1: 0x%x\n", &v[0]);
	std::vector<int> t(v);
	t.push_back(88);
	printf("2: 0x%x\n", &t[0]);
	return t; // ��std::move(t);���һ��
	//return std::move(t);
}

/***             ��ֵ�������ļ�ֵ֮���� ��ȷ���ݡ�����ת�� (Perfect Forwarding)
�ܹ��������ȷ�ض��巺�ͺ���
��ȷ���������������ĳ�������Ҫ��һ�����ԭ�ⲻ���Ĵ��ݸ���һ��������
��ԭ�ⲻ�����������ǲ�����ֵ���䣬�� C++ �У����˲���ֵ֮�⣬����һ���������ԣ���ֵ����ֵ�� const/non-const��
��ȷ���ݾ����ڲ������ݹ����У�������Щ���ԺͲ���ֵ�����ܸı䡣�ڷ��ͺ����У�����������ǳ��ձ顣
***/
//void process_value(int i) { std::cout << "int\n"; }
void process_value(int& i) { std::cout << "int&\n"; }
void process_value(const int& i) { std::cout << "const int&\n"; }
void process_value(int&& i) { std::cout << "int&&\n"; }
void process_value(const int&& i) { std::cout << "const int&&\n"; }
template <typename T> 
void forward_value(T&& val) 
{
	process_value(val);
}
//template <typename T> void forward_value(const T& val) {
//	process_value(val);
//}
//template <typename T> void forward_value(T& val) {
//	process_value(val);
//}
void test_forward()
{
	int a = 0;
	const int& b = 1;
	forward_value(a); // int& 
	forward_value(b); // const int& 
	forward_value(2); // int& (ԭ�Ľ�������int&&�����϶����ǰ����Ͼ�����forward_value��ͱ������������ֻ������ֵ��)
}

int main()
{
	test_rvr(0);
	cout << "----------------------------\n";

	test_forward();
	cout << "----------------------------\n";

	printf("3: 0x%08x\n", test("��ֵ���ò��ԣ�").c_str());
	cout << "----------------------------\n";

	std::vector<int> v(3); // �ı����ֵ�Ĵ�С <3�����ῴ��v2[0]��ַ�ı仯
	v.push_back(2);
	v.push_back(5);
	v.push_back(9);
	std::vector<int> v2 = test(v);
	printf("3: 0x%x\n", &v2[0]); 
	for (int i = 0; i < 100; ++i)
		v2.push_back(i);
	printf("4: 0x%x\n", &v2[0]);
	cout << "----------------------------\n";

	getchar();
	return 0;
}