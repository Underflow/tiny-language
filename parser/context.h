#pragma once

#include <string>
#include <vector>
#include <map>

#include "../ast/ast.h"

class Context
{
    public:
        typedef std::map<std::string, Ast*> Scope;

        Context();
        bool TypeExists(const std::string& ty) const;
		int TypeId(const std::string& ty);

        void PushScope();
        void PopScope();

        void DeclVar(const std::string& varname, Ast* decl);
        Ast* GetVar(const std::string& varname) const;

    private:
        std::map<std::string, int> types_;
        std::vector<Scope> vars_;
};
