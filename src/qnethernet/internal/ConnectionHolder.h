// SPDX-FileCopyrightText: (c) 2021-2022,2024 Shawn Silverman <shawn@pobox.com>
// SPDX-License-Identifier: AGPL-3.0-or-later

// ConnectionHolder.h holds everything needed to define a connection.
// This file is part of the QNEthernet library.

#pragma once

#include "lwip/opt.h"

#if LWIP_TCP

// C++ includes
#include <memory>
#include <vector>

#include "lwip/err.h"
#include "qnethernet/internal/ConnectionState.h"

namespace qindesign {
namespace network {
namespace internal {

// ConnectionHolder is effectively a connection proxy, useful because
// connections need to be managed by both a server and client. This is the
// argument passed to the lwIP callbacks.
struct ConnectionHolder final {
  err_t lastError = ERR_OK;
  /*volatile*/ bool connected = false;
  std::unique_ptr<ConnectionState> state;

  // Tracks acknowledged accepted connections. This will always be true for
  // connections that were initiated locally.
  /*volatile*/ bool accepted = false;

  // Remaining data after a connection is closed
  // Will only be non-empty after the connection is closed
  /*volatile*/ size_t remainingPos = 0;
  std::vector<uint8_t> remaining;
  // `remainingPos` should never be past the end of `remaining`
};

}  // namespace internal
}  // namespace network
}  // namespace qindesign

#endif  // LWIP_TCP
