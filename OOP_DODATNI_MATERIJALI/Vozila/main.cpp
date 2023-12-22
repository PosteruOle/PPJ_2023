/* Nas zadatak je da napravimo jednostavan program koji ce simulirati
 * rad Perionice automobila. Vlasniku vozila treba omoguciti da dodaje 
 * vozila u red, da na liniju za pranje postavi prvo vozilo iz reda. Cenu 
 * pranja vozila treba odredjivati na osnovu vrste vozila. Program treba da
 * podrzava razlicite vrste vozila kroz hijerarhiju klasa vozila.
 */
#include <iostream>
/* double-ended queue */
#include <deque>

/* Nasledjivanje u C++ moze biti jednostruko i visestruko. Jednostruko nasledjivanje
 * podrazumeva da izvedena klasa ima tacno jednu roditeljsku klasu, dok kod visetrukog nasledjivanja
 * izvedena klasa moze imati vise roditeljskih klasa. Posledica toga je da kod jednostrukog 
 * nasledjivanja, kompletna hijerahija klasa ima jednu baznu klasu, dok kod visestrukog nasledjivanja
 * hijerarhija moze imati vise baznih klasa. Visestruko nasledjivanje je mocan koncept koji nepazljivim
 * koriscenjem cesto dovodi do problema poznatog kao "diamond problem". Najjednostavnija ilustracija 
 * opisanog problema je sledeca:
 * 
 * 1. Zamislimo da imamo baznu klasu Osoba.
 * 2. Iz bazne klase osoba mozemo izvesti klase naslednice Student i Zaposleni (na fakultetu).
 * 3. Asistent je ujedno i student i zaposleni na fakultetu, pa je prirodno da klasa Asistent nasledjuje
 *    klase Student i Zaposleni.
 * 
 * Problem dijamanta se krije u tome sto bi Asistent nasledio dve kopije atributa klase Osoba (jednu iz roditelja
 * Student, drugu iz roditelja Zaposleni), sto dovodi do viseznacnosti. Opisani problem se moze jednostavno
 * razresiti, ali je to izvan opsega, ali i potreba naseg kursa. Upravo zbog toga, u svim nasim primerima 
 * zadrzacemo se iskljucivo na jednostrukom nasledjivanju.
 * 
 * Da bi se izbegao gore opisani problem, programski jezici poput Jave i C# ne podrzavaju visetruko nasledjivanje 
 * klasa, vec to resavaju na drugaciji nacin. Klasa moze naslediti najvise jednu roditeljsku klasu, ali moze 
 * implementirati proizvoljni broj interfejsa koji su posebni tipovi podataka u Javi i C#. 
 * U programskom jeziku C++ interfejsi formalno ne postoje, vec se interfejsom smatra cisto apstraktna 
 * klasa bez atributa, tj. klasa koja nema podataka vec je sacinjena samo od apstraktnih metoda. 
 * 
 * Pored ova dva tipa nasledjivanja, programski jezik C++ podrzava i tri vida nasledjivanja. Nasledjivanje
 * moze biti privatno, zasticeno i javno i to se mora navesti prilikom deklaracije klase kljucnim recima
 * private, protected i public redom. Nezavisno od vida nasledjivanja, sva javna i zasticena polja i sve javne
 * i zasticene metode bazna klase su vidljivi u izvedenoj klasi. Vid nasledjivanja ima efekta na to kako korisnik 
 * izvedene klase vidi nasledjene elemente. Efekat vidova nasledjivanja je sledeci:
 * 
 * 1. private - javne metode i javna polja bazne klase ce se ponasati kao privatni u izvedenoj klasi, tj. nece biti
 *              dostupni korisniku. 
 * 2. protected - javne metode i javna polja bazne klase ce se ponasati kao zasticeni u izvedenoj klasi, tj. nece biti
 *              dostupni korisniku, ali bice dostupni ostatku hijerarhije klasa.
 * 3. public - javne metode i javna polja bazne klase ce se ponasati kao javni u izvedenoj klasi, tj. bice
 *              dostupni korisniku.  
 * 
 * Dakle, vidovi nasledjivanja definisu na koji nacin se ponasaju javne metode i javna polja bazne klase prilikom
 * koriscenja izvedene klase. 
 * 
 * U praksi, nasledjivanje se gotovo uvek definise kao javno, jer je sustina nasledjivanja da se omoguci upotreba vec
 * definisanih metoda bazne klase u izvedenoj klasi. Zasticenim ili privatnim nasledjivanjem, takva praksa ne bi bila
 * moguca, jer korisnik izvedene klase ne bi ni bio svestan tih metoda i polja. Kada god pomislite da koristite 
 * privatno nasledjivanje, tj. ako zelite da klasa B privatno nasledjuje klasu A, tada je mnogo bolje da u klasu B
 * dodate novi atribut koji je tipa klase A. 
 * 
 * Da bismo obezbedili dinamicki polimorfizam, tj. dinamicko vezivanje metoda tokom izvrsavanja programa
 * potrebno je da koristimo kljcnu rec virtual. Dakle, metod obelezen sa virtual
 * 
 * virtual nazivMetoda(listaArgumenata) {
 *      implementacija
 * }
 * 
 * dozvoljava predefinisanje (overriding) u izvedenoj klasi. Pri tome, ne moramo navoditi kljucnu rec virtual. Ako
 * u izvedenoj klasi ostavimo kljucnu rec virtual, to znaci da dozvoljavamo dalje predefinisanje metoda u buducim
 * izvodjenjima i prosirenjima hijerarhije klasa. 
 * 
 * Ukoliko postoji potreba za cisto virtuelnim, tj. apstraktnim metodama, neophodno je da na kraju deklaracije 
 * metoda dodamo " = 0". Preciznije, cisto apstraktni metod ima sledeci potpis u baznoj klasi:
 * 
 * virtual nazivMetoda(listaArgumenata) = 0;
 * 
 * Klasa koja ima cisto virtuelni metod se naziva apstraktna klasa i ne moze se direktno instancirati. Izvedena
 * klasa treba da implementira navedeni apstraktni metod da bi se konkretizovala. 
 * 
 * Programski jezik C++ ne podrzava kljucnu rec "base" kao referencu na baznu klasu. U slucaju da nam treba ponasanje
 * nekog predefinisanog metoda iz bazne klase potrebno je da koristimo kvalifikovano ime metoda u obliku
 * BaznaKlasa::nazivMetoda().
 * 
 * Iz ovoga se moze zakljuciti da treba razlikovati virtuelne i apstraktne metode. Virtuelne metode su u baznoj
 * klasi obelezene kljucnom reci virtual i obezbedjuju podrazumevano ponasanje u baznoj klasi, tj. implementaciju. 
 * Kljucna rec virtual samo omogucava predefinisanje ili dodefinisanje ponasanja u izvedenim klasama. Apstraktne
 * metode na kraju svoje deklaracije imaju oznaku "= 0" i ne obezbedjuju podrazumevano ponasanje, tj. implementaciju
 * u baznoj klasi. Klasa koja ima barem jedan cisto apstraktni metod je apstraktna i ne moze se direktno instancirati.
 * Izvedene klase su duzne da taj cisto apstraktni metod predefinisu da bi se konkretizovale i omogucile instanciranje.
 * 
 * S obzirom da C++ ne poseduje automatsko upravljanje memorijom (npr. garbage collector), potrebno je da mi vodimo
 * racuna koje resurse i na koji nacin nasa hijerarhija klasa koristi. Preciznije mi smo duzni da obezbedimo 
 * pravilno unistavanje resursa koji nam vise nisu potrebni. Da bismo razumeli kako to funkcionise razmotricemo 
 * sledeci, jednostavan primer. Neka je data bazna klasa A i njena izvedena klasa B. Prvo cemo posmatrati kreiranje
 * objekta klase b B, a zatim i njegovo unistavanje. S obzirom da se radi o nasledjivanju, klasa B jeste instanca 
 * klase A, sto znaci da postupak kreiranje treba da bude sledeci:
 * 
 * 1. Kreiramo sve resurse koje koristi bazna klasa (A).
 * 2. Kreiramo sve resurse koje specijalizacija (klasa B) dodatno koristi.
 * 3. Nakon koraka 1 i 2 kreiran je objekat klase B.
 * 
 * Programski jezik C++ upravo na ovaj nacin vrsi konstrukciju objekta koji je deo neke hijerarhije klasa. Medjutim,
 * prilikom unistavanja objekta, prica je malo drugacija. Podrazumevani destruktor unistice samo resurse objekta B, 
 * ali ne i one resurse nasledjene od bazne klase. Da bi se to desilo, potrebno je da mi pravilno uvezemo destruktore. 
 * Preciznije, destruktor bazne klase MORA se obeleziti kao virtuelni, tj. kljucnom reci virtual. Kada to uradimo, 
 * prilikom unitavanja objekta B, automatski ce biti pozvan i destruktor bazne klase. Imajuci ovo u vidu, unistavanje
 * objekta klase B bice izvrseno na sledeci nacin:
 * 
 * 1. Prvo se poziva destruktor izvedene klase, cime se unistavaju resursi izvedene klase.
 * 2. Zatim se poziva destruktor bazne klase, cime se unistavaju resursi bazne klase. 
 * 3. Nakon koraka 1 i 2 objekat klase B bice ispravno i u potpunosti unisten. 
 * 
 * Pored svega ovoga, jos jedna specificnost programskog jezika C++ je da dinamicki polimorfizam radi iskljucivo
 * u kombinaciji sa pokazivacima ili referencama. U kombinaciji sa automatskim promenljivama, dinamicki polimorfizam
 * se ne izvrsava. Imajuci u vidu specificnosti referenci, prilikom upotrebe hijerhije klasa najcesce se koriste 
 * pokazivaci i dinamicko kreiranje objekata na hipu. Upravo zbog ovoga, vazno je posebno voditi racuna o pravilnom
 * vezivanju destruktora, jer bi u suprotnom doslo do katastrofalnog curenja memorije i resursa. 
 */

