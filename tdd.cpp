#include "median.cpp"
#include <cassert>
#include <vector>

void test() {
	VernaTask task3;
	std::vector<int> u, v;
	u = {1, 3, 5, 7, 9, 11, 13}; v = {2, 4, 6, 8, 10}; assert(6.5 == task3.findMedian(u, v));
	u = {1, 3, 5, 7, 9, 11}; v = {2, 4, 6, 8, 10}; assert(6 == task3.findMedian(u, v));
	u = {1, 3, 5, 7, 9}; v = {2, 4, 7, 8, 10, 20}; assert(7 == task3.findMedian(u, v));
	u = {1, 3, 5, 6, 9, 11}; v = {2, 4, 8, 8, 10, 20}; assert(7 == task3.findMedian(u, v));
	u = {1, 3, 5, 6, 9, 11}; v = {4}; assert(5 == task3.findMedian(u, v));
	u = {1, 3, 5, 6, 9, 11}; v = {4, 7}; assert(5.5 == task3.findMedian(u, v));
	u = {1, 2}; v = {3}; assert(2 == task3.findMedian(u, v));
	u = {1, 3}; v = {2}; assert(2 == task3.findMedian(u, v));
	u = {2, 3}; v = {1}; assert(2 == task3.findMedian(u, v));
	u = {3, 5, 7}; v = {1}; assert(4 == task3.findMedian(u, v));
	u = {3, 5, 7}; v = {4}; assert(4.5 == task3.findMedian(u, v));
	u = {3, 5, 7}; v = {6}; assert(5.5 == task3.findMedian(u, v));
	u = {3, 5, 7}; v = {8}; assert(6 == task3.findMedian(u, v));
	u = {3, 5}; v = {1, 2, 7}; assert(3 == task3.findMedian(u, v));
	u = {1, 3}; v = {5, 7}; assert(4 == task3.findMedian(u, v));
}

int main() {
	test();
	return 0;
}
