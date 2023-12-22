/* Potrebno je napisati program za rad sa izrazima u analitickom obliku. 
 * Treba da napisemo hijerarhiju klasa za rad sa analitickim izrazima. U izrazima
 * se mogu pojavljivati:
 * 1. Konstante - predstavljacemo ih tipom double
 * 2. Promenljive - svaka promenljiva je definisana svojim imenom. u izrazima se moze
 *                  pojavljivati proizvoljan broj promenljivih. 
 * 3. Uobicajene unarne i binarne operacije, kao i funkcije
 *      3.1 Promena znaka (unarni minus)
 *      3.2 Sabiranje, oduzimanje, mnozenje i deljenje
 *      3.3 Funkcije sin, cos, tan, cot, ln, exp, sqrt
 * 4. Radi jednostavnosti, umesto operatora, u internoj reprezentaciji izraza mogu se
 *    koristiti odgovarajuce funkcije. Ako je dat izraz (x-a2)*(y+7.23), mozemo ga zapisati kao
 *    (PUTA (MINUS x a2) (PLUS y 7.23))
 * 
 * Potrebno je obezbediti sledece operacije nad izrazima:
 * 
 * 1. Izracunavanje vrednosti izraza za date vrednosti promenljivih
 * 2. Uproscavanje izraza zamenjivanjem odredjenog skupa promenljivih datim vrednostima
 * 3. Osnovne aritmeticke operacije nad izrazima
 * 4. Izracunavanje izvoda izraza po datoj promenljivoj.
 * 
 * Radi jednostavnosti program prvo ucitava izraz, a zatim skup vrednosti promenljivih.
 * Program treba da izracuna vrednost izraza i da na izlaz ispise izraz uproscen po promenljivoj x.
 */
#include <iostream>
#include <map>
#include <exception>
#include <cmath>

/* Da bismo pravilno resili zadatak moramo da sagledamo celine koje postoje u zadatku: 
 * 1. Program podrzava rad sa promenljivama, sto znaci da negde treba da cuvamo promenljive i njihove vrednosti
 *    Dakle, treba da napravimo posebnu klasu koja ce predstavljati skup promenljivih i njima pridruzenih vrednosti.
 * 2. Program treba da omoguciti rad sa izrazima. Potrebno je da sagledamo sta sve moze biti izraz. Potrebno je da
 *    precizno definisemo sta moze biti izraz:
 *      2.1. Konstanta moze biti izraz.
 *      2.2. Promenljiva moze biti izraz.
 *      2.3. Izraz moze biti kombinacija vrednosti iz 2.1 i 2.2 povezanih odgovarajucim operatorom (sabiranje, oduzimanje...)
 *      2.4. Izraz moze biti neka unarna transformacija postojecih izraza (promena znaka, primena funkcije itd)
 *      2.5. Izraz moze biti kombinacija izraza 2.1-2.4
 *      2.6. Vrednost izraza definisana je vrednostima promenljivih koje u njemu ucestuvuju.
 *
 * Iz ove male analize mozemo da zakljucimo da nam treba klasa Okolina koja ce cuvati promenljive i njihove vrednosti
 * i u kojoj ce Izraz moci da odredi svoju vrednosti.
 * Treba nam hijerarhija klasa Izraz kojom cemo definisati i omoguciti izracunavanje izraza. 
 * Hijerarhija moze biti sledeca:
 * 
 * Izraz (Apstraktna) ----> Konstanta
 *                 |
 *                 -------> Promenljiva
 *                 |
 *                 -------> BinarniOperator (Apstraktna) ----> Zbir
 *                 |                                     |
 *                 |                                     ----> Razlika
 *                 |                                     |
 *                 |                                     ----> Proizvod
 *                 |                                     |
 *                 |                                     ----> Kolicnik
 *                 |
 *                 -------> Funkcija (Apstraktna) ----> Suprotni (Unarni minus)
 *                                                |
 *                                                ----> Sin
 *                                                |
 *                                                ----> Cos
 *                                                |
 *                                                ----> Tan
 *                                                |
 *                                                ----> Cot
 *                                                |
 *                                                ----> Log
 *                                                |
 *                                                ----> Exp
 *                                                |
 *                                                ----> Sqrt
 *                              
 */

