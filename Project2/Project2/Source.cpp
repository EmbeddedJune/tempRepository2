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

		tcp::endpoint endpoint(tcp::v4(), 13);			// ����� �ϴ� �� ���� endpoint. 13�� port # ������ ���� ����
		tcp::acceptor acceptor(io_service, endpoint);	// endpoint���� io_service�� accept�� acceptor�� ����

		std::cout << "Server started" << std::endl;

		for (;;)	// ���� ����
		{
			const std::string message_to_send = "Hello From Server";

			boost::asio::ip::tcp::iostream stream;	// �Ϲ� iostream�� �ƴ϶� �����ε�� tcp::iostream�̴�.

			std::cout << "check 1" << std::endl;	// ��Ʈ��ŷ������ cout�� �� �� �ִ�.

			boost::system::error_code ec;
			acceptor.accept(*stream.rdbuf(), ec);	// Ŭ���̾�Ʈ ������ �޾Ƶ��δ�.

			std::cout << "check 2" << std::endl;

			if (!ec)	//TODO: How to take care of multiple clients? Multi-threading?
			{	// Ŭ���̾�Ʈ�� ����� ������ �ƴٸ�,
				// receive message from client 
				std::string line;	
				std::getline(stream, line);			// ����� ��Ʈ������ 
				std::cout << line << std::endl;		// Ŭ���̾�Ʈ ���忡���� ���⼭ �����͸� ������ ������ �޴´�.

				// send message to client
				stream << message_to_send;
				stream << std::endl;				// Ŭ���̾�Ʈ ���忡���� ���⼭ �����͸� �о�� ������ ������.
			}
		}
	}
	catch (std::exception& e)						// ���� �߻���
	{
		std::cout << e.what() << std::endl;
	}
}