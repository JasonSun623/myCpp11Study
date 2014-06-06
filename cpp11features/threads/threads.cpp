#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <windows.h>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
using namespace std;
//http://cpp1x.org/Thread.html  http://zh.cppreference.com/w/cpp/thread

//          std::thread
/***
std::thread�ĳ�Ա������
join   :���������߳�(������ס�߳�)��ֱ�����߳����н�����
swap   : �������̵߳���ز���(underlying handles)������
detach : �����̶߳���������������С�Detach ���̲߳��ٿ�����(�㲻�õ�������)��

std::this_thread�ṩ�ĺ���
get_id    : ���ص�ǰ�̵߳� ID��
yield     : ���ߵ��ȳ������������߳�(���㴦��æ�ȴ���ʱ��ǳ�����)��
sleep_for : ������ǰ�߳�ֱ��ָ����ʱ��(sleep_duration)��
sleep_util: ������ǰ�߳�ֱ��ָ����ʱ��(sleep_time)��
***/
void func1()
{
	std::cout << "func1()\n";
}

// ��������ޅ�����func1ͬ�����ᵼ�������������޷���Ϊthread���̺߳���
// cannot convert argument 1 from 'overloaded-function' to 'std::thread &&'
//void func1(int& a) 
//{
//	std::cout << "func(int& a)\n";
//}

//���Ը��̺߳������������Ĳ���
void func2(int i, double d, const std::string& s)
{
	std::cout << i << ", " << d << ", " << s << "\n";
	std::cout << "func2()\n";
}

//�����÷�ʽ���ݣ�ע���̺߳���Ĭ�϶�����ֵ��ʽ���ݵģ�����ʹ�� std::ref ����std::cref ����ת��
void func3(int& a)
{
	a ++;
	std::cout << "func3()\n";
}

int func4(const int& a)
{
	std::cout << "func4()\n";
	return a + 100;
}

class SomeClass
{
public:
	int PrintString(const std::string& str) { std::cout << str << "\n";  return 1; }
};

void test_thread()
{
	std::cout << "test_thread id: " << std::this_thread::get_id() << "\n";
	{
		std::thread t(func1); //��ס�����ﲻ�������أ�Ҳ������������ͬ������func1����ʹ����ǩ����һ��
		std::cout << t.get_id() << "\t" << std::this_thread::get_id() << "\n";
		t.join();
		std::cout << t.get_id() << "\t" << std::this_thread::get_id() << "\n";
		//t.detach();
		std::cout << "-----------------------\n";
	}
	{   //���ݶ������
		std::thread t(func2, 1, 12.50, "sample");
		t.join();
		std::cout << "-----------------------\n";
	}
	{	//�����÷�ʽ����ʱ�����ݵĲ�������ʹ�� std::ref ����std::cref ����ת��		
		int a = 42;
		std::thread t(func3, std::ref(a));
		t.join();
		std::cout << a << std::endl;
		std::cout << "-----------------------\n";
	}
	{	//��const���÷�ʽ����		
		int a = 42;
		std::thread t(func4, std::cref(a));
		t.join();
		std::cout << a << std::endl;
		std::cout << "-----------------------\n";
	}
	{	//�����Ա����Ϊ�߳�ִ�к���
		
		SomeClass sc;
		std::string str("Hello,World!");
		std::thread t(&SomeClass::PrintString, &sc, std::cref(str));
		t.join();		
		std::cout << "-----------------------\n";
	}
}


//          std::mutex
/***
C++11 �� <mutex> ͷ�ļ����ṩ������ mutex ����ͬ������:
mutex           : �ṩ�˺��ĺ��� lock(), unlock() �� �������� trylock_() ����(�ж� mutex �Ƿ����)��
recursive_mutex : ������ͬ�̶߳�λ��mutex��
timed_mutex     : ��mutex�����ƣ����������Լ����������ķ���trylock__for()��rylock__until(),����������ָ����ʱ��λ���ʱ����ȡmutex��
recursive_timed_mutex : timed_mutex �� recursive_mutex ���ۺ���
***/
std::mutex glock_;
void func()
{
	std::lock_guard<std::mutex> locker(glock_);
	//glock_.lock();
	std::cout << "entered thread " << std::this_thread::get_id() << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(rand() % 10));
	std::cout << "leaving thread " << std::this_thread::get_id() << std::endl;
	//glock_.unlock();
}

