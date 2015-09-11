#ifndef NETSTREAM_HH
#define NETSTREAM_HH

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

#include "exceptions.hh"

#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#include <iostream>
#include <string>

namespace ritz {
  template<typename _CharT, typename _Traits = std::char_traits<_CharT>>
  class basic_sockbuf
    : public std::basic_streambuf<_CharT, _Traits>
  {
  public:
    using char_type = _CharT;
    using traits_type = _Traits;
    using int_type = typename traits_type::int_type;
    using pos_type = typename traits_type::pos_type;
    using off_type = typename traits_type::off_type;

    basic_sockbuf() :
      std::basic_streambuf<char_type, traits_type>(),
      boundp(false),
      sd(0)
    {}

    basic_sockbuf(basic_sockbuf const& rhs) = delete;

    basic_sockbuf(basic_sockbuf&& rhs) {
      boundp = rhs.openp;
      rhs.openp = false;
      sd = rhs.sd;
      rhs.sd = 0;
    }

    basic_sockbuf& operator=(basic_sockbuf&& rhs) {
      this->close();
      boundp = rhs.boundp;
      rhs.boundp = false;
      sd = rhs.sd;
      rhs.sd = 0;

      return *this;
    }

    basic_sockbuf& operator=(basic_sockbuf const& rhs) = delete;

    virtual ~basic_sockbuf() {
      try {
        this->close();
      } catch (std::exception const& e) {}
    }

    void swap(basic_sockbuf& rhs) {
      bool boundp_tmp = boundp;
      int sd_tmp = sd;

      boundp = rhs.boundp;
      sd = rhs.sd;
      rhs.openp = boundp_tmp;
      rhs.sd_temp = sd_tmp;
    }

    bool is_bound() const {
      return boundp;
    }

    basic_sockbuf* bind(std::string const& addr, std::string const& port) {
      struct addrinfo hints, *server, *p;
      int res, yes=1;

      memset(&hints, 0, sizeof(struct addrinfo));
      hints.ai_family = AF_UNSPEC;
      hints.ai_socktype = SOCK_STREAM;
      hints.ai_flags = AI_PASSIVE;

      if ((res = getaddrinfo(addr.c_str(),port.c_str(),&hints,&server)) != 0)
        throw gai_error(res);

      for (p = server; p != nullptr; p = p->ai_next) {
        if ((sd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
          continue;

        if (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
          throw runtime_error("setsockopt failed");

        if (::bind(sd, p->ai_addr, p->ai_addrlen) == -1) {
          ::close(sd);
          continue;
        }

        break;
      }

      this->sd = sd;

      return this;
    }

    void close() {
      ::close(sd);
      boundp = false;
      sd = 0;
    }

  private:
    bool boundp;
    int sd;
  };

  using sockbuf = basic_sockbuf<char>;
  using wsockbuf = basic_sockbuf<wchar_t>;
}

#endif
