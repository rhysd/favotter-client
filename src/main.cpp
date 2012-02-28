#include "favotter.hpp"

int main(int const argc, char const * const argv[])
{
	favotter f;

	if( (argc == 2) && (std::strcmp(argv[1], "-all") == 0) ){
		f.show_all_page(NULL, true);
	}else   if( (argc == 2) && ((std::strcmp(argv[1], "--current") == 0) ||
				(std::strcmp(argv[1], "-c") == 0))          ){
		f.show_all_page("current", false);
	}else{
		f.show_all_page();
	}

	return 0;
}
