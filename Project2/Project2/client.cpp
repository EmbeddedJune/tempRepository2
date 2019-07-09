#include <iostream>
#include <string>	
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main(int argc, char** argv)
{
	try
	{
		if (argc != 2)
		{
			std::cerr << "Usage : Client <host>\n";
			return EXIT_FAILURE;
		}
		
		tcp::iostream stream(argv[1], std::to_string(int(13))); // port num = 13
		if (!stream)
		{
			std::cout << "No address. Unable to connect: " << stream.error().message() << std::endl;
			return EXIT_FAILURE;
		}

		// send message to server
		stream << "Hello from client Embedded June\n";

		// receive message from server
		std::string line;
		std::getline(stream, line);
		std::cout << line << std::endl;
	}
	catch(std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}
}