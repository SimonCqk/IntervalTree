#pragma once

#include<functional>

enum class rbcolor{
	black,
	red
};

template<typename T>
struct Interval{
	T begin;
	T end;

	int Compare(const Interval& ivl);
};

template<
	typename IntervalT,
	typename ValT
>
class IntervalValue {
public:
	explicit IntervalValue(const Interval<IntervalT>& ivl, ValT val);
	ValT Value();
	Interval<IntervalT> Interval();

private:
	ValT val;
	Interval<IntervalT> interval;
};

template<
	typename IntervalT,
	typename ValT
>
class intervalNode {
public:

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