/* Pravimo sledecu hijerarhiju klasa
 * Vozilo ----> Kamion
 *        |
 *        ----> Kombi
 *        |
 *        ----> Automobil ----> SportskiAutomobil
 *                        |
 *                        ----> Sedan
 *                        |
 *                        ----> Karavan
 */

/* bazna klasa hijerarhije 
 * Primetimo da u trenutku razmatranja pojma Vozilo nemamo dovoljno informacija
 * da preciziramo tacno o kojoj vrsti vozila se radi (automobil, kombi, kamion itd), ali mozemo
 * da uocimo neke njihove zajednicke karakteristike poput broja prozora, broja tockova, broja sedista
 * i slicno. Ove zajednicke karakteristike mozemo da objedinimo u baznoj klasi Vozilo, koja ce biti 
 * apstraktna.
 */
class Vozilo {

public:
    /* konstruktor bazne klase */
    Vozilo() {
        /* stampamo poruku da bismo mogli da pratimo redosled pozivanja konstruktora 
         * prilikom instanciranja objekata koji pripadaju hijerarhiji
         */
        std::cout << "Kreiram vozilo" << std::endl;
    }
    /* destruktor bazne klase se mora obeleziti kljucnom reci virtual
     * da bi bio automatski pozvan prilikom unistavanja objekta hijerarhije
     */
    virtual ~Vozilo() {
        /* stampamo poruku da bismo mogli da pratimo redosled pozivanja destruktora 
         * prilikom unistavanja objekata koji pripadaju hijerarhiji
         */
        std::cout << "Unistavam vozilo" << std::endl;
    }

