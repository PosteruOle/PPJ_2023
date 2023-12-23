#include "SyntaxTree.hpp"

/********************************* Syntax tree node **************************************/

/* definicija operatora << */
std::ostream& operator <<(std::ostream& s, const SyntaxTreeNode& stn) {

    /* rekurzivno stampamo stablo, pocevsi od cvora stn */
    stn.Print(s);
    /* vracamo tok */
    return s;
}

/********************************* Statement Sequence **************************************/

/* podrazumevani konstruktor */
StatementSequenceNode::StatementSequenceNode() : _statements(){

}
/* konstruktor kopije */
StatementSequenceNode::StatementSequenceNode(const StatementSequenceNode& ss) : _statements(){

    /* pravimo duboku kopiju objekata */
    Copy(ss._statements);
}
/* destruktor */
StatementSequenceNode::~StatementSequenceNode() {

    /* oslobadjamo dinamicke resurse koje klasa cuva */
    Free();
}

/* pomocni metod koji oslobadja memoriju */
void StatementSequenceNode::Free() {

    /* redom oslobadjamo svaku naredbu iz vektora */
    for (auto it = _statements.begin(); it != _statements.end(); it++) {
        delete *it;
    }
}

/* pomocni metod koji pravi duboku kopiju postojeceg vektora naredbi */
void StatementSequenceNode::Copy(const std::vector<SyntaxTreeNode*>& vec) {

    /* redom prolazimo kroz vektor argument i dodajemo duboke kopije u vektor atribut */
    for (auto it = vec.begin(); it != vec.end(); it++) {
        _statements.push_back((*it)->Clone());
    }
}

/* metod dodaje naredbu u vektor naredbi */
void StatementSequenceNode::Add(SyntaxTreeNode* statement) {

    /* na kraj vektora se dodaje nova naredba */
    _statements.push_back(statement);
}

/* metod koji izvrsava dati tip naredbe */
double StatementSequenceNode::Interpret(SymbolTable& st) const {

    /* prolazimo kroz vektor naredbi i redom svaku izvrsavamo */
    for (auto it = _statements.begin(); it != _statements.end(); it++) {
        (*it)->Interpret(st);
    }
    /* povratna vrednost ovde postoji samo radi potpunosti */
    return 0;
}

/* metod kompajlira dati tip naredbe */
void StatementSequenceNode::Compile(SymbolTable& st) const {

    /* prolazimo kroz vektor naredbi i redom svaku kompajliramo */
    for (auto it = _statements.begin(); it != _statements.end(); it++) {
        (*it)->Compile(st);
        std::cout << std::endl;
    }
}

/* metod kreira kopiju postojeceg objekta */
SyntaxTreeNode* StatementSequenceNode::Clone() const {

    /* kopiramo objekat pozivom konstruktora kopije */
    return new StatementSequenceNode(*this);
}

/* metod kreira string reprezentaciju cvora */
void StatementSequenceNode::Print(std::ostream& s) const {

    /* prolazimo kroz vektor naredbi i stampamo svaku naredbu */
    for (auto it = _statements.begin(); it != _statements.end(); it++) {
        (*it)->Print(s);
    }
}

/********************************* Assignment Node **************************************/

/* konstruktor - plitko kopiranje atributa */
AssignmentNode::AssignmentNode(const std::string& id, SyntaxTreeNode* val) {

    _identifier = id;
    _val = val;
}

/* konstruktor kopije */
AssignmentNode::AssignmentNode(const AssignmentNode& a) {
    
    _identifier = a._identifier;
    _val = a._val->Clone();
}

/* destruktor */
AssignmentNode::~AssignmentNode() {

    /* unistavamo dinamicke resurse */
    delete _val;
}

/* metod koji izvrsava dati tip naredbe */
double AssignmentNode::Interpret(SymbolTable& st) const {
    
    /* pamtimo/menjamo vrednost promenljive u tablici simbola */
    st.SetSymbolValue(_identifier, _val->Interpret(st));

    /* kao rezultat vracamo novu vrednost promenljive */
    return st.GetSymbolValue(_identifier);
}

