#include <cassert>
#include <array>
#include <vector>
#include <iostream>

static constexpr double EPS = 1E-5;

double median(const std::vector<int> &v, int l, int r) {
	assert(l < r);
	if ((r-l) % 2 == 1)
		return v[(l+r) / 2];
	return   (v[(l+r) / 2 - 1]
		+ v[(l+r) / 2]) / 2.;
}

int nonmedian_half_length(int l, int r) {
	if ((r-l) % 2 == 1)
		return (r-l-1) / 2;
	return (r-l-2) / 2;
}

bool equal(double a, double b) {
	return abs(a-b) < EPS;
}

bool less_than(double a, double b) {
	return a+EPS < b;
}

double median_edge_case_1_element_array(int x, const std::vector<int> &v, int vl, int vr) {
	const double v_median = median(v, vl, vr);
	const int vm = (vl+vr) / 2;
	const bool odd_length_v = (vr-vl) % 2 == 1;
	if (less_than(x, v_median)) {
		if (odd_length_v)
			return (v[vm] + std::max(x, v[vm-1])) / 2.;
		else
			return std::max(x, v[vm-1]);
	}
	else {
		if (odd_length_v)
			return (v[vm] + std::min(x, v[vm+1])) / 2.;
		else
			return std::min(x, v[vm]);
	}
}

double median_edge_case_2_elements_array(const std::array<int, 2> u, const std::vector<int> &v, int vl, int vr) {
	const double v_median = median(v, vl, vr);
	const int vm = (vl+vr) / 2;
	const bool odd_length_v = (vr-vl) % 2 == 1;
	if (less_than(u[1], v_median)) {
		if (odd_length_v)
			return std::max(u[1], v[vm-1]);
		else
			return (v[vm] + std::max(u[1], v[vm-1])) / 2.;
	}
	if (less_than(v_median, u[0])) {
		if (odd_length_v)
			return std::min(u[0], v[vm+1]);
		else
			return (v[vm-1] + std::min(u[0], v[vm])) / 2.;
	}
	else {
		if (odd_length_v)
			return v[vm];
		else
			return (std::max(u[0], v[vm-1]) + std::min(u[1], v[vm])) / 2.;
	}
}

double median(const std::vector<int> &u, int ul, int ur, const std::vector<int> &v, int vl, int vr) {
	assert(size(u) <= size(v));
	const double u_median = median(u, ul, ur);
	const double v_median = median(v, vl, vr);
	if (equal(u_median, v_median))
		return u_median;
	if (ur-ul == 1 && vr-vl == 1)
		return (u[ul]+v[vl]) / 2.;
	if (ur-ul == 1)
		return median_edge_case_1_element_array(u[ul], v, vl, vr);
	if (ur-ul == 2)
		return median_edge_case_2_elements_array({u[ul], u[ul+1]}, v, vl, vr);
	int removable_length = std::min(nonmedian_half_length(ul, ur), nonmedian_half_length(vl, vr));
	if (less_than(u_median, v_median)) {
		ul += removable_length;
		vr -= removable_length;
	}
	else {
		vl += removable_length;
		ur -= removable_length;
	}
	return median(u, ul, ur, v, vl, vr);
}

class VernaTask {
public:
	double findMedian(std::vector<int> &nums1, std::vector<int> &nums2) {
		if (size(nums1) < size(nums2))
			return median(nums1, 0, size(nums1), nums2, 0, size(nums2));
		return median(nums2, 0, size(nums2), nums1, 0, size(nums1));
	}
};

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
}

int main() {
	test();
	return 0;
}
