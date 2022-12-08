class Grade {
private:
    static const char GRADES[] = {...};
    // Or use string
    char                  ltr;
    int                   prct;

public:
    void setPrct(int prct) {
        this->prct = prct;
        this->ltr  = GRADES[prct / 10];
    }
    void setLtr(char ltr) {
        this->ltr  = ltr;
        this->prct = 100 - (ltr -'A') * 10 - 5;
    }
    void print() { std::cout << "Grade:" << this->prct << "->" << this->ltr << std::endl; }
};
