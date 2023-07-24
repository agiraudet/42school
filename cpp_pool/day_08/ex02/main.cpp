/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 10:22:44 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/28 13:05:55 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <list>
#include "MutantStack.hpp"

int main(void)
{
	std::cout << "Mutant Stack vs list (const it)" << std::endl;
	std::cout << "--- mutant stack ---" << std::endl;
	{
		MutantStack<int>	mstack;

		mstack.push(1312);
		mstack.push(456);
		mstack.push(18);
		mstack.push(24);

		MutantStack<int>::const_iterator it = mstack.begin();
		MutantStack<int>::const_iterator ite = mstack.end();
		ite--;
		std::cout << *ite << std::endl;
		std::cout << *it << std::endl;
		std::cout << *++it << std::endl;
		std::cout << *it << std::endl;
		std::cout << *it++ << std::endl;
		std::cout << *it << std::endl;
		std::cout << *--it << std::endl;
		std::cout << *it++ << std::endl;
	}
	std::cout << "--- list ---" << std::endl;
	{
		std::list<int>	lst;


		lst.push_back(1312);
		lst.push_back(456);
		lst.push_back(18);
		lst.push_back(24);

		std::list<int>::const_iterator it = lst.begin();
		std::list<int>::const_iterator ite = lst.end();
		ite--;
		std::cout << *ite << std::endl;
		std::cout << *it << std::endl;
		std::cout << *++it << std::endl;
		std::cout << *it << std::endl;
		std::cout << *it++ << std::endl;
		std::cout << *it << std::endl;
		std::cout << *--it << std::endl;
		std::cout << *it++ << std::endl;
	}
	std::cout << std::endl << "Subject Demo" << std::endl;
	std::cout << "--- mutant stack ---" << std::endl;
	{
		MutantStack<int> mstack;

		mstack.push(5);
		mstack.push(17);

		std::cout << mstack.top() << std::endl;

		mstack.pop();

		std::cout << mstack.size() << std::endl;

		mstack.push(3);
		mstack.push(5);
		mstack.push(737);
		//[...]
		mstack.push(0);

		MutantStack<int>::iterator it = mstack.begin();
		MutantStack<int>::iterator ite = mstack.end();

		++it;
		--it;
		while (it != ite)
		{
			std::cout << *it << std::endl;
			++it;
		}
		std::stack<int> s(mstack);
	}
	std::cout << "--- list ---" << std::endl;
	{
		std::list<int> lst;

		lst.push_back(5);
		lst.push_back(17);

		std::cout << lst.back() << std::endl;

		lst.pop_back();

		std::cout << lst.size() << std::endl;

		lst.push_back(3);
		lst.push_back(5);
		lst.push_back(737);
		//[...]
		lst.push_back(0);

		std::list<int>::iterator it = lst.begin();
		std::list<int>::iterator ite = lst.end();

		++it;
		--it;
		while (it != ite)
		{
			std::cout << *it << std::endl;
			++it;
		}
		std::list<int> s(lst);
	}
	std::cout << std::endl << "### Copy test ###" << std::endl;
	{
		std::cout << "--- copy constructor ---" << std::endl;
		MutantStack<int>	mstack;

		mstack.push(1312);
		mstack.push(456);
		mstack.push(18);
		mstack.push(24);

		MutantStack<int>	cpA(mstack);
		{
			MutantStack<int>::iterator it = cpA.begin();
			MutantStack<int>::iterator ite = cpA.end();
			while (it != ite)
			{
				std::cout << *it << std::endl;
				++it;
			}
		}

		std::cout << "--- assignation ---" << std::endl;
		MutantStack<int>	cpB;
		cpB = mstack;
		{
			MutantStack<int>::iterator it = cpB.begin();
			MutantStack<int>::iterator ite = cpB.end();
			while (it != ite)
			{
				std::cout << *it << std::endl;
				++it;
			}
		}
	}
	return 0;
}
