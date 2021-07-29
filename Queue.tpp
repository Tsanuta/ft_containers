/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Queue.tpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olidon <olidon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 17:26:53 by olidon            #+#    #+#             */
/*   Updated: 2021/03/14 18:03:17 by olidon           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Queue.hpp"

namespace ft
{

	/*
	** ------------------------- MEMBER FUNCTIONS -----------------------------
	*/

	/* constructor */
	template < class T, class Container >
	queue< T, Container >::queue(const container_type& ctnr) : _container(ctnr)
	{
	}

	/* empty */
	template < class T, class Container >
	bool												queue< T, Container >::empty() const
	{
		return (_container.empty());
	}

	/* size */
	template < class T, class Container >
	typename queue< T, Container >::size_type			queue< T, Container >::size() const
	{
		return (_container.size());
	}

	/* front */
	template < class T, class Container >
	typename queue< T, Container >::value_type&			queue< T, Container >::front()
	{
		return (_container.front());
	}

	template < class T, class Container >
	typename queue< T, Container >::value_type const &	queue< T, Container >::front() const
	{
		return (_container.front());
	}

	/* back */
	template < class T, class Container >
	typename queue< T, Container >::value_type&			queue< T, Container >::back()
	{
		return (_container.back());
	}

	template < class T, class Container >
	typename queue< T, Container >::value_type const &	queue< T, Container >::back() const
	{
		return (_container.back());
	}

	/* push */
	template < class T, class Container >
	void												queue< T, Container >::push(const value_type& val)
	{
		return (_container.push_back(val));
	}

	/* pop */
	template < class T, class Container >
	void												queue< T, Container >::pop()
	{
		return (_container.pop_front());
	}

	/*
	** ------------------- NON MEMBER FUNCTION OVERLOADS -----------------------
	*/

	/* relational operators */
	template < class T, class Container >
	bool						operator==(const queue< T, Container >& lhs, const queue< T, Container >& rhs)
	{
		return (operator==(lhs._container, rhs._container));
	}

	template < class T, class Container >
	bool						operator!=(const queue< T, Container >& lhs, const queue< T, Container >& rhs)
	{
		return (!(operator==(lhs, rhs)));
	}

	template < class T, class Container >
	bool						operator<(const queue< T, Container >& lhs, const queue< T, Container >& rhs)
	{
		return (operator<(lhs._container, rhs._container));
	}

	template < class T, class Container >
	bool						operator<=(const queue< T, Container >& lhs, const queue< T, Container >& rhs)
	{
		return (!(operator<(rhs, lhs)));
	}

	template < class T, class Container >
	bool						operator>(const queue< T, Container >& lhs, const queue< T, Container >& rhs)
	{
		return (operator<(rhs, lhs));
	}

	template < class T, class Container >
	bool						operator>=(const queue< T, Container >& lhs, const queue< T, Container >& rhs)
	{
		return (!(operator<(lhs, rhs)));
	}

}
