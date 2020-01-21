#include "Delegate.h"
#include "Utils.h"


class B
{
public:
	bool Func(int i)
	{
		LOG("Test Member Function (%d)\n", i);

		return true;
	}

	void FuncMulticast(int i, int j)
	{
		LOG("Test Multicast Member Function (%d, %d)\n", i, j);
	}
};

bool TestRawFunc()
{
	LOG("Test Raw Function\n");
	return true;
}

void TestMulticastRawFunc(int i, int j)
{
	LOG("Test Multicast Raw Function (%d, %d)\n", i, j);
}

void TestDelegate()
{
	const char* Toto = "Lambda";
	B b;
	bool res = false;

	Delegate<> TestVoidVoidLambda;
	TestVoidVoidLambda.BindLambda([Toto]() { LOG("Test Void Void %s\n", Toto); });
	TestVoidVoidLambda.Execute();

	Delegate<bool> TestBoolVoidRaw;
	TestBoolVoidRaw.BindRaw(&TestRawFunc);
	res = TestBoolVoidRaw.Execute();

	Delegate<bool, int> TestBoolIntMember;
	TestBoolIntMember.BindMember(&b, &B::Func);
	res = TestBoolIntMember.Execute(42);

	MulticastDelegate<int, int> TestMulticast;
	TestMulticast.AddMember(&b, &B::FuncMulticast);
	TestMulticast.AddMemberUnique(&b, &B::FuncMulticast);
	TestMulticast.RemoveMember(&b, &B::FuncMulticast);
	TestMulticast.AddMember(&b, &B::FuncMulticast);
	TestMulticast.AddLambda([Toto](int i, int j) { LOG("Test Multicast %s (%d, %d)\n", Toto, i, j); });
	TestMulticast.AddRaw(TestMulticastRawFunc);

	TestMulticast.Broadcast(4, 8);

	TestMulticast.Clear();
}