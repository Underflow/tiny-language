#include "program.h"

void Program::Pretty(std::ostream& strm) const
{
    for (const auto& decl : decls_)
        decl->Pretty(strm);
}
