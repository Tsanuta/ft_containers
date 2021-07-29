/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Iterator.tpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olidon <olidon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 14:04:58 by olidon            #+#    #+#             */
/*   Updated: 2021/03/13 14:39:38 by olidon           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Iterator.hpp"

namespace ft
{
	/*
	** ---------------------------- BIDIRECTIONAL -----------------------------
	*/

	template < class Category, class T, class Node >
	bidirectional< Category, T, Node >::bidirectional() : _ptr(NULL)
	{
	}

	template < class Category, class T, class Node >
	bidirectional< Category, T, Node >::bidirectional(Node *ptr) : _ptr(ptr)
	{
	}

	template < class Category, class T, class Node >
	bidirectional< Category, T, Node >::~bidirectional()
	{
		_ptr = NULL;
	}

	template < class Category, class T, class Node >
	bidirectional< Category, T, Node >::bidirectional(const bidirectional< Category, T, Node >& src) : _ptr(src._ptr)
	{
	}

	template < class Category, class T, class Node >
	template <class Cat2, class T2, class Node2 >
	bidirectional< Category, T, Node >::bidirectional(const bidirectional< Cat2, T2, Node2 >& src) : _ptr(src._ptr)
	{
	}

	/*
	** ---------------------------- RANDOM_ACCESS -----------------------------
	*/

	template < class Category, class T, class Node >
	random_access< Category, T, Node >::random_access()
	{
		this->_ptr = NULL;
	}

	template < class Category, class T, class Node >
	random_access< Category, T, Node >::random_access(Node *ptr)
	{
		this->_ptr = ptr;
	}

	template < class Category, class T, class Node >
	random_access< Category, T, Node >::~random_access()
	{
		this->_ptr = NULL;
	}

	template < class Category, class T, class Node >
	random_access< Category, T, Node >::random_access(const random_access< Category, T, Node >& src)
	{
		this->_ptr = src._ptr;
	}

	template < class Category, class T, class Node >
	random_access< Category, T, Node >::random_access(const bidirectional< Category, value_type, Node >& src) : bidirectional< Category, value_type, Node >(src)
	{
	}

	/*
	** -------------------------- BIDIRECTIONAL OPERATORS ---------------------------
	*/

	template < class Category, class T, class Node >
	bidirectional< Category, T, Node >&						bidirectional< Category, T, Node >::operator=(const bidirectional< Category, T, Node >& rhs)
	{
		this->_ptr = rhs._ptr;
		return (*this);
	}

	template < class Category, class T, class Node >
	bidirectional< Category, T, Node >&						bidirectional< Category, T, Node >::operator++()
	{
		_increment(this->_ptr);
		return (*this);
	}

	template < class Category, class T, class Node >
	bidirectional< Category, T, Node >						bidirectional< Category, T, Node >::operator++(int)
	{
		bidirectional< Category, T, Node >	postinc(*this);

		operator++();
		return postinc;
	}

	template < class Category, class T, class Node >
	bool													bidirectional< Category, T, Node >::operator==(bidirectional< Category, T, Node > const &rhs) const
	{
		return (this->_ptr == rhs._ptr);
	}

	template < class Category, class T, class Node >
	bool													bidirectional< Category, T, Node >::operator!=(bidirectional< Category, T, Node > const &rhs) const
	{
		return (this->_ptr != rhs._ptr);
	}

	template < class Category, class T, class Node >
	typename bidirectional< Category, T, Node >::reference	bidirectional< Category, T, Node >::operator*() const
	{
		return (this->_deref_ptr(this->_ptr));
	}

	template < class Category, class T, class Node >
	typename bidirectional< Category, T, Node >::pointer	bidirectional< Category, T, Node >::operator->() const
	{
		return &(operator*());
	}

	template < class Category, class T, class Node >
	bidirectional< Category, T, Node >&						bidirectional< Category, T, Node >::operator--()
	{
		_decrement(this->_ptr);
		return (*this);
	}

	template < class Category, class T, class Node >
	bidirectional< Category, T, Node >						bidirectional< Category, T, Node >::operator--(int)
	{
		bidirectional< Category, T, Node >	postdec(*this);

		operator--();
		return postdec;
	}

	template < class Category, class T, class Node >
	bidirectional< Category, T, Node >						bidirectional< Category, T, Node >::base() const
	{
		return (_ptr);
	}

	template < class Category, class T, class Node >
	typename bidirectional< Category, T, Node >::reference	bidirectional< Category, T, Node >::_deref_ptr(value_type *p) const
	{
		return (*p);
	}

	template < class Category, class T, class Node >
	template < class ClassNode >
	typename bidirectional< Category, T, Node >::reference	bidirectional< Category, T, Node >::_deref_ptr(ClassNode *node) const
	{
		return (node->operator*());
	}

	template < class Category, class T, class Node >
	void													bidirectional< Category, T, Node >::_increment(value_type *)
	{
		++this->_ptr;
	}

	template < class Category, class T, class Node >
	template < class ClassNode >
	void													bidirectional< Category, T, Node >::_increment(ClassNode *)
	{
		this->_ptr = &this->_ptr->operator++();
	}

	template < class Category, class T, class Node >
	void													bidirectional< Category, T, Node >::_decrement(value_type *)
	{
		--this->_ptr;
	}

	template < class Category, class T, class Node >
	template < class ClassNode >
	void													bidirectional< Category, T, Node >::_decrement(ClassNode *)
	{
		this->_ptr = &this->_ptr->operator--();
	}

	/*
	** ------------------------- RANDOM_ACCESS OPERATORS -------------------------
	*/

	template < class Category, class T, class Node >
	random_access< Category, T, Node >				random_access< Category, T, Node >::operator+(difference_type n) const
	{
		random_access< Category, T, Node >	tmp = this->_ptr + n;

		return tmp;
	}

	template < class Category, class T, class Node >
	random_access< Category, T, Node >				random_access< Category, T, Node >::operator-(difference_type n) const
	{
		random_access< Category, T, Node >	tmp = this->_ptr - n;

		return tmp;
	}

	template < class Category, class T, class Node >
	bool											random_access< Category, T, Node >::operator<(random_access const &rhs) const
	{
		return (this->_ptr < rhs._ptr);
	}

	template < class Category, class T, class Node >
	bool											random_access< Category, T, Node >::operator>(random_access const &rhs) const
	{
		return (this->_ptr > rhs._ptr);
	}

	template < class Category, class T, class Node >
	bool											random_access< Category, T, Node >::operator<=(random_access const &rhs) const
	{
		return (this->_ptr <= rhs._ptr);
	}

	template < class Category, class T, class Node >
	bool											random_access< Category, T, Node >::operator>=(random_access const &rhs) const
	{
		return (this->_ptr >= rhs._ptr);
	}

	template < class Category, class T, class Node >
	random_access< Category, T, Node >				&random_access< Category, T, Node >::operator+=(difference_type n)
	{
		this->_ptr = this->_ptr + n;
		return *this;
	}

	template < class Category, class T, class Node >
	random_access< Category, T, Node >				&random_access< Category, T, Node >::operator-=(difference_type n)
	{
		this->_ptr = this->_ptr - n;
		return *this;
	}

	template < class Category, class T, class Node >
	typename random_access< Category, T, Node >::reference	random_access< Category, T, Node >::operator[](difference_type n) const
	{
		return this->_ptr[n];
	}

	/*
	** ---------------------------- REVERSE_ITERATOR -----------------------------
	*/

	template < class Iter >
	reverse_iterator< Iter >::reverse_iterator() : _base(iterator_type())
	{
	}

	template < class Iter >
	reverse_iterator< Iter >::~reverse_iterator()
	{
		_base = NULL;
	}

	template < class Iter >
	reverse_iterator< Iter >::reverse_iterator(typename reverse_iterator< Iter >::iterator_type it) : _base(it)
	{
	}

	template < class Iter >
	reverse_iterator< Iter >::reverse_iterator(const reverse_iterator< Iter >& rev_it) : _base(rev_it._base)
	{
	}

	template < class Iter >
	template < class Iter2 >
	reverse_iterator< Iter >::reverse_iterator(const reverse_iterator< Iter2 >& rev_it) : _base(rev_it._base)
	{
	}

	template < class Iter >
	typename reverse_iterator< Iter >::iterator_type	reverse_iterator< Iter >::base() const
	{
		return _base;
	}

	template < class Iter >
	typename reverse_iterator< Iter >::reference		reverse_iterator< Iter >::operator*() const
	{
		return (*_base);
	}

	template < class Iter >
	reverse_iterator< Iter >							reverse_iterator< Iter >::operator+(difference_type n) const
	{
		return (reverse_iterator(this->base().operator-(n)));
	}

	template < class Iter >
	reverse_iterator< Iter >&							reverse_iterator< Iter >::operator++()
	{
		--_base;
		return (*this);
	}

	template < class Iter >
	reverse_iterator< Iter >							reverse_iterator< Iter >::operator++(int)
	{
		reverse_iterator< Iter >	postinc(*this);

		operator++();
		return postinc;
	}

	template < class Iter >
	reverse_iterator< Iter >							&reverse_iterator< Iter >::operator+=(difference_type n)
	{
		_base -= n;
		return (*this);
	}

	template < class Iter >
	reverse_iterator< Iter >							reverse_iterator< Iter >::operator-(difference_type n) const
	{
		return (reverse_iterator(this->base().operator+(n)));
	}

	template < class Iter >
	reverse_iterator< Iter >&							reverse_iterator< Iter >::operator--()
	{
		++_base;
		return (*this);
	}

	template < class Iter >
	reverse_iterator< Iter >							reverse_iterator< Iter >::operator--(int)
	{
		reverse_iterator< Iter >	postdec(*this);

		operator--();
		return postdec;
	}

	template < class Iter >
	reverse_iterator< Iter >							&reverse_iterator< Iter >::operator-=(difference_type n)
	{
		_base += n;
		return (*this);
	}

	template < class Iter >
	typename reverse_iterator< Iter >::pointer			reverse_iterator< Iter >::operator->() const
	{
		return &(operator*());
	}

	template < class Iter >
	typename reverse_iterator< Iter >::reference		reverse_iterator< Iter >::operator[](difference_type n) const
	{
		return _base[-n];
	}

	template < class Iter >
	bool												reverse_iterator< Iter >::operator==(reverse_iterator const &rhs) const
	{
		return (this->base() == rhs.base());
	}

	template < class Iter >
	bool												reverse_iterator< Iter >::operator!=(reverse_iterator const &rhs) const
	{
		return (this->base() != rhs.base());
	}

	/*
	** ---------------------------- NON-MEMBER FUNCTION -----------------------------
	*/

	/* RANDOM ACCESS ITERATOR */
	/* operator+ */
	template < class Category, class T, class Node >
	random_access< Category, T, Node >						operator+(typename random_access< Category, T, Node >::difference_type n,
																		const random_access< Category, T, Node >& it)
	{
		random_access< Category, T, Node >	tmp = it._ptr + n;
		return tmp;
	}

	/* operator- */
	template < class Category, class T, class Node >
	typename random_access< Category, T, Node >::difference_type	operator-(const random_access< Category, T, Node >& lhs,
																		const random_access< Category, T, Node >& rhs)
	{
		return (lhs._ptr - rhs._ptr);
	}


	/* REVERSE ITERATOR */
	/* relational operators */
	template < class Iterator >
	bool													operator==(const reverse_iterator< Iterator >& lhs,
																		const reverse_iterator< Iterator >& rhs)
	{
		return (lhs.base().operator==(rhs.base()));
	}

	template < class Iterator >
	bool													operator!=(const reverse_iterator< Iterator >& lhs,
																		const reverse_iterator< Iterator >& rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template < class Iterator >
	bool													operator<(const reverse_iterator< Iterator >& lhs,
																		const reverse_iterator< Iterator >& rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template < class Iterator >
	bool													operator<=(const reverse_iterator< Iterator >& lhs,
																		const reverse_iterator< Iterator >& rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template < class Iterator >
	bool													operator>(const reverse_iterator< Iterator >& lhs,
																		const reverse_iterator< Iterator >& rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template < class Iterator >
	bool													operator>=(const reverse_iterator< Iterator >& lhs,
																		const reverse_iterator< Iterator >& rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	/* operator+ */
	template < class Iterator >
	reverse_iterator< Iterator >							operator+(typename reverse_iterator< Iterator >::difference_type n,
																		const reverse_iterator< Iterator >& rev_it)
	{
		reverse_iterator< Iterator >	tmp = rev_it.operator+(n);
		return tmp;
	}

	/* operator- */
	template < class Iterator >
	typename reverse_iterator< Iterator >::difference_type	operator-(const reverse_iterator<Iterator>& lhs,
																		const reverse_iterator<Iterator>& rhs)
	{
		return (rhs.base() - lhs.base());
	}

}
