#include <iostream>
#include <ctime>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main()
{
	try
	{
		boost::asio::io_service io_service;

		tcp::endpoint endpoint(tcp::v4(), 13);			// 통신을 하는 양 끝점 endpoint. 13은 port # 임의의 숫자 가능
		tcp::acceptor acceptor(io_service, endpoint);	// endpoint에서 io_service를 accept할 acceptor를 생성

		std::cout << "Server started" << std::endl;

		for (;;)	// 무한 루프
		{
			const std::string message_to_send = "Hello From Server";

			boost::asio::ip::tcp::iostream stream;	// 일반 iostream이 아니라 오버로드된 tcp::iostream이다.

			std::cout << "check 1" << std::endl;	// 네트워킹에서도 cout을 쓸 수 있다.

			boost::system::error_code ec;
			acceptor.accept(*stream.rdbuf(), ec);	// 클라이언트 접속을 받아들인다.

			std::cout << "check 2" << std::endl;

			if (!ec)	//TODO: How to take care of multiple clients? Multi-threading?
			{	// 클라이언트가 제대로 접속이 됐다면,
				// receive message from client 
				std::string line;	
				std::getline(stream, line);			// 입출력 스트림에서 
				std::cout << line << std::endl;		// 클라이언트 입장에서는 여기서 데이터를 보내야 서버가 받는다.

				// send message to client
				stream << message_to_send;
				stream << std::endl;				// 클라이언트 입장에서는 여기서 데이터를 읽어야 서버가 보낸다.
			}
		}
	}
	catch (std::exception& e)						// 예외 발생시
	{
		std::cout << e.what() << std::endl;
	}
}