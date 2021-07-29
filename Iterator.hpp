/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olidon <olidon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 11:26:06 by olidon            #+#    #+#             */
/*   Updated: 2021/03/15 11:31:19 by olidon           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEMPLATE_ITERATOR_HPP
# define TEMPLATE_ITERATOR_HPP

# include <iostream>
# include <string>
# include <memory>

namespace ft
{
	/*
	---------- BASIC STRUCT ----------
	*/

	struct bidirectional_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

	template < class T >
	struct iterator_traits
	{
		typedef T			value_type;
		typedef ptrdiff_t	difference_type;
		typedef T*   		pointer;
		typedef T&			reference;
	};

	template < class T >
	struct iterator_traits< const T >
	{
		typedef T			value_type;
		typedef ptrdiff_t	difference_type;
		typedef const T*	pointer;
		typedef const T&	reference;
	};

	/*
	** -------------------------- BIDIRECTIONAL OPERATORS ---------------------------
	*/
	template < class Category, class T, class Node >
	class bidirectional : public ft::iterator_traits< T >
	{
		public:
		/* ---- DEFINE ---- */
			typedef typename ft::iterator_traits< T >::value_type		value_type;
			typedef typename ft::iterator_traits< T >::difference_type	difference_type;
			typedef typename ft::iterator_traits< T >::pointer			pointer;
			typedef typename ft::iterator_traits< T >::reference		reference;
			typedef Category											iterator_category;

		/* ---- MEMBER FUNCTIONS ----- */
			bidirectional();
			bidirectional(Node *ptr);
			bidirectional(const bidirectional& src);
			bidirectional		base() const;

			template < class Cat2, class T2, class Node2 >
			bidirectional(const bidirectional< Cat2, T2, Node2 >& src);

			bidirectional&		operator=(const bidirectional& rhs);
			~bidirectional();
			bidirectional&		operator++();
			bidirectional		operator++(int);
			bool				operator==(bidirectional const &rhs) const;
			bool				operator!=(bidirectional const &rhs) const;
			reference			operator*() const;
			pointer				operator->() const;
			bidirectional&		operator--();
			bidirectional		operator--(int);

			reference			_deref_ptr(value_type *p) const;
			template < class ClassNode >
			reference			_deref_ptr(ClassNode *node) const;
			void				_increment(value_type *p);
			template < class ClassNode >
			void				_increment(ClassNode *node);
			void				_decrement(value_type *p);
			template < class ClassNode >
			void				_decrement(ClassNode *node);

			Node*				_ptr;
	};

	/*
	** ------------------------- RANDOM_ACCESS OPERATORS -------------------------
	*/
	template < class Category, class T, class Node >
	class random_access : public bidirectional< Category, typename ft::iterator_traits< T >::value_type, Node >
	{
		public:
		/* ---- DEFINE ---- */
			typedef typename ft::iterator_traits< T >::value_type		value_type;
			typedef typename ft::iterator_traits< T >::difference_type	difference_type;
			typedef typename ft::iterator_traits< T >::pointer			pointer;
			typedef typename ft::iterator_traits< T >::reference		reference;
			typedef Category											iterator_category;

		/* ---- MEMBER FUNCTIONS ----- */
			random_access();
			random_access(Node *ptr);
			random_access(const random_access& src);
			random_access(const bidirectional< Category, value_type, Node >& src);
			~random_access();

			random_access		operator+(difference_type n) const;
			random_access		operator-(difference_type n) const;
			bool				operator<(random_access const &rhs) const;
			bool				operator>(random_access const &rhs) const;
			bool				operator<=(random_access const &rhs) const;
			bool				operator>=(random_access const &rhs) const;
			random_access		&operator+=(difference_type n);
			random_access		&operator-=(difference_type n);
			reference			operator[](difference_type n) const;
	};

	/*
	** ---------------------------- REVERSE_ITERATOR -----------------------------
	*/
	template < class Iter >
	class reverse_iterator
	{
		public:
		/* ---- DEFINE ---- */
			typedef Iter								iterator_type;
			typedef typename Iter::value_type			value_type;
			typedef typename Iter::difference_type		difference_type;
			typedef typename Iter::pointer				pointer;
			typedef typename Iter::reference			reference;
			typedef typename Iter::iterator_category	iterator_category;

		/* ---- MEMBER FUNCTIONS ----- */
			reverse_iterator();
			explicit reverse_iterator(iterator_type it);
			reverse_iterator(const reverse_iterator< Iter >& rev_it);
			template < class Iter2 >
			reverse_iterator(const reverse_iterator< Iter2 >& src);
			iterator_type		base() const;
			~reverse_iterator();

			reference			operator*() const;
			reverse_iterator	operator+(difference_type n) const;
			reverse_iterator&	operator++();
			reverse_iterator	operator++(int);
			reverse_iterator&	operator+=(difference_type n);
			reverse_iterator	operator-(difference_type n) const;
			reverse_iterator&	operator--();
			reverse_iterator	operator--(int);
			reverse_iterator&	operator-=(difference_type n);
			pointer				operator->() const;
			reference			operator[](difference_type n) const;
			bool				operator==(reverse_iterator const &rhs) const;
			bool				operator!=(reverse_iterator const &rhs) const;

			iterator_type		_base;
	};

	/*
	** ---------------------------- NON-MEMBER FUNCTION -----------------------------
	*/

	/* RANDOM ACCESS ITERATOR */
	/* operator+ */
	template < class Category, class T, class Node >
	random_access< Category, T, Node >								operator+(typename random_access< Category, T, Node >::difference_type n,
																		const random_access< Category, T, Node >& it);
	/* operator- */
	template < class Category, class T, class Node >
	typename random_access< Category, T, Node >::difference_type	operator-(const random_access< Category, T, Node >& lhs,
																		const random_access< Category, T, Node >& rhs);

	/* REVERSE ITERATOR */
	/* relational operators */
	template <class Iterator>
	bool															operator== (const reverse_iterator<Iterator>& lhs,
																			const reverse_iterator<Iterator>& rhs);
	template <class Iterator>
	bool															operator!= (const reverse_iterator<Iterator>& lhs,
																			const reverse_iterator<Iterator>& rhs);
	template <class Iterator>
	bool															operator<  (const reverse_iterator<Iterator>& lhs,
																			const reverse_iterator<Iterator>& rhs);
	template <class Iterator>
	bool															operator<= (const reverse_iterator<Iterator>& lhs,
																			const reverse_iterator<Iterator>& rhs);
	template <class Iterator>
	bool															operator>  (const reverse_iterator<Iterator>& lhs,
																			const reverse_iterator<Iterator>& rhs);
	template <class Iterator>
	bool															operator>= (const reverse_iterator<Iterator>& lhs,
																			const reverse_iterator<Iterator>& rhs);
	/* operator+ */
	template < class Iterator >
	reverse_iterator< Iterator >									operator+(typename reverse_iterator< Iterator >::difference_type n,
																				const reverse_iterator< Iterator >& rev_it);
	/* operator- */
	template < class Iterator >
	typename reverse_iterator< Iterator >::difference_type			operator-(const reverse_iterator<Iterator>& lhs,
																				const reverse_iterator<Iterator>& rhs);

}

# include "Iterator.tpp"

#endif
