#include "spec.hpp"

int main()
{
  _(1 + 1) SHOULD(== 2);
  _(1 + 2) SHOULD(== 2);
  _(1 + 2) SHOULD(== 3.0);
  return 0;
}
