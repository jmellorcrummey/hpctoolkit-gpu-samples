#include <iostream>
#include <sstream>
#include <vector>
#include "cfg.h"
#include "cfg_analyzer.h"
#include "graph_reader.h"

int main() {
  GraphReader graph_reader("sample.dot");
  std::vector<Function *> functions = graph_reader.construct_cfg();

  CFGAnalyzer analyzer(functions);
  std::vector<Call *> calls = analyzer.extract_calls();
  for (auto call : calls) {
    std::stringstream stream;
    stream << std::hex << call->caller_block->insts.front()->offset;
    std::cout << "From func<" << call->caller_function->name << "> 0x" << stream.str() <<
      " to " << call->callee_function->name << std::endl;
  }

  std::vector<Loop *> loops = analyzer.extract_loops();
  for (auto loop : loops) {
    for (auto entry : loop->entries) {
      std::cout << "In function <" << loop->function->name << ">" << std::endl;
      std::stringstream stream;
      stream << std::hex << entry->entry_block->insts.front()->offset;
      std::cout << "Loop entry point 0x" << stream.str() << std::endl;
      stream << std::hex << entry->back_edge_block->insts.back()->offset;
      std::cout << "Loop entry back edge 0x" << stream.str() << std::endl;
    }
  }

  return 0;
}
