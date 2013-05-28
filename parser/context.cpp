#include "context.h"

Context::Context()
{
	types_["int"] = 0;
	types_["float"] = 1;
	PushScope();
}


bool Context::TypeExists(const std::string& ty) const
{
	return types_.find(ty) != types_.end();
}

void Context::PushScope()
{
    vars_.push_back(Scope());
}

void Context::PopScope()
{
    vars_.pop_back();
}

void Context::DeclVar(const std::string& varname, VarDecl* decl)
{
	vars_.back()[varname] = decl;
}

VarDecl* Context::GetVar(const std::string& varname) const
{
	for (auto t = vars_.rbegin(); t != vars_.rend(); ++t)
	{
		auto& scope = *t;
		auto iter = scope.find(varname);

		if (iter != scope.end())
			return iter->second;
	}

	return nullptr;
}

int Context::TypeId(const std::string& ty)
{
	return types_[ty];
}