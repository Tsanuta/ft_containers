/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olidon <olidon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 11:27:35 by olidon            #+#    #+#             */
/*   Updated: 2021/03/14 18:20:44 by olidon           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"


class testclass
{
	public:
		testclass() : val(0) {};
		testclass(int val) : val(val) {};
		testclass(testclass const &src) : val(src.val) {};
		testclass&	operator=(const testclass &rhs) { val = rhs.val; return *this; };
		~testclass() {};
		int	val;
	private:
};

std::ostream		&operator<<(std::ostream &o, testclass const &rhs) { o << rhs.val; return o; }
bool					operator==(const testclass& lhs, const testclass& rhs) {return (lhs.val == rhs.val);};
bool					operator!=(const testclass& lhs, const testclass& rhs) {return (lhs.val != rhs.val);};
bool					operator<(const testclass& lhs, const testclass& rhs) {return (lhs.val < rhs.val);};
bool					operator<=(const testclass& lhs, const testclass& rhs) {return (lhs.val <= rhs.val);};
bool					operator>(const testclass& lhs, const testclass& rhs) {return (lhs.val > rhs.val);};
bool					operator>=(const testclass& lhs, const testclass& rhs) {return (lhs.val >= rhs.val);};

int		main(void)
{
	std::ofstream	ofs1;
	std::ofstream	ofs2;

	ofs1.open("Success.txt");
	ofs2.open("Errors.txt");
	if (ofs1.fail() || ofs2.fail())
	{
		std::cout << "Error: Could not create or open file" << std::endl;
		return 0;
	}

	/*
	------- LIST -------
	*/

	std::cout << "------ TEST LIST CHAR * ------\n";
	const char	*lst_char_tab[] = {"1A", "2B", "3C", "4D", "5E", "100Z", "150ZA", "200ZB", "250ZC", "300ZD"};
	list_test< const char * >(lst_char_tab, &ofs1, &ofs2);

	std::cout << "------ TEST LIST INT ------\n";
	int		lst_int_tab[] = {1, 2, 3, 4 ,5 , 100, 150, 200, 250, 300};
	list_test< int >(lst_int_tab, &ofs1, &ofs2);

	std::cout << "------ TEST LIST STRING ------\n";
	std::string		lst_str_tab[] = {"1A", "2B", "3C", "4D", "5E", "100Z", "150ZA", "200ZB", "250ZC", "300ZD"};
	list_test< std::string >(lst_str_tab, &ofs1, &ofs2);

	std::cout << "------ TEST LIST DOUBLE ------\n";
	double		lst_dbl_tab[] = {18.55, 2.5, 6.6, 1.55, 2.2, 3.5, 3.1, 2.999, 6.6666, 50.5};
	list_test< double >(lst_dbl_tab, &ofs1, &ofs2);

	std::cout << "------ TEST LIST CLASS ------\n";
	testclass		a(1), b(2),	c(3), d(4), e(5), f(6), g(7), h(8), i(9), j(10);

	testclass		lst_class_tab[] = {a, b, c, d, e, f, g, h, i, j};
	list_test< testclass >(lst_class_tab, &ofs1, &ofs2);

	/*
	------- VECTOR -------
	*/

	std::cout << "------ TEST VECTOR INT ------\n";
	int		vct_int_tab[] = {1, 2, 3, 4 ,5 , 100, 150, 200, 250, 300};
	vector_test< int >(vct_int_tab, &ofs1, &ofs2);

	std::cout << "------ TEST VECTOR STRING ------\n";
	std::string		vct_str_tab[] = {"1A", "2B", "3C", "4D", "5E", "100Z", "150ZA", "200ZB", "250ZC", "300ZD"};
	vector_test< std::string >(vct_str_tab, &ofs1, &ofs2);

	std::cout << "------ TEST VECTOR DOUBLE ------\n";
	double		vct_dbl_tab[] = {18.55, 2.5, 6.6, 1.55, 2.2, 3.5, 3.1, 2.999, 6.6666, 50.5};
	vector_test< double >(vct_dbl_tab, &ofs1, &ofs2);

	std::cout << "------ TEST VECTOR CLASS ------\n";
	testclass		vct_class_tab[] = {a, b, c, d, e, f, g, h, i, j};
	vector_test< testclass >(vct_class_tab, &ofs1, &ofs2);

	/*
	------- MAP -------
	*/

	std::cout << "------ TEST MAP < CHAR, INT > ------\n";
	std::pair<char, int>	map_char_int_tab[] = {std::make_pair('a', 10), std::make_pair('b', 30), std::make_pair('c', 50), std::make_pair('d', 70) ,std::make_pair('e', 80) , std::make_pair('f', 90), std::make_pair('g', 100), std::make_pair('h', 150), std::make_pair('i', 200), std::make_pair('j', 250)};
	map_test< char, int >(map_char_int_tab, &ofs1, &ofs2);

	std::cout << "------ TEST MAP < INT, STD::STRING > ------\n";
	std::pair<int, std::string>	map_int_str_tab[] = {std::make_pair(0, "AAA"), std::make_pair(1, "BBB"), std::make_pair(2, "CCC"), std::make_pair(3, "DDD") ,std::make_pair(4, "EEE") , std::make_pair(5, "FFF"), std::make_pair(6, "GGG"), std::make_pair(7, "HHH"), std::make_pair(8, "III"), std::make_pair(9, "JJJ")};
	map_test< int, std::string >(map_int_str_tab, &ofs1, &ofs2);

	std::cout << "------ TEST MAP < CLASS, STD::STRING > ------\n";
	std::pair<testclass, std::string>	map_class_str_tab[] = {std::make_pair(a, "AAA"), std::make_pair(b, "BBB"), std::make_pair(c, "CCC"), std::make_pair(d, "DDD") ,std::make_pair(e, "EEE") , std::make_pair(f, "FFF"), std::make_pair(g, "GGG"), std::make_pair(h, "HHH"), std::make_pair(i, "III"), std::make_pair(j, "JJJ")};
	map_test< testclass, std::string >(map_class_str_tab, &ofs1, &ofs2);

	std::cout << "------ TEST MAP < INT, CLASS > ------\n";
	std::pair<int, testclass>	map_int_class_tab[] = {std::make_pair(0, a), std::make_pair(1, b), std::make_pair(2, c), std::make_pair(3, d) ,std::make_pair(4, e) , std::make_pair(5, f), std::make_pair(6, g), std::make_pair(7, h), std::make_pair(8, i), std::make_pair(9, j)};
	map_test< int, testclass >(map_int_class_tab, &ofs1, &ofs2);

	/*
	------- STACK -------
	*/

	std::cout << "------ TEST STACK INT ------\n";
	int		sta_int_tab[] = {1, 2, 3, 4 ,5 , 100, 150, 200, 250, 300};
	stack_test< int >(sta_int_tab, &ofs1, &ofs2);

	std::cout << "------ TEST STACK STRING ------\n";
	std::string		sta_str_tab[] = {"1A", "2B", "3C", "4D", "5E", "100Z", "150ZA", "200ZB", "250ZC", "300ZD"};
	stack_test< std::string >(sta_str_tab, &ofs1, &ofs2);

	std::cout << "------ TEST STACK DOUBLE ------\n";
	double		sta_dbl_tab[] = {18.55, 2.5, 6.6, 1.55, 2.2, 3.5, 3.1, 2.999, 6.6666, 50.5};
	stack_test< double >(sta_dbl_tab, &ofs1, &ofs2);

	std::cout << "------ TEST STACK CLASS ------\n";
	testclass		sta_class_tab[] = {a, b, c, d, e, f, g, h, i, j};
	stack_test< testclass >(sta_class_tab, &ofs1, &ofs2);

	/*
	------- QUEUE -------
	*/

	std::cout << "------ TEST QUEUE INT ------\n";
	int		que_int_tab[] = {1, 2, 3, 4 ,5 , 100, 150, 200, 250, 300};
	queue_test< int >(que_int_tab, &ofs1, &ofs2);

	std::cout << "------ TEST QUEUE STRING ------\n";
	std::string		que_str_tab[] = {"1A", "2B", "3C", "4D", "5E", "100Z", "150ZA", "200ZB", "250ZC", "300ZD"};
	queue_test< std::string >(que_str_tab, &ofs1, &ofs2);

	std::cout << "------ TEST QUEUE DOUBLE ------\n";
	double		que_dbl_tab[] = {18.55, 2.5, 6.6, 1.55, 2.2, 3.5, 3.1, 2.999, 6.6666, 50.5};
	queue_test< double >(que_dbl_tab, &ofs1, &ofs2);

	std::cout << "------ TEST QUEUE CLASS ------\n";
	testclass		que_class_tab[] = {a, b, c, d, e, f, g, h, i, j};
	queue_test< testclass >(que_class_tab, &ofs1, &ofs2);

	ofs1.close();
	ofs2.close();
}
