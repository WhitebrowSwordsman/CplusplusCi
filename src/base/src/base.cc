// Created by WhitebrowSwordsman on 2022/04/22.
//
// Copyright (c) 2022 The CplusplusCi Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/base.h"

BEGIN_NAMESPACE_BASE

BASE_API const char* GetVersion() { return "1.0.0.001"; }
BASE_API const char* GetOsName() {
#if defined(OS_WINDOWS)
  return "Windows";
#else
  return "Unknown system type";
#endif
}
BASE_API const char* GetName() { return "Base"; }

END_NAMESPACE_BASE
