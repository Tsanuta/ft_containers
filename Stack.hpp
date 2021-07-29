/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olidon <olidon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 16:19:09 by olidon            #+#    #+#             */
/*   Updated: 2021/03/15 11:25:48 by olidon           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEMPLATE_STACK_HPP
# define TEMPLATE_STACK_HPP

# include <iostream>
# include <string>
# include <deque>

namespace ft
{

	template < class T, class Container = std::deque< T > >
	class stack {

		public:

		/* ---- DEFINE ---- */
			typedef T			value_type;
			typedef Container	container_type;
			typedef size_t		size_type;

		/* ---- MEMBER FUNCTIONS ----- */
			/* constructor */
			explicit			stack(const container_type& ctnr = container_type());

			/* empty */
			bool				empty() const;
			/* size */
			size_type			size() const;
			/* top */
			value_type&			top();
			const value_type&	top() const;
			/* push */
			void				push(const value_type& val);
			/* pop */
			void				pop();


			template < class T2, class Container2 >
			friend bool				operator==(const stack< T2, Container2 >& lhs, const stack< T2, Container2 >& rhs);
			template < class T2, class Container2 >
			friend bool				operator<(const stack< T2, Container2 >& lhs, const stack< T2, Container2 >& rhs);

		protected:
			container_type		_container;

	};

	/* ---- NON MEMBER FUNCTION OVERLOADS ---- */
	/* relational operators */

	template < class T, class Container >
	bool						operator==(const stack< T, Container >& lhs, const stack< T, Container >& rhs);
	template < class T, class Container >
	bool						operator!=(const stack< T, Container >& lhs, const stack< T, Container >& rhs);
	template < class T, class Container >
	bool						operator<(const stack< T, Container >& lhs, const stack< T, Container >& rhs);
	template < class T, class Container >
	bool						operator<=(const stack< T, Container >& lhs, const stack< T, Container >& rhs);
	template < class T, class Container >
	bool						operator>(const stack< T, Container >& lhs, const stack< T, Container >& rhs);
	template < class T, class Container >
	bool						operator>=(const stack< T, Container >& lhs, const stack< T, Container >& rhs);

}

# include "Stack.tpp"

#endif
