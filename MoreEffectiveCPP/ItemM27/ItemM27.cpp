#include <iostream>
#include <vector>

class UPNumber {
public:
	UPNumber() = default;
	void destroy() const { delete this; }
private:
	~UPNumber() = default;
};

void TestNotStack()
{
	// UPNumber A; E0330
	UPNumber* pA = new UPNumber();
	pA->destroy();
	// delete pA;
}

int main(int argn, char* argc[])
{
    TestNotStack();
    return 0;
}
