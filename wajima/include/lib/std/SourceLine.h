/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/include/lib/std/Attic/SourceLine.h,v 1.1 2002/05/10 19:30:53 ama Exp $
 */

#ifndef ZEFIRO_STD_SOURCELINE_H
#define ZEFIRO_STD_SOURCELINE_H

#include <string>

/*! \brief Constructs a SourceLine object initialized with the location where the macro is expanded.
 * \ingroup CreatingNewAssertions
 * \relates zefiro_std::SourceLine
 * Used to write your own assertion macros.
 * \see Asserter for example of usage.
 */
#define ZEFIRO_STD_SOURCELINE() ::zefiro_std::SourceLine( __FILE__, __LINE__ )


namespace zefiro_std
{

/*! \brief Represents a source line location.
 * \ingroup CreatingNewAssertions
 * \ingroup BrowsingCollectedTestResult
 *
 * Used to capture the failure location in assertion.
 * 
 * Use the ZEFIRO_STD_SOURCELINE() macro to construct that object. Typically used when
 * writing an assertion macro in association with Asserter.
 *
 * \see Asserter.
 */
class SourceLine
{
public:
  SourceLine();

  SourceLine( const std::string &fileName,
              int lineNumber );

  /// Destructor.
  virtual ~SourceLine();

  bool isValid() const;

  int lineNumber() const;

  std::string fileName() const;

  bool operator ==( const SourceLine &other ) const;
  bool operator !=( const SourceLine &other ) const;

private:
  std::string m_fileName;
  int m_lineNumber;
};


}; // namespace zefiro_std



#endif  // ZEFIRO_STD_SOURCELINE_H