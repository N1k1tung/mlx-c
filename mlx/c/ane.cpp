#include "mlx/c/ane.h"

#include <stdexcept>

#include "mlx/backend/ane/diagnostics.h"
#include "mlx/backend/ane/runtime.h"
#include "mlx/c/error.h"
#include "mlx/c/private/mlx.h"
#include "mlx/c/private/string.h"

extern "C" int mlx_ane_get_diagnostics(mlx_ane_diagnostics_snapshot* res) {
  try {
    if (res == nullptr) {
      throw std::invalid_argument("mlx_ane_get_diagnostics: null output pointer");
    }
    auto snapshot = mlx::core::ane::get_diagnostics();
    res->total_ops = static_cast<uint64_t>(snapshot.total_ops);
    res->supported_ops = static_cast<uint64_t>(snapshot.supported_ops);
    res->ane_dispatches = static_cast<uint64_t>(snapshot.ane_dispatches);
    res->gpu_fallbacks = static_cast<uint64_t>(snapshot.gpu_fallbacks);
    res->cpu_fallbacks = static_cast<uint64_t>(snapshot.cpu_fallbacks);
    res->compile_cache_hits = static_cast<uint64_t>(snapshot.compile_cache_hits);
    res->compile_cache_misses =
        static_cast<uint64_t>(snapshot.compile_cache_misses);
    res->partition_boundaries =
        static_cast<uint64_t>(snapshot.partition_boundaries);
  } catch (std::exception& e) {
    mlx_error(e.what());
    return 1;
  }
  return 0;
}

extern "C" int mlx_ane_reset_diagnostics(void) {
  try {
    mlx::core::ane::reset_diagnostics();
  } catch (std::exception& e) {
    mlx_error(e.what());
    return 1;
  }
  return 0;
}

extern "C" int mlx_ane_runtime_is_available(bool* res) {
  try {
    if (res == nullptr) {
      throw std::invalid_argument(
          "mlx_ane_runtime_is_available: null output pointer");
    }
    *res = mlx::core::ane::runtime().is_runtime_available();
  } catch (std::exception& e) {
    mlx_error(e.what());
    return 1;
  }
  return 0;
}

extern "C" int mlx_ane_runtime_unavailable_reason(mlx_string* res) {
  try {
    if (res == nullptr) {
      throw std::invalid_argument(
          "mlx_ane_runtime_unavailable_reason: null output pointer");
    }
    auto reason = mlx::core::ane::runtime().runtime_unavailable_reason();
    mlx_string_set_(*res, reason);
  } catch (std::exception& e) {
    mlx_error(e.what());
    return 1;
  }
  return 0;
}

extern "C" int mlx_ane_pin_to_surface(mlx_array arr) {
  try {
    auto& a = mlx_array_get_(arr);
    return mlx::core::ane::runtime().pin_to_surface(a) ? 0 : 1;
  } catch (std::exception& e) {
    mlx_error(e.what());
    return 1;
  }
}
