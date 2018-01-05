#include <stdio.h>
#include <iostream>
#include <boost/program_options.hpp>
#include "Core.hpp"
#include "Inst.hpp"

using namespace WdRiscv;


// Print on the standard output in hexadecimal notation the given
// 16-bit instruction code followed by the equivalent 32-bit instruction
// code.  If verbose is true, also print the assembly code of both
// 16 and 32 bit instructions.
static void
printExpanded(Core<uint32_t>& core, uint16_t inst16, bool verbose)
{
  uint32_t inst32 = 0;
  core.expandInst(inst16, inst32);

  printf("%04x %08x", inst16, inst32);
  if (verbose)
    {
      std::string asm16, asm32;
      core.disassembleInst16(inst16, asm16);
      core.disassembleInst32(inst32, asm32);
      printf("  %s  %s", asm16.c_str(), asm32.c_str());
    }
  printf("\n");
}


// Generate on the standard output all 16-bit instruction code and
// their equivalent 32-bit instruction codes.
int
main(int argc, char* argv[])
{
  bool verbose = false;

  try
    {
      // Define command line options.
      namespace po = boost::program_options;
      po::options_description desc("options");
      desc.add_options()
	("help,h", "Produce this message.")
	("verbose,v", "Generate assembly language for the compressed and expanded instructions");

      po::variables_map varMap;
      po::store(po::parse_command_line(argc, argv, desc), varMap);
      po::notify(varMap);

      verbose = varMap.count("verbose") > 0;
      if (varMap.count("help"))
	{
	  std::cout << "Generate all possible (valid and invalid) 16-bit ";
	  std::cout << "riscv compressed codes and\n";
	  std::cout << "corresponding uncompressed instruction codes.\n\n";
	  std::cout << desc;
	  return 0;
	}
    }
  catch (std::exception& exp)
    {
      std::cerr << "Failed to parse command line args: " << exp.what() << '\n';
      return 1;
    }


  unsigned hartId = 0, memSize = 1024, regCount = 32;
  Core<uint32_t> core(hartId, memSize, regCount);

  for (unsigned inst16 = 0; inst16 <= 0xffff; ++inst16)
    printExpanded(core, inst16, verbose);

  return 0;
}
