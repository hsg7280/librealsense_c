// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2020 Intel Corporation. All Rights Reserved.

#include "../func/func-common.h"
#include "../../include/librealsense2/hpp/rs_frame.hpp"
#include <iostream>

using namespace rs2;

TEST_CASE("test video_stream_profile operator==", "[live]")
{
    // Test that for 2 video_stream_profile objects, if width and height are different
    // then, video_stream_profile.operator== returns false.

    auto devices = find_devices_by_product_line_or_exit(RS2_PRODUCT_LINE_ANY_INTEL);
    auto dev = devices[0];

    auto depth_sens = dev.first< rs2::depth_sensor >();

    stream_profile profile0, profile1;
    std::vector< stream_profile > stream_profiles;
    REQUIRE_NOTHROW(stream_profiles = depth_sens.get_stream_profiles());
    REQUIRE_NOTHROW(stream_profiles.size() > 1);
    profile0 = stream_profiles[0];
    video_stream_profile vprofile0 = profile0.as<video_stream_profile>();

    for (auto profile : stream_profiles)
    {
        if (profile == profile0)
        {
            video_stream_profile vprofile = profile.as<video_stream_profile>();
            if (vprofile0.width() == vprofile.width() &&
                vprofile0.height() == vprofile.height())
            {
                REQUIRE(vprofile0 == vprofile);
            }
            else
            {
                REQUIRE(!(vprofile0 == vprofile));
            }
        }
    }
}