/* metod kompajlira dati tip naredbe */
void AssignmentNode::Compile(SymbolTable& st) const {

    /* kompajliramo naredbu */
    _val->Compile(st);
    /* pamtimo medjurezultat */
    std::cout << "push tmp1" << std::endl;

    /* ako menjamo vrednost postojece promenljive */
    if (st.SymbolDefined(_identifier)) {
        /* generisemo odgovarajucu komandu */
        std::cout << "mov " << _identifier << ", tmp1";
    }
    else {
        /* inace, generisemo komandu kojom definisemo promenljivu */
        std::cout << "def " << _identifier << ", tmp1";
    }
     
    std::cout << std::endl;
}

/* metod kreira kopiju postojeceg objekta */
SyntaxTreeNode* AssignmentNode::Clone() const {

    /* kopiramo objekat pozivom konstruktora kopije */
    return new AssignmentNode(*this);
}

/* apstraktni metod kreira string reprezentaciju cvora */
void AssignmentNode::Print(std::ostream& s) const {

    /* stampamo sadrzaj cvora */
    s << _identifier << " = ";
    _val->Print(s);
    s << std::endl;
}

/********************************* Print Node **************************************/

/* konstruktor - plitko kopiranje atributa */
PrintNode::PrintNode( SyntaxTreeNode* val) {
    _statement = val;
}

/* konstruktor kopije */
PrintNode::PrintNode(const PrintNode& a) {
    _statement = a._statement->Clone();
}

/* destruktor */
PrintNode::~PrintNode() {

    /* unistavamo dinamicke resurse */
    delete _statement;
}

/* metod koji izvrsava dati tip naredbe */
double PrintNode::Interpret(SymbolTable& st) const {
    
    /* izvrsavamo naredbu koja je argument cvora */
    double val = _statement->Interpret(st);
    
    /* prikazujemo rezultat na standardnom izlazu */
    std::cout << val << std::endl;

    /* kao rezultat vracamo rezultat naredbe */
    return val;
}

/* metod kompajlira dati tip naredbe */
void PrintNode::Compile(SymbolTable& st) const {

    /* generisemo zamisljeni medjukod */
    std::cout << "print_stm ";
    _statement->Compile(st);
    std::cout << std::endl;
}

/* metod kreira kopiju postojeceg objekta */
SyntaxTreeNode* PrintNode::Clone() const {

    /* kopiramo objekat pozivom konstruktora kopije */
    return new PrintNode(*this);
}

/* apstraktni metod kreira string reprezentaciju cvora */
void PrintNode::Print(std::ostream& s) const {

    /* stampamo sadrzaj cvora */
    s << "print ( ";
    _statement->Print(s);
    s << " )" << std::endl;
}

/********************************* Constant Node **************************************/

/* konstruktor */
ConstantNode::ConstantNode( double val) {
    _val = val;
}

/* konstruktor kopije */
ConstantNode::ConstantNode(const ConstantNode& a) {
    _val = a._val;
}

/* metod koji izvrsava dati tip naredbe */
double ConstantNode::Interpret(SymbolTable& st) const {

    /* rezultat naredbe je vrednost konstante */
    return _val;
}

/* metod kompajlira dati tip naredbe */
void ConstantNode::Compile(SymbolTable& st) const {

    /* generisemo zamisljeni medjukod */
    std::cout << "push " << _val << std::endl;
}

/* metod kreira kopiju postojeceg objekta */
SyntaxTreeNode* ConstantNode::Clone() const {

    /* kopiramo objekat pozivom konstruktora kopije */
    return new ConstantNode(*this);
}

/* apstraktni metod kreira string reprezentaciju cvora */
void ConstantNode::Print(std::ostream& s) const {   

    /* stampamo sadrzaj cvora */
    s << _val;
}

/********************************* Identifier Node **************************************/

/* konstruktor */
IdentifierNode::IdentifierNode(const std::string& name) {
    _name = name;
}

/* konstruktor kopije */
IdentifierNode::IdentifierNode(const IdentifierNode& a) {
    _name = a._name;
}

/* metod koji izvrsava dati tip naredbe */
double IdentifierNode::Interpret(SymbolTable& st) const {

    /* rezultat naredbe je vrednost promenljive iz tablice simbola */
    return st.GetSymbolValue(_name);
}

/* metod kompajlira dati tip naredbe */
void IdentifierNode::Compile(SymbolTable& st) const {

    /* generisemo zamisljeni medjukod */
    std::cout << "push " << _name << std::endl;
}

/* metod kreira kopiju postojeceg objekta */
SyntaxTreeNode* IdentifierNode::Clone() const {

    /* kopiramo objekat pozivom konstruktora kopije */
    return new IdentifierNode(*this);
}

