/* Copyright (c) 2019 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License.
 */

#include "common/base/SlowOpTracker.h"

#include "common/base/Base.h"
#include "common/time/WallClock.h"

DEFINE_int64(slow_op_threshhold_ms, 50, "default threshhold for slow operation");
