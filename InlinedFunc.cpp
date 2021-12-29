#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace {
struct GetInlined : public FunctionPass {

  static char ID;
  GetInlined() : FunctionPass(ID) {}

  virtual bool runOnFunction(Function &F) override {
    outs() << "*";
    outs().write_escaped(F.getName()) << '\n';
    for (auto &B : F) {
      for (auto &I : B) {
        if (CallInst *CI = dyn_cast<CallInst>(&I)) {
          outs() << " |-" << CI->getCalledFunction()->getName() << "\n";
        }
      }
    }
    return false;
  }
};
} // namespace

char GetInlined::ID = 0;
static RegisterPass<GetInlined> X("inlines", "Display inlined Function", false,
                                  false);
