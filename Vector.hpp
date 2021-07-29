/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olidon <olidon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 11:26:06 by olidon            #+#    #+#             */
/*   Updated: 2021/03/13 14:44:57 by olidon           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEMPLATE_VECTOR_HPP
# define TEMPLATE_VECTOR_HPP

# include <iostream>
# include <string>
# include <memory>
# include <algorithm>
# include <stdexcept>
# include "Iterator.hpp"

namespace ft
{
	template< typename T, class Alloc = std::allocator< T > >
	class vector {

		public:

		/* ---- DEFINE ---- */
			typedef T																							value_type;
			typedef Alloc																						allocator_type;
			typedef typename allocator_type::reference															reference;
			typedef typename allocator_type::const_reference													const_reference;
			typedef typename ft::random_access< random_access_iterator_tag, T, value_type >						iterator;
			typedef typename ft::random_access< random_access_iterator_tag, const T, value_type >				const_iterator;
			typedef typename ft::reverse_iterator< iterator >													reverse_iterator;
			typedef typename ft::reverse_iterator< const_iterator >												const_reverse_iterator;
			typedef T*																							pointer;
			typedef const T*																					const_pointer;
			typedef typename ft::random_access< random_access_iterator_tag, T, value_type >::difference_type	difference_type;
			typedef size_t																						size_type;

		/* ---- MEMBER FUNCTIONS ----- */
			/* constructor */
			explicit vector(const allocator_type& alloc = allocator_type());	// default
			explicit vector(size_type n, const value_type& val = value_type(),
							const allocator_type& alloc = allocator_type());	// fill
			template < class InputIterator >
			vector(InputIterator first, InputIterator last,
							const allocator_type& alloc = allocator_type());	// range
			vector(const vector& x);											// copy
			/* destructor */
			~vector();
			/* operator= */
			vector< T, Alloc >&		operator=(const vector< T, Alloc >& x);

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
			/* size */
			size_type				size() const;
			/* max_size */
			size_type				max_size() const;
			/* resize */
			void					resize(size_type n, value_type val = value_type());
			/* capacity */
			size_type				capacity() const;
			/* empty */
			bool					empty() const;
			/* reserve */
			void					reserve(size_type n);

		/* ---- ELEMENT ACCESS ---- */
			/* operator[] */
			reference				operator[](size_type n);
			const_reference			operator[](size_type n) const;
			/* at */
			reference				at(size_type n);
			const_reference			at(size_type n) const;
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
			void					swap(vector& x);
			/* clear */
			void					clear();

		private:

			allocator_type		_my_alloc;
			pointer 			_begin;
			pointer 			_end;
			pointer 			_end_cap;

			/* insert utils */
			template < class InputIterator >
			void		_insert_values(iterator position, InputIterator first, InputIterator last, int);
			template < class InputIterator >
			void		_insert_values(iterator position, InputIterator first, InputIterator last, void *);
			void		_insert_values_from_numbers(iterator position, size_type n, const value_type& val);
			template < class InputIterator >
			void		_insert_values_from_iterators(iterator position, InputIterator first, InputIterator last);
			/* add values utils */
			template < class InputIterator >
			void		_add_values(InputIterator first, InputIterator last, int);
			template < class InputIterator >
			void		_add_values(InputIterator first, InputIterator last, void *);
			void		_add_values_from_numbers(size_type n, const value_type & val);
			template < class InputIterator >
			void		_add_values_from_iterators(InputIterator first, InputIterator last);
			/* assign utils */
			template < class InputIterator >
			void		_assign_values(InputIterator first, InputIterator last, int);
			template < class InputIterator >
			void		_assign_values(InputIterator first, InputIterator last, void *);
			void		_assign_values_from_numbers(size_type n, const value_type & val);
			/* allocation utils */
			void		_vallocate(size_type n);
			void		_vdeallocate();
			/* construction utils */
			void		_construct_at_end(size_type n, const_reference x);
			template < class InputIterator >
			void		_construct_at_end_it(InputIterator first, InputIterator last);
			template < class InputIterator >
			void		_construct_at_end_itn(InputIterator *first, InputIterator last, size_type n);
			void		_construct_backward(pointer _begin1, pointer _end1, vector< T, Alloc > &v);
			void		_construct_forward(pointer _begin1, pointer _end1, vector< T, Alloc > &v);
			void		_destruct_at_end(pointer _new_last);
			/* function utils */
			void		_split_buffer(size_type n, size_type old_size, vector< T, Alloc > &v);
			void		_push_back_slow_path(const_reference x);
			void		_swap_out_circular_buffer(vector< T, Alloc > &v);
			pointer		_swap_out_circular_buffer2(vector< T, Alloc > &v, pointer p);
			size_type	_recommended_size(size_type new_size);
			void		_append(size_type n, const reference x);
			pointer		_move(pointer first, pointer last, pointer result);
			/* exception */
			void		_throw_out_of_range() const;
			void		_throw_length_error();

			// void			ft_print_vector(); // a enlever


			template < class U >
			struct val_is_integral                     {typedef void* type;};
			template <>
			struct val_is_integral<bool>               {typedef int type;};
			template <>
			struct val_is_integral<char>               {typedef int type;};
			template <>
			struct val_is_integral<signed char>        {typedef int type;};
			template <>
			struct val_is_integral<unsigned char>      {typedef int type;};
			template <>
			struct val_is_integral<wchar_t>            {typedef int type;};
			template <>
			struct val_is_integral<short>              {typedef int type;};
			template <>
			struct val_is_integral<unsigned short>     {typedef int type;};
			template <>
			struct val_is_integral<int>                {typedef int type;};
			template <>
			struct val_is_integral<unsigned int>       {typedef int type;};
			template <>
			struct val_is_integral<long>               {typedef int type;};
			template <>
			struct val_is_integral<unsigned long>      {typedef int type;};
			template <>
			struct val_is_integral<long long>          {typedef int type;};
			template <>
			struct val_is_integral<unsigned long long> {typedef int type;};
			template <>
			struct val_is_integral<__int128_t>         {typedef int type;};
			template <>
			struct val_is_integral<__uint128_t>        {typedef int type;};
	};

	/* ---- NON MEMBER FUNCTION OVERLOADS ---- */
	/* relational operators (vector) */
	template < typename T, class Alloc >
	bool					operator==(const vector< T, Alloc >& lhs,
											const vector< T, Alloc >& rhs);
	template < typename T, class Alloc >
	bool					operator!=(const vector< T, Alloc >& lhs,
											const vector< T, Alloc >& rhs);
	template < typename T, class Alloc >
	bool					operator<(const vector< T, Alloc >& lhs,
											const vector< T, Alloc >& rhs);
	template < typename T, class Alloc >
	bool					operator<=(const vector< T, Alloc >& lhs,
											const vector< T, Alloc >& rhs);
	template < typename T, class Alloc >
	bool					operator>(const vector< T, Alloc >& lhs,
											const vector< T, Alloc >& rhs);
	template < typename T, class Alloc >
	bool					operator>=(const vector< T, Alloc >& lhs,
											const vector< T, Alloc >& rhs);
	/* swap (vector) */
	template < typename T, class Alloc >
	void					swap(vector< T, Alloc >& x, vector< T, Alloc >& y);

}

# include "Vector.tpp"

#endif
