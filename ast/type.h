#pragma once

#include <map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

class Type
{
private:
    int id_;
    static int type_counter_;
    static std::map<Type, std::vector<Type>> cast_map_;
public:
    virtual void Pretty(std::ostream& strm) const;
    void SetCastable(Type& into_type);
    bool IsCastable(Type& into_type);
    bool operator==(Type const& t) const;
    bool operator<(Type const& t) const;
    int Id() const;
    Type();
};
