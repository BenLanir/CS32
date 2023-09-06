#include <iostream>
#include "Set.h"
#include <cassert>

int main()
{
	Set test;
	test.insert("hello");
	Set test2;
	test2.insert("yo");
	test2.insert("ay");
	test2.swap(test);
	
}