#include <mbedtls/sha1.h>
#include <mbedtls/md5.h>

extern "C" {

// SHA1
void SHA1Init(mbedtls_sha1_context* ctx) { mbedtls_sha1_init(ctx); }
void SHA1Update(mbedtls_sha1_context* ctx, const unsigned char* data, size_t len) {
    mbedtls_sha1_update_ret(ctx, data, len);
}
void SHA1Final(unsigned char output[20], mbedtls_sha1_context* ctx) {
    mbedtls_sha1_finish_ret(ctx, output);
}

// MD5 wrappers
#ifdef mbedtls_md5_starts
#undef mbedtls_md5_starts
#endif
#ifdef mbedtls_md5_update
#undef mbedtls_md5_update
#endif
#ifdef mbedtls_md5_finish
#undef mbedtls_md5_finish
#endif

void mbedtls_md5_starts(mbedtls_md5_context* ctx) {
    mbedtls_md5_starts_ret(ctx);
}
void mbedtls_md5_update(mbedtls_md5_context* ctx, const unsigned char* data, size_t len) {
    mbedtls_md5_update_ret(ctx, data, len);
}
void mbedtls_md5_finish(mbedtls_md5_context* ctx, unsigned char output[16]) {
    mbedtls_md5_finish_ret(ctx, output);
}

}