#pragma once
#include <misaka/net/server.hpp>

#include <gmock/gmock.h>

class MockServer : public misaka::net::Server {
public:
    MOCK_METHOD(void, Listen, (), (final));
    MOCK_METHOD(void, StopListen, (), (final));
    MOCK_METHOD(void, SetRequestProcessor, (std::function<Response(const misaka::net::Context&)> processor), (final));
    MOCK_METHOD((asio::awaitable<std::optional<Response>>), Send, (Request request, const misaka::net::Endpoint& remote, std::chrono::seconds timeout), (final));
};