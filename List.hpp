/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   List.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olidon <olidon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 11:26:06 by olidon            #+#    #+#             */
/*   Updated: 2021/03/13 14:41:20 by olidon           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEMPLATE_LIST_HPP
# define TEMPLATE_LIST_HPP

# include <iostream>
# include <string>
# include <memory>
# include <algorithm>
# include "ClassListNodeBase.hpp"
# include "Iterator.hpp"

namespace ft
{
	template< typename T, class Alloc = std::allocator< T > >
	class list {

		public:

		/* ---- DEFINE ---- */
			typedef T																									value_type;
			typedef Alloc																								allocator_type;
			typedef typename allocator_type::reference																	reference;
			typedef typename allocator_type::const_reference															const_reference;
			typedef typename ft::bidirectional< bidirectional_iterator_tag, T, list_node_base< T > >					iterator;
			typedef typename ft::bidirectional< bidirectional_iterator_tag, const T, list_node_base< T > >				const_iterator;
			typedef typename ft::reverse_iterator< iterator >															reverse_iterator;
			typedef typename ft::reverse_iterator< const_iterator >														const_reverse_iterator;
			typedef T*																									pointer;
			typedef const T*																							const_pointer;
			typedef typename ft::bidirectional< bidirectional_iterator_tag, T, list_node_base< T > >::difference_type	difference_type;
			typedef size_t																								size_type;

		/* ---- MEMBER FUNCTIONS ----- */
			/* constructor */
			explicit list(const allocator_type& alloc = allocator_type()); 	// default
			explicit list(size_type n, const value_type& val = value_type(),
				const allocator_type& alloc = allocator_type());			// fill
			template < class InputIterator >
			list(InputIterator first, InputIterator last,
				const allocator_type& alloc = allocator_type());			// range
			list(const list< T, Alloc >& x);								// Copy
			/* destructor */
			~list();
			/* operator= */
			list< T, Alloc >&		operator=(const list< T, Alloc >& x);

		/* ---- ITERATORS ---- */
			/* begin */
			iterator				begin();
			const_iterator			begin() const;
			/* end */
			iterator				end();
			const_iterator			end() const;
			/* rbegin */
			reverse_iterator		rbegin();
			const_reverse_iterator	rbegin() const;
			/* rend */
			reverse_iterator		rend();
			const_reverse_iterator	rend() const;

		/* ---- CAPACITY ---- */
			/* empty */
			bool					empty() const;
			/* size */
			size_type				size() const;
			/* max_size */
			size_type				max_size() const;

		/* ---- ELEMENT ACCESS ---- */
			/* front */
			reference				front();
			const_reference			front() const;
			/* back */
			reference				back();
			const_reference			back() const;

		/* ---- MODIFIERS ---- */
			/* assign */
			template < class InputIterator >
			void					assign(InputIterator first,
											InputIterator last);	// range
			void					assign(size_type n,
											const value_type& val);	// fill
			/* push_front */
			void					push_front(const value_type& val);
			/* pop_front */
			void					pop_front();
			/* push_back */
			void					push_back(const value_type& val);
			/* pop_back */
			void					pop_back();
			/* insert */
			iterator				insert(iterator position,
									const value_type& val);			// single element
			void					insert(iterator position, size_type n,
									const value_type& val);			// fill
			template < class InputIterator >
			void					insert(iterator position, InputIterator first,
									InputIterator last);			// range
			/* erase */
			iterator				erase(iterator position);
			iterator				erase(iterator first, iterator last);
			/* swap */
			void					swap(list& x);
			/* resize */
			void					resize(size_type n, value_type val = value_type());
			/* clear */
			void					clear();

		/* ---- OPERATIONS ---- */
			/* splice */
			void					splice(iterator position, list& x);	// entire list
			void					splice(iterator position, list& x,
														iterator i);	// single element
			void					splice(iterator position, list& x, iterator first,
													iterator last);		// element range
			/* remove */
			void					remove(const value_type& val);
			/* remove_if */
			template <class Predicate>
			void					remove_if(Predicate pred);
			/* unique */
			void					unique();
			template <class BinaryPredicate>
			void					unique(BinaryPredicate binary_pred);
			/* merge */
			void					merge(list& x);
			template <class Compare>
			void					merge(list& x, Compare comp);
			/* sort */
			void					sort();
			template <class Compare>
			void					sort(Compare comp);
			/* reverse */
			void					reverse();


		private:

			typedef ft::list_node_base< T >*													node;
			typedef typename allocator_type::template rebind< ft::list_node_base< T > >::other	node_allocator_type;

			node_allocator_type	_my_node_alloc;
			allocator_type		_my_alloc;
			size_type			_size;
			node 				_begin;
			node 				_end;

			template< class InputIterator >
			void			insert_values(iterator position, InputIterator first, InputIterator last, int);
			template< class InputIterator >
			void			insert_values(iterator position, InputIterator first, InputIterator last, void *);
			void			insert_values_from_numbers(iterator position, size_type n, const value_type& val);
			template< class InputIterator >
			void			insert_values_from_iterators(iterator position, InputIterator first, InputIterator last);

			template< class InputIterator >
			void			add_values(InputIterator first, InputIterator last, int);
			template< class InputIterator >
			void			add_values(InputIterator first, InputIterator last, void *);
			void			add_values_from_numbers(size_type n, const value_type & val);
			template< class InputIterator >
			void			add_values_from_iterators(InputIterator first, InputIterator last);

			void			init_node();
			void			link_node(const value_type& val, node prev, node next);
			void			just_link_node(node prev, node next, node newprev, node newnext);
			node			create_node(const value_type& val, node prev, node next);
			node			create_node_no_val(node prev, node next);
			void			unlink_node(node prev, node next);
			void			just_unlink_node(node prev, node next);
			void			delete_node(node n);
			void			delete_node_no_val(node n);
			// void			ft_print_list(); // a enlever

			template< class U >
			struct val_is_integral							{typedef void* type;};
			template< >
			struct val_is_integral< bool >					{typedef int type;};
			template< >
			struct val_is_integral< char >					{typedef int type;};
			template< >
			struct val_is_integral< signed char > 			{typedef int type;};
			template< >
			struct val_is_integral< unsigned char >			{typedef int type;};
			template< >
			struct val_is_integral< wchar_t >				{typedef int type;};
			template< >
			struct val_is_integral< short >					{typedef int type;};
			template< >
			struct val_is_integral< unsigned short >		{typedef int type;};
			template< >
			struct val_is_integral<int>						{typedef int type;};
			template< >
			struct val_is_integral< unsigned int >			{typedef int type;};
			template< >
			struct val_is_integral< long >					{typedef int type;};
			template< >
			struct val_is_integral< unsigned long >			{typedef int type;};
			template< >
			struct val_is_integral< long long >				{typedef int type;};
			template< >
			struct val_is_integral< unsigned long long >	{typedef int type;};
			template< >
			struct val_is_integral< __int128_t >			{typedef int type;};
			template< >
			struct val_is_integral< __uint128_t >			{typedef int type;};
	};

	/* ---- NON MEMBER FUNCTION OVERLOADS ---- */
		/* relational operators (list) */
		template < typename T, class Alloc >
		bool					operator==(const list< T, Alloc >& lhs,
												const list< T, Alloc >& rhs);
		template < typename T, class Alloc >
		bool					operator!=(const list< T, Alloc >& lhs,
												const list< T, Alloc >& rhs);
		template < typename T, class Alloc >
		bool					operator<(const list< T, Alloc >& lhs,
												const list< T, Alloc >& rhs);
		template < typename T, class Alloc >
		bool					operator<=(const list< T, Alloc >& lhs,
												const list< T, Alloc >& rhs);
		template < typename T, class Alloc >
		bool					operator>(const list< T, Alloc >& lhs,
												const list< T, Alloc >& rhs);
		template < typename T, class Alloc >
		bool					operator>=(const list< T, Alloc >& lhs,
												const list< T, Alloc >& rhs);
		/* swap (list) */
		template < typename T, class Alloc >
		void					swap(list< T, Alloc >& x, list< T, Alloc >& y);

}

# include "List.tpp"

#endif
