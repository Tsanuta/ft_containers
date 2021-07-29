/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.tpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olidon <olidon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 18:03:15 by olidon            #+#    #+#             */
/*   Updated: 2021/03/13 14:42:26 by olidon           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Map.hpp"

namespace ft
{
	/*
	** ------------------------- MEMBER FUNCTIONS -----------------------------
	*/

	/* constructor */
	template< class Key, class T, class Compare, class Alloc >
	map< Key, T, Compare, Alloc >::map(const key_compare& comp, const allocator_type& alloc) : _my_node_alloc(alloc), _comp(comp)
	{
		_init_node();
	}

	template< class Key, class T, class Compare, class Alloc >
	template <class InputIterator>
	map< Key, T, Compare, Alloc >::map(InputIterator first, InputIterator last,
		const key_compare& comp, const allocator_type& alloc) : _my_node_alloc(alloc), _comp(comp)
	{
		_init_node();
		insert(first, last);
	}

	template< class Key, class T, class Compare, class Alloc >
	map< Key, T, Compare, Alloc >::map(const map< Key, T, Compare, Alloc >& x) : _comp(x._comp)
	{
		_init_node();
		insert(x.begin(), x.end());
	}

	/* destructor */
	template< class Key, class T, class Compare, class Alloc >
	map< Key, T, Compare, Alloc >::~map()
	{
		this->clear();
		_delete_node_no_val(_begin);
		_delete_node_no_val(_end);
		_size = 0;
	}

	/* operator= */
	template< class Key, class T, class Compare, class Alloc >
	map< Key, T, Compare, Alloc >&	map< Key, T, Compare, Alloc >::operator=(const map< Key, T, Compare, Alloc >& x)
	{
		if (this != &x)
		{
			this->_comp = x._comp;
			this->clear();
			this->insert(x.begin(), x.end());
		}
		return *this;
	}

	/* ---- ITERATORS ---- */
	/* begin */
	template< class Key, class T, class Compare, class Alloc >
	typename map< Key, T, Compare, Alloc >::iterator				map< Key, T, Compare, Alloc >::begin()
	{
		iterator		tmp(_begin);

		++tmp;
		if (!tmp._ptr)
			tmp = end();
		return (tmp);
	}

	template< class Key, class T, class Compare, class Alloc >
	typename map< Key, T, Compare, Alloc >::const_iterator			map< Key, T, Compare, Alloc >::begin() const
	{
		const_iterator	tmp(_begin);

		++tmp;
		if (!tmp._ptr)
			tmp = end();
		return (tmp);
	}

	/* end */
	template< class Key, class T, class Compare, class Alloc >
	typename map< Key, T, Compare, Alloc >::iterator				map< Key, T, Compare, Alloc >::end()
	{
		return (iterator(_end));
	}

	template< class Key, class T, class Compare, class Alloc >
	typename map< Key, T, Compare, Alloc >::const_iterator			map< Key, T, Compare, Alloc >::end() const
	{
		return (const_iterator(_end));
	}

	/* rbegin */
	template< class Key, class T, class Compare, class Alloc >
	typename map< Key, T, Compare, Alloc >::reverse_iterator		map< Key, T, Compare, Alloc >::rbegin()
	{
		reverse_iterator	tmp(_end);

		++tmp;
		if (!tmp.base()._ptr)
			tmp = rend();
		return (tmp);
	}

	template< class Key, class T, class Compare, class Alloc >
	typename map< Key, T, Compare, Alloc >::const_reverse_iterator	map< Key, T, Compare, Alloc >::rbegin() const
	{
		const_reverse_iterator	tmp(_end);

		++tmp;
		if (!tmp.base()._ptr)
			tmp = rend();
		return (tmp);
	}

	/* rend */
	template< class Key, class T, class Compare, class Alloc >
	typename map< Key, T, Compare, Alloc >::reverse_iterator		map< Key, T, Compare, Alloc >::rend()
	{
		return (reverse_iterator(_begin));
	}

	template< class Key, class T, class Compare, class Alloc >
	typename map< Key, T, Compare, Alloc >::const_reverse_iterator	map< Key, T, Compare, Alloc >::rend() const
	{
		return (const_reverse_iterator(_begin));
	}

	/* ---- CAPACITY ---- */
	/* empty */
	template< class Key, class T, class Compare, class Alloc >
	bool									map< Key, T, Compare, Alloc >::empty() const
	{
		if (!_root)
			return true;
		return false;
	}

	/* size */
	template< class Key, class T, class Compare, class Alloc >
	typename map< Key, T, Compare, Alloc >::size_type						map< Key, T, Compare, Alloc >::size() const
	{
		return (_size);
	}

	/* max_size */
	template< class Key, class T, class Compare, class Alloc >
	typename map< Key, T, Compare, Alloc >::size_type						map< Key, T, Compare, Alloc >::max_size() const
	{
		return (std::min(_my_node_alloc.max_size(), static_cast<unsigned long>(std::numeric_limits< difference_type >::max())));
	}

	/* ---- ELEMENT ACCESS ---- */
	/* operator[] */
	template< class Key, class T, class Compare, class Alloc >
	typename map< Key, T, Compare, Alloc >::mapped_type&					map< Key, T, Compare, Alloc >::operator[](const key_type& k)
	{
		node	n = _search_node(k);
		if (n)
			return (n->value.second);
		return(_insert_node(_root, nullptr, std::pair< Key, T >(k, mapped_type()))->value.second);
	}

	/* ---- MODIFIERS ---- */
	/* insert */
	template< class Key, class T, class Compare, class Alloc >
	std::pair< typename map< Key, T, Compare, Alloc >::iterator, bool >		map< Key, T, Compare, Alloc >::insert(const value_type& val)
	{
		// size_t	prev_size = size();
		bool	new_element = false;
		node	n = _search_node(val.first);

		if (!n)
		{
			new_element = true;
			n = _insert_node(_root, nullptr, val);
		}
		return (std::pair< iterator, bool >(iterator(n), new_element));
	}

	template< class Key, class T, class Compare, class Alloc >
	typename map< Key, T, Compare, Alloc >::iterator						map< Key, T, Compare, Alloc >::insert(iterator, const value_type& val)
	{
		node	n = _search_node(val.first);

		if (!n)
			n = _insert_node(_root, nullptr, val);
		return (iterator(n));
	}

	template< class Key, class T, class Compare, class Alloc >
	template <class InputIterator>
	void																	map< Key, T, Compare, Alloc >::insert(InputIterator first, InputIterator last)
	{
		node	n;

		while (first != last)
		{
			n = _search_node((*first).first);
			if (!n)
				n = _insert_node(_root, nullptr, *first);
			++first;
		}
	}

	/* erase */
	template< class Key, class T, class Compare, class Alloc >
	void												map< Key, T, Compare, Alloc >::erase(iterator position)
	{
		_remove_node(position._ptr);
	}

	template< class Key, class T, class Compare, class Alloc >
	typename map< Key, T, Compare, Alloc >::size_type	map< Key, T, Compare, Alloc >::erase(const key_type& k)
	{
		node		n = _search_node(k);

		if (n)
		{
			_remove_node(n);
			return (1);
		}
		return (0);
	}

	template< class Key, class T, class Compare, class Alloc >
	void												map< Key, T, Compare, Alloc >::erase(iterator first, iterator last)
	{
		while (first != last)
			erase(first++);
	}

	/* swap */
	template< class Key, class T, class Compare, class Alloc >
	void												map< Key, T, Compare, Alloc >::swap(map& x)
	{
		std::swap(x, *this);
	}

	/* clear */
	template< class Key, class T, class Compare, class Alloc >
	void												map< Key, T, Compare, Alloc >::clear()
	{
		iterator	first = begin();
		iterator	last = end();

		while (first != last)
			erase(first++);
	}

	/* ---- OBSERVERS ---- */
	/* key comp */
	template< class Key, class T, class Compare, class Alloc >
	typename map< Key, T, Compare, Alloc >::key_compare				map< Key, T, Compare, Alloc >::key_comp() const
	{
		return (this->_comp);
	}

	/* value comp */
	template< class Key, class T, class Compare, class Alloc >
	typename map< Key, T, Compare, Alloc >::value_compare			map< Key, T, Compare, Alloc >::value_comp() const
	{
		return (value_compare(_comp));
	}

	/* ---- OPERATIONS ---- */
	/* find */
	template< class Key, class T, class Compare, class Alloc >
	typename map< Key, T, Compare, Alloc >::iterator				map< Key, T, Compare, Alloc >::find(const key_type& k)
	{
		node	n = _search_node(k);

		if (n)
			return (iterator(n));
		return (end());
	}

	template< class Key, class T, class Compare, class Alloc >
	typename map< Key, T, Compare, Alloc >::const_iterator			map< Key, T, Compare, Alloc >::find(const key_type& k) const
	{
		node	n = _search_node(k);

		if (n)
			return (const_iterator(n));
		return (end());
	}

	/* count */
	template< class Key, class T, class Compare, class Alloc >
	typename map< Key, T, Compare, Alloc >::size_type				map< Key, T, Compare, Alloc >::count(const key_type& k) const
	{
		node	n = _search_node(k);

		if (n)
			return (1);
		return (0);
	}

	/* lower_bound */
	template< class Key, class T, class Compare, class Alloc >
	typename map< Key, T, Compare, Alloc >::iterator				map< Key, T, Compare, Alloc >::lower_bound(const key_type& k)
	{
		iterator	it = begin();
		iterator	ite = end();

		while(it != ite)
		{
			if ((!_comp(k, it->first) && !_comp(it->first, k)) || _comp(k, it->first))
				return (it);
			++it;
		}
		return it;
	}

	template< class Key, class T, class Compare, class Alloc >
	typename map< Key, T, Compare, Alloc >::const_iterator			map< Key, T, Compare, Alloc >::lower_bound(const key_type& k) const
	{
		const_iterator	it = begin();
		const_iterator	ite = end();

		while(it != ite)
		{
			if ((!_comp(k, it->first) && !_comp(it->first, k)) || _comp(k, it->first))
				return (it);
			++it;
		}
		return it;
	}

	/* upper_bound */
	template< class Key, class T, class Compare, class Alloc >
	typename map< Key, T, Compare, Alloc >::iterator				map< Key, T, Compare, Alloc >::upper_bound(const key_type& k)
	{
		iterator	it = begin();
		iterator	ite = end();

		while(it != ite)
		{
			if (!_comp(it->first, k) && !(!_comp(k, it->first) && !_comp(it->first, k)))
				return (it);
			++it;
		}
		return it;
	}

	template< class Key, class T, class Compare, class Alloc >
	typename map< Key, T, Compare, Alloc >::const_iterator			map< Key, T, Compare, Alloc >::upper_bound(const key_type& k) const
	{
		const_iterator	it = begin();
		const_iterator	ite = end();

		while(it != ite)
		{
			if (!_comp(it->first, k) && !(!_comp(k, it->first) && !_comp(it->first, k)))
				return (it);
			++it;
		}
		return it;
	}

	/* equal_range */
	template< class Key, class T, class Compare, class Alloc >
	std::pair< typename map< Key, T, Compare, Alloc >::const_iterator, typename map< Key, T, Compare, Alloc >::const_iterator >	map< Key, T, Compare, Alloc >::equal_range(const key_type& k) const
	{
		return (std::pair< const_iterator, const_iterator >(lower_bound(k), upper_bound(k)));
	}

	template< class Key, class T, class Compare, class Alloc >
	std::pair< typename map< Key, T, Compare, Alloc >::iterator, typename map< Key, T, Compare, Alloc >::iterator >				map< Key, T, Compare, Alloc >::equal_range(const key_type& k)
	{
		return (std::pair< iterator, iterator >(lower_bound(k), upper_bound(k)));
	}

	/*
	** ---------------------- MAP PRIVATE FUNCTIONS ---------------------------
	*/

	/* init utils */
	template< class Key, class T, class Compare, class Alloc >
	void							map< Key, T, Compare, Alloc >::_init_node()
	{
		_root = nullptr;
		_begin = nullptr;
		_end = nullptr;
		_begin = _create_node_no_val(_root, nullptr, nullptr);
		_begin->is_end = true;
		_end = _create_node_no_val(_root, nullptr, nullptr);
		_end->is_end = true;
		_size = 0;
	}

	template< class Key, class T, class Compare, class Alloc >
	ft::map_node_base< Key, T >			*map< Key, T, Compare, Alloc >::_create_node(const value_type& val,
													node parent, node left, node right)
	{
		node n = _my_node_alloc.allocate(1);
		_my_node_alloc.construct(n, ft::map_node_base< Key, T >(val, parent, left, right));
		++_size;
		return (n);
	}

	template< class Key, class T, class Compare, class Alloc >
	ft::map_node_base< Key, T >			*map< Key, T, Compare, Alloc >::_create_node_no_val(node parent, node left,
																							 node right)
	{
		node n = _my_node_alloc.allocate(1);
		n->parent = parent;
		n->left = left;
		n->right = right;
		++_size;
		return (n);
	}

	template< class Key, class T, class Compare, class Alloc >
	void								map< Key, T, Compare, Alloc >::_delete_node(node n)
	{
		_my_node_alloc.destroy(n);
		_my_node_alloc.deallocate(n, 1);
		--_size;
	}

	template< class Key, class T, class Compare, class Alloc >
	void								map< Key, T, Compare, Alloc >::_delete_node_no_val(node n)
	{
		_my_node_alloc.deallocate(n, 1);
		--_size;
	}

	template< class Key, class T, class Compare, class Alloc >
	void								map< Key, T, Compare, Alloc >::_add_node(node& root, node parent, const node& curr)
	{
		if (!_root)
		{
			_root = curr;
			_root->parent = parent;
			root = _root;
		}
		else if (!root)
		{
			root = curr;
			root->parent = parent;
		}
		else if (root == _begin)
		{
			root = curr;
			root->parent = parent;
		}
		else if (root == _end)
		{
			root = curr;
			root->parent = parent;
		}
		else if (this->_comp(curr->value.first, root->value.first))
			_add_node(root->left, root, curr);
		else
			_add_node(root->right, root, curr);
	}

	template< class Key, class T, class Compare, class Alloc >
	void								map< Key, T, Compare, Alloc >::_reconnect_begin()
	{
		node	curr = _root;

		while(curr->left && curr->left->is_end == false)
			curr = curr->left;
		_begin->parent = curr;
		curr->left = _begin;
	}

	template< class Key, class T, class Compare, class Alloc >
	void								map< Key, T, Compare, Alloc >::_reconnect_end()
	{
		node	curr = _root;

		while(curr->right && curr->right->is_end == false)
			curr = curr->right;
		curr->right = _end;
		_end->parent = curr;
	}

	template< class Key, class T, class Compare, class Alloc >
	ft::map_node_base< Key, T >			*map< Key, T, Compare, Alloc >::_remove_node(node& curr)
	{
		node	parent = curr->parent;
		node	ret = curr;

		if ((!curr->left || (curr->left && curr->left->is_end))
			&& (!curr->right || (curr->right && curr->right->is_end)))
		{
			if (parent && curr != _root)
			{
				if (parent->left == curr)
				{
					if (curr->left && curr->left->is_end)
					{
						parent->left = _begin;
						_begin->parent = parent;
					}
					else
						parent->left = nullptr;
				}
				else
				{
					if (curr->right && curr->right->is_end)
					{
						parent->right = _end;
						_end->parent = parent;
					}
					else
						parent->right = nullptr;
				}
				ret = parent;
				_delete_node(curr);
			}
			else
			{
				_root = nullptr;
				_begin->parent = _root;
				_end->parent = _root;
				ret = _end;
				_delete_node(curr);
			}
		}
		else if (curr->left && curr->right)
		{
			node	tmp_left = curr->left;
			node	tmp_right = curr->right;

			if (curr->parent)
			{
				if (curr->parent->left == curr)
					curr->parent->left = nullptr;
				else
					curr->parent->right = nullptr;
			}
			else
				_root = nullptr;
			_delete_node(curr);
			if (tmp_right && tmp_right->is_end == false)
				_add_node(_root, nullptr, tmp_right);
			if (tmp_left && tmp_left->is_end == false)
				_add_node(_root, nullptr, tmp_left);
			_reconnect_begin();
			_reconnect_end();
		}
		else
		{
			node	child;

			if (curr->left)
				child = curr->left;
			else
				child = curr->right;

			ret = child;
			child->parent = parent;
			if (curr != _root)
			{
				if (curr == parent->left)
					parent->left = child;
				else
					parent->right = child;
			}
			else
				_root = child;
			_delete_node(curr);
		}
		return ret;
	}

	template< class Key, class T, class Compare, class Alloc >
	typename map< Key, T, Compare, Alloc >::node		map< Key, T, Compare, Alloc >::_insert_node(node& root, node parent, const value_type& val)
	{
		if (!_root)
		{
			_root = _create_node(val, nullptr, _begin, _end);
			_begin->parent = _root;
			_end->parent = _root;
			root = _root;
			return (_root);
		}
		else if (!root)
		{
			root = _create_node(val, parent, nullptr, nullptr);
			return (root);
		}
		else if (root == _begin)
		{
			root = _create_node(val, root->parent, _begin, nullptr);
			_begin->parent = root;
			return (root);
		}
		else if (root == _end)
		{
			root = _create_node(val, root->parent, nullptr, _end);
			_end->parent = root;
			return (root);
		}
		else if (_comp(val.first, root->value.first))
			return(_insert_node(root->left, root, val));
		else if (_comp(root->value.first, val.first))
			return(_insert_node(root->right, root, val));
		else
		{
			root->value.second = val.second;
			return (root);
		}
	}

	template< class Key, class T, class Compare, class Alloc >
	typename map< Key, T, Compare, Alloc >::node		map< Key, T, Compare, Alloc >::_search_node(const key_type& k) const
	{
		iterator	it = begin();
		iterator	ite = end();

		while (it != ite)
		{
			if (!(_comp(it._ptr->value.first, k) || _comp(k, it._ptr->value.first)))
				return (it._ptr);
			++it;
		}
		return nullptr;
	}
}