    /* cisto apstraktne metode
     * obelezene kljucnom reci virtual i sa "= 0" na kraju
     */
    virtual std::string Vrsta() const = 0;
    virtual int BrojProzora() const = 0;
    virtual int BrojTockova() const = 0;
    virtual int BrojSedista() const = 0;

    /* kreiramo mehanizam kloniranja, jer virtuelni konstruktori kopije ne postoje 
     * Pozivanje konstruktora kopije je moguce nad konkretnim tipovima, ali ne i nad apstraktnim
     * tipovima, sto je nase vozilo. Medjutim, niko nam ne brani da naucimo objekte nase hijerarhije kako
     * da se kloniraju.
     */
    virtual Vozilo* kopija() const = 0;
};

/* Izvedene klasa automobil. Primetimo da i ovde nemamo dovoljno
 * informacija o tome o kakvom se automobilu radi, pa i Automobil
 * moze ostati apstraktna klasa iz koje cemo u nastavku izvesti
 * nove klase u hijerarhiji. Medjutim, ovde nisu bas sve karakteristike
 * vozila nepoznate, pa ce neke funkcije iz apstraktnih preci u virtuelne. 
 */
class Automobil : public Vozilo {

public:
    /* konstruktor izvedene klase, koja ce u nastavku biti baza za dalja 
     * prosirivanja hijerarhije
     */
    Automobil() {
        /* stampamo poruku da bismo mogli da pratimo redosled pozivanja konstruktora 
         * prilikom instanciranja objekata koji pripadaju hijerarhiji
         */
        std::cout << "Kreiram automobil" << std::endl;
    }
    /* s obzirom da je i klasa Automobil bazna klasa i njen destruktor moramo obeleziti
     * kao virtuelni da bismo obezbedili pravilno uvezivanje destruktora prilikom unistavanja objekta
     */
    virtual ~Automobil() {
        /* stampamo poruku da bismo mogli da pratimo redosled pozivanja destruktora 
         * prilikom unistavanja objekata koji pripadaju hijerarhiji
         */
        std::cout << "Unistavam automobil" << std::endl;
    }

