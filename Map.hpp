/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olidon <olidon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 18:04:07 by olidon            #+#    #+#             */
/*   Updated: 2021/03/13 14:42:34 by olidon           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEMPLATE_MAP_HPP
# define TEMPLATE_MAP_HPP

# include <iostream>
# include <string>
# include <memory>		// for allocator
# include <functional>	// for less
# include <utility>		// for pair
# include "ClassMapNodeBase.hpp"
# include "Iterator.hpp"

namespace ft
{
	template< typename Key, typename T, class Compare = std::less< Key >, class Alloc = std::allocator< std::pair< const Key, T > > >
	class map {

		public:

		/* ---- DEFINE ---- */
			typedef Key																									key_type;
			typedef T																									mapped_type;
			typedef std::pair< const key_type, mapped_type >															value_type;
			typedef Compare																								key_compare;
			class value_compare
			{	// in C++98, it is required to inherit binary_function<value_type,value_type,bool>
				friend class map;
				protected:
					Compare comp;
					value_compare (Compare c) : comp(c) {}	// constructed with map's comparison object
				public:
					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;
					bool operator()(const value_type& x, const value_type& y) const {
						return comp(x.first, y.first); }
			};
			typedef Alloc																									allocator_type;
			typedef typename allocator_type::reference																		reference;
			typedef typename allocator_type::const_reference																const_reference;
			typedef typename ft::bidirectional< bidirectional_iterator_tag, value_type, map_node_base< Key, T > >			iterator;
			typedef typename ft::bidirectional< bidirectional_iterator_tag, const value_type, map_node_base< Key, T > >		const_iterator;
			typedef typename ft::reverse_iterator< iterator >																reverse_iterator;
			typedef typename ft::reverse_iterator< const_iterator >															const_reverse_iterator;
			typedef value_type*																								pointer;
			typedef const value_type*																						const_pointer;
			typedef typename ft::bidirectional< bidirectional_iterator_tag, T, map_node_base< Key, T > >::difference_type	difference_type;
			typedef size_t																									size_type;

		/* ---- MEMBER FUNCTIONS ----- */
			/* constructor */
			explicit map(const key_compare& comp = key_compare(),
						const allocator_type& alloc = allocator_type());	// empty
			template <class InputIterator>
			map(InputIterator first, InputIterator last,
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type());			// range
			map(const map& x);												// copy
			/* destructor */
			~map();
			/* operator= */
			map< Key, T, Compare, Alloc >&	operator= (const map< Key, T, Compare, Alloc >& x);

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

			/* operator[] */
			mapped_type&			operator[](const key_type& k);

		/* ---- MODIFIERS ---- */
			/* insert */
			std::pair< iterator, bool >	insert(const value_type& val);						// single element
			iterator					insert(iterator position, const value_type& val);	// with hint
			template <class InputIterator>
			void						insert(InputIterator first, InputIterator last);	// range
			/* erase */
			void						erase(iterator position);
			size_type					erase(const key_type& k);
			void						erase(iterator first, iterator last);
			/* swap */
			void						swap(map& x);
			/* clear */
			void						clear();

		/* ---- OBSERVERS ---- */
			/* key comp */
			key_compare					key_comp() const;
			/* value comp */
			value_compare				value_comp() const;

		/* ---- OPERATIONS ---- */
			/* find */
			iterator									find(const key_type& k);
			const_iterator								find(const key_type& k) const;
			/* count */
			size_type									count(const key_type& k) const;
			/* lower_bound */
			iterator									lower_bound(const key_type& k);
			const_iterator								lower_bound(const key_type& k) const;
			/* upper_bound */
			iterator									upper_bound(const key_type& k);
			const_iterator								upper_bound(const key_type& k) const;
			/* equal_range */
			std::pair< const_iterator, const_iterator >	equal_range(const key_type& k) const;
			std::pair< iterator, iterator >				equal_range(const key_type& k);

		private:

			typedef ft::map_node_base< Key, T >*													node;
			typedef typename allocator_type::template rebind< ft::map_node_base< Key, T > >::other	node_allocator_type;

			node_allocator_type	_my_node_alloc;
			allocator_type		_my_alloc;
			key_compare			_comp;
			size_type			_size;
			node 				_root;
			node				_begin;
			node				_end;

			void				_init_node();
			node				_create_node(const value_type& val, node parent, node left, node right);
			node				_create_node_no_val(node parent, node left, node right);
			void				_delete_node(node n);
			void				_delete_node_no_val(node n);
			node				_insert_node(node& root, node parent, const value_type& val);
			void				_add_node(node& root, node parent, const node& curr);
			node				_remove_node(node& curr);
			node				_search_node(const key_type& k) const;
			void				_reconnect_begin();
			void				_reconnect_end();

	};

}

# include "Map.tpp"

#endif