void test_mutex()
{
	srand((unsigned int)time(0));

	std::thread t1(func);
	std::thread t2(func);
	std::thread t3(func);

	t1.join();
	t2.join();
	t3.join();
}

//           safe container
template <typename T>
class container
{
public:
	void add(T element)
	{
		std::lock_guard<std::recursive_mutex> locker(lock_);
		elements_.push_back(element);
	}

	void addrange(int num, ...)
	{
		va_list arguments;

		va_start(arguments, num);
		for (int i = 0; i < num; i++)
		{
			std::lock_guard<std::recursive_mutex> locker(lock_);
			add(va_arg(arguments, T));
		}
		va_end(arguments);
	}

	void dump()
	{
		std::lock_guard<std::recursive_mutex> locker(lock_);
		std::copy(elements_.begin(), elements_.end(), std::ostream_iterator<T>(std::cout, "\t"));
		std::cout << "\n";
	}
private:
	std::recursive_mutex lock_; //���ﲻ��ʹ��mutex����Ϊaddrange�����addʱ��λ�ȡ�����������������ȻҲ�������취����ȡ������
	std::vector<T> elements_;
};

void test_safe_vector()
{
	container<int> cc;
	cc.add(1);
	cc.addrange(5, 3, 4, 5, 6, 9);
	cc.dump();
}

//         dead lock
class SomeType
{
public:
	std::mutex mutex_;
};

void ChangeTwoObj(SomeType& lhs, SomeType& rhs)
{
	//lhs.mutex_.lock();  //��������������������
	//rhs.mutex_.lock();
	std::lock(lhs.mutex_, rhs.mutex_); // Ok, ��������

	//do something .....

	lhs.mutex_.unlock();
	rhs.mutex_.unlock();
	std::cout << "ChangeTwoObj Over\n";
}

void test_deadlock()
{
	SomeType s1, s2;

	std::thread t1(ChangeTwoObj, std::ref(s1), std::ref(s2));
	std::thread t2(ChangeTwoObj, std::ref(s2), std::ref(s1));
	t1.join();
	t2.join();
}


//         condition variable
/***
ע�⣺
std::condition_variableֻ������std::unique_lock<std::mutex>��
condition_variable_any�����������κ��û����������������BasicLockableҪ��
condition_variable_any�ṩ������std::condition_variable�Ĺ��ܣ�����һ��������������һЩ�̵߳�ͬ��ԭ�
***/
void test_condition_variable()
{
	std::queue<int> produced_nums;
	std::mutex m;
	std::condition_variable cond_var;
	bool done = false;
	bool notified = false;

	std::thread producer([&]() {
		for (int i = 0; i < 5; ++i) {
			std::this_thread::sleep_for(std::chrono::seconds(1));
			std::unique_lock<std::mutex> lock(m);
			std::cout << "producing " << i << '\n';
			produced_nums.push(i);
			notified = true;
			cond_var.notify_one();
		}

		done = true;
		cond_var.notify_one();
	});

	std::thread consumer([&]() {
		std::unique_lock<std::mutex> lock(m);
		while (!done) {
			while (!notified) {  // loop to avoid spurious wakeups
				cond_var.wait(lock);
			}
			while (!produced_nums.empty()) {
				std::cout << "consuming " << produced_nums.front() << '\n';
				produced_nums.pop();
			}
			notified = false;
		}
	});

	producer.join();
	consumer.join();
}

//         Futures
void test_future()
{

}


int main()
{
	test_thread();
	std::cout << "- - - - - - - - - - - - -\n";

	test_mutex();
	std::cout << "- - - - - - - - - - - - -\n";

	test_safe_vector();
	std::cout << "- - - - - - - - - - - - -\n";

	test_deadlock();
	std::cout << "- - - - - - - - - - - - -\n";

	test_condition_variable();
	std::cout << "- - - - - - - - - - - - -\n";

	test_future();
	std::cout << "- - - - - - - - - - - - -\n";

	getchar();
	return 0;
}