    /* znamo da se radi o Automobilu kao vrsti automobila, pa zbog toga implementiramo
     * nasledjenu funkciju. Medjutim, mozda ce klase koje dalje izvodimo zeleti da dodefinisu
     * ovaj metod, pa zbog toga ostavljamo kljucnu rec virtual.
     */
    virtual std::string Vrsta() const {
        return "Automobil";
    }
    
    /* broj prozora i dalje ne znamo, pa metod ostaje cisto virtuelni, tj. apstraktni */
    virtual int BrojProzora() const = 0;

    /* broj tockova nam je u ovom momentu poznat i nece se menjati, ma o kom tipu 
     * automobila da se radi. zbog toga metod ne mora biti virtuelni, jer ne postoji
     * potreba za njegovim predefinisanjem za razlicite tipove automobila. 
     */
    int BrojTockova() const {
        return 4;
    }

    /* broj sedista i dalje ne znamo, pa metod ostaje cisto virtuelni, tj. apstraktni */
    virtual int BrojSedista() const = 0;

    /* kreiramo mehanizam kloniranja, jer virtuelni konstruktori kopije ne postoje 
     * Pozivanje konstruktora kopije je moguce nad konkretnim tipovima, ali ne i nad apstraktnim
     * tipovima, sto je nase vozilo. Medjutim, niko nam ne brani da naucimo objekte nase hijerarhije kako
     * da se kloniraju.
     */
    virtual Vozilo* kopija() const = 0;
};

/* Nova izvedena klasa iz klase Vozilo */
class Kamion: public Vozilo {

public:
    /* konstruktor izvedene klase */
    Kamion() {
        /* stampamo poruku da bismo mogli da pratimo redosled pozivanja konstruktora 
         * prilikom instanciranja objekata koji pripadaju hijerarhiji
         */
        std::cout << "Kreiram kamion" << std::endl;
    }
    /* iz klase Kamion nece dalje biti izvodjenja, pa njen konstruktor ne moramo
     * da obelezimo kao virtuelni.
     */
    ~Kamion() {
        /* stampamo poruku da bismo mogli da pratimo redosled pozivanja destruktora 
         * prilikom unistavanja objekata koji pripadaju hijerarhiji
         */
        std::cout << "Unistavam kamion" << std::endl;
    }

