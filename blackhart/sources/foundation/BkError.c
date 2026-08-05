// Standard headers.
#include <stdlib.h>

// blackhart headers.
#include "foundation/BkError.h"
#include "foundation/BkLogger.h"
#include "foundation/BkString.h"

// ~~~~~ Def(INTERNAL) ~~~~~

void _BkError_Initialize(void) {}

void _BkError_Uninitialize(void) {}

// ~~~~~ Def(PUBLIC) ~~~~~

void BkError_Log(struct BkErrorInfo const* info, char const* file, int line) {
  BK_ASSERT(BK_ISNULL(info));
  BK_ASSERT(BK_ISNULL(file));

  char const* const what = (info->what != NULL) ? info->what : "(unknown)";
  char const* const why = (info->why != NULL) ? info->why : "(unknown)";

  BkLog(
      BkString_CreateFormatted("Error:\n"
                               "  what:   %s\n"
                               "  why:    %s\n",
                               what, why));

  if (info->where != NULL)
    BkLog(BkString_CreateFormatted("  where:  %s (%s:%d)\n", info->where, file,
                                   line));
  else
    BkLog(BkString_CreateFormatted("  where:  %s:%d\n", file, line));

  if (info->how != NULL)
    BkLog(BkString_CreateFormatted("  how:    %s\n", info->how));

  if (info->result != NULL)
    BkLog(BkString_CreateFormatted("  result: %s\n", info->result));
}

void BkError_Fatal(struct BkErrorInfo const* info, char const* file, int line) {
  BkError_Log(info, file, line);
  exit(BK_FAILURE);
}
