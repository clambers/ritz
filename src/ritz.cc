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

#include <node.h>

namespace ritz {
  using namespace v8;

  void create_server(FunctionCallbackInfo<Value> const& args) {
    Isolate* iso = args.GetIsolate();
    args.GetReturnValue().Set(String::NewFromUtf8(iso, "Hello world!"));
  }

  void init(Local<Object> exports) {
    NODE_SET_METHOD(exports, "createServer", create_server);
  }

  NODE_MODULE(addon, init)
}
