/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/std/SourceLine.cpp,v 1.2 2002/04/28 13:31:40 ama Exp $
 */

#include <std/SourceLine.h>


namespace zefiro_std
{

SourceLine::SourceLine() :
    m_lineNumber( -1 )
{
}


SourceLine::SourceLine( const std::string &fileName,
                        int lineNumber ) :
    m_fileName( fileName ),
    m_lineNumber( lineNumber )
{
}


SourceLine::~SourceLine()
{
}


bool 
SourceLine::isValid() const
{
  return !m_fileName.empty();
}


int 
SourceLine::lineNumber() const
{
  return m_lineNumber;
}


std::string 
SourceLine::fileName() const
{
  return m_fileName;
}


bool 
SourceLine::operator ==( const SourceLine &other ) const
{
  return m_fileName == other.m_fileName  &&
         m_lineNumber == other.m_lineNumber;
}


bool 
SourceLine::operator !=( const SourceLine &other ) const
{
  return !( *this == other );
}


} // namespace zefiro_std
