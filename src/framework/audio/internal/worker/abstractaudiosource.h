/*
 * SPDX-License-Identifier: GPL-3.0-only
 * MuseScore-CLA-applies
 *
 * MuseScore
 * Music Composition & Notation
 *
 * Copyright (C) 2021 MuseScore BVBA and others
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#ifndef MU_AUDIO_ABSTRACTAUDIOSOURCE_H
#define MU_AUDIO_ABSTRACTAUDIOSOURCE_H

#include "iaudiosource.h"

namespace mu::audio {
class AbstractAudioSource : public IAudioSource
{
public:
    virtual ~AbstractAudioSource() = default;

    virtual void setSampleRate(unsigned int sampleRate) override;

    mu::async::Channel<unsigned int> streamsCountChanged() const override;
    const float* data() const override;
    virtual void setBufferSize(unsigned int samples) override;

protected:
    unsigned int m_sampleRate = 1;
    std::vector<float> m_buffer = {};
    async::Channel<unsigned int> m_streamsCountChanged;
};
}

#endif // MU_AUDIO_ABSTRACTAUDIOSOURCE_H
