/* Hijerarhija klasa koja predstavlja cvorove stabla */
#ifndef SYNTAX_TREE_H
#define SYNTAX_TREE_H

#include <iostream>
#include <cstdlib>
#include <vector>
/* izvrsavanje zavisi od vrednosti promenljivih, 
 * pa ukljucujemo potrebne tipove
 */
#include "SymbolTable.hpp"

/* apstraktna klasa koja definise cvor sintaksnog stabla u opstem slucaju */
class SyntaxTreeNode {

public:
    /* podrazumevani konstruktor */
    SyntaxTreeNode() { }
    /* virtuelni destruktor da bismo omogucili pravilno nadovezivanje
     * destruktora prilikom unistavanja objekata hijerarhije 
     */
    virtual ~SyntaxTreeNode() { }
    /* apstraktni metod koji izvrsava dati tip naredbe */
    virtual double Interpret(SymbolTable& st) const = 0;
    /* apstraktni metod kompajlira dati tip naredbe */
    virtual void Compile(SymbolTable& st) const = 0;
    /* apstraktni metod kreira kopiju postojeceg objekta */
    virtual SyntaxTreeNode* Clone() const = 0;
    /* apstraktni metod kreira string reprezentaciju cvora */
    virtual void Print(std::ostream& s) const = 0;
};

/* predefinisani operator kojim se stampa cvor sintaksnog stabla */
std::ostream& operator <<(std::ostream& s, const SyntaxTreeNode& stn);

/* izvedena klasa koja predstavlja niz naredbi */
class StatementSequenceNode : public SyntaxTreeNode {

private:
    /* u cvoru cuvamo niz naredbi, tj. cvorova naslednika (n-arni cvor)*/
    std::vector<SyntaxTreeNode*> _statements;
    /* pomocni metod koji uslobadja resurse */
    void Free();
    /* pomocni metod koji kreira duboku kopiju atributa klase */
    void Copy(const std::vector<SyntaxTreeNode*>& vec);
public:
    /* konstruktor */
    StatementSequenceNode();
    /* kosntruktor kopije */
    StatementSequenceNode(const StatementSequenceNode& ss);
    /* destruktor je obavezan, jer klasa u sebi cuva dinamicke resurse */
    ~StatementSequenceNode();

    /* pomocni metod kojim se dodaje novi dete cvor u niz dece cvorova */
    void Add(SyntaxTreeNode* statement);
    /* konkretni metod koji izvrsava dati tip naredbe */
    virtual double Interpret(SymbolTable& st) const;
    /* konkretni metod kompajlira dati tip naredbe */
    virtual void Compile(SymbolTable& st) const;
    /* konkretni metod kreira kopiju postojeceg objekta */
    virtual SyntaxTreeNode* Clone() const;
    virtual void Print(std::ostream& s) const;
};

class AssignmentNode : public SyntaxTreeNode {
private:
    std::string _identifier;
    SyntaxTreeNode* _val;
public: 
    /* konstruktor */
    AssignmentNode(const std::string& id, SyntaxTreeNode* val);
    /* konstruktor kopije */
    AssignmentNode(const AssignmentNode& a);
    /* destruktor je obavezan, jer klasa u sebi cuva dinamicke resurse */
    ~AssignmentNode();
    
    /* konkretni metod koji izvrsava dati tip naredbe */
    virtual double Interpret(SymbolTable& st) const;
    /* konkretni metod kompajlira dati tip naredbe */
    virtual void Compile(SymbolTable& st) const;
    /* konkretni metod kreira kopiju postojeceg objekta */
    virtual SyntaxTreeNode* Clone() const;
    virtual void Print(std::ostream& s) const;
};

class PrintNode : public SyntaxTreeNode {
private:
    SyntaxTreeNode* _statement;
public: 
    /* konstruktor */
    PrintNode( SyntaxTreeNode* val);
    /* konstruktor kopije */
    PrintNode(const PrintNode& a);
    /* destruktor je obavezan, jer klasa u sebi cuva dinamicke resurse */
    ~PrintNode();

    /* konkretni metod koji izvrsava dati tip naredbe */
    virtual double Interpret(SymbolTable& st) const;
    /* konkretni metod kompajlira dati tip naredbe */
    virtual void Compile(SymbolTable& st) const;
    /* konkretni metod kreira kopiju postojeceg objekta */
    virtual SyntaxTreeNode* Clone() const;
    virtual void Print(std::ostream& s) const;
};

class ConstantNode : public SyntaxTreeNode {
private:
    double _val;
public: 
    /* konstruktor */
    ConstantNode( double val);
    /* konstruktor kopije */
    ConstantNode(const ConstantNode& a);    

    /* konkretni metod koji izvrsava dati tip naredbe */
    virtual double Interpret(SymbolTable& st) const;
    /* konkretni metod kompajlira dati tip naredbe */
    virtual void Compile(SymbolTable& st) const;
    /* konkretni metod kreira kopiju postojeceg objekta */
    virtual SyntaxTreeNode* Clone() const;
    virtual void Print(std::ostream& s) const;
};

class IdentifierNode : public SyntaxTreeNode {
private:
    std::string _name;
public: 
    /* konstruktor */
    IdentifierNode(const std::string& name);
    /* konstruktor kopije */
    IdentifierNode(const IdentifierNode& a);

    /* konkretni metod koji izvrsava dati tip naredbe */
    virtual double Interpret(SymbolTable& st) const;
    /* konkretni metod kompajlira dati tip naredbe */
    virtual void Compile(SymbolTable& st) const;
    /* konkretni metod kreira kopiju postojeceg objekta */
    virtual SyntaxTreeNode* Clone() const;
    virtual void Print(std::ostream& s) const;
};

