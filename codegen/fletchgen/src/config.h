#pragma once

#include <cstdint>
#include "constants.h"
#include "arrow-utils.h"

namespace fletchgen {
namespace config {

typedef unsigned int width;

struct Burst {
  unsigned int step = 1;
  unsigned int max = 64;
};

/// Bus related configuration
struct Bus {
  width addr_width = ce::BUS_ADDR_WIDTH_DEFAULT;
  width data_width = ce::BUS_DATA_WIDTH_DEFAULT;
  width len_width = ce::BUS_LEN_WIDTH_DEFAULT;
  Burst burst;
};

/// MMIO related configuration
struct Reg {
  width reg_width = ce::REG_WIDTH_DEFAULT;
};

/// Arrow related configuration
struct Arrow {
  width index_width = ce::INDEX_WIDTH_DEFAULT;
};

/// UserCore related configuration
struct User {
  width tag_width = ce::TAG_WIDTH_DEFAULT;
  unsigned int num_user_regs = 0;
};

/// Platform configuration
struct Platform {
  Bus bus;
  Reg reg;
  unsigned int regs_per_address() { return bus.addr_width / reg.reg_width; }
};

/// Global configuration used in creating wrapper & top level
struct Config {
  Config() = default;

  Platform plat;
  Arrow arr;
  User user;
};

/// Default configuration
constexpr Config default_config;

/// @brief Derive a configuration from Schema metadata.
Config fromSchema(arrow::Schema *schema);

} // namespace config
} // namespace fletchgen