/* pomocna klasa u kojoj cuvamo promenljive i njihove vrednosti */
class Okolina {

private:
    /* mapa u kojoj cuvamo imena promenljivih sa pridruzenim vrednostima */
    std::map<std::string, double> _promenljive;

public:
    /* podrazumevani konstruktor */
    Okolina() {

    }

    /* metod dodaje promenljivu u okolinu */
    bool DodajPromenljivu(const std::string& s, double v) {

        if (PromenljivaDefinisana(s))
            return false;
        
        _promenljive[s] = v;
        return true;
    }

    /* metod proverava da li je promenljiva definisana */
    bool PromenljivaDefinisana(const std::string& s) const {
        
        auto it = _promenljive.find(s);

        return it != _promenljive.end();
    }

    /* metod vraca vrednost promenljive */
    double VrednostPromenljive(const std::string& s) const {

        /* ako promenljiva nije definisana, baca se izuzetak */
        if (!PromenljivaDefinisana(s))
            throw std::invalid_argument("promenljiva nije definisana");
        
        /* inace se vraca vrednost promenljive */
        auto it = _promenljive.find(s);
        return it->second;
    }

    /* metod menja  vrednost promenljive */
    void IzmeniVrednostPromenljive(const std::string& s, double v) {

        /* ako promenljiva nije definisana, baca se izuzetak */
        if (!PromenljivaDefinisana(s))
            throw std::invalid_argument("promenljiva nije definisana");
        
        /* menjamo vrednost promenljive */
        _promenljive[s] = v;
    }

    /* operator indeksiranja */
    double& operator [](std::string& s) {

        if (!PromenljivaDefinisana(s))
            throw std::invalid_argument("promenljiva nije definisana");
        
        auto it = _promenljive.find(s);
        return it->second;
    }

    /* const operator indeksiranja */
    double operator [](std::string& s) const{

        if (!PromenljivaDefinisana(s))
            throw std::invalid_argument("promenljiva nije definisana");
        
        auto it = _promenljive.find(s);
        return it->second;
    }
};

/* definisemo hijerarhiju klasa Izraz */
class Izraz {
/* klasa definise samo interfejs */
public:
    /* imamo hijerarhiju klasa, pa moramo da uvezemo destruktore */
    virtual ~Izraz() {

    }

    /* metod koji odredjuje vrednost izraza */
    virtual double Vrednost(const Okolina& a) const = 0;

    /* metod koji stampa izraz na ostream */
    virtual void Ispisi(std::ostream& s) const = 0;

    /* metod kreira kopiju postojeceg objekta */
    virtual Izraz* Kopija() const = 0;

    virtual Izraz* Uprosti(const Okolina& o, const std::string& s) const = 0;

    virtual Izraz* Izvod(const Okolina& o, const std::string& s) const = 0;
};

/* preopterecivanje operatora ispisa */
std::ostream& operator <<(std::ostream& s, const Izraz& i) {
    
    i.Ispisi(s);
    return s;
}

/* definisemo izvedenu klasu konstanta */
class Konstanta : public Izraz {

private: 
    /* konstanta je opisana svojom vrednoscu */
    double _vrednost;

public:
    Konstanta(double v) {
        _vrednost = v;
    }

    Konstanta(const Konstanta& k) {
        
        _vrednost = k._vrednost;
    }

    /* predefinisemo apstraktne metode */
    double Vrednost(const Okolina& o) const {
        return _vrednost;
    }

    void Ispisi(std::ostream& s) const {
        s << _vrednost;
    }

    Izraz* Kopija() const {

        return new Konstanta(*this);
    }

    virtual Izraz* Uprosti(const Okolina& o, const std::string& s) const {

        return new Konstanta(*this);
    }

    virtual Izraz* Izvod(const Okolina& o, const std::string& s) const {

        return new Konstanta(0);
    }
};

