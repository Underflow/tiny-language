#include "type.h"


std::map<Type, std::vector<Type>> Type::cast_map_;
int Type::type_counter_;

void Type::Pretty(std::ostream& strm) const
{
    strm << "Type id: " << id_;
}

Type::Type()
{
    id_ = type_counter_;
    type_counter_++;
}

int Type::Id() const
{
    return id_;
}

void Type::SetCastable(Type& into_type)
{
    if(cast_map_.find(*this) != cast_map_.end())
    {
        cast_map_[*this].push_back(into_type);
    }
    else
    {
        cast_map_[*this] = {into_type};
    }
}

bool Type::operator<(Type const& t) const
{
    return id_ < t.Id();
}
bool Type::operator==(Type const& t) const
{
    return id_ == t.Id();
}

bool Type::IsCastable(Type& into_type)
{
    if(cast_map_.find(*this) != cast_map_.end())
    {
        std::vector<Type>& castable = cast_map_[*this];
        if(std::find(castable.begin(), castable.end(), into_type) != castable.end())
            return true;
        else
        {
            bool res = false;
            for(Type t : castable)
            {
                res = res || t.IsCastable(into_type);
                if(res)
                    return true;
            }
        }
    }
    return false;
}
