#ifndef EMPRESTIMODAO_H
#define EMPRESTIMODAO_H

#include <QtSql/QtSql>

class EmprestimoDAO
{
public:
    struct DataCurva{
        std::string dataTx;
        double cotacao;
        double diasUteis;
        double valor;
    }datacurva;

public:
    void retrievelData(const std::string&, std::vector <DataCurva>& );
private:
    QSqlDatabase m_db;
    std::vector <DataCurva> m_datacurva;
public:
    EmprestimoDAO();
    ~EmprestimoDAO();
    void createDatabase();
    void insertData(const std::string& );
    void insertDataCurva(const DataCurva& );
};

#endif // EMPRESTIMODAO_H