/* definisemo izvedenu klasu promenljiva */
class Promenljiva : public Izraz {

private:
    /* promenljiva je opisana svojim nazivom */
    std::string _ime;

public:
    Promenljiva(const std::string& s) {
        _ime = s;
    }

    Promenljiva(const Promenljiva& p) {

        _ime = p._ime;
    }

    /* predefinisemo apstraktne metode */
    double Vrednost(const Okolina& o) const {
        try {

            double vred = o.VrednostPromenljive(_ime);
            return vred;
        }
        catch (std::invalid_argument& s) {
            throw;
        }
    }

    void Ispisi(std::ostream& s) const {
        s << _ime;
    }

    Izraz* Kopija() const {

        return new Promenljiva(*this);
    }

    virtual Izraz* Uprosti(const Okolina& o, const std::string& s) const {

        if (s == _ime) {
            return new Konstanta(o.VrednostPromenljive(s));
        }
        else 
            return new Promenljiva(*this);
    }

    virtual Izraz* Izvod(const Okolina& o, const std::string& s) const {

        if (s == _ime)
            return new Konstanta(1);
        else 
            return new Konstanta(0);
    }
};

/* definisemo izvedenu klasu binarni operator 
 * iz koje cemo kasnije izvesti klase zbir, razlika, proizvod itd
 */
class BinarniOperator : public Izraz {

protected:
    /* binarni je opisan svojim levim i desnim operandom 
     * koji mogu biti bilo kakvi izrazi
     */
    Izraz *levi, *desni;
    /* Da bismo mogli da koristimo dinamicki polimorfizam, izraze 
     * moramo da cuvamo kao pokazivace. Nivo zastite mora biti protected, 
     * da bi izrazi bili vidljivi u izvedenim klasama
     */
public:
    /* konstruktor */
    BinarniOperator(Izraz* l, Izraz* d) : levi(l), desni(d) {
        
    }
    /* izvodicemo nove klase, moramo da ulancamo destruktore */
    virtual ~BinarniOperator() {
        delete levi;
        delete desni;
    }

    /* konstruktor kopije */
    BinarniOperator(const BinarniOperator& b) {

        levi = b.levi->Kopija();
        desni = b.desni->Kopija();
    }

    /* bazna klasa nema sopstvenih atributa niti ce izvedene klase imati sopstvenih atributa, 
     * pa mozemo da implementiramo operator dodele
     */
    BinarniOperator& operator =(const BinarniOperator& z) {

        /* self-assignement check*/
        if (this == &z) {
            return *this;
        }

        /* unistavamo stare izraze */
        delete levi;
        delete desni;

        /* postavljamo njihove nove vrednosti */
        levi = z.levi->Kopija();
        desni = z.desni->Kopija();

        /* vracamo izmenjeni objekat */
        return *this;
    }

    /* u ovom trenutku i dalje ne znamo o kom operatoru se radi
     * pa metode ostaju apstraktne
     */
    virtual double Vrednost(const Okolina& o) const = 0;
    virtual void Ispisi(std::ostream& s) const = 0;
    virtual Izraz* Kopija() const = 0;
    virtual Izraz* Uprosti(const Okolina& o, const std::string& s) const = 0;
    virtual Izraz* Izvod(const Okolina& o, const std::string& s) const = 0;
};

/* definisemo izvedenu klasu Zbir */
class Zbir : public BinarniOperator {

public: 

    /* konstruktor - pozivamo konstruktor bazne klase */
    Zbir(Izraz* l, Izraz* d) : BinarniOperator(l, d) {

    }

    /* konstruktor kopije - zovemo konstruktor kopije bazne klase */
    Zbir(const Zbir& z) : BinarniOperator(z){

    }
  

    /* implementiramo apstraktne metode */
    double Vrednost(const Okolina& o) const {
        return levi->Vrednost(o) + desni->Vrednost(o);
    }

    void Ispisi(std::ostream& s) const {
        s << "( PLUS " << (*levi) << " " << (*desni) << ") ";
    }

    Izraz* Kopija() const {

        return new Zbir(*this);
    }

