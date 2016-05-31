#ifndef VIRTUALREALM_H
#define VIRTUALREALM_H
#include <vector>
#include <memory>
#include <unordered_map>
#include <boost/cstdint.hpp>
#include <boost/asio.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

class SessionPool;

class VirtualRealm : public std::enable_shared_from_this<VirtualRealm> {
 public:
  typedef std::shared_ptr<boost::asio::io_service> IOPtr;
  typedef std::shared_ptr<boost::asio::ip::tcp::acceptor> AcceptorPtr;
  typedef std::shared_ptr<VirtualRealm> Ptr;
  static Ptr Init(short port);
  VirtualRealm(short port);
  void Run();
  void PollOne();
  IOPtr io_service_;
 private:
  short port_;
  typedef std::shared_ptr<SessionPool> SessionPoolPtr;
  AcceptorPtr acceptor_;
  SessionPoolPtr sp_;
 public:
  SessionPoolPtr GetSessionPool();
};

class Session : public std::enable_shared_from_this<Session> {
  enum { MAX_LENGTH = 0x400 };
  typedef std::shared_ptr<SessionPool> SessionPoolPtr;
  boost::uint8_t buffer_[MAX_LENGTH];
  boost::asio::ip::tcp::socket socket_;
  std::string uuid_;
  SessionPoolPtr sp_; 

 public:
  std::string& GetUUID();
  typedef std::shared_ptr<Session> Ptr;
  static Ptr Init(std::string &uuid, SessionPoolPtr sp);
  boost::asio::ip::tcp::socket &GetSocket();
  Session(std::string &uuid, SessionPoolPtr sp);
};

class SessionPool : public std::enable_shared_from_this<SessionPool> {
  std::unordered_map<std::string, Session::Ptr> sessions_;
  VirtualRealm::AcceptorPtr acceptor_;

 public:
  static std::string GenerateUUID();
  typedef boost::uuids::basic_random_generator<boost::mt19937> Generator;
  VirtualRealm::IOPtr io_service_;
  typedef std::shared_ptr<SessionPool> Ptr;
  void GenerateAndAccept();
  SessionPool();
  static Ptr Init(VirtualRealm::AcceptorPtr acceptor, VirtualRealm::IOPtr io); 
 private:
  static Generator generator_;
};
#endif
