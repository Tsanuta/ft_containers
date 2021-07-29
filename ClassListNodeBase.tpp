/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClassListNodeBase.tpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olidon <olidon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 15:27:15 by olidon            #+#    #+#             */
/*   Updated: 2021/03/13 14:26:52 by olidon           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ClassListNodeBase.hpp"

namespace ft
{

	template< typename T >
	list_node_base< T >::list_node_base(const value_type &val, node *prev, node *next) : next(next), prev(prev), value(val)
	{
	}

	template< typename T >
	list_node_base< T >::~list_node_base()
	{
	}

	template< typename T >
	list_node_base< T >::list_node_base(node const &src) : next(src.next), prev(src.prev), value(src.value)
	{
	}

	template< typename T >
	list_node_base< T >			&list_node_base< T >::operator=(node const &rhs)
	{
		this->prev = rhs.prev;
		this->next = rhs.next;
		this->value = rhs.value;
		return *this;
	}

	template< typename T >
	list_node_base< T >			&list_node_base< T >::operator++()
	{
		return (*next);
	}

	template< typename T >
	list_node_base< T >			list_node_base< T >::operator++(int)
	{
		list_node_base<T>	postinc(*this);

		operator++();
		return postinc;
	}

	template< typename T >
	typename list_node_base< T >::reference		list_node_base< T >::operator*()
	{
		return this->value;
	}

	template< typename T >
	list_node_base< T >			&list_node_base< T >::operator--()
	{
		return (*prev);
	}

	template< typename T >
	list_node_base< T >			list_node_base< T >::operator--(int)
	{
		list_node_base<T>	postdecc(*this);

		operator--();
		return postdecc;
	}

}