    Izraz* Uprosti(const Okolina& o, const std::string& s) const {

        Izraz* l = levi->Uprosti(o, s);
        Izraz* d = desni->Uprosti(o, s);

        if (dynamic_cast<Konstanta*>(l) != nullptr && 
                dynamic_cast<Konstanta*>(d) != nullptr) {
            Izraz* rez = new Konstanta(l->Vrednost(o) + d->Vrednost(o));
            delete l; 
            delete d;
            return rez;
        }
        else 
            return new Zbir(l,d);
    }

    Izraz* Izvod(const Okolina& o, const std::string& s) const {

        Izraz* l = levi->Izvod(o, s);
        Izraz* d = desni->Izvod(o, s);

        if (dynamic_cast<Konstanta*>(l) != nullptr && 
                dynamic_cast<Konstanta*>(d) != nullptr) {
            Izraz* rez = new Konstanta(l->Vrednost(o) + d->Vrednost(o));
            delete l; 
            delete d;
            return rez;
        }
        else 
            return new Zbir(l,d);
    }
};

/* definisemo izvedenu klasu Razlika */
class Razlika : public BinarniOperator {

public: 

    /* konstruktor - pozivamo konstruktor bazne klase */
    Razlika(Izraz* l, Izraz* d) : BinarniOperator(l, d) {

    }

    /* konstruktor kopije - zovemo konstruktor kopije bazne klase */
    Razlika(const Razlika& z) : BinarniOperator(z){

    }
  

    /* implementiramo apstraktne metode */
    double Vrednost(const Okolina& o) const {
        return levi->Vrednost(o) - desni->Vrednost(o);
    }

    void Ispisi(std::ostream& s) const {
        s << "( MINUS " << (*levi) << " " << (*desni) << ") ";
    }

    Izraz* Kopija() const  {

        return new Razlika(*this);
    }

    Izraz* Uprosti(const Okolina& o, const std::string& s) const {

        Izraz* l = levi->Uprosti(o, s);
        Izraz* d = desni->Uprosti(o, s);

        if (dynamic_cast<Konstanta*>(l) != nullptr && 
                dynamic_cast<Konstanta*>(d) != nullptr) {
            Izraz* rez = new Konstanta(l->Vrednost(o) - d->Vrednost(o));
            delete l; 
            delete d;
            return rez;
        }
        else 
            return new Razlika(l,d);
    }
    Izraz* Izvod(const Okolina& o, const std::string& s) const {

        Izraz* l = levi->Uprosti(o, s);
        Izraz* d = desni->Uprosti(o, s);

        if (dynamic_cast<Konstanta*>(l) != nullptr && 
                dynamic_cast<Konstanta*>(d) != nullptr) {
            Izraz* rez = new Konstanta(l->Vrednost(o) - d->Vrednost(o));
            delete l; 
            delete d;
            return rez;
        }
        else 
            return new Razlika(l,d);
    }
};

/* definisemo izvedenu klasu Proizvod */
class Proizvod : public BinarniOperator {

public: 

    /* konstruktor - pozivamo konstruktor bazne klase */
    Proizvod(Izraz* l, Izraz* d) : BinarniOperator(l, d) {

    }

    /* konstruktor kopije - zovemo konstruktor kopije bazne klase */
    Proizvod(const Razlika& z) : BinarniOperator(z){

    }
  

    /* implementiramo apstraktne metode */
    double Vrednost(const Okolina& o) const {
        return levi->Vrednost(o) * desni->Vrednost(o);
    }

    void Ispisi(std::ostream& s) const {
        s << "( PUTA " << (*levi) << " " << (*desni) << ") ";
    }

    Izraz* Kopija() const  {

        return new Proizvod(*this);
    }

    Izraz* Uprosti(const Okolina& o, const std::string& s) const  {
        Izraz* l = levi->Uprosti(o, s);
        Izraz* d = desni->Uprosti(o, s);

        if (dynamic_cast<Konstanta*>(l) != nullptr && 
                dynamic_cast<Konstanta*>(d) != nullptr) {
            Izraz* rez = new Konstanta(l->Vrednost(o) * d->Vrednost(o));
            delete l; 
            delete d;
            return rez;
        }
        else 
            return new Proizvod(l,d);
    }

