/*
 * Copyright (C) 2010-2019 The ESPResSo project
 * Copyright (C) 2002,2003,2004,2005,2006,2007,2008,2009,2010
 *   Max-Planck-Institute for Polymer Research, Theory Group
 *
 * This file is part of ESPResSo.
 *
 * ESPResSo is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ESPResSo is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SCRIPT_INTERFACE_OBSERVABLES_CYLINDRICALPIDPROFILEOBSERVABLE_HPP
#define SCRIPT_INTERFACE_OBSERVABLES_CYLINDRICALPIDPROFILEOBSERVABLE_HPP

#include "script_interface/auto_parameters/AutoParameters.hpp"

#include "Observable.hpp"
#include "core/observables/CylindricalPidProfileObservable.hpp"

#include <boost/range/algorithm.hpp>

#include <cstddef>
#include <iterator>
#include <memory>
#include <type_traits>
#include <vector>

namespace ScriptInterface {
namespace Observables {

template <typename CoreObs>
class CylindricalPidProfileObservable
    : public AutoParameters<CylindricalPidProfileObservable<CoreObs>,
                            Observable> {
  using Base =
      AutoParameters<CylindricalPidProfileObservable<CoreObs>, Observable>;

public:
  static_assert(std::is_base_of<::Observables::CylindricalPidProfileObservable,
                                CoreObs>::value,
                "");
  using Base::Base;
  CylindricalPidProfileObservable() {
    this->add_parameters({
        {"ids",
         [this](const Variant &v) {
           cylindrical_pid_profile_observable()->ids() =
               get_value<std::vector<int>>(v);
         },
         [this]() { return cylindrical_pid_profile_observable()->ids(); }},
        {"center",
         [this](const Variant &v) {
           cylindrical_pid_profile_observable()->center =
               get_value<::Utils::Vector3d>(v);
         },
         [this]() { return cylindrical_pid_profile_observable()->center; }},
        {"axis",
         [this](const Variant &v) {
           cylindrical_pid_profile_observable()->axis =
               get_value<Utils::Vector3d>(v);
         },
         [this]() { return cylindrical_pid_profile_observable()->axis; }},
        {"n_r_bins",
         [this](const Variant &v) {
           cylindrical_pid_profile_observable()->n_bins[0] =
               static_cast<size_t>(get_value<int>(v));
         },
         [this]() {
           return static_cast<int>(
               cylindrical_pid_profile_observable()->n_bins[0]);
         }},
        {"n_phi_bins",
         [this](const Variant &v) {
           cylindrical_pid_profile_observable()->n_bins[1] =
               static_cast<size_t>(get_value<int>(v));
         },
         [this]() {
           return static_cast<int>(
               cylindrical_pid_profile_observable()->n_bins[1]);
         }},
        {"n_z_bins",
         [this](const Variant &v) {
           cylindrical_pid_profile_observable()->n_bins[2] =
               static_cast<size_t>(get_value<int>(v));
         },
         [this]() {
           return static_cast<int>(
               cylindrical_pid_profile_observable()->n_bins[2]);
         }},
        {"min_r",
         [this](const Variant &v) {
           cylindrical_pid_profile_observable()->limits[0].first =
               get_value<double>(v);
         },
         [this]() {
           return cylindrical_pid_profile_observable()->limits[0].first;
         }},
        {"min_phi",
         [this](const Variant &v) {
           cylindrical_pid_profile_observable()->limits[1].first =
               get_value<double>(v);
         },
         [this]() {
           return cylindrical_pid_profile_observable()->limits[1].first;
         }},
        {"min_z",
         [this](const Variant &v) {
           cylindrical_pid_profile_observable()->limits[2].first =
               get_value<double>(v);
         },
         [this]() {
           return cylindrical_pid_profile_observable()->limits[2].first;
         }},
        {"max_r",
         [this](const Variant &v) {
           cylindrical_pid_profile_observable()->limits[0].second =
               get_value<double>(v);
         },
         [this]() {
           return cylindrical_pid_profile_observable()->limits[0].second;
         }},
        {"max_phi",
         [this](const Variant &v) {
           cylindrical_pid_profile_observable()->limits[1].second =
               get_value<double>(v);
         },
         [this]() {
           return cylindrical_pid_profile_observable()->limits[1].second;
         }},
        {"max_z",
         [this](const Variant &v) {
           cylindrical_pid_profile_observable()->limits[2].second =
               get_value<double>(v);
         },
         [this]() {
           return cylindrical_pid_profile_observable()->limits[2].second;
         }},
    });
  };

  void do_construct(VariantMap const &params) override {
    m_observable =
        make_shared_from_args<CoreObs, std::vector<int>, Utils::Vector3d,
                              Utils::Vector3d, int, int, int, double, double,
                              double, double, double, double>(
            params, "ids", "center", "axis", "n_r_bins", "n_phi_bins",
            "n_z_bins", "min_r", "max_r", "min_phi", "max_phi", "min_z",
            "max_z");
  }

  Variant do_call_method(std::string const &method,
                         VariantMap const &parameters) override {
    if (method == "edges") {
      std::vector<Variant> variant_edges;
      boost::copy(cylindrical_pid_profile_observable()->edges(),
                  std::back_inserter(variant_edges));
      return variant_edges;
    }
    return Base::do_call_method(method, parameters);
  }

  std::shared_ptr<::Observables::Observable> observable() const override {
    return m_observable;
  }

  virtual std::shared_ptr<::Observables::CylindricalPidProfileObservable>
  cylindrical_pid_profile_observable() const {
    return m_observable;
  }

private:
  std::shared_ptr<CoreObs> m_observable;
};

} /* namespace Observables */
} /* namespace ScriptInterface */

#endif
