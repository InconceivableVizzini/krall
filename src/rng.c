// SPDX-License-Identifier: GPL-2.0-only

#include "krall/rng.h"
#include <assert.h>
#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/random.h>

uint32_t random_number_generator_state[4];

void initialize_random_number_generator(void) {
  ssize_t bytes_or_status =
      getrandom(random_number_generator_state,
                sizeof random_number_generator_state, GRND_NONBLOCK);
  while ((bytes_or_status == -1 && (errno == EAGAIN || errno == EINTR)) ||
         (bytes_or_status >= 0 &&
          bytes_or_status < (ssize_t)sizeof random_number_generator_state)) {
    bytes_or_status =
        getrandom(random_number_generator_state,
                  sizeof random_number_generator_state, GRND_NONBLOCK);
  }
}

// xoshiro128++ 1.0 was devised by David Blackman and Sebastiano Vigna
uint32_t random_u32(void) {
  const uint32_t mixed_up_bits =
      random_number_generator_state[0] + random_number_generator_state[3];
  const uint32_t random_number =
      ((mixed_up_bits << 7) | (mixed_up_bits >> 25)) +
      random_number_generator_state[0];
  const uint32_t bigified_number = random_number_generator_state[1] << 9;
  random_number_generator_state[2] ^= random_number_generator_state[0];
  random_number_generator_state[3] ^= random_number_generator_state[1];
  random_number_generator_state[1] ^= random_number_generator_state[2];
  random_number_generator_state[0] ^= random_number_generator_state[3];

  random_number_generator_state[2] ^= bigified_number;
  random_number_generator_state[3] = ((random_number_generator_state[3] << 11) |
                                      (random_number_generator_state[3] >> 21));

  return random_number;
}
