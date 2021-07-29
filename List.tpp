/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   List.tpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olidon <olidon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 11:26:01 by olidon            #+#    #+#             */
/*   Updated: 2021/03/14 18:22:52 by olidon           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "List.hpp"

namespace ft
{
	/*
	** ------------------------- MEMBER FUNCTIONS -----------------------------
	*/

	/* constructor */
	template< typename T, class Alloc >
	list< T, Alloc >::list(const allocator_type& alloc) : _my_node_alloc(alloc)
	{
		init_node();
	}

	template< typename T, class Alloc >
	list< T, Alloc >::list(size_type n, const value_type& val,
								const allocator_type& alloc) : _my_node_alloc(alloc)
	{
		init_node();
		add_values_from_numbers(n, val);
	}

	template< typename T, class Alloc >
	template < class InputIterator >
	list< T, Alloc >::list(InputIterator first, InputIterator last,
								const allocator_type& alloc) : _my_node_alloc(alloc)
	{
		init_node();
		add_values(first, last, typename val_is_integral< InputIterator >::type());
	}

	template< typename T, class Alloc >
	list< T, Alloc >::list(const list< T, Alloc > &x)
	{
		init_node();
		iterator it = x.begin();
		iterator ite = x.end();

		add_values_from_iterators(it, ite);
	}

	/* destructor */
	template< typename T, class Alloc >
	list< T, Alloc >::~list()
	{
		node	curr;
		node	tmp;

		curr = _begin->next;
		while (curr != _end)
		{
			tmp = curr->next;
			delete_node(curr);
			curr = tmp;
		}
		delete_node_no_val(_begin);
		delete_node_no_val(_end);
		_size = 0;
	}

	/* operator= */
	template< typename T, class Alloc >
	list< T, Alloc >&				list< T, Alloc >::operator=(const list< T, Alloc >& x)
	{
		if (*this != x)
		{
			clear();
			iterator it = x.begin();
			iterator ite = x.end();

			add_values_from_iterators(it, ite);
		}
		return *this;
	}

	/*
	** ------------------------------ ITERATORS -------------------------------
	*/

	/* begin */
	template< typename T, class Alloc >
	typename list< T, Alloc >::iterator						list< T, Alloc >::begin()
	{
		return (iterator(_begin->next));
	}

	template< typename T, class Alloc >
	typename list< T, Alloc >::const_iterator				list< T, Alloc >::begin() const
	{
		return (const_iterator(_begin->next));
	}

	/* end */
	template< typename T, class Alloc >
	typename list< T, Alloc >::iterator						list< T, Alloc >::end()
	{
		return (iterator(_end));
	}

	template< typename T, class Alloc >
	typename list< T, Alloc >::const_iterator				list< T, Alloc >::end() const
	{
		return (const_iterator(_end));
	}

	/* rbegin */
	template< typename T, class Alloc >
	typename list< T, Alloc >::reverse_iterator				list< T, Alloc >::rbegin()
	{
		return (reverse_iterator(_end->prev));
	}

	template< typename T, class Alloc >
	typename list< T, Alloc >::const_reverse_iterator			list< T, Alloc >::rbegin() const
	{
		return (const_reverse_iterator(_end->prev));
	}

	/* rend */
	template< typename T, class Alloc >
	typename list< T, Alloc >::reverse_iterator				list< T, Alloc >::rend()
	{
		return (reverse_iterator(_begin));
	}

	template< typename T, class Alloc >
	typename list< T, Alloc >::const_reverse_iterator			list< T, Alloc >::rend() const
	{
		return (const_reverse_iterator(_begin));
	}

	/*
	** ------------------------------- CAPACITY --------------------------------
	*/

	/* empty */
	template< typename T, class Alloc >
	bool									list< T, Alloc >::empty() const
	{
		if (_begin->next != _end)
			return false;
		return true;
	}

	// /* size */
	template< typename T, class Alloc >
	typename list< T, Alloc >::size_type	list< T, Alloc >::size() const
	{
		return _size;
	}

	/* max_size */
	template< typename T, class Alloc >
	typename list< T, Alloc >::size_type	list< T, Alloc >::max_size() const
	{
		return (std::min(_my_node_alloc.max_size(), static_cast<unsigned long>(std::numeric_limits< difference_type >::max())));
	}

	/*
	** ------------------------------- ELEMENT ---------------------------------
	*/

	/* front */
	template< typename T, class Alloc >
	typename list< T, Alloc >::reference			list< T, Alloc >::front()
	{
		return (_begin->next->value);
	}

	template< typename T, class Alloc >
	typename list< T, Alloc >::const_reference		list< T, Alloc >::front() const
	{
		return (_begin->next->value);
	}

	/* back */
	template< typename T, class Alloc >
	typename list< T, Alloc >::reference				list< T, Alloc >::back()
	{
		return (_end->prev->value);
	}

	template< typename T, class Alloc >
	typename list< T, Alloc >::const_reference		list< T, Alloc >::back() const
	{
		return (_end->prev->value);
	}

	/*
	** ------------------------------ MODIFIERS --------------------------------
	*/

	/* assign */
	template< typename T, class Alloc >
	template < class InputIterator >
	void					list< T, Alloc >::assign(InputIterator first,
														InputIterator last)
	{
		clear();
		add_values(first, last, typename val_is_integral< InputIterator >::type());
	}

	template< typename T, class Alloc >
	void					list< T, Alloc >::assign(size_type n,
														const value_type& val)
	{
		clear();
		for (; n > 0; --n)
			push_back(val);
	}

	/* push_front */
	template< typename T, class Alloc >
	void					list< T, Alloc >::push_front(const value_type& val)
	{
		if (_end->prev == _begin)
			link_node(val, _begin, _end);
		else
			link_node(val, _begin, _begin->next);
	}

	/* pop_front */
	template< typename T, class Alloc >
	void					list< T, Alloc >::pop_front()
	{
		if (_end->prev != _begin)
			unlink_node(_begin, _begin->next->next);
	}

	/* push_back */
	template< typename T, class Alloc >
	void					list< T, Alloc >::push_back(const value_type& val)
	{
		if (_begin->next == _end)
			link_node(val, _begin, _end);
		else
			link_node(val, _end->prev, _end);
	}

	/* pop_back */
	template< typename T, class Alloc >
	void					list< T, Alloc >::pop_back()
	{
		if (_begin->next != _end)
			unlink_node(_end->prev->prev, _end);
		// ft_print_list();
	}

	/* insert */
	template< typename T, class Alloc >
	typename list< T, Alloc >::iterator	list< T, Alloc >::insert(iterator position,
														const value_type& val)
	{
		list< T, Alloc >::node	pos = position._ptr;

		link_node(val, pos->prev, pos);
		return (iterator(pos->prev));

	}

	template< typename T, class Alloc >
	void					list< T, Alloc >::insert(iterator position,
											size_type n, const value_type& val)
	{
		insert_values_from_numbers(position, n, val);
	}

	template< typename T, class Alloc >
	template < class InputIterator >
	void					list< T, Alloc >::insert(iterator position, InputIterator first, InputIterator last)
	{
		insert_values(position, first, last, typename val_is_integral< InputIterator >::type());
	}

	/* erase */
	template< typename T, class Alloc >
	typename list< T, Alloc >::iterator				list< T, Alloc >::erase(iterator position)
	{
		iterator	next_pos(position);

		++next_pos;
		unlink_node(position._ptr->prev, position._ptr->next);
		return (next_pos);
	}

	template< typename T, class Alloc >
	typename list< T, Alloc >::iterator				list< T, Alloc >::erase(iterator first,
																		iterator last)
	{
		iterator	tmp;
		while(first != last)
		{
			tmp = first;
			++tmp;
			unlink_node(first._ptr->prev, first._ptr->next);
			first = tmp;
		}
		return (last);
	}

	/* swap */
	template< typename T, class Alloc >
	void					list< T, Alloc >::swap(list& x)
	{
		std::swap(x, *this);
	}

	/* resize */
	template< typename T, class Alloc >
	void					list< T, Alloc >::resize(size_type n,
												value_type val)
	{
		if (n > _size)
		{
			for(; n > _size; )
				push_back(val);
		}
		if (n < _size)
		{
			for(; n < _size; )
				pop_back();
		}
	}

	/* clear */
	template< typename T, class Alloc >
	void					list< T, Alloc >::clear()
	{
		node	curr;
		node	tmp;

		curr = _begin->next;
		while(curr != _end)
		{
			tmp = curr->next;
			unlink_node(curr->prev, curr->next);
			curr = tmp;
		}
		_size = 0;
	}

	/*
	** ------------------------------ OPERATIONS -------------------------------
	*/

	/* splice */
	template< typename T, class Alloc >
	void					list< T, Alloc >::splice(iterator position, list& x)
	{
		if (!x.empty())
		{
			just_link_node(position._ptr->prev, position._ptr, x._begin->next, x._end->prev);
			just_unlink_node(x._begin, x._end);
			_size += x._size;
			x._size = 0;
		}
	}

	template< typename T, class Alloc >
	void					list< T, Alloc >::splice(iterator position,
															list& x, iterator i)
	{
		iterator	j = i;
		iterator	k = i;
		++j;
		--k;
		if (position != i && position != j)
		{
			just_unlink_node(k._ptr, j._ptr);
			just_link_node(position._ptr->prev, position._ptr, i._ptr, i._ptr);
			++_size;
			--x._size;
		}
	}

	template< typename T, class Alloc >
	void					list< T, Alloc >::splice(iterator position,
										list& x, iterator first, iterator last)
	{
		iterator	tmp = first;
		size_t		n = 0;
		iterator	tmpfirst = first;
		--tmpfirst;
		iterator	tmplast = last;
		iterator	tmplastprev = last;
		--tmplastprev;

		if (first != last)
		{
			while(tmp != last)
			{
				++tmp;
				++n;
			}
			just_unlink_node(tmpfirst._ptr, tmplast._ptr);
			just_link_node(position._ptr->prev, position._ptr, first._ptr, tmplastprev._ptr);
			_size += n;
			x._size -= n;
		}
	}

	/* remove */
	template< typename T, class Alloc >
	void					list< T, Alloc >::remove(const value_type& val)
	{
		node	curr;
		node	tmp;

		curr = _begin->next;
		if (_begin->next != _end)
		{
			while (curr != _end)
			{
				tmp = curr->next;
				if (curr->value == val)
					unlink_node(curr->prev, curr->next);
				curr = tmp;
			}
		}
	}

	/* remove_if */
	template< typename T, class Alloc >
	template <class Predicate>
	void					list< T, Alloc >::remove_if(Predicate pred)
	{
		node	curr;
		node	tmp;

		curr = _begin->next;
		if (_begin->next != _end)
		{
			while (curr != _end)
			{
				tmp = curr->next;
				if (pred(curr->value))
					unlink_node(curr->prev, curr->next);
				curr = tmp;
			}
		}
	}

	/* unique */
	template< typename T, class Alloc >
	void					list< T, Alloc >::unique()
	{
		iterator	iprev = this->begin();
		iterator	i = this->begin();
		iterator	end = this->end();
		iterator	tmp;

		if (size() > 1)
		{
			++i;
			while (i != end)
			{
				tmp = i;
				++tmp;
				if (*i == *iprev)
				{
					unlink_node(i._ptr->prev, i._ptr->next);
					// ++i;
					i = tmp;
					iprev = i;
					--iprev;
				}
				else
				{
					++i;
					++iprev;
				}
			}
		}
	}

	template< typename T, class Alloc >
	template <class BinaryPredicate>
	void					list< T, Alloc >::unique(BinaryPredicate binary_pred)
	{
		iterator	iprev = this->begin();
		iterator	i = this->begin();
		iterator	end = this->end();
		iterator	tmp;

		if (size() > 1)
		{
			++i;
			while (i != end)
			{
				tmp = i;
				++tmp;
				if (binary_pred(*i, *iprev))
				{
					unlink_node(i._ptr->prev, i._ptr->next);
					i = tmp;
					iprev = i;
					--iprev;
				}
				else
				{
					++i;
					++iprev;
				}
			}
		}
	}

	/* merge */
	template< typename T, class Alloc >
	void					list< T, Alloc >::merge(list& x)
	{
		iterator end = this->end();

		this->splice(end, x);
		this->sort();
	}

	template< typename T, class Alloc >
	template <class Compare>
	void					list< T, Alloc >::merge(list& x, Compare comp)
	{
		if (this != &x)
		{
			iterator end = this->end();

			this->splice(end, x);
			this->sort(comp);
		}
	}

	/* sort */
	template< typename T, class Alloc >
	void					list< T, Alloc >::sort()
	{
		iterator	i = this->begin();
		iterator	iprev = this->begin();
		iterator	end = this->end();

		if (_size == 0 || _size == 1)
			return ;
		if (_size > 2)
		{
			++i;
			while (i != end)
			{
				if (*i < *iprev)
				{
					i._ptr->next->prev = iprev._ptr;
					iprev._ptr->prev->next = i._ptr;
					iprev._ptr->next = i._ptr->next;
					i._ptr->next = iprev._ptr;
					i._ptr->prev = iprev._ptr->prev;
					iprev._ptr->prev = i._ptr;
					i = this->begin();
					++i;
					iprev = this->begin();
				}
				else
				{
					++i;
					++iprev;
				}
			}
		}
	}

	template< typename T, class Alloc >
	template <class Compare>
	void					list< T, Alloc >::sort(Compare comp)
	{
		iterator	i = this->begin();
		iterator	iprev = this->begin();
		iterator	end = this->end();

		if (_size == 0 || _size == 1)
			return ;
		if (_size > 2)
		{
			++i;
			while (i != end)
			{
				if (comp(*i, *iprev))
				{
					i._ptr->next->prev = iprev._ptr;
					iprev._ptr->prev->next = i._ptr;
					iprev._ptr->next = i._ptr->next;
					i._ptr->next = iprev._ptr;
					i._ptr->prev = iprev._ptr->prev;
					iprev._ptr->prev = i._ptr;
					i = this->begin();
					++i;
					iprev = this->begin();
				}
				else
				{
					++i;
					++iprev;
				}
			}
		}
	}

	/* reverse */
	template< typename T, class Alloc >
	void					list< T, Alloc >::reverse()
	{
		if (_size > 1)
		{
			iterator end = this->end();
			iterator i = this->begin();
			std::swap(i._ptr->prev->prev, i._ptr->prev->next);
			i._ptr = i._ptr->prev->prev;
			for (; i != end;)
			{
				std::swap(i._ptr->prev, i._ptr->next);
				i._ptr = i._ptr->prev;
			}
			std::swap(end._ptr->prev, end._ptr->next);
			std::swap(_begin, _end);
		}
	}


	/*
	** ---------------------- LIST PRIVATE FUNCTIONS ---------------------------
	*/

	template< typename T, class Alloc >
	template < class InputIterator >
	void	list< T, Alloc >::insert_values(iterator position, InputIterator first, InputIterator last, int)
	{
		insert_values_from_numbers(position, static_cast<size_type>(first), last);
	}

	template< typename T, class Alloc >
	template < class InputIterator >
	void	list< T, Alloc >::insert_values(iterator position, InputIterator first, InputIterator last, void *)
	{
		insert_values_from_iterators(position, first, last);
	}

	template< typename T, class Alloc >
	void	list< T, Alloc >::insert_values_from_numbers(iterator position, size_type n, const value_type& val)
	{
		for (; n > 0; --n)
			insert(position, val);
	}

	template< typename T, class Alloc >
	template < class InputIterator >
	void	list< T, Alloc >::insert_values_from_iterators(iterator position, InputIterator first, InputIterator last)
	{
		while (first != last)
		{
			insert(position, *first);
			++first;
		}
	}

	template< typename T, class Alloc >
	template < class InputIterator >
	void	list< T, Alloc >::add_values(InputIterator first, InputIterator last, int)
	{
		add_values_from_numbers(static_cast<size_type>(first), last);
	}

	template< typename T, class Alloc >
	template < class InputIterator >
	void	list< T, Alloc >::add_values(InputIterator first, InputIterator last, void *)
	{
		add_values_from_iterators(first, last);
	}

	template< typename T, class Alloc >
	void	list< T, Alloc >::add_values_from_numbers(size_type n, const value_type & val)
	{
		for (; n > 0; --n)
			push_back(val);
	}

	template< typename T, class Alloc >
	template < class InputIterator >
	void	list< T, Alloc >::add_values_from_iterators(InputIterator first, InputIterator last)
	{
		for (; first != last; ++first)
			push_back(*first);
	}

	template< typename T, class Alloc >
	void									list< T, Alloc >::init_node()
	{
		_begin = NULL;
		_end = NULL;
		_begin = create_node_no_val(_end, _end);
		_end = create_node_no_val(_begin, _begin);
		_begin->next = _end;
		_begin->prev = _end;
		_end->prev = _begin;
		_end->next = _begin;
		_size = 0;
	}

	template< typename T, class Alloc >
	void									list< T, Alloc >::link_node(const value_type& val, node prev, node next)
	{
		prev->next = create_node(val, prev, next);
		next->prev = prev->next;
	}

	template< typename T, class Alloc >
	void									list< T, Alloc >::just_link_node(node prev, node next, node newprev, node newnext)
	{
		prev->next = newprev;
		next->prev = newnext;
		newprev->prev = prev;
		newnext->next = next;
	}

	template< typename T, class Alloc >
	ft::list_node_base< T >					*list< T, Alloc >::create_node(const value_type& val,
													node prev, node next)
	{
		node n = _my_node_alloc.allocate(1);
		_my_node_alloc.construct(n, ft::list_node_base< T >(val, prev, next));
		++_size;
		return (n);
	}

	template< typename T, class Alloc >
	ft::list_node_base< T >					*list< T, Alloc >::create_node_no_val(node prev, node next)
	{
		node n = _my_node_alloc.allocate(1);
		n->prev = prev;
		n->next = next;
		++_size;
		return (n);
	}

	template< typename T, class Alloc >
	void									list< T, Alloc >::unlink_node(node prev, node next)
	{
		delete_node(prev->next);
		prev->next = next;
		next->prev = prev;
	}

	template< typename T, class Alloc >
	void									list< T, Alloc >::just_unlink_node(node prev, node next)
	{
		prev->next = next;
		next->prev = prev;
	}

	template< typename T, class Alloc >
	void									list< T, Alloc >::delete_node(node n)
	{
		_my_node_alloc.destroy(n);
		_my_node_alloc.deallocate(n, 1);
		--_size;
	}

	template< typename T, class Alloc >
	void									list< T, Alloc >::delete_node_no_val(node n)
	{
		_my_node_alloc.deallocate(n, 1);
		--_size;
	}

	/*
	** ------------------- NON MEMBER FUNCTION OVERLOADS -----------------------
	*/

	/* relational operators (list) */
	template < typename T, class Alloc >
	bool									operator==(const list< T, Alloc >& lhs,
														const list< T, Alloc >& rhs)
	{
		typedef typename list< T, Alloc >::const_iterator	const_iterator;
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
	bool									operator!=(const list< T, Alloc >& lhs,
														const list< T, Alloc >& rhs)
	{
		return !(lhs == rhs);
	}

	template < typename T, class Alloc >
	bool									operator<(const list< T, Alloc >& lhs,
														const list< T, Alloc >& rhs)
	{
		typedef typename list< T, Alloc >::const_iterator	const_iterator;
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
	bool									operator<=(const list< T, Alloc >& lhs,
														const list< T, Alloc >& rhs)
	{
		return !(rhs < lhs);
	}

	template < typename T, class Alloc >
	bool									operator>(const list< T, Alloc >& lhs,
														const list< T, Alloc >& rhs)
	{
		return (rhs < lhs);
	}

	template < typename T, class Alloc >
	bool									operator>=(const list< T, Alloc >& lhs,
														const list< T, Alloc >& rhs)
	{
		return !(lhs < rhs);
	}

	/* swap (list) */
	template < typename T, class Alloc >
	void									swap(list< T, Alloc >& x,
															list< T, Alloc >& y)
	{
		std::swap(x, y);
	}

}
/* ************************************************************************** */