    Izraz* Izvod(const Okolina& o, const std::string& s) const {

        Izraz *il = levi->Izvod(o, s);
        Izraz *id = desni->Izvod(o, s);

        Izraz* ll = new Proizvod(il, desni->Kopija());
        Izraz* dd = new Proizvod(levi->Kopija(), id);

        return new Zbir(ll, dd);
    }
};

/* definisemo izvedenu klasu Kolicnik */
class Kolicnik : public BinarniOperator {

public: 

    /* konstruktor - pozivamo konstruktor bazne klase */
    Kolicnik(Izraz* l, Izraz* d) : BinarniOperator(l, d) {

    }

    /* konstruktor kopije - zovemo konstruktor kopije bazne klase */
    Kolicnik(const Razlika& z) : BinarniOperator(z){

    }
  

    /* implementiramo apstraktne metode */
    double Vrednost(const Okolina& o) const {
        if (desni->Vrednost(o) != 0)
            return levi->Vrednost(o) / desni->Vrednost(o);
        else 
            throw std::invalid_argument("Deljenje nulom");
    }

    void Ispisi(std::ostream& s) const {
        s << "( PUTA " << (*levi) << " " << (*desni) << ") ";
    }

    Izraz* Kopija() const  {

        return new Kolicnik(*this);
    }

    Izraz* Uprosti(const Okolina& o, const std::string& s) const  {
        Izraz* l = levi->Uprosti(o, s);
        Izraz* d = desni->Uprosti(o, s);

        if (dynamic_cast<Konstanta*>(l) != nullptr && 
                dynamic_cast<Konstanta*>(d) != nullptr) {
            Izraz* rez = new Konstanta(l->Vrednost(o) / d->Vrednost(o));
            delete l; 
            delete d;
            return rez;
        }
        else 
            return new Kolicnik(l,d);
    }

    Izraz* Izvod(const Okolina& o, const std::string& s) const {

        Izraz *il = levi->Izvod(o, s);
        Izraz *id = desni->Izvod(o, s);

        Izraz* ll = new Proizvod(il, desni->Kopija());
        Izraz* dd = new Proizvod(levi->Kopija(), id);

        Izraz* gore = new Razlika(ll, dd);
        Izraz* dole = new Proizvod(desni->Kopija(), desni->Kopija());

        return new Kolicnik(gore, dole);
    }
};

/* izvodimo klasu za reprezentaciju funkcija, jer funkcije mozemo na neki nacin 
 * posmatrati kao unarne operatore. Primenjujemo slicno razmisljanje kao 
 * za Binarne operatore. 
 */
class Funkcija : public Izraz {

protected:
    /* argument funkcije je jedan izraz, tj. onaj na koji treba primeniti funkciju */
    Izraz* izraz;
public:
    /* konstruktor */
    Funkcija(Izraz* i) : izraz(i) {

    }
    /* konstruktor kopije */
    Funkcija(const Funkcija& f) {

        izraz = f.izraz->Kopija();
    }
    /* virtuelni destruktor, jer se radi o hijerarhiji klasa */
    virtual ~Funkcija() {
        delete izraz;
    }

    /* operator dodele mozemo da implementiramo, jer ni bazna, a ni izvedene klase nemaju atributa */
    Funkcija& operator =(const Funkcija& f) {

        /* self assignment check */
        if (this == &f) {
            return *this;
        }

        /* unistavamo stari izraz */
        delete izraz;
        /* kopiramo izraz iz argumenta */
        izraz = f.izraz->Kopija();
        /* vracamo izmenjeni objekat */
        return *this;
    }

    /* apstraktne metode */

    /* metod koji odredjuje vrednost izraza */
    virtual double Vrednost(const Okolina& a) const = 0;

    /* metod koji stampa izraz na ostream */
    virtual void Ispisi(std::ostream& s) const = 0;

    /* metod kreira kopiju postojeceg objekta */
    virtual Izraz* Kopija() const = 0;

