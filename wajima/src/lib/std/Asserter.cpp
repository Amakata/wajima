/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/std/Asserter.cpp,v 1.3 2002/04/29 16:29:05 ama Exp $
 */

#include "std/Asserter.h"
#include "std/NotEqualException.h"


namespace zefiro_std
{

namespace Asserter
{

void 
fail( std::string message, 
      SourceLine sourceLine )
{
  throw Exception( message, sourceLine );
}


void 
failIf( bool shouldFail, 
        std::string message, 
        SourceLine location )
{
  if ( shouldFail )
    fail( message, location );
}


void 
failNotEqual( std::string expected, 
              std::string actual, 
              SourceLine sourceLine,
              std::string additionalMessage )
{
  throw NotEqualException( expected, 
                           actual, 
                           sourceLine, 
                           additionalMessage );
}


void 
failNotEqualIf( bool shouldFail,
                std::string expected, 
                std::string actual, 
                SourceLine sourceLine,
                std::string additionalMessage )
{
  if ( shouldFail )
    failNotEqual( expected, actual, sourceLine, additionalMessage );
}


} // namespace Asserter
} // namespace zefiro_std