/* apstraktni metod kreira string reprezentaciju cvora */
void IdentifierNode::Print(std::ostream& s) const {

    /* stampamo sadrzaj cvora */
    s << _name;
}

/********************************* Operator Node **************************************/

/* konstruktor - plitko kopiranje atributa */
BinaryOperatorNode::BinaryOperatorNode(const std::string symbol, SyntaxTreeNode* op1, SyntaxTreeNode* op2) {
    _symbol = symbol;
    _left = op1;
    _right = op2;
}

/* destruktor */
BinaryOperatorNode::~BinaryOperatorNode() {

    /* unistavamo dinamicke resurse */
    delete _left;
    delete _right;
}

/* apstraktni metod kreira string reprezentaciju cvora */
void BinaryOperatorNode::Print(std::ostream& s) const {

    /* stampamo sadrzaj cvora */
    s << _symbol << " (";
    _left->Print(s);
    s << ", ";
    _right->Print(s);
    s << ")";
}

/********************************* Plus Node **************************************/

/* konstruktor - plitko kopiranje atributa */
PlusNode::PlusNode(const std::string symbol, SyntaxTreeNode* op1, SyntaxTreeNode* op2)
    /* pozivamo konstruktor nadklase */
    : BinaryOperatorNode(symbol, op1, op2) {

    }

/* konstruktor kopije */
PlusNode::PlusNode(const PlusNode& op) 
    /* pozivamo konstruktor nadklase sa dubokim kopijama argumenata */
    : BinaryOperatorNode(op._symbol, op._left->Clone(), op._right->Clone()){
    
    
}

/* metod koji izvrsava dati tip naredbe */
double PlusNode::Interpret(SymbolTable& st) const {

    /* rezultat je zbir vrednosti levog i desnog operanda */
    return _left->Interpret(st) + _right->Interpret(st);;
}

/* metod kompajlira dati tip naredbe */
void PlusNode::Compile(SymbolTable& st) const {

    /* prvo kompajliramo levi operand i cuvamo medjurezultat */
    _left->Compile(st);
    std::cout << "push tmp1" << std::endl;
    std::cout << std::endl;

    /* zatim kompajliramo densi operand i cuvamo medjurezultat */
    _right->Compile(st);
    std::cout << "push tmp2" << std::endl;
    std::cout << std::endl;

    /* generisemo komandu koja sabira medjurezultate */
    std::cout << "add tmp1 tmp2"<< std::endl;
    std::cout << std::endl;
}

/* metod kreira kopiju postojeceg objekta */
SyntaxTreeNode* PlusNode::Clone() const {

    /* kopiramo objekat pozivom konstruktora kopije */
    return new PlusNode(*this);
}


/********************************* Minus Node **************************************/

/* konstruktor - plitko kopiranje atributa */
MinusNode::MinusNode(const std::string symbol, SyntaxTreeNode* op1, SyntaxTreeNode* op2)
    /* pozivamo konstruktor nadklase */
    : BinaryOperatorNode(symbol, op1, op2) {

    }

/* konstruktor kopije */
MinusNode::MinusNode(const MinusNode& op)
    /* pozivamo konstruktor nadklase sa dubokim kopijama argumenata */
     : BinaryOperatorNode(op._symbol, op._left->Clone(), op._right->Clone()) {
    
}

/* metod koji izvrsava dati tip naredbe */
double MinusNode::Interpret(SymbolTable& st) const {

    /* rezultat je razlika vrednosti levog i desnog operanda */
    return _left->Interpret(st) - _right->Interpret(st);
}

/* metod kompajlira dati tip naredbe */
void MinusNode::Compile(SymbolTable& st) const {

    /* prvo kompajliramo levi operand i cuvamo medjurezultat */
    _left->Compile(st);
    std::cout << "push tmp1" << std::endl;
    std::cout << std::endl;

    /* zatim kompajliramo densi operand i cuvamo medjurezultat */
    _right->Compile(st);
    std::cout << "push tmp2" << std::endl;
    std::cout << std::endl;

    /* generisemo komandu koja oduzima medjurezultate */
    std::cout << "sub tmp1 tmp2"<< std::endl;
    std::cout << std::endl;
}

/* metod kreira kopiju postojeceg objekta */
SyntaxTreeNode* MinusNode::Clone() const {

    /* kopiramo objekat pozivom konstruktora kopije */
    return new MinusNode(*this);
}

