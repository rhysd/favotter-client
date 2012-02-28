#ifndef FAVOTTER_HPP
#define FAVOTTER_HPP

#include "regexes.hpp"

#include <cstring>
#include <cstdlib>

#include <iostream>
#include <string>
#include <queue>
#include <algorithm>
//#include <thread>

#include <boost/asio.hpp>
// #include <boost/xpressive/xpressive_static.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>

namespace xpressive = boost::xpressive;
namespace ip = boost::asio::ip;

class favotter : public boost::noncopyable {

	std::queue<boost::tuple<std::string, std::string, int> > tweets;
	std::queue<boost::tuple<std::string, std::string, int> > page_buf;
    regexes regex_parsers;
	xpressive::sregex const tweet_parser;
	int page;
	xpressive::sregex const href_parser;
	std::string const href_format;
	xpressive::sregex const uncensored_parser;
	std::string const uncensored_format;
	bool show_uncensored;
	std::string mode;  //"new&threshold=10", "best"

	void get_page();
public:
	explicit favotter();
	void showpage();
	void show_all_page(char const* mode_ = NULL, bool const show_uncensored_ = false);
	void show_next_page(char const *mode_ = NULL, bool const show_uncensored_ = false);
};

#endif // FAVOTTER_HPP
