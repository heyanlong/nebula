/* Copyright (c) 2020 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License.
 */

#include "graph/executor/admin/ResetBalanceExecutor.h"

#include "graph/planner/plan/Admin.h"

namespace nebula {
namespace graph {

folly::Future<Status> ResetBalanceExecutor::execute() {
  SCOPED_TIMER(&execTime_);
  return resetBalance();
}

folly::Future<Status> ResetBalanceExecutor::resetBalance() {
  return qctx()
      ->getMetaClient()
      ->balance({}, false, true)
      .via(runner())
      .thenValue([this](StatusOr<int64_t> resp) {
        SCOPED_TIMER(&execTime_);
        if (!resp.ok()) {
          LOG(ERROR) << resp.status();
          return resp.status();
        }
        DataSet v({"ID"});
        v.emplace_back(Row({resp.value()}));
        return finish(std::move(v));
      });
}

}  // namespace graph
}  // namespace nebula