    /* metod koji uproscava izraz */
    virtual Izraz* Uprosti(const Okolina& o, const std::string& s) const = 0;

    /* metod koji racuna izvod izraza */
    virtual Izraz* Izvod(const Okolina& o, const std::string& s) const = 0;
};

/* implementiramo unarni minus */
class Suprotni : public Funkcija {

public:
    /* konstruktor */
    Suprotni(Izraz* i) : Funkcija(i) {

    }
    Suprotni(const Suprotni& s) : Funkcija(s) {

    }

    /* metod koji odredjuje vrednost izraza */
    double Vrednost(const Okolina& a) const {

        return -izraz->Vrednost(a);
    }

    /* metod koji stampa izraz na ostream */
    void Ispisi(std::ostream& s) const {
        s << "SUPROTNI ( " << (*izraz) << ") "; 
    }

    /* metod kreira kopiju postojeceg objekta */
    Izraz* Kopija() const {
        
        return new Suprotni(*this);
    }

    Izraz* Uprosti(const Okolina& o, const std::string& s) const {

        Izraz* l = izraz->Uprosti(o, s);

        if (dynamic_cast<Konstanta*>(l) != nullptr) {
            Izraz* rez = new Konstanta(-l->Vrednost(o));
            delete l;
            return rez;
        }
        else 
            return new Suprotni(l);
    }

    Izraz* Izvod(const Okolina& o, const std::string& s) const {

        Izraz* l = izraz->Izvod(o, s);
        if (dynamic_cast<Konstanta*>(l) != nullptr) {
            Izraz* rez = new Konstanta(-l->Vrednost(o));
            delete l;
            return rez;
        }
        else 
            return new Suprotni(l);
    }
};

class Sin : public Funkcija {

public:
    /* konstruktor */
    Sin(Izraz* i) : Funkcija(i) {

    }
    Sin(const Sin& s) : Funkcija(s) {

    }

    /* metod koji odredjuje vrednost izraza */
    double Vrednost(const Okolina& a) const {

        return sin(-izraz->Vrednost(a));
    }

    /* metod koji stampa izraz na ostream */
    void Ispisi(std::ostream& s) const {
        s << "SIN ( " << (*izraz) << ") "; 
    }

    /* metod kreira kopiju postojeceg objekta */
    Izraz* Kopija() const {
        
        return new Sin(*this);
    }

    Izraz* Uprosti(const Okolina& o, const std::string& s) const {

        Izraz* l = izraz->Uprosti(o, s);

        if (dynamic_cast<Konstanta*>(l) != nullptr) {
            Izraz* rez = new Konstanta(sin(l->Vrednost(o)));
            delete l;
            return rez;
        }
        else 
            return new Sin(l);
    }

    Izraz* Izvod(const Okolina& o, const std::string& s) const;
};

class Cos : public Funkcija {

public:
    /* konstruktor */
    Cos(Izraz* i) : Funkcija(i) {

    }
    Cos(const Cos& s) : Funkcija(s) {

    }

    /* metod koji odredjuje vrednost izraza */
    double Vrednost(const Okolina& a) const {

        return cos(-izraz->Vrednost(a));
    }

    /* metod koji stampa izraz na ostream */
    void Ispisi(std::ostream& s) const {
        s << "COS ( " << (*izraz) << ") "; 
    }

    /* metod kreira kopiju postojeceg objekta */
    Izraz* Kopija() const {
        
        return new Cos(*this);
    }

    Izraz* Uprosti(const Okolina& o, const std::string& s) const {

        Izraz* l = izraz->Uprosti(o, s);

        if (dynamic_cast<Konstanta*>(l) != nullptr) {
            Izraz* rez = new Konstanta(cos(l->Vrednost(o)));
            delete l;
            return rez;
        }
        else 
            return new Cos(l);
    }

    Izraz* Izvod(const Okolina& o, const std::string& s) const {

        Izraz* l = izraz->Izvod(o, s);
        
        return new Suprotni(new Proizvod(new Sin(izraz->Kopija()), l));
    }
};

