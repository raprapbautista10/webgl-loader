#if 0  // A cute trick to making this .cc self-building from shell.
g++ $0 -O2 -Wall -Werror -o `basename $0 .cc`;
exit;
#endif
// Copyright 2011 Google Inc. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License"); you
// may not use this file except in compliance with the License. You
// may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
// implied. See the License for the specific language governing
// permissions and limitations under the License.

#include "../base.h"
#include "../stream.h"

#include <iostream>  // DO NOT SUBMIT
#include <string>

namespace webgl_loader {

class BufferedInputTest {
 public:
  void TestFromMemory() {
    const char bytes[] = { 1, 2, 3, 4, 5 };
    BufferedInput bi(bytes, sizeof(bytes));
    CHECK(kNoError == bi.error());
    int sum = 0;
    while (bi.cursor != bi.end()) {
      sum += *bi.cursor++ ;
    }
    CHECK(15 == sum);
    CHECK(kNoError == bi.error());
    bi.Refill();
    CHECK(bi.begin() == bi.cursor);
    CHECK(kEndOfFile == bi.error());
    sum = 0;
    while (bi.cursor != bi.end()) {
      sum += *bi.cursor++;
    }
    CHECK(0 == sum);
  }
};

}  // namespace webgl_loader

int main() {
  webgl_loader::BufferedInputTest tester;
  tester.TestFromMemory();
    
  return 0;
}
