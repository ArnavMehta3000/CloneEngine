#pragma once

namespace Clone::Common
{
// Convert value to string
#define STRINGIFY(x) #x
// Convert value to wide string
#define STRINGIFYW(value) L ## #value
// Convert frame rate to delta time
#define FPS_TO_DT(fps) 1.0 / fps
// Convert delta time to frame rate
#define DT_TO_FPS(dt) 1.0 / dt
}