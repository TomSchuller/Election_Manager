/********************************************************************
 * This class contains the functions that make operations on a Dynamic Array
********************************************************************/
#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <exception>
#include <list>
#include <map>
#define rcastc reinterpret_cast<const char*>
#define rcast reinterpret_cast<char*>


enum class DISTRICT_TYPE {
	UNIFIED = 0, DIVIDED
};

enum class ELECTION_TYPE {
	REGULAR, SIMPLE
};

const float ROUND = 0.5;
const int UNDEFINED = -1;
const int DISTRICT = 0;
const int DIVIDED = 1;
using namespace std;

template <class T>
class Dynamic_Array
{
private:
	T* _arr = nullptr;
	int _len;
	int _size;

	void resize() {
		if (_size == 0) _size = 1;
		else _size *= 2;
		T* temp = nullptr;
		try {
			temp = new T[_size];
		}
		catch (bad_alloc& ex) {
			std::cout << "Allocation failed: " << ex.what() << endl;
		}

		// Resize only if the this array is not empty
		if (_arr != nullptr) {
			for (int i = 0; i < _len; i++) {
				temp[i] = _arr[i];
			}
			delete[] _arr;
		}
		_arr = temp;
	}

public:
	Dynamic_Array(int length = 0) : _arr(nullptr), _len(0), _size(length) { if (length > 0) _arr = new T[length]; }


	Dynamic_Array(const Dynamic_Array& other) : _arr(nullptr) {
		*this = other;
	}

	~Dynamic_Array() {
		delete[] _arr;
	}

	const T& front()    const { return _arr[0]; }
	int      size()     const { return _len; }
	int      capacity() const { return _size; }
	bool     empty()    const { return _len == 0; }
	void     clear() { _len = 0; }

	void setLength(int newLength) {
		if (newLength > _size) {
			_size = (newLength + 1) / 2;
			try {
				resize();
			}
			catch (bad_alloc& ex) {
				throw;
			}
			catch (...) {
				throw;
			}
		}
		_len = newLength;
	}

	const Dynamic_Array& operator=(const Dynamic_Array& other) {
		if (this != &other) {
			_len = other._len;
			_size = other._size;
			delete[] _arr;
			try {
				_arr = new T[_size];
			}
			catch (bad_alloc& ex) {
				throw;
			}

			for (int i = 0; i < _len; i++)
				_arr[i] = other._arr[i];
		}
		return *this;
	}

	const T& operator[](int i) const {
		return _arr[i];
	}
	T& operator[](int i) {
		return _arr[i];
	}

	const T& at(int i) const {
		if (i < 0 || i >= _len) {
			throw out_of_range("Invalid array index");
		}
		return _arr[i];
	}

	T& at(int i) {
		if (i < 0 || i >= _len) {
			throw out_of_range("Invalid array index");
		}
		return _arr[i];
	}

	void push_back(const T& value) {
		if (_len == _size) {
			try {
				resize();
			}
			catch (bad_alloc& ex) {
				throw;
			}
			catch (...) {
				throw;
			}
		}
		_arr[_len] = value;
		++_len;
	}

	friend ostream& operator<<(ostream& os, const Dynamic_Array<T>& t) {
		for (int i = 0; i < t.size(); i++) {
			os << t[i];
		}
		return os;
	}

	class reverse_iterator;
	class iterator
	{
	private:
		Dynamic_Array* _da;
		int			  _i;
	public:
		using iterator_category = bidirectional_iterator_tag;
		using different_type = ptrdiff_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;

		iterator(Dynamic_Array& arr, int i) : _da(&arr), _i(i) {
			if (i < 0 || i > arr.size()) throw out_of_range("Invalid array index");
		}
		iterator(const iterator& other) : _da(other._da), _i(other._i) {}

		friend class const_iterator;
		friend class reverse_iterator;

		const iterator& operator=(const iterator& other) {
			_da = other._da;
			_i = other._i;
			return *this;
		}

		// comparison with another iterator
		bool operator==(const iterator& other) const {
			return (_da == other._da) && (_i == other._i);
		}
		bool operator!=(const iterator& other) const {
			return !(*this == other);
		}

		bool operator<(const iterator& other) const {
			return _i < other._i;
		}

		// smart-pointer iterator methods
		T& operator*() {
			return _da->_arr[_i];
		}
		T* operator->() {
			return &_da->_arr[_i];
		}

		// increment-decrement iterator methods
		iterator& operator++() {
			if (++_i > _da->size()) throw out_of_range("Invalid array index");
			return *this;
		}

		iterator operator++(int) {
			iterator temp(*this);
			if (++_i > _da->size()) throw out_of_range("Invalid array index");
			return temp;
		}

		iterator& operator--() {
			if (--_i < 0) throw out_of_range("Invalid array index");
			return *this;
		}

		iterator operator--(int) {
			iterator temp(*this);
			if (--_i < 0) throw out_of_range("Invalid array index");
			return temp;
		}
	};

	class const_iterator
	{
	private:
		const Dynamic_Array* _da;
		int				    _i;
	public:
		using iterator_category = bidirectional_iterator_tag;
		using different_type = ptrdiff_t;
		using value_type = const T;
		using pointer = const T*;  
		using reference = const T&; 

		const_iterator(const Dynamic_Array& arr, int i) : _da(&arr), _i(i) {}
		const_iterator(const const_iterator& other) : _da(other._da), _i(other._i) {}
		const_iterator(const iterator& other) : _da(other._da), _i(other._i) {}

		const const_iterator& operator=(const const_iterator& other) {
			_da = other._da;
			_i = other._i;
			return *this;
		}

