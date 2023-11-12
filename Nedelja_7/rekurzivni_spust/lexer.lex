%option noyywrap

%{
    #include <iostream>
    #include <cstdlib>
    #include <string>

    using namespace std;

    #include "tokeni.hpp"
%}

%%

[0-9]+    { return BROJ; }
"+"       { return PLUS; }
"*"       { return PUTA; }
"("       { return OZ; }
")"       { return ZZ; }

%%