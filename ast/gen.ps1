$classes = "VarDecl", "FunDecl", "Type", "Block", "CompoundExp",
    "Statement", "Exp", "Affect", "Comparison", "LowExp", "HighExp", "Paren",
    "Term", "Funcall", "IntLit", "FloatLit", "BoolLit", "Prototype", "Fundef",
    "StringLit"

foreach ($c in $classes) {

    $f = New-Item ($c.ToLower() + ".h") -type file

    $txt =

"#pragma once

#include `"ast.h`"

class $c : public Ast
{
    virtual void Pretty(std::ostream& strm) const;
};
"

    echo $txt > $f

    $f = New-Item($c.ToLower() + ".cpp") -type file

    $txt =
"#include `"${c.ToLower()}.h`"

void $c::Pretty(std::ostream& strm) const
{
}
"

    echo $txt > $f
}
