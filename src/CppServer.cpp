#include <thrift/concurrency/ThreadManager.h>
#include <thrift/concurrency/PlatformThreadFactory.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/server/TThreadPoolServer.h>
#include <thrift/server/TThreadedServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>
#include <thrift/TToString.h>
#include <thrift/stdcxx.h>

#include <iostream>
#include <stdexcept>
#include <sstream>

#include "../gen-cpp/TestService.h"

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::concurrency;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace apache::thrift::server;

using namespace tutorial;

class TestServiceHandler: public TestServiceIf {
public:
  TestServiceHandler() {}

  void ping() {
      cout << "ping()" << endl;
  }

};

int main() {

  // if you don't need per-connection state, do the following instead
  TThreadedServer server(
    stdcxx::make_shared<TestServiceProcessor>(stdcxx::make_shared<TestServiceHandler>()),
    stdcxx::make_shared<TServerSocket>(16191), // port
    stdcxx::make_shared<TBufferedTransportFactory>(),
    stdcxx::make_shared<TBinaryProtocolFactory>()
  );

  cout << "Starting the server..." << endl;
  server.serve();
  cout << "Done." << endl;
  return 0;
}