class BinaryOperatorNode : public SyntaxTreeNode {

protected:
    std::string _symbol;
    SyntaxTreeNode *_left, *_right;
public:
    /* konstruktor */
    BinaryOperatorNode(const std::string symbol, SyntaxTreeNode* op1, SyntaxTreeNode* op2);
    /* destruktor je obavezan, jer klasa u sebi cuva dinamicke resurse */
    ~BinaryOperatorNode();

    /* apstraktni metod koji izvrsava dati tip naredbe */
    virtual double Interpret(SymbolTable& st) const = 0;
    /* apstraktni metod kompajlira dati tip naredbe */
    virtual void Compile(SymbolTable& st) const = 0;
    /* apstraktni metod kreira kopiju postojeceg objekta */
    virtual SyntaxTreeNode* Clone() const = 0;
    virtual void Print(std::ostream& s) const;
};

class PlusNode : public BinaryOperatorNode {
public:
    /* konstruktor */
    PlusNode(const std::string symbol, SyntaxTreeNode* op1, SyntaxTreeNode* op2);
    /* konstruktor kopije */
    PlusNode(const PlusNode& op);

    /* konkretni metod koji izvrsava dati tip naredbe */
    virtual double Interpret(SymbolTable& st) const;
    /* konkretni metod kompajlira dati tip naredbe */
    virtual void Compile(SymbolTable& st) const;
    /* konkretni metod kreira kopiju postojeceg objekta */
    virtual SyntaxTreeNode* Clone() const;
};

class MinusNode : public BinaryOperatorNode {
public:
    /* konstruktor */
    MinusNode(const std::string symbol, SyntaxTreeNode* op1, SyntaxTreeNode* op2);
    /* konstruktor kopije */
    MinusNode(const MinusNode& op);

    /* konkretni metod koji izvrsava dati tip naredbe */
    virtual double Interpret(SymbolTable& st) const;
    /* konkretni metod kompajlira dati tip naredbe */
    virtual void Compile(SymbolTable& st) const;
    /* konkretni metod kreira kopiju postojeceg objekta */
    virtual SyntaxTreeNode* Clone() const;
};

class TimesNode : public BinaryOperatorNode {
public:
    /* konstruktor */
    TimesNode(const std::string symbol, SyntaxTreeNode* op1, SyntaxTreeNode* op2);
    /* konstruktor kopije */
    TimesNode(const TimesNode& op);

    /* konkretni metod koji izvrsava dati tip naredbe */
    virtual double Interpret(SymbolTable& st) const;
    /* konkretni metod kompajlira dati tip naredbe */
    virtual void Compile(SymbolTable& st) const;
    /* konkretni metod kreira kopiju postojeceg objekta */
    virtual SyntaxTreeNode* Clone() const;
};

class DivisionNode : public BinaryOperatorNode {
public:
    /* konstruktor */
    DivisionNode(const std::string symbol, SyntaxTreeNode* op1, SyntaxTreeNode* op2);
    /* konstruktor kopije */
    DivisionNode(const DivisionNode& op);

    /* konkretni metod koji izvrsava dati tip naredbe */
    virtual double Interpret(SymbolTable& st) const;
    /* konkretni metod kompajlira dati tip naredbe */
    virtual void Compile(SymbolTable& st) const;
    /* konkretni metod kreira kopiju postojeceg objekta */
    virtual SyntaxTreeNode* Clone() const;
};

class UnaryOperatorNode : public SyntaxTreeNode {

protected:
    std::string _symbol;
    SyntaxTreeNode *_exp;
public:
    /* konstruktor */
    UnaryOperatorNode(const std::string symbol, SyntaxTreeNode* op1);
    /* destruktor je obavezan, jer klasa u sebi cuva dinamicke resurse */
    ~UnaryOperatorNode();

    /* apstraktni metod koji izvrsava dati tip naredbe */
    virtual double Interpret(SymbolTable& st) const = 0;
    /* apstraktni metod kompajlira dati tip naredbe */
    virtual void Compile(SymbolTable& st) const = 0;
    /* apstraktni metod kreira kopiju postojeceg objekta */
    virtual SyntaxTreeNode* Clone() const = 0;
    virtual void Print(std::ostream& s) const;
};

class UMinusNode : public UnaryOperatorNode {
public:
    /* konstruktor */
    UMinusNode(const std::string symbol, SyntaxTreeNode* op);
    /* konstruktor kopije */
    UMinusNode(const UMinusNode& op);

    /* konkretni metod koji izvrsava dati tip naredbe */
    virtual double Interpret(SymbolTable& st) const;
    /* konkretni metod kompajlira dati tip naredbe */
    virtual void Compile(SymbolTable& st) const;
    /* konkretni metod kreira kopiju postojeceg objekta */
    virtual SyntaxTreeNode* Clone() const;
};

class LogicalNode : public BinaryOperatorNode {
public:
    /* konstruktor */
    LogicalNode(const std::string symbol, SyntaxTreeNode* op1, SyntaxTreeNode* op2);
    /* konstruktor kopije */
    LogicalNode(const LogicalNode& op);

    /* konkretni metod koji izvrsava dati tip naredbe */
    virtual double Interpret(SymbolTable& st) const;
    /* konkretni metod kompajlira dati tip naredbe */
    virtual void Compile(SymbolTable& st) const;
    /* konkretni metod kreira kopiju postojeceg objekta */
    virtual SyntaxTreeNode* Clone() const;
};

#endif
