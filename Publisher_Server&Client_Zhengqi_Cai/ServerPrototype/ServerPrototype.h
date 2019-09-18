#pragma once
///////////////////////////////////////////////////////////////////////
// ServerPrototype.h - Console App that processes incoming messages  //
// ver 1.0                                                           //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2018         //
///////////////////////////////////////////////////////////////////////
/*
*  Package Operations:
* ---------------------
*  Package contains one class, Server, that contains a Message-Passing Communication
*  facility. It processes each message by invoking an installed callable object
*  defined by the message's command key.
*
*  Message handling runs on a child thread, so the Server main thread is free to do
*  any necessary background processing (none, so far).
*
*  Required Files:
* -----------------
*  ServerPrototype.h, ServerPrototype.cpp
*  Comm.h, Comm.cpp, IComm.h
*  Message.h, Message.cpp
*  FileSystem.h, FileSystem.cpp
*  Utilities.h
*
*  Maintenance History:
* ----------------------
*  ver 1.0 : 3/27/2018
*  - first release
*/
#include <vector>
#include <string>
#include <unordered_map>
#include <functional>
#include <thread>
#include "../CppCommWithFileXfer/Message/Message.h"
#include "../CppCommWithFileXfer/MsgPassingComm/Comm.h"
#include <windows.h>
#include <tchar.h>

//using namespace ;
//using namespace MsgPassingCommunication;
namespace Repository
{
  using File = std::string;
  using Files = std::vector<File>;
  using Dir = std::string;
  using Dirs = std::vector<Dir>;
  using SearchPath = std::string;
  using Key = std::string;
  using Msg = MsgPassingCommunication::Message;
  using ServerProc = std::function<bool(MsgPassingCommunication::Message)>;
  using MsgDispatcher = std::unordered_map<Key,ServerProc>;
  
  const SearchPath projectsStoreRoot = "../ServerStorage/Projects"; 
  const SearchPath ClientsDataRoot = "../ServerStorage/ClientsTemp";
  const MsgPassingCommunication::EndPoint serverEndPoint("localhost", 8080);  // listening endpoint
  bool demoOn=false;
  class ProtoServer
  {
  public:
	ProtoServer(MsgPassingCommunication::EndPoint ep, const std::string& name);
    void start();
    void stop();
	virtual void assembleDispatcher();
    void processMessages();
    void postMessage(MsgPassingCommunication::Message msg);
    MsgPassingCommunication::Message getMessage();
  
  
  protected:
    MsgPassingCommunication::Comm comm_;
    MsgDispatcher dispatcher_;
    std::thread msgProcThrd_;

	static Dirs getDirs(const SearchPath& path = projectsStoreRoot);
	static Files getFiles(const SearchPath& path = projectsStoreRoot);
	bool serverQuit(MsgPassingCommunication::Message msg);
	bool echo(MsgPassingCommunication::Message msg);
	bool quit(MsgPassingCommunication::Message msg) { return true; }

	void addMsgProc(Key key, ServerProc proc);

	bool running_ = false;
	bool logOn = true;
  };

  class CodePubrServer :public ProtoServer {
  public:
	  CodePubrServer(MsgPassingCommunication::EndPoint ep, const std::string& name) :ProtoServer(ep, name) {}
	   void assembleDispatcher() override;
  private:
	  bool demoOn(MsgPassingCommunication::Message msg);
	  bool demoOff(MsgPassingCommunication::Message msg);
	  bool getFiles(MsgPassingCommunication::Message msg);
	  bool getDirs(MsgPassingCommunication::Message msg);
	  bool fullyProduce(MsgPassingCommunication::Message msg);
	  bool downloadSelected(MsgPassingCommunication::Message msg);
	  bool deleteClientStore(MsgPassingCommunication::Message msg);

	  void addandSendAssistEntities(Msg& reply);


  };
}