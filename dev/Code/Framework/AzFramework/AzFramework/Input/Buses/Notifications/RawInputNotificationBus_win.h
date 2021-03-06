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

#pragma once

#include <AzCore/EBus/EBus.h>

typedef struct tagRAWINPUT RAWINPUT;
typedef struct tagRID_DEVICE_INFO RID_DEVICE_INFO;

////////////////////////////////////////////////////////////////////////////////////////////////////
namespace AzFramework
{
    ////////////////////////////////////////////////////////////////////////////////////////////////
    //! EBus interface used to listen for raw win input events broadcast by the system. Applications
    //! that want RawInput events to be processed by the AzFramework input system must broadcast all
    //! WM_INPUT events received by the system's WndProc, which is the lowest level we can get input.
    //!
    //! It's possible to receive multiple events per button/key per frame, and (depending on how the
    //! windows event loop is pumped) it is also possible that events could be sent from any thread,
    //! however it is assumed they will always be sent from the WndProc function on the main thread.
    //!
    //! This EBus is intended primarily for the AzFramework input system to process win input events.
    //! Most systems that need to process input should use the generic AzFramework input interfaces,
    //! but if necessary it is perfectly valid to connect directly to this EBus for raw win events.
    class RawInputNotificationsWin : public AZ::EBusTraits
    {
    public:
        ////////////////////////////////////////////////////////////////////////////////////////////
        //! EBus Trait: raw input notifications are addressed to a single address
        static const AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;

        ////////////////////////////////////////////////////////////////////////////////////////////
        //! EBus Trait: raw input notifications can be handled by multiple listeners
        static const AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Multiple;

        ////////////////////////////////////////////////////////////////////////////////////////////
        //! Default destructor
        virtual ~RawInputNotificationsWin() = default;

        ////////////////////////////////////////////////////////////////////////////////////////////
        //! Process raw input events (assumed to be dispatched on the main thread)
        //! \param[in] rawInput The raw input data
        virtual void OnRawInputEvent(const RAWINPUT& /*rawInput*/) {}

        ////////////////////////////////////////////////////////////////////////////////////////////
        //! Process raw input device connection events (assumed to be dispatched on the main thread)
        virtual void OnRawInputDeviceChangeEvent() {}

        ////////////////////////////////////////////////////////////////////////////////////////////
        //! Process raw WM_CHAR events (assumed to be dispatched on the main thread)
        //! \param[in] codeUnitUTF16 The UTF16 unicode code-unit. Note that this may not correspond
        //! directly to a single UTF16 code-point (or character); each individual event may be part
        //! of a two code-unit 'surrogate pair' that together defines a single UTF16 code-point.
        virtual void OnRawInputCodeUnitUTF16Event(uint16_t /*codeUnitUTF16*/) {}
    };
    using RawInputNotificationBusWin = AZ::EBus<RawInputNotificationsWin>;
} // namespace AzFramework
