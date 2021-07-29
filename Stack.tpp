/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stack.tpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olidon <olidon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 16:19:12 by olidon            #+#    #+#             */
/*   Updated: 2021/03/14 18:08:58 by olidon           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Stack.hpp"

namespace ft
{
	/*
	** ------------------------- MEMBER FUNCTIONS -----------------------------
	*/

	/* constructor */
	template < class T, class Container >
	stack< T, Container >::stack(const container_type& ctnr) : _container(ctnr)
	{
	}

	/* empty */
	template < class T, class Container >
	bool												stack< T, Container >::empty() const
	{
		return (_container.empty());
	}

	/* size */
	template < class T, class Container >
	typename stack< T, Container >::size_type			stack< T, Container >::size() const
	{
		return (_container.size());
	}

	/* top */
	template < class T, class Container >
	typename stack< T, Container >::value_type&			stack< T, Container >::top()
	{
		return (_container.back());
	}

	template < class T, class Container >
	typename stack< T, Container >::value_type const &	stack< T, Container >::top() const
	{
		return (_container.back());
	}

	/* push */
	template < class T, class Container >
	void												stack< T, Container >::push(const value_type& val)
	{
		return (_container.push_back(val));
	}

	/* pop */
	template < class T, class Container >
	void												stack< T, Container >::pop()
	{
		return (_container.pop_back());
	}

	/*
	** ------------------- NON MEMBER FUNCTION OVERLOADS -----------------------
	*/

	/* relational operators */
	template < class T, class Container >
	bool						operator==(const stack< T, Container >& lhs, const stack< T, Container >& rhs)
	{
		return (operator==(lhs._container, rhs._container));
	}

	template < class T, class Container >
	bool						operator!=(const stack< T, Container >& lhs, const stack< T, Container >& rhs)
	{
		return (!(operator==(lhs, rhs)));
	}

	template < class T, class Container >
	bool						operator<(const stack< T, Container >& lhs, const stack< T, Container >& rhs)
	{
		return (operator<(lhs._container, rhs._container));
	}

	template < class T, class Container >
	bool						operator<=(const stack< T, Container >& lhs, const stack< T, Container >& rhs)
	{
		return (!(operator<(rhs, lhs)));
	}

	template < class T, class Container >
	bool						operator>(const stack< T, Container >& lhs, const stack< T, Container >& rhs)
	{
		return (operator<(rhs, lhs));
	}

	template < class T, class Container >
	bool						operator>=(const stack< T, Container >& lhs, const stack< T, Container >& rhs)
	{
		return (!(operator<(lhs, rhs)));
	}

}
