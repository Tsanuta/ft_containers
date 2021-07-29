/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.tpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olidon <olidon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 11:26:01 by olidon            #+#    #+#             */
/*   Updated: 2021/03/13 14:45:05 by olidon           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Vector.hpp"

namespace ft
{
	/*
	** ------------------------- MEMBER FUNCTIONS -----------------------------
	*/

	/* constructor */
	template< typename T, class Alloc >
	vector< T, Alloc >::vector(const allocator_type& alloc) : _my_alloc(alloc), _begin(nullptr), _end(nullptr), _end_cap(nullptr)
	{
	}

	template< typename T, class Alloc >
	vector< T, Alloc >::vector(size_type n, const value_type& val,
								const allocator_type& alloc) : _my_alloc(alloc), _begin(nullptr), _end(nullptr), _end_cap(nullptr)
	{
		_add_values_from_numbers(n, val);
	}

	template< typename T, class Alloc >
	template < class InputIterator >
	vector< T, Alloc >::vector(InputIterator first, InputIterator last,
								const allocator_type& alloc) : _my_alloc(alloc), _begin(nullptr), _end(nullptr), _end_cap(nullptr)
	{
		_add_values(first, last, typename val_is_integral< InputIterator >::type());
	}

	template< typename T, class Alloc >
	vector< T, Alloc >::vector(const vector< T, Alloc > &x) : _begin(nullptr), _end(nullptr), _end_cap(nullptr)
	{
		iterator it = x.begin();
		iterator ite = x.end();

		_add_values_from_iterators(it, ite);
	}

	/* destructor */
	template< typename T, class Alloc >
	vector< T, Alloc >::~vector()
	{
		if (_begin != nullptr)
			_my_alloc.deallocate(_begin, capacity());
	}

	/* operator= */
	template< typename T, class Alloc >
	vector< T, Alloc >&				vector< T, Alloc >::operator=(const vector< T, Alloc >& x)
	{
		if (this != &x)
			assign(x._begin, x._end);
		return *this;
	}

	/*
	** ------------------------------ ITERATORS -------------------------------
	*/

	/* begin */
	template< typename T, class Alloc >
	typename vector< T, Alloc >::iterator						vector< T, Alloc >::begin()
	{
		return (iterator(this->_begin));
	}

	template< typename T, class Alloc >
	typename vector< T, Alloc >::const_iterator				vector< T, Alloc >::begin() const
	{
		return (const_iterator(this->_begin));
	}

	/* end */
	template< typename T, class Alloc >
	typename vector< T, Alloc >::iterator						vector< T, Alloc >::end()
	{
		return (iterator(this->_end));
	}

	template< typename T, class Alloc >
	typename vector< T, Alloc >::const_iterator				vector< T, Alloc >::end() const
	{
		return (const_iterator(this->_end));
	}

	/* rbegin */
	template< typename T, class Alloc >
	typename vector< T, Alloc >::reverse_iterator				vector< T, Alloc >::rbegin()
	{
		return (reverse_iterator(this->_end - 1));
	}

	template< typename T, class Alloc >
	typename vector< T, Alloc >::const_reverse_iterator			vector< T, Alloc >::rbegin() const
	{
		return (const_reverse_iterator(this->_end - 1));
	}

	/* rend */
	template< typename T, class Alloc >
	typename vector< T, Alloc >::reverse_iterator				vector< T, Alloc >::rend()
	{
		return (reverse_iterator(this->_begin - 1));
	}

	template< typename T, class Alloc >
	typename vector< T, Alloc >::const_reverse_iterator			vector< T, Alloc >::rend() const
	{
		return (const_reverse_iterator(this->_begin - 1));
	}

	/*
	** ------------------------------- CAPACITY --------------------------------
	*/

	/* size */
	template< typename T, class Alloc >
	typename vector< T, Alloc >::size_type	vector< T, Alloc >::size() const
	{
		return (static_cast< size_type >(_end - _begin));
	}

	/* max_size */
	template< typename T, class Alloc >
	typename vector< T, Alloc >::size_type	vector< T, Alloc >::max_size() const
	{
		return (std::min(_my_alloc.max_size(), static_cast<unsigned long>(std::numeric_limits< difference_type >::max())));
	}

	template< typename T, class Alloc >
	void									vector< T, Alloc >::resize(size_type n, value_type val)
	{
		size_type cs = size();

		if (cs < n)
			this->_append(n - cs, val);
		else if (cs > n)
			this->_destruct_at_end(this->_begin + n);
	}

	template< typename T, class Alloc >
	typename vector< T, Alloc >::size_type	vector< T, Alloc >::capacity() const
	{
		return (static_cast< size_type >(_end_cap - _begin));
	}

	/* empty */
	template< typename T, class Alloc >
	bool									vector< T, Alloc >::empty() const
	{
		if (_begin != _end)
			return false;
		return true;
	}

	/* reserve */
	template< typename T, class Alloc >
	void									vector< T, Alloc >::reserve(size_type n)
	{
		if (n > capacity())
		{
			vector< T, Alloc >	v;
			v._vallocate(n);
			v._construct_at_end_it(this->begin(), this->end());
			swap(v);
		}
	}

	/*
	** ------------------------------- ELEMENT ACCESS ---------------------------------
	*/

	/* operator[] */
	template< typename T, class Alloc >
	typename vector< T, Alloc >::reference			vector< T, Alloc >::operator[](size_type n)
	{
		return (_begin[n]);
	}

	template< typename T, class Alloc >
	typename vector< T, Alloc >::const_reference	vector< T, Alloc >::operator[](size_type n) const
	{
		return (_begin[n]);
	}

	/* at */
	template< typename T, class Alloc >
	typename vector< T, Alloc >::reference			vector< T, Alloc >::at(size_type n)
	{
		if (n >= size())
			_throw_out_of_range();
		return (_begin[n]);
	}

	template< typename T, class Alloc >
	typename vector< T, Alloc >::const_reference	vector< T, Alloc >::at(size_type n) const
	{
		if (n >= size())
			this->_throw_out_of_range();
		return (_begin[n]);
	}

	/* front */
	template< typename T, class Alloc >
	typename vector< T, Alloc >::reference			vector< T, Alloc >::front()
	{
		return (*this->_begin);
	}

	template< typename T, class Alloc >
	typename vector< T, Alloc >::const_reference	vector< T, Alloc >::front() const
	{
		return (*this->_begin);
	}

	/* back */
	template< typename T, class Alloc >
	typename vector< T, Alloc >::reference			vector< T, Alloc >::back()
	{
		return *(this->_end - 1);
	}

	template< typename T, class Alloc >
	typename vector< T, Alloc >::const_reference	vector< T, Alloc >::back() const
	{
		return *(this->_end - 1);
	}

	/*
	** ------------------------------ MODIFIERS --------------------------------
	*/

	/* assign */
	template< typename T, class Alloc >
	template < class InputIterator >
	void					vector< T, Alloc >::assign(InputIterator first,
														InputIterator last)
	{
		_assign_values(first, last, typename val_is_integral< InputIterator >::type());
	}

	template< typename T, class Alloc >
	void					vector< T, Alloc >::assign(size_type n,
														const value_type& val)
	{
		_assign_values_from_numbers(n, val);
	}

	/* push_back */
	template< typename T, class Alloc >
	void					vector< T, Alloc >::push_back(const value_type& val)
	{
		if (_end != _end_cap)
		{
			_my_alloc.construct(this->_end, val);
			++this->_end;
		}
		else
			_push_back_slow_path(val);
	}

	/* pop_back */
	template< typename T, class Alloc >
	void					vector< T, Alloc >::pop_back()
	{
		this->_destruct_at_end(this->_end - 1);
	}

	/* insert */
	template< typename T, class Alloc >
	typename vector< T, Alloc >::iterator	vector< T, Alloc >::insert(iterator position,
														const value_type& val)
	{
		pointer	p = _begin + (position - begin());
		if (_end < _end_cap)
		{
			if (p == _end)
			{
				_my_alloc.construct(_end, val);
				++_end;
			}
			else
			{
				++_end;
				pointer	_end_cp = _end - 1;
				while(_end_cp != p)
				{
					*_end_cp = *(_end_cp - 1);
					--_end_cp;
				}
				_my_alloc.construct(_end_cp, val);
			}
		}
		else
		{
			vector< T, Alloc >	v;
			_split_buffer(_recommended_size(size() + 1), static_cast< size_type >(p - _begin), v);
			v._construct_at_end(1, val);
			p = _swap_out_circular_buffer2(v, p);
			_my_alloc.construct(p, val);
		}
		return (iterator(p));
	}

	template< typename T, class Alloc >
	void					vector< T, Alloc >::insert(iterator position,
											size_type n, const value_type& val)
	{
		_insert_values_from_numbers(position, n, val);
	}

	template< typename T, class Alloc >
	template < class InputIterator >
	void					vector< T, Alloc >::insert(iterator position, InputIterator first, InputIterator last)
	{
		_insert_values(position, first, last, typename val_is_integral< InputIterator >::type());
	}

	/* erase */
	template< typename T, class Alloc >
	typename vector< T, Alloc >::iterator				vector< T, Alloc >::erase(iterator position)
	{
		difference_type	ps = position._ptr - _begin;
		pointer			p = _begin + ps;

		_destruct_at_end(_move(p + 1, _end, p));
		return (iterator(p));
	}

	template< typename T, class Alloc >
	typename vector< T, Alloc >::iterator				vector< T, Alloc >::erase(iterator first,
																		iterator last)
	{
		pointer			p = _begin + (first._ptr - _begin);

		if (first != last)
			_destruct_at_end(_move(p + (last._ptr - first._ptr), _end, p));
		return (iterator(p));
	}

	/* swap */
	template< typename T, class Alloc >
	void					vector< T, Alloc >::swap(vector& x)
	{
		std::swap(this->_begin, x._begin);
		std::swap(this->_end, x._end);
		std::swap(this->_end_cap, x._end_cap);
		std::swap(this->_my_alloc, x._my_alloc);
	}

	/* clear */
	template< typename T, class Alloc >
	void					vector< T, Alloc >::clear()
	{
		_destruct_at_end(_begin);
	}

	/*
	** ---------------------- VECTOR PRIVATE FUNCTIONS ---------------------------
	*/

	template< typename T, class Alloc >
	template < class InputIterator >
	void	vector< T, Alloc >::_insert_values(iterator position, InputIterator first, InputIterator last, int)
	{
		_insert_values_from_numbers(position, static_cast<size_type>(first), last);
	}

	template< typename T, class Alloc >
	template < class InputIterator >
	void	vector< T, Alloc >::_insert_values(iterator position, InputIterator first, InputIterator last, void *)
	{
		_insert_values_from_iterators(position, first, last);
	}

	template< typename T, class Alloc >
	void	vector< T, Alloc >::_insert_values_from_numbers(iterator position, size_type n, const value_type& val)
	{
		pointer	p = _begin + (position._ptr - _begin);
		if (n > 0)
		{
			if (n <= static_cast< size_type >(_end_cap - _end))
			{
				if (n > static_cast< size_type >(_end - p))
				{
					size_type	cx = n - static_cast< size_type >(_end - p);
					_construct_at_end(cx, val);
					n -= cx;
				}
				if (n > 0)
				{
					_end += n;
					pointer	_end_cp = _end - 1;
					while((_end_cp - n + 1) != p)
					{
						*_end_cp = *(_end_cp - n);
						--_end_cp;
					}
					while(n)
					{
						_my_alloc.construct(_end_cp, val);
						--_end_cp;
						--n;
					}
				}
			}
			else
			{
				vector< T, Alloc >	v;
				_split_buffer(_recommended_size(size() + 1), static_cast< size_type >(p - _begin), v);
				v._construct_at_end(n, val);
				p = _swap_out_circular_buffer2(v, p);
			}
		}
	}

	template< typename T, class Alloc >
	template < class InputIterator >
	void	vector< T, Alloc >::_insert_values_from_iterators(iterator position, InputIterator first, InputIterator last)
	{
		pointer	p = _begin + (position._ptr - _begin);
		size_type	n = (last._ptr - first._ptr);
		if (n > 0)
		{
			if (n <= static_cast< size_type >(_end_cap - _end))
			{
				if (n > static_cast< size_type >(_end - p))
				{
					size_type	cx = n - (_end - p);
					_construct_at_end_itn(&first, last, cx);
					n -= cx;
				}
				if (n > 0)
				{
					_end += n;
					pointer	_end_cp = _end - 1;
					while((_end_cp - n + 1) != p)
					{
						*_end_cp = *(_end_cp - n);
						--_end_cp;
					}
					while(n)
					{
						_my_alloc.construct(_end_cp, *first);
						++first;
						--_end_cp;
						--n;
					}
				}
			}
			else
			{
				vector< T, Alloc >	v;
				_split_buffer(_recommended_size(size() + 1), p - _begin, v);
				v._construct_at_end_it(first, last);
				p = _swap_out_circular_buffer2(v, p);
			}
		}
	}

	template< typename T, class Alloc >
	template < class InputIterator >
	void	vector< T, Alloc >::_add_values(InputIterator first, InputIterator last, int)
	{
		_add_values_from_numbers(static_cast<size_type>(first), last);
	}

	template< typename T, class Alloc >
	template < class InputIterator >
	void	vector< T, Alloc >::_assign_values(InputIterator first, InputIterator last, int)
	{
		_assign_values_from_numbers(static_cast<size_type>(first), last);
	}

	template< typename T, class Alloc >
	template < class InputIterator >
	void	vector< T, Alloc >::_add_values(InputIterator first, InputIterator last, void *)
	{
		_add_values_from_iterators(first, last);
	}

	template< typename T, class Alloc >
	template < class InputIterator >
	void	vector< T, Alloc >::_assign_values(InputIterator first, InputIterator last, void *)
	{
		size_type	n = static_cast< size_type >(last - first);

		clear();
		if (n > capacity())
		{
			vector< T, Alloc >	v;

			_split_buffer(n, 0, v);
			_swap_out_circular_buffer(v);
		}
		for(; first != last; ++first)
			push_back(*first);
	}

	template< typename T, class Alloc >
	void	vector< T, Alloc >::_add_values_from_numbers(size_type n, const value_type & val)
	{
		if (n > 0)
		{
			_vallocate(n);
			_construct_at_end(n, val);
		}
	}

	template< typename T, class Alloc >
	void	vector< T, Alloc >::_assign_values_from_numbers(size_type n, const value_type & val)
	{
		clear();
		if (n > capacity())
		{
			vector< T, Alloc >	v;

			_split_buffer(n, 0, v);
			_swap_out_circular_buffer(v);
		}
		for (; n > 0; --n)
			push_back(val);
	}

	template< typename T, class Alloc >
	template < class InputIterator >
	void	vector< T, Alloc >::_construct_at_end_itn(InputIterator *first, InputIterator last, size_type n)
	{
		while ((*first != last) || n)
		{
			_my_alloc.construct(this->_end, **first);
			++this->_end;
			++*first;
			--n;
		}
	}

	template< typename T, class Alloc >
	template < class InputIterator >
	void	vector< T, Alloc >::_construct_at_end_it(InputIterator first, InputIterator last)
	{
		while (first != last)
		{
			_my_alloc.construct(this->_end, *first);
			++this->_end;
			++first;
		}
	}

	template< typename T, class Alloc >
	template < class InputIterator >
	void	vector< T, Alloc >::_add_values_from_iterators(InputIterator first, InputIterator last)
	{
		InputIterator	firstcp(first);
		InputIterator	lastcp(last);
		size_type		n = 0;

		while(firstcp != lastcp)
		{
			++firstcp;
			++n;
		}
		if (n > 0)
		{
			_vallocate(n);
			_construct_at_end_it(first, last);
		}
	}

	template< typename T, class Alloc >
	void									vector< T, Alloc >::_vallocate(size_type n)
	{
		if (n > max_size())
			this->_throw_length_error();
		this->_begin = this->_end = _my_alloc.allocate(n);
		this->_end_cap = this->_begin + n;
	}

	template< typename T, class Alloc >
	void									vector< T, Alloc >::_construct_at_end(size_type n, const_reference x)
	{
		while (n > 0)
		{
			_my_alloc.construct(this->_end, x);
			this->_end++;
			--n;
		}
	}

	template< typename T, class Alloc >
	void									vector< T, Alloc >::_vdeallocate()
	{
		if (this->__begin_ != nullptr)
		{
			clear();
			_my_alloc.deallocate(this->_begin, capacity());
			this->__begin_ = this->__end_ = this->_end_cap = nullptr;
		}
	}

	template< typename T, class Alloc >
	void									vector< T, Alloc >::_destruct_at_end(pointer _new_last)
	{
		pointer		_soon_to_be_end = _end;

		while (_new_last != _soon_to_be_end)
			_my_alloc.destroy(--_soon_to_be_end);
		_end = _new_last;
	}

	template< typename T, class Alloc >
	void									vector< T, Alloc >::_construct_backward(pointer _begin1, pointer _end1, vector< T, Alloc > &v)
	{
		while (_end1 != _begin1)
		{
			_my_alloc.construct((v._begin - 1), *--_end1);
			--v._begin;
		}
	}

	template< typename T, class Alloc >
	void									vector< T, Alloc >::_construct_forward(pointer _begin1, pointer _end1, vector< T, Alloc > &v)
	{
		while (_begin1 != _end1)
		{
			_my_alloc.construct((v._end), *_begin1);
			++_begin1;
			++v._end;
		}
	}

	template< typename T, class Alloc >
	void									vector< T, Alloc >::_split_buffer(size_type n, size_type old_size, vector< T, Alloc > &v)
	{
		v._vallocate(n);
		v._begin = v._end = v._end + old_size;
	}

	template< typename T, class Alloc >
	void									vector< T, Alloc >::_push_back_slow_path(const_reference x)
	{
		vector< T, Alloc >	v;

		_split_buffer(_recommended_size(size() + 1), size(), v);
		_my_alloc.construct(v._end, x);
		v._end++;
		_swap_out_circular_buffer(v);
	}

	template< typename T, class Alloc >
	void									vector< T, Alloc >::_swap_out_circular_buffer(vector< T, Alloc > &v)
	{
		_construct_backward(this->_begin, this->_end, v);
		std::swap(this->_begin, v._begin);
		std::swap(this->_end, v._end);
		std::swap(this->_end_cap, v._end_cap);
	}

	template< typename T, class Alloc >
	typename vector< T, Alloc >::pointer			vector< T, Alloc >::_swap_out_circular_buffer2(vector< T, Alloc > &v, pointer p)
	{
		pointer		r = v._begin;

		_construct_backward(this->_begin, p, v);
		_construct_forward(p, this->_end, v);
		std::swap(this->_begin, v._begin);
		std::swap(this->_end, v._end);
		std::swap(this->_end_cap, v._end_cap);
		return r;
	}

	template< typename T, class Alloc >
	typename vector< T, Alloc >::size_type	vector< T, Alloc >::_recommended_size(size_type new_size)
	{
		const size_type 	ms = max_size();

		if (new_size > ms)
			this->_throw_length_error();
		const size_type		cap = capacity();

		if (cap >= ms / 2)
			return ms;
		return std::max(2 * cap, new_size);
	}

	template< typename T, class Alloc >
	void									vector< T, Alloc >::_append(size_type n, const reference x)
	{
		if (static_cast< size_type >(this->_end_cap - this->_end) >= n)
			this->_construct_at_end(n, x);
		else
		{
			vector< T, Alloc >	v;

			_split_buffer(_recommended_size(size() + n), size(), v);

			v._construct_at_end(n, x);
			_swap_out_circular_buffer(v);
		}
	}

	template< typename T, class Alloc >
	typename vector< T, Alloc >::pointer				vector< T, Alloc >::_move(pointer first, pointer last, pointer result)
	{
		while (first != last)
		{
			*result = *first;
			++result; ++first;
		}
		return result;
	}

	template< typename T, class Alloc >
	void												vector< T, Alloc >::_throw_out_of_range() const
	{
		throw std::out_of_range("vector");
	}

	template< typename T, class Alloc >
	void												vector< T, Alloc >::_throw_length_error()
	{
		throw std::length_error("vector");
		// throw std::length_error("allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size");
	}

	/*
	** ------------------- NON MEMBER FUNCTION OVERLOADS -----------------------
	*/

	/* relational operators (vector) */
	template < typename T, class Alloc >
	bool									operator==(const vector< T, Alloc >& lhs,
														const vector< T, Alloc >& rhs)
	{
		typedef typename vector< T, Alloc >::const_iterator	const_iterator;
		const_iterator										end1 = lhs.end();
		const_iterator										end2 = rhs.end();
		const_iterator										i1 = lhs.begin();
		const_iterator										i2 = rhs.begin();

		if (lhs.size() != rhs.size())
			return (false);
		while (i1 != end1 && i2 != end2 && *i1 == *i2)
		{
			++i1;
			++i2;
		}
		return (i1 == end1 && i2 == end2);
	}

	template < typename T, class Alloc >
	bool									operator!=(const vector< T, Alloc >& lhs,
														const vector< T, Alloc >& rhs)
	{
		return !(lhs == rhs);
	}

	template < typename T, class Alloc >
	bool									operator<(const vector< T, Alloc >& lhs,
														const vector< T, Alloc >& rhs)
	{
		typedef typename vector< T, Alloc >::const_iterator	const_iterator;
		const_iterator										end1 = lhs.end();
		const_iterator										end2 = rhs.end();
		const_iterator										i1 = lhs.begin();
		const_iterator										i2 = rhs.begin();

		for (; i2 != end2; ++i1, (void) ++i2)
		{
			if (i1 == end1 || (*i1 < *i2))
				return true;
			if (*i2 < *i1)
				return false;
		}
		return false;
	}

	template < typename T, class Alloc >
	bool									operator<=(const vector< T, Alloc >& lhs,
														const vector< T, Alloc >& rhs)
	{
		return !(rhs < lhs);
	}

	template < typename T, class Alloc >
	bool									operator>(const vector< T, Alloc >& lhs,
														const vector< T, Alloc >& rhs)
	{
		return (rhs < lhs);
	}

	template < typename T, class Alloc >
	bool									operator>=(const vector< T, Alloc >& lhs,
														const vector< T, Alloc >& rhs)
	{
		return !(lhs < rhs);
	}

	/* swap (vector) */
	template < typename T, class Alloc >
	void									swap(vector< T, Alloc >& x,
															vector< T, Alloc >& y)
	{
		x.swap(y);
	}
}
/* ************************************************************************** */