    /* konstruktor kopije */
    Kamion(const Kamion& k) {
        std::cout << "Kreiram kopiju kamiona" << std::endl;
    }   

    /* implementiramo sve apstraktne metode iz bazne klase */
    std::string Vrsta() const {
        return "Kamion";
    }
    int BrojProzora() const  {
        return 4;
    }
    int BrojTockova() const  {
        return 6;
    }
    int BrojSedista() const  {
        return 2;
    }

    /* primetimo da nijedan metod nema kljucnu rec virtual, jer nece biti daljeg izvodjenja */

    /* implementiramo mehanizam kloniranja */
    Vozilo* kopija() const {
        return new Kamion(*this);
    }
};

class Kombi: public Vozilo {

public:
    /* konstruktor izvedene klase */
    Kombi() {
        /* stampamo poruku da bismo mogli da pratimo redosled pozivanja konstruktora 
         * prilikom instanciranja objekata koji pripadaju hijerarhiji
         */
        std::cout << "Kreiram kombi" << std::endl;
    }
    /* iz klase Kombi nece dalje biti izvodjenja, pa njen konstruktor ne moramo
     * da obelezimo kao virtuelni.
     */
    ~Kombi() {
        /* stampamo poruku da bismo mogli da pratimo redosled pozivanja destruktora 
         * prilikom unistavanja objekata koji pripadaju hijerarhiji
         */
        std::cout << "Unistavam kombi" << std::endl;
    }
    /* konstruktor kopije */
    Kombi(const Kombi& k) {
        std::cout << "Kreiram kopiju kombija" << std::endl;
    }   

    /* implementiramo sve apstraktne metode iz bazne klase */
    std::string Vrsta() const {
        return "Kombi";
    }
    int BrojProzora() const {
        return 5;
    }
    int BrojTockova() const {
        return 4;
    }
    int BrojSedista() const {
        return 3;
    }
    /* primetimo da nijedan metod nema kljucnu rec virtual, jer nece biti daljeg izvodjenja */

    /* implementiramo mehanizam kloniranja */
    Vozilo* kopija() const {
        return new Kombi(*this);
    }
};

/* izvedena klasa koja nasledjuje klasu Automobil, a time posredno i klasu vozilo */
class SportskiAutomobil : public Automobil {
public:
    /* konstruktor izvedene klase */
    SportskiAutomobil() {
        /* stampamo poruku da bismo mogli da pratimo redosled pozivanja konstruktora 
         * prilikom instanciranja objekata koji pripadaju hijerarhiji
         */
        std::cout << "Kreiram sportski automobil" << std::endl;
    }
    /* iz klase SportskiAutomobil nece dalje biti izvodjenja, pa njen konstruktor ne moramo
     * da obelezimo kao virtuelni.
     */
    ~SportskiAutomobil() {
        /* stampamo poruku da bismo mogli da pratimo redosled pozivanja destruktora 
         * prilikom unistavanja objekata koji pripadaju hijerarhiji
         */
        std::cout << "Unistavam sportski automobil" << std::endl;
    }

    /* konstruktor kopije */
    SportskiAutomobil(const SportskiAutomobil& k) {
        std::cout << "Kreiram kopiju sportskog automobila" << std::endl;
    }   

    /* implementiramo sve apstraktne metode iz bazne klase */
    std::string Vrsta() const {
        /* ukoliko zelimo da koristimo postojecu implementaciju iz bazne klase prilikom predefinisanja metoda
         * u izvedenoj klasi treba samo da je pozovemo njenim punim imenom
         */
        return Automobil::Vrsta() + " -> Sportski Automobil";
    }

    int BrojProzora() const {
        return 6;
    }
    int BrojTockova() const {
        return 4;
    }
    int BrojSedista() const {
        return 2;
    }
    /* primetimo da nijedan metod nema kljucnu rec virtual, jer nece biti daljeg izvodjenja */

    /* implementiramo mehanizam kloniranja */
    Vozilo* kopija() const {
        return new SportskiAutomobil(*this);
    }
};

