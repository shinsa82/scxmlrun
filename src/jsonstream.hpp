// (C) Copyright IBM Corp. 2018.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef JSONSTREAM_HPP
#define JSONSTREAM_HPP

#include <nlohmann/json.hpp>
#include <mosquitto.h>

#include <istream>
#include <queue>

class jsonstream
{
public:
    virtual jsonstream& read (std::string&) = 0;
    virtual jsonstream& read (nlohmann::json&) = 0;
    virtual jsonstream& write (const std::string&) = 0;
    virtual jsonstream& write (nlohmann::json&) = 0;
};

// jsonistream

class jsonistream : public jsonstream
{
public:
    virtual jsonistream& read (std::string&) = 0;
    virtual jsonistream& read (nlohmann::json&) = 0;
    jsonstream& write (const std::string&) {}
    jsonstream& write (nlohmann::json&) {}
};

class jsonifstream : public jsonistream
{
public:
    virtual jsonifstream& read (std::string&);
    virtual jsonifstream& read (nlohmann::json&);

public:
    jsonifstream (void);
    jsonifstream (const char*);
    ~jsonifstream (void);

private:
    std::ifstream* _in;
};

// jsonimstream (mqtt)

class jsonimstream : public jsonistream
{
public:
    virtual jsonimstream& read (std::string&);
    virtual jsonimstream& read (nlohmann::json&);

public:
    jsonimstream (void);
    jsonimstream (mosquitto* mosq) : jsonimstream () { _mosq = mosq; }
    ~jsonimstream (void);

public:
    mosquitto& broker (void) { return (*_mosq); }
    std::queue<std::string*>& messages (void) { return (_messages); }

private:
    mosquitto* _mosq;
    std::queue<std::string*> _messages;
};

// jsonostream

class jsonostream : public jsonstream
{
public:
    jsonistream& read (std::string&) {}
    jsonostream& read (nlohmann::json&) {}
    virtual jsonostream& write (const std::string&) = 0;
    virtual jsonostream& write (nlohmann::json&) = 0;
};

class jsonofstream : public jsonostream
{
public:
    virtual jsonofstream& write (const std::string&);
    virtual jsonofstream& write (nlohmann::json&);

public:
    jsonofstream (void);
    jsonofstream (const char*);
    ~jsonofstream (void);

private:
    std::ofstream* _out;
};

// jsonomstream (mqtt)

class jsonomstream : public jsonostream
{
public:
    virtual jsonomstream& write (const std::string&);
    virtual jsonomstream& write (nlohmann::json&);

private:
    jsonomstream& write (const char* msg, const char* topic, int qos);

public:
    jsonomstream (void);
    jsonomstream (mosquitto* mosq, const char* topic = nullptr) :
        jsonomstream ()
    { _mosq = mosq; _topic = topic; }
    ~jsonomstream (void);

private:
    mosquitto* _mosq;
    const char* _topic;
};

#endif
