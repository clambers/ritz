#ifndef EXCEPTIONS_HH
#define EXCEPTIONS_HH

/**
 * Copyright (C) 2015 Chris Lamberson.
 *
 * This file is part of Ritz.
 *
 * Ritz is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * Ritz is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General
 * Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with Ritz. If not, see <http://www.gnu.org/licenses/>.
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include <exception>
#include <stdexcept>
#include <string>
#include <sstream>

namespace ritz {
  class runtime_error : public std::runtime_error {
  public:
    runtime_error(std::string const& m) :
      std::runtime_error("ritz error: "),
      message(m) {}

    virtual char const* what() const throw() override {
      oss.str("");
      oss << std::runtime_error::what() << message;
      return oss.str().c_str();
    }

  private:
    static std::ostringstream oss;
    std::string message;
  };

  class gai_error : public runtime_error {
  public:
    gai_error(int c) :
      runtime_error("getaddrinfo: "),
      code(c) {}

    virtual char const* what() const throw() override {
      oss.str("");
      oss << runtime_error::what() << gai_strerror(code);
      return oss.str().c_str();
    }

  private:
    static std::ostringstream oss;
    int code;
  };
}

std::ostringstream ritz::runtime_error::oss;
std::ostringstream ritz::gai_error::oss;

#endif
