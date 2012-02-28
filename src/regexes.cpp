#include "regexes.hpp"

xpressive::sregex const regexes_impl::get_tweet_parser() const
{
	using namespace boost::xpressive;

	return std::move( sregex(
				"<span class=\" status_text description\">" >>
				(s1 = +(~before("</span>  </div>") >> _)) >>
				+(~before("<a title=\"") >> _) >>
				"<a title=\""  >>  (s2 = +~(set= '\"')) >> "\"" >>
				+(~before("<span class=\"favotters\"> ") >> _) >>
				"<span class=\"favotters\"> " >> (s3 = +_d)
				) );
}

xpressive::sregex const regexes_impl::get_href_parser() const
{
	using namespace boost::xpressive;

	return std::move( sregex(
				"<a href=\"" >> +(~before(">") >> _) >>
				">" >> (s1 = +(~before("</a>") >> _))
				>> "</a>"
				) );
}

xpressive::sregex const regexes_impl::get_uncensored_parser() const
{
	using namespace boost::xpressive;

	return std::move( sregex(
				as_xpr( "<span class=\"censored\">&lt;censored&gt;</span>" )
				) );
}



