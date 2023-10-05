#include <cassert>
#include <array>
#include <vector>
#include <algorithm>
#include <iostream>

static constexpr double EPS = 1E-5;

static double median(const std::vector<int> &v, int l, int r) {
	assert(l < r);
	if ((r-l) % 2 == 1)
		return v[(l+r) / 2];
	return   (v[(l+r) / 2 - 1]
		+ v[(l+r) / 2]) / 2.;
}

static int nonmedian_half_length(int l, int r) {
	if ((r-l) % 2 == 1)
		return (r-l-1) / 2;
	return (r-l-2) / 2;
}

static bool equal(double a, double b) {
	return abs(a-b) < EPS;
}

static bool less_than(double a, double b) {
	return a+EPS < b;
}

static double median(const std::vector<int> &u, int ul, int ur, const std::vector<int> &v, int vl, int vr) {
	assert(size(u) <= size(v));
	const double u_median = median(u, ul, ur);
	const double v_median = median(v, vl, vr);
	if (equal(u_median, v_median))
		return u_median;
	if (ur-ul < 3 && vr-vl < 3) {
		std::vector<int> total;
		for (int i = ul; i < ur; ++i)
			total.push_back(u[i]);
		for (int i = vl; i < vr; ++i)
			total.push_back(v[i]);
		sort(begin(total), end(total));
		return median(total, 0, size(total));
	}
	if (ur-ul < 3) {
		const bool odd_length_v = (vr-vl) % 2 == 1;
		const int vm = (vl+vr) / 2;
		std::vector<int> active_elements;
		for (int i = ul; i < ur; ++i)
			active_elements.push_back(u[i]);
		if (odd_length_v) {
			active_elements.push_back(v[vm-1]);
			active_elements.push_back(v[vm]);
			active_elements.push_back(v[vm+1]);
		}
		else {
			active_elements.push_back(v[vm-2]);
			active_elements.push_back(v[vm-1]);
			active_elements.push_back(v[vm]);
			active_elements.push_back(v[vm+1]);
		}
		sort(begin(active_elements), end(active_elements));
		return median(active_elements, 0, size(active_elements));
	}
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
