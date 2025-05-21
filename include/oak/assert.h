#ifndef OAK_ASSERT_H
#define OAK_ASSERT_H
#include <assert.h>
#define OAK_ASSERT(cond) if (!(cond)) {__assert_fail(#cond, __FILE__, __LINE__, __PRETTY_FUNCTION__);} 
#endif // OAK_ASSERT_H

