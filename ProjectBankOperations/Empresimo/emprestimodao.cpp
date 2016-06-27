#include "emprestimodao.h"
#include <QString>
#include <iostream>

EmprestimoDAO::EmprestimoDAO()
{
}

EmprestimoDAO::~EmprestimoDAO()
{
    m_db.close();
}

void EmprestimoDAO::createDatabase()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("database.db3");
    if (m_db.open())
    {
        QSqlQuery query(m_db);
        {
            const std::string sql= " CREATE TABLE  if not exists emprestimo "
                                   " ( emprestimo_id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                   " date_curva TEXT NOT NULL ); ";
            if (query.exec(QString(sql.c_str())))
            {
                qDebug() << "criado tabela com sucesso.";
            } else {
                qDebug() << "erro ao criar tabela." << query.lastError();
            }
        }
        {
            const std::string sql= " CREATE TABLE  if not exists curva_emprestimo "
                                   " ( curva_id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                   " emprestimo_id INTEGER REFERENCES emprestimo(emprestimo_id) , "
                                   " data_taxa TEXT NOT NULL, "
                                   " cotacao REAL NOT NULL, "
                                   " dias_uteis  REAL NOT NULL, "
                                   " valor_taxa REAL NOT NULL); ";
            if (query.exec(QString(sql.c_str())))
            {
                qDebug() << "criado tabela com sucesso.";
            } else {
                qDebug() << "erro ao criar tabela." << query.lastError();
            }
        }
    } else {
        qDebug() << "DB Nao aberto.";
    }    
}

void EmprestimoDAO::insertDataCurva(const DataCurva& data )
{
    m_datacurva.emplace_back(data);
}

void EmprestimoDAO::insertData(const std::string& dataOrigem  )
{
    {
        std::string sql = " SELECT  emprestimo_id, date_curva FROM emprestimo WHERE date_curva = " + dataOrigem + "; ";
        QSqlQuery query( QString(sql.c_str()) );
        query.exec();
        if( query.value(0).toInt() > 0 )
            return;
    }

    int id ;

    {
        std::string sql = " INSERT INTO emprestimo (date_curva) VALUES ('" + dataOrigem + "') ";
        QSqlQuery query( QString(sql.c_str()) );
        id = query.lastInsertId().toInt();
    }
    {
        for(const auto& it : m_datacurva)
        {
            std::string sql = " INSERT INTO curva_emprestimo (emprestimo_id, data_taxa, cotacao, dias_uteis, valor_taxa) VALUES (";
            sql += std::to_string(id) + ", '" + it.dataTx +"', " +  std::to_string(it.cotacao) + ", " +  std::to_string(it.diasUteis) + ", " + std::to_string(it.valor) + ")";
            QSqlQuery query( QString(sql.c_str()) );
        }

    }
}

void EmprestimoDAO::retrievelData(const std::string& dataOrigem , std::vector <DataCurva>& dataCurve )
{
    int id = 0;
    {
        std::string sql = " SELECT  count(*) FROM emprestimo WHERE date_curva = " + dataOrigem + "; ";
        QSqlQuery query( QString(sql.c_str()) );
        if(!query.exec())
            return;

        while (query.next()) {
            id = query.value(0).toInt();
        }
        if(id == 0)
            return;
    }
    {
        std::string sql = " SELECT  data_taxa, cotacao, dias_uteis, valor_taxa FROM curva_emprestimo WHERE emprestimo_id = " +  std::to_string(id)+ "; ";
        QSqlQuery query( QString(sql.c_str()) );
        query.exec();

        while (query.next()) {
            DataCurva curve;
            curve.dataTx = query.value(0).toString().toStdString();
            curve.cotacao = query.value(1).toDouble();
            curve.diasUteis = query.value(2).toDouble();
            curve.valor = query.value(3).toDouble();
            dataCurve.emplace_back(curve);
        }
    }
}
