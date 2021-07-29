/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Queue.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olidon <olidon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 17:27:48 by olidon            #+#    #+#             */
/*   Updated: 2021/03/15 11:30:37 by olidon           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEMPLATE_QUEUE_HPP
# define TEMPLATE_QUEUE_HPP

# include <iostream>
# include <string>
# include <deque>

namespace ft
{
	template < class T, class Container = std::deque< T > >
	class queue {

		public:
		/* ---- DEFINE ---- */
			typedef T			value_type;
			typedef Container	container_type;
			typedef size_t		size_type;

		/* ---- MEMBER FUNCTIONS ----- */
			/* constructor */
			explicit			queue(const container_type& ctnr = container_type());
			/* empty */
			bool				empty() const;
			/* size */
			size_type			size() const;
			/* front */
			value_type&			front();
			const value_type&	front() const;
			/* back */
			value_type&			back();
			const value_type&	back() const;
			/* push */
			void				push(const value_type& val);
			/* pop */
			void				pop();

			template < class T2, class Container2 >
			friend bool				operator==(const queue< T2, Container2 >& lhs, const queue< T2, Container2 >& rhs);
			template < class T2, class Container2 >
			friend bool				operator<(const queue< T2, Container2 >& lhs, const queue< T2, Container2 >& rhs);

		protected:
			container_type		_container;

	};

	/* ---- NON MEMBER FUNCTION OVERLOADS ---- */
	/* relational operators */
	template < class T, class Container >
	bool						operator==(const queue< T, Container >& lhs, const queue< T, Container >& rhs);
	template < class T, class Container >
	bool						operator!=(const queue< T, Container >& lhs, const queue< T, Container >& rhs);
	template < class T, class Container >
	bool						operator<(const queue< T, Container >& lhs, const queue< T, Container >& rhs);
	template < class T, class Container >
	bool						operator<=(const queue< T, Container >& lhs, const queue< T, Container >& rhs);
	template < class T, class Container >
	bool						operator>(const queue< T, Container >& lhs, const queue< T, Container >& rhs);
	template < class T, class Container >
	bool						operator>=(const queue< T, Container >& lhs, const queue< T, Container >& rhs);

}

# include "Queue.tpp"

#endif
