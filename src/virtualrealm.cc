#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/lexical_cast.hpp>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <memory>
#include <thread>
#include <utility>
#include "virtualrealm.h"
#include "logger.h"
#include "util.h"

namespace ip = boost::asio::ip;

VirtualRealm::VirtualRealm(short port) : port_(port) {}

VirtualRealm::Ptr VirtualRealm::Init(short port) {
  VirtualRealm::Ptr retval = Ptr(new VirtualRealm(port));
  retval->io_service_ = IOPtr(new boost::asio::io_service());
  retval->acceptor_ = AcceptorPtr(new ip::tcp::acceptor(*retval->io_service_, ip::tcp::endpoint(ip::tcp::v4(), port)));
  retval->sp_ = SessionPool::Init(retval->acceptor_, retval->io_service_);
  return retval;
}

static void Worker(VirtualRealm::Ptr vr) { vr->io_service_->run(); }

static void SingleWorker(VirtualRealm::Ptr vr) { vr->io_service_->poll_one(); }

void VirtualRealm::Run() {
  boost::thread_group threads;
  for (unsigned int i = 0; i < (std::thread::hardware_concurrency()
                                    ? std::thread::hardware_concurrency()
                                    : 2);
       ++i) {
    threads.create_thread(boost::bind(&Worker, shared_from_this()));
  }
  threads.join_all();
}

void VirtualRealm::PollOne() {
  boost::thread_group threads;
  for (unsigned int i = 0; i < (std::thread::hardware_concurrency() ? std::thread::hardware_concurrency() : 2); ++i) {
    threads.create_thread(boost::bind(&SingleWorker, shared_from_this()));
  }
  threads.join_all();
}


SessionPool::SessionPool() {}

SessionPool::Ptr SessionPool::Init(VirtualRealm::AcceptorPtr acceptor, VirtualRealm::IOPtr io_service) {
  Ptr retval = Ptr(new SessionPool());
  retval->io_service_ = io_service;
  retval->acceptor_ = acceptor;

  retval->GenerateAndAccept();
  return retval;
}

SessionPool::Generator SessionPool::generator_;

SessionPool::Ptr VirtualRealm::GetSessionPool() { return sp_; }

std::string SessionPool::GenerateUUID() {
  return boost::uuids::to_string(generator_());
}

void SessionPool::GenerateAndAccept() {
  auto self = shared_from_this();
  std::string uuid = GenerateUUID();
  Session::Ptr session =
      Session::Init(uuid, self);

  sessions_[uuid] = session;
  acceptor_->async_accept(session->GetSocket(),
                         [this, self, uuid](const boost::system::error_code &err) {
                           if (err) sessions_.erase(uuid);
                           self->GenerateAndAccept();
                         });
}

Session::Session(std::string &uuid, SessionPool::Ptr sp)
    : sp_(sp), uuid_(uuid), socket_(*sp->io_service_) {}

Session::Ptr Session::Init(std::string &uuid,
                           SessionPool::Ptr sp) {
  return Ptr(new Session(uuid, sp));
}

ip::tcp::socket &Session::GetSocket() { return socket_; }
