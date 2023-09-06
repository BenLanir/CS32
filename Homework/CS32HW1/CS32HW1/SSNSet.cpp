#include "SSNSet.h"

SSNSet::SSNSet()
{
}

bool SSNSet::add(unsigned long ssn)
{
	return(SSNs.insert(ssn));
}

int SSNSet::size() const
{
	return(SSNs.size());
}

void SSNSet::print() const
{
	unsigned long a;
	for (int i = 0; i < SSNs.size(); i++)
	{
		SSNs.get(i, a);
		std::cout << a << std::endl;
	}
}