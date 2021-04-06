// Copyright 2021 Lamp

#ifndef INCLUDE_COMMON_HPP_
#define INCLUDE_COMMON_HPP_


// JSON - parser
#include <nlohmann/json.hpp>
using json = nlohmann::json;
// Processes libs
#include <boost/process.hpp>
#include <async++.h>

// Boost prog options
#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include <boost/thread.hpp>
#include <boost/thread/thread.hpp>
#include <sstream>
// Boost log
#include <boost/log/core.hpp>
#include <boost/log/common.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/exceptions.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/utility/setup/console.hpp>

#include <memory>

#include <csignal>
#include <ctime>
#include <pthread.h>
#include <iostream>

#include <filesystem>

#include <string>

class settings {
 public:
  const std::string BUILD_TARGET = "_builds";
  const std::string INSTALL_TARGET = "_install";
  const std::string PACK_TARGET = "package";
  [[nodiscard]] std::string get_conifig() const { return _config; }
  [[nodiscard]] bool        install()     const { return _install; }
  [[nodiscard]] bool        pack()        const { return _pack; }

  settings(const std::string& config, bool install, bool pack)
      :_config(config), _install(install), _pack(pack){
  }

 private:
  std::string _config,
      _source_path;
  bool _install,
       _pack;

 public:
  std::string get_command(const std::string& target){
    if (target == "config") {
      return (" -B" + BUILD_TARGET + " -DCMAKE_INSTALL_PREFIX=" +
              INSTALL_TARGET + " -DCMAKE_BUILD_TYPE=" + _config);
    } else {
      return ("--target " + BUILD_TARGET +
              (target != "build" ? (" --target " + target) : ""));
    }
  }
};

struct thread_data {
 public:
  thread_data() = delete;

  bool _terminated = false;
  boost::process::child _current_child;
};

namespace log_setup {
  void init();
}

#endif // INCLUDE_COMMON_HPP_