		const const_iterator& operator=(const iterator& other) {
			_da = other._da;
			_i = other._i;
			return *this;
		}

		// comparison with another iterator
		bool operator==(const const_iterator& other) const {
			return (_da == other._da) && (_i == other._i);
		}
		bool operator!=(const const_iterator& other) const {
			return !(*this == other);
		}

		// smart-pointer iterator methods
		const T& operator*() {
			return _da->_arr[_i];
		}
		const T* operator->() {
			return &_da->_arr[_i];
		}

		// increment-decrement iterator methods
		const_iterator& operator++() {
			if (++_i > _da->size()) throw out_of_range("Invalid array index");
			return *this;
		}
		const_iterator operator++(int) {
			const_iterator temp(*this);
			if (++_i > _da->size()) throw out_of_range("Invalid array index");
			return temp;
		}

		const_iterator& operator--() {
			if (--_i < 0) throw out_of_range("Invalid array index");
			return *this;
		}

		const_iterator operator--(int) {
			const_iterator temp(*this);
			if (--_i < 0) throw out_of_range("Invalid array index");
			return temp;
		}
	};

	class reverse_iterator
	{
	private:
		Dynamic_Array* _da;
		int			  _i;
	public:
		using iterator_category = bidirectional_iterator_tag;
		using different_type = ptrdiff_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;

		reverse_iterator(Dynamic_Array& arr, int i) : _da(&arr), _i(i) {}
		reverse_iterator(const reverse_iterator& other) : _da(other._da), _i(other._i) {}
		reverse_iterator(const iterator& other) : _da(other._da), _i(other._i) {}

		const reverse_iterator& operator=(const reverse_iterator& other) {
			_da = other._da;
			_i = other._i;
			return *this;
		}

		// comparison with another reverse_iterator
		bool operator==(const reverse_iterator& other) const {
			return (_da == other._da) && (_i == other._i);
		}
		bool operator!=(const reverse_iterator& other) const {
			return !(*this == other);
		}

		// smart-pointer reverse_iterator methods
		T& operator*() {
			return _da->_arr[_i];
		}
		T* operator->() {
			return &_da->_arr[_i];
		}

		// increment-decrement iterator methods
		reverse_iterator& operator++() {
			if (--_i < 0) throw out_of_range("Invalid array index");
			return *this;
		}

		reverse_iterator operator++(int) {
			reverse_iterator temp(*this);
			if (--_i < 0) throw out_of_range("Invalid array index");
			return temp;
		}

		reverse_iterator& operator--() {
			if (++_i > _da->size()) throw out_of_range("Invalid array index");
			return *this;
		}

		reverse_iterator operator--(int) {
			reverse_iterator temp(*this);
			if (++_i > _da->size()) throw out_of_range("Invalid array index");
			return temp;
		}
	};

	iterator insert(const iterator& pos, const T& val) {
		try {
		    // Resize
			if (_len == _size)
				resize();

			iterator itrEnd = end();
			iterator itrCurrent = itrEnd, itrPrev = --itrEnd;
			// Find position's iterator
			while (itrCurrent != pos)
			{
				*itrCurrent = *itrPrev;
				itrCurrent = itrPrev--;
			}
			// Insert and increase length
			iterator p = pos;
			*p = val;
			++_len;
			return p;
		}
		catch (bad_alloc& ex) {
			throw;
		}
		catch (out_of_range& ex) {
			throw;
		}
		catch (exception& ex) {
			throw;
		}
		catch (...) {
			throw;
		}
	}

	iterator erase(const iterator& iter) {
		if (iter == end()) {
			return end(); // don't do anything.
		}
		try {
			iterator itrEnd = end();
			iterator temp = iter, itrNext = ++temp;
			iterator itrCurrent = iter;

			// Step over iterator to delete
			while (itrCurrent != itrEnd)
			{
				*itrCurrent = *itrNext;
				itrCurrent = itrNext++;
			}
		}
		catch (out_of_range& ex) {
			throw;
		}
		catch (exception& ex) {
			throw;
		}
		catch (...) {
			throw;
		}

		--_len;
		return iter;
	}

	iterator erase(const iterator& first, const iterator& last)
	{
		try {
			if (last < first) throw invalid_argument("Error! The first iterator is larger than the last iterator!");
			// If only one element then erase it
			if (first == last)
				return erase(first);


			int count = 1; // more than 1 element 
			iterator curr1(first);
			iterator itrEnd = end();
			while (curr1 != last) // How many I need to delete
			{
				++count;
				++curr1;
			}
			_len -= (count);

			// If last == end, delete one more
			if (last == itrEnd) {
				++_len;
				return first;
			}

			iterator curr(first);
			iterator next(last);
			next++;

			while (curr != last && next != itrEnd)
			{
				*curr = *next; // fill data
				++curr;
				++next;
			}

			while (next != itrEnd)
			{
				*curr = *next;
				++curr;
				++next;
			}


			return first;
		}
		catch (invalid_argument& ex) {
			throw;
		}
		catch (out_of_range& ex) {
			throw;
		}
		catch (exception& ex) {
			throw;
		}
		catch (...) {
			throw;
		}
	}

	iterator begin() {
		return iterator(*this, 0);
	}

	iterator end() {
		return iterator(*this, _len);
	}

	const_iterator cbegin() const {
		return const_iterator(*this, 0);
	}

	const_iterator cend() const {
		return const_iterator(*this, _len);
	}

	reverse_iterator rbegin() {
		return reverse_iterator(*this, _len - 1);
	}

	reverse_iterator rend() {
		return reverse_iterator(*this, -1);
	}

	void print() const { 
		for (int i = 0; i < _len; i++)
			cout << _arr[i] << " ";
		cout << endl;
	}
};