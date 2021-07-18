#ifndef TILT_LOOPGEN
#define TILT_LOOPGEN

#include "tilt/codegen/irgen.h"

#include <stdexcept>

using namespace std;

namespace tilt
{

    class LoopGenCtx : public IRGenCtx<Expr, Expr> {
    public:
        LoopGenCtx(Sym sym, const OpNode* op, Looper loop) :
            IRGenCtx(sym, &op->syms, &loop->syms), op(op), loop(loop)
        {}

    private:
        const OpNode* op;
        Looper loop;

        map<Sym, Sym> sym_ref_map;
        map<Sym, map<Point, Indexer>> pt_idx_maps;

        friend class LoopGen;
    };

    class LoopGen : public IRGen<LoopGenCtx, Expr, Expr> {
    public:
        LoopGen(LoopGenCtx ctx) : IRGen(ctx) {}

        static Looper Build(Sym, const OpNode*);

    private:
        Indexer& create_idx(const Sym, const Point);
        void build_loop();

        Sym& sym_ref(const Sym& sym) { return ctx().sym_ref_map[sym]; }

        Expr visit(const Symbol&) final;
        Expr visit(const IfElse&) final;
        Expr visit(const Get&) final;
        Expr visit(const New&) final;
        Expr visit(const Exists&) final;
        Expr visit(const ConstNode&) final;
        Expr visit(const NaryExpr&) final;
        Expr visit(const SubLStream&) final;
        Expr visit(const Element&) final;
        Expr visit(const OpNode&) final;
        Expr visit(const AggNode&) final;
        Expr visit(const AllocIndex&) final { throw std::runtime_error("Invalid expression"); };
        Expr visit(const GetTime&) final { throw std::runtime_error("Invalid expression"); };
        Expr visit(const GetIndex&) final { throw std::runtime_error("Invalid expression"); };
        Expr visit(const Fetch&) final { throw std::runtime_error("Invalid expression"); };
        Expr visit(const Load&) final { throw std::runtime_error("Invalid expression"); };
        Expr visit(const Store&) final { throw std::runtime_error("Invalid expression"); };
        Expr visit(const Advance&) final { throw std::runtime_error("Invalid expression"); };
        Expr visit(const NextTime&) final { throw std::runtime_error("Invalid expression"); };
        Expr visit(const GetStartIdx&) final { throw std::runtime_error("Invalid expression"); };
        Expr visit(const GetEndIdx&) final { throw std::runtime_error("Invalid expression"); };
        Expr visit(const CommitData&) final { throw std::runtime_error("Invalid expression"); };
        Expr visit(const CommitNull&) final { throw std::runtime_error("Invalid expression"); };
        Expr visit(const AllocRegion&) final { throw std::runtime_error("Invalid expression"); };
        Expr visit(const MakeRegion&) final { throw std::runtime_error("Invalid expression"); };
        Expr visit(const Call&) final { throw std::runtime_error("Invalid expression"); };
        Expr visit(const Loop&) final { throw std::runtime_error("Invalid expression"); };
    };

} // namespace tilt

#endif // TILT_LOOPGEN