class Sedan : public Automobil {
public:
    /* konstruktor izvedene klase */
    Sedan() {
        /* stampamo poruku da bismo mogli da pratimo redosled pozivanja konstruktora 
         * prilikom instanciranja objekata koji pripadaju hijerarhiji
         */
        std::cout << "Kreiram sedan" << std::endl;
    }
    /* iz klase Sedan nece dalje biti izvodjenja, pa njen konstruktor ne moramo
     * da obelezimo kao virtuelni.
     */
    ~Sedan() {
        /* stampamo poruku da bismo mogli da pratimo redosled pozivanja destruktora 
         * prilikom unistavanja objekata koji pripadaju hijerarhiji
         */
        std::cout << "Unistavam sedan" << std::endl;
    }

    /* konstruktor kopije */
    Sedan(const Sedan& k) {
        std::cout << "Kreiram kopiju sedan" << std::endl;
    }   

    /* implementiramo sve apstraktne metode iz bazne klase */
    std::string Vrsta() const {
        /* ukoliko zelimo da koristimo postojecu implementaciju iz bazne klase prilikom predefinisanja metoda
         * u izvedenoj klasi treba samo da je pozovemo njenim punim imenom
         */
        return Automobil::Vrsta() + " -> Sedan";
    }

    int BrojProzora() const {
        return 6;
    }
    int BrojTockova() const {
        return 4;
    }
    int BrojSedista() const {
        return 4;
    }
    /* primetimo da nijedan metod nema kljucnu rec virtual, jer nece biti daljeg izvodjenja */

    /* implementiramo mehanizam kloniranja */
    Vozilo* kopija() const {
        return new Sedan(*this);
    }
};

class Karavan : public Automobil {
public:
    /* konstruktor izvedene klase */
    Karavan(){
        /* stampamo poruku da bismo mogli da pratimo redosled pozivanja konstruktora 
         * prilikom instanciranja objekata koji pripadaju hijerarhiji
         */
        std::cout << "Kreiram karavan" << std::endl;
    }
    /* iz klase Karavan nece dalje biti izvodjenja, pa njen konstruktor ne moramo
     * da obelezimo kao virtuelni.
     */
    ~Karavan() {
        /* stampamo poruku da bismo mogli da pratimo redosled pozivanja destruktora 
         * prilikom unistavanja objekata koji pripadaju hijerarhiji
         */
        std::cout << "Unistavam karavan" << std::endl;
    }

     /* konstruktor kopije */
    Karavan(const Karavan& k) {
        std::cout << "Kreiram kopiju karavana" << std::endl;
    }   

    /* implementiramo sve apstraktne metode iz bazne klase */
    std::string Vrsta() const {
        /* ukoliko zelimo da koristimo postojecu implementaciju iz bazne klase prilikom predefinisanja metoda
         * u izvedenoj klasi treba samo da je pozovemo njenim punim imenom
         */
        return Automobil::Vrsta() + " -> Karavan";
    }

    int BrojProzora() const {
        return 8;
    }
    int BrojTockova() const {
        return 4;
    }
    int BrojSedista() const {
        return 4;
    }
    /* primetimo da nijedan metod nema kljucnu rec virtual, jer nece biti daljeg izvodjenja */

    /* implementiramo mehanizam kloniranja */
    Vozilo* kopija() const {
        return new Karavan(*this);
    }
};

/* kreiramo klasu perionica koja definise */
class Perionica {
private:
    /* vozila cuvamo u redu, jer onaj ko prvi stigne, prvi ce biti opran
     * BITNO:
     * da bismo mogli da koristimo dinamicki polimorfizam, podatke moramo da cuvamo kao
     * pokazivace. cuvanje pokazivaca u redu znaci da cuvamo podatke sa hipa, pa nasa klasa
     * mora da vodi racuna o njihovom unistavanja. posledica toga je da moramo da obezbedimo
     * destruktor, konstruktor kopije i operator dodele. 
     */
    std::deque<Vozilo*> _red;
    /* pomocni metod koji izdvaja prvi element iz reda */
    Vozilo* prviNaRedu() {
        /* procitamo element sa pocetka reda */
        Vozilo* v = _red.front();
        /* uklonimo element iz reda */
        _red.pop_front();
        /* vratimo zapamceni element */
        return v;
    }

