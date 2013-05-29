#pragma once

#include <map>
#include <iostream>
#include <set>
#include <algorithm>
#include <functional>

class Type
{
private:
    int id_;
    static std::map<Type, std::set<Type>> cast_map_;
public:
    virtual void Pretty(std::ostream& strm) const;
    void SetCastable(const Type& into_type);
    bool IsCastable(const Type& into_type) const;
    bool operator==(const Type& t) const;
    bool operator<(const Type& t) const;
    int Id() const;
    Type();
};