Izraz* Sin::Izvod(const Okolina& o, const std::string& s) const {

        Izraz* l = izraz->Izvod(o, s);
        
        return new Proizvod(new Cos(izraz->Kopija()), l);
    }

class Tan : public Funkcija {

public:
    /* konstruktor */
    Tan(Izraz* i) : Funkcija(i) {

    }
    Tan(const Tan& s) : Funkcija(s) {

    }

    /* metod koji odredjuje vrednost izraza */
    double Vrednost(const Okolina& a) const {

        return tan(-izraz->Vrednost(a));
    }

    /* metod koji stampa izraz na ostream */
    void Ispisi(std::ostream& s) const {
        s << "TAN ( " << (*izraz) << ") "; 
    }

    /* metod kreira kopiju postojeceg objekta */
    Izraz* Kopija() const {
        
        return new Tan(*this);
    }

    Izraz* Uprosti(const Okolina& o, const std::string& s) const {

        Izraz* l = izraz->Uprosti(o, s);

        if (dynamic_cast<Konstanta*>(l) != nullptr) {
            Izraz* rez = new Konstanta(tan(l->Vrednost(o)));
            delete l;
            return rez;
        }
        else 
            return new Tan(l);
    }

    Izraz* Izvod(const Okolina& o, const std::string& s) const {

        Izraz* l = izraz->Izvod(o, s);
        
        return new Kolicnik(l, new Proizvod(new Cos(izraz->Kopija()), new Cos(izraz->Kopija())));
    }
};

class Cot : public Funkcija {

public:
    /* konstruktor */
    Cot(Izraz* i) : Funkcija(i) {

    }
    Cot(const Cot& s) : Funkcija(s) {

    }

    /* metod koji odredjuje vrednost izraza */
    double Vrednost(const Okolina& a) const {
        
        double x = -izraz->Vrednost(a);
        return cos(x)/sin(x);
    }

    /* metod koji stampa izraz na ostream */
    void Ispisi(std::ostream& s) const {
        s << "COT ( " << (*izraz) << ") "; 
    }

    /* metod kreira kopiju postojeceg objekta */
    Izraz* Kopija() const {
        
        return new Cot(*this);
    }

    Izraz* Uprosti(const Okolina& o, const std::string& s) const {

        Izraz* l = izraz->Uprosti(o, s);

        if (dynamic_cast<Konstanta*>(l) != nullptr) {
            double x = l->Vrednost(o);
            Izraz* rez = new Konstanta(cos(x)/sin(x));
            delete l;
            return rez;
        }
        else 
            return new Cot(l);
    }

    Izraz* Izvod(const Okolina& o, const std::string& s) const {

        Izraz* l = izraz->Izvod(o, s);
        
        return new Kolicnik(new Suprotni(l), new Proizvod(new Sin(izraz->Kopija()), new Sin(izraz->Kopija())));
    }
};

class Log : public Funkcija {

public:
    /* konstruktor */
    Log(Izraz* i) : Funkcija(i) {

    }
    Log(const Log& s) : Funkcija(s) {

    }

    /* metod koji odredjuje vrednost izraza */
    double Vrednost(const Okolina& a) const {
        
        return log(izraz->Vrednost(a));
    }

    /* metod koji stampa izraz na ostream */
    void Ispisi(std::ostream& s) const {
        s << "LOG ( " << (*izraz) << ") "; 
    }

    /* metod kreira kopiju postojeceg objekta */
    Izraz* Kopija() const {
        
        return new Log(*this);
    }

    Izraz* Uprosti(const Okolina& o, const std::string& s) const {

        Izraz* l = izraz->Uprosti(o, s);

        if (dynamic_cast<Konstanta*>(l) != nullptr) {
            double x = l->Vrednost(o);
            Izraz* rez = new Konstanta(log(x));
            delete l;
            return rez;
        }
        else 
            return new Log(l);
    }

    Izraz* Izvod(const Okolina& o, const std::string& s) const {

        Izraz* l = izraz->Izvod(o, s);
        
        return new Proizvod(new Kolicnik(new Konstanta(1), izraz->Kopija()), l);
    }
};

