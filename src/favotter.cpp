#include "favotter.hpp"

/* compile : g++ *.cpp -L /usr/lib -l boost_system -l boost_thread-mt*/

void favotter::get_page()
{
	ip::tcp::iostream s( "favotter.net", "http" );

	if(s.bad()){
		std::cout << "CONNECT: fatal (ErrorCode=" << s.bad() << ")\n";
		return;
	}
	if(s.fail()){
		std::cout << "CONNECT: failed (ErrorCode=" << s.fail() << ")\n";
		return;
	}

	s << "GET /home.php?mode=" << mode << "&page=" << page << " HTTP/1.0\r\n";
	s << "Host: favotter.net\r\n";
	s << "\r\n";
	s << std::flush;

	if(s.bad()){
		std::cout << "CONNECT: fatal (ErrorCode=" << s.bad() << ")\n";
		return;
	}
	if(s.fail()){
		std::cout << "GET: failed (ErrorCode=" << s.fail() << ")\n";
		return;
	}

	std::string html;
	std::string buffer;
	while ( getline(s, buffer) ){
		html += buffer;
	}

	xpressive::sregex_iterator cur(html.begin(), html.end(), tweet_parser), end;

	for( ; cur != end; ++cur){
		xpressive::smatch const what = *cur;
		if( show_uncensored || !xpressive::regex_search(what[1].str(), uncensored_parser) ){
			page_buf.push(boost::make_tuple(
						what[2],
						std::move( regex_replace(
								std::move( regex_replace(what[1].str(), href_parser, href_format) ),
								uncensored_parser,
								uncensored_format
								)
							),
						boost::lexical_cast<int>(what[3])
						)
					);
		}
	}

	if(page_buf.empty()){
		std::cout << "fail to get page data (page: " << page << " )\n";
		std::exit(0);
	}

	++page;
}

favotter::favotter(): tweets(),
	tweet_parser( regex_parsers.get_tweet_parser() ),
	page(1),
	href_parser( regex_parsers.get_href_parser() ),
	href_format("$1"),
	uncensored_parser( regex_parsers.get_uncensored_parser() ),
	uncensored_format(" <uncensored> "),
	mode("best")
{ }

void favotter::showpage()
{
	std::string buf;

	std::cout << "**************************** page:" << page << " ****************************\n\n";

	while(true){
		for(int i=0;i<3;i++){
			if(tweets.empty()) break;
			std::cout << '@' << tweets.front().get<0>() << ": " << tweets.front().get<2>() << " faved\n"
				<< tweets.front().get<1>() << "\n\n";
			tweets.pop();
		}

		if(tweets.empty()) break;

		std::getline(std::cin, buf);
	}
}

void favotter::show_all_page(char const* mode_, bool const show_uncensored_)
{
	show_uncensored = show_uncensored_;
	if(mode_!=NULL){
		if(std::strcmp(mode_, "current")==0) mode = "new&threshold=10";
	}

	get_page();
	while(!page_buf.empty()){
		tweets.push(page_buf.front());
		page_buf.pop();
	}

	std::string buf;

	while(true){
		boost::thread io_thread( boost::bind( &favotter::get_page, this ) );

		//get_page();
		showpage();

		io_thread.join();

		while(!page_buf.empty()){
			tweets.push( page_buf.front() );
			page_buf.pop();
		}
	}
}

inline void favotter::show_next_page(char const *mode_, bool const show_uncensored_)
{
	if(mode_ != NULL) mode = mode_;

	std::string buf;
	show_uncensored = show_uncensored_;
	boost::thread io_thread( boost::bind(&favotter::get_page, this ) );

	//get_page();
	showpage();

	io_thread.join();

	while(!page_buf.empty()){
		tweets.push( page_buf.front() );
		page_buf.pop();
	}
}
