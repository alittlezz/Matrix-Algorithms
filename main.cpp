#include <Matrix.h>
#include <Timer.h>

/*
1 2
3 5
*/

void test1(std::string title){
    Timer timer(title);
    Matrix <double> a(2, 2);
    a.read();
    a.getInverse();
    a.print();
}

int main()
{
	test1("Testing inverse of matrix");
    return 0;
}
