#include "program.h"

void Program::Pretty(std::ostream& strm) const
{
    strm << "#include \"runtime.h\"\n";
    for (const auto& var : vars_)
    {
        var->Pretty(strm);
        strm << ";\n";
    }

    for (const auto& fun : funs_)
        fun->Pretty(strm);

    for (const auto& fun : funs_)
    {
        strm << "int " << fun->name() << "_wrap(char** args)\n"
            "{\n"
            "    return " << fun->name() << "(";
        if (fun->nb_args() > 0)
        {
            int i = 0;
            strm << "atoi(args[" << i << "])";
            ++i;

            for (; i < fun->nb_args(); ++i)
                strm << ", atoi(args[" << i << "])";
        }
        strm << ");\n"
            "}\n";
    }

    strm <<
        "int main(int argc, char** argv)\n"
        "{\n"
        "    struct hash_tab *fun_table = NULL;\n";
        
    for (const auto& fun : funs_)
        strm <<
        "    register_fun(&fun_table, \"" << fun->name()
                << "\", &" + fun->name() << "_wrap);\n";

    strm <<
        "    exec(argv[1], (char**)&argv[2], fun_table);\n"
        "}\n";
}
