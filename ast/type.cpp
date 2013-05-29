#include "type.h"

std::map<Type, std::set<Type>> Type::cast_map_;

void Type::Pretty(std::ostream& strm) const
{
    strm << "Type id: " << id_;
}

Type::Type()
{
    static int type_counter_;
    id_ = type_counter_;
    type_counter_++;
}

inline int Type::Id() const
{
    return id_;
}

void Type::SetCastable(const Type& into_type)
{
    cast_map_[*this].insert(into_type);
}

inline bool Type::operator<(const Type& t) const
{
    return id_ < t.Id();
}
inline bool Type::operator==(const Type& t) const
{
    return id_ == t.Id();
}

bool Type::IsCastable(const Type& into_type) const
{
    if(cast_map_.find(*this) != cast_map_.end())
    {
        std::set<Type>& castable = cast_map_[*this];
        if (castable.find(into_type) != castable.end())
            return true;
        else
        {
            bool res = false;
            for(const Type& t : castable)
            {
                res = res || t.IsCastable(into_type);
                if(res)
                    return true;
            }
        }
    }
    return false;
}