/********************************* Times Node **************************************/

/* konstruktor - plitko kopiranje atributa */
TimesNode::TimesNode(const std::string symbol, SyntaxTreeNode* op1, SyntaxTreeNode* op2)
    /* pozivamo konstruktor nadklase */
    : BinaryOperatorNode(symbol, op1, op2) {

    }

/* konstruktor kopije */
TimesNode::TimesNode(const TimesNode& op)
    /* pozivamo konstruktor nadklase sa dubokim kopijama argumenata */
     : BinaryOperatorNode(op._symbol, op._left->Clone(), op._right->Clone()){

}

/* metod koji izvrsava dati tip naredbe */
double TimesNode::Interpret(SymbolTable& st) const {

    /* rezultat je proizvod vrednosti levog i desnog operanda */
    return _left->Interpret(st) * _right->Interpret(st);
}

/* metod kompajlira dati tip naredbe */
void TimesNode::Compile(SymbolTable& st) const {

    /* prvo kompajliramo levi operand i cuvamo medjurezultat */
    _left->Compile(st);
    std::cout << "push tmp1" << std::endl;
    std::cout << std::endl;

    /* zatim kompajliramo densi operand i cuvamo medjurezultat */
    _right->Compile(st);
    std::cout << "push tmp2" << std::endl;
    std::cout << std::endl;

    /* generisemo komandu koja mnozi medjurezultate */
    std::cout << "mul tmp1 tmp2"<< std::endl;
    std::cout << std::endl;
}

/* metod kreira kopiju postojeceg objekta */
SyntaxTreeNode* TimesNode::Clone() const {

    /* kopiramo objekat pozivom konstruktora kopije */
    return new TimesNode(*this);
};


/********************************* Division Node **************************************/

/* konstruktor - plitko kopiranje atributa */
DivisionNode::DivisionNode(const std::string symbol, SyntaxTreeNode* op1, SyntaxTreeNode* op2)
    /* pozivamo konstruktor nadklase */
    : BinaryOperatorNode(symbol, op1, op2) {

    }

/* konstruktor kopije */
DivisionNode::DivisionNode(const DivisionNode& op) 
    /* pozivamo konstruktor nadklase sa dubokim kopijama argumenata */
     : BinaryOperatorNode(op._symbol, op._left->Clone(), op._right->Clone()){
    

}

/* metod koji izvrsava dati tip naredbe */
double DivisionNode::Interpret(SymbolTable& st) const {
    
    /* rezultat je kolicnik vrednosti levog i desnog operanda */
    return _left->Interpret(st) / _right->Interpret(st);
}

/* metod kompajlira dati tip naredbe */
void DivisionNode::Compile(SymbolTable& st) const {

    /* prvo kompajliramo levi operand i cuvamo medjurezultat */
    _left->Compile(st);
    std::cout << "push tmp1" << std::endl;
    std::cout << std::endl;

    /* zatim kompajliramo densi operand i cuvamo medjurezultat */
    _right->Compile(st);
    std::cout << "push tmp2" << std::endl;
    std::cout << std::endl;

    /* generisemo komandu koja deli medjurezultate */
    std::cout << "div tmp1 tmp2"<< std::endl;
    std::cout << std::endl;
}

/* metod kreira kopiju postojeceg objekta */
SyntaxTreeNode* DivisionNode::Clone() const {

    /* kopiramo objekat pozivom konstruktora kopije */
    return new DivisionNode(*this);
}

/********************************* Unary Operator Node **************************************/

/* konstruktor - plitko kopiranje atributa */
UnaryOperatorNode::UnaryOperatorNode(const std::string symbol, SyntaxTreeNode* op1) {
    _symbol = symbol;
    _exp = op1;
}

/* destruktor */
UnaryOperatorNode::~UnaryOperatorNode() {

    /* unistavamo dinamicke resurse */
    delete _exp;
}

/* apstraktni metod kreira string reprezentaciju cvora */
void UnaryOperatorNode::Print(std::ostream& s) const {

    /* stampamo sadrzaj cvora */
    s << _symbol << " (";
    _exp->Print(s);
    s << ")";
}


/********************************* UMinus Node **************************************/

/* konstruktor - plitko kopiranje atributa */
UMinusNode::UMinusNode(const std::string symbol, SyntaxTreeNode* op)
    /* pozivamo konstruktor nadklase */
    : UnaryOperatorNode(symbol, op) {

    }