    /* pomocni metod koji brise sadrzaj reda */
    void isprazniRed() {
        while (!_red.empty()) {
            delete prviNaRedu();
        }
    }

    /* popunjavanje reda na osnovu postojeceg */
    void popuniRed(const std::deque<Vozilo*>& red) {

        /* prolazimo kroz red i ubacujemo element na kraj */
        for (auto it = red.begin(); it != red.end(); it++) {
            _red.push_back((*it)->kopija());
        }
    }

    /* pomocni metod koji odredjuje cenu na osnovu tipa vozila */
    int odrediCenu(Vozilo* v) {
        
        int osnovnaCena = 800;
        
        /* tip vozila mozemo da proverimo pomocu operatora dynamic_cast */
        if (dynamic_cast<Automobil*>(v) != nullptr) {
            osnovnaCena += 20*v->BrojTockova() + 40*v->BrojProzora() + 60*v->BrojSedista();
        }
        else if (dynamic_cast<Kamion*>(v) != nullptr) {
            osnovnaCena *= 3;
        }
        else if (dynamic_cast<Kombi*>(v) != nullptr) {
            osnovnaCena*=2;
        }

        return osnovnaCena;
    }

public:
    /* podrazumevano konstruktor koji kreira praznu perionicu */
    Perionica() : _red() {
        /* stampamo poruku da bismo pratili instanciranje objekata */
        std::cout << "Kreiram perionicu" << std::endl;
    }
    /* eksplicitni destruktor, jer nasa klasa koristi dinamicke resurse */
    ~Perionica() {
        std::cout << "Unistavam red" << std::endl;
        /* unistavamo svaki element iz reda */
        isprazniRed();
        std::cout << "Unisten red" << std::endl;
    }
    /* konstruktor kopije kojim pravimo duboku kopiju postojece perionice */
    Perionica(const Perionica& p) : _red(){

        popuniRed(p._red);
    }
    /* operator dodele */
    Perionica& operator =(const Perionica& p) {

        /* self-assignment check */
        if (this == &p)
            return *this;

        /* ispraznimo stari sadrzaj */
        isprazniRed();
        /* napunimo red novim sadrzajem */
        popuniRed(p._red);

        return *this;
    }

    /* dodajemo novo vozilo u red */
    void DodajVozilo(Vozilo* v) {
        _red.push_back(v);
    }

    /* metod koji "pere" vozilo */
    void OperiVozilo() {

        /* ako neko ceka u redu */
        if (!_red.empty()) {
            /* izbacujemo vozilo iz reda */
            Vozilo* v = prviNaRedu();
            /* "peremo" vozilo */
            std::cout << "Na redu je: " << std::endl
                      << "\tTip vozila: " << v->Vrsta()
                      << "\tBroj tockova: " << v->BrojTockova()
                      << "\tBroj sedista: " << v->BrojSedista()
                      << "\tBroj Prozora: " << v->BrojProzora()
                      << "\tCena: " << odrediCenu(v)
                      << std::endl;
            /* unistavamo vozilo */
            delete v;
        }
        else {
            std::cout << "Perionica je prazna" << std::endl;
        }
    }

    /* metod koji provera da li neko ceka u redu */
    bool NekoCeka() {

        return !_red.empty();
    }
};

/* test program */
int main() {

    /* kreiramo perionicu */
    Perionica p;

    /* dodajemo vozila u red */
    p.DodajVozilo(new Kamion());
    p.DodajVozilo(new Kombi());
    p.DodajVozilo(new SportskiAutomobil());
    p.DodajVozilo(new Karavan());
    p.DodajVozilo(new Sedan());

    /* peremo vozila */
    while (p.NekoCeka())
        p.OperiVozilo();

    return 0;
}