class Exp : public Funkcija {

public:
    /* konstruktor */
    Exp(Izraz* i) : Funkcija(i) {

    }
    Exp(const Exp& s) : Funkcija(s) {

    }

    /* metod koji odredjuje vrednost izraza */
    double Vrednost(const Okolina& a) const {
        
        return exp(izraz->Vrednost(a));
    }

    /* metod koji stampa izraz na ostream */
    void Ispisi(std::ostream& s) const {
        s << "EXP ( " << (*izraz) << ") "; 
    }

    /* metod kreira kopiju postojeceg objekta */
    Izraz* Kopija() const {
        
        return new Exp(*this);
    }

    Izraz* Uprosti(const Okolina& o, const std::string& s) const {

        Izraz* l = izraz->Uprosti(o, s);

        if (dynamic_cast<Konstanta*>(l) != nullptr) {
            double x = l->Vrednost(o);
            Izraz* rez = new Konstanta(exp(x));
            delete l;
            return rez;
        }
        else 
            return new Log(l);
    }

    Izraz* Izvod(const Okolina& o, const std::string& s) const {

        Izraz* l = izraz->Izvod(o, s);
        
        return new Proizvod(new Exp(izraz->Kopija()), l);
    }
};

class Sqrt : public Funkcija {

public:
    /* konstruktor */
    Sqrt(Izraz* i) : Funkcija(i) {

    }
    Sqrt(const Sqrt& s) : Funkcija(s) {

    }

    /* metod koji odredjuje vrednost izraza */
    double Vrednost(const Okolina& a) const {
        
        return sqrt(izraz->Vrednost(a));
    }

    /* metod koji stampa izraz na ostream */
    void Ispisi(std::ostream& s) const {
        s << "SQRT ( " << (*izraz) << ") "; 
    }

    /* metod kreira kopiju postojeceg objekta */
    Izraz* Kopija() const {
        
        return new Sqrt(*this);
    }

    Izraz* Uprosti(const Okolina& o, const std::string& s) const {

        Izraz* l = izraz->Uprosti(o, s);

        if (dynamic_cast<Konstanta*>(l) != nullptr) {
            double x = l->Vrednost(o);
            Izraz* rez = new Konstanta(sqrt(x));
            delete l;
            return rez;
        }
        else 
            return new Log(l);
    }

    Izraz* Izvod(const Okolina& o, const std::string& s) const {

        Izraz* l = izraz->Izvod(o, s);
        
        return new Kolicnik(new Suprotni(l), new Proizvod(new Konstanta(2), new Sqrt(izraz->Kopija())));
    }
};

int main() {

    Okolina o;
    o.DodajPromenljivu("x", 5);
    o.DodajPromenljivu("y", 10);

    // (x/2) + (y - (3.14*z))
    Izraz* i1 = new Kolicnik(new Promenljiva("x"), new Sin(new Konstanta(2)));
    Izraz* i2 = new Proizvod(new Exp(new Sqrt(new Konstanta(3.14))), new Promenljiva("x"));
    Izraz* i3 = new Razlika(new Promenljiva("y"), i2);
    Izraz* i4 = new Zbir(i1, i3);

    std::cout << (*i4) << "=" << (i4->Vrednost(o)) << std::endl;

    Izraz* izvod = i4->Izvod(o, "x'");
    std::cout << (*izvod) << "=" << (izvod->Vrednost(o)) << std::endl;

    Izraz* i5 = i4->Uprosti(o, "x");
    std::cout << (*i5) << "=" << (i5->Vrednost(o)) << std::endl;

    Izraz* i6 = i5->Uprosti(o, "y");
    std::cout << (*i6) << "=" << (i6->Vrednost(o)) << std::endl;

    /* treba biti obazriv sa brisanjem objekata, jer u klasama ne cuvamo uvek kopije,
     * pa treba pazljivo oslobadjati memoriju.
     */
    delete i5;
    delete i4;
    delete i6;
    delete izvod;

    return 0;
}