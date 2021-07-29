/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClassMapNodeBase.tpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olidon <olidon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 15:27:15 by olidon            #+#    #+#             */
/*   Updated: 2021/03/13 14:32:01 by olidon           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ClassMapNodeBase.hpp"

namespace ft
{

	template< typename Key, typename T >
	map_node_base< Key, T >::map_node_base(const value_type &val, node *parent, node *left, node *right) : parent(parent), left(left), right(right), value(val), is_end(false)
	{
	}

	template< typename Key, typename T >
	map_node_base< Key, T >::~map_node_base()
	{
	}

	template< typename Key, typename T >
	map_node_base< Key, T >::map_node_base(node const &src) : parent(src.parent), left(src.left), right(src.right), value(src.value), is_end(src.is_end)
	{
	}

	template< typename Key, typename T >
	map_node_base< Key, T >			&map_node_base< Key, T >::operator=(node const &rhs)
	{
		if (this != rhs)
		{
			this->parent = rhs.parent;
			this->left = rhs.left;
			this->right = rhs.right;
			this->is_end = rhs.is_end;
			this->value = rhs.value;
		}
		return *this;
	}

	template< typename Key, typename T >
	map_node_base< Key, T >			&map_node_base< Key, T >::operator++()
	{
		node*	p;
		node*	curr = this;

		if (!curr)
			return (*this);
		else if (curr->right)
		{
			curr = curr->right;
			while(curr->left && !curr->left->is_end)
				curr = curr->left;
		}
		else
		{
			p = curr->parent;
			while (p && curr == p->right)
			{
				curr = p;
				p = p->parent;
			}
			curr = p;
		}
		return *curr;
	}

	template< typename Key, typename T >
	map_node_base< Key, T >			map_node_base< Key, T >::operator++(int)
	{
		map_node_base< Key, T >	postinc(*this);

		operator++();
		return postinc;
	}

	template< typename Key, typename T >
	typename map_node_base< Key, T >::reference		map_node_base< Key, T >::operator*()
	{
		return this->value;
	}

	template< typename Key, typename T >
	map_node_base< Key, T >			&map_node_base< Key, T >::operator--()
	{
		node*	p;
		node*	curr = this;

		if (!curr)
			return (*this);
		else if (curr->left)
		{
			curr = curr->left;
			while(curr->right && !curr->right->is_end)
				curr = curr->right;
		}
		else
		{
			p = curr->parent;
			while (p && curr == p->left)
			{
				curr = p;
				p = p->parent;
			}
			curr = p;
		}
		return *curr;
	}

	template< typename Key, typename T >
	map_node_base< Key, T >			map_node_base< Key, T >::operator--(int)
	{
		map_node_base< Key, T >	postdecc(*this);

		operator--();
		return postdecc;
	}

}
