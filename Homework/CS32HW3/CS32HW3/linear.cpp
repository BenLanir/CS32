// Return false if the somePredicate function returns true for at
// least one of the array elements; return true otherwise.
bool allFalse(const std::string a[], int n)
{
	if (n < 1)
		return true;
	if (somePredicate(a[n - 1]))
		return false;
	return allFalse(a, n - 1);
}

// Return the number of elements in the array for which the
// somePredicate function returns false.
int countFalse(const std::string a[], int n)
{
	if (n < 1)
		return 0;
	if (!somePredicate(a[n - 1]))
		return 1 + countFalse(a, n - 1);
	return countFalse(a, n - 1);
}

// Return the subscript of the first element in the array for which
// the somePredicate function returns false.  If there is no such
// element, return -1.
int firstFalse(const std::string a[], int n)
{
	if (n < 1)
		return -1;
	if (n == 1 && !somePredicate(a[0]))
		return 0;
	else if (n == 1)
		return -1;
	int temp = firstFalse(a, n - 1);
	if (temp != -1)
		return temp;
	if (!somePredicate(a[n - 1]))
		return n - 1;
	return -1;
}

// Return the subscript of the greatest std::string in the array (i.e.,
// the smallest subscript m such that a[m] >= a[k] for all
// k from 0 to n-1).  If the array has no elements to examine,
// return -1.
int locateMaximum(const std::string a[], int n)
{
	if (n < 1)
		return -1;
	if (n == 1)
		return 0;
	int temp = locateMaximum(a, n - 1);
	std::string value = a[temp];
	if (a[n - 1] > value)
		return n - 1;
	return temp;
}

// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 does not contain
// a2 as a not-necessarily-contiguous subsequence), return false.
// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
// For example, if a1 is the 7 element array
//    "stan" "kyle" "cartman" "kenny" "kyle" "cartman" "butters"
// then the function should return true if a2 is
//    "kyle" "kenny" "butters"
// or
//    "kyle" "cartman" "cartman"
// and it should return false if a2 is
//    "kyle" "butters" "kenny"
// or
//    "stan" "kenny" "kenny"
bool contains(const std::string a1[], int n1, const std::string a2[], int n2)
{
	if (n2 < 1)
		return true;
	if (n1 < 1)
		return false;
	if (a1[n1 - 1] == a2[n2 - 1])
		return contains(a1, n1 - 1, a2, n2 - 2);
	return contains(a1, n1 - 1, a2, n2);
}