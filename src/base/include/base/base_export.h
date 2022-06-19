// Created by WhitebrowSwordsman on 2022/04/22.
//
// Copyright (c) 2022 The CplusplusCi Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#if defined(BASE_COMPONENT_BUILD)
#if defined(WIN32)

#if defined(BASE_IMPLEMENTATION)
#define BASE_EXPORT __declspec(dllexport)
#else
#define BASE_EXPORT __declspec(dllimport)
#endif  // defined(BASE_IMPLEMENTATION)

#else  // defined(WIN32)
#if defined(BASE_IMPLEMENTATION)
#define BASE_EXPORT __attribute__((visibility("default")))
#else
#define BASE_EXPORT
#endif  // defined(BASE_IMPLEMENTATION)
#endif

#else  // defined(BASE_COMPONENT_BUILD)
#define BASE_EXPORT
#endif

#define BASE_API BASE_EXPORT

#define BEGIN_NAMESPACE_BASE namespace base {
#define END_NAMESPACE_BASE }
#define BASE base