/* konstruktor kopije */
UMinusNode::UMinusNode(const UMinusNode& op)
    /* pozivamo konstruktor nadklase sa dubokim kopijama argumenata */
    : UnaryOperatorNode(op._symbol, op._exp->Clone()){

}

/* metod koji izvrsava dati tip naredbe */
double UMinusNode::Interpret(SymbolTable& st) const {
    
    /* rezultat je suprotna vrednost operanda */
    return -_exp->Interpret(st);
}

/* metod kompajlira dati tip naredbe */
void UMinusNode::Compile(SymbolTable& st) const {
    
    /* prvo kompajliramo operand i cuvamo medjurezultat */
    _exp->Compile(st);
    std::cout << "push tmp1" << std::endl;
    std::cout << std::endl;

    /* zatim generisemo komandu kojom se odredjuje suprotni broj */
    std::cout << "sub 0 tmp1"<< std::endl;
    std::cout << std::endl;
}

/* metod kreira kopiju postojeceg objekta */
SyntaxTreeNode* UMinusNode::Clone() const {

    /* kopiramo objekat pozivom konstruktora kopije */
    return new UMinusNode(*this);
}


/********************************* Logical Node **************************************/

/* konstruktor - plitko kopiranje atributa */
LogicalNode::LogicalNode(const std::string symbol, SyntaxTreeNode* op1, SyntaxTreeNode* op2)
    /* pozivamo konstruktor nadklase */
    : BinaryOperatorNode(symbol, op1, op2) {

    }

/* konstruktor kopije */
LogicalNode::LogicalNode(const LogicalNode& op) 
    /* pozivamo konstruktor nadklase sa dubokim kopijama argumenata */
    : BinaryOperatorNode(op._symbol, op._left->Clone(), op._right->Clone()){

}

/* metod koji izvrsava dati tip naredbe */
double LogicalNode::Interpret(SymbolTable& st) const {

    /* rezultat naredbe je rezultat uporedjivanja  */
    bool result = true;
    
    /* u zavisnosti od operatora vrsimo odgovarajuce poredjenje */
    if (_symbol == "==") {
        result = _left->Interpret(st) == _right->Interpret(st);
    }
    else if (_symbol == "!=") {
        result = _left->Interpret(st) != _right->Interpret(st);
    }
    else if (_symbol == "<=") {
        result = _left->Interpret(st) <= _right->Interpret(st);
    }

    else if (_symbol == ">=") {
        result = _left->Interpret(st) >= _right->Interpret(st);
    }

    else if (_symbol == "<") {
        result = _left->Interpret(st) < _right->Interpret(st);
    }

    else if (_symbol == ">") {
        result = _left->Interpret(st) > _right->Interpret(st);
    }

    /* rezultat je numericka reprezentacija logicke vrednosti */
    return result == true ? 1 : 0;
}

/* metod kompajlira dati tip naredbe */
void LogicalNode::Compile(SymbolTable& st) const {

    /* prvo kompajliramo levi operand i cuvamo medjurezultat */
    _left->Compile(st);
    std::cout << "push tmp1" << std::endl;
    std::cout << std::endl;

    /* zatim kompajliramo densi operand i cuvamo medjurezultat */
    _right->Compile(st);
    std::cout << "push tmp2" << std::endl;
    std::cout << std::endl;

    /* generisemo komandu koja uporedjuje medjurezultate 
     * u zavisnosti od simbola 
     */
    if (_symbol == "==") {
        std::cout << "eq tmp1 tmp2"<< std::endl;
    }
    else if (_symbol == "!=") {
        std::cout << "neq tmp1 tmp2"<< std::endl;
    }
    else if (_symbol == "<=") {
        std::cout << "leq tmp1 tmp2"<< std::endl; 
    }

    else if (_symbol == ">=") {
        std::cout << "geq tmp1 tmp2"<< std::endl;
    }

    else if (_symbol == "<") {
        std::cout << "le tmp1 tmp2"<< std::endl;
    }

    else if (_symbol == ">") {
        std::cout << "ge tmp1 tmp2"<< std::endl;
    }

    std::cout << std::endl;
}

/* metod kreira kopiju postojeceg objekta */
SyntaxTreeNode* LogicalNode::Clone() const {

    /* kopiramo objekat pozivom konstruktora kopije */
    return new LogicalNode(*this);
}
