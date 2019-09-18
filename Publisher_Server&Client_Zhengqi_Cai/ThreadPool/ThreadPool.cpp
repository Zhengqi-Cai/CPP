// ThreadPool.cpp

#include <thread>
#include <chrono>
#include <iostream>
#include <sstream>
#include "ThreadPool.h"



//----< test stub >--------------------------------------------------

#ifdef TEST_THREADPOOL

#include <iostream>
using namespace std::chrono_literals;
using namespace oldUtilities;
using namespace MsgPassingCommunication;
using Utils = StringHelper;

int main()
{
  Show::attach(&std::cout);
  Show::start();
  DebugLog::attach(&std::cout);
  DebugLog::start();

  Utils::Title(true,"Testing ThreadPool");

  ThreadPool<2> trpl;

  CallObj co = [&trpl](Message msg) ->bool { 
    Show::write(
      "\n  hello from thread " + 
      oldUtilities::Converter<std::thread::id>::toString(std::this_thread::get_id())+msg.toString()
    ); 
    return true;
  };
  EndPoint ep("local", 8080);
  Message msg(ep, ep);
  CallWrapper cw(co, msg);
  for (size_t i = 0; i < 20; ++i)
    trpl.workItem(cw);

  CallObj exit = [](Message msg) ->bool { return false; };
  CallWrapper cw2(exit, msg);

  trpl.workItem(cw2);
  trpl.wait();

  //std::cout << "\n\n";
}

#endif
