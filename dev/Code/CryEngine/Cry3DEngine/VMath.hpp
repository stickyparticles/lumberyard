/*
* All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
* its licensors.
*
* For complete copyright and license terms please see the LICENSE at the root of this
* distribution (the "License"). All use of this software is governed by the License,
* or, if provided, by the license below or the license accompanying this file. Do not
* remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*
*/
// Original file Copyright Crytek GMBH or its affiliates, used under license.

// Description : unified vector math lib


#ifndef __VMATH__
#define __VMATH__

#define VEC4_SSE

//#include <math.h>
#include <Cry_Math.h>

namespace NVMath
{
#if defined(_CPU_NEON)
    #include "VMath_NEON.hpp"
#elif (defined(WIN32) || defined(WIN64) || defined(DURANGO) || defined(ORBIS) || defined(LINUX) || defined(MAC) || defined(IOS_SIMULATOR)) && (defined(VEC4_SSE) || defined(VEC4_SSE4))
    #include "VMath_SSE.hpp"
#else
    #include "VMath_C.hpp"
#endif
}


#endif

