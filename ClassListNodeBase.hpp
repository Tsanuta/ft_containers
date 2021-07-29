/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClassListNodeBase.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olidon <olidon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 15:27:15 by olidon            #+#    #+#             */
/*   Updated: 2021/03/13 14:41:33 by olidon           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEMPLATE_CLASSLISTNODEBASE_HPP
# define TEMPLATE_CLASSLISTNODEBASE_HPP

# include <iostream>
# include <string>
# include "Iterator.hpp"

namespace ft
{
	template< typename T >
	class list_node_base {
		public:

		/* ---- DEFINE ---- */
			typedef T											value_type;
			typedef typename iterator_traits< T >::reference	reference;
			typedef typename iterator_traits< T >::pointer		pointer;
			typedef list_node_base< T >							node;

		/* ---- MEMBER FUNCTIONS ----- */
			list_node_base(const value_type &val, node *prev, node *next);
			list_node_base(node const &src);
			node		&operator=(node const &rhs);
			~list_node_base();

			node		&operator++();
			node		operator++(int);
			reference	operator*();
			node		&operator--();
			node		operator--(int);

			node*		next;
			node*		prev;
			value_type	value;

		private:
			list_node_base();

	};
}

# include "ClassListNodeBase.tpp"

#endif
