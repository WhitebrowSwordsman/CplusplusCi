// Created by WhitebrowSwordsman on 2022/04/22.
//
// Copyright (c) 2022 The CplusplusCi Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <iostream>

#include "base/base.h"

int main() {
  std::cout << BASE::GetOsName() << " " << BASE::GetName() << " " << BASE::GetVersion() << std::endl;
  getchar();
  return 0;
}
