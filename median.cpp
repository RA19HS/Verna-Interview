#include <cassert>
#include <array>
#include <vector>
#include <iostream>

static constexpr double EPS = 1E-5;

std::vector<int> u{1, 3, 5, 7, 9, 11, 13};
std::vector<int> v{2, 4, 6};

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
	if (ur-ul == 1) {
		int vm = (vl+vr) / 2;
		if (less_than(u_median, v_median)) {
			if ((vr-vl) % 2 == 1)
				return (v[vm] + std::max(u[ul], v[vm-1])) / 2.;
			else
				return std::max(u[ul], v[vm-1]);
		}
		else {
			if ((vr-vl) % 2 == 1)
				return (v[vm] + std::min(u[ul], v[vm+1])) / 2.;
			else
				return std::min(u[ul], v[vm]);
		}
	}
	if (ur-ul == 2)
		;
	if (vr-vl < 3)
		;
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
	std::cerr << median(u, 0, 1) << '\n';
	std::cerr << median(0, size(u), 0, size(v)) << '\n';
	return 0;
}
