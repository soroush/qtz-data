#include "async/database-exception.hpp"

DatabaseException::DatabaseException(const QSqlError &e, const QString userMsg) :
    m_code(e.nativeErrorCode()),
    m_message(e.text()),
    m_error(e)
{
    if(userMsg.isEmpty())
        this->m_userMessage = m_message;
}

const char *DatabaseException::what() const throw()
{
    return QString(QStringLiteral("Error ") + m_code + QStringLiteral(": ") + m_message)
           .toStdString().c_str();
}

QSqlError DatabaseException::getError() const
{
    return m_error;
}
