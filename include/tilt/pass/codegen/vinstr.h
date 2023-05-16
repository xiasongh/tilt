#ifndef INCLUDE_TILT_PASS_CODEGEN_VINSTR_H_
#define INCLUDE_TILT_PASS_CODEGEN_VINSTR_H_

#include "tilt/base/type.h"

#define TILT_VINSTR_ATTR __attribute__((always_inline))

#define REGISTER_VINSTR(MOD, CTX, VINSTR, ...) \
    llvm::Linker::linkModules(MOD, easy::get_module(CTX, VINSTR, __VA_ARGS__)); \
    (MOD).getFunction(#VINSTR)->setLinkage(llvm::Function::InternalLinkage);

namespace tilt {
extern "C" {

TILT_VINSTR_ATTR uint32_t get_buf_size(ts_t);
TILT_VINSTR_ATTR ts_t get_start_time(region_t*);
TILT_VINSTR_ATTR ts_t get_end_time(region_t*);
TILT_VINSTR_ATTR ts_t get_ckpt(region_t*, ts_t);
TILT_VINSTR_ATTR char* fetch(region_t*, ts_t, uint32_t);
TILT_VINSTR_ATTR region_t* make_region(region_t*, region_t*, ts_t, ts_t);
TILT_VINSTR_ATTR region_t* init_region(region_t*, ts_t, uint32_t, char*);
TILT_VINSTR_ATTR region_t* commit_data(region_t*, ts_t);
TILT_VINSTR_ATTR region_t* commit_null(region_t*, ts_t);

}  // extern "C"
}  // namespace tilt

#endif  // INCLUDE_TILT_PASS_CODEGEN_VINSTR_H_
