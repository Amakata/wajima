#ifndef ZEFIRO_STD_EXCEPTION_H
#define ZEFIRO_STD_EXCEPTION_H

#include <std/SourceLine.h>
#include <exception>
#include <string>

namespace zefiro_std {

/*! \brief Exceptions thrown by failed assertions.
 * \ingroup BrowsingCollectedTestResult
 *
 * Exception is an exception that serves
 * descriptive strings through its what() method
 */
class Exception : public std::exception
{
public:

    class Type
    {
    public:
        Type( std::string type ) : m_type ( type ) {}

        bool operator ==( const Type &other ) const
        {
	    return m_type == other.m_type;
        }
    private:
        const std::string m_type;
    };


    Exception( std::string  message = "", 
	       SourceLine sourceLine = SourceLine() );

    Exception( std::string  message, 
	       long lineNumber, 
	       std::string fileName );

    Exception (const Exception& other);

    virtual ~Exception () throw();

    Exception& operator= (const Exception& other);

    const char *what() const throw ();

    SourceLine sourceLine() const;

    long lineNumber() const;
    std::string fileName() const;

    static const std::string UNKNOWNFILENAME;
    static const long UNKNOWNLINENUMBER;

    virtual Exception *clone() const;
    
    virtual bool isInstanceOf( const Type &type ) const;

    static Type type();

private:
    // VC++ does not recognize call to parent class when prefixed
    // with a namespace. This is a workaround.
    typedef std::exception SuperClass;

    std::string m_message;
    SourceLine m_sourceLine;
};


} // namespace zefiro_std

#endif // ZEFIRO_STD_EXCEPTION_H

