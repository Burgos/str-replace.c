
//
// str-replace.c
//
// Copyright (c) 2013 Stephen Mathieson
// MIT licensed
//

/**************************************************************************
 
(The MIT License)

Copyright (c) 2013 Stephen Mathieson <me@stephenmathieson.com>

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the 'Software'),
to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR
ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

**************************************************************************/

#include <stdlib.h>
#include <string.h>
#include "occurrences/occurrences.h"
#include "strdup/strdup.h"
#include "str-replace.h"

/*
 * Replace all occurrences of `sub` with `replace` in `str`
 */

char *
str_replace(const char *str, const char *sub, const char *replace) {
  char *pos = (char *) str;
  int count = occurrences(sub, str);

  if (0 >= count) return strdup(str);

  int size = (
        strlen(str)
      - (strlen(sub) * count)
      + strlen(replace) * count
    ) + 1;

  char *result = (char *) malloc(size);
  if (NULL == result) return NULL;
  memset(result, '\0', size);
  char *current;
  while ((current = strstr(pos, sub))) {
    int len = current - pos;
    strncat(result, pos, len);
    strncat(result, replace, strlen(replace));
    pos = current + strlen(sub);
  }

  if (pos != (str + strlen(str))) {
    strncat(result, pos, (str - pos));
  }

  return result;
}
