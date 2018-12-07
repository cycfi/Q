/*=============================================================================
   Copyright (c) 2014-2018 Joel de Guzman. All rights reserved.

   Distributed under the MIT License [ https://opensource.org/licenses/MIT ]
=============================================================================*/
#if !defined(CYCFI_Q_SQUARE_HPP_DECEMBER_24_2015)
#define CYCFI_Q_SQUARE_HPP_DECEMBER_24_2015

#include <q/support/phase.hpp>
#include <q/detail/antialiasing.hpp>

namespace cycfi { namespace q
{
   ////////////////////////////////////////////////////////////////////////////
   // basic square-wave synthesizer (not bandwidth limited)
   ////////////////////////////////////////////////////////////////////////////
   struct basic_square_synth
   {
      constexpr float operator()(phase p) const
      {
         constexpr auto middle = phase::max() / 2;
         return p < middle ? 1.0f : -1.0f;
      }
   };

   constexpr auto basic_square = basic_square_synth{};

   ////////////////////////////////////////////////////////////////////////////
   // square-wave synthesizer (bandwidth limited using poly_blep)
   ////////////////////////////////////////////////////////////////////////////
   struct square_synth
   {
      constexpr float operator()(phase p, phase dt) const
      {
         constexpr auto middle = phase::max() / 2;
         auto r = p < middle ? 1.0f : -1.0f;

         // Correct rising discontinuity
         r += detail::poly_blep(p, dt);

         // Correct falling discontinuity
         r -= detail::poly_blep(p + middle, dt);

         return r;
      }
   };

   constexpr auto square = square_synth{};
}}

#endif