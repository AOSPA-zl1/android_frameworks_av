/*
 * Copyright (C) 2012 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef SOFT_AAC_ENCODER_2_H_

#define SOFT_AAC_ENCODER_2_H_

#include "SimpleSoftOMXComponent.h"

#include "aacenc_lib.h"

namespace android {

struct SoftAACEncoder2 : public SimpleSoftOMXComponent {
    SoftAACEncoder2(
            const char *name,
            const OMX_CALLBACKTYPE *callbacks,
            OMX_PTR appData,
            OMX_COMPONENTTYPE **component);

protected:
    virtual ~SoftAACEncoder2();

    virtual OMX_ERRORTYPE internalGetParameter(
            OMX_INDEXTYPE index, OMX_PTR params);

    virtual OMX_ERRORTYPE internalSetParameter(
            OMX_INDEXTYPE index, const OMX_PTR params);

    virtual void onQueueFilled(OMX_U32 portIndex);

    virtual void onReset();

private:
    enum {
        kNumBuffers             = 4,
        kNumSamplesPerFrame     = 1024
    };

    HANDLE_AACENCODER mAACEncoder;

    OMX_U32 mNumChannels;
    OMX_U32 mSampleRate;
    OMX_U32 mBitRate;
    OMX_S32 mSBRMode;
    OMX_S32 mSBRRatio;
    OMX_U32 mAACProfile;

    bool mSentCodecSpecificData;
    size_t mInputSize;
    int16_t *mInputFrame;
    size_t mAllocatedFrameSize;
    int64_t mInputTimeUs;

    bool mSawInputEOS;

    bool mSignalledError;

    void initPorts();
    status_t initEncoder();

    status_t setAudioParams();

    DISALLOW_EVIL_CONSTRUCTORS(SoftAACEncoder2);
};

}  // namespace android

#endif  // SOFT_AAC_ENCODER_2_H_
