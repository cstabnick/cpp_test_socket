#include <iostream>
#include "./sock.h"

const char *PROG_FAIL_ERR = 
"\r\nTHE PROGRAM WILL NOW CRASH.\
\r\nTHANK YOU FOR TRYING TO USE IT.\
";


int main(int argc, char** argv) {

	try {
		Sock* s = new Sock();


		if (argc > 1) {
			const char* msg = argv[1];
			s->CreateTestSocket(msg);

		} else {

			s->CreateTestSocket("hi");
		}


	} catch (const char* msg) {
		std::cerr << msg << std::endl << PROG_FAIL_ERR << std::endl;
	}
}