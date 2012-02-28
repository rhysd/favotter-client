#ifndef REGEXES_HPP
#define REGEXES_HPP

#include <memory>
#include <boost/xpressive/xpressive_static.hpp>

namespace xpressive = boost::xpressive;

// class regexes_impl;

class regexes_impl{
public:
    xpressive::sregex const get_tweet_parser() const;
    xpressive::sregex const get_href_parser() const;
    xpressive::sregex const get_uncensored_parser() const;
};

class regexes{
	std::unique_ptr<regexes_impl> regex_ptr;
public:
	regexes() : regex_ptr( new regexes_impl() ) {}

	xpressive::sregex const get_tweet_parser() const
	{
		return regex_ptr->get_tweet_parser();
	}

	xpressive::sregex const get_href_parser() const
	{
		return regex_ptr->get_href_parser();
	}

	xpressive::sregex const get_uncensored_parser() const
	{
		return regex_ptr->get_uncensored_parser();
	}
};

#endif
