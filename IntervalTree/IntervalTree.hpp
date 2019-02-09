#pragma once

#include<functional>

// Color enum for red-black tree node
enum class rbcolor {
	black,
	red
};

// Comparable interval implementation, equivalent to [begin, end) 
template<typename T>
struct Interval {
	T begin;
	T end;

	// Compare two intervals.
	// return 0 if this == ivl, -1 if this < ivl, 1 if this > ivl.
	int Compare(const Interval& ivl) {
		if (begin < ivl.begin&&end <= ivl.begin) {
			return -1;
		}
		if (end >= ivl.end) {
			return 1;
		}
		return 0;
	}
};

// IntervalValue wraps a interval with a concrete value stored inside.
template<
	typename IntervalT,
	typename ValT
>
class IntervalValue {
public:
	explicit IntervalValue(const Interval<IntervalT>& ivl, ValT val)
		:val(val), interval(ivl) {}

	ValT Value() {
		return val;
	}

	Interval<IntervalT> Interval() {
		return interval;
	}

private:
	ValT val;
	Interval interval;
};

// Node of interval tree, also node of red-black tree.
template<
	typename IntervalT,
	typename ValT
>
class intervalNode {
public:
	explicit intervalNode(const IntervalValue<IntervalT, ValT>& iv, rbcolor color)
		:iv(iv), left(nullptr), right(nullptr), parent(nullptr), color(color) {}

	rbcolor color() {
		return color;
	}

	int height() {
		int lh = 0, rh = 0;
		if (left != nullptr) {
			lh = left->height();
		}
		if (right != nullptr) {
			rh = right->height();
		}
		if (lh < rh) return rh + 1;
		return lh + 1;
	}

	intervalNode* min() {
		intervalNode* ret = this;
		while (ret->left != nullptr) {
			ret = ret->left;
		}
		return ret;
	}

	// return the next in-order node in tree
	intervalNode* successor() {
		if (right != nullptr) {
			return right.min();
		}
		intervalNode* ret = parent;
		while (ret != nullptr&&this == ret->right) {
			this = ret;
			ret = ret->parent;
		}
		return ret;
	}

	// updateTarget updates the target values for a node and its ancestors
	void updateTarget() {

	}

private:
	IntervalValue<IntervalT, ValT> iv;
	ValT target;
	intervalNode<IntervalT, ValT>* left, right, parent;
	rbcolor color;
};

template<
	typename IntervalT,
	typename ValT
>
class IntervalTree {
public:

	using FilterFunc = std::function<bool(const IntervalValue<IntervalT, ValT>& iv)>;

private:
	size_t size;
	intervalNode< IntervalT, ValT>* root;
};
