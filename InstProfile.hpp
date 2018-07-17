// -*- c++ -*-

#pragma once

#include <vector>
#include <unordered_map>
#include "InstId.hpp"


namespace WdRiscv
{

  struct InstProfile
  {
    InstId id_ = InstId::illegal;
    uint64_t freq_ = 0;  // Number of times instruction was executed

    // One entry per interger register: Count of times register was used
    // by instruction as rd.
    std::vector<uint64_t> rd_;

    // One entry per interger register: Count of times register was
    // used by instruction as rs1.
    std::vector<uint64_t> rs1_;

    // One entry per interger register: Count of times register was
    // used by instruction as rs2/immediate.
    std::vector<uint64_t> rs2_;

    int32_t minImm_ = 0;  // Minumum immediate operand value.
    int32_t maxImm_ = 0;  // Maximum immediage operand value.
  };
}


    