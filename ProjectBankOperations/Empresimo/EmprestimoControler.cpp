#include "EmprestimoControler.h"

#include <iostream>
#include <QFile>
#include <QXmlStreamReader>

EmprestimoControler::EmprestimoControler() :
    m_emprestimoView( new EmprestimoView() )
{    
    m_emprestimoView->show();
}

EmprestimoControler::~EmprestimoControler(){
    delete m_emprestimoView;
}

void EmprestimoControler::holidays()
{
    std::vector <QDate> holyday;
    const std::string filename = "holidays.xml";
    QFile file(QString(filename.c_str()));
    if (!file.open(QIODevice::ReadOnly))
    {
        std::cerr << "Error: Cannot read file " << qPrintable(QString(filename.c_str()))
                  << ": " << qPrintable(file.errorString())
                  << std::endl;
        return;
    }

    QXmlStreamReader rxml;
    rxml.setDevice(&file);
    rxml.readNext();

    while (!rxml.isEndDocument())
    {
        if (rxml.isStartElement())
        {
            if (rxml.name().toString() == "holiday" )
            {
                foreach(const QXmlStreamAttribute &attr, rxml.attributes())
                {
                    if (attr.name().toString() == QLatin1String("date"))
                    {
                        const std::string & d = attr.value().toString().toStdString();
                        const int32_t& day = std::stol(d.substr(8,2));
                        const int32_t& month = std::stol(d.substr(5,2));
                        const int32_t& year = std::stol(d.substr(0,4));
                        QDate date(year, month, day);

                        holyday.emplace_back(date);
                    }
                }
            }
        }else if (rxml.isEndElement())
        {
            rxml.readNext();
        }
        rxml.readNext();
    }
    if (rxml.hasError())
    {
        std::cout << "XML error: " << rxml.errorString().data() << std::endl;
    }
    m_emprestimoView->holidays(holyday);
}
