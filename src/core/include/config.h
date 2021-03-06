// Copyright 2016 Chirstopher Torres (Raven), L3nn0x
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http ://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/*!
 * \file config.h
 *
 * \author L3nn0x
 * \date march 2016
 *
 * The configuration file
 */
#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <spdlog/spdlog.h>
#include <string>
#include "logconsole.h"

#include <visit_struct/visit_struct.hpp>
#include <configuru.hpp>

namespace Core {

/*!
 * \class Config
 *
 * \brief The configuration class
 *
 * This class is used to fetch the configuration from a config file, or create it if it doesn't exist
 * The file is in \s Json format to make it easier to read and modify
 *
 * \note This class is a singleton because the configuration is the same across the entire server
 */
class Config {
 public:
  /*!
   * \brief Function to get the single instance of the Config class
   *
   * This function will create a \s Config instance with specified filename on first call. It'll afterwards just return the instance
   *
   * \param[in] filename The name of the configuration file to be loaded/created. It'll only be used on the fisrt call and thus can be ignored afterwards.
   * \param[out] Config& The \s Config instance
   */
  static Config &getInstance(std::string filename = "server.json");

 private:
  Config(std::string filename);
  Config(const Config &) = delete;
  Config &operator=(const Config &) = delete;
  ~Config();

  std::string file_;

 public:
  struct Database {
    std::string host = "127.0.0.1";
    std::string database = "osirose";
    std::string user = "root";
    std::string password = "";
    uint16_t port = 3306;
  };
  struct ServerData {
    uint32_t id = 0;
    std::string ip = "127.0.0.1";
    std::string iscListenIp = "127.0.0.1";
    uint8_t accessLevel = 1;
    uint32_t parentId = 0;
    uint32_t maxConnections = 0;
    bool useThreads = true;
    uint32_t maxThreads = 512;
    uint8_t mode = 0;
  };
  struct LoginServer {
    uint16_t clientPort = 29000;
    uint16_t iscPort = 29010;
    uint8_t accessLevel = 1;
    uint8_t logLevel = 2;
  };
  struct CharServer {
    std::string worldName = "osIROSE";
    std::string loginIp = "127.0.0.1";
    uint16_t clientPort = 29100;
    uint16_t iscPort = 29110;
    uint8_t accessLevel = 1;
    uint8_t logLevel = 2;
  };
  struct MapServer {
    std::string channelName = "Athena";
    std::string charIp = "127.0.0.1";
    uint16_t clientPort = 29200;
    uint16_t iscPort = 29210;
    uint8_t accessLevel = 1;
    uint16_t mapId = 0;
    uint8_t logLevel = 2;
  };
  struct Configuration {
    Database database;
    ServerData serverData;
    LoginServer loginServer;
    CharServer charServer;
    MapServer mapServer;
  };

 private:
  Configuration config_;

 public:
  Database& database() { return config_.database; }
  ServerData& serverData() { return config_.serverData; }
  LoginServer& loginServer() { return config_.loginServer; }
  CharServer& charServer() { return config_.charServer; }
  MapServer& mapServer() { return config_.mapServer; }

};

}

VISITABLE_STRUCT(Core::Config::Database, host, database, user, password, port);
VISITABLE_STRUCT(Core::Config::ServerData, id, ip, iscListenIp, accessLevel, parentId, maxConnections, useThreads, maxThreads, mode);
VISITABLE_STRUCT(Core::Config::LoginServer, clientPort, iscPort, accessLevel, logLevel);
VISITABLE_STRUCT(Core::Config::CharServer, worldName, loginIp, clientPort, iscPort, accessLevel, logLevel);
VISITABLE_STRUCT(Core::Config::MapServer, channelName, charIp, clientPort, iscPort, accessLevel, mapId, logLevel);
VISITABLE_STRUCT(Core::Config::Configuration, database, serverData, loginServer, charServer, mapServer);

#endif /* !_CONFIG_H_ */
