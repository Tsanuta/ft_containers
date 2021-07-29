/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClassMapNodeBase.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olidon <olidon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 15:27:15 by olidon            #+#    #+#             */
/*   Updated: 2021/03/13 14:42:47 by olidon           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEMPLATE_CLASSMAPNODEBASE_HPP
# define TEMPLATE_CLASSMAPNODEBASE_HPP

# include <iostream>
# include <string>
# include <utility>
# include "Iterator.hpp"

namespace ft
{
	template< typename Key, typename T >
	class map_node_base {
		public:

		/* ---- DEFINE ---- */
			typedef Key													key_type;
			typedef T													mapped_type;
			typedef std::pair< const key_type, mapped_type >			value_type;
			typedef typename iterator_traits< value_type >::reference	reference;
			typedef typename iterator_traits< value_type >::pointer		pointer;
			typedef map_node_base< Key, T >								node;

		/* ---- MEMBER FUNCTIONS ----- */
			map_node_base(const value_type &val, node *parent, node *left, node *right);
			map_node_base(node const &src);
			node		&operator=(node const &rhs);
			~map_node_base();

			node		&operator++();
			node		operator++(int);
			reference	operator*();
			node		&operator--();
			node		operator--(int);

			node*		parent;
			node*		left;
			node*		right;
			value_type	value;
			bool		is_end;

		private:
			map_node_base();

	};
}

# include "ClassMapNodeBase.tpp"

#endif
