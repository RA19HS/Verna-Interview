#include <cassert>
#include <array>
#include <vector>
#include <iostream>

static constexpr double EPS = 1E-5;

std::vector<int> u, v;

double median(std::vector<int> &v, int l, int r) {
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

double median(int ul, int ur, int vl, int vr) {
	double u_median = median(u, ul, ur);
	double v_median = median(v, vl, vr);
	if (equal(u_median, v_median))
		return u_median;
	if (ur-ul == 1 && vr-vl == 1)
		return (u[ul]+v[vl]) / 2.;
	if (vr-vl < 3) {
		swap(u, v); // It's O(1)
		std::swap(ul, vl);
		std::swap(ur, vr);
		std::swap(u_median, v_median);
	}
	if (ur-ul == 1) {
		const int vm = (vl+vr) / 2;
		const bool odd_length_v = (vr-vl) % 2 == 1;
		if (less_than(u[ul], v_median)) {
			if (odd_length_v)
				return (v[vm] + std::max(u[ul], v[vm-1])) / 2.;
			else
				return std::max(u[ul], v[vm-1]);
		}
		else {
			if (odd_length_v)
				return (v[vm] + std::min(u[ul], v[vm+1])) / 2.;
			else
				return std::min(u[ul], v[vm]);
		}
	}
	if (ur-ul == 2) {
		const int vm = (vl+vr) / 2;
		const bool odd_length_v = (vr-vl) % 2 == 1;
		if (less_than(u[ul+1], v_median)) {
			if (odd_length_v)
				return std::max(u[ul+1], v[vm-1]);
			else
				return (v[vm] + std::max(u[ul+1], v[vm-1])) / 2.;
		}
		if (less_than(v_median, u[ul])) {
			if (odd_length_v)
				return std::min(u[ul], v[vm+1]);
			else
				return (v[vm-1] + std::min(u[ul], v[vm])) / 2.;
		}
		else {
			if (odd_length_v)
				return v[vm];
			else
				return (std::max(u[ul], v[vm-1]) + std::min(u[ul+1], v[vm])) / 2.;
		}
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
	return median(ul, ur, vl, vr);
}

int main() {
	u = {1, 3, 5, 7, 9, 11, 13};
	v = {2, 4, 6, 8, 10};
	std::cerr << "6.5 ? " << median(0, size(u), 0, size(v)) << '\n';
	u = {1, 3, 5, 7, 9, 11};
	v = {2, 4, 6, 8, 10};
	std::cerr << "6 ? " << median(0, size(u), 0, size(v)) << '\n';
	u = {1, 3, 5, 7, 9};
	v = {2, 4, 7, 8, 10, 20};
	std::cerr << "7 ? " << median(0, size(u), 0, size(v)) << '\n';
	u = {1, 3, 5, 6, 9, 11};
	v = {2, 4, 8, 8, 10, 20};
	std::cerr << "7 ? " << median(0, size(u), 0, size(v)) << '\n';
	u = {1, 3, 5, 6, 9, 11};
	v = {4};
	std::cerr << "5 ? " << median(0, size(u), 0, size(v)) << '\n';
	u = {1, 3, 5, 6, 9, 11};
	v = {4, 7};
	std::cerr << "5.5 ? " << median(0, size(u), 0, size(v)) << '\n';
	return 0;
}
