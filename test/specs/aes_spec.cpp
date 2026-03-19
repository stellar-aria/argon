#include "argon.hpp"
#include "argon/features.h"
#include "cppspec.hpp"

// clang-format off

// AES wrappers are only available when __ARM_FEATURE_CRYPTO is defined.
// On targets that lack crypto (e.g., SIMDe x86, baseline cortex-a9),
// all tests in this file are skipped at compile time.

#if ARGON_HAS_CRYPTO && !defined(ARGON_PLATFORM_MVE)

auto describe_aes_encrypt_decrypt = describe("AES encrypt/decrypt round-trip", ${
  it("AesEncrypt then AesDecrypt with zero key recovers the input", _{
    // AES single-round: state = AesDecrypt(AesEncrypt(state, key), key)
    // Note: this is NOT a full AES round — it's AddRoundKey+SubBytes+ShiftRows only.
    std::array<uint8_t, 16> state_arr;
    std::array<uint8_t, 16> key_arr;
    std::iota(state_arr.begin(), state_arr.end(), uint8_t{0});
    key_arr.fill(uint8_t{0});

    auto state = Argon<uint8_t>::Load(state_arr.data());
    auto key   = Argon<uint8_t>::Load(key_arr.data());

    auto encrypted = state.AesEncrypt(key);
    auto decrypted = encrypted.AesDecrypt(key);

    expect(decrypted.to_array()).to_equal(state_arr);
  });
});

auto describe_aes_mix_columns = describe("AesMixColumns / AesInverseMixColumns round-trip", ${
  it("MixColumns followed by InverseMixColumns recovers the input", _{
    std::array<uint8_t, 16> input_arr;
    std::iota(input_arr.begin(), input_arr.end(), uint8_t{1});

    auto v = Argon<uint8_t>::Load(input_arr.data());
    auto mixed    = v.AesMixColumns();
    auto unmixed  = mixed.AesInverseMixColumns();

    expect(unmixed.to_array()).to_equal(input_arr);
  });
});

CPPSPEC_MAIN(
  describe_aes_encrypt_decrypt,
  describe_aes_mix_columns
);

#else

// Crypto not available — provide a no-op test so CTest still runs this target.
auto describe_aes_skipped = describe("AES (skipped: no __ARM_FEATURE_CRYPTO)", ${
  it("is skipped on this platform", _{
    expect(true).to_be_true();
  });
});

CPPSPEC_MAIN(describe_aes_skipped);

#endif
