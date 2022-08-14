#include "IPCClient.h"

#include <cstring>
#include <fcntl.h>
#include <stdexcept>
#include <unistd.h>

IPCClient::~IPCClient()
{
	if (pipe != -1)
		close(pipe);
}

void IPCClient::Connect()
{
	pipe = open((std::string(getenv("HOME")) + "/.local/share/OpenVR-SpaceCalibrator/pipe").c_str(), O_RDWR);

	if (pipe == -1)
	{
		throw std::runtime_error("Space Calibrator driver unavailable. Make sure SteamVR is running, and the Space Calibrator addon is enabled in SteamVR settings.");
	}

	auto response = SendBlocking(protocol::Request(protocol::RequestHandshake));
	if (response.type != protocol::ResponseHandshake || response.protocol.version != protocol::Version)
	{
		throw std::runtime_error(
			"Incorrect driver version installed, try reinstalling OpenVR-SpaceCalibrator. (Client: " +
			std::to_string(protocol::Version) +
			", Driver: " +
			std::to_string(response.protocol.version) +
			")"
		);
	}
}

protocol::Response IPCClient::SendBlocking(const protocol::Request &request)
{
	Send(request);
	return Receive();
}

void IPCClient::Send(const protocol::Request &request)
{
	ssize_t bytesWritten = write(pipe, &request, sizeof request);
	if (bytesWritten == -1)
	{
		throw std::runtime_error(std::string("Error writing IPC request. Error: ") + strerror(errno));
	}
}

protocol::Response IPCClient::Receive()
{
	protocol::Response response(protocol::ResponseInvalid);
	ssize_t bytesRead = read(pipe, &response, sizeof response);
	if (bytesRead == -1)
	{
		throw std::runtime_error(std::string("Error reading IPC response. Error: ") + strerror(errno));
	}

	if (bytesRead != sizeof response)
	{
		throw std::runtime_error("Invalid IPC response with size " + std::to_string(bytesRead));
	}

	return